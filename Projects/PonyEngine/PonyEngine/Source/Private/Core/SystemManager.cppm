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
import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	export class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param systemFactories System factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const std::vector<ISystemFactory*>& systemFactories, IEngine& engine);
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
		std::vector<ISystemFactory*> m_systemFactories; /// @brief System factories. Must be synchronized with @p m_systems by index.

		const IEngine& m_engine; /// @brief Engine that owns the manager.
	};

	SystemManager::SystemManager(const std::vector<ISystemFactory*>& systemFactories, IEngine& engine) :
		m_systems{},
		m_systemFactories{},
		m_engine{engine}
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Create systems");

		for (ISystemFactory* const systemFactory : systemFactories)
		{
			assert((systemFactory != nullptr));

			ISystem* const system = systemFactory->Create(engine);
			m_systems.push_back(system);
			m_systemFactories.push_back(systemFactory);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, system->GetName());
		}

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Systems created");
	}

	inline SystemManager::SystemManager(SystemManager&& other) noexcept :
		m_systems(std::move(other.m_systems)),
		m_systemFactories(std::move(other.m_systemFactories)),
		m_engine{other.m_engine}
	{
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy systems");

		for (std::size_t i = 0, count = m_systems.size(), index = count - i - 1; i < count; ++i, index = count - i - 1)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, m_systems[index]->GetName());

			try
			{
				m_systemFactories[index]->Destroy(m_systems[index]);
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

		for (std::vector<ISystem*>::reverse_iterator systemIterator = m_systems.rbegin(); systemIterator != m_systems.rend(); ++systemIterator)
		{
			ISystem* const system = *systemIterator;

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
