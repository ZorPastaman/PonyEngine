/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:ServiceManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Text;

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
		void* FindService(const std::type_info& type) noexcept;
		/// @brief Finds a service interface.
		/// @param type Service interface type.
		/// @return Service interface; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		const void* FindService(const std::type_info& type) const noexcept;

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

		std::vector<std::shared_ptr<IService>> services; ///< Services.
		std::vector<ITickableService*> tickableServices; ///< Tickable services.
		std::unordered_map<std::type_index, void*> serviceInterfaces; ///< Service interfaces.
		std::vector<ServiceData> serviceData; ///< Initial service data.
	};
}

namespace PonyEngine::Application
{
	ServiceManager::ServiceManager(IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	ServiceManager::~ServiceManager() noexcept
	{
		if (services.size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Services weren't removed:");
			for (const std::shared_ptr<IService>& service : services)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Service: '{}'.", typeid(*service).name());
			}
		}
	}

	void* ServiceManager::FindService(const std::type_info& type) noexcept
	{
		if (const auto pair = serviceInterfaces.find(type); pair != serviceInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	const void* ServiceManager::FindService(const std::type_info& type) const noexcept
	{
		if (const auto pair = serviceInterfaces.find(type); pair != serviceInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	ServiceHandle ServiceManager::AddService(const std::function<ServiceData(IApplicationContext&)>& factory)
	{
		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Service can be added only on start-up.");
		}
		const ServiceData data = factory(*application);
		if (!data.service) [[unlikely]]
		{
			throw std::invalid_argument("Service is nullptr.");
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service...", typeid(*data.service).name());

		if (data.tickableService && static_cast<IService*>(data.tickableService) != data.service.get()) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect tickable service.");
		}

		services.push_back(data.service);

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding service interfaces...");
			for (const auto& [interfaceType, interface] : data.publicInterfaces)
			{
				if (!interfaceType) [[unlikely]]
				{
					throw std::invalid_argument("Interface is nullptr.");
				}

				PONY_LOG(application->Logger(), Log::LogType::Debug, "Interface: '{}'.", interfaceType->name());
				if (serviceInterfaces.contains(*interfaceType)) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Interface of type '{}' has already been added.", interfaceType->name()));
				}
				if (!interface) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Interface of type '{}' is nullptr.", interfaceType->name()));
				}
				serviceInterfaces[*interfaceType] = interface;
			}
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding service interfaces done.");

			try
			{
				serviceData.push_back(data);
			}
			catch (...)
			{
				for (const std::type_info* interface : std::views::keys(data.publicInterfaces))
				{
					serviceInterfaces.erase(*interface);
				}

				throw;
			}
		}
		catch (...)
		{
			services.pop_back();
			throw;
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service done.", typeid(*data.service).name());

		return ServiceHandle{.id = data.service.get()};
	}

	void ServiceManager::RemoveService(const ServiceHandle handle)
	{
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Service can be removed only on start-up or shut-down.");
		}

		if (!handle.IsValid()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle.");
		}

		std::optional<std::size_t> indexOpt = std::nullopt;
		for (std::size_t i = services.size(); i-- > 0uz; )
		{
			if (services[i].get() == handle.id)
			{
				indexOpt = i;
				break;
			}
		}
		if (!indexOpt) [[unlikely]]
		{
			throw std::invalid_argument("Service not found.");
		}
		const std::size_t index = *indexOpt;

		const char* const serviceName = typeid(*services[index]).name();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Removing '{}' service...", serviceName);
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Removing service interfaces...");
		for (const std::type_info* interface : std::views::keys(serviceData[index].publicInterfaces))
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Interface: '{}'.", interface->name());
			serviceInterfaces.erase(*interface);
		}
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Removing service interfaces done.");

		if (serviceData[index].tickableService)
		{
			if (const auto position = std::ranges::find(tickableServices, serviceData[index].tickableService); position != tickableServices.cend())
			{
				tickableServices.erase(position);
			}
		}

		serviceData.erase(serviceData.cbegin() + index);
		services.erase(services.cbegin() + index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Removing '{}' service done.", serviceName);
	}

	void ServiceManager::Begin()
	{
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
		End(services.size());
	}

	void ServiceManager::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking application services.");
		for (ITickableService* const tickableService : tickableServices)
		{
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking '{}' service.", typeid(*tickableService).name());
				tickableService->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On ticking '{}' service.", typeid(*tickableService).name());
				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on ticking '{}' service.", typeid(*tickableService).name());
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
		std::vector<std::pair<ITickableService*, std::int32_t>> orderedTickableServices;
		orderedTickableServices.reserve(serviceData.size());
		for (const ServiceData& data : serviceData)
		{
			if (data.tickableService)
			{
				orderedTickableServices.push_back(std::pair(data.tickableService, data.tickOrder));
			}
		}
		std::ranges::sort(orderedTickableServices, [](const std::pair<ITickableService*, std::int32_t>& lhs, const std::pair<ITickableService*, std::int32_t>& rhs) noexcept
		{
			return lhs.second < rhs.second;
		});

		tickableServices.reserve(orderedTickableServices.size());
		for (std::size_t i = 0uz; i < orderedTickableServices.size(); ++i)
		{
			ITickableService* const tickableService = orderedTickableServices[i].first;
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Service: '{}'.", typeid(*tickableService).name());
			PONY_LOG_IF(i > 0uz && orderedTickableServices[i].second == orderedTickableServices[i - 1].second, application->Logger(), Log::LogType::Warning,
				"'{}' and '{}' services have the same tick order. It may cause unpredictable results.", typeid(*orderedTickableServices[i - 1uz].first).name(), typeid(*orderedTickableServices[i].first).name());
			tickableServices.push_back(tickableService);
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting tickable services done.");
	}

	void ServiceManager::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning application services...");
		for (const std::shared_ptr<IService>& service : services)
		{
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' service...", typeid(*service).name());
				service->Begin();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' service done.", typeid(*service).name());
				++count;
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On beginning '{}' service.", typeid(*service).name());
				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on beginning '{}' service.", typeid(*service).name());
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
			const std::shared_ptr<IService>& service = services[i];
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' service...", typeid(*service).name());
				service->End();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' service done.", typeid(*service).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On ending '{}' service.", typeid(*service).name());
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on ending '{}' service.", typeid(*service).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending application services done.");
	}
}
