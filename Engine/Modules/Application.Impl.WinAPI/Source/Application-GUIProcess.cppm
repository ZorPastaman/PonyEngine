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
#include <stdio.h>

#include "PonyEngine/Log/Log.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shellapi.h>

export module PonyEngine.Application.Impl.WinAPI:GUIProcess;

import std;

import PonyEngine.Application.WinAPI;
import PonyEngine.Log;

import :Process;

export namespace PonyEngine::Application
{
	/// @brief GUI process.
	class GUIProcess final : public Process, private IMainData, private IMessagePump
	{
	public:
		/// @brief Creates a GUI process.
		/// @param hInstance Instance from WinMain().
		/// @param hPrevInstance Previous instance from WinMain().
		/// @param lpCmdLine Command line from WinMain().
		/// @param nShowCmd Show command from WinMain().
		/// @param commandLine Command line.
		[[nodiscard("Pure constructor")]]
		GUIProcess(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd, std::span<const std::string_view> commandLine);
		GUIProcess(const GUIProcess&) = delete;
		GUIProcess(GUIProcess&&) = delete;

		virtual ~GUIProcess() noexcept override = default;

		GUIProcess& operator =(const GUIProcess&) = delete;
		GUIProcess& operator =(GUIProcess&&) = delete;

	protected:
		virtual void CreateConsole() noexcept override;
		virtual void DestroyConsole() noexcept override;

		virtual void AddProcessInterfaces() override;
		virtual void RemoveProcessInterfaces() override;

		[[nodiscard("Must be used")]] 
		virtual void TickPlatform() override;

	private:
		[[nodiscard("Pure function")]] 
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual HINSTANCE PrevInstance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PSTR CommandLine() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual int ShowCommand() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual UINT LastMessageType() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual DWORD LastMessageNativeTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual POINT LastMessageCursorPoint() const noexcept override;

		/// @brief Update WinAPI message time.
		/// @param newMessageTime New message time.
		void UpdateMessageTime(DWORD newMessageTime) noexcept;

		HINSTANCE instance; ///< Instance.
		HINSTANCE prevInstance; ///< Previous instance.
		PSTR cmdLine; ///< Command line.
		int showCmd; ///< Show command.

		bool hasConsole; ///< Does the process have a console?

		std::chrono::time_point<std::chrono::steady_clock> lastMessageTime; ///< Time of a last message.
		DWORD lastMessageNativeTime; ///< Native time of a last message.
		UINT lastMessageType; ///< Type of a last message.
		POINT lastMessageCursorPoint; ///< Cursor point of a last message.
	};
}

namespace PonyEngine::Application
{
	GUIProcess::GUIProcess(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd, 
		const std::span<const std::string_view> commandLine) :
		Process(commandLine),
		instance{hInstance},
		prevInstance{hPrevInstance},
		cmdLine{lpCmdLine},
		showCmd{nShowCmd},
		hasConsole{false},
		lastMessageTime(std::chrono::steady_clock::now()),
		lastMessageNativeTime(GetTickCount()),
		lastMessageType{0u},
		lastMessageCursorPoint{.x = 0l, .y = 0l}
	{
	}

	void GUIProcess::CreateConsole() noexcept
	{
#ifdef PONY_ENGINE_APPLICATION_CREATE_CONSOLE
		PONY_LOG(Application().LogService(), Log::LogType::Info, "Creating console...");

		if (!AllocConsole()) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to allocate console. ErrorCode = '0x{:X}'.", GetLastError());
			return;
		}
		hasConsole = true;

		if (!SetConsoleCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to set console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}
		if (!SetConsoleOutputCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to set output console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stdout)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stdout to console. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stderr)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stderr to console. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "CONIN$", "r", stdin)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stdin to console. ErrorCode = '0x{:X}'.", error);
		}

		PONY_LOG(Application().LogService(), Log::LogType::Info, "Creating console done.");
#endif
	}

	void GUIProcess::DestroyConsole() noexcept
	{
#ifdef PONY_ENGINE_APPLICATION_CREATE_CONSOLE
		if (!hasConsole)
		{
			return;
		}

		PONY_LOG(Application().LogService(), Log::LogType::Info, "Destroying console...");

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stdout)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stdout back to nul. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stderr)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stderr back to nul. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "r", stdin)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to reassign stdin back to nul. ErrorCode = '0x{:X}'.", error);
		}

		if (!FreeConsole()) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to free console. ErrorCode = '0x{:X}'.", GetLastError());
		}
		hasConsole = false;

		PONY_LOG(Application().LogService(), Log::LogType::Info, "Destroying console done.");
#endif
	}

	void GUIProcess::AddProcessInterfaces()
	{
		try
		{
			Application().AddInterface<IMainData>(*this);
			try
			{
				Application().AddInterface<IMessagePump>(*this);
			}
			catch (...)
			{
				Application().RemoveInterface<IMainData>(*this);
				throw;
			}
		}
		catch (...)
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, std::current_exception(), "On adding process interfaces.");
			throw;
		}
	}

	void GUIProcess::RemoveProcessInterfaces()
	{
		Application().RemoveInterface<IMessagePump>(*this);
		Application().RemoveInterface<IMainData>(*this);
	}

	void GUIProcess::TickPlatform()
	{
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			lastMessageType = message.message;
			UpdateMessageTime(message.time);
			lastMessageCursorPoint = message.pt;

			if (message.message == WM_QUIT) [[unlikely]]
			{
				const int exitCode = static_cast<int>(message.wParam);
				PONY_LOG(Application().LogService(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", exitCode);
				Application().Stop(exitCode);
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	HINSTANCE GUIProcess::Instance() const noexcept
	{
		return instance;
	}

	HINSTANCE GUIProcess::PrevInstance() const noexcept
	{
		return prevInstance;
	}

	PSTR GUIProcess::CommandLine() const noexcept
	{
		return cmdLine;
	}

	int GUIProcess::ShowCommand() const noexcept
	{
		return showCmd;
	}

	UINT GUIProcess::LastMessageType() const noexcept
	{
		assert(std::this_thread::get_id() == Application().MainThreadID() && "Must be called on main thread");
		return lastMessageType;
	}

	DWORD GUIProcess::LastMessageNativeTimePoint() const noexcept
	{
		assert(std::this_thread::get_id() == Application().MainThreadID() && "Must be called on main thread");
		return lastMessageNativeTime;
	}

	std::chrono::time_point<std::chrono::steady_clock> GUIProcess::LastMessageTimePoint() const noexcept
	{
		assert(std::this_thread::get_id() == Application().MainThreadID() && "Must be called on main thread");
		return lastMessageTime;
	}

	POINT GUIProcess::LastMessageCursorPoint() const noexcept
	{
		assert(std::this_thread::get_id() == Application().MainThreadID() && "Must be called on main thread");
		return lastMessageCursorPoint;
	}

	void GUIProcess::UpdateMessageTime(const DWORD newMessageTime) noexcept
	{
		const DWORD prevToNowDiff = newMessageTime - lastMessageNativeTime;
		const DWORD nowToPrevDiff = lastMessageNativeTime - newMessageTime;

		if (newMessageTime < lastMessageNativeTime && prevToNowDiff > nowToPrevDiff) [[unlikely]]
		{
			lastMessageTime -= std::chrono::milliseconds(nowToPrevDiff);
		}
		else [[likely]]
		{
			lastMessageTime += std::chrono::milliseconds(prevToNowDiff);
		}

		lastMessageNativeTime = newMessageTime;
	}
}
