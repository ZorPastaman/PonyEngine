/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "CppUnitTest.h"

export module Mocks:SubLogger;

import <chrono>;
import <cstddef>;
import <cstdint>;
import <exception>;
import <optional>;
import <string_view>;

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

export namespace Log
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

namespace Log
{
	void SubLogger::Log(const PonyDebug::Log::LogEntry& logEntry) const noexcept
	{
		if (expectedMessage)
		{
			Assert::AreEqual(expectedMessage.value(), logEntry.Message());
		}
		if (expectedException)
		{
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException.value()), reinterpret_cast<std::uintptr_t>(logEntry.Exception()));
		}
		if (expectedTime)
		{
			Assert::AreEqual(expectedTime.value().time_since_epoch().count(), logEntry.TimePoint().time_since_epoch().count());
		}
		if (expectedFrameCount)
		{
			if (expectedFrameCount.value())
			{
				Assert::IsTrue(logEntry.FrameCount().has_value());
				Assert::AreEqual(expectedFrameCount.value().value(), logEntry.FrameCount().value());
			}
			else
			{
				Assert::IsFalse(logEntry.FrameCount().has_value());
			}
		}
		if (expectedLogType)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(expectedLogType.value()), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logEntry.LogType()));
		}

		++version;
	}

	std::size_t SubLogger::Version() const noexcept
	{
		return version;
	}
}
