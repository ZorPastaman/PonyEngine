/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:ServiceManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :InterfaceContainer;
import :ServiceContainer;
import :TickableServiceInfo;

export namespace PonyEngine::Application
{
	/// @brief Service manager.
	class ServiceManager final : private IServiceModuleContext
	{
	public:
		/// @brief Creates a service manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit ServiceManager(IApplicationContext& application) noexcept;
		ServiceManager(const ServiceManager&) = delete;
		ServiceManager(ServiceManager&&) = delete;

		~ServiceManager() noexcept;

		[[nodiscard("Must be used to remove")]]
		virtual ServiceHandle AddService(const std::function<ServiceData(IApplicationContext&)>& factory) override;
		virtual void RemoveService(ServiceHandle handle) override;

		/// @brief Finds a service interface.
		/// @param type Service interface type.
		/// @return Service interface; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		void* FindService(std::type_index type) noexcept;
		/// @brief Finds a service interface.
		/// @param type Service interface type.
		/// @return Service interface; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		const void* FindService(std::type_index type) const noexcept;

		/// @brief Begins the services.
		void Begin();
		/// @brief Ends the services.
		void End() noexcept;
		/// @brief Ticks the services.
		void Tick();

		/// @brief Gets the public service module context.
		/// @return Service module context.
		[[nodiscard("Pure function")]]
		IServiceModuleContext& PublicServiceModuleContext() noexcept;
		/// @brief Gets the public service module context.
		/// @return Service module context.
		[[nodiscard("Pure function")]]
		const IServiceModuleContext& PublicServiceModuleContext() const noexcept;

		ServiceManager& operator =(const ServiceManager&) = delete;
		ServiceManager& operator =(ServiceManager&&) = delete;

	private:
		/// @brief Updates tickable services vector.
		void UpdateTickableServices();

		/// @brief Begins the services.
		/// @param count How many services are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the services.
		/// @param count How many services to end.
		void End(std::size_t count) noexcept;

		IApplicationContext* application; ///< Application context.

		ServiceContainer serviceContainer; ///< Service container.

		std::vector<ITickableService*> tickableServices; ///< Tickable services.
		std::unordered_map<std::type_index, void*> serviceInterfaces; ///< Service interfaces.

		ServiceHandle nextServiceHandle; ///< Next service handle.
	};
}

namespace PonyEngine::Application
{
	ServiceManager::ServiceManager(IApplicationContext& application) noexcept :
		application{&application},
		nextServiceHandle{.id = 1u}
	{
	}

	ServiceManager::~ServiceManager() noexcept
	{
		if (serviceContainer.Size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Services weren't removed:");
			for (std::size_t i = 0uz; i < serviceContainer.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Service: '{}'.", typeid(serviceContainer.Service(i)).name());
			}
		}
	}

	void* ServiceManager::FindService(const std::type_index type) noexcept
	{
		if (const auto pair = serviceInterfaces.find(type); pair != serviceInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	const void* ServiceManager::FindService(const std::type_index type) const noexcept
	{
		if (const auto pair = serviceInterfaces.find(type); pair != serviceInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	ServiceHandle ServiceManager::AddService(const std::function<ServiceData(IApplicationContext&)>& factory)
	{
		if (!nextServiceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more service handles available");
		}

		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Service can be added only on start-up");
		}
		const ServiceData data = factory(*application);
		if (!data.service) [[unlikely]]
		{
			throw std::invalid_argument("Service is nullptr");
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service...", typeid(*data.service).name());
		if (serviceContainer.IndexOf(*data.service) < serviceContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Service has already been added");
		}
		if (data.tickableService && static_cast<IService*>(data.tickableService) != data.service.get()) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect tickable service");
		}
		for (const auto [interfaceType, interface] : data.publicInterfaces)
		{
			if (serviceContainer.ContainsInterface(interfaceType)) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Interface of type '{}' has already been added", interfaceType.name()));
			}
			if (!interface) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Interface of type '{}' is nullptr", interfaceType.name()));
			}
		}

		const ServiceHandle currentHandle = nextServiceHandle;
		serviceContainer.Add(currentHandle, data);
		const InterfaceContainer& interfaceContainer = serviceContainer.Interfaces(serviceContainer.Size() - 1uz);
		try
		{
			for (std::size_t i = 0uz; i < interfaceContainer.Size(); ++i)
			{
				serviceInterfaces[interfaceContainer.Type(i)] = interfaceContainer.Interface(i);
			}
		}
		catch (...)
		{
			for (std::size_t i = 0uz; i < interfaceContainer.Size(); ++i)
			{
				serviceInterfaces.erase(interfaceContainer.Type(i));
			}
			serviceContainer.Remove(serviceContainer.Size() - 1uz);
		}
		++nextServiceHandle.id;
		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service done. Handle: '0x{:X}'.", typeid(*data.service).name(), currentHandle.id);

		return currentHandle;
	}

	void ServiceManager::RemoveService(const ServiceHandle handle)
	{
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Service can be removed only on start-up or shut-down");
		}

		if (const std::size_t index = serviceContainer.IndexOf(handle); index < serviceContainer.Size()) [[likely]]
		{
			const char* const serviceName = typeid(serviceContainer.Service(index)).name();
			PONY_LOG(application->Logger(), Log::LogType::Info, "Removing '{}' service...", serviceName);
			const InterfaceContainer& interfaceContainer = serviceContainer.Interfaces(index);
			for (std::size_t i = 0uz; i < interfaceContainer.Size(); ++i)
			{
				serviceInterfaces.erase(interfaceContainer.Type(i));
			}

			if (const ITickableService* const tickableService = serviceContainer.TickableService(index).tickableService)
			{
				if (const auto position = std::ranges::find(tickableServices, tickableService); position != tickableServices.cend())
				{
					tickableServices.erase(position);
				}
			}

			serviceContainer.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "Removing '{}' service done. Handle: '0x{:X}'.", serviceName, handle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Service not found");
		}
	}

