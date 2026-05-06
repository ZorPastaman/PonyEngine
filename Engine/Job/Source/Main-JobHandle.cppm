/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job:JobHandle;

import std;

import PonyEngine.Hash;

export namespace PonyEngine::Job
{
	struct JobHandle final
	{
		const void* data = nullptr;
		std::size_t version = 0uz;

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsValid() const noexcept;

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const JobHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Job::JobHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Job::JobHandle& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(PonyEngine::Hash::FNV1a64(std::span(reinterpret_cast<const std::byte*>(&handle), sizeof(PonyEngine::Job::JobHandle))));
	}
};

namespace PonyEngine::Job
{
	constexpr bool JobHandle::IsValid() const noexcept
	{
		return data;
	}

	constexpr JobHandle::operator bool() const noexcept
	{
		return IsValid();
	}
}
