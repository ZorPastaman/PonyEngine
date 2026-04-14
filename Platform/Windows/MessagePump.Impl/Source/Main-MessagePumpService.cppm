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

export module PonyEngine.MessagePump.Impl.Windows:MessagePumpService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.MessagePump;

export namespace PonyEngine::MessagePump::Windows
{
	/// @brief Windows message pump service.
	class MessagePumpService final : public Application::IService, private Application::ITickableService, private IMessagePumpService
	{
	public:
		/// @brief Creates a pump service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit MessagePumpService(Application::IApplicationContext& application) noexcept;
		MessagePumpService(const MessagePumpService&) = delete;
		MessagePumpService(MessagePumpService&&) = delete;

		~MessagePumpService() noexcept = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void AddTickableServices(Application::ITickableServiceAdder& adder) override;
		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		MessagePumpService& operator =(const MessagePumpService&) = delete;
		MessagePumpService& operator =(MessagePumpService&&) = delete;

	private:
		virtual void Tick() noexcept override;

		[[nodiscard("Pure function")]]
		virtual MessagePumpFeature SupportedFeatures() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t>LastMessageCursorPosition() const noexcept override;

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
	MessagePumpService::MessagePumpService(Application::IApplicationContext& application) noexcept :
		application{&application},
		messageTime(std::chrono::steady_clock::now()),
		rawMessageTime(GetTickCount())
	{
	}

	void MessagePumpService::Begin() noexcept
	{
	}

	void MessagePumpService::End() noexcept
	{
	}

	void MessagePumpService::AddTickableServices(Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER);
	}

	void MessagePumpService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IMessagePumpService>(*this);
	}

	void MessagePumpService::Tick() noexcept
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

	MessagePumpFeature MessagePumpService::SupportedFeatures() const noexcept
	{
		return MessagePumpFeature::MessageTime | MessagePumpFeature::CursorPosition;
	}

	std::chrono::time_point<std::chrono::steady_clock> MessagePumpService::LastMessageTime() const noexcept
	{
		return messageTime;
	}

	Math::Vector2<std::int32_t> MessagePumpService::LastMessageCursorPosition() const noexcept
	{
		return cursorPosition;
	}

	void MessagePumpService::UpdateTime(const DWORD newMessageTime) noexcept
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
