/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Path.Configurator:Utility;

import std;

import PonyEngine.Application;

export namespace PonyEngine::Path
{
	/// @brief Adds a project tail to the path.
	/// @param path Path.
	/// @param application Application context.
	/// @return Path with a project tail.
	[[nodiscard("Pure function")]]
	std::filesystem::path AddProjectTail(const std::filesystem::path& path, const Application::IApplicationContext& application);
	/// @brief Adds a log tail to the path.
	/// @param path Path.
	/// @return Path with a log tail.
	[[nodiscard("Pure function")]]
	std::filesystem::path AddLogTail(const std::filesystem::path& path);
}

namespace PonyEngine::Path
{
	std::filesystem::path AddProjectTail(const std::filesystem::path& path, const Application::IApplicationContext& application)
	{
		return path / application.CompanyName() / application.ProjectName();
	}

	std::filesystem::path AddLogTail(const std::filesystem::path& path)
	{
		return path / PONY_STRINGIFY_VALUE(PONY_ENGINE_PATH_LOG_PATH);
	}
}
