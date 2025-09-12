/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Main:Loop;

import std;

export namespace PonyEngine::Application
{
	/// @brief Loop.
	/// @tparam Size Step count.
	template<std::size_t Size> requires (Size > 0)
	class Loop final
	{
	public:
		static constexpr std::size_t StepCount = Size; ///< Step count.

		/// @brief Creates a loop.
		/// @param span Loop steps.
		[[nodiscard("Pure constructor")]]
		explicit Loop(std::span<const std::function<void()>, Size> span) noexcept;
		/// @brief Creates a loop.
		/// @tparam Ts Step types.
		/// @param steps Steps.
		template<typename... Ts> [[nodiscard("Pure constructor")]]
		explicit Loop(const Ts&... steps) noexcept requires (sizeof...(Ts) == Size && (std::is_same_v<Ts, std::function<void()>> && ...));
		Loop(const Loop&) = delete;
		Loop(Loop&&) = delete;

		~Loop() noexcept = default;

		/// @brief Gets a current step.
		/// @return Current step.
		[[nodiscard("Pure function")]]
		std::size_t Step() const noexcept;
		/// @brief Invokes a current step and increments the step index.
		void Next();

		Loop& operator =(const Loop&) = delete;
		Loop& operator =(Loop&&) = delete;

	private:
		std::array<std::function<void()>, Size> steps; ///< Steps.
		std::size_t stepIndex; ///< Current step index.
	};
}

namespace PonyEngine::Application
{
	template<std::size_t Size> requires (Size > 0)
	Loop<Size>::Loop(const std::span<const std::function<void()>, Size> span) noexcept :
		stepIndex{0uz}
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			steps[i] = span[i];
		}
	}

	template<std::size_t Size> requires (Size > 0)
	template<typename... Ts>
	Loop<Size>::Loop(const Ts&... steps) noexcept requires (sizeof...(Ts) == Size && (std::is_same_v<Ts, std::function<void()>> && ...)) :
		steps{steps...},
		stepIndex{0uz}
	{
	}

	template<std::size_t Size> requires (Size > 0)
	std::size_t Loop<Size>::Step() const noexcept
	{
		return stepIndex;
	}

	template<std::size_t Size> requires (Size > 0)
	void Loop<Size>::Next()
	{
		steps[stepIndex]();
		stepIndex = (stepIndex + 1uz) % Size;
	}
}
