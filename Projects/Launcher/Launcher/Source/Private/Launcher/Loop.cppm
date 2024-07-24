/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module Launcher:Loop;

import <initializer_list>;

import :ILoopElement;

export namespace Launcher
{
	/// @brief Runs loop.
	/// @param loopElements Loop elements.
	/// @return Exit code.
	int RunLoop(std::initializer_list<ILoopElement*> loopElements);
}

namespace Launcher
{
	/// @brief Checks if the @p loopElements are valid.
	/// @param loopElements Loop elements to check.
	/// @return @a True if the @p loopElements are valid; @a false otherwise.
	bool IsValid(std::initializer_list<ILoopElement*> loopElements) noexcept;

	int RunLoop(const std::initializer_list<ILoopElement*> loopElements)
	{
		assert((IsValid(loopElements) && "The loop elements aren't valid."));

		while (true)
		{
			for (ILoopElement* const loopElement : loopElements)
			{
				if (int exitCode; loopElement->Tick(exitCode))
				{
					return exitCode;
				}
			}
		}
	}

	bool IsValid(const std::initializer_list<ILoopElement*> loopElements) noexcept
	{
		if (loopElements.size() == 0)
		{
			return false;
		}

		for (const ILoopElement* const loopElement : loopElements)
		{
			if (!loopElement)
			{
				return false;
			}
		}

		return true;
	}
}
