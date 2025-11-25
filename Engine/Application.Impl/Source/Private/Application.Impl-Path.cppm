/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:Path;

import std;

import :Name;

export namespace PonyEngine::Application
{
	/// @brief Adds a tail to the path.
	/// @param path Path.
	/// @return Path with a tail.
	[[nodiscard("Pure function")]]
	std::filesystem::path AddTail(const std::filesystem::path& path);
}

namespace PonyEngine::Application
{
	std::filesystem::path AddTail(const std::filesystem::path& path)
	{
		return (path / CompanyName() / ProjectName()).lexically_normal();
	}
}
