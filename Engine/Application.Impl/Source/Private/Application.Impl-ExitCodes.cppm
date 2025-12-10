/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application.Impl:ExitCodes;

export namespace PonyEngine::Application
{
	/// @brief Exit codes that must be used by main. The application uses negative codes.
	struct ExitCodes final
	{
		NON_CONSTRUCTIBLE_BODY(ExitCodes)

		static constexpr int InitialExitCode = -1000;
		static constexpr int UnexpectedException = -5;
		static constexpr int DeinitializationException = -3;
		static constexpr int RunningException = -2;
		static constexpr int InitializationException = -1;
		static constexpr int Success = 0;
	};
}
