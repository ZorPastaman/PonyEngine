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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:ServiceManager;

import <exception>;
import <format>;
import <functional>;
import <iostream>;
import <string>;
import <utility>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;

namespace PonyEngine::Core
{
	/// @brief Holder of services.
	export class ServiceManager final
	{
	public:
		/// @brief Creates a @p ServiceManager.
		/// @param serviceFactories Service factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		ServiceManager(const std::vector<IServiceFactory*>& serviceFactories, IEngine& engine);
		ServiceManager(const ServiceManager&) = delete;
		[[nodiscard("Pure constructor")]]
		inline ServiceManager(ServiceManager&& other) noexcept = default;

		~ServiceManager() noexcept;

		/// @brief Finds a service with the @p predicate.
		/// @param predicate Predicate.
		/// @return Found service. May be nullptr.
		[[nodiscard("Pure function")]]
		IService* FindService(const std::function<bool(const IService*)>& predicate) const;

		/// @brief Begins services.
		/// @details Call this after a creation of a @p ServiceManager.
		void Begin() const;
		/// @brief Ends services.
		/// @details Call this before a destruction of a @p ServiceManager.
		void End() const noexcept;

		ServiceManager& operator =(const ServiceManager&) = delete;
		inline ServiceManager& operator =(ServiceManager&& other) noexcept = default;

	private:
		std::vector<std::pair<IService*, IServiceFactory*>> m_services; /// @brief Pairs of a service and a service factory that was used to create the service.
		const IEngine& m_engine; /// @brief Engine that owns the manager.
	};

	ServiceManager::ServiceManager(const std::vector<IServiceFactory*>& serviceFactories, IEngine& engine) :
		m_services{},
		m_engine{engine}
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Create services.");

		for (IServiceFactory* const factory : serviceFactories)
		{
			assert((factory != nullptr));
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Create '{}'.", factory->GetServiceName()).c_str());
			IService* const service = factory->Create(engine);
			assert((service != nullptr));
			m_services.push_back(std::pair(service, factory));
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' created.", service->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Services created.");
	}

	ServiceManager::~ServiceManager() noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Destroy services.");

		for (std::vector<std::pair<IService*, IServiceFactory*>>::const_reverse_iterator it = m_services.crbegin(); it != m_services.crend(); ++it)
		{
			IService* const service = it->first;
			IServiceFactory* const factory = it->second;
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Destroy '{}'.", service->GetName()).c_str());
			factory->Destroy(service);
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' destroyed.", factory->GetServiceName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Services destroyed.");
	}

	IService* ServiceManager::FindService(const std::function<bool(const IService*)>& predicate) const
	{
		assert((predicate));

		for (const std::pair<IService*, IServiceFactory*> serviceFactory : m_services)
		{
			if (predicate(serviceFactory.first))
			{
				return serviceFactory.first;
			}
		}

		return nullptr;
	}

	void ServiceManager::Begin() const
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Begin services.");

		for (const std::pair<IService*, IServiceFactory*> serviceFactory : m_services)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Begin '{}'.", serviceFactory.first->GetName()).c_str());
			serviceFactory.first->Begin();
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' begun.", serviceFactory.first->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Services begun.");
	}

	void ServiceManager::End() const noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "End services.");

		for (std::vector<std::pair<IService*, IServiceFactory*>>::const_reverse_iterator it = m_services.crbegin(); it != m_services.crend(); ++it)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("End '{}'.", it->first->GetName()).c_str());

			try
			{
				it->first->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine, e, "On ending a service.");
			}

			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' ended.", it->first->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Services ended.");
	}
}
