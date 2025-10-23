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

import PonyEngine.Application.Extension;
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

		MessageLoopManager& operator =(const MessageLoopManager&) = delete;
		MessageLoopManager& operator =(MessageLoopManager&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.
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

			if (message.message == WM_QUIT) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", static_cast<int>(message.wParam));
				application->Stop(static_cast<int>(message.wParam));
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}
}
#endif
