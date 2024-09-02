/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <exception>
#include <format>
#include <string>

import PonyBase.StringUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(StringUtilityTests)
	{
		struct ExceptionHandler final
		{
			void operator ()(const std::exception&) const noexcept
			{
			}
		};

		TEST_METHOD(ConvertWStringToStringTest)
		{
			const auto origin = std::string("Pony. Engine, Convert- String!");
			const auto wideOrigin = std::wstring(origin.cbegin(), origin.cend());

			const std::string converted = PonyBase::Utility::ConvertToString(wideOrigin);
			Assert::AreEqual(0, origin.compare(converted));
		}

		TEST_METHOD(SafeFormatTest)
		{
			const auto format = "Format {}.";
			const auto formatArg = "format arg";
			Assert::AreEqual(std::format(format, formatArg), PonyBase::Utility::SafeFormat(format, formatArg));
			Assert::AreEqual(std::format(format, formatArg), PonyBase::Utility::SafeFormat<ExceptionHandler>(format, formatArg));
			Assert::AreEqual(std::format(format, formatArg), PonyBase::Utility::SafeFormat(ExceptionHandler(), format, formatArg));
		}
	};
}
