/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <utility>

import PonyShader.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(ThreadGroupCountsTests)
	{
		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountCount);
			Assert::AreEqual(65536u, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax);
			Assert::AreEqual(4194304u, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountProductMax);
		}

		TEST_METHOD(DefaultConstructorTest)
		{
			const auto counts = PonyShader::Core::ThreadGroupCounts();
			Assert::AreEqual(0u, counts.ThreadGroupCountX());
			Assert::AreEqual(0u, counts.ThreadGroupCountY());
			Assert::AreEqual(0u, counts.ThreadGroupCountZ());
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto counts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			Assert::AreEqual(4u, counts.ThreadGroupCountX());
			Assert::AreEqual(7u, counts.ThreadGroupCountY());
			Assert::AreEqual(2u, counts.ThreadGroupCountZ());
		}

		TEST_METHOD(SpanConstructorTest)
		{
			constexpr std::array<std::uint32_t, 3> data = { 1u, 5u, 3u };
			const auto counts = PonyShader::Core::ThreadGroupCounts(data);
			Assert::AreEqual(data[0], counts.ThreadGroupCountX());
			Assert::AreEqual(data[1], counts.ThreadGroupCountY());
			Assert::AreEqual(data[2], counts.ThreadGroupCountZ());
		}

		TEST_METHOD(GetSetTest)
		{
			auto counts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			counts.ThreadGroupCountX(6u);
			Assert::AreEqual(6u, counts.ThreadGroupCountX());
			counts.ThreadGroupCountY(10u);
			Assert::AreEqual(10u, counts.ThreadGroupCountY());
			counts.ThreadGroupCountZ(16u);
			Assert::AreEqual(16u, counts.ThreadGroupCountZ());

			counts.ThreadGroupCount(0, 20u);
			Assert::AreEqual(20u, counts.ThreadGroupCount(0));
			counts.ThreadGroupCount(1, 100u);
			Assert::AreEqual(100u, counts.ThreadGroupCount(1));
			counts.ThreadGroupCount(2, 600u);
			Assert::AreEqual(600u, counts.ThreadGroupCount(2));

			counts = PonyShader::Core::ThreadGroupCounts(4u, 1u, 1u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountX(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCountX(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);
			counts = PonyShader::Core::ThreadGroupCounts(1u, 7u, 1u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountY(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCountY(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);
			counts = PonyShader::Core::ThreadGroupCounts(1u, 1u, 2u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountZ(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCountZ(PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);
			counts = PonyShader::Core::ThreadGroupCounts(4u, 1u, 1u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(0, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCount(0, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);
			counts = PonyShader::Core::ThreadGroupCounts(1u, 7u, 1u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(1, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCount(1, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);
			counts = PonyShader::Core::ThreadGroupCounts(1u, 1u, 2u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(2, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax); });
			counts.ThreadGroupCount(2, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountMax - 1u);

			counts = PonyShader::Core::ThreadGroupCounts(20u, 100u, 600u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountX(70u); });
			counts.ThreadGroupCountX(69u);
			counts.ThreadGroupCountX(20u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountY(350u); });
			counts.ThreadGroupCountY(349u);
			counts.ThreadGroupCountY(100u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCountZ(2098u); });
			counts.ThreadGroupCountZ(2097u);
			counts.ThreadGroupCountZ(600u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(0, 70u); });
			counts.ThreadGroupCount(0, 69u);
			counts.ThreadGroupCount(0, 20u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(1, 350u); });
			counts.ThreadGroupCount(1, 349u);
			counts.ThreadGroupCount(1, 100u);
			Assert::ExpectException<std::invalid_argument>([&] { counts.ThreadGroupCount(2, 2098u); });
			counts.ThreadGroupCount(2, 2097u);
			counts.ThreadGroupCount(2, 600u);
		}

		TEST_METHOD(SpanTest)
		{
			const auto counts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			Assert::AreEqual(4u, counts.Span()[0]);
			Assert::AreEqual(7u, counts.Span()[1]);
			Assert::AreEqual(2u, counts.Span()[2]);
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto counts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			auto copied = PonyShader::Core::ThreadGroupCounts();
			copied = counts;
			Assert::IsTrue(counts == copied);

			auto moved = PonyShader::Core::ThreadGroupCounts();
			moved = std::move(copied);
			Assert::IsTrue(counts == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto counts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			const auto copied = counts;
			Assert::IsTrue(copied == counts);

			for (std::size_t i = 0; i < 3; ++i)
			{
				const std::uint32_t was = counts.ThreadGroupCount(i);
				counts.ThreadGroupCount(i, was + 1u);
				Assert::IsFalse(copied == counts);
				counts.ThreadGroupCount(i, was);
			}
		}

		static constexpr PonyShader::Core::ThreadGroupCounts ThreadGroupCountsConstexpr()
		{
			auto threadGroupCounts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			auto moved = std::move(threadGroupCounts);

			moved.ThreadGroupCountX(2u);
			moved.ThreadGroupCountY(2u);
			moved.ThreadGroupCountZ(2u);
			moved.ThreadGroupCount(0, 2u);

			auto copied = PonyShader::Core::ThreadGroupCounts();
			copied = moved;

			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultThreadGroupCounts = PonyShader::Core::ThreadGroupCounts();
			[[maybe_unused]] constexpr auto threadGroupCounts = PonyShader::Core::ThreadGroupCounts(4u, 7u, 2u);
			[[maybe_unused]] constexpr auto threadGroupCountsS = PonyShader::Core::ThreadGroupCounts(std::array{ 4u, 7u, 2u });
			[[maybe_unused]] constexpr auto copied = threadGroupCounts;
			[[maybe_unused]] constexpr auto moved = ThreadGroupCountsConstexpr();

			[[maybe_unused]] constexpr std::uint32_t x = threadGroupCounts.ThreadGroupCountX();
			[[maybe_unused]] constexpr std::uint32_t y = threadGroupCounts.ThreadGroupCountY();
			[[maybe_unused]] constexpr std::uint32_t z = threadGroupCounts.ThreadGroupCountZ();
			[[maybe_unused]] constexpr std::uint32_t c = threadGroupCounts.ThreadGroupCount(2);

			[[maybe_unused]] constexpr std::uint32_t s = threadGroupCounts.Span()[0];

			[[maybe_unused]] constexpr bool equal = threadGroupCounts == threadGroupCountsS;
			[[maybe_unused]] constexpr bool notEqual = threadGroupCounts != threadGroupCountsS;
		}
	};
}
