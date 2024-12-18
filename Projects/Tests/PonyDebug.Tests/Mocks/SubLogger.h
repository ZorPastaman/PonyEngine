/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <optional>
#include <string_view>

import PonyDebug.Log;

namespace Log
{
	class SubLogger final : public PonyDebug::Log::ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		SubLogger() noexcept = default;
		SubLogger(const SubLogger&) = delete;
		SubLogger(SubLogger&&) = delete;

		~SubLogger() noexcept = default;

		virtual void Log(const PonyDebug::Log::LogEntry& logEntry) const noexcept override;

		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

		SubLogger& operator =(const SubLogger&) = delete;
		SubLogger& operator =(SubLogger&&) = delete;

		std::optional<std::string_view> expectedMessage = {};
		std::optional<const std::exception*> expectedException = {};
		std::optional<std::chrono::time_point<std::chrono::system_clock>> expectedTime = {};
		std::optional<std::optional<std::int64_t>> expectedFrameCount = {};
		std::optional<PonyDebug::Log::LogType> expectedLogType = {};

	private:
		mutable std::size_t version = 0;
	};
}
