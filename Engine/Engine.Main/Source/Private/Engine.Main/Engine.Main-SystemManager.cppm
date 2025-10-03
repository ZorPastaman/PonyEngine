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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Engine.Main:SystemManager;

import std;

import PonyEngine.Engine.Extension;
import PonyEngine.Log;

export namespace PonyEngine::Engine
{
	/// @brief System manager.
	class SystemManager final
	{
	public:
		/// @brief Creates a system manager.
		/// @param engine Engine context.
		/// @param systemFactories Engine system factories. The order of the factories may be changed.
		[[nodiscard("Pure constructor")]]
		SystemManager(IEngineContext& engine, std::span<ISystemFactory*> systemFactories);
		SystemManager(const SystemManager&) = delete;
		SystemManager(SystemManager&&) = delete;

		~SystemManager() noexcept;

		[[nodiscard("Pure function")]]
		void* FindSystem(const std::type_info& typeInfo) noexcept;
		[[nodiscard("Pure function")]]
		const void* FindSystem(const std::type_info& typeInfo) const noexcept;

		/// @brief Begins the systems.
		void Begin();
		/// @brief Ends the systems.
		void End() noexcept;
		/// @brief Ticks the systems.
		void Tick();

		SystemManager& operator =(const SystemManager&) = delete;
		SystemManager& operator =(SystemManager&&) = delete;

	private:
		/// @brief Initializes the system manager.
		/// @param systemFactories System factories.
		void Initialize(std::span<ISystemFactory*> systemFactories);
		/// @brief Finalizes the system manager.
		void Finalize() noexcept;

		/// @brief Begins the systems.
		/// @param count How many systems are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the systems.
		/// @param count How many systems to end.
		void End(std::size_t count) noexcept;

		IEngineContext* engine; ///< Engine context.

		std::vector<std::shared_ptr<ISystem>> systems; ///< Systems.
		std::vector<ITickableSystem*> tickableSystems; ///< Tickable systems.
		std::unordered_map<std::type_index, void*> systemInterfaces; ///< System interfaces.
		std::unordered_map<ISystem*, std::vector<std::type_index>> systemInterfacesMap; ///< System to interfaces map.
	};
}

namespace PonyEngine::Engine
{
	SystemManager::SystemManager(IEngineContext& engine, const std::span<ISystemFactory*> systemFactories) :
		engine{&engine}
	{
		try
		{
			Initialize(systemFactories);
		}
		catch (...)
		{
			Finalize();
			throw;
		}
	}

	SystemManager::~SystemManager() noexcept
	{
		Finalize();
	}

