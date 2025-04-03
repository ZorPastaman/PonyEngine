/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <utility>

import PonyShader.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(BoolTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const auto defaultBool = PonyShader::Core::Bool();
			Assert::IsFalse(defaultBool);

			const PonyShader::Core::Bool falseBool = false;
			Assert::IsFalse(falseBool);
			const PonyShader::Core::Bool trueBool = true;
			Assert::IsTrue(trueBool);

			auto copied = trueBool;
			Assert::IsTrue(copied);

			const auto moved = std::move(copied);
			Assert::IsTrue(moved);
		}

		TEST_METHOD(AssignmentTest)
		{
			const PonyShader::Core::Bool value = true;

			auto copied = PonyShader::Core::Bool();
			copied = value;
			Assert::IsTrue(copied);

			auto moved = PonyShader::Core::Bool();
			moved = std::move(copied);
			Assert::IsTrue(copied);
		}

		TEST_METHOD(EqualTest)
		{
			Assert::IsTrue(PonyShader::Core::Bool(false) == PonyShader::Core::Bool(false));
			Assert::IsTrue(PonyShader::Core::Bool(true) == PonyShader::Core::Bool(true));
			Assert::IsFalse(PonyShader::Core::Bool(false) == PonyShader::Core::Bool(true));
			Assert::IsFalse(PonyShader::Core::Bool(true) == PonyShader::Core::Bool(false));
		}

		static constexpr PonyShader::Core::Bool BoolConstexpr()
		{
			auto value = PonyShader::Core::Bool();
			auto moved = std::move(value);

			auto val = PonyShader::Core::Bool();
			moved = val;
			moved = std::move(val);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultBool = PonyShader::Core::Bool();
			[[maybe_unused]] constexpr auto value = PonyShader::Core::Bool(true);
			[[maybe_unused]] constexpr auto copied = value;
			[[maybe_unused]] constexpr auto moved = BoolConstexpr();

			[[maybe_unused]] constexpr bool val = value;

			[[maybe_unused]] constexpr bool equal = value == copied;
			[[maybe_unused]] constexpr bool notEqual = value != copied;
		}
	};
}
