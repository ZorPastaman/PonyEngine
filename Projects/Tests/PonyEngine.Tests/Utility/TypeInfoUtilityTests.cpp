/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <typeinfo>;

import PonyEngine.TypeInfoUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(TypeInfoUtilityTests)
	{
		TEST_METHOD(TypeInfoHashTest)
		{
			const auto& type = typeid(TypeInfoUtilityTests);
			constexpr auto typeInfoHash = PonyEngine::Utility::TypeInfoHash();

			Assert::AreEqual(type.hash_code(), typeInfoHash(type));
		}

		TEST_METHOD(TypeInfoEqualTest)
		{
			const auto& hashType = typeid(PonyEngine::Utility::TypeInfoHash);
			const auto& equalType = typeid(PonyEngine::Utility::TypeInfoEqual);
			constexpr auto typeInfoEqual = PonyEngine::Utility::TypeInfoEqual();

			Assert::IsTrue(typeInfoEqual(hashType, hashType));
			Assert::IsFalse(typeInfoEqual(hashType, equalType));
		}
	};
}
