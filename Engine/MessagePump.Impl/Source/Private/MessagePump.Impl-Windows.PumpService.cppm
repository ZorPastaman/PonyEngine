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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.MessagePump.Impl:Windows.PumpService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.MessagePump;

export namespace PonyEngine::MessagePump::Windows
{
	/// @brief Windows pump service.
	class PumpService final : public Application::ITickableService, private IPumpService
	{
	public:
		/// @brief Creates a pump service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit PumpService(Application::IApplicationContext& application) noexcept;
		PumpService(const PumpService&) = delete;
		PumpService(PumpService&&) = delete;

		~PumpService() noexcept = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;
		virtual void Tick() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PumpFeature SupportedFeatures() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t>LastMessageCursorPosition() const noexcept override;

		/// @brief Gets the public pump service.
		/// @return Public pump service.
		[[nodiscard("Pure function")]]
		IPumpService& PublicPumpService() noexcept;
		/// @brief Gets the public pump service.
		/// @return Public pump service.
		[[nodiscard("Pure function")]]
		const IPumpService& PublicPumpService() const noexcept;

		PumpService& operator =(const PumpService&) = delete;
		PumpService& operator =(PumpService&&) = delete;

	private:
		/// @brief Updates time based on a new message time.
		/// @param newMessageTime New message time.
		void UpdateTime(DWORD newMessageTime) noexcept;

		Application::IApplicationContext* application; ///< Application context.

		std::chrono::time_point<std::chrono::steady_clock> messageTime; ///< Time of the last message.
		DWORD rawMessageTime; ///< Raw time of the last message.
		Math::Vector2<std::int32_t> cursorPosition; ///< Cursor position of the last message.
	};
}

namespace PonyEngine::MessagePump::Windows
{
	PumpService::PumpService(Application::IApplicationContext& application) noexcept :
		application{&application},
		messageTime(std::chrono::steady_clock::now()),
		rawMessageTime(GetTickCount())
	{
	}

	void PumpService::Begin() noexcept
	{
	}

	void PumpService::End() noexcept
	{
	}

	void PumpService::Tick() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Peeking WINAPI messages.");
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

	PumpFeature PumpService::SupportedFeatures() const noexcept
	{
		return PumpFeature::MessageTime | PumpFeature::CursorPosition;
	}

	std::chrono::time_point<std::chrono::steady_clock> PumpService::LastMessageTime() const noexcept
	{
		return messageTime;
	}

	Math::Vector2<std::int32_t> PumpService::LastMessageCursorPosition() const noexcept
	{
		return cursorPosition;
	}

	IPumpService& PumpService::PublicPumpService() noexcept
	{
		return *this;
	}

	const IPumpService& PumpService::PublicPumpService() const noexcept
	{
		return *this;
	}

	void PumpService::UpdateTime(const DWORD newMessageTime) noexcept
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
