/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

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
import PonyEngine.Debug.Log;

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of services.
	export class ServiceManager final : public IServiceManager
	{
	public:
		/// @brief Creates a @p ServiceManager.
		[[nodiscard("Pure constructor")]]
		ServiceManager(const std::vector<ServiceFactoryInfo>& serviceFactoryInfos, IEngine& engine);
		ServiceManager(const ServiceManager&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline ServiceManager(ServiceManager&& other) noexcept;

		virtual ~ServiceManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual IService* FindService(const std::function<bool(const IService*)>& predicate) const override;

		void Begin();
		void End() noexcept;

	private:
		std::vector<IService*> m_services; /// @brief Services.
		std::vector<std::function<void(IService*)>> m_destroyFunctions;

		const IEngine& m_engine;
	};

	ServiceManager::ServiceManager(const std::vector<ServiceFactoryInfo>& serviceFactoryInfos, IEngine& engine) :
		m_services{},
		m_destroyFunctions{},
		m_engine{engine}
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Create services");

		for (const ServiceFactoryInfo& factoryInfo : serviceFactoryInfos)
		{
			IService* const service = factoryInfo.createFunction(engine);
			m_services.push_back(service);
			m_destroyFunctions.push_back(factoryInfo.destroyFunction);
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, service->GetName());
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Services created");
	}

	inline ServiceManager::ServiceManager(ServiceManager&& other) noexcept :
		m_services(std::move(other.m_services)),
		m_destroyFunctions(std::move(other.m_destroyFunctions)),
		m_engine{other.m_engine}
	{
	}

	ServiceManager::~ServiceManager() noexcept
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Destroy services");

		for (std::size_t i = 0, count = m_services.size(); i < count; ++i)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, m_services[i]->GetName());

			try
			{
				m_destroyFunctions[i](m_services[i]);
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << " on destroying a service." << std::endl;
			}
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Services destroyed");
	}

	IService* ServiceManager::FindService(const std::function<bool(const IService*)>& predicate) const
	{
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
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Begin services");

		for (IService* const service : m_services)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, service->GetName());
			service->Begin();
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Services begun");
	}

	void ServiceManager::End() noexcept
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "End services");

		for (IService* const service : m_services)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, service->GetName());

			try
			{
				service->End();
			}
			catch (std::exception& e)
			{
				m_engine.GetLogger().LogException(e, "on ending a service");
			}
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Services ended");
	}
}
