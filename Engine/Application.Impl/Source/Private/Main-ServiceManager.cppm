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
	class ServiceManager final : public IServiceModuleContext
	{
	public:
		/// @brief Creates a service manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit ServiceManager(IApplicationContext& application) noexcept;
		ServiceManager(const ServiceManager&) = delete;
		ServiceManager(ServiceManager&&) = delete;

		~ServiceManager() noexcept;

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

		[[nodiscard("Must be used to remove")]]
		virtual ServiceHandle AddService(const std::function<std::shared_ptr<IService>(IApplicationContext&)>& factory) override;
		virtual void RemoveService(ServiceHandle handle) override;

		ServiceManager& operator =(const ServiceManager&) = delete;
		ServiceManager& operator =(ServiceManager&&) = delete;

	private:
		/// @brief Tickable service adder.
		class TickableServiceAdder final : public ITickableServiceAdder
		{
		public:
			/// @brief Creates a tickable service adder.
			/// @param application Application context.
			/// @param container Tickable service container.
			[[nodiscard("Pure constructor")]]
			TickableServiceAdder(IApplicationContext& application, std::vector<TickableServiceInfo>& container) noexcept;
			TickableServiceAdder(const TickableServiceAdder&) = delete;
			TickableServiceAdder(TickableServiceAdder&&) = delete;

			~TickableServiceAdder() noexcept = default;

			virtual void Add(ITickableService& tickable, std::int32_t tickOrder) override;

			TickableServiceAdder& operator =(const TickableServiceAdder&) = delete;
			TickableServiceAdder& operator =(TickableServiceAdder&&) = delete;

		private:
			IApplicationContext* application; ///< Application context.

			std::vector<TickableServiceInfo>* container; ///< Tickable service container.
		};
		/// @brief Service interface adder.
		class ServiceInterfaceAdder final : public IServiceInterfaceAdder
		{
		public:
			/// @brief Creates a service interface adder.
			/// @param application Application context.
			/// @param container Service interface container.
			/// @param globalContainer Global interface container.
			[[nodiscard("Pure constructor")]]
			ServiceInterfaceAdder(IApplicationContext& application, InterfaceContainer& container, std::unordered_map<std::type_index, void*>& globalContainer) noexcept;
			ServiceInterfaceAdder(const ServiceInterfaceAdder&) = delete;
			ServiceInterfaceAdder(ServiceInterfaceAdder&&) = delete;

			~ServiceInterfaceAdder() noexcept = default;

			virtual void AddInterface(std::type_index type, void* interface) override;

			ServiceInterfaceAdder& operator =(const ServiceInterfaceAdder&) = delete;
			ServiceInterfaceAdder& operator =(ServiceInterfaceAdder&&) = delete;

		private:
			IApplicationContext* application; ///< Application context.

			InterfaceContainer* container; ///< Service interface container.
			std::unordered_map<std::type_index, void*>* globalContainer; ///< Global interface container.
		};

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

	ServiceHandle ServiceManager::AddService(const std::function<std::shared_ptr<IService>(IApplicationContext&)>& factory)
	{
		if (!nextServiceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more service handles available");
		}

		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Service can be added only on start-up");
		}

		const std::shared_ptr<IService> service = factory(*application);
		if (!service) [[unlikely]]
		{
			throw std::invalid_argument("Service is nullptr");
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service...", typeid(*service).name());
		if (serviceContainer.IndexOf(*service) < serviceContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Service has already been added");
		}

		const ServiceHandle currentHandle = nextServiceHandle;
		const std::size_t serviceIndex = serviceContainer.Add(currentHandle, service);

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding tickable service...");
			auto tickableAdder = TickableServiceAdder(*application, serviceContainer.TickableServices(serviceIndex));
			service->AddTickableServices(tickableAdder);
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding tickable service done.");
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On adding tickable services.");
			serviceContainer.Remove(serviceIndex);

			throw;
		}

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding service interfaces...");
			auto interfaceAdder = ServiceInterfaceAdder(*application, serviceContainer.Interfaces(serviceIndex), serviceInterfaces);
			service->AddInterfaces(interfaceAdder);
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding service interfaces done.");
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On adding service interfaces.");
			for (const std::type_index type : serviceContainer.Interfaces(serviceIndex).Types())
			{
				serviceInterfaces.erase(type);
			}
			serviceContainer.Remove(serviceIndex);

			throw;
		}

		++nextServiceHandle.id;
		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service done. Handle: '0x{:X}'.", typeid(*service).name(), currentHandle.id);

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
			for (const std::type_index type : serviceContainer.Interfaces(index).Types())
			{
				serviceInterfaces.erase(type);
			}
			for (const TickableServiceInfo& tickable : serviceContainer.TickableServices(index))
			{
				if (const auto position = std::ranges::find(tickableServices, tickable.tickableService); position != tickableServices.cend())
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

	ServiceManager::TickableServiceAdder::TickableServiceAdder(IApplicationContext& application, std::vector<TickableServiceInfo>& container) noexcept :
		application{&application},
		container{&container}
	{
	}

	void ServiceManager::TickableServiceAdder::Add(ITickableService& tickable, const std::int32_t tickOrder)
	{
		container->push_back(TickableServiceInfo{.tickableService = &tickable, .tickOrder = tickOrder});
		PONY_LOG(application->Logger(), Log::LogType::Info, "Tickable of type '{}' added.", typeid(tickable).name());
	}

	ServiceManager::ServiceInterfaceAdder::ServiceInterfaceAdder(IApplicationContext& application, InterfaceContainer& container, 
		std::unordered_map<std::type_index, void*>& globalContainer) noexcept :
		application{&application},
		container{&container},
		globalContainer{&globalContainer}
	{
	}

	void ServiceManager::ServiceInterfaceAdder::AddInterface(const std::type_index type, void* const interface)
	{
		if (container->IndexOf(type) < container->Size()) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Interface of type '{}' has already been added", type.name()));
		}
		if (globalContainer->contains(type)) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Interface of type '{}' has already been added by another service", type.name()));
		}

		if (!interface) [[unlikely]]
		{
			throw std::invalid_argument("Interface is nullptr");
		}

		container->Add(type, interface);
		try
		{
			globalContainer->emplace(type, interface);
		}
		catch (...)
		{
			container->Remove(container->Size() - 1uz);
			throw;
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Interface of type '{}' added.", type.name());
	}

	void ServiceManager::UpdateTickableServices()
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting tickable services...");
		std::size_t tickableCount = 0uz;
		for (std::size_t i = 0uz; i < serviceContainer.Size(); ++i)
		{
			tickableCount += serviceContainer.TickableServices(i).size();
		}

		std::vector<TickableServiceInfo> orderedTickableServices;
		orderedTickableServices.reserve(tickableCount);
		for (std::size_t i = 0uz; i < serviceContainer.Size(); ++i)
		{
			orderedTickableServices.append_range(serviceContainer.TickableServices(i));
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
