/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <iostream>
#include <stdexcept>

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Windows:Console;

import PonyEngine.Utility;

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
		if (!AllocConsole())
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to allocate console. Error code: '0x{:X}'.", GetLastError()));
		}

		SetConsoleCodePage(codePageID);

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stdout))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to reassign stdout. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stderr))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to reassign stderr. Error code: '0x{:X}'.", error));
		}
		if (const errno_t error = freopen_s(&fp, "CONIN$", "r", stdin))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to reassign stdin. Error code: '0x{:X}'.", error));
		}

		std::ios::sync_with_stdio();
		std::cout.clear();
		std::clog.clear();
		std::cerr.clear();
		std::cin.clear();
	}

	void DestroyConsole()
	{
		if (const int error = fclose(stdin))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to close stdin. Error code: '0x{:X}'.", error));
		}
		if (const int error = fclose(stdout))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to close stdout. Error code: '0x{:X}'.", error));
		}
		if (const int error = fclose(stderr))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to close stderr. Error code: '0x{:X}'.", error));
		}

		if (!FreeConsole())
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to free console. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	void SetConsoleCodePage(const UINT codePageID)
	{
		if (!SetConsoleCP(codePageID))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set console code page to '{}'. Error code: '0x{:X}'.", codePageID, GetLastError()));
		}
		if (!SetConsoleOutputCP(codePageID))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set console output code page to '{}'. Error code: '0x{:X}'.", codePageID, GetLastError()));
		}
	}
}
