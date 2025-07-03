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

export module PonyEngine.Engine.Main:ExitCodes;

export namespace PonyEngine::Engine
{
	/// @brief Exit codes that must be used by an engine. The engine uses codes in [1000, 1005].
	struct ExitCodes final
	{
		NON_CONSTRUCTIBLE_BODY(ExitCodes)

		static constexpr int Success = 0;
		static constexpr int InitialExitCode = 1000; ///< The initial exit code of the engine. It's set on its construction.
		static constexpr int TickException = 1001;
	};
}
