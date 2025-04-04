/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <span>
#include <utility>

import PonyShader.Mesh;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Mesh
{
	TEST_CLASS(PrimitiveTests)
	{
		TEST_METHOD(DefaultConstructorTest)
		{
			const auto defaultPrimitive = PonyShader::Mesh::Primitive();
			Assert::AreEqual(std::uint8_t{0u}, defaultPrimitive.I0());
			Assert::AreEqual(std::uint8_t{0u}, defaultPrimitive.I1());
			Assert::AreEqual(std::uint8_t{0u}, defaultPrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, defaultPrimitive.I3());
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto onePrimitive = PonyShader::Mesh::Primitive(4u);
			Assert::AreEqual(std::uint8_t{4u}, onePrimitive.I0());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I1());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I3());

			const auto twoPrimitive = PonyShader::Mesh::Primitive(4u, 6u);
			Assert::AreEqual(std::uint8_t{4u}, twoPrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, twoPrimitive.I1());
			Assert::AreEqual(std::uint8_t{0u}, twoPrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, twoPrimitive.I3());

			const auto threePrimitive = PonyShader::Mesh::Primitive(4u, 6u, 5u);
			Assert::AreEqual(std::uint8_t{4u}, threePrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, threePrimitive.I1());
			Assert::AreEqual(std::uint8_t{5u}, threePrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, threePrimitive.I3());

			const auto fourPrimitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			Assert::AreEqual(std::uint8_t{4u}, fourPrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, fourPrimitive.I1());
			Assert::AreEqual(std::uint8_t{5u}, fourPrimitive.I2());
			Assert::AreEqual(std::uint8_t{7u}, fourPrimitive.I3());
		}

		TEST_METHOD(SpanConstructorTest)
		{
			constexpr auto oneArray = std::array<std::uint8_t, 1>{ 4u };
			const auto onePrimitive = PonyShader::Mesh::Primitive(std::span<const std::uint8_t, 1>(oneArray.data(), oneArray.size()));
			Assert::AreEqual(std::uint8_t{4u}, onePrimitive.I0());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I1());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, onePrimitive.I3());

			constexpr auto twoArray = std::array<std::uint8_t, 2>{ 4u, 6u };
			const auto twoPrimitive = PonyShader::Mesh::Primitive(std::span<const std::uint8_t, 2>(twoArray.data(), twoArray.size()));
			Assert::AreEqual(std::uint8_t{4u}, twoPrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, twoPrimitive.I1());
			Assert::AreEqual(std::uint8_t{0u}, twoPrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, twoPrimitive.I3());

			constexpr auto threeArray = std::array<std::uint8_t, 3>{ 4u, 6u, 5u };
			const auto threePrimitive = PonyShader::Mesh::Primitive(std::span<const std::uint8_t, 3>(threeArray.data(), threeArray.size()));
			Assert::AreEqual(std::uint8_t{4u}, threePrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, threePrimitive.I1());
			Assert::AreEqual(std::uint8_t{5u}, threePrimitive.I2());
			Assert::AreEqual(std::uint8_t{0u}, threePrimitive.I3());

			constexpr auto fourArray = std::array<std::uint8_t, 4>{ 4u, 6u, 5u, 7u };
			const auto fourPrimitive = PonyShader::Mesh::Primitive(std::span<const std::uint8_t, 4>(fourArray.data(), fourArray.size()));
			Assert::AreEqual(std::uint8_t{4u}, fourPrimitive.I0());
			Assert::AreEqual(std::uint8_t{6u}, fourPrimitive.I1());
			Assert::AreEqual(std::uint8_t{5u}, fourPrimitive.I2());
			Assert::AreEqual(std::uint8_t{7u}, fourPrimitive.I3());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			constexpr auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			const auto copied = primitive;
			Assert::IsTrue(primitive == copied);
		}

		TEST_METHOD(MoveConstructorTest)
		{
			auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			const auto moved = std::move(primitive);
			Assert::IsTrue(primitive == moved);
		}

		TEST_METHOD(IndexTest)
		{
			auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			primitive.I0() = 5u;
			primitive.I1() = 2u;
			primitive.I2() = 7u;
			primitive.I3() = 1u;
			Assert::AreEqual(std::uint8_t{5u}, primitive.I0());
			Assert::AreEqual(std::uint8_t{2u}, primitive.I1());
			Assert::AreEqual(std::uint8_t{7u}, primitive.I2());
			Assert::AreEqual(std::uint8_t{1u}, primitive.I3());

			const auto primitiveC = primitive;
			Assert::AreEqual(std::uint8_t{5u}, primitiveC.I0());
			Assert::AreEqual(std::uint8_t{2u}, primitiveC.I1());
			Assert::AreEqual(std::uint8_t{7u}, primitiveC.I2());
			Assert::AreEqual(std::uint8_t{1u}, primitiveC.I3());
		}

		TEST_METHOD(SpanTest)
		{
			auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			primitive.Span()[0] = 5u;
			primitive.Span()[1] = 2u;
			primitive.Span()[2] = 7u;
			primitive.Span()[3] = 1u;
			Assert::AreEqual(std::uint8_t{5u}, primitive.Span()[0]);
			Assert::AreEqual(std::uint8_t{2u}, primitive.Span()[1]);
			Assert::AreEqual(std::uint8_t{7u}, primitive.Span()[2]);
			Assert::AreEqual(std::uint8_t{1u}, primitive.Span()[3]);

			const auto primitiveC = primitive;
			Assert::AreEqual(std::uint8_t{5u}, primitiveC.Span()[0]);
			Assert::AreEqual(std::uint8_t{2u}, primitiveC.Span()[1]);
			Assert::AreEqual(std::uint8_t{7u}, primitiveC.Span()[2]);
			Assert::AreEqual(std::uint8_t{1u}, primitiveC.Span()[3]);
		}

		TEST_METHOD(AccessTest)
		{
			auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			primitive[0] = 5u;
			primitive[1] = 2u;
			primitive[2] = 7u;
			primitive[3] = 1u;
			Assert::AreEqual(std::uint8_t{5u}, primitive[0]);
			Assert::AreEqual(std::uint8_t{2u}, primitive[1]);
			Assert::AreEqual(std::uint8_t{7u}, primitive[2]);
			Assert::AreEqual(std::uint8_t{1u}, primitive[3]);

			const auto primitiveC = primitive;
			Assert::AreEqual(std::uint8_t{5u}, primitiveC[0]);
			Assert::AreEqual(std::uint8_t{2u}, primitiveC[1]);
			Assert::AreEqual(std::uint8_t{7u}, primitiveC[2]);
			Assert::AreEqual(std::uint8_t{1u}, primitiveC[3]);
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			auto copied = PonyShader::Mesh::Primitive();
			copied = primitive;
			Assert::IsTrue(primitive == copied);

			auto moved = PonyShader::Mesh::Primitive();
			moved = std::move(copied);
			Assert::IsTrue(primitive == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto primitive = PonyShader::Mesh::Primitive(4u, 6u, 5u, 7u);
			const auto copied = primitive;
			Assert::IsTrue(primitive == copied);

			for (std::size_t i = 0; i < 4; ++i)
			{
				const std::uint8_t was = primitive[i];
				primitive[i] += 1u;
				Assert::IsFalse(primitive == copied);
				primitive[i] = was;
			}
		}

		static constexpr PonyShader::Mesh::Primitive PrimitiveConstexpr()
		{
			auto primitive = PonyShader::Mesh::Primitive(2u, 3u, 5u, 7u);
			auto moved = std::move(primitive);

			moved.I0() += 1u;
			moved.I1() += 1u;
			moved.I2() += 2u;
			moved.I3() += 2u;
			moved.Span()[0] += 2u;

			moved[1] += 3u;

			auto copied = PonyShader::Mesh::Primitive();
			copied = moved;
			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultPrimitive = PonyShader::Mesh::Primitive();
			[[maybe_unused]] constexpr auto primitive = PonyShader::Mesh::Primitive(2u, 3u, 5u, 7u);
			constexpr auto indices = std::array<std::uint8_t, 4>{ 4u, 5u, 2u, 8u };
			[[maybe_unused]] constexpr auto primitiveS = PonyShader::Mesh::Primitive(std::span<const std::uint8_t, 4>(indices.data(), indices.size()));
			[[maybe_unused]] constexpr auto copied = primitive;
			[[maybe_unused]] constexpr auto moved = PrimitiveConstexpr();

			[[maybe_unused]] constexpr std::uint8_t i0 = primitive.I0();
			[[maybe_unused]] constexpr std::uint8_t i1 = primitive.I1();
			[[maybe_unused]] constexpr std::uint8_t i2 = primitive.I2();
			[[maybe_unused]] constexpr std::uint8_t i3 = primitive.I3();
			[[maybe_unused]] constexpr std::uint8_t is = primitive.Span()[3];

			[[maybe_unused]] constexpr std::uint8_t ii = primitive[2];

			[[maybe_unused]] constexpr bool equal = primitive == primitiveS;
			[[maybe_unused]] constexpr bool notEqual = primitive != primitiveS;
		}
	};
}
