/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <string_view>

import PonyEngine.Core;

namespace Core
{
	class Application final : public PonyEngine::Core::IApplicationContext
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		PonyDebug::Log::ILogger* logger = nullptr;
	};
}
