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
	export class WindowClassParams final
	{
	public:
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit inline WindowClassParams(const std::wstring& className);
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit inline WindowClassParams(std::wstring&& className) noexcept;
		/// @brief Create a Window class params with a predefined class name.
		/// @param className Class name.
		explicit inline WindowClassParams(const wchar_t* className) noexcept;
		WindowClassParams(const WindowClassParams& other) = default;
		WindowClassParams(WindowClassParams&& other) = default;

		~WindowClassParams() noexcept = default;

		/// @brief Gets a class name.
		/// @return Class name.
		[[nodiscard("Pure function")]]
		inline const std::wstring& GetWindowClassName() const noexcept;

		WindowClassParams& operator =(const WindowClassParams& other) = default;
		WindowClassParams& operator =(WindowClassParams&& other) = default;

	private:
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

	inline WindowClassParams::WindowClassParams(const wchar_t* className) noexcept :
		m_className(className)
	{
	}

	inline const std::wstring& WindowClassParams::GetWindowClassName() const noexcept
	{
		return m_className;
	}
}
