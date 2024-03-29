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

namespace PonyEngine::Input
{
	/// @brief Registered input event handle.
	export struct Handle final
	{
	public:
		/// @brief Creates a handle with the @p id.
		/// @param id Unique event ID.
		[[nodiscard("Pure constructor")]]
		explicit inline Handle(std::size_t id) noexcept;
		[[nodiscard("Pure constructor")]]
		inline Handle(const Handle& other) noexcept = default;

		inline ~Handle() noexcept = default;

		/// @brief Gets ID.
		/// @return ID.
		[[nodiscard("Pure function")]]
		inline std::size_t GetId() const noexcept;

		inline Handle& operator =(const Handle& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		inline bool operator ==(const Handle& other) const noexcept = default;

	private:
		std::size_t m_id; /// @brief Unique event ID.
	};

	inline Handle::Handle(std::size_t id) noexcept :
		m_id{id}
	{
	}

	inline std::size_t Handle::GetId() const noexcept
	{
		return m_id;
	}
}

/// @brief Handle hash struct.
export template<>
struct std::hash<PonyEngine::Input::Handle> final
{
public:
	[[nodiscard("Pure operator")]]
	inline std::size_t operator ()(const PonyEngine::Input::Handle& handle) const noexcept;
};

inline std::size_t std::hash<PonyEngine::Input::Handle>::operator ()(const PonyEngine::Input::Handle& handle) const noexcept
{
	return handle.GetId();
}
