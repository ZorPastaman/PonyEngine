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

export module PonyEngine.Application.Main:PlatformMessageService;

import std;

import PonyEngine.Application.Extension;
import PonyEngine.Log;

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

		PlatformMessageService& operator =(const PlatformMessageService&) = delete;
		PlatformMessageService& operator =(PlatformMessageService&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	PlatformMessageService::PlatformMessageService(IApplicationContext& application) noexcept :
		application{&application}
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
