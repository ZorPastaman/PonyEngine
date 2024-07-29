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

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogTypeTests)
	{
		static void ToStringTestElement(const PonyEngine::Log::LogType logType, const char* expectedString)
		{
			Assert::AreEqual(expectedString, PonyEngine::Log::ToString(logType));

			std::ostringstream ss;
			ss << logType;
			Assert::AreEqual(expectedString, ss.str().c_str());
		}

		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(0), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(1), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Verbose));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(2), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(4), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Info));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(8), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Warning));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(16), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Error));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(32), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Exception));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(63), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::All));
		}

		TEST_METHOD(LogicalOperatorsTest)
		{
			constexpr auto orLogType = PonyEngine::Log::LogType::Debug | PonyEngine::Log::LogType::Warning | PonyEngine::Log::LogType::Exception;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(42), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(orLogType));

			constexpr auto andLogType = (PonyEngine::Log::LogType::Verbose | PonyEngine::Log::LogType::Debug | PonyEngine::Log::LogType::Warning) & orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(10), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(andLogType));

			constexpr auto xorLogType = (PonyEngine::Log::LogType::Verbose | PonyEngine::Log::LogType::Debug | PonyEngine::Log::LogType::Warning) ^ orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(33), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(xorLogType));

			constexpr PonyEngine::Log::LogType complementLogType = ~orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(21), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(complementLogType));
		}

		TEST_METHOD(ToStringTest)
		{
			ToStringTestElement(PonyEngine::Log::LogType::None, "None");
			ToStringTestElement(PonyEngine::Log::LogType::Verbose, "Verbose");
			ToStringTestElement(PonyEngine::Log::LogType::Debug, "Debug");
			ToStringTestElement(PonyEngine::Log::LogType::Info, "Info");
			ToStringTestElement(PonyEngine::Log::LogType::Warning, "Warning");
			ToStringTestElement(PonyEngine::Log::LogType::Error, "Error");
			ToStringTestElement(PonyEngine::Log::LogType::Exception, "Exception");
			ToStringTestElement(PonyEngine::Log::LogType::All, "Unknown");
			ToStringTestElement(PonyEngine::Log::LogType::Info | PonyEngine::Log::LogType::Debug, "Unknown");
			ToStringTestElement(static_cast<PonyEngine::Log::LogType>(111), "Unknown");
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto complement = ~PonyEngine::Log::LogType::Debug;
			[[maybe_unused]] constexpr auto andResult = PonyEngine::Log::LogType::Info & PonyEngine::Log::LogType::Warning;
			[[maybe_unused]] constexpr auto orResult = PonyEngine::Log::LogType::Error | PonyEngine::Log::LogType::Exception;
			[[maybe_unused]] constexpr auto xorResult = PonyEngine::Log::LogType::Verbose ^ PonyEngine::Log::LogType::Info;
		}
	};
}
