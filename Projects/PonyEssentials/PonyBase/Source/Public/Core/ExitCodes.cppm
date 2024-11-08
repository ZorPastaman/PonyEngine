/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Core:ExitCodes;

export namespace PonyBase::Core
{
	/// @brief Exit codes that are returned from main().
	///	@remark The enum is always int based.
	///	@remark Negative exit codes are returned by an application, positive ones are returned by an engine.
	enum class ExitCodes : int
	{
		EngineTickException = -3,
		ApplicationTickException = -2,
		MainException = -1,
		Success = 0,
		SystemTickException = 1,
		SystemManagerTickException = 2
	};
}