	void* SystemManager::FindSystem(const std::type_info& typeInfo) noexcept
	{
		if (const auto pair = systemInterfaces.find(typeInfo); pair != systemInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	const void* SystemManager::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		if (const auto pair = systemInterfaces.find(typeInfo); pair != systemInterfaces.cend()) [[likely]]
		{
			return pair->second;
		}

		return nullptr;
	}

	void SystemManager::Begin()
	{
		std::size_t begunSystemCount = 0uz;
		try
		{
			Begin(begunSystemCount);
		}
		catch (...)
		{
			End(begunSystemCount);
			throw;
		}
	}

	void SystemManager::End() noexcept
	{
		End(systems.size());
	}

	void SystemManager::Tick()
	{
		PONY_LOG(engine->Logger(), Log::LogType::Verbose, "Ticking engine systems.");
		for (ITickableSystem* const tickableSystem : tickableSystems)
		{
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Verbose, "Ticking '{}' system.", typeid(*tickableSystem).name());
				tickableSystem->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ticking '{}' system.", typeid(*tickableSystem).name());

				throw;
			}
			catch (...)
			{
				PONY_LOG(engine->Logger(), Log::LogType::Exception, "Unknown exception on ticking '{}' system.", typeid(*tickableSystem).name());

				throw;
			}
		}
	}

	void SystemManager::Initialize(const std::span<ISystemFactory*> systemFactories)
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine systems...");

		std::vector<std::pair<ITickableSystem*, std::int32_t>> tickableSystemsRaw;
		tickableSystemsRaw.reserve(systemFactories.size());
		systems.reserve(systemFactories.size());

		for (ISystemFactory* const factory : systemFactories)
		{
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine system... Factory: '{}'.", typeid(*factory).name());

				SystemData systemData = factory->Create(*engine);
				std::shared_ptr<ISystem> system = nullptr;
				switch (systemData.system.index())
				{
				case 0:
					system = std::get<0>(systemData.system);
					break;
				case 1:
					system = std::get<1>(systemData.system);
					tickableSystemsRaw.emplace_back(std::get<1>(systemData.system).get(), systemData.tickOrder);
					break;
				default:
					assert(false && "Unexpected variant index.");
					break;
				}
				assert(system && "The system is nullptr.");
				systems.push_back(system);

				PONY_LOG(engine->Logger(), Log::LogType::Debug, "Adding system interfaces.");
				std::vector<std::type_index>& interfaces = systemInterfacesMap[system.get()];
				for (const auto& [type, interface] : systemData.publicInterfaces.Span())
				{
					PONY_LOG(engine->Logger(), Log::LogType::Debug, "Interface: '{}'.", type.get().name());
					assert(!systemInterfaces.contains(type.get()) && "The interface has already been added.");
					systemInterfaces[type.get()] = interface;
					interfaces.push_back(type.get());
				}

				PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine system done. System: '{}'.", typeid(*system).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On creating engine system. Factory: '{}'.", typeid(*factory).name());
				throw;
			}
			catch (...)
			{
				PONY_LOG(engine->Logger(), Log::LogType::Exception, "Unknown exception on creating engine system. Factory: '{}'.", typeid(*factory).name());
				throw;
			}
		}

		std::ranges::sort(tickableSystemsRaw, [](const std::pair<ITickableSystem*, std::int32_t>& lhs, const std::pair<ITickableSystem*, std::int32_t>& rhs) noexcept { return lhs.second < rhs.second; });
		if constexpr (IsInMask(Log::LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 1uz; i < tickableSystemsRaw.size(); ++i)
			{
				PONY_LOG_IF(tickableSystemsRaw[i - 1uz].second == tickableSystemsRaw[i].second, this->engine->Logger(), Log::LogType::Warning, 
					"'{}' and '{}' systems have the same tick order. It may cause unpredictable results.", typeid(*tickableSystemsRaw[i - 1uz].first).name(), typeid(*tickableSystemsRaw[i].first).name());
			}
		}
		tickableSystems.reserve(tickableSystemsRaw.size());
		for (ITickableSystem* const system : std::views::keys(tickableSystemsRaw))
		{
			PONY_LOG(engine->Logger(), Log::LogType::Debug, typeid(*system).name());
			tickableSystems.push_back(system);
		}

		PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine systems done.");
	}

	void SystemManager::Finalize() noexcept
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing engine systems...");
		for (std::size_t i = systems.size(); i-- > 0uz; )
		{
			std::shared_ptr<ISystem>& system = systems[i];
			const char* const systemName = typeid(*system).name();
			PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing '{}' system...", systemName);

			for (const std::type_index type : systemInterfacesMap[system.get()])
			{
				systemInterfaces.erase(type);
			}

			system.reset();
			PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing '{}' system done.", systemName);
		}
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing engine systems done.");
	}

	void SystemManager::Begin(std::size_t& count)
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning engine systems...");
		for (const std::shared_ptr<ISystem>& system : systems)
		{
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning '{}' system...", typeid(*system).name());
				system->Begin();
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning '{}' system done.", typeid(*system).name());
				++count;
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On beginning '{}' system.", typeid(*system).name());

				throw;
			}
			catch (...)
			{
				PONY_LOG(engine->Logger(), Log::LogType::Exception, "Unknown exception on beginning '{}' system.", typeid(*system).name());

				throw;
			}
		}
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning engine systems done.");
	}

	void SystemManager::End(const std::size_t count) noexcept
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Ending engine systems...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			const std::shared_ptr<ISystem>& system = systems[i];
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Ending '{}' system...", typeid(*system).name());
				system->End();
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Ending '{}' system done.", typeid(*system).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(engine->Logger(), e, "On ending '{}' system.", typeid(*system).name());
			}
			catch (...)
			{
				PONY_LOG(engine->Logger(), Log::LogType::Exception, "Unknown exception on ending '{}' system.", typeid(*system).name());
			}
		}
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Ending engine systems done.");
	}
}
