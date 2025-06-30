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

export module PonyEngine.Engine:IEngine;

export namespace PonyEngine::Engine
{
	/// @brief Engine.
	class IEngine
	{
		INTERFACE_BODY(IEngine)

		/// @brief Did the engine receive an exit code?
		/// @remark Exit code can be gotten via @p ExitCode().
		/// @return @a False if the engine received an exit code; @a true otherwise;
		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept = 0;
		/// @brief Gets the exit code.
		/// @note Mustn't be called if @p IsRunning() returns @a true.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept = 0;
	};
}
