/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:Loop;

import <array>;
import <cstddef>;

import :ILoopElement;

export namespace Launcher
{
	/// @brief Loop.
	/// @tparam ElementCount Loop element count.
	template<std::size_t ElementCount> requires(ElementCount > 0)
	class Loop final
	{
	public:
		/// @brief Creates a loop.
		/// @param loopElements Loop elements.
		[[nodiscard("Pure constructor")]]
		explicit Loop(const std::array<ILoopElement*, ElementCount>& loopElements) noexcept;
		Loop(const Loop&) = delete;
		Loop(Loop&&) = delete;

		~Loop() noexcept = default;

		/// @brief Runs loop. It infinitely loops until one of the loop elements stops the loop.
		/// @return Exit code.
		int Run();

		Loop& operator =(const Loop&) = delete;
		Loop& operator =(Loop&&) = delete;

	private:
		std::array<ILoopElement*, ElementCount> loopElements; ///< Loop elements.
	};
}

namespace Launcher
{
	template<std::size_t ElementCount> requires(ElementCount > 0)
	Loop<ElementCount>::Loop(const std::array<ILoopElement*, ElementCount>& loopElements) noexcept :
		loopElements(loopElements)
	{
	}

	template<std::size_t ElementCount> requires(ElementCount > 0)
	int Loop<ElementCount>::Run()
	{
		while (true)
		{
			for (auto loopElement : loopElements)
			{
				if (int exitCode; loopElement->Tick(exitCode))
				{
					return exitCode;
				}
			}
		}
	}
}
