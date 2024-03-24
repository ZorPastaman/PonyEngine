/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:LogInput;

import <cstddef>;

namespace PonyEngine::Debug::Log
{
	export struct LogInput final
	{
	public:
		inline LogInput() noexcept = default;
		inline LogInput(const char* message, std::size_t frameCount) noexcept;

		inline ~LogInput() noexcept = default;

		const char* message = "";
		std::size_t frameCount = 0;
	};

	inline LogInput::LogInput(const char* const message, const std::size_t frameCount) noexcept :
		message{message},
		frameCount{frameCount}
	{
	}
}
