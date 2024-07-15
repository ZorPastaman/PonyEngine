/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.TypeInfoUtility;

import <cstddef>;
import <typeinfo>;

export namespace PonyEngine::Utility
{
	/// @brief @p std::type_info hash algorithm.
	struct TypeInfoHash final
	{
		/// @brief Gets a hash of the @p typeInfo.
		/// @param typeInfo Type info.
		/// @return Type info hash.
		[[nodiscard("Pure operator")]]
		std::size_t operator ()(const std::type_info& typeInfo) const noexcept;
	};

	/// @brief @p std::type_info equal algorithm.
	struct TypeInfoEqual final
	{
		/// @brief Check if the two @p std::type_info are equal.
		/// @param left Left type info.
		/// @param right Right type info.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ()(const std::type_info& left, const std::type_info& right) const noexcept;
	};
}

namespace PonyEngine::Utility
{
	std::size_t TypeInfoHash::operator ()(const std::type_info& typeInfo) const noexcept
	{
		return typeInfo.hash_code();
	}

	bool TypeInfoEqual::operator ()(const std::type_info& left, const std::type_info& right) const noexcept
	{
		return left == right;
	}
}
