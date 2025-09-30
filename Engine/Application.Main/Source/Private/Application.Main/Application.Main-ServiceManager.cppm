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

export module PonyEngine.Application.Main:ServiceManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Utility;

export namespace PonyEngine::Application
{
	/// @brief Service manager.
	class ServiceManager final
	{
	public:
		/// @brief Creates a service manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit ServiceManager(IApplicationContext& application) noexcept;
		ServiceManager(const ServiceManager&) = delete;
		ServiceManager(ServiceManager&&) = delete;

		~ServiceManager() noexcept = default;

		[[nodiscard("Pure function")]]
		void* FindService(const std::type_info& type) noexcept;
		[[nodiscard("Pure function")]]
		const void* FindService(const std::type_info& type) const noexcept;

		/// @brief Adds a service.
		/// @param factory Service factory.
		void AddService(IServiceFactory& factory);
		/// @brief Clears the service manager.
		void Clear() noexcept;

		/// @brief Adds the interface added hook.
		/// @param interface Interface type.
		/// @param hook Hook.
		void AddInterfaceAddedHook(const std::type_info& interface, const std::function<void(const IService*, void*)>& hook);
		/// @brief Adds the service removed hook.
		/// @param service Service.
		/// @param hook Hook.
		void AddServiceRemovedHook(const IService* service, const std::function<void(const IService*)>& hook);

		/// @brief Begins the services.
		void Begin();
		/// @brief Ends the services.
		void End() noexcept;
		/// @brief Ticks the services.
		void Tick();

		ServiceManager& operator =(const ServiceManager&) = delete;
		ServiceManager& operator =(ServiceManager&&) = delete;

	private:
		/// @brief Begins the services.
		/// @param count How many services are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the services.
		/// @param count How many services to end.
		void End(std::size_t count) noexcept;

		IApplicationContext* application; ///< Application context.

		std::vector<std::shared_ptr<IService>> services; ///< Services.
		std::vector<ITickableService*> tickableServices; ///< Tickable services.
		std::vector<std::int32_t> tickOrders; ///< Tickable service orders. 
		std::unordered_map<std::type_index, void*> serviceInterfaces; ///< Service interfaces.
		std::unordered_map<const IService*, std::vector<std::type_index>> serviceInterfacesMap; ///< Service to interfaces map.

		std::unordered_map<std::type_index, std::vector<std::function<void(const IService*, void*)>>> onInterfaceAddedHooks; ///< On interface added hooks;
		std::unordered_map<const IService*, std::vector<std::function<void(const IService*)>>> onServiceRemovedHooks; ///< On service removed hooks;
	};
}

namespace PonyEngine::Application
{
	ServiceManager::ServiceManager(IApplicationContext& application) noexcept :
		application{&application}
	{
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

	void ServiceManager::AddService(IServiceFactory& factory)
	{
		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Creating application service... Factory: '{}'.", typeid(*&factory).name());
			ServiceData data = factory.Create(*application);

			std::shared_ptr<IService> service = nullptr;
			ITickableService* tickableService = nullptr;
			switch (data.service.index())
			{
			case 0:
				service = std::get<0>(data.service);
				break;
			case 1:
				service = std::get<1>(data.service);
				tickableService = std::get<1>(data.service).get();
				break;
			default:
				assert(false && "Unexpected variant index.");
				break;
			}
			assert(service && "The service is nullptr!");

			services.push_back(service);
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding service interfaces.");
				std::vector<std::type_index>& interfaces = serviceInterfacesMap[service.get()];
				for (const auto& [type, interface] : data.publicInterfaces.Span())
				{
					PONY_LOG(application->Logger(), Log::LogType::Debug, "Interface: '{}'.", type.get().name());
					assert(!serviceInterfaces.contains(type.get()) && "The interface has already been added.");
					serviceInterfaces[type.get()] = interface;
					interfaces.push_back(type.get());

					if (const auto position = onInterfaceAddedHooks.find(type.get()); position != onInterfaceAddedHooks.cend())
					{
						for (const std::function<void(const IService*, void*)>& hook : position->second)
						{
							hook(service.get(), interface);
						}
					}
				}

				if (tickableService)
				{
					PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding to tickable services.");
					std::size_t index = 0uz;
					for (; index < tickOrders.size() && data.tickOrder <= tickOrders[index]; ++index);
					PONY_LOG_IF(index > 0uz && tickOrders[index - 1uz] == data.tickOrder, application->Logger(), Log::LogType::Warning, 
						"'{}' and '{}' services have the same tick order. It may cause unpredictable results.", typeid(*tickableServices[index - 1uz]).name(), typeid(*tickableService).name());
					tickOrders.insert(tickOrders.cbegin() + index, data.tickOrder);

					try
					{
						tickableServices.insert(tickableServices.cbegin() + index, tickableService);
					}
					catch (...)
					{
						tickOrders.erase(tickOrders.cbegin() + index);
						throw;
					}
				}
			}
			catch (...)
			{
				serviceInterfacesMap.erase(service.get());
				for (const std::reference_wrapper<const std::type_info>& type : std::views::keys(data.publicInterfaces.Span()))
				{
					serviceInterfaces.erase(type.get());
				}
				services.pop_back();

				throw;
			}

			PONY_LOG(application->Logger(), Log::LogType::Info, "Creating application service done. Service: '{}'.", typeid(*service).name());
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating application service. Factory: '{}'.", typeid(factory).name());
			throw;
		}
		catch (...)
		{
			PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on creating application service. Factory: '{}'.", typeid(factory).name());
			throw;
		}
	}

	void ServiceManager::Clear() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing application services...");
		for (std::size_t i = services.size(); i-- > 0uz; )
		{
			std::shared_ptr<IService>& service = services[i];
			const char* const serviceName = typeid(*service).name();
			PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing '{}' service...", serviceName);

			if (const auto position = onServiceRemovedHooks.find(service.get()); position != onServiceRemovedHooks.cend())
			{
				for (const std::function<void(const IService*)>& hook : position->second)
				{
					try
					{
						hook(service.get());
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(application->Logger(), e, "On service removed hook. Service: '{}'.", typeid(*service).name());
					}
					catch (...)
					{
						PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on service removed hook. Service: '{}'.", typeid(*service).name());
					}
				}
			}

			for (const std::type_index type : serviceInterfacesMap[service.get()])
			{
				serviceInterfaces.erase(type);
			}

			service.reset();
			PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing '{}' service done.", serviceName);
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing application services done.");

		services.clear();
		tickableServices.clear();
		tickOrders.clear();
		serviceInterfaces.clear();
		serviceInterfacesMap.clear();
		onInterfaceAddedHooks.clear();
		onServiceRemovedHooks.clear();
	}

	void ServiceManager::AddInterfaceAddedHook(const std::type_info& interface, const std::function<void(const IService*, void*)>& hook)
	{
		onInterfaceAddedHooks[interface].push_back(hook);
	}

	void ServiceManager::AddServiceRemovedHook(const IService* const service, const std::function<void(const IService*)>& hook)
	{
		onServiceRemovedHooks[service].push_back(hook);
	}

	void ServiceManager::Begin()
	{
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
