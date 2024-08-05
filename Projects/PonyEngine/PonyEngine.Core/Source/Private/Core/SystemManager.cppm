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

export namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		/// @param engineParams Engine parameters.
		/// @param engineToUse Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		SystemManager(const EngineParams& engineParams, IEngine& engineToUse);
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
		std::unordered_map<std::type_index, void*> systemInterfaces; ///< System interfaces.
		std::vector<SystemUniquePtr> systems; ///< Systems.
		std::vector<ISystem*> tickableSystems; ///< Tickable systems.

		IEngine* const engine; ///< Engine that owns the manager.
	};
}

namespace PonyEngine::Core
{
	SystemManager::SystemManager(const EngineParams& engineParams, IEngine& engineToUse) :
		engine{&engineToUse}
	{
		PONY_LOG(engine, Log::LogType::Info, "Create systems.");

		for (EngineParams::SystemFactoriesIterator factory = engineParams.GetSystemFactories(); !factory.IsEnd(); ++factory)
		{
			PONY_LOG(engine, Log::LogType::Info, "Create '{}' system.", (*factory).GetSystemName());

			SystemUniquePtr system = (*factory).Create(*engine);
			ISystem* const systemPointer = system.get();
			if (!systemPointer)
			{
				throw std::logic_error("The system is nullptr.");
			}

			systems.push_back(std::move(system));

			if (systemPointer->GetIsTickable())
			{
				PONY_LOG(engine, Log::LogType::Debug, "Add to the tickable systems.");
				tickableSystems.push_back(systemPointer);
			}
			else
			{
				PONY_LOG(engine, Log::LogType::Debug, "The system is not tickable.");
			}

			const ObjectInterfaces interfaces = systemPointer->GetPublicInterfaces();
			for (auto interfacesIterator = interfaces.GetObjectInterfaces(); !interfacesIterator.IsEnd(); ++interfacesIterator)
			{
				auto [type, objectPointer] = *interfacesIterator;
				PONY_LOG(engine, Log::LogType::Debug, "Add '{}' interface.", type.get().name());
				systemInterfaces.insert_or_assign(type.get(), objectPointer);
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
			PONY_LOG(engine, Log::LogType::Info, "Destroy system '{}'.", (*system)->GetName());
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

		for (const auto& system : systems)
		{
			PONY_LOG(engine, Log::LogType::Info, "Begin '{}' system.", system->GetName());
			system->Begin();
			PONY_LOG(engine, Log::LogType::Info, "System begun.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems begun.");
	}

	void SystemManager::End() const noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, "End systems.");

		for (auto system = systems.crbegin(); system != systems.crend(); ++system)
		{
			PONY_LOG(engine, Log::LogType::Info, "End '{}' system.", (*system)->GetName());
			try
			{
				(*system)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine, e, "On ending a system.");
			}
			PONY_LOG(engine, Log::LogType::Info, "System ended.");
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems ended.");
	}

	void SystemManager::Tick() const
	{
		PONY_LOG(engine, Log::LogType::Verbose, "Tick systems.");

		for (ISystem* const system : tickableSystems)
		{
			PONY_LOG(engine, Log::LogType::Verbose, system->GetName());
			system->Tick();
		}
	}
}
