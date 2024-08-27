/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Common:ExitCodes;

export namespace PonyEngine::Common
{
	/// @brief Exit codes that are returned from main().
	///	@remark The enum is always int based.
	///	@remark Negative exit codes are returned by an application, positive are returned by an engine.
	enum class ExitCodes : int
	{
		EngineTickException = -2,
		ApplicationException = -1,
		Success = 0,
		SystemTickException = 1
	};
}
