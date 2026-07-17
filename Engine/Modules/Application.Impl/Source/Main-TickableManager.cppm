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

export module PonyEngine.Application.Impl:TickableManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :LoggerManager;
import :ThreadManager;

export namespace PonyEngine::Application
{
	/// @brief Tickable manager.
	class TickableManager final
	{
	public:
		/// @brief Creates a tickable manager.
		/// @param loggerManager Logger manager.
		/// @param threadManager Thread manager.
		[[nodiscard("Pure constructor")]]
		TickableManager(const LoggerManager& loggerManager, const ThreadManager& threadManager) noexcept;
		TickableManager(const TickableManager&) = delete;
		TickableManager(TickableManager&&) = delete;

		~TickableManager() noexcept = default;

		/// @brief Adds the tickable.
		/// @param tickable Tickable to add.
		/// @param order Tick order.
		void AddTickable(ITickable& tickable, std::int32_t order);
		/// @brief Removes the tickable.
		/// @param tickable 
		/// @param order 
		void RemoveTickable(ITickable& tickable, std::int32_t order);

		/// @brief Builds an ordered tickable list.
		void UpdateTickableList();
		/// @brief Clears an ordered tickable list.
		void ClearTickableList() noexcept;
		/// @brief Ticks an ordered tickable list.
		/// @note Must be called after @p UpdateTickableList().
		void Tick() const;

		TickableManager& operator =(const TickableManager&) = delete;
		TickableManager& operator =(TickableManager&&) = delete;

	private:
		const LoggerManager* loggerManager; ///< Logger manager.
		const ThreadManager* threadManager; ///< Thread manager.

		std::vector<std::pair<ITickable*, std::int32_t>> protoTickables; ///< Added tickables.
		std::vector<ITickable*> tickables; ///< Sorted tickables.
	};
}

namespace PonyEngine::Application
{
	TickableManager::TickableManager(const LoggerManager& loggerManager, const ThreadManager& threadManager) noexcept :
		loggerManager{&loggerManager},
		threadManager{&threadManager}
	{
	}

	void TickableManager::AddTickable(ITickable& tickable, const std::int32_t order)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Adding tickable. Tickable: '{}'; Order: '{}'.", typeid(tickable).name(), order);
		protoTickables.emplace_back(&tickable, order);
	}

	void TickableManager::RemoveTickable(ITickable& tickable, const std::int32_t order)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Removing tickable. Tickable: '{}'.", typeid(tickable).name());
		if (const auto position = std::ranges::find(protoTickables, std::pair(&tickable, order)); position != protoTickables.cend()) [[likely]]
		{
			protoTickables.erase(position);
		}
#ifndef NDEBUG
		else [[unlikely]]
		{
			throw std::invalid_argument("Tickable wasn't added");
		}
#endif
	}

	void TickableManager::UpdateTickableList()
	{
		tickables.clear();
		tickables.reserve(protoTickables.size());

		std::ranges::sort(protoTickables, std::less<std::int32_t>(), &std::pair<ITickable*, std::int32_t>::second);
		for (std::size_t i = 1uz; i < protoTickables.size(); ++i)
		{
			PONY_LOG_IF(protoTickables[i].second == protoTickables[i - 1uz].second, loggerManager->Logger(), Log::LogType::Warning,
				"Tickables '{}' and '{}' have the same order: '{}'.", typeid(*protoTickables[i].first).name(),
				typeid(*protoTickables[i - 1uz].first).name(), protoTickables[i].second);
		}

		for (ITickable* const tickable : std::views::keys(protoTickables))
		{
			tickables.push_back(tickable);
		}
	}

	void TickableManager::ClearTickableList() noexcept
	{
		tickables.clear();
	}

	void TickableManager::Tick() const
	{
		for (ITickable* const tickable : tickables)
		{
			PONY_LOG(loggerManager->Logger(), Log::LogType::Verbose, "Ticking '{}'.", typeid(*tickable).name());
			tickable->Tick();
		}
	}
}
