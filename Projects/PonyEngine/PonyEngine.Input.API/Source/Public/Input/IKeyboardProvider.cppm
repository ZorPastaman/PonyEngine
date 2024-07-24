/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:IKeyboardProvider;

import :IKeyboardObserver;

export namespace PonyEngine::Input
{
	/// @brief Keyboard input provider.
	class IKeyboardProvider
	{
	public:
		IKeyboardProvider(const IKeyboardProvider&) = delete;
		IKeyboardProvider(IKeyboardProvider&&) = delete;

		/// @brief Adds a keyboard input observer.
		/// @param keyboardObserver Keyboard input observer. It mustn't be nullptr. It mustn't be already added.
		virtual void AddKeyboardObserver(IKeyboardObserver* keyboardObserver) = 0;
		/// @brief Removes a keyboard input observer.
		/// @param keyboardObserver Keyboard input observer.
		virtual void RemoveKeyboardObserver(IKeyboardObserver* keyboardObserver) = 0;

		/// @brief Gets the provider name.
		/// @return Provider name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		IKeyboardProvider& operator =(const IKeyboardProvider&) = delete;
		IKeyboardProvider& operator =(IKeyboardProvider&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IKeyboardProvider() noexcept = default;

		~IKeyboardProvider() noexcept = default;
	};
}
