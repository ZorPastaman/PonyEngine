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

export module PonyEngine.Core.Implementation:SystemManager;

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
	/// @brief Holder and ticker of systems.
	export class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param systemFactoryInfos System factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const std::vector<SystemFactoryInfo>& systemFactoryInfos, IEngine& engine);
		SystemManager(const SystemManager&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline SystemManager(SystemManager&& other) noexcept;

		virtual ~SystemManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const override;

		/// @brief Begins the systems.
		void Begin();
		/// @brief Ends the systems.
		void End() noexcept;

		/// @brief Ticks the systems.
		void Tick() const;

	private:
		std::vector<ISystem*> m_systems; /// @brief Systems.
		std::vector<std::function<void(ISystem*)>> m_destroyFunctions; /// @brief Destroy functions. Must be synchronized with @p m_systems by index.

		const IEngine& m_engine; /// @brief Engine that owns the manager.
	};

	SystemManager::SystemManager(const std::vector<SystemFactoryInfo>& systemFactoryInfos, IEngine& engine) :
		m_systems{},
		m_destroyFunctions{},
		m_engine{engine}
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Create systems");

		for (const SystemFactoryInfo& factoryInfo : systemFactoryInfos)
		{
			assert((factoryInfo.createFunction));
			assert((factoryInfo.destroyFunction));

			ISystem* const system = factoryInfo.createFunction(engine);
			m_systems.push_back(system);
			m_destroyFunctions.push_back(factoryInfo.destroyFunction);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, system->GetName());
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Systems created");
	}

	inline SystemManager::SystemManager(SystemManager&& other) noexcept :
		m_systems(std::move(other.m_systems)),
		m_destroyFunctions(std::move(other.m_destroyFunctions)),
		m_engine{other.m_engine}
	{
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy systems");

		for (std::size_t i = 0, count = m_systems.size(); i < count; ++i)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, m_systems[i]->GetName());

			try
			{
				m_destroyFunctions[i](m_systems[i]);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine.GetLogger(), e, "On destroying a system");
			}
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Systems destroyed");
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		assert((predicate));

		for (ISystem* const system : m_systems)
		{
			if (predicate(system))
			{
				return system;
			}
		}

		return nullptr;
	}

	void SystemManager::Begin()
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Begin systems");

		for (ISystem* const system : m_systems)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, system->GetName());
			system->Begin();
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Systems begun");
	}

	void SystemManager::End() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "End systems");

		for (ISystem* const system : m_systems)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, system->GetName());

			try
			{
				system->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine.GetLogger(), e, "On ending a system");
			}
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Systems ended");
	}

	void SystemManager::Tick() const
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Tick systems");

		for (ISystem* const system : m_systems)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, system->GetName());
			system->Tick();
		}
	}
}
