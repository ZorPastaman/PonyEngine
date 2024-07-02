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

#include "PonyEngine/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:SystemManager;

import <cstddef>;
import <exception>;
import <functional>;
import <format>;
import <iostream>;
import <string>;
import <typeinfo>;
import <unordered_map>;
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

		[[nodiscard("Pure function")]]
		void* FindSystem(const std::type_info& typeInfo) const;

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
		struct TypeInfoHash final
		{
			[[nodiscard("Pure operator")]]
			std::size_t operator ()(const std::type_info& typeInfo) const noexcept;
		};

		struct TypeInfoEqual final
		{
			[[nodiscard("Pure operator")]]
			bool operator ()(const std::type_info& left, const std::type_info& right) const noexcept;
		};

		std::vector<ISystem*> systems; ///< Systems. It's synced with the @p factories by index.
		std::vector<ISystemFactory*> factories; ///< System factories. It's synced with the @p systems by index.
		std::vector<ISystem*> tickableSystems; ///< Tickable systems.
		std::unordered_map<std::reference_wrapper<const type_info>, void*, TypeInfoHash, TypeInfoEqual> systemInterfaces; ///< System interfaces.
		const IEngine& engine; ///< Engine that owns the manager.
	};
}

namespace PonyEngine::Core
{
	SystemManager::SystemManager(const EngineParams& engineParams, IEngine& engine) :
		engine{engine}
	{
		PONY_LOG(engine, Log::LogType::Info, "Create systems.");

		for (EngineParams::SystemFactoriesIterator it = engineParams.GetSystemFactoriesIterator(); !it.IsEnd(); ++it)
		{
			ISystemFactory* const factory = *it;
			assert((factory != nullptr));
			PONY_LOG(engine, Log::LogType::Info, std::format("Create '{}'.", factory->GetSystemName()).c_str());
			const auto [system, interfaces] = factory->Create(engine);
			assert((system != nullptr));
			systems.push_back(system);
			factories.push_back(factory);
			if (system->IsTickable())
			{
				PONY_LOG(engine, Log::LogType::Info, "Add to tickable systems.");
				tickableSystems.push_back(system);
			}
			else
			{
				PONY_LOG(engine, Log::LogType::Info, "The system is not tickable.");
			}

			for (auto interfacesIterator = interfaces.GetObjectInterfacesIterator(); !interfacesIterator.IsEnd(); ++interfacesIterator)
			{
				systemInterfaces.insert(*interfacesIterator);
			}

			PONY_LOG(engine, Log::LogType::Info, std::format("'{}' created.", system->GetName()).c_str());
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems created.");
	}

	SystemManager::~SystemManager() noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, "Destroy systems.");

		for (std::size_t i = systems.size() - 1; i != std::size_t{0} - 1; --i)
		{
			ISystem* const system = systems[i];
			ISystemFactory* const factory = factories[i];
			PONY_LOG(engine, Log::LogType::Info, std::format("Destroy '{}'.", system->GetName()).c_str());
			factory->Destroy(system);
			PONY_LOG(engine, Log::LogType::Info, std::format("'{}' destroyed.", factory->GetSystemName()).c_str());
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems destroyed.");
	}

	void* SystemManager::FindSystem(const std::type_info& typeInfo) const
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

		for (ISystem* const system : systems)
		{
			PONY_LOG(engine, Log::LogType::Info, std::format("Begin '{}'.", system->GetName()).c_str());
			system->Begin();
			PONY_LOG(engine, Log::LogType::Info, std::format("'{}' begun.", system->GetName()).c_str());
		}

		PONY_LOG(engine, Log::LogType::Info, "Systems begun.");
	}

	void SystemManager::End() const noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, "End systems.");

		for (auto it = systems.crbegin(); it != systems.crend(); ++it)
		{
			ISystem* const system = *it;

			PONY_LOG(engine, Log::LogType::Info, std::format("End '{}'.", system->GetName()).c_str());
			try
			{
				system->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine, e, "On ending a system.");
			}
			PONY_LOG(engine, Log::LogType::Info, std::format("'{}' ended.", system->GetName()).c_str());
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

	std::size_t SystemManager::TypeInfoHash::operator ()(const std::type_info& typeInfo) const noexcept
	{
		return typeInfo.hash_code();
	}

	bool SystemManager::TypeInfoEqual::operator ()(const std::type_info& left, const std::type_info& right) const noexcept
	{
		return left == right;
	}
}
