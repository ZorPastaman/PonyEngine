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
import PonyEngine.Memory;

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

		/// @brief Gets the service count.
		/// @return Service count.
		[[nodiscard("Pure function")]]
		std::size_t ServiceCount() const noexcept;
		/// @brief Finds an index of the service.
		/// @param service Service.
		/// @return Service index; nullopt if it's not found.
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> IndexOf(const IService* service) const noexcept;
		/// @brief Gets a service.
		/// @param index Service index.
		/// @return Service.
		[[nodiscard("Pure function")]]
		ServiceData& Service(std::size_t index) noexcept;
		/// @brief Gets a service.
		/// @param index Service index.
		/// @return Service.
		[[nodiscard("Pure function")]]
		const ServiceData& Service(std::size_t index) const noexcept;
		/// @brief Adds a service.
		/// @param data Service data.
		/// @note It must be called only before Begin().
		void AddService(const ServiceData& data);
		/// @brief Removes a service.
		/// @param index Service index.
		/// @note It must be called only after End().
		void RemoveService(std::size_t index) noexcept;

		/// @brief Begins the services.
		void Begin();
		/// @brief Ends the services.
		void End() noexcept;
		/// @brief Ticks the services.
		void Tick();

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

	std::size_t ServiceManager::ServiceCount() const noexcept
	{
		return serviceData.size();
	}

	std::optional<std::size_t> ServiceManager::IndexOf(const IService* const service) const noexcept
	{
		for (std::size_t i = services.size(); i-- > 0uz; ) // It usually gets a last service.
		{
			if (services[i].get() == service)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	ServiceData& ServiceManager::Service(const std::size_t index) noexcept
	{
		return serviceData[index];
	}

	const ServiceData& ServiceManager::Service(const std::size_t index) const noexcept
	{
		return serviceData[index];
	}

	void ServiceManager::AddService(const ServiceData& data)
	{
		const std::shared_ptr<IService> service = data.service.index() == 0 ? std::get<0>(data.service) : std::get<1>(data.service);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service...", typeid(*service).name());
		assert(service && "The service is nullptr.");
		services.push_back(service);

		try
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding service interfaces...");
			for (const Memory::TypedPtr<>& interface : data.publicInterfaces)
			{
				PONY_LOG(application->Logger(), Log::LogType::Debug, "Interface: '{}'.", interface.Type().name());
				assert(!serviceInterfaces.contains(interface.Type()) && "The interface has already been added.");
				serviceInterfaces[interface.Type()] = interface.Get();
			}
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Adding service interfaces done.");

			try
			{
				serviceData.push_back(data);
			}
			catch (...)
			{
				for (const Memory::TypedPtr<>& interface : data.publicInterfaces)
				{
					serviceInterfaces.erase(interface.Type());
				}

				throw;
			}
		}
		catch (...)
		{
			services.pop_back();
			throw;
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Adding '{}' service done.", typeid(*service).name());
	}

	void ServiceManager::RemoveService(const std::size_t index) noexcept
	{
		const char* const serviceName = typeid(*services[index]).name();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Removing '{}' service...", serviceName);
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Removing service interfaces...");
		for (const Memory::TypedPtr<>& interface : serviceData[index].publicInterfaces)
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Interface: '{}'.", interface.Type().name());
			serviceInterfaces.erase(interface.Type());
		}
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Removing service interfaces done.");

		if (serviceData[index].service.index() == 1)
		{
			const ITickableService* const tickableService = std::get<1>(serviceData[index].service).get();
			if (const auto position = std::ranges::find(tickableServices, tickableService); position != tickableServices.cend())
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

	void ServiceManager::UpdateTickableServices()
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting tickable services...");
		std::vector<std::pair<ITickableService*, std::int32_t>> orderedTickableServices;
		orderedTickableServices.reserve(serviceData.size());
		for (const ServiceData& data : serviceData)
		{
			if (data.service.index() == 1)
			{
				orderedTickableServices.push_back(std::pair(std::get<1>(data.service).get(), data.tickOrder));
			}
		}
		std::ranges::sort(orderedTickableServices, [](const std::pair<ITickableService*, std::int32_t>& lhs, const std::pair<ITickableService*, std::int32_t>& rhs)
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
