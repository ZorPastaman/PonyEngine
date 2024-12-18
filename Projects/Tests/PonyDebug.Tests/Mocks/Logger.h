/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <cstddef>
#include <cstdint>
#include <exception>
#include <optional>
#include <string_view>

import PonyDebug.Log;

namespace Log
{
	class Logger final : public PonyDebug::Log::ILogger
	{
	public:
		virtual void Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) const noexcept override;
		virtual void LogException(const ::std::exception& exception, const PonyDebug::Log::LogInput& logInput) const noexcept override;

		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

		std::optional<PonyDebug::Log::LogType> expectedLogType = {};
		std::optional<const std::exception*> expectedException = {};
		std::optional<std::string_view> expectedMessage = {};
		std::optional<std::optional<std::int64_t>> expectedFrameCount = {};

	private:
		mutable std::size_t version = 0;
	};
}
