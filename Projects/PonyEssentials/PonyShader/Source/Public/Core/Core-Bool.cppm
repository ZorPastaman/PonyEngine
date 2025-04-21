/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Core:Bool;

import <cstdint>;

export namespace PonyShader::Core
{
	/// @brief 4-byte bool.
	class Bool final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Bool() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Bool(bool value) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Bool(const Bool& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Bool(Bool&& other) noexcept = default;

		constexpr ~Bool() noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr operator bool() const noexcept;

		constexpr Bool& operator =(const Bool& other) noexcept = default;
		constexpr Bool& operator =(Bool&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Bool& other) const noexcept = default;

	private:
		std::uint32_t value; ///< Actual value.
	};
}

namespace PonyShader::Core
{
	constexpr Bool::Bool(const bool value) noexcept :
		value{value}
	{
	}

	constexpr Bool::operator bool() const noexcept
	{
		return value;
	}
}
