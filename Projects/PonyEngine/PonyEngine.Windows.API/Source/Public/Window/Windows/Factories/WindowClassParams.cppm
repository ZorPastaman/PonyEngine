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

namespace PonyEngine::Window
{
	/// @brief Window class parameters. They are used in RegisterClass() function.
	export struct WindowClassParams final
	{
	public:
		/// @brief Creates a default Window class params.
		WindowClassParams();
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		WindowClassParams(const std::wstring& className);
		WindowClassParams(const WindowClassParams& other) = default;
		WindowClassParams(WindowClassParams&& other) = default;

		~WindowClassParams() noexcept = default;

		WindowClassParams& operator =(const WindowClassParams& other) = default;
		WindowClassParams& operator =(WindowClassParams&& other) = default;

		std::wstring m_className; /// @brief Class name.
	};

	WindowClassParams::WindowClassParams() :
		m_className(L"Pony Engine Game")
	{
	}

	WindowClassParams::WindowClassParams(const std::wstring& className) :
		m_className(className)
	{
	}
}
