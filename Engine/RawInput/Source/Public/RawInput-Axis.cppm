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

export module PonyEngine.RawInput:Axis;

import std;

export namespace PonyEngine::Input
{
	/// @brief Input axis.
	class Axis final
	{
	public:
		static constexpr char PathSeparator = PONY_INPUT_PATH_SEPARATOR; ///< Axis path separator.

		[[nodiscard("Pure constructor")]]
		Axis() noexcept = default;
		/// @brief Creates an axis.
		/// @param path Axis path.
		[[nodiscard("Pure constructor")]]
		explicit Axis(std::string_view path);
		[[nodiscard("Pure constructor")]]
		Axis(const Axis& other) = default;
		[[nodiscard("Pure constructor")]]
		Axis(Axis&& other) noexcept = default;

		~Axis() noexcept = default;

		/// @brief Gets the whole path.
		/// @return Whole path.
		[[nodiscard("Pure function")]]
		std::string_view Path() const noexcept;
		/// @brief Gets a layout.
		/// @return Layout.
		[[nodiscard("Pure function")]]
		std::string_view Layout() const noexcept;

		Axis& operator =(const Axis& other) = default;
		Axis& operator =(Axis&& other) noexcept = default;
		/// @brief Appends a path.
		/// @param other path to append.
		/// @return @a This.
		Axis& operator /=(const Axis& other);
		/// @brief Appends a path.
		/// @param other path to append.
		/// @return @a This.
		Axis& operator /=(std::string_view other);

		[[nodiscard("Pure operator")]]
		bool operator ==(const Axis& other) const noexcept = default;
		[[nodiscard("Pure operator")]]
		bool operator ==(std::string_view other) const noexcept;

	private:
		std::string path; ///< Axis path.
	};

	/// @brief Appends the @p rhs to the @p lhs.
	/// @param lhs Path start.
	/// @param rhs Path to append.
	/// @return Result.
	[[nodiscard("Pure operator")]]
	Axis operator /(const Axis& lhs, const Axis& rhs);
	/// @brief Appends the @p rhs to the @p lhs.
	/// @param lhs Path start.
	/// @param rhs Path to append.
	/// @return Result.
	[[nodiscard("Pure operator")]]
	Axis operator /(const Axis& lhs, std::string_view rhs);
}

export template<>
struct std::hash<PonyEngine::Input::Axis> final
{
	[[nodiscard("Pure function")]]
	std::size_t operator ()(const PonyEngine::Input::Axis& axis) const noexcept
	{
		return std::hash<std::string_view>()(axis.Path());
	}
};

namespace PonyEngine::Input
{
	Axis::Axis(const std::string_view path)
	{
		bool lastWasSeparator = false;
		for (std::size_t i = 0uz; i < path.size(); ++i)
		{
			const char symbol = path[i];
			const bool isSeparator = symbol == PathSeparator;

			if (!isSeparator || (i != 0uz && i != path.size() - 1uz && !lastWasSeparator)) [[likely]]
			{
				this->path.push_back(symbol);
			}

			lastWasSeparator = isSeparator;
		}
	}

	std::string_view Axis::Path() const noexcept
	{
		return path;
	}

	std::string_view Axis::Layout() const noexcept
	{
		const std::string_view wholePath = path;
		const std::size_t separatorIndex = wholePath.find(PathSeparator);

		return separatorIndex == std::string_view::npos ? wholePath : wholePath.substr(0uz, separatorIndex);
	}

	Axis& Axis::operator /=(const Axis& other)
	{
		return *this = *this / other;
	}

	Axis& Axis::operator /=(const std::string_view other)
	{
		return *this = *this / other;
	}

	bool Axis::operator ==(const std::string_view other) const noexcept
	{
		return path == other;
	}

	Axis operator /(const Axis& lhs, const Axis& rhs)
	{
		return lhs / rhs.Path();
	}

	Axis operator /(const Axis& lhs, const std::string_view rhs)
	{
		std::string path;
		path += lhs.Path();
		path += Axis::PathSeparator;
		path += rhs;

		return Axis(path);
	}
}
