/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "SubLogger.h"

#include "CppUnitTest.h"

#include <cstdint>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
