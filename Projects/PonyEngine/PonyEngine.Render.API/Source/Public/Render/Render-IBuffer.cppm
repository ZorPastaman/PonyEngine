/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:IBuffer;

import <cstddef>;
import <cstdint>;
import <optional>;
import <span>;
import <stdexcept>;
import <string_view>;

import PonyBase.Container;

export namespace PonyEngine::Render
{
	/// @brief Buffer.
	class IBuffer
	{
		INTERFACE_BODY(IBuffer)

		/// @brief Tries to find a data type index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data type index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> DataTypeIndex(std::string_view dataType) const noexcept = 0;
		/// @brief Gets a data type by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		virtual std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept = 0;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataTypeCount() const noexcept = 0;

		/// @brief Gets a data size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets the data count by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept = 0;
		/// @brief Gets the data count.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount() const noexcept = 0;

		/// @brief Gets a data element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data element size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets a data element count.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data element count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;

		/// @brief Gets a data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets a data.
		/// @tparam T Data type. Its size must be an element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const;

		/// @brief Gets a data element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept = 0;
		/// @brief Gets a data element.
		/// @tparam T Data type. Its size must be an element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Data.
		template<typename T> [[nodiscard("Pure function")]]
		const T& Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
	};
}

namespace PonyEngine::Render
{
	template <typename T>
	std::span<const T> IBuffer::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Data(dataTypeIndex, dataIndex);

		return std::span<const T>(reinterpret_cast<const T*>(span.data()), span.size() / sizeof(T));
	}

	template <typename T>
	const T& IBuffer::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Element(dataTypeIndex, dataIndex, elementIndex);

		return *reinterpret_cast<const T*>(span.data());
	}
}
