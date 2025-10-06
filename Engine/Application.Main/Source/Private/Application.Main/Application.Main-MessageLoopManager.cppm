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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application.Main:MessageLoopManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Message loop manager.
	class MessageLoopManager final
	{
	public:
		/// @brief Creates a message loop manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit MessageLoopManager(IApplicationContext& application) noexcept;
		MessageLoopManager(const MessageLoopManager&) = delete;
		MessageLoopManager(MessageLoopManager&&) = delete;

		~MessageLoopManager() noexcept = default;

		void Tick() noexcept;

		void AddMessageObserver(IMessageObserver& observer, UINT messageType);
		void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes);
		void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept;
		void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept;
		void RemoveMessageObserver(IMessageObserver& observer) noexcept;

		MessageLoopManager& operator =(const MessageLoopManager&) = delete;
		MessageLoopManager& operator =(MessageLoopManager&&) = delete;

	private:
		/// @brief Calls message observers of the specified message type.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		void ObserveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		IApplicationContext* application; ///< Application context.

		std::unordered_map<UINT, std::vector<IMessageObserver*>> messageObservers; ///< Message observers.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	MessageLoopManager::MessageLoopManager(IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	void MessageLoopManager::Tick() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Peeking messages.");
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			PONY_LOG(application->Logger(), Log::LogType::Verbose, "Received '{}' message for hwnd '0x{:X}'.", message.message, reinterpret_cast<std::uintptr_t>(message.hwnd));

			if (!message.hwnd) [[unlikely]]
			{
				ObserveMessage(message.message, message.wParam, message.lParam);
			}

			if (message.message == WM_QUIT) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", static_cast<int>(message.wParam));
				application->Stop(static_cast<int>(message.wParam));
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	void MessageLoopManager::AddMessageObserver(IMessageObserver& observer, const UINT messageType)
	{
		std::vector<IMessageObserver*>& observers = messageObservers[messageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The observer has already been added.");
		observers.push_back(&observer);
	}

	void MessageLoopManager::AddMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (std::size_t i = 0uz; i < messageTypes.size(); ++i)
		{
			try
			{
				AddMessageObserver(observer, messageTypes[i]);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveMessageObserver(observer, messageTypes[i]);
				}

				throw;
			}
		}
	}

	void MessageLoopManager::RemoveMessageObserver(IMessageObserver& observer, const UINT messageType) noexcept
	{
		if (const auto position = messageObservers.find(messageType); position != messageObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of '{}' message type but it hadn't been added.", messageType);
	}

	void MessageLoopManager::RemoveMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes) noexcept
	{
		for (const UINT messageType : messageTypes)
		{
			RemoveMessageObserver(observer, messageType);
		}
	}

	void MessageLoopManager::RemoveMessageObserver(IMessageObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (std::vector<IMessageObserver*>& observers : std::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove message observer but it hadn't been added.");
	}

	void MessageLoopManager::ObserveMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}
	}
}
#endif
