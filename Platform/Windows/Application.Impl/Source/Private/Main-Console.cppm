/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <stdio.h>

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:Console;

import std;

export namespace PonyEngine::Application::Windows
{
	/// @brief Logs to output debug string.
	/// @param message Log message.
	void LogToOutputDebugString(std::string_view message) noexcept;

	/// @brief Creates a console.
	void CreateConsole();
	/// @brief Destroys a console.
	void DestroyConsole();
}

namespace PonyEngine::Application::Windows
{
	/// @brief Sets both the input and output code pages of the console.
	/// @param codePageID Code page ID.
	void SetConsoleCodePage(UINT codePageID);

	void LogToOutputDebugString(const std::string_view message) noexcept
	{
#if PONY_ENGINE_PLATFORM_CONSOLE_LOG
		OutputDebugStringA(message.data());
#endif
	}

	void CreateConsole()
	{
		if (!AllocConsole()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to allocate console: ErrorCode = '0x{:X}'", GetLastError()));
		}

		SetConsoleCodePage(CP_UTF8);

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stdout)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stdout: ErrorCode = '0x{:X}'", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stderr)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stderr: ErrorCode = '0x{:X}'", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONIN$", "r", stdin)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stdin: ErrorCode = '0x{:X}'", error));
		}
	}

	void DestroyConsole()
	{
		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stdout)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stdout: ErrorCode = '0x{:X}'", error));
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stderr)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stderr: ErrorCode = '0x{:X}'", error));
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "r", stdin)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reassign stdin: ErrorCode = '0x{:X}'", error));
		}

		if (!FreeConsole()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to free console: ErrorCode = '0x{:X}'", GetLastError()));
		}
	}

	void SetConsoleCodePage(const UINT codePageID)
	{
		if (!SetConsoleCP(codePageID)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set console code page to '{}': ErrorCode = '0x{:X}'", codePageID, GetLastError()));
		}
		if (!SetConsoleOutputCP(codePageID)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set console output code page to '{}': ErrorCode = '0x{:X}'", codePageID, GetLastError()));
		}
	}
}
