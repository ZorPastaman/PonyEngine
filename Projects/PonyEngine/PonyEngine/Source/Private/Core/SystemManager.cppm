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

#include "Log/LogMacro.h"

export module PonyEngine.Core.Implementation:SystemManager;

import <cstddef>;
import <exception>;
import <format>;
import <functional>;
import <iostream>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Log;

export namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	class SystemManager final
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param engineParams Engine parameters.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const EngineParams& engineParams, IEngine& engine);
		SystemManager(const SystemManager&) = delete;
		SystemManager(SystemManager&&) = delete;

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
		SystemManager& operator =(SystemManager&& other) = delete;

	private:
		std::vector<ISystem*> m_systems; ///< Systems. It's synced with the @p m_factories by index.
		std::vector<ISystemFactory*> m_factories; ///< System factories. It's synced with the @p m_systems by index.
		std::vector<ISystem*> m_tickableSystems; ///< Tickable systems.
		const IEngine& m_engine; ///< Engine that owns the manager.
	};
}

namespace PonyEngine::Core
{
	SystemManager::SystemManager(const EngineParams& engineParams, IEngine& engine) :
		m_engine{engine}
	{
		PONY_LOG(m_engine, Log::LogType::Info, "Create systems.");

		for (EngineParams::SystemFactoriesIterator it = engineParams.GetSystemFactoriesIterator(); !it.IsEnd(); ++it)
		{
			ISystemFactory* const factory = *it;
			assert((factory != nullptr));
			PONY_LOG(m_engine, Log::LogType::Info, std::format("Create '{}'.", factory->GetSystemName()).c_str());
			ISystem* const system = factory->Create(engine);
			assert((system != nullptr));
			m_systems.push_back(system);
			m_factories.push_back(factory);
			if (system->IsTickable())
			{
				PONY_LOG(m_engine, Log::LogType::Info, "Add to tickable systems.");
				m_tickableSystems.push_back(system);
			}
			else
			{
				PONY_LOG(m_engine, Log::LogType::Info, "The system is not tickable.");
			}
			PONY_LOG(m_engine, Log::LogType::Info, std::format("'{}' created.", system->GetName()).c_str());
		}

		PONY_LOG(m_engine, Log::LogType::Info, "Systems created.");
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(m_engine, Log::LogType::Info, "Destroy systems.");

		for (std::size_t i = m_systems.size() - 1; i != std::size_t{0} - 1; --i)
		{
			ISystem* const system = m_systems[i];
			ISystemFactory* const factory = m_factories[i];
			PONY_LOG(m_engine, Log::LogType::Info, std::format("Destroy '{}'.", system->GetName()).c_str());
			factory->Destroy(system);
			PONY_LOG(m_engine, Log::LogType::Info, std::format("'{}' destroyed.", factory->GetSystemName()).c_str());
		}

		PONY_LOG(m_engine, Log::LogType::Info, "Systems destroyed.");
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		assert((static_cast<bool>(predicate)));

		for (ISystem* const system : m_systems)
		{
			if (predicate(system))
			{
				return system;
			}
		}

		return nullptr;
	}

	void SystemManager::Begin() const
	{
		PONY_LOG(m_engine, Log::LogType::Info, "Begin systems.");

		for (ISystem* const system : m_systems)
		{
			PONY_LOG(m_engine, Log::LogType::Info, std::format("Begin '{}'.", system->GetName()).c_str());
			system->Begin();
			PONY_LOG(m_engine, Log::LogType::Info, std::format("'{}' begun.", system->GetName()).c_str());
		}

		PONY_LOG(m_engine, Log::LogType::Info, "Systems begun.");
	}

	void SystemManager::End() const noexcept
	{
		PONY_LOG(m_engine, Log::LogType::Info, "End systems.");

		for (auto it = m_systems.crbegin(); it != m_systems.crend(); ++it)
		{
			ISystem* const system = *it;

			PONY_LOG(m_engine, Log::LogType::Info, std::format("End '{}'.", system->GetName()).c_str());
			try
			{
				system->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(m_engine, e, "On ending a system.");
			}
			PONY_LOG(m_engine, Log::LogType::Info, std::format("'{}' ended.", system->GetName()).c_str());
		}

		PONY_LOG(m_engine, Log::LogType::Info, "Systems ended.");
	}

	void SystemManager::Tick() const
	{
		PONY_LOG(m_engine, Log::LogType::Verbose, "Tick systems.");

		for (ISystem* const system : m_tickableSystems)
		{
			PONY_LOG(m_engine, Log::LogType::Verbose, system->GetName());
			system->Tick();
		}
	}
}
