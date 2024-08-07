/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;
import <cstdint>;
import <exception>;
import <format>;
import <string>;

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	class EmptyLogger final : public PonyEngine::Log::ILogger
	{
	public:
		const std::exception* lastException;
		std::string lastMessage;
		std::size_t lastFrameCount;
		PonyEngine::Log::LogType lastLogType;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override
		{
			return "";
		}

		virtual void Log(const PonyEngine::Log::LogType logType, const PonyEngine::Log::LogInput& logInput) noexcept override
		{
			lastMessage = logInput.message ? logInput.message : "";
			lastFrameCount = logInput.frameCount;
			lastLogType = logType;
		}

		virtual void LogException(const std::exception& exception, const PonyEngine::Log::LogInput& logInput) noexcept override
		{
			lastException = &exception;
			lastMessage = logInput.message ? logInput.message : "";
			lastFrameCount = logInput.frameCount;
		}

		virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override
		{
		}
		virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override
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
			constexpr std::size_t frameCount = 1023;

			PonyEngine::Log::LogToLogger(logger, PonyEngine::Log::LogType::Info, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Info), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			logger.lastMessage = "";
			logger.lastLogType = PonyEngine::Log::LogType::None;
			PonyEngine::Log::LogToLogger(logger, PonyEngine::Log::LogType::Warning, PonyEngine::Log::AdditionalInfo{.frameCount = frameCount}, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Warning), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			PonyEngine::Log::LogToLogger(logger, PonyEngine::Log::LogType::Info, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Info), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			PonyEngine::Log::LogToLogger(logger, PonyEngine::Log::LogType::Info, PonyEngine::Log::AdditionalInfo{.frameCount = frameCount}, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Info), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));
		}

		TEST_METHOD(LogExceptionToLoggerTest)
		{
			auto logger = EmptyLogger();
			logger.lastFrameCount = 100;

			const auto message = "Message";
			constexpr std::size_t frameCount = 1023;
			const auto exception = std::exception("Exception");

			PonyEngine::Log::LogExceptionToLogger(logger, exception);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			logger.lastException = nullptr;
			PonyEngine::Log::LogExceptionToLogger(logger, PonyEngine::Log::AdditionalInfo{.frameCount = frameCount}, exception);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(frameCount, logger.lastFrameCount);

			logger.lastException = nullptr;
			logger.lastFrameCount = 1000;
			PonyEngine::Log::LogExceptionToLogger(logger, exception, message);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			logger.lastMessage = "";
			PonyEngine::Log::LogExceptionToLogger(logger, PonyEngine::Log::AdditionalInfo{.frameCount = frameCount}, exception, message);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(frameCount, logger.lastFrameCount);

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			PonyEngine::Log::LogExceptionToLogger(logger, exception, format, formatArg);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			PonyEngine::Log::LogExceptionToLogger(logger, PonyEngine::Log::AdditionalInfo{.frameCount = frameCount}, exception, format, formatArg);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(frameCount, logger.lastFrameCount);
		}
	};
}
