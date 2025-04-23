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
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <format>
#include <numbers>
#include <ostream>
#include <span>
#include <string>
#include <type_traits>
#include <utility>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(Vector4Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::int8_t, PonyMath::Core::Vector4<std::int8_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<std::int8_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int16_t, PonyMath::Core::Vector4<std::int16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<std::int16_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int32_t, PonyMath::Core::Vector4<std::int32_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<std::int32_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<std::int64_t, PonyMath::Core::Vector4<std::int64_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<std::int64_t>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Vector4<float>::ComponentCount);
			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Vector4<std::int16_t>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyMath::Core::Vector4<std::int16_t>();
			Assert::AreEqual(std::int16_t{}, vector.X());
			Assert::AreEqual(std::int16_t{}, vector.Y());
			Assert::AreEqual(std::int16_t{}, vector.Z());
			Assert::AreEqual(std::int16_t{}, vector.W());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto vector = PonyMath::Core::Vector4<float>();
			Assert::AreEqual(float{}, vector.X());
			Assert::AreEqual(float{}, vector.Y());
			Assert::AreEqual(float{}, vector.Z());
			Assert::AreEqual(float{}, vector.W());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			const auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			const auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			const auto vector = PonyMath::Core::Vector4<std::int16_t>(std::array<std::int16_t, 4>{x, y, z, w});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(ConstructorSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			const auto vector = PonyMath::Core::Vector4<float>(std::array<float, 4>{x, y, z, w});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const PonyMath::Core::Vector4<std::int16_t> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const PonyMath::Core::Vector4<float> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const PonyMath::Core::Vector4<std::int16_t> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const PonyMath::Core::Vector4<float> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());

			constexpr auto vectorC = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
			Assert::AreEqual(w, vectorC.W());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());

			constexpr auto vectorC = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
			Assert::AreEqual(w, vectorC.W());
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);
			Assert::AreEqual(w, vector.Span()[3]);

			constexpr auto vectorC = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
			Assert::AreEqual(w, vectorC.Span()[3]);
		}

		TEST_METHOD(SpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);
			Assert::AreEqual(w, vector.Span()[3]);

			constexpr auto vectorC = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
			Assert::AreEqual(w, vectorC.Span()[3]);
		}

		TEST_METHOD(MagnitudeShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(6.481f, vector.Magnitude(), 0.001f);

			Assert::AreEqual(0.f, PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(6.481f, vector.Magnitude(), 0.001f);

			Assert::AreEqual(0.f, PonyMath::Core::Vector4<float>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(std::int16_t{42}, vector.MagnitudeSquared());

			Assert::AreEqual(std::int16_t{0}, PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(MagnitudeSquaredFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(42.f, vector.MagnitudeSquared());

			Assert::AreEqual(0.f, PonyMath::Core::Vector4<float>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(NormalizeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const PonyMath::Core::Vector4<float> normalized = vector.Normalized();
			Assert::AreEqual(0.309f, normalized.X(), 0.001f);
			Assert::AreEqual(-0.463f, normalized.Y(), 0.001f);
			Assert::AreEqual(0.772f, normalized.Z(), 0.001f);
			Assert::AreEqual(-0.309f, normalized.W(), 0.001f);
			vector.Normalize();
			Assert::IsTrue(vector == normalized);
		}

		TEST_METHOD(NormalizeSafeTest)
		{
			auto vector = PonyMath::Core::Vector4<float>(2.f, -3.f, 5.f, -2.f);
			constexpr auto fallback = PonyMath::Core::Vector4<float>(1.0f, 0.0f, 1.f, 2.f);
			const PonyMath::Core::Vector4<float> normalized = vector.Normalized(fallback);
			Assert::AreEqual(0.309f, normalized.X(), 0.001f);
			Assert::AreEqual(-0.463f, normalized.Y(), 0.001f);
			Assert::AreEqual(0.772f, normalized.Z(), 0.001f);
			Assert::AreEqual(-0.309f, normalized.W(), 0.001f);

			vector.Normalize(fallback);
			Assert::IsTrue(vector == normalized);

			auto zeroVector = PonyMath::Core::Vector4<float>::Predefined::Zero;
			const PonyMath::Core::Vector4<float> normalizedZero = zeroVector.Normalized(fallback);
			Assert::AreEqual(fallback.X(), normalizedZero.X());
			Assert::AreEqual(fallback.Y(), normalizedZero.Y());
			Assert::AreEqual(fallback.Z(), normalizedZero.Z());
			Assert::AreEqual(fallback.W(), normalizedZero.W());

			zeroVector.Normalize(fallback);
			Assert::IsTrue(zeroVector == normalizedZero);
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::int16_t min = vector.Min();
			Assert::AreEqual(std::int16_t{-3}, min);
			constexpr auto cVector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::int16_t cMin = cVector.Min();
			Assert::AreEqual(std::int16_t{-3}, cMin);
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float min = vector.Min();
			Assert::AreEqual(float{-3}, min);
			constexpr auto cVector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float cMin = cVector.Min();
			Assert::AreEqual(float{-3}, cMin);
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::int16_t max = vector.Max();
			Assert::AreEqual(std::int16_t{5}, max);
			constexpr auto cVector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::int16_t cMax = cVector.Max();
			Assert::AreEqual(std::int16_t{5}, cMax);
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float max = vector.Max();
			Assert::AreEqual(float{5}, max);
			constexpr auto cVector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float cMax = cVector.Max();
			Assert::AreEqual(float{5}, cMax);
		}

		TEST_METHOD(MinMaxShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
			constexpr auto cVector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
		}

		TEST_METHOD(MinMaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
			constexpr auto cVector = PonyMath::Core::Vector4<float>(x, y, z, w);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
		}

		TEST_METHOD(SumThisShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::int16_t sum = vector.Sum();
			Assert::AreEqual(std::int16_t{2}, sum);
		}

		TEST_METHOD(SumThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float sum = vector.Sum();
			Assert::AreEqual(2.f, sum);
		}

		TEST_METHOD(SwapShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const PonyMath::Core::Vector4<std::int16_t> swapped = vector.Swapped();
			Assert::AreEqual(w, swapped.X());
			Assert::AreEqual(z, swapped.Y());
			Assert::AreEqual(y, swapped.Z());
			Assert::AreEqual(x, swapped.W());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(SwapFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const PonyMath::Core::Vector4<float> swapped = vector.Swapped();
			Assert::AreEqual(w, swapped.X());
			Assert::AreEqual(z, swapped.Y());
			Assert::AreEqual(y, swapped.Z());
			Assert::AreEqual(x, swapped.W());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Vector4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Vector4<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyMath::Core::Vector4<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyMath::Core::Vector4<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsUnitShortTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>(1, 0, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>(0, 1, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>(0, 0, 1, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>(0, 0, 0, 1).IsUnit());
		}

		TEST_METHOD(IsUnitFloatTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector4<float>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyMath::Core::Vector4<float>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(1, 0, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 1, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 0, 1, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 0, 0, 1).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.Normalized().IsUnit());
		}

		TEST_METHOD(IsAlmostUnitTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector4<float>::Predefined::Zero.IsAlmostUnit());
			Assert::IsFalse(PonyMath::Core::Vector4<float>::Predefined::One.IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(1, 0, 0, 0).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 1, 0, 0).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 0, 1, 0).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(0, 0, 0, 1).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.Normalized().IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.IsAlmostUnit(5.f));
		}

		TEST_METHOD(IsUniformShortTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>(1, 0, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>(0, 1, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>(0, 0, 1, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<std::int16_t>(0, 0, 0, 1).IsUniform());
		}

		TEST_METHOD(IsUniformFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(1, 0, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 1, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 0, 1, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 0, 0, 1).IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.Normalized().IsUniform());
		}

		TEST_METHOD(IsAlmostUniformyTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Zero.IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(1, 0, 0, 0).IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 1, 0, 0).IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 0, 1, 0).IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<float>(0, 0, 0, 1).IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One.Normalized().IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<float>(1, 0, 0, 0).IsAlmostUniform(5.f));
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const float nan = std::numeric_limits<float>::quiet_NaN();
			Assert::IsTrue(vector.IsFinite());
			vector.X() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.X() = x;
			vector.Y() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.Y() = y;
			vector.Z() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.Z() = z;
			vector.W() = nan;
			Assert::IsFalse(vector.IsFinite());
		}

		TEST_METHOD(MultiplyThisShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			constexpr std::int16_t xS = 4;
			constexpr std::int16_t yS = 7;
			constexpr std::int16_t zS = -1;
			constexpr std::int16_t wS = -5;
			constexpr auto scale = PonyMath::Core::Vector4<std::int16_t>(xS, yS, zS, wS);
			vector.Multiply(scale);
			Assert::AreEqual(std::int16_t{x * xS}, vector.X());
			Assert::AreEqual(std::int16_t{y * yS}, vector.Y());
			Assert::AreEqual(std::int16_t{z * zS}, vector.Z());
			Assert::AreEqual(std::int16_t{w * wS}, vector.W());
		}

		TEST_METHOD(MultiplyThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr float zS = -1;
			constexpr float wS = -5;
			constexpr auto scale = PonyMath::Core::Vector4<float>(xS, yS, zS, wS);
			vector.Multiply(scale);
			Assert::AreEqual(x * xS, vector.X());
			Assert::AreEqual(y * yS, vector.Y());
			Assert::AreEqual(z * zS, vector.Z());
			Assert::AreEqual(w * wS, vector.W());
		}

		TEST_METHOD(DivideThisShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			constexpr std::int16_t xS = 4;
			constexpr std::int16_t yS = 7;
			constexpr std::int16_t zS = -1;
			constexpr std::int16_t wS = -5;
			constexpr auto scale = PonyMath::Core::Vector4<std::int16_t>(xS, yS, zS, wS);
			vector.Divide(scale);
			Assert::AreEqual(std::int16_t{ x / xS }, vector.X());
			Assert::AreEqual(std::int16_t{ y / yS }, vector.Y());
			Assert::AreEqual(std::int16_t{ z / zS }, vector.Z());
			Assert::AreEqual(std::int16_t{ w / wS }, vector.W());
		}

		TEST_METHOD(DivideThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr float zS = -1;
			constexpr float wS = -5;
			constexpr auto scale = PonyMath::Core::Vector4<float>(xS, yS, zS, wS);
			vector.Divide(scale);
			Assert::AreEqual(x / xS, vector.X(), 0.0001f);
			Assert::AreEqual(y / yS, vector.Y(), 0.0001f);
			Assert::AreEqual(z / zS, vector.Z(), 0.0001f);
			Assert::AreEqual(w / wS, vector.W(), 0.0001f);
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const std::string expectedString = std::format("({}, {}, {}, {})", x, y, z, w);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToStringFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const std::string expectedString = std::format("({}, {}, {}, {})", x, y, z, w);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatVector = PonyMath::Core::Vector4<float>(3.1f, -2.2f, 4.4f, -2.1f);
			const auto intVector = static_cast<PonyMath::Core::Vector4<std::int32_t>>(floatVector);
			Assert::AreEqual(3, intVector.X());
			Assert::AreEqual(-2, intVector.Y());
			Assert::AreEqual(4, intVector.Z());
			Assert::AreEqual(-2, intVector.W());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);
			Assert::AreEqual(w, vector[3]);

			constexpr  auto vectorC = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
			Assert::AreEqual(w, vectorC[3]);
		}

		TEST_METHOD(AccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);
			Assert::AreEqual(w, vector[3]);

			constexpr  auto vectorC = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
			Assert::AreEqual(w, vectorC[3]);
		}

		TEST_METHOD(CopyAssignmentShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<std::int16_t>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(CopyAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<float>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(MoveAssignmentShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -2;
			auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<std::int16_t>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(MoveAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<float>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
			Assert::AreEqual(w, copiedVector.W());
		}

		TEST_METHOD(SumAssignmentShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xC = 6;
			constexpr std::int16_t yC = 4;
			constexpr std::int16_t zC = -2;
			constexpr std::int16_t wC = -5;
			auto vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL = vectorC += vectorR;
			Assert::AreEqual(static_cast<std::int16_t>(xC + xR), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC + yR), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC + zR), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC + wR), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SumAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			constexpr float wC = -5;
			auto vectorC = PonyMath::Core::Vector4<float>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<float>& vectorL = vectorC += vectorR;
			Assert::AreEqual(xC + xR, vectorC.X());
			Assert::AreEqual(yC + yR, vectorC.Y());
			Assert::AreEqual(zC + zR, vectorC.Z());
			Assert::AreEqual(wC + wR, vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xC = 6;
			constexpr std::int16_t yC = 4;
			constexpr std::int16_t zC = -2;
			constexpr std::int16_t wC = -5;
			auto vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(static_cast<std::int16_t>(xC - xR), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC - yR), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC - zR), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC - wR), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			constexpr float wC = -5;
			auto vectorC = PonyMath::Core::Vector4<float>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<float>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(xC - xR, vectorC.X());
			Assert::AreEqual(yC - yR, vectorC.Y());
			Assert::AreEqual(zC - zR, vectorC.Z());
			Assert::AreEqual(wC - wR, vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(MultiplyAssignmentShortTest)
		{
			constexpr std::int16_t multiplierI = 4;
			constexpr std::int16_t xC = 6;
			constexpr std::int16_t yC = 4;
			constexpr std::int16_t zC = -2;
			constexpr std::int16_t wC = -5;
			auto vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC * multiplierI), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC * multiplierI), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL1 = vectorC *= multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(xC * multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC * multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC * multiplierF), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC * multiplierF), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(MultiplyAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			constexpr float wC = -5;
			auto vectorC = PonyMath::Core::Vector4<float>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<float>& vectorL = vectorC *= multiplier;
			Assert::AreEqual(xC * multiplier, vectorC.X());
			Assert::AreEqual(yC * multiplier, vectorC.Y());
			Assert::AreEqual(zC * multiplier, vectorC.Z());
			Assert::AreEqual(wC * multiplier, vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(DivideAssignmentShortTest)
		{
			constexpr std::int16_t multiplierI = 4;
			constexpr std::int16_t xC = 6;
			constexpr std::int16_t yC = 4;
			constexpr std::int16_t zC = -2;
			constexpr std::int16_t wC = -5;
			auto vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC / multiplierI), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC / multiplierI), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector4<std::int16_t>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<std::int16_t>& vectorL1 = vectorC /= multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(xC / multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<std::int16_t>(yC / multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zC / multiplierF), vectorC.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wC / multiplierF), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(DivideAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			constexpr float wC = -5;
			auto vectorC = PonyMath::Core::Vector4<float>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<float>& vectorL = vectorC /= multiplier;
			Assert::AreEqual(xC / multiplier, vectorC.X());
			Assert::AreEqual(yC / multiplier, vectorC.Y());
			Assert::AreEqual(zC / multiplier, vectorC.Z());
			Assert::AreEqual(wC / multiplier, vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(EqualityShortTest)
		{
			constexpr std::int16_t x = 2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = 5;
			constexpr std::int16_t w = -5;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			PonyMath::Core::Vector4<std::int16_t> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<std::int16_t>::ComponentCount; ++i)
			{
				otherVector.Span()[i] += 1;
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Span()[i] = vector.Span()[i];
			}
		}

		TEST_METHOD(EqualityFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -5;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			PonyMath::Core::Vector4<float> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				otherVector.Span()[i] = std::nextafter(otherVector.Span()[i], 0.f);
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Span()[i] += 1;
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Span()[i] = vector.Span()[i];
			}
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::One == PonyMath::Core::Vector4<float>(1, 1, 1, 1));
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Zero == PonyMath::Core::Vector4<float>(0, 0, 0, 0));
			Assert::IsTrue(PonyMath::Core::Vector4<float>::Predefined::Negative == PonyMath::Core::Vector4<float>(-1, -1, -1, -1));

			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::One == PonyMath::Core::Vector4<std::int16_t>(1, 1, 1, 1));
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::Zero == PonyMath::Core::Vector4<std::int16_t>(0, 0, 0, 0));
			Assert::IsTrue(PonyMath::Core::Vector4<std::int16_t>::Predefined::Negative == PonyMath::Core::Vector4<std::int16_t>(-1, -1, -1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			std::int16_t xR = 2;
			std::int16_t yR = -3;
			std::int16_t zR = 5;
			std::int16_t wR = -2;
			auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			std::int16_t xL = 6;
			std::int16_t yL = 4;
			std::int16_t zL = -3;
			std::int16_t wL = -5;
			auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			std::int16_t dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(std::int16_t{-5}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			xL = 6;
			yL = 4;
			zL = 3;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(std::int16_t{49}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			xL = 3;
			yL = -2;
			zL = -2;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(std::int16_t{0}, dot);
		}

		TEST_METHOD(DotFloatTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			float wR = -2;
			auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			float xL = 6;
			float yL = 4;
			float zL = -3;
			float wL = -5;
			auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			float dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(-5.f, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			xL = 6;
			yL = 4;
			zL = 3;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(49.f, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			xL = 3;
			yL = -2;
			zL = -2;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(0.f, dot);
		}

		TEST_METHOD(DistanceShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -3;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			Assert::AreEqual(11.747f, PonyMath::Core::Distance(vectorL, vectorR), 0.001f);
			Assert::AreEqual(std::int16_t{138}, PonyMath::Core::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(DistanceFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -3;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			Assert::AreEqual(11.747f, PonyMath::Core::Distance(vectorL, vectorR), 0.001f);
			Assert::AreEqual(138.f, PonyMath::Core::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(AngleTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			float wR = -2;
			auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -3;
			float wL = -5;
			auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL).Normalized();
			float angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(1.654f, angle, 0.001f);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			xL = 6;
			yL = 4;
			zL = 3;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL).Normalized();
			angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(0.618f, angle, 0.001f);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			xL = 3;
			yL = -2;
			zL = -2;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL).Normalized();
			angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(std::numbers::pi_v<float> / 2.f, angle, 0.001f);

			angle = PonyMath::Core::Angle(vectorL, vectorL);
			Assert::AreEqual(0.f, angle, 0.001f);

			angle = PonyMath::Core::Angle(vectorL, -vectorL);
			Assert::AreEqual(std::numbers::pi_v<float>, angle, 0.001f);
		}

		TEST_METHOD(ProjectTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			float wR = -2;
			auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -3;
			float wL = -5;
			auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			PonyMath::Core::Vector4<float> projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(-0.238f, projected.X(), 0.001f);
			Assert::AreEqual(0.357f, projected.Y(), 0.001f);
			Assert::AreEqual(-0.595f, projected.Z(), 0.001f);
			Assert::AreEqual(0.238f, projected.W(), 0.001f);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			xL = 6;
			yL = 4;
			zL = 3;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(2.333f, projected.X(), 0.001f);
			Assert::AreEqual(3.5f, projected.Y(), 0.001f);
			Assert::AreEqual(5.833f, projected.Z(), 0.001f);
			Assert::AreEqual(2.333f, projected.W(), 0.001f);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR).Normalized();
			xL = 3;
			yL = -2;
			zL = -2;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(0.f, projected.X(), 0.001f);
			Assert::AreEqual(0.f, projected.Y(), 0.001f);
			Assert::AreEqual(0.f, projected.Z(), 0.001f);
			Assert::AreEqual(0.f, projected.W(), 0.001f);

			projected = PonyMath::Core::Project(vectorL, vectorL.Normalized());
			Assert::AreEqual(3.f, projected.X(), 0.001f);
			Assert::AreEqual(-2.f, projected.Y(), 0.001f);
			Assert::AreEqual(-2.f, projected.Z(), 0.001f);
			Assert::AreEqual(5.f, projected.W(), 0.001f);
		}

		TEST_METHOD(MultiplyVectorShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			const PonyMath::Core::Vector4<std::int16_t> scaled = PonyMath::Core::Multiply(vectorL, vectorR);
			Assert::AreEqual(static_cast<std::int16_t>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL * yR), scaled.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL * zR), scaled.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL * wR), scaled.W());
		}

		TEST_METHOD(MultiplyVectorFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			const PonyMath::Core::Vector4<float> scaled = PonyMath::Core::Multiply(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
			Assert::AreEqual(zL * zR, scaled.Z());
			Assert::AreEqual(wL * wR, scaled.W());
		}

		TEST_METHOD(DivideVectorShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);
			const PonyMath::Core::Vector4<std::int16_t> scaled = PonyMath::Core::Divide(vectorL, vectorR);
			Assert::AreEqual(static_cast<std::int16_t>(xL / xR), scaled.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL / yR), scaled.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL / zR), scaled.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL / wR), scaled.W());
		}

		TEST_METHOD(DivideVectorFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);
			const PonyMath::Core::Vector4<float> scaled = PonyMath::Core::Divide(vectorL, vectorR);
			Assert::AreEqual(xL / xR, scaled.X(), 0.0001f);
			Assert::AreEqual(yL / yR, scaled.Y(), 0.0001f);
			Assert::AreEqual(zL / zR, scaled.Z(), 0.0001f);
			Assert::AreEqual(wL / wR, scaled.W(), 0.0001f);
		}

		TEST_METHOD(AbsShortTest)
		{
			constexpr std::int16_t x = -2;
			constexpr std::int16_t y = -3;
			constexpr std::int16_t z = -5;
			constexpr std::int16_t w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			const PonyMath::Core::Vector4<std::int16_t> abs = PonyMath::Core::Abs(vector);
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(x)), abs.X());
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(y)), abs.Y());
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(z)), abs.Z());
			Assert::AreEqual(static_cast<std::int16_t>(std::abs(w)), abs.W());
		}

		TEST_METHOD(AbsFloatTest)
		{
			constexpr float x = -2;
			constexpr float y = -3;
			constexpr float z = -5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			const PonyMath::Core::Vector4<float> abs = PonyMath::Core::Abs(vector);
			Assert::AreEqual(std::abs(x), abs.X());
			Assert::AreEqual(std::abs(y), abs.Y());
			Assert::AreEqual(std::abs(z), abs.Z());
			Assert::AreEqual(std::abs(w), abs.W());
		}

		TEST_METHOD(MinCombinedShortTest)
		{
			constexpr std::int16_t x = 8;
			constexpr std::int16_t y = 12;
			constexpr std::int16_t z = 1;
			constexpr std::int16_t w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			constexpr std::int16_t x1 = 10;
			constexpr std::int16_t y1 = 6;
			constexpr std::int16_t z1 = 1;
			constexpr std::int16_t w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<std::int16_t>(x1, y1, z1, w1);
			auto min = PonyMath::Core::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
			Assert::AreEqual(z, min.Z());
			Assert::AreEqual(w, min.W());
		}

		TEST_METHOD(MinCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr float z1 = 1;
			constexpr float w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<float>(x1, y1, z1, w1);
			auto min = PonyMath::Core::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
			Assert::AreEqual(z, min.Z());
			Assert::AreEqual(w, min.W());
		}

		TEST_METHOD(MaxCombinedShortTest)
		{
			constexpr std::int16_t x = 8;
			constexpr std::int16_t y = 12;
			constexpr std::int16_t z = 1;
			constexpr std::int16_t w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			constexpr std::int16_t x1 = 10;
			constexpr std::int16_t y1 = 6;
			constexpr std::int16_t z1 = 1;
			constexpr std::int16_t w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<std::int16_t>(x1, y1, z1, w1);
			auto min = PonyMath::Core::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
			Assert::AreEqual(z, min.Z());
			Assert::AreEqual(w1, min.W());
		}

		TEST_METHOD(MaxCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr float z = 1;
			constexpr float w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr float z1 = 1;
			constexpr float w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<float>(x1, y1, z1, w1);
			auto min = PonyMath::Core::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
			Assert::AreEqual(z, min.Z());
			Assert::AreEqual(w1, min.W());
		}

		TEST_METHOD(ClampShortTest)
		{
			constexpr std::int16_t x = 8;
			constexpr std::int16_t y = 2;
			constexpr std::int16_t z = 1;
			constexpr std::int16_t w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<std::int16_t>(x, y, z, w);
			constexpr std::int16_t x1 = 10;
			constexpr std::int16_t y1 = 6;
			constexpr std::int16_t z1 = 1;
			constexpr std::int16_t w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<std::int16_t>(x1, y1, z1, w1);
			constexpr std::int16_t x2 = 9;
			constexpr std::int16_t y2 = 8;
			constexpr std::int16_t z2 = 5;
			constexpr std::int16_t w2 = 1;
			constexpr auto vector2 = PonyMath::Core::Vector4<std::int16_t>(x2, y2, z2, w2);

			auto clamped = PonyMath::Core::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
			Assert::AreEqual(z, clamped.Z());
			Assert::AreEqual(w, clamped.W());
		}

		TEST_METHOD(ClampFloatTest)
		{
			constexpr float x = 0.8;
			constexpr float y = 0.2;
			constexpr float z = 0.1;
			constexpr float w = 0.2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float x1 = 0.9;
			constexpr float y1 = 0.6;
			constexpr float z1 = 0.1;
			constexpr float w1 = 0.4;
			constexpr auto vector1 = PonyMath::Core::Vector4<float>(x1, y1, z1, w1);
			constexpr float x2 = 0.85;
			constexpr float y2 = 0.8;
			constexpr float z2 = 0.5;
			constexpr float w2 = 0.1;
			constexpr auto vector2 = PonyMath::Core::Vector4<float>(x2, y2, z2, w2);

			auto clamped = PonyMath::Core::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
			Assert::AreEqual(z, clamped.Z());
			Assert::AreEqual(w, clamped.W());
		}

		TEST_METHOD(ClampMagnitudeTest)
		{
			constexpr float x = 0.8;
			constexpr float y = 0.2;
			constexpr float z = 0.1;
			constexpr float w = 0.2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			auto clamped = PonyMath::Core::ClampMagnitude(vector, 40.f);
			Assert::IsTrue(vector == clamped);

			clamped = PonyMath::Core::ClampMagnitude(vector, 0.5f);
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vector.Normalized() * 0.5f, clamped));
		}

		TEST_METHOD(LerpShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<std::int16_t> lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());
			Assert::AreEqual(wL, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());
			Assert::AreEqual(wR, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(std::int16_t{4}, lerped.X());
			Assert::AreEqual(std::int16_t{1}, lerped.Y());
			Assert::AreEqual(std::int16_t{1}, lerped.Z());
			Assert::AreEqual(std::int16_t{-4}, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(std::int16_t{-2}, lerped.X());
			Assert::AreEqual(std::int16_t{-10}, lerped.Y());
			Assert::AreEqual(std::int16_t{12}, lerped.Z());
			Assert::AreEqual(std::int16_t{1}, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(std::int16_t{10}, lerped.X());
			Assert::AreEqual(std::int16_t{11}, lerped.Y());
			Assert::AreEqual(std::int16_t{-9}, lerped.Z());
			Assert::AreEqual(std::int16_t{-8}, lerped.W());
		}

		TEST_METHOD(LerpFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<float> lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());
			Assert::AreEqual(wL, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());
			Assert::AreEqual(wR, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(4.f, lerped.X());
			Assert::AreEqual(0.5f, lerped.Y());
			Assert::AreEqual(1.5f, lerped.Z());
			Assert::AreEqual(-3.5f, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(-2.f, lerped.X());
			Assert::AreEqual(-10.f, lerped.Y());
			Assert::AreEqual(12.f, lerped.Z());
			Assert::AreEqual(1.f, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(10.f, lerped.X());
			Assert::AreEqual(11.f, lerped.Y());
			Assert::AreEqual(-9.f, lerped.Z());
			Assert::AreEqual(-8.f, lerped.W());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			PonyMath::Core::Vector4<float> vectorL = vectorR;

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] = std::nextafter(vectorL.Span()[i], 0.f);
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] += 1;
				Assert::IsFalse(PonyMath::Core::AreAlmostEqual(vectorL, vectorR));
				Assert::IsTrue(PonyMath::Core::AreAlmostEqual(vectorL, vectorR, 5.f));
				vectorL.Span()[i] = vectorR.Span()[i];
			}
		}

		TEST_METHOD(SumShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<std::int16_t> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<std::int16_t>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL + yR), sum.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL + zR), sum.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL + wR), sum.W());
		}

		TEST_METHOD(SumFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<float> sum = vectorL + vectorR;
			Assert::AreEqual(xL + xR, sum.X());
			Assert::AreEqual(yL + yR, sum.Y());
			Assert::AreEqual(zL + zR, sum.Z());
			Assert::AreEqual(wL + wR, sum.W());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);

			const PonyMath::Core::Vector4<std::int16_t> negated = -vectorR;
			Assert::AreEqual(static_cast<std::int16_t>(-xR), negated.X());
			Assert::AreEqual(static_cast<std::int16_t>(-yR), negated.Y());
			Assert::AreEqual(static_cast<std::int16_t>(-zR), negated.Z());
			Assert::AreEqual(static_cast<std::int16_t>(-wR), negated.W());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);

			const PonyMath::Core::Vector4<float> negated = -vectorR;
			Assert::AreEqual(-xR, negated.X());
			Assert::AreEqual(-yR, negated.Y());
			Assert::AreEqual(-zR, negated.Z());
			Assert::AreEqual(-wR, negated.W());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr std::int16_t xR = 2;
			constexpr std::int16_t yR = -3;
			constexpr std::int16_t zR = 5;
			constexpr std::int16_t wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<std::int16_t>(xR, yR, zR, wR);
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<std::int16_t> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<std::int16_t>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL - yR), difference.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL - zR), difference.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL - wR), difference.W());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr float wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<float>(xR, yR, zR, wR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<float> difference = vectorL - vectorR;
			Assert::AreEqual(xL - xR, difference.X());
			Assert::AreEqual(yL - yR, difference.Y());
			Assert::AreEqual(zL - zR, difference.Z());
			Assert::AreEqual(wL - wR, difference.W());
		}

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr std::int16_t multiplierI = 3;
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<std::int16_t> product = vectorL * multiplierI;
			Assert::AreEqual(static_cast<std::int16_t>(xL * multiplierI), product.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL * multiplierI), product.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL * multiplierI), product.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL * multiplierI), product.W());
			Assert::IsTrue(multiplierI * vectorL == vectorL * multiplierI);

			constexpr float multiplierF = 4;
			product = vectorL * multiplierF;
			Assert::AreEqual(static_cast<std::int16_t>(xL * multiplierF), product.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL * multiplierF), product.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL * multiplierF), product.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL * multiplierF), product.W());
			Assert::IsTrue(multiplierF * vectorL == vectorL * multiplierF);
		}

		TEST_METHOD(MultiplyFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<float> product = vectorL * multiplier;
			Assert::AreEqual(xL * multiplier, product.X());
			Assert::AreEqual(yL * multiplier, product.Y());
			Assert::AreEqual(zL * multiplier, product.Z());
			Assert::AreEqual(wL * multiplier, product.W());
			Assert::IsTrue(multiplier * vectorL == vectorL * multiplier);
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr std::int16_t divisorI = 3;
			constexpr std::int16_t xL = 6;
			constexpr std::int16_t yL = 4;
			constexpr std::int16_t zL = -2;
			constexpr std::int16_t wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<std::int16_t>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<std::int16_t> product = vectorL / divisorI;
			Assert::AreEqual(static_cast<std::int16_t>(xL / divisorI), product.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL / divisorI), product.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL / divisorI), product.Z());

			constexpr float divisorF = 4;
			product = vectorL / divisorF;
			Assert::AreEqual(static_cast<std::int16_t>(xL / divisorF), product.X());
			Assert::AreEqual(static_cast<std::int16_t>(yL / divisorF), product.Y());
			Assert::AreEqual(static_cast<std::int16_t>(zL / divisorF), product.Z());
			Assert::AreEqual(static_cast<std::int16_t>(wL / divisorF), product.W());
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float divisor = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr float wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<float>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<float> product = vectorL / divisor;
			Assert::AreEqual(xL / divisor, product.X(), 0.001f);
			Assert::AreEqual(yL / divisor, product.Y(), 0.001f);
			Assert::AreEqual(zL / divisor, product.Z(), 0.001f);
			Assert::AreEqual(wL / divisor, product.W(), 0.001f);
		}

		static constexpr PonyMath::Core::Vector4<float> VectorConstexpr()
		{
			[[maybe_unused]] auto vector = PonyMath::Core::Vector4<float>(4, 5, 1, 6);
			PonyMath::Core::Vector4<float> movedVector = std::move(vector);

			movedVector.X() += 2;
			movedVector.Y() *= 3;
			movedVector.Z() /= 4;
			movedVector.Span()[1] -= 6;

			[[maybe_unused]] constexpr auto constVector = PonyMath::Core::Vector4<float>(4, 5, 1, 6);

			[[maybe_unused]] const float min = movedVector.Min();
			[[maybe_unused]] const float max = movedVector.Max();
			[[maybe_unused]] const auto minMax = movedVector.MinMax();

			movedVector.Swap();

			movedVector.Multiply(constVector);
			movedVector.Divide(constVector);

			movedVector[1] -= 4;

			movedVector += PonyMath::Core::Vector4<float>(4, 5, 1, 6);
			movedVector -= PonyMath::Core::Vector4<float>(4, 5, 1, 6);
			movedVector *= 4.f;
			movedVector /= 4.f;
			movedVector *= 3;
			movedVector /= 5;

			[[maybe_unused]] auto movedVector1 = PonyMath::Core::Vector4<float>();
			movedVector1 = constVector;
			movedVector1 = std::move(movedVector);

			return movedVector1;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto one = PonyMath::Core::Vector4<float>::Predefined::One;
			[[maybe_unused]] constexpr auto zero = PonyMath::Core::Vector4<float>::Predefined::Zero;
			[[maybe_unused]] constexpr auto negative = PonyMath::Core::Vector4<float>::Predefined::Negative;

			[[maybe_unused]] constexpr auto defaultVector = PonyMath::Core::Vector4<float>();
			[[maybe_unused]] constexpr auto vector = PonyMath::Core::Vector4<float>(4, 5, 1, 6);
			[[maybe_unused]] constexpr auto arrayVector = PonyMath::Core::Vector4<float>(std::array<float, 4>{4, 5, 1, 6});
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> copiedVector = vector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> movedVector = VectorConstexpr();

			[[maybe_unused]] constexpr float x = vector.X();
			[[maybe_unused]] constexpr float y = vector.Y();
			[[maybe_unused]] constexpr float z = vector.Z();
			[[maybe_unused]] constexpr float w = vector.W();

			[[maybe_unused]] constexpr auto spanElement = vector.Span()[0];

			[[maybe_unused]] constexpr float magnitudeSquared = vector.MagnitudeSquared();
			[[maybe_unused]] constexpr float min = vector.Min();
			[[maybe_unused]] constexpr float max = vector.Max();
			[[maybe_unused]] constexpr std::pair<float, float> minMax = vector.MinMax();
			[[maybe_unused]] constexpr float thisSum = vector.Sum();
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> swapped = vector.Swapped();

			[[maybe_unused]] constexpr bool isZero = vector.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = vector.IsAlmostZero();
			[[maybe_unused]] constexpr bool isUnit = vector.IsUnit();
			[[maybe_unused]] constexpr bool isUniform = vector.IsUniform();

			[[maybe_unused]] constexpr auto intVector = static_cast<PonyMath::Core::Vector4<std::int32_t>>(vector);

			[[maybe_unused]] constexpr float value = vector[0];

			[[maybe_unused]] constexpr bool equal = arrayVector == vector;
			[[maybe_unused]] constexpr bool notEqual = arrayVector != vector;

			[[maybe_unused]] constexpr float dot = PonyMath::Core::Dot(vector, arrayVector);
			[[maybe_unused]] constexpr float distance = PonyMath::Core::DistanceSquared(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> project = PonyMath::Core::Project(vector, PonyMath::Core::Vector4<float>(1, 0, 0, 0));

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> scale = PonyMath::Core::Multiply(vector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> scaleD = PonyMath::Core::Divide(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> minCombined = PonyMath::Core::Min(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> maxCombined = PonyMath::Core::Max(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> clamped = PonyMath::Core::Clamp(vector, defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> lerp = PonyMath::Core::Lerp(vector, arrayVector, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Core::AreAlmostEqual(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> sum = vector + arrayVector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> difference = vector - arrayVector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> product = vector * 3.f;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> productL = 3.f * vector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> quotient = vector / 2.f;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> productI = PonyMath::Core::Vector4<std::int32_t>(4, 5, 1, 6) * 3;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<std::int32_t> productIL = 3 * PonyMath::Core::Vector4<std::int32_t>(4, 5, 1, 6);
		}
	};
}
