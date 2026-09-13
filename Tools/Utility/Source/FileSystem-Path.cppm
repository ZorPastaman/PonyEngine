/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.FileSystem:Path;

import std;

export namespace PonyTools::FileSystem
{
	/// @brief Normalizes the @p path.
	/// @return Normalized path.
	[[nodiscard("Pure function")]]
	std::filesystem::path NormalizePath(const std::filesystem::path& path);
}

namespace PonyTools::FileSystem
{
	std::filesystem::path NormalizePath(const std::filesystem::path& path)
	{
		return std::filesystem::absolute(path).lexically_normal();
	}
}
