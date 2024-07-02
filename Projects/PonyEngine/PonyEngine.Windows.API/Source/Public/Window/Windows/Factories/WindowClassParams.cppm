/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories:WindowClassParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Window class parameters. They are used in RegisterClass() function.
	class WindowClassParams final
	{
	public:
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit WindowClassParams(const std::wstring& className);
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit WindowClassParams(const wchar_t* className) noexcept;
		WindowClassParams(const WindowClassParams& other) = default;
		WindowClassParams(WindowClassParams&& other) = default;

		~WindowClassParams() noexcept = default;

		/// @brief Gets a class name.
		/// @return Class name.
		[[nodiscard("Pure function")]]
		const std::wstring& GetWindowClassName() const noexcept;

		WindowClassParams& operator =(const WindowClassParams& other) = default;
		WindowClassParams& operator =(WindowClassParams&& other) = default;

	private:
		std::wstring className; ///< Class name.
	};
}

namespace PonyEngine::Window
{
	WindowClassParams::WindowClassParams(const std::wstring& className) :
		className(className)
	{
	}

	WindowClassParams::WindowClassParams(const wchar_t* className) noexcept :
		className(className)
	{
	}

	const std::wstring& WindowClassParams::GetWindowClassName() const noexcept
	{
		return className;
	}
}
