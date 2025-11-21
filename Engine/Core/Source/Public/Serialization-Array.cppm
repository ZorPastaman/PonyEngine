/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Serialization:Array;

import std;

import PonyEngine.Type;

import :Basic;

export namespace PonyEngine::Serialization
{
	/// @brief Gets a required text length to serialize the @p values.
	/// @tparam T Value type.
	/// @param values Values.
	/// @return Text length.
	/// @remark Floating points are always treated as longest values.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr std::size_t GetSerializedArrayTextLength(std::span<const T> values) noexcept;
	/// @brief Gets a required text length to serialize an array of any values of type @p T.
	/// @tparam T Value type.
	/// @param count Value count.
	/// @return Text length.
	/// @remark Floating points are always treated as longest values.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr std::size_t GetSerializedArrayTextLength(std::size_t count) noexcept;
	constexpr char SerializedArrayTextSeparator = ','; ///< Default text separator for a serialized array.

	/// @brief Serializes the @p values to the binary @p data.
	/// @tparam T Value type.
	/// @tparam Size Value count.
	/// @tparam DataSize Data byte count.
	/// @param values Values.
	/// @param data Binary data.
	/// @return Pointer after the last element of the written data.
	template<typename T, std::size_t Size, std::size_t DataSize>
	std::byte* SerializeArrayBinary(std::span<const T, Size> values, std::span<std::byte, DataSize> data) noexcept(Size != std::dynamic_extent && DataSize != std::dynamic_extent) requires(Size == std::dynamic_extent || DataSize == std::dynamic_extent || DataSize >= Size * sizeof(T));
	/// @brief Deserializes the @p values from the binary @p data.
	/// @tparam T Value type.
	/// @tparam Size Value count.
	/// @tparam DataSize Data byte count.
	/// @param data Binary data.
	/// @param values Values.
	/// @return Pointer after the last element of the read data.
	template<typename T, std::size_t Size, std::size_t DataSize>
	const std::byte* DeserializeArrayBinary(std::span<const std::byte, DataSize> data, std::span<T, Size> values) noexcept(Size != std::dynamic_extent && DataSize != std::dynamic_extent) requires(Size == std::dynamic_extent || DataSize == std::dynamic_extent || DataSize >= Size * sizeof(T));

	/// @brief Serializes the @p values to the text @p data.
	/// @tparam Optimized If true, it writes directly to the @p data; otherwise it creates a temporary buffer to write to and then copies it to the @p data.
	///                   So, the main difference is what happens on an exception. If Optimized is @a true, the @p data may be corrupted. If Optimized is @a false, the @p data will be changed only on success.
	/// @tparam T Value type.
	/// @param values Values.
	/// @param data Text data.
	/// @param separator Array element separator.
	/// @return Pointer after the last element of the written data.
	/// @remark Bool values are written without separators.
	template<bool Optimized = false, Type::Arithmetic T>
	char* SerializeArrayText(std::span<const T> values, std::span<char> data, char separator = SerializedArrayTextSeparator);
	/// @brief Deserializes the @p values from the text @p data.
	/// @tparam Optimized If true, it writes directly to the @p values; otherwise it creates a temporary buffer to write to and then copies it to the @p values.
	///                   So, the main difference is what happens on an exception. If Optimized is @a true, the @p values may be corrupted. If Optimized is @a false, the @p values will be changed only on success.
	/// @tparam T Value type.
	/// @param data Text data.
	/// @param values Values.
	/// @param separator Array element separator.
	/// @return Pointer after the last element of the read data.
	/// @remark Bool values are read without separators.
	template<bool Optimized = false, Type::Arithmetic T>
	const char* DeserializeArrayText(std::span<const char> data, std::span<T> values, char separator = SerializedArrayTextSeparator);
}

namespace PonyEngine::Serialization
{
	/// @brief Gets a separator length.
	/// @tparam T Value type.
	/// @param count Value count.
	/// @return Separator length.
	template<Type::Arithmetic T>
	constexpr std::size_t GetSeparatorTextLength(std::size_t count) noexcept;

	/// @brief Serializes the @p values to the text @p data.
	/// @tparam T Value type.
	/// @param values Values.
	/// @param data Text data.
	/// @param separator Array element separator.
	/// @return Pointer after the last element of the written data.
	template<Type::Arithmetic T>
	char* SerializeArrayTextDirect(std::span<const T> values, std::span<char> data, char separator = ',');
	/// @brief Deserializes the @p values from the text @p data.
	/// @tparam T Value type.
	/// @param data Text data.
	/// @param values Values.
	/// @param separator Array element separator.
	/// @return Pointer after the last element of the read data.
	template<Type::Arithmetic T>
	const char* DeserializeArrayTextDirect(std::span<const char> data, std::span<T> values, char separator = ',');

	template<Type::Arithmetic T>
	constexpr std::size_t GetSerializedArrayTextLength(const std::span<const T> values) noexcept
	{
		std::size_t length = 0uz;
		for (const T value : values)
		{
			length += GetSerializedTextLength(value);
		}

		return length + GetSeparatorTextLength<T>(values.size());
	}

