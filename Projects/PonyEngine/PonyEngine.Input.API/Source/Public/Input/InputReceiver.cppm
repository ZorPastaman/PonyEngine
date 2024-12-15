/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputReceiver;

import <functional>;

export namespace PonyEngine::Input
{
	/// @brief Input receiver. It executes a function when a bound to it event is invoked.
	class InputReceiver final
	{
	public:
		/// @brief Creates an empty @p InputReceiver.
		[[nodiscard("Pure constructor")]]
		InputReceiver() noexcept;
		InputReceiver(const InputReceiver&) = delete;
		InputReceiver(InputReceiver&&) = delete;

		~InputReceiver() noexcept = default;

		/// @brief Resets the receiver. it sets an empty action.
		void Reset() noexcept;
		/// @brief Gets the action.
		/// @return Action that is called on a receiver event.
		[[nodiscard("Pure function")]]
		const std::function<void(float)>& Action() const noexcept;
		/// @brief Sets the action.
		/// @param action Action that is called on a receiver event.
		void Action(const std::function<void(float)>& action) noexcept;

		/// @brief Executes the input event action.
		/// @param value Input event value.
		void Execute(float value);

		InputReceiver& operator =(const InputReceiver&) = delete;
		InputReceiver& operator =(InputReceiver&&) = delete;

	private:
		std::function<void(float)> func; ///< Input event action.
	};
}

namespace PonyEngine::Input
{
	InputReceiver::InputReceiver() noexcept
	{
		Reset();
	}

	void InputReceiver::Reset() noexcept
	{
		func = std::function<void(float)>{};
	}

	const std::function<void(float)>& InputReceiver::Action() const noexcept
	{
		return func;
	}

	void InputReceiver::Action(const std::function<void(float)>& action) noexcept
	{
		if (action == nullptr)
		{
			Reset();

			return;
		}

		func = action;
	}

	void InputReceiver::Execute(const float value)
	{
		func(value);
	}
}
