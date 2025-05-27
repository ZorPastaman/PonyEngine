/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module Application.Windows:Console;

export namespace Application::Windows
{
	/// @brief Sets both the input and output code pages of the console.
	/// @param codePageID Code page ID.
	void SetConsoleCodePage(UINT codePageID);
}

namespace Application::Windows
{
	void SetConsoleCodePage(const UINT codePageID)
	{
		SetConsoleCP(codePageID);
		SetConsoleOutputCP(codePageID);
	}
}
