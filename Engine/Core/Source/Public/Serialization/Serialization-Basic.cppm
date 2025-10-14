/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Serialization:Basic;

import std;

import PonyEngine.Text;
import PonyEngine.Type;

export namespace PonyEngine::Serialization
{
	/// @brief Gets a required text length to serialize the @p value.
	/// @tparam T Value type.
	/// @param value Value.
	/// @return Text length.
	/// @remark Floating points are always treated as longest values.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr std::size_t GetSerializedTextLength(T value) noexcept;
	/// @brief Gets a required text length to serialize any value of type @p T.
	/// @tparam T Value type.
	/// @return Text length.
	template<Type::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr std::size_t GetSerializedTextLength() noexcept;
	/// @brief Required text length to serialize any value of type @p T.
	/// @tparam T Value type.
	template<Type::Arithmetic T>
	constexpr std::size_t SerializedTextLength = GetSerializedTextLength<T>();

	/// @brief Serializes the @p value to the binary @p data.
	/// @tparam T Value type.
	/// @param value Value.
	/// @param data Binary data.
	template<typename T>
	void SerializeBinary(T value, std::span<std::byte, sizeof(T)> data) noexcept;
	/// @brief Deserializes the @p value from the binary @p data.
	/// @tparam T Value type.
	/// @param data Binary data.
	/// @param value Value.
	template<typename T>
	void DeserializeBinary(std::span<const std::byte, sizeof(T)> data, T& value) noexcept;

	/// @brief Serializes the @p value to the text @p data.
	/// @tparam T Value type.
	/// @param value Value.
	/// @param data Text data.
	/// @return Pointer after the end of the written data.
	template<Type::Arithmetic T>
	char* SerializeText(T value, std::span<char> data);
	/// @brief Deserializes the @p value from the text @p data.
	/// @tparam T Value type.
	/// @param data Text data.
	/// @param value Value.
	/// @return Pointer after the end of the read data.
	template<Type::Arithmetic T>
	const char* DeserializeText(std::span<const char> data, T& value);
}

namespace PonyEngine::Serialization
{
	template<Type::Arithmetic T>
	constexpr std::size_t GetSerializedTextLength(const T value) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return GetSerializedTextLength<T>();
		}
		else
		{
			if constexpr (std::is_signed_v<T>)
			{
				return Type::Digits10(value) + (value < T{0});
			}
			else
			{
				return Type::Digits10(value);
			}
		}
	}

	template<Type::Arithmetic T>
	constexpr std::size_t GetSerializedTextLength() noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::numeric_limits<T>::max_digits10 + Type::Digits10(std::numeric_limits<T>::max_exponent10) + 4;
		}
		else
		{
			return std::numeric_limits<T>::digits10 + std::is_signed_v<T> + 1;
		}
	}

	template<typename T>
	void SerializeBinary(const T value, const std::span<std::byte, sizeof(T)> data) noexcept
	{
		std::memcpy(data.data(), &value, sizeof(T));
	}

	template<typename T>
	void DeserializeBinary(const std::span<const std::byte, sizeof(T)> data, T& value) noexcept
	{
		std::memcpy(&value, data.data(), sizeof(T));
	}

	template<Type::Arithmetic T>
	char* SerializeText(const T value, const std::span<char> data)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			if (data.size() < 1uz) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to serialize data. Error code: '0x{:X}'.", std::to_underlying(std::errc::value_too_large)));
			}

			data[0] = '0' + value;
			return data.data() + 1uz;
		}
		else
		{
			const auto [pt, ec] = std::to_chars(data.data(), data.data() + data.size(), value);

			if (ec != std::errc()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to serialize data. Error code: '0x{:X}'.", std::to_underlying(ec)));
			}

			return pt;
		}
	}

	template<Type::Arithmetic T>
	const char* DeserializeText(const std::span<const char> data, T& value)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			if (data.size() < 1uz) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to deserialize data. Error code: '0x{:X}'.", std::to_underlying(std::errc::invalid_argument)));
			}
			if (data[0] != '0' && data[0] != '1') [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to deserialize data. Error code: '0x{:X}'.", std::to_underlying(std::errc::invalid_argument)));
			}

			value = data[0] != '0';
			return data.data() + 1uz;
		}
		else
		{
			const auto [pt, ec] = std::from_chars(data.data(), data.data() + data.size(), value);

			if (ec != std::errc()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to deserialize data. Error code: '0x{:X}'.", std::to_underlying(ec)));
			}

			return pt;
		}
	}
}
