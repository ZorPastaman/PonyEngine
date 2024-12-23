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

export module PonyEngine.Core.Detail:SystemManager;

import <algorithm>;
import <cstdint>;
import <exception>;
import <memory>;
import <ranges>;
import <string>;
import <typeindex>;
import <typeinfo>;
import <unordered_map>;
import <utility>;
import <variant>;
import <vector>;

import PonyBase.Core;
import PonyBase.ObjectUtility;

import PonyDebug.Log;

import PonyEngine.Core;

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
		void CreateSystems(std::span<const SystemFactoryEntry> systemFactories);
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
		[[nodiscard("Redundant call")]]
		SystemData CreateSystem(ISystemFactory* factory) const;
		/// @brief Adds the @p system as a non-tickable system.
		/// @param system Non-tickable system.
		void AddNonTickable(std::unique_ptr<System> system);
		/// @brief Adds the @p system as a tickable system.
		/// @param system Tickable system.
		/// @param tickOrder Tick order.
		/// @param tickableSystemsBuffer Tickable systems buffer.
		void AddTickable(std::unique_ptr<TickableSystem> system, std::int32_t tickOrder, std::vector<std::pair<TickableSystem*, std::int32_t>>& tickableSystemsBuffer);

		IEngineContext* engine; ///< Engine.

		std::vector<std::unique_ptr<System>> systems; ///< Systems.
		std::vector<TickableSystem*> tickableSystems; ///< Tickable systems.
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

	void SystemManager::CreateSystems(const std::span<const SystemFactoryEntry> systemFactories)
	{
		auto tickableSystemsBuffer = std::vector<std::pair<TickableSystem*, std::int32_t>>();

		for (const auto& [factory, tickOrder] : systemFactories)
		{
			assert(factory && "The system factory is nullptr.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create '{}' system with '{}' factory.", typeid(*factory).name(), factory->SystemType().name());
			SystemData systemData = CreateSystem(factory.get());

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

			for (const auto& [interface, objectPointer] : systemData.publicInterfaces.Span())
			{
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' interface.", interface.get().name());
				assert(!systemInterfaces.contains(interface.get()) && "The interface has already been added.");
				systemInterfaces.emplace(interface.get(), objectPointer);
			}

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System created.");
		}

		std::ranges::sort(tickableSystemsBuffer, [](const std::pair<TickableSystem*, std::int32_t>& left, const std::pair<TickableSystem*, std::int32_t>& right){ return left.second < right.second; });
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Tick order:");
		for (TickableSystem* const tickableSystem : std::views::keys(tickableSystemsBuffer))
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, typeid(*tickableSystem).name());
			tickableSystems.push_back(tickableSystem);
		}
	}

	void SystemManager::DestroySystems() noexcept
	{
		for (auto system = systems.rbegin(); system != systems.rend(); ++system)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' system.", typeid(**system).name());
			system->reset();
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System destroyed.");
		}

		systems.clear();
		tickableSystems.clear();
		systemInterfaces.clear();
	}

	void SystemManager::BeginSystems() const
	{
		for (const std::unique_ptr<System>& system : systems)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Begin '{}' system.", typeid(*system).name());
			try
			{
				system->Begin();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On beginning '{}' system.", typeid(*system).name());

				throw;
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System begun.");
		}
	}

	void SystemManager::EndSystems() const noexcept
	{
		for (auto system = systems.crbegin(); system != systems.crend(); ++system)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "End '{}' system.", typeid(**system).name());
			try
			{
				(*system)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ending '{}' system.", typeid(**system).name());
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "System ended.");
		}
	}

	void SystemManager::TickSystems() const
	{
		for (TickableSystem* const system : tickableSystems)
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, typeid(*system).name());
			try
			{
				system->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ticking '{}' system.", typeid(*system).name());
				engine->Stop(static_cast<int>(PonyBase::Core::ExitCodes::SystemTickException));

				throw;
			}
		}
	}

	SystemData SystemManager::CreateSystem(ISystemFactory* const factory) const
	{
		try
		{
			return factory->Create(*engine, SystemParams{});
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(engine->Logger(), e, "On creating '{}' system with '{}' factory.", typeid(*factory).name(), factory->SystemType().name());

			throw;
		}
	}

	void SystemManager::AddNonTickable(std::unique_ptr<System> system)
	{
		assert(system && "The system is nullptr.");
		assert(std::ranges::find_if(systems, [&](const std::unique_ptr<System>& addedSystem) { return typeid(*addedSystem) == typeid(*system); }) == systems.cend() &&
			"The system has already been added.");
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' to non-tickable systems.", typeid(*system).name());
		systems.push_back(std::move(system));
	}

	void SystemManager::AddTickable(std::unique_ptr<TickableSystem> system, const std::int32_t tickOrder, std::vector<std::pair<TickableSystem*, std::int32_t>>& tickableSystemsBuffer)
	{
		assert(system && "The system is nullptr.");
		assert(std::ranges::find_if(systems, [&](const std::unique_ptr<System>& addedSystem) { return typeid(*addedSystem) == typeid(*system); }) == systems.cend() &&
			"The system has already been added.");
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Add '{}' to tickable systems.", typeid(*system).name());
		tickableSystemsBuffer.emplace_back(system.get(), tickOrder);
		systems.push_back(std::move(system));
	}
}
