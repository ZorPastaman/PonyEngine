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
	/// @brief Log data input.
	export class LogInput final
	{
	public:
		/// @brief Creates a @p LogInput.
		/// @param message Log message.
		/// @param frameCount Engine frame count.
		[[nodiscard("Pure constructor")]]
		inline LogInput(const char* message, std::size_t frameCount) noexcept;
		[[nodiscard("Pure constructor")]]
		inline LogInput(const LogInput& other) noexcept = default;

		inline ~LogInput() noexcept = default;

		/// @brief Gets a log message.
		/// @return Log message.
		[[nodiscard("Pure function")]]
		inline const char* GetMessage() const noexcept;
		/// @brief Gets an engine frame count.
		/// @return Engine frame count.
		[[nodiscard("Pure function")]]
		inline std::size_t GetFrameCount() const noexcept;

		LogInput& operator =(const LogInput& other) noexcept = default;

	private:
		const char* const m_message; /// @brief Log message.
		const std::size_t m_frameCount; /// @brief Engine frame count.
	};

	inline LogInput::LogInput(const char* const message, const std::size_t frameCount) noexcept :
		m_message{message},
		m_frameCount{frameCount}
	{
	}

	inline const char* LogInput::GetMessage() const noexcept
	{
		return m_message;
	}

	inline std::size_t LogInput::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}
}
