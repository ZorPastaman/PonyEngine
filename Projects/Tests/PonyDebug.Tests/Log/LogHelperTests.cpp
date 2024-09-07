/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <format>
#include <string>

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	class EmptyLogger final : public PonyDebug::Log::ILogger
	{
	public:
		const std::exception* lastException;
		std::string lastMessage;
		std::size_t lastFrameCount;
		PonyDebug::Log::LogType lastLogType;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override
		{
			return "";
		}

		virtual void Log(const PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept override
		{
			lastMessage = logInput.message ? logInput.message : "";
			lastFrameCount = logInput.frameCount.value_or(0);
			lastLogType = logType;
		}

		virtual void LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept override
		{
			lastException = &exception;
			lastMessage = logInput.message ? logInput.message : "";
			lastFrameCount = logInput.frameCount.value_or(0);
		}

		virtual void AddSubLogger(PonyDebug::Log::ISubLogger&) override
		{
		}
		virtual void RemoveSubLogger(PonyDebug::Log::ISubLogger&) override
		{
		}
	};

	TEST_CLASS(LogHelperTests)
	{
		TEST_METHOD(LogToLoggerTest)
		{
			auto logger = EmptyLogger();
			logger.lastFrameCount = 100;

			const auto message = "Message";

			PonyDebug::Log::LogToLogger(logger, PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Info), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logger.lastLogType));

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			PonyDebug::Log::LogToLogger(logger, PonyDebug::Log::LogType::Info, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Info), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logger.lastLogType));
		}

		TEST_METHOD(LogExceptionToLoggerTest)
		{
			auto logger = EmptyLogger();
			logger.lastFrameCount = 100;

			const auto message = "Message";
			const auto exception = std::exception("Exception");

			PonyDebug::Log::LogExceptionToLogger(logger, exception);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			logger.lastException = nullptr;
			logger.lastFrameCount = 1000;
			PonyDebug::Log::LogExceptionToLogger(logger, exception, message);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			PonyDebug::Log::LogExceptionToLogger(logger, exception, format, formatArg);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
		}
	};
}
