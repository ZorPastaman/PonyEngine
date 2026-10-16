/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.World:Name;

import std;

export namespace PonyEngine::World
{
	/// @brief Entity name.
	class Name final
	{
	public:
		static constexpr std::uint8_t MaxLength = 63u; ///< Name max length.

		/// @brief Creates an empty name.
		[[nodiscard("Pure constructor")]]
		Name() noexcept;
		/// @brief Creates name.
		/// @param name Name. It's truncated after the @p MaxLength.
		[[nodiscard("Pure constructor")]]
		explicit Name(std::string_view name) noexcept;
		[[nodiscard("Pure constructor")]]
		Name(const Name& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Name(Name&& other) noexcept = default;

		~Name() noexcept = default;

		/// @brief Gets the name data.
		/// @return Name data.
		[[nodiscard("Pure function")]]
		char* Data() noexcept;
		/// @brief Gets the name data.
		/// @return Name data.
		[[nodiscard("Pure function")]]
		const char* Data() const noexcept;
		/// @brief Gets the name length.
		/// @return Name length.
		[[nodiscard("Pure function")]]
		std::uint8_t Length() const noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Get() const noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure operator")]]
		std::string_view operator *() const noexcept;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Name& other) const noexcept;

		Name& operator =(const Name& other) noexcept = default;
		Name& operator =(Name&& other) noexcept = default;

	private:
		std::uint8_t size; ///< Name length.
		std::array<char, MaxLength> data; ///< Name array.
	};
}

namespace PonyEngine::World
{
	Name::Name() noexcept :
		size{0u}
	{
	}

	Name::Name(const std::string_view name) noexcept :
		size{name.size() > MaxLength ? MaxLength : static_cast<std::uint8_t>(name.size())}
	{
		std::memcpy(data.data(), name.data(), size);
	}

	char* Name::Data() noexcept
	{
		return data.data();
	}

	const char* Name::Data() const noexcept
	{
		return data.data();
	}

	std::uint8_t Name::Length() const noexcept
	{
		return size;
	}

	std::string_view Name::Get() const noexcept
	{
		return std::string_view(data.data(), size);
	}

	std::string_view Name::operator *() const noexcept
	{
		return Get();
	}

	bool Name::operator ==(const Name& other) const noexcept
	{
		return size == other.size && std::memcmp(data.data(), other.data.data(), size) == 0;
	}
}
