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

export module PonyEngine.Application.Impl:IdentityUtility;

import std;

import PonyEngine.Meta;

export namespace PonyEngine::Application
{
	/// @brief Gets the engine name.
	/// @return Engine name.
	[[nodiscard("Pure function")]]
	constexpr std::string_view EngineName() noexcept;
	/// @brief Gets the engine version.
	/// @return Engine version.
	[[nodiscard("Pure function")]]
	constexpr Meta::Version EngineVersion() noexcept;
	/// @brief Gets the engine title.
	/// @return Engine title.
	[[nodiscard("Pure function")]]
	constexpr std::string_view EngineTitle() noexcept;

	/// @brief Gets the company name.
	/// @return Company name.
	[[nodiscard("Pure function")]]
	constexpr std::string_view CompanyName() noexcept;
	/// @brief Gets the project name.
	/// @return Project name.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ProjectName() noexcept;
	/// @brief Gets the project version.
	/// @return Project version.
	[[nodiscard("Pure function")]]
	constexpr Meta::Version ProjectVersion() noexcept;
	/// @brief Gets the company title.
	/// @return Company title.
	[[nodiscard("Pure function")]]
	constexpr std::string_view CompanyTitle() noexcept;
	/// @brief Gets the project title.
	/// @return Project title.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ProjectTitle() noexcept;
}

namespace PonyEngine::Application
{
	constexpr std::string_view EngineName() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_ENGINE_NAME);
	}

	constexpr Meta::Version EngineVersion() noexcept
	{
		return Meta::Version(PONY_ENGINE_VERSION_MAJOR, PONY_ENGINE_VERSION_MINOR, PONY_ENGINE_VERSION_PATCH, PONY_ENGINE_VERSION_TWEAK);
	}

	constexpr std::string_view EngineTitle() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_ENGINE_TITLE);
	}

	constexpr std::string_view CompanyName() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_COMPANY_NAME);
	}

	constexpr std::string_view ProjectName() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_PROJECT_NAME);
	}

	constexpr Meta::Version ProjectVersion() noexcept
	{
		return Meta::Version(PONY_PROJECT_VERSION_MAJOR, PONY_PROJECT_VERSION_MINOR, PONY_PROJECT_VERSION_PATCH, PONY_PROJECT_VERSION_TWEAK);
	}

	constexpr std::string_view CompanyTitle() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_COMPANY_TITLE);
	}

	constexpr std::string_view ProjectTitle() noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_PROJECT_TITLE);
	}
}
