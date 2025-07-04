/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application.Main:ExitCodes;

export namespace PonyEngine::Application
{
	/// @brief Exit codes that must be used by main. The application uses negative codes.
	struct ExitCodes final
	{
		NON_CONSTRUCTIBLE_BODY(ExitCodes)

		static constexpr int TickException = -3;
		static constexpr int ApplicationException = -2;
		static constexpr int MainException = -1;
		static constexpr int Success = 0;
	};
}
