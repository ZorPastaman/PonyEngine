/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Keyboard.Impl:KeyboardEvent;

import std;

import PonyEngine.Input;
import PonyEngine.Math;

export namespace PonyEngine::Input
{
	struct KeyboardInput final
	{
		KeyboardLayout key;
		bool pressed;
		std::chrono::time_point<std::chrono::steady_clock> eventTime;
		Math::Vector2<std::int32_t> cursorPosition;
	};

	struct KeyboardConnection final
	{
		bool isConnected;
	};

	using KeyboardEvent = std::variant<KeyboardInput, KeyboardConnection>;
}
