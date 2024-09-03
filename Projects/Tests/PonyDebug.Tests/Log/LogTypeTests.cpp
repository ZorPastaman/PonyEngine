/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <string>
#include <type_traits>

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogTypeTests)
	{
		static void ToStringTestElement(const PonyDebug::Log::LogType logType, const char* expectedString)
		{
			Assert::AreEqual(expectedString, PonyDebug::Log::ToString(logType));

			std::ostringstream ss;
			ss << logType;
			Assert::AreEqual(expectedString, ss.str().c_str());
		}

		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(0), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(1), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Verbose));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(2), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Debug));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(4), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Info));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(8), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Warning));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(16), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Error));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(32), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::Exception));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(63), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(PonyDebug::Log::LogType::All));
		}

		TEST_METHOD(LogicalOperatorsTest)
		{
			constexpr auto orLogType = PonyDebug::Log::LogType::Debug | PonyDebug::Log::LogType::Warning | PonyDebug::Log::LogType::Exception;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(42), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(orLogType));

			constexpr auto andLogType = (PonyDebug::Log::LogType::Verbose | PonyDebug::Log::LogType::Debug | PonyDebug::Log::LogType::Warning) & orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(10), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(andLogType));

			constexpr auto xorLogType = (PonyDebug::Log::LogType::Verbose | PonyDebug::Log::LogType::Debug | PonyDebug::Log::LogType::Warning) ^ orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(33), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(xorLogType));

			constexpr PonyDebug::Log::LogType complementLogType = ~orLogType;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(21), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(complementLogType));
		}

		TEST_METHOD(ToStringTest)
		{
			ToStringTestElement(PonyDebug::Log::LogType::None, "Unknown");
			ToStringTestElement(PonyDebug::Log::LogType::Verbose, "Verbose");
			ToStringTestElement(PonyDebug::Log::LogType::Debug, "Debug");
			ToStringTestElement(PonyDebug::Log::LogType::Info, "Info");
			ToStringTestElement(PonyDebug::Log::LogType::Warning, "Warning");
			ToStringTestElement(PonyDebug::Log::LogType::Error, "Error");
			ToStringTestElement(PonyDebug::Log::LogType::Exception, "Exception");
			ToStringTestElement(PonyDebug::Log::LogType::All, "Unknown");
			ToStringTestElement(PonyDebug::Log::LogType::Info | PonyDebug::Log::LogType::Debug, "Unknown");
			ToStringTestElement(static_cast<PonyDebug::Log::LogType>(111), "Unknown");
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto complement = ~PonyDebug::Log::LogType::Debug;
			[[maybe_unused]] constexpr auto andResult = PonyDebug::Log::LogType::Info & PonyDebug::Log::LogType::Warning;
			[[maybe_unused]] constexpr auto orResult = PonyDebug::Log::LogType::Error | PonyDebug::Log::LogType::Exception;
			[[maybe_unused]] constexpr auto xorResult = PonyDebug::Log::LogType::Verbose ^ PonyDebug::Log::LogType::Info;
			[[maybe_unused]] constexpr auto string = PonyDebug::Log::ToString(PonyDebug::Log::LogType::Info);
		}
	};
}
