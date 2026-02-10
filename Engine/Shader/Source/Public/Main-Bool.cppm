/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Shader:Bool;

import std;

export namespace PonyEngine::Shader
{
	/// @brief 4-byte bool.
	class Bool final
	{
	public:
		/// @brief Creates a false bool.
		[[nodiscard("Pure constructor")]]
		constexpr Bool() noexcept;
		/// @brief Creates a bool.
		/// @param value Value.
		[[nodiscard("Pure constructor")]]
		constexpr Bool(bool value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Bool(const Bool& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Bool(Bool&& other) noexcept = default;

		constexpr ~Bool() noexcept = default;

		/// @brief Gets the value.
		/// @return Value.
		[[nodiscard("Pure function")]]
		constexpr bool Get() const noexcept;
		/// @brief Sets the value.
		/// @param value Value to set.
		constexpr void Set(bool value) noexcept;

		/// @brief Gets the value.
		/// @return Value.
		[[nodiscard("Pure operator")]]
		constexpr operator bool() const noexcept;

		constexpr Bool& operator =(const Bool& other) noexcept = default;
		constexpr Bool& operator =(Bool&& other) noexcept = default;
		/// @brief Sets the value.
		/// @param value Value to set.
		/// @return @a This.
		constexpr Bool& operator =(bool value) noexcept;

	private:
		std::uint32_t value; ///< Value.
	};
}

namespace PonyEngine::Shader
{
	constexpr Bool::Bool() noexcept :
		Bool(false)
	{
	}

	constexpr Bool::Bool(const bool value) noexcept :
		value{value}
	{
	}

	constexpr bool Bool::Get() const noexcept
	{
		return value;
	}

	constexpr void Bool::Set(const bool value) noexcept
	{
		this->value = value;
	}

	constexpr Bool::operator bool() const noexcept
	{
		return value;
	}

	constexpr Bool& Bool::operator =(const bool value) noexcept
	{
		this->value = value;
		return *this;
	}
}
