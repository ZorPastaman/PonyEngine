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

export module PonyEngine.Application.Main.Windows:Console;

import std;

import PonyEngine.Text;

export namespace PonyEngine::Application::Windows
{
	/// @brief Creates a console.
	/// @param codePageID Console code page.
	void CreateConsole(UINT codePageID);
	/// @brief Destroys a console.
	void DestroyConsole();
}

namespace PonyEngine::Application::Windows
{
	/// @brief Sets both the input and output code pages of the console.
	/// @param codePageID Code page ID.
	void SetConsoleCodePage(UINT codePageID);

	void CreateConsole(const UINT codePageID)
	{
		if (!AllocConsole()) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to allocate console. Error code: '0x{:X}'.", GetLastError()));
		}

		SetConsoleCodePage(codePageID);

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
