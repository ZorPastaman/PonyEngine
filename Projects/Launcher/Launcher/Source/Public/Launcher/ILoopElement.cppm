/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:ILoopElement;

export namespace Launcher
{
	/// @brief Loop element.
	class ILoopElement
	{
	public:
		/// @brief Ticks the loop element.
		/// @param exitCode Exit code. It's used only if the function returned @a true.
		/// @return @a True if the loop should exit; @a false otherwise.
		virtual bool Tick(int& exitCode) = 0;

	protected:
		~ILoopElement() noexcept = default;
	};
}
