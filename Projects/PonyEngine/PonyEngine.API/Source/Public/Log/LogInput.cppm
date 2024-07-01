/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogInput;

import <cstddef>;

export namespace PonyEngine::Log
{
	/// @brief Log data input.
	class LogInput final
	{
	public:
		/// @brief Creates a @p LogInput.
		/// @param message Log message.
		/// @param frameCount Engine frame count.
		[[nodiscard("Pure constructor")]]
		LogInput(const char* message, std::size_t frameCount) noexcept;
		[[nodiscard("Pure constructor")]]
		LogInput(const LogInput& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LogInput(LogInput&& other) noexcept = default;

		~LogInput() noexcept = default;

		/// @brief Gets a log message.
		/// @return Log message.
		[[nodiscard("Pure function")]]
		const char* GetMessage() const noexcept;
		/// @brief Gets an engine frame count.
		/// @return Engine frame count.
		[[nodiscard("Pure function")]]
		std::size_t GetFrameCount() const noexcept;

		LogInput& operator =(const LogInput& other) noexcept = default;
		LogInput& operator =(LogInput&& other) noexcept = default;

	private:
		const char* m_message; ///< Log message.
		std::size_t m_frameCount; ///< Engine frame count.
	};
}

namespace PonyEngine::Log
{
	LogInput::LogInput(const char* const message, const std::size_t frameCount) noexcept :
		m_message{message},
		m_frameCount{frameCount}
	{
	}

	const char* LogInput::GetMessage() const noexcept
	{
		return m_message;
	}

	std::size_t LogInput::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}
}
