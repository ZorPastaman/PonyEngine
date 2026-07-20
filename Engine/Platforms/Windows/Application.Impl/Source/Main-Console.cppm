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
	/// @brief Sets both the input and output code pages of the console.
	/// @param codePageID Code page ID.
	void SetConsoleCodePage(UINT codePageID) noexcept;

	/// @brief Creates a console.
	void CreateConsole();
	/// @brief Destroys a console.
	void DestroyConsole();
}

namespace PonyEngine::Application::Windows
{
	void SetConsoleCodePage(const UINT codePageID) noexcept
	{
		SetConsoleCP(codePageID);
		SetConsoleOutputCP(codePageID);
	}

	void CreateConsole()
	{
		if (!AllocConsole()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to allocate console: ErrorCode = '0x{:X}'", GetLastError()));
		}

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
}
