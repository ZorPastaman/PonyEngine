/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <string>;
import <type_traits>;

import PonyEngine.Debug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Debug::Log
{
	TEST_CLASS(LogTypeTests)
	{
		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(0), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(1), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Verbose));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(2), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Debug));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(4), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Info));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(8), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Warning));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(16), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Error));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(32), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::Exception));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(63), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(PonyEngine::Debug::Log::LogType::All));
		}

		TEST_METHOD(LogicalOperatorsTest)
		{
			const PonyEngine::Debug::Log::LogType orLogType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning | PonyEngine::Debug::Log::LogType::Exception;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(42), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(orLogType));

			const PonyEngine::Debug::Log::LogType andLogType = (PonyEngine::Debug::Log::LogType::Verbose | PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning) & orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(10), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(andLogType));

			const PonyEngine::Debug::Log::LogType xorLogType = (PonyEngine::Debug::Log::LogType::Verbose | PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning) ^ orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(33), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(xorLogType));

			const PonyEngine::Debug::Log::LogType complementLogType = ~orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(21), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(complementLogType));
		}

		TEST_METHOD(ToStringTest)
		{
			const PonyEngine::Debug::Log::LogType logType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning | PonyEngine::Debug::Log::LogType::Exception;
			std::string string = PonyEngine::Debug::Log::ToString(logType);
			Assert::AreEqual("Debug | Warning | Exception", string.c_str());

			string = PonyEngine::Debug::Log::ToString(logType, true);
			Assert::AreEqual("Debug | Warning | Exception (42)", string.c_str());

			std::ostringstream ss;
			ss << logType;
			Assert::AreEqual(string, ss.str());
		}
	};
}
