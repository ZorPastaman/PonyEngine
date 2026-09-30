/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:ObjectHandle;

import std;

export namespace PonyEngine::World
{
	using ObjectHandleID = std::uint32_t; ///< Object handle ID.
	using ObjectHandleVersion = std::uint32_t; ///< Handle version.

	/// @brief Typeless object handle. Don't use them directly. Use the @p ObjectHandle.
	struct alignas(std::uint64_t) TypelessObjectHandle final
	{
		ObjectHandleID id = std::numeric_limits<ObjectHandleID>::max(); ///< Handle ID.
		ObjectHandleVersion version = 0u; ///< Handle version.

		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const TypelessObjectHandle& other) const noexcept = default;
	};

	static_assert(sizeof(TypelessObjectHandle) == sizeof(std::uint64_t) && alignof(TypelessObjectHandle) == alignof(std::uint64_t), "TypelessObjectHandle is invalid");

	/// @brief Object handle. Can be used in components to reference objects.
	/// @tparam T Object type.
	template<typename T>
	struct ObjectHandle final
	{
		TypelessObjectHandle typeless; ///< Typeless handle.

		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ObjectHandle& other) const noexcept = default;
	};

	/// @brief Returns the handle as std::uint64_t.
	/// @param handle Object handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(TypelessObjectHandle& handle) noexcept;
	/// @brief Returns the handle as std::uint64_t.
	/// @param handle Object handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const TypelessObjectHandle& handle) noexcept;

	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @param handles Object handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<TypelessObjectHandle> handles) noexcept;
	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @param handles Object handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const TypelessObjectHandle> handles) noexcept;

	/// @brief Returns the handle as std::uint64_t.
	/// @tparam T Object type.
	/// @param handle Object handle.
	/// @return Raw data.
	template<typename T> [[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(ObjectHandle<T>& handle) noexcept;
	/// @brief Returns the handle as std::uint64_t.
	/// @tparam T Object type.
	/// @param handle Object handle.
	/// @return Raw data.
	template<typename T> [[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const ObjectHandle<T>& handle) noexcept;

	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @tparam T Object type.
	/// @param handles Object handles.
	/// @return Raw data.
	template<typename T> [[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<ObjectHandle<T>> handles) noexcept;
	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @tparam T Object type.
	/// @param handles Object handles.
	/// @return Raw data.
	template<typename T> [[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const ObjectHandle<T>> handles) noexcept;
}

namespace PonyEngine::World
{
	std::uint64_t& TypelessObjectHandle::AsRawData() noexcept
	{
		return World::AsRawData(*this);
	}

	const std::uint64_t& TypelessObjectHandle::AsRawData() const noexcept
	{
		return World::AsRawData(*this);
	}

	std::uint64_t& AsRawData(TypelessObjectHandle& handle) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(handle);
	}

	const std::uint64_t& AsRawData(const TypelessObjectHandle& handle) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(handle);
	}

	std::span<std::uint64_t> AsRawData(const std::span<TypelessObjectHandle> handles) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(handles.data()), handles.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const TypelessObjectHandle> handles) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(handles.data()), handles.size());
	}

	template<typename T>
	std::uint64_t& ObjectHandle<T>::AsRawData() noexcept
	{
		return World::AsRawData(*this);
	}

	template<typename T>
	const std::uint64_t& ObjectHandle<T>::AsRawData() const noexcept
	{
		return World::AsRawData(*this);
	}

	template<typename T>
	std::uint64_t& AsRawData(ObjectHandle<T>& handle) noexcept
	{
		static_assert(sizeof(ObjectHandle) == sizeof(std::uint64_t) && alignof(ObjectHandle) == alignof(std::uint64_t), "ObjectHandle is invalid");
		return reinterpret_cast<std::uint64_t&>(handle);
	}

	template<typename T>
	const std::uint64_t& AsRawData(const ObjectHandle<T>& handle) noexcept
	{
		static_assert(sizeof(ObjectHandle) == sizeof(std::uint64_t) && alignof(ObjectHandle) == alignof(std::uint64_t), "ObjectHandle is invalid");
		return reinterpret_cast<std::uint64_t&>(handle);
	}

	template<typename T>
	std::span<std::uint64_t> AsRawData(const std::span<ObjectHandle<T>> handles) noexcept
	{
		static_assert(sizeof(ObjectHandle) == sizeof(std::uint64_t) && alignof(ObjectHandle) == alignof(std::uint64_t), "ObjectHandle is invalid");
		return std::span(reinterpret_cast<std::uint64_t*>(handles.data()), handles.size());
	}

	template<typename T>
	std::span<const std::uint64_t> AsRawData(const std::span<const ObjectHandle<T>> handles) noexcept
	{
		static_assert(sizeof(ObjectHandle) == sizeof(std::uint64_t) && alignof(ObjectHandle) == alignof(std::uint64_t), "ObjectHandle is invalid");
		return std::span(reinterpret_cast<const std::uint64_t*>(handles.data()), handles.size());
	}
}

export template<>
struct std::hash<PonyEngine::World::TypelessObjectHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::TypelessObjectHandle& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(handle.AsRawData());
	}
};

export template<typename T>
struct std::hash<PonyEngine::World::ObjectHandle<T>> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::ObjectHandle<T>& handle) const noexcept
	{
		return std::hash<PonyEngine::World::TypelessObjectHandle>()(handle.typeless);
	}
};
