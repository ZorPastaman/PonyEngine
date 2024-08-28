/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/EngineLog.h"

export module PonyEngine.Core.Implementation:SystemManager;

import <exception>;
import <format>;
import <memory>;
import <stdexcept>;
import <string>;
import <typeindex>;
import <typeinfo>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.StringUtility;

export namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param systemFactories System factories.
		/// @param engineToUse Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engineToUse);
		SystemManager(const SystemManager&) = delete;
		SystemManager(SystemManager&&) = delete;

		~SystemManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override;

		/// @brief Begins the systems.
		/// @details Call this before a first tick.
		void Begin() const;
		/// @brief Ends the systems.
		/// @details Call this before a destruction of the @p SystemManager.
		void End() const noexcept;

		/// @brief Ticks the systems.
		void Tick() const;

		SystemManager& operator =(const SystemManager&) = delete;
		SystemManager& operator =(SystemManager&& other) = delete;

	private:
		std::vector<SystemUniquePtr> systems; ///< Systems.
		std::vector<ITickableSystem*> tickableSystems; ///< Tickable systems.
		std::unordered_map<std::type_index, void*> systemInterfaces; ///< System interfaces.

		const IEngine* const engine; ///< Engine that owns the manager.
	};
}

namespace PonyEngine::Core
{
	/// @brief Creates a system.
	/// @param factory Factory to use.
	/// @param params System params to use.
	/// @return Created system.
	[[nodiscard("Pure function")]]
	SystemData CreateSystem(ISystemFactory* factory, const SystemParams& params);

	SystemManager::SystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engineToUse) :
		engine{&engineToUse}
	{
		PONY_LOG(engine, Log::LogType::Info, "Create systems.");

		const auto systemParams = SystemParams{.engine = engineToUse};
		for (ISystemFactory* const factory : systemFactories)
		{
			PONY_LOG(engine, Log::LogType::Info, "Create '{}' system with '{}' factory.", factory->SystemName(), factory->Name());

			SystemData system = CreateSystem(factory, systemParams);

			if (!system.system)
			{
				throw std::logic_error(Log::SafeFormat("The '{}' system from the '{}' factory is nullptr.", factory->SystemName(), factory->Name()));
			}

			systems.push_back(std::move(system.system));

			if (system.tickableSystem)
			{
				PONY_LOG(engine, Log::LogType::Debug, "Add to tickable systems.");
				tickableSystems.push_back(system.tickableSystem);
			}
			else
			{
				PONY_LOG(engine, Log::LogType::Debug, "System is not tickable.");
			}

			for (auto [interface, objectPointer] : system.publicInterfaces)
			{
				PONY_LOG(engine, Log::LogType::Debug, "Add '{}' interface.", interface.get().name());
				systemInterfaces.insert_or_assign(interface.get(), objectPointer);
			}

			PONY_LOG(engine, Log::LogType::Info, "System created.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems created.");
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, "Destroy systems.");

		for (auto system = systems.rbegin(); system != systems.rend(); ++system)
		{
			PONY_LOG(engine, Log::LogType::Info, "Destroy system '{}'.", (*system)->Name());
			system->reset();
			PONY_LOG(engine, Log::LogType::Info, "System destroyed.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems destroyed.");
	}

	void* SystemManager::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		if (const auto pair = systemInterfaces.find(typeInfo); pair != systemInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	void SystemManager::Begin() const
	{
		PONY_LOG(engine, Log::LogType::Info, "Begin systems.");

		for (const SystemUniquePtr& system : systems)
		{
			PONY_LOG(engine, Log::LogType::Info, "Begin '{}' system.", system->Name());
			try
			{
				system->Begin();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine, e, "On beginning '{}' system.", system->Name());

				throw;
			}
			PONY_LOG(engine, Log::LogType::Info, "System begun.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems begun.");
	}

	void SystemManager::End() const noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, "End systems.");

		for (auto system = systems.crbegin(); system != systems.crend(); ++system)
		{
			PONY_LOG(engine, Log::LogType::Info, "End '{}' system.", (*system)->Name());
			try
			{
				(*system)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine, e, "On ending '{}' system.", (*system)->Name());
			}
			PONY_LOG(engine, Log::LogType::Info, "System ended.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems ended.");
	}

	void SystemManager::Tick() const
	{
		PONY_LOG(engine, Log::LogType::Verbose, "Tick systems.");

		for (ITickableSystem* const system : tickableSystems)
		{
			PONY_LOG(engine, Log::LogType::Verbose, system->Name());
			try
			{
				system->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine, e, "On ticking '{}' system.", system->Name());

				throw;
			}
		}
	}

	SystemData CreateSystem(ISystemFactory* factory, const SystemParams& params)
	{
		try
		{
			return factory->Create(params);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(&params.engine, e, "On creating '{}' system with '{}' factory.", factory->SystemName(), factory->Name());

			throw;
		}
	}
}
