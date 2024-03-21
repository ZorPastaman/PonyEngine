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
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit inline WindowClassParams(const std::wstring& className);
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit inline WindowClassParams(std::wstring&& className) noexcept;
		WindowClassParams(const WindowClassParams& other) = default;
		WindowClassParams(WindowClassParams&& other) = default;

		~WindowClassParams() noexcept = default;

		WindowClassParams& operator =(const WindowClassParams& other) = default;
		WindowClassParams& operator =(WindowClassParams&& other) = default;

		std::wstring m_className; /// @brief Class name.
	};

	inline WindowClassParams::WindowClassParams(const std::wstring& className) :
		m_className(className)
	{
	}

	inline WindowClassParams::WindowClassParams(std::wstring&& className) noexcept :
		m_className(className)
	{
	}
}
