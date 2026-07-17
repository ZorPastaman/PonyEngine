/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:InterfaceManager;

import std;

import PonyEngine.Log;

import :LoggerManager;
import :ThreadManager;

export namespace PonyEngine::Application
{
	/// @brief Interface manager.
	class InterfaceManager final
	{
	public:
		/// @brief Creates an interface manager.
		/// @param loggerManager Logger manager.
		/// @param threadManager Thread manager.
		[[nodiscard("Pure constructor")]]
		InterfaceManager(const LoggerManager& loggerManager, const ThreadManager& threadManager) noexcept;
		InterfaceManager(const InterfaceManager&) = delete;
		InterfaceManager(InterfaceManager&&) = delete;

		~InterfaceManager() noexcept = default;

		/// @brief Tries to find an interface.
		/// @param type Interface type.
		/// @return Interface; @a nullptr if not found.
		[[nodiscard("Pure function")]]
		void* FindInterface(std::type_index type) const noexcept;
		/// @brief Adds the interface.
		/// @param type Interface type.
		/// @param interface Interface.
		void AddInterface(std::type_index type, void* interface);
		/// @brief Removes the interface.
		/// @param type Interface type.
		/// @param interface Interface.
		void RemoveInterface(std::type_index type, const void* interface);

		InterfaceManager& operator =(const InterfaceManager&) = delete;
		InterfaceManager& operator =(InterfaceManager&&) = delete;

	private:
		const LoggerManager* loggerManager; ///< Logger manager.
		const ThreadManager* threadManager; ///< Thread manager.

		std::unordered_map<std::type_index, void*> interfaces; ///< Interfaces.
	};
}

namespace PonyEngine::Application
{
	InterfaceManager::InterfaceManager(const LoggerManager& loggerManager, const ThreadManager& threadManager) noexcept :
		loggerManager{&loggerManager},
		threadManager{&threadManager}
	{
	}

	void* InterfaceManager::FindInterface(const std::type_index type) const noexcept
	{
		if (const auto position = interfaces.find(type); position != interfaces.cend()) [[likely]]
		{
			return position->second;
		}

		return nullptr;
	}

	void InterfaceManager::AddInterface(const std::type_index type, void* const interface)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Adding interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
		if (!interfaces.try_emplace(type, interface).second) [[unlikely]]
		{
			throw std::invalid_argument("Interface is already added");
		}
	}

	void InterfaceManager::RemoveInterface(const std::type_index type, const void* const interface)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Removing interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
		if (const auto position = interfaces.find(type); position != interfaces.cend() && position->second == interface) [[likely]]
		{
			interfaces.erase(position);
		}
		else
		{
			throw std::invalid_argument("Interface wasn't added");
		}
	}
}
