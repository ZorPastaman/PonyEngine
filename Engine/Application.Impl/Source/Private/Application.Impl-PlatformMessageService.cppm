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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application.Impl:PlatformMessageService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Math;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Platform message service.
	class PlatformMessageService final : public ITickableService
	{
	public:
		/// @brief Creates a platform message service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit PlatformMessageService(IApplicationContext& application) noexcept;
		PlatformMessageService(const PlatformMessageService&) = delete;
		PlatformMessageService(PlatformMessageService&&) = delete;

		~PlatformMessageService() noexcept = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;
		virtual void Tick() noexcept override;

		/// @brief Gets the time of the last message.
		/// @return Time of the last message.
		[[nodiscard("Pure function")]]
		std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept;
		/// @brief Gets the cursor position of the last message.
		/// @return Cursor position in the screen coordinates of the last message.
		[[nodiscard("Pure function")]]
		Math::Vector2<std::int32_t> LastMessageCursorPosition() const noexcept;

		PlatformMessageService& operator =(const PlatformMessageService&) = delete;
		PlatformMessageService& operator =(PlatformMessageService&&) = delete;

	private:
		/// @brief Updates time based on a new message time.
		/// @param newMessageTime New message time.
		void UpdateTime(DWORD newMessageTime) noexcept;

		IApplicationContext* application; ///< Application context.

		std::chrono::time_point<std::chrono::steady_clock> messageTime; ///< Time of the last message.
		DWORD rawMessageTime; ///< Raw time of the last message.
		Math::Vector2<std::int32_t> cursorPosition; ///< Cursor position of the last message.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	PlatformMessageService::PlatformMessageService(IApplicationContext& application) noexcept :
		application{&application},
		messageTime(std::chrono::steady_clock::now()),
		rawMessageTime(GetTickCount())
	{
	}

	void PlatformMessageService::Begin() noexcept
	{
	}

	void PlatformMessageService::End() noexcept
	{
	}

	void PlatformMessageService::Tick() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Peeking messages.");
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			PONY_LOG(application->Logger(), Log::LogType::Verbose, "Received '{}' message for hwnd '0x{:X}'.", message.message, reinterpret_cast<std::uintptr_t>(message.hwnd));
			UpdateTime(message.time);
			cursorPosition = Math::Vector2<std::int32_t>(static_cast<std::int32_t>(message.pt.x), static_cast<std::int32_t>(message.pt.y));

			if (message.message == WM_QUIT) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", static_cast<int>(message.wParam));
				application->Stop(static_cast<int>(message.wParam));
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	std::chrono::time_point<std::chrono::steady_clock> PlatformMessageService::LastMessageTime() const noexcept
	{
		return messageTime;
	}

	Math::Vector2<std::int32_t> PlatformMessageService::LastMessageCursorPosition() const noexcept
	{
		return cursorPosition;
	}

	void PlatformMessageService::UpdateTime(const DWORD newMessageTime) noexcept
	{
		const DWORD prevToNowDiff = newMessageTime - rawMessageTime;
		const DWORD nowToPrevDiff = rawMessageTime - newMessageTime;

		if (newMessageTime < rawMessageTime && prevToNowDiff > nowToPrevDiff) [[unlikely]]
		{
			messageTime -= std::chrono::milliseconds(nowToPrevDiff);
		}
		else [[likely]]
		{
			messageTime += std::chrono::milliseconds(prevToNowDiff);
		}

		rawMessageTime = newMessageTime;
	}
}
#endif
