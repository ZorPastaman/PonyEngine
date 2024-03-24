/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:IPlatformQuitChecker;

namespace Launcher
{
	/// @brief Platform quit checker.
	export class IPlatformQuitChecker
	{
	public:
		/// @brief Checks if the application must be closed.
		/// @param exitCode Exit code.
		/// @return @a True if the application must be closed; @a false otherwise.
		[[nodiscard("Non-ignorable result")]]
		virtual bool Check(int& exitCode) const = 0;

	protected:
		inline virtual ~IPlatformQuitChecker() noexcept = default;
	};
}
