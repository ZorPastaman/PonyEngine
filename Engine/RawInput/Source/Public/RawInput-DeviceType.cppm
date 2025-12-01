/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Input/Layout.h"

export module PonyEngine.RawInput:DeviceType;

import std;

export namespace PonyEngine::Input
{
	/// @brief Device type.
	class DeviceType final
	{
	public:
		static constexpr char SubtypeSeparator = PONY_INPUT_PATH_SEPARATOR; ///< Device subtype separator.

		[[nodiscard("Pure constructor")]]
		DeviceType() noexcept = default;
		/// @brief Creates a device type.
		/// @param path Device type path.
		[[nodiscard("Pure constructor")]]
		explicit DeviceType(std::string_view path);
		[[nodiscard("Pure constructor")]]
		DeviceType(const DeviceType& other) = default;
		[[nodiscard("Pure constructor")]]
		DeviceType(DeviceType&& other) noexcept = default;

		~DeviceType() noexcept = default;

		/// @brief Gets the whole type.
		/// @return Whole type.
		[[nodiscard("Pure function")]]
		std::string_view Type() const noexcept;
		/// @brief Gets a base type.
		/// @return Base type.
		[[nodiscard("Pure function")]]
		std::string_view BaseType() const noexcept;

		DeviceType& operator =(const DeviceType& other) = default;
		DeviceType& operator =(DeviceType&& other) noexcept = default;
		/// @brief Appends a path.
		/// @param other path to append.
		/// @return @a This.
		DeviceType& operator /=(const DeviceType& other);
		/// @brief Appends a path.
		/// @param other path to append.
		/// @return @a This.
		DeviceType& operator /=(std::string_view other);

		[[nodiscard("Pure operator")]]
		bool operator ==(const DeviceType& other) const noexcept = default;
		[[nodiscard("Pure operator")]]
		bool operator ==(std::string_view other) const noexcept;

	private:
		std::string path; ///< Device type path.
	};

	/// @brief Appends the @p rhs to the @p lhs.
	/// @param lhs Path start.
	/// @param rhs Path to append.
	/// @return Result.
	[[nodiscard("Pure operator")]]
	DeviceType operator /(const DeviceType& lhs, const DeviceType& rhs);
	/// @brief Appends the @p rhs to the @p lhs.
	/// @param lhs Path start.
	/// @param rhs Path to append.
	/// @return Result.
	[[nodiscard("Pure operator")]]
	DeviceType operator /(const DeviceType& lhs, std::string_view rhs);
}

namespace PonyEngine::Input
{
	DeviceType::DeviceType(const std::string_view path)
	{
		bool lastWasSeparator = false;
		for (std::size_t i = 0uz; i < path.size(); ++i)
		{
			const char symbol = path[i];
			const bool isSeparator = symbol == SubtypeSeparator;

			if (!isSeparator || (i != 0uz && i != path.size() - 1uz && !lastWasSeparator)) [[likely]]
			{
				this->path.push_back(symbol);
			}

			lastWasSeparator = isSeparator;
		}
	}

	std::string_view DeviceType::Type() const noexcept
	{
		return path;
	}

	std::string_view DeviceType::BaseType() const noexcept
	{
		const std::string_view wholePath = path;
		const std::size_t separatorIndex = wholePath.find(SubtypeSeparator);

		return separatorIndex == std::string_view::npos ? wholePath : wholePath.substr(0uz, separatorIndex);
	}

	DeviceType& DeviceType::operator /=(const DeviceType& other)
	{
		return *this = *this / other;
	}

	DeviceType& DeviceType::operator /=(const std::string_view other)
	{
		return *this = *this / other;
	}

	bool DeviceType::operator ==(const std::string_view other) const noexcept
	{
		return path == other;
	}

	DeviceType operator /(const DeviceType& lhs, const DeviceType& rhs)
	{
		return lhs / rhs.Type();
	}

	DeviceType operator /(const DeviceType& lhs, const std::string_view rhs)
	{
		std::string path;
		path += lhs.Type();
		path += DeviceType::SubtypeSeparator;
		path += rhs;

		return DeviceType(path);
	}
}
