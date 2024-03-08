/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:ServiceManager;

import <algorithm>;
import <cassert>;
import <cstddef>;
import <exception>;
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
	/// @brief Holder and ticker of services.
	export class ServiceManager final : public IServiceManager
	{
	public:
		/// @brief Creates a @p ServiceManager.
		/// @param serviceFactories Service factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		ServiceManager(const std::vector<IServiceFactory*>& serviceFactories, IEngine& engine);
		ServiceManager(const ServiceManager&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline ServiceManager(ServiceManager&& other) noexcept;

		virtual ~ServiceManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual IService* FindService(const std::function<bool(const IService*)>& predicate) const override;

		/// @brief Begins services.
		void Begin();
		/// @brief Ends services.
		void End() noexcept;

	private:
		std::vector<IService*> m_services; /// @brief Services.
		std::vector<IServiceFactory*> m_serviceFactories; /// @brief Service factories. Must be synchronized with @p m_services by index.

		const IEngine& m_engine; /// @brief Engine that owns the manager.
	};

	ServiceManager::ServiceManager(const std::vector<IServiceFactory*>& serviceFactories, IEngine& engine) :
		m_services{},
		m_destroyFunctions{},
		m_engine{engine}
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Create services");

		for (IServiceFactory* const serviceFactory : serviceFactories)
		{
			assert((serviceFactory != nullptr));

			IService* const service = serviceFactory->Create(engine);
			assert((service != nullptr));
			m_services.push_back(service);
			m_serviceFactories.push_back(serviceFactory);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, service->GetName());
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Services created");
	}

	inline ServiceManager::ServiceManager(ServiceManager&& other) noexcept :
		m_services(std::move(other.m_services)),
		m_serviceFactories(std::move(other.m_serviceFactories)),
		m_engine{other.m_engine}
	{
	}

	ServiceManager::~ServiceManager() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy services");

		for (std::size_t i = 0, count = m_services.size(), index = count - i - 1; i < count; ++i, index = count - i - 1)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, m_services[index]->GetName());

			try
			{
				m_serviceFactories[index]->Destroy(m_services[index]);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine.GetLogger(), e, "On destroying a service");
			}
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Services destroyed");
	}

	IService* ServiceManager::FindService(const std::function<bool(const IService*)>& predicate) const
	{
		assert((predicate));

		for (IService* const service : m_services)
		{
			if (predicate(service))
			{
				return service;
			}
		}

		return nullptr;
	}

	void ServiceManager::Begin()
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Begin services");

		for (IService* const service : m_services)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, service->GetName());
			service->Begin();
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Services begun");
	}

	void ServiceManager::End() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "End services");

		for (std::vector<IService*>::reverse_iterator serviceIterator = m_services.rbegin(); serviceIterator != m_services.rend(); ++serviceIterator)
		{
			IService* const service = *serviceIterator;

			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, service->GetName());

			try
			{
				service->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine.GetLogger(), e, "On ending a service");
			}
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Services ended");
	}
}
