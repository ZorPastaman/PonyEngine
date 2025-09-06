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
	class SystemManager final : public ISystemManager
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
		virtual void* FindSystem(const std::type_info& typeInfo) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const void* FindSystem(const std::type_info& typeInfo) const noexcept override;

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
	};
}

namespace PonyEngine::Engine
{
	SystemManager::SystemManager(IEngineContext& engine, const std::span<ISystemFactory*> systemFactories) :
		engine{&engine}
	{
		PONY_LOG(this->engine->Logger(), Log::LogType::Debug, "Sorting engine system factories.");
		std::ranges::sort(systemFactories, [](const ISystemFactory* const lhs, const ISystemFactory* const rhs) noexcept { return lhs->InitOrder() < rhs->InitOrder(); });
		if constexpr (IsInMask(Log::LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 0uz; i < systemFactories.size(); ++i)
			{
				for (std::size_t j = i + 1uz; j < systemFactories.size() && systemFactories[i]->InitOrder() == systemFactories[j]->InitOrder(); ++j)
				{
					PONY_LOG(this->engine->Logger(), Log::LogType::Warning, "'{}' and '{}' systems have the same init order. It may cause unpredictable results.", 
						typeid(*systemFactories[i]).name(), typeid(*systemFactories[j]).name());
				}
			}
		}

		std::size_t begunSystemCount = 0uz;
		try
		{
			Initialize(systemFactories);
			Begin(begunSystemCount);
		}
		catch (...)
		{
			End(begunSystemCount);
			Finalize();

			throw;
		}
	}

	SystemManager::~SystemManager() noexcept
	{
		End(systems.size());
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
		std::vector<std::pair<SystemData, std::int32_t>> systemData;
		systemData.reserve(systemFactories.size());
		systems.reserve(systemFactories.size());
		std::size_t interfaceCount = 0;
		for (ISystemFactory* const factory : systemFactories)
		{
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine system... Factory: '{}'.", typeid(*factory).name());
				SystemData system = factory->Create(*engine);
				std::visit([&]<typename SystemPtr>(const SystemPtr& systemPtr) noexcept
				{
					if constexpr (std::is_same_v<std::shared_ptr<ISystem>, SystemPtr> || std::is_same_v<std::shared_ptr<ITickableSystem>, SystemPtr>)
					{
						assert(systemPtr && "The created system is nullptr!");
						systems.push_back(systemPtr);
						PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine system done. System: '{}'.", typeid(*systemPtr).name());
					}
					else
					{
						static_assert(false, "Unsupported engine system type!");
					}
				}, system.system);
				interfaceCount += system.publicInterfaces.Count();
				systemData.emplace_back(std::move(system), factory->TickOrder());
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
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Creating engine systems done.");

		PONY_LOG(engine->Logger(), Log::LogType::Debug, "Getting interfaces.");
		systemInterfaces.reserve(interfaceCount);
		for (std::size_t i = 0; i < systemData.size(); ++i)
		{
			PONY_LOG(engine->Logger(), Log::LogType::Debug, "System: '{}'.", typeid(*systems[i]).name());
			for (const auto& [type, interface] : systemData[i].first.publicInterfaces.Span())
			{
				PONY_LOG(engine->Logger(), Log::LogType::Debug, "Interface: '{}'.", type.get().name());
				assert(!systemInterfaces.contains(type.get()) && "The interface has already been added.");
				systemInterfaces[type.get()] = interface;
			}
		}

		PONY_LOG(engine->Logger(), Log::LogType::Debug, "Caching tickable systems.");
		std::erase_if(systemData, [](const auto& p) { return !std::get_if<std::shared_ptr<ITickableSystem>>(&p.first.system); });
		std::ranges::sort(systemData, [](const auto& lhs, const auto& rhs) noexcept { return lhs.second < rhs.second; });
		tickableSystems.reserve(systemData.size());
		if constexpr (IsInMask(Log::LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 0uz; i < systemData.size(); ++i)
			{
				for (std::size_t j = i + 1uz; j < systemData.size() && systemData[i].second == systemData[j].second; ++j)
				{
					PONY_LOG(this->engine->Logger(), Log::LogType::Warning, "'{}' and '{}' systems have the same tick order. It may cause unpredictable results.",
						typeid(*std::get<std::shared_ptr<ITickableSystem>>(systemData[i].first.system)).name(), typeid(*std::get<std::shared_ptr<ITickableSystem>>(systemData[j].first.system)).name());
				}
			}
		}
		for (SystemData& system : std::views::keys(systemData))
		{
			const auto tickableSystem = std::get<std::shared_ptr<ITickableSystem>>(system.system);
			PONY_LOG(engine->Logger(), Log::LogType::Debug, typeid(*tickableSystem).name());
			tickableSystems.push_back(tickableSystem.get());
		}
	}

	void SystemManager::Finalize() noexcept
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing engine systems...");
		for (std::size_t i = systems.size(); i-- > 0uz; )
		{
			std::shared_ptr<ISystem>& system = systems[i];
			PONY_LOG(engine->Logger(), Log::LogType::Info, "Releasing '{}' system.", typeid(*system).name());
			system.reset();
		}
		PONY_LOG(engine->Logger(), Log::LogType::Debug, "Releasing engine systems done.");
	}

	void SystemManager::Begin(std::size_t& count)
	{
		PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning engine systems...");
		for (const std::shared_ptr<ISystem>& system : systems)
		{
			try
			{
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Beginning '{}' system.", typeid(*system).name());
				system->Begin();
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
				PONY_LOG(engine->Logger(), Log::LogType::Info, "Ending '{}' system.", typeid(*system).name());
				system->End();
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
