/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Logger.h"

#include "CppUnitTest.h"

#include <cstdint>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	void Logger::Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept
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

	void Logger::LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept
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

	std::string_view Logger::Name() const noexcept
	{
		return "TestLogger";
	}

	std::size_t Logger::Version() const noexcept
	{
		return version;
	}
}
