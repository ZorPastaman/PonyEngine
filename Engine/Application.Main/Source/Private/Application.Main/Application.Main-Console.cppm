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

#if PONY_WINCORE
#include "PonyEngine/Platform/WinCore/Framework.h"
#endif

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application.Main:Console;

import std;

import PonyEngine.Log;
import PonyEngine.Text;

export namespace PonyEngine::Application
{
	/// @brief Log to standard console.
	/// @param logType Log type.
	/// @param message Message.
	void LogToConsole(Log::LogType logType, std::string_view message) noexcept;
}

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Creates a console.
	void CreateConsole();
	/// @brief Destroys a console.
	void DestroyConsole();
}
#endif

namespace PonyEngine::Application
{
	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	std::ostream& ChooseConsoleStream(Log::LogType logType) noexcept;

	void LogToConsole(const Log::LogType logType, const std::string_view message) noexcept
	{
#if PONY_CONSOLE_LOG
		try
		{
			ChooseConsoleStream(logType) << message;
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
#endif

#if PONY_PLATFORM_CONSOLE_LOG
#if PONY_WINCORE
		OutputDebugStringA(message.data());
#endif
#endif
	}

	std::ostream& ChooseConsoleStream(const Log::LogType logType) noexcept
	{
		switch (logType)
		{
		case Log::LogType::Verbose:
		case Log::LogType::Debug:
		case Log::LogType::Info:
			return std::cout;
		case Log::LogType::Warning:
			return std::clog;
		case Log::LogType::Error:
		case Log::LogType::Exception:
			return std::cerr;
		default: [[unlikely]]
			assert(false && "Invalid log type.");
			return std::cerr;
		}
	}
}

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	/// @brief Sets both the input and output code pages of the console.
	/// @param codePageID Code page ID.
	void SetConsoleCodePage(UINT codePageID);

	void CreateConsole()
	{
		if (!AllocConsole()) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to allocate console. Error code: '0x{:X}'.", GetLastError()));
		}

		SetConsoleCodePage(CP_UTF8);

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stdout)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stdout. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stderr)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stderr. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONIN$", "r", stdin)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stdin. Error code: '0x{:X}'.", error));
		}
	}

	void DestroyConsole()
	{
		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stdout)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stdout. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stderr)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stderr. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "r", stdin)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to reassign stdin. Error code: '0x{:X}'.", error));
		}

		if (!FreeConsole()) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to free console. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	void SetConsoleCodePage(const UINT codePageID)
	{
		if (!SetConsoleCP(codePageID)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to set console code page to '{}'. Error code: '0x{:X}'.", codePageID, GetLastError()));
		}
		if (!SetConsoleOutputCP(codePageID)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to set console output code page to '{}'. Error code: '0x{:X}'.", codePageID, GetLastError()));
		}
	}
}
#endif
