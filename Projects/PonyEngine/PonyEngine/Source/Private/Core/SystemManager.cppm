/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

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

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	export class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
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

		void Begin();
		void End() noexcept;

		/// @brief Ticks the systems.
		void Tick() const;

	private:
		std::vector<ISystem*> m_systems; /// @brief Systems.
		std::vector<std::function<void(ISystem*)>> m_destroyFunctions;

		const IEngine& m_engine;
	};

	SystemManager::SystemManager(const std::vector<SystemFactoryInfo>& systemFactoryInfos, IEngine& engine) :
		m_systems{},
		m_destroyFunctions{},
		m_engine{engine}
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Create systems");

		for (const SystemFactoryInfo& factoryInfo : systemFactoryInfos)
		{
			ISystem* const system = factoryInfo.createFunction(engine);
			m_systems.push_back(system);
			m_destroyFunctions.push_back(factoryInfo.destroyFunction);
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, system->GetName());
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Systems created");
	}

	inline SystemManager::SystemManager(SystemManager&& other) noexcept :
		m_systems(std::move(other.m_systems)),
		m_destroyFunctions(std::move(other.m_destroyFunctions)),
		m_engine{other.m_engine}
	{
	}

	SystemManager::~SystemManager() noexcept
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Destroy systems");

		for (std::size_t i = 0, count = m_systems.size(); i < count; ++i)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, m_systems[i]->GetName());

			try
			{
				m_destroyFunctions[i](m_systems[i]);
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << " on destroying a system." << std::endl;
			}
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Systems destroyed");
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
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
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Begin systems");

		for (ISystem* const system : m_systems)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, system->GetName());
			system->Begin();
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Systems begun");
	}

	void SystemManager::End() noexcept
	{
		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "End systems");

		for (ISystem* const system : m_systems)
		{
			m_engine.GetLogger().Log(Debug::Log::LogType::Info, system->GetName());

			try
			{
				system->End();
			}
			catch (std::exception& e)
			{
				m_engine.GetLogger().LogException(e, "on ending a system");
			}
		}

		m_engine.GetLogger().Log(Debug::Log::LogType::Info, "Systems ended");
	}

	void SystemManager::Tick() const
	{
		for (ISystem* const system : m_systems)
		{
			system->Tick();
		}
	}
}