	void ServiceManager::Begin()
	{
		assert(application->FlowState() == FlowState::Beginning && "Incorrect flow state.");

		UpdateTickableServices();

		std::size_t begunServicesCount = 0uz;
		try
		{
			Begin(begunServicesCount);
		}
		catch (...)
		{
			End(begunServicesCount);
			throw;
		}
	}

	void ServiceManager::End() noexcept
	{
		assert(application->FlowState() == FlowState::Ending && "Incorrect flow state.");

		End(serviceContainer.Size());
	}

	void ServiceManager::Tick()
	{
		assert(application->FlowState() == FlowState::Running && "Incorrect flow state.");

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking application services.");
		for (ITickableService* const tickableService : tickableServices)
		{
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking '{}' service.", typeid(*tickableService).name());
				tickableService->Tick();
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ticking '{}' service.", typeid(*tickableService).name());
				throw;
			}
		}
	}

	IServiceModuleContext& ServiceManager::PublicServiceModuleContext() noexcept
	{
		return *this;
	}

	const IServiceModuleContext& ServiceManager::PublicServiceModuleContext() const noexcept
	{
		return *this;
	}

	void ServiceManager::UpdateTickableServices()
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting tickable services...");
		std::vector<TickableServiceInfo> orderedTickableServices;
		orderedTickableServices.reserve(serviceContainer.Size());
		for (std::size_t i = 0uz; i < serviceContainer.Size(); ++i)
		{
			if (const TickableServiceInfo& info = serviceContainer.TickableService(i); info.tickableService)
			{
				orderedTickableServices.push_back(info);
			}
		}
		std::ranges::sort(orderedTickableServices, [](const TickableServiceInfo& lhs, const TickableServiceInfo& rhs) noexcept
		{
			return lhs.tickOrder < rhs.tickOrder;
		});

		tickableServices.clear();
		tickableServices.reserve(orderedTickableServices.size());
		for (std::size_t i = 0uz; i < orderedTickableServices.size(); ++i)
		{
			ITickableService* const tickableService = orderedTickableServices[i].tickableService;
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Service: '{}'.", typeid(*tickableService).name());
			PONY_LOG_IF(i > 0uz && orderedTickableServices[i].tickOrder == orderedTickableServices[i - 1].tickOrder, application->Logger(), Log::LogType::Warning,
				"'{}' and '{}' services have the same tick order: '{}'. It may cause unpredictable results.", 
				typeid(*orderedTickableServices[i - 1uz].tickableService).name(), typeid(*orderedTickableServices[i].tickableService).name(), orderedTickableServices[i].tickOrder);
			tickableServices.push_back(tickableService);
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting tickable services done.");
	}

	void ServiceManager::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application services...");
		for (std::size_t i = 0uz; i < serviceContainer.Size(); ++i)
		{
			IService& service = serviceContainer.Service(i);

			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' service...", typeid(service).name());
				service.Begin();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' service done.", typeid(service).name());
				++count;
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On beginning '{}' service.", typeid(service).name());
				throw;
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application services done.");
	}

	void ServiceManager::End(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application services...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			IService& service = serviceContainer.Service(i);
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' service...", typeid(service).name());
				service.End();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' service done.", typeid(service).name());
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ending '{}' service.", typeid(service).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application services done.");
	}
}