	template<Type::Arithmetic T>
	constexpr std::size_t GetSerializedArrayTextLength(const std::size_t count) noexcept
	{
		return GetSerializedTextLength<T>() * count + GetSeparatorTextLength<T>(count);
	}

	template<typename T, std::size_t Size, std::size_t DataSize>
	std::byte* SerializeArrayBinary(const std::span<const T, Size> values, const std::span<std::byte, DataSize> data) noexcept(Size != std::dynamic_extent && DataSize != std::dynamic_extent) requires(Size == std::dynamic_extent || DataSize == std::dynamic_extent || DataSize >= Size * sizeof(T))
	{
		if constexpr (Size != std::dynamic_extent && DataSize != std::dynamic_extent)
		{
			constexpr std::size_t byteCount = sizeof(T) * Size;
			std::memcpy(data.data(), values.data(), byteCount);

			return data.data() + byteCount;
		}
		else
		{
			const std::size_t byteCount = values.size() * sizeof(T);

			if (byteCount > data.size()) [[unlikely]]
			{
				throw std::invalid_argument("Data is too small.");
			}

			std::memcpy(data.data(), values.data(), byteCount);
			return data.data() + byteCount;
		}
	}

	template<typename T, std::size_t Size, std::size_t DataSize>
	const std::byte* DeserializeArrayBinary(const std::span<const std::byte, DataSize> data, const std::span<T, Size> values) noexcept(Size != std::dynamic_extent && DataSize != std::dynamic_extent) requires(Size == std::dynamic_extent || DataSize == std::dynamic_extent || DataSize >= Size * sizeof(T))
	{
		if constexpr (Size != std::dynamic_extent && DataSize != std::dynamic_extent)
		{
			constexpr std::size_t byteCount = sizeof(T) * Size;
			std::memcpy(values.data(), data.data(), byteCount);

			return data.data() + byteCount;
		}
		else
		{
			const std::size_t byteCount = values.size() * sizeof(T);

			if (byteCount > data.size()) [[unlikely]]
			{
				throw std::invalid_argument("Data is too small.");
			}

			std::memcpy(values.data(), data.data(), byteCount);
			return data.data() + byteCount;
		}
	}

	template<bool Optimized, Type::Arithmetic T>
	char* SerializeArrayText(const std::span<const T> values, const std::span<char> data, const char separator)
	{
		if constexpr (Optimized)
		{
			return SerializeArrayTextDirect(values, data, separator);
		}
		else
		{
			const auto buffer = std::make_unique<char[]>(data.size());
			const char* const end = SerializeArrayTextDirect<T>(values, std::span(buffer.get(), data.size()), separator);
			const std::size_t count = end - buffer.get();
			std::memcpy(data.data(), buffer.get(), count);

			return data.data() + count;
		}
	}

	template<bool Optimized, Type::Arithmetic T>
	const char* DeserializeArrayText(const std::span<const char> data, const std::span<T> values, const char separator)
	{
		if constexpr (Optimized)
		{
			return DeserializeArrayTextDirect<T>(data, values, separator);
		}
		else
		{
			const auto buffer = std::make_unique<T[]>(values.size());
			const char* const end = DeserializeArrayTextDirect(data, std::span(buffer.get(), values.size()), separator);
			const std::size_t count = values.size() * sizeof(T);
			std::memcpy(values.data(), buffer.get(), count);

			return end;
		}
	}

	template<Type::Arithmetic T>
	constexpr std::size_t GetSeparatorTextLength(const std::size_t count) noexcept
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			return 0uz;
		}
		else
		{
			return std::max(count, 1uz) - 1uz;
		}
	}

	template<Type::Arithmetic T>
	char* SerializeArrayTextDirect(const std::span<const T> values, const std::span<char> data, const char separator)
	{
		char* dataPoint = data.data();
		const char* const end = data.data() + data.size();

		for (std::size_t i = 0uz; i < values.size(); ++i)
		{
			dataPoint = SerializeText(values[i], std::span(dataPoint, end));

			if constexpr (!std::is_same_v<T, bool>)
			{
				if (i < values.size() - 1uz) [[likely]]
				{
					if (dataPoint == end) [[unlikely]]
					{
						throw std::runtime_error(std::format("Failed to serialize data. Error code: '0x{:X}'.", std::to_underlying(std::errc::value_too_large)));
					}

					*dataPoint = separator;
					++dataPoint;
				}
			}
		}

		return dataPoint;
	}

	template<Type::Arithmetic T>
	const char* DeserializeArrayTextDirect(const std::span<const char> data, const std::span<T> values, const char separator)
	{
		const char* dataPoint = data.data();
		const char* const end = data.data() + data.size();

		for (T& value : values)
		{
			dataPoint = DeserializeText(std::span(dataPoint, end), value);

			if constexpr (!std::is_same_v<T, bool>)
			{
				if (dataPoint != end) [[likely]]
				{
					dataPoint += *dataPoint == separator;
				}
			}
		}

		return dataPoint;
	}
}
