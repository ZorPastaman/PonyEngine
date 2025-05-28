/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module Application:ExitCodes;

export namespace Application
{
	/// @brief Exit codes that must be used by main. Negative codes represent errors in an application or engine.
	///        Positive codes represent errors in systems.
	struct ExitCodes final
	{
		NON_CONSTRUCTIBLE_BODY(ExitCodes)

		static constexpr int EngineTickException = -3;
		static constexpr int ApplicationTickException = -2;
		static constexpr int MainException = -1;
		static constexpr int Success = 0;
		static constexpr int SystemTickException = 1;
		static constexpr int SystemManagerTickException = 2;
	};
}
