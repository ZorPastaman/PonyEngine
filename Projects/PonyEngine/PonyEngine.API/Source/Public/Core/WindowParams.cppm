/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:WindowParams;

import <string>;
import <utility>;

namespace PonyEngine::Core
{
	/// @brief Holds engine window parameters.
	export struct WindowParams final
	{
	public:
		/// @brief Creates a @p WindowParams.
		[[nodiscard("Pure constructor")]]
		inline WindowParams();
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		inline WindowParams(const WindowParams& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline WindowParams(WindowParams&& other);

		inline ~WindowParams() = default;

		std::string title; /// @brief Window title. The default value is Pony Engine Game.
		bool createWindow; /// @brief If it's @a true, a window will be created; otherwise the engine will work without a window. The default value is @a true.
	};

	inline WindowParams::WindowParams() :
		title("Pony Engine Game"),
		createWindow{true}
	{
	}

	inline WindowParams::WindowParams(const WindowParams& other) :
		title(other.title),
		createWindow{other.createWindow}
	{
	}

	inline WindowParams::WindowParams(WindowParams&& other) :
		title(std::move(other.title)),
		createWindow{other.createWindow}
	{
	}
}
