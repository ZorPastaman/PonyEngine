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

export module PonyEngine.Core.Implementation:SystemManager;

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
	/// @brief Holder and ticker of systems.
	export class SystemManager final
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param systemFactories System factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const std::vector<ISystemFactory*>& systemFactories, IEngine& engine);
		SystemManager(const SystemManager&) = delete;
		[[nodiscard("Pure constructor")]]
		inline SystemManager(SystemManager&& other) noexcept = default;

		~SystemManager() noexcept;

		/// @brief Finds a system with the @p predicate.
		/// @param predicate Predicate.
		/// @return Found system. May be nullptr.
		[[nodiscard("Pure function")]]
		ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const;

		/// @brief Begins the systems.
		/// @details Call this before a first tick.
		void Begin() const;
		/// @brief Ends the systems.
		/// @details Call this before a destruction of a @p SystemManager.
		void End() const noexcept;

		/// @brief Ticks the systems.
		void Tick() const;

		SystemManager& operator =(const SystemManager&) = delete;
		inline SystemManager& operator =(SystemManager&& other) noexcept = default;

	private:
		std::vector<std::pair<ISystem*, ISystemFactory*>> m_systems; /// @brief Pairs of a system and a system factory that was used to create the system.
		const IEngine& m_engine; /// @brief Engine that owns the manager.
	};

	SystemManager::SystemManager(const std::vector<ISystemFactory*>& systemFactories, IEngine& engine) :
		m_systems{},
		m_engine{engine}
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Create systems.");

		for (ISystemFactory* const factory : systemFactories)
		{
			assert((factory != nullptr));
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Create '{}'.", factory->GetSystemName()).c_str());
			ISystem* const system = factory->Create(engine);
			assert((system != nullptr));
			m_systems.push_back(std::pair(system, factory));
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' created.", system->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Systems created.");
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Destroy systems.");

		for (std::vector<std::pair<ISystem*, ISystemFactory*>>::const_reverse_iterator it = m_systems.crbegin(); it != m_systems.crend(); ++it)
		{
			ISystem* const system = it->first;
			ISystemFactory* const factory = it->second;
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Destroy '{}'.", system->GetName()).c_str());
			factory->Destroy(system);
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' destroyed.", factory->GetSystemName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Systems destroyed.");
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		assert((predicate));

		for (const std::pair<ISystem*, ISystemFactory*> systemFactory : m_systems)
		{
			if (predicate(systemFactory.first))
			{
				return systemFactory.first;
			}
		}

		return nullptr;
	}

	void SystemManager::Begin() const
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Begin systems.");

		for (const std::pair<ISystem*, ISystemFactory*> systemFactory : m_systems)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Begin '{}'.", systemFactory.first->GetName()).c_str());
			systemFactory.first->Begin();
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' begun.", systemFactory.first->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Systems begun.");
	}

	void SystemManager::End() const noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "End systems.");

		for (std::vector<std::pair<ISystem*, ISystemFactory*>>::const_reverse_iterator it = m_systems.crbegin(); it != m_systems.crend(); ++it)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("End '{}'.", it->first->GetName()).c_str());
			try
			{
				it->first->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine, e, "On ending a system.");
			}
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("'{}' ended.", it->first->GetName()).c_str());
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Systems ended.");
	}

	void SystemManager::Tick() const
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Verbose, "Tick systems.");

		for (const std::pair<ISystem*, ISystemFactory*> systemFactory : m_systems)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, systemFactory.first->GetName());
			systemFactory.first->Tick();
		}
	}
}
