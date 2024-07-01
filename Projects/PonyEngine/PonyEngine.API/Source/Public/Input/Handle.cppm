/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Handle;

import <cstddef>;
import <unordered_map>;

export namespace PonyEngine::Input
{
	/// @brief Registered input event handle.
	class Handle final
	{
	public:
		/// @brief Creates a handle with the @p id.
		/// @param id Unique event ID.
		[[nodiscard("Pure constructor")]]
		explicit Handle(std::size_t id) noexcept;
		[[nodiscard("Pure constructor")]]
		Handle(const Handle& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Handle(Handle&& other) noexcept = default;

		~Handle() noexcept = default;

		/// @brief Gets ID.
		/// @return ID.
		[[nodiscard("Pure function")]]
		std::size_t GetId() const noexcept;

		Handle& operator =(const Handle& other) noexcept = default;
		Handle& operator =(Handle&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Handle& other) const noexcept = default;

	private:
		std::size_t m_id; ///< Unique event ID.
	};
}

namespace PonyEngine::Input
{
	Handle::Handle(const std::size_t id) noexcept :
		m_id{id}
	{
	}

	std::size_t Handle::GetId() const noexcept
	{
		return m_id;
	}
}

/// @brief Handle hash struct.
export template<>
struct std::hash<PonyEngine::Input::Handle> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::Input::Handle& handle) const noexcept;
};

std::size_t std::hash<PonyEngine::Input::Handle>::operator ()(const PonyEngine::Input::Handle& handle) const noexcept
{
	return handle.GetId();
}
