/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Application.Impl:Name;

import std;

export namespace PonyEngine::Application
{
	/// @brief Gets the company name.
	/// @return Company name.
	[[nodiscard("Pure function")]]
	std::string_view CompanyName() noexcept;
	/// @brief Gets the project name.
	/// @return Project name.
	[[nodiscard("Pure function")]]
	std::string_view ProjectName() noexcept;
	/// @brief Gets the project version.
	/// @return Project version.
	[[nodiscard("Pure function")]]
	std::string_view ProjectVersion() noexcept;
	/// @brief Gets the company title.
	/// @return Company title.
	[[nodiscard("Pure function")]]
	std::string_view CompanyTitle() noexcept;
	/// @brief Gets the project title.
	/// @return Project title.
	[[nodiscard("Pure function")]]
	std::string_view ProjectTitle() noexcept;
}

namespace PonyEngine::Application
{
	std::string_view CompanyName() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_COMPANY_NAME);
	}

	std::string_view ProjectName() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_PROJECT_NAME);
	}

	std::string_view ProjectVersion() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_PROJECT_VERSION);
	}

	std::string_view CompanyTitle() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_COMPANY_TITLE);
	}

	std::string_view ProjectTitle() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_PROJECT_TITLE);
	}
}
