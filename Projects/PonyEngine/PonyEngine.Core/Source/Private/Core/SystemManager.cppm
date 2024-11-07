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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Core.Implementation:SystemManager;

import <algorithm>;
import <exception>;
import <ranges>;
import <string>;
import <typeindex>;
import <typeinfo>;
import <unordered_map>;
import <utility>;
import <variant>;
import <vector>;

import PonyBase.Core;
import PonyBase.Memory;
import PonyBase.ObjectUtility;

import PonyDebug.Log;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param engine Engine context.
		[[nodiscard("Pure constructor")]]
		explicit SystemManager(IEngineContext& engine);
		SystemManager(const SystemManager&) = delete;
		SystemManager(SystemManager&&) = delete;

		~SystemManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override;

		/// @brief Creates systems.
		/// @param systemFactories System factories.
		void CreateSystems(const SystemFactoriesContainer& systemFactories);
		/// @brief Destroys systems.
		void DestroySystems() noexcept;

		/// @brief Begins the systems.
		/// @details Call this before a first tick.
		void BeginSystems() const;
		/// @brief Ends the systems.
		/// @details Call this before a destruction of the @p SystemManager.
		void EndSystems() const noexcept;

		/// @brief Ticks the systems.
		void TickSystems() const;

		SystemManager& operator =(const SystemManager&) = delete;
		SystemManager& operator =(SystemManager&& other) = delete;

	private:
		/// @brief Creates a system.
		/// @param factory Factory to use.
		/// @return Created system.
		[[nodiscard("Pure function")]]
		SystemData CreateSystem(ISystemFactory* factory) const;
		/// @brief Adds the @p system as a non-tickable system.
		/// @param system Non-tickable system.
		void AddNonTickable(PonyBase::Memory::UniquePointer<IEngineSystem> system);
		/// @brief Adds the @p system as a tickable system.
		/// @param system Tickable system.
		/// @param tickOrder Tick order.
		/// @param tickableSystemsBuffer Tickable systems buffer.
		void AddTickable(PonyBase::Memory::UniquePointer<ITickableEngineSystem> system, int tickOrder, std::vector<std::pair<ITickableEngineSystem*, int>>& tickableSystemsBuffer);

		IEngineContext* engine; ///< Engine.

		std::vector<PonyBase::Memory::UniquePointer<IEngineSystem>> systems; ///< Systems.
		std::vector<ITickableEngineSystem*> tickableSystems; ///< Tickable systems.
		std::unordered_map<std::type_index, void*> systemInterfaces; ///< System interfaces.
	};
}

namespace PonyEngine::Core
{
	SystemManager::SystemManager(IEngineContext& engine) :
		engine{&engine}
	{
	}

	void* SystemManager::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		if (const auto pair = systemInterfaces.find(typeInfo); pair != systemInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	void SystemManager::CreateSystems(const SystemFactoriesContainer& systemFactories)
	{
		auto tickableSystemsBuffer = std::vector<std::pair<ITickableEngineSystem*, int>>();

		for (const auto [factory, tickOrder] : systemFactories)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create '{}' system with '{}' factory.", factory->SystemName(), factory->Name());
			SystemData systemData = CreateSystem(factory);

			switch (systemData.system.index())
			{
			case 0:
				AddNonTickable(std::move(std::get<0>(systemData.system)));
				break;
			case 1:
				AddTickable(std::move(std::get<1>(systemData.system)), tickOrder, tickableSystemsBuffer);
				break;
			default:
				assert(false && "Incorrect system type.");
				break;
			}

			for (const auto [interface, objectPointer] : systemData.publicInterfaces)
			{
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' interface.", interface.get().name());
				assert(!systemInterfaces.contains(interface.get()) && "The interface has already been added.");
				systemInterfaces.emplace(interface.get(), objectPointer);
			}

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System created.");
		}

		std::ranges::sort(tickableSystemsBuffer, [](const std::pair<ITickableEngineSystem*, int>& left, const std::pair<ITickableEngineSystem*, int>& right){ return left.second < right.second; });
		for (auto tickableSystem : std::views::keys(tickableSystemsBuffer))
		{
			tickableSystems.push_back(tickableSystem);
		}
	}

	void SystemManager::DestroySystems() noexcept
	{
		for (auto system = systems.rbegin(); system != systems.rend(); ++system)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system.", (*system)->Name());
			system->Reset();
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System destroyed.");
		}

		systems.clear();
		tickableSystems.clear();
		systemInterfaces.clear();
	}

	void SystemManager::BeginSystems() const
	{
		for (const PonyBase::Memory::UniquePointer<IEngineSystem>& system : systems)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Begin '{}' system.", system->Name());
			try
			{
				system->Begin();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On beginning '{}' system.", system->Name());

				throw;
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System begun.");
		}
	}

	void SystemManager::EndSystems() const noexcept
	{
		for (auto system = systems.crbegin(); system != systems.crend(); ++system)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "End '{}' system.", (*system)->Name());
			try
			{
				(*system)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ending '{}' system.", (*system)->Name());
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System ended.");
		}
	}

	void SystemManager::TickSystems() const
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Tick systems.");

		for (ITickableEngineSystem* const system : tickableSystems)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, system->Name());
			try
			{
				system->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ticking '{}' system.", system->Name());
				engine->Stop(static_cast<int>(PonyBase::Core::ExitCodes::SystemTickException));

				throw;
			}
		}
	}

	SystemData SystemManager::CreateSystem(ISystemFactory* const factory) const
	{
		try
		{
			return factory->Create(*engine, EngineSystemParams{});
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(engine->Logger(), e, "On creating '{}' system with '{}' factory.", factory->SystemName(), factory->Name());

			throw;
		}
	}

	void SystemManager::AddNonTickable(PonyBase::Memory::UniquePointer<IEngineSystem> system)
	{
		assert(system && "The system is nullptr.");
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' to non-tickable systems.", system->Name());
		systems.push_back(std::move(system));
	}

	void SystemManager::AddTickable(PonyBase::Memory::UniquePointer<ITickableEngineSystem> system, const int tickOrder, std::vector<std::pair<ITickableEngineSystem*, int>>& tickableSystemsBuffer)
	{
		assert(system && "The system is nullptr.");
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' to tickable systems.", system->Name());
		tickableSystemsBuffer.emplace_back(system.Get(), tickOrder);
		auto baseSystem = PonyBase::Memory::UniquePointer<IEngineSystem>(std::move(system));
		systems.push_back(std::move(baseSystem));
	}
}
