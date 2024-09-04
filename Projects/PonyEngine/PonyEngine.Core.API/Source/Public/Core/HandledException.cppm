/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:HandledException;

import <concepts>;
import <exception>;
import <string>;

export namespace PonyEngine::Core
{
	/// @brief Thrown if an exception that occured in the engine was handled by the engine but the engine can't continue to work.
	/// @details If you caught this exception, it means that the engine has already logged it and stopped itself.
	class HandledException final : public std::exception
	{
	public:
		[[nodiscard("Pure constructor")]]
		HandledException() noexcept = default;
		/// @brief Creates a @p HandledException.
		/// @tparam T Exception type.
		/// @param exception Handled exception.
		template<std::derived_from<std::exception> T> [[nodiscard("Pure constructor")]]
		explicit HandledException(const T& exception) noexcept;
		[[nodiscard("Pure constructor")]]
		HandledException(const HandledException& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		HandledException(HandledException&& other) noexcept = default;

		virtual ~HandledException() noexcept override = default;

		/// @brief Gets the handled exception.
		/// @return Handled exception.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const noexcept;

		HandledException& operator =(const HandledException& other) noexcept = default;
		HandledException& operator =(HandledException&& other) noexcept = default;

	private:
		std::exception_ptr exception; ///< Handled exception.
	};
}

namespace PonyEngine::Core
{
	template<std::derived_from<std::exception> T>
	HandledException::HandledException(const T& exception) noexcept :
		std::exception(exception),
		exception(std::make_exception_ptr(exception))
	{
	}

	const std::exception_ptr& HandledException::Exception() const noexcept
	{
		return exception;
	}
}
