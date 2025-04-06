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

export module Mocks:Logger;

import <cstddef>;
import <cstdint>;
import <exception>;
import <optional>;
import <string_view>;
import <type_traits>;

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

export namespace Log
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

namespace Log
{
	void Logger::Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) const noexcept
	{
		if (expectedLogType)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(expectedLogType.value()), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logType));
		}
		if (expectedMessage)
		{
			Assert::AreEqual(expectedMessage.value(), logInput.message);
		}
		if (expectedFrameCount)
		{
			if (expectedFrameCount.value())
			{
				Assert::IsTrue(logInput.frameCount.has_value());
				Assert::AreEqual(expectedFrameCount.value().value(), logInput.frameCount.value());
			}
			else
			{
				Assert::IsFalse(logInput.frameCount.has_value());
			}
		}

		++version;
	}

	void Logger::LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) const noexcept
	{
		if (expectedException)
		{
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException.value()), reinterpret_cast<std::uintptr_t>(&exception));
		}
		if (expectedMessage)
		{
			Assert::AreEqual(expectedMessage.value(), logInput.message);
		}
		if (expectedFrameCount)
		{
			if (expectedFrameCount.value())
			{
				Assert::IsTrue(logInput.frameCount.has_value());
				Assert::AreEqual(expectedFrameCount.value().value(), logInput.frameCount.value());
			}
			else
			{
				Assert::IsFalse(logInput.frameCount.has_value());
			}
		}

		++version;
	}

	std::size_t Logger::Version() const noexcept
	{
		return version;
	}
}
