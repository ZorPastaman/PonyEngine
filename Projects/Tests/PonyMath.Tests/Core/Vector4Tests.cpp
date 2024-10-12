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
#include <format>
#include <numbers>

import PonyMath.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Vector4Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyMath::Core::Vector4<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyMath::Core::Vector4<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyMath::Core::Vector4<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyMath::Core::Vector4<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector4<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Vector4<float>::ComponentCount);
			Assert::AreEqual(std::size_t{4}, PonyMath::Core::Vector4<short>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyMath::Core::Vector4<short>();
			Assert::AreEqual(short{}, vector.X());
			Assert::AreEqual(short{}, vector.Y());
			Assert::AreEqual(short{}, vector.Z());
			Assert::AreEqual(short{}, vector.W());
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			const auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			const auto vector = PonyMath::Core::Vector4<short>(std::array<short, 4>{x, y, z, w});
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const PonyMath::Core::Vector4<short> copiedVector = vector;
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const PonyMath::Core::Vector4<short> copiedVector = std::move(vector);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());

			constexpr auto vectorC = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);
			Assert::AreEqual(w, vector.Span()[3]);

			constexpr auto vectorC = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			Assert::AreEqual(6.481, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::Vector4<short>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			Assert::AreEqual(6.481, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::Vector4<float>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			Assert::AreEqual(short{42}, vector.MagnitudeSquared());

			Assert::AreEqual(short{0}, PonyMath::Core::Vector4<short>::Predefined::Zero.MagnitudeSquared());
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
			Assert::AreEqual(0.309, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.463, static_cast<double>(normalized.Y()), 0.001);
			Assert::AreEqual(0.772, static_cast<double>(normalized.Z()), 0.001);
			Assert::AreEqual(-0.309, static_cast<double>(normalized.W()), 0.001);
			vector.Normalize();
			Assert::IsTrue(vector == normalized);
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const short min = vector.Min();
			Assert::AreEqual(short{-3}, min);
			constexpr auto cVector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const short cMin = cVector.Min();
			Assert::AreEqual(short{-3}, cMin);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const short max = vector.Max();
			Assert::AreEqual(short{5}, max);
			constexpr auto cVector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const short cMax = cVector.Max();
			Assert::AreEqual(short{5}, cMax);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
			constexpr auto cVector = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const short sum = vector.Sum();
			Assert::AreEqual(short{2}, sum);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			const PonyMath::Core::Vector4<short> swapped = vector.Swapped();
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
			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Vector4<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Vector4<short>::Predefined::Zero.Span()[i];
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
			Assert::IsFalse(PonyMath::Core::Vector4<short>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyMath::Core::Vector4<short>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<short>(1, 0, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<short>(0, 1, 0, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<short>(0, 0, 1, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector4<short>(0, 0, 0, 1).IsUnit());
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
			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<short>(1, 0, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<short>(0, 1, 0, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<short>(0, 0, 1, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector4<short>(0, 0, 0, 1).IsUniform());
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

		TEST_METHOD(SetShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			constexpr short zNew = -1;
			constexpr short wNew = -5;
			vector.Set(xNew, yNew, zNew, wNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
			Assert::AreEqual(wNew, vector.W());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			constexpr float zNew = -1;
			constexpr float wNew = -5;
			vector.Set(xNew, yNew, zNew, wNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
			Assert::AreEqual(wNew, vector.W());
		}

		TEST_METHOD(SetSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			constexpr short zNew = -1;
			constexpr short wNew = -5;
			vector.Set(std::array<short, 4>{xNew, yNew, zNew, wNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
			Assert::AreEqual(wNew, vector.W());
		}

		TEST_METHOD(SetSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr float w = -2;
			auto vector = PonyMath::Core::Vector4<float>(x, y, z, w);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			constexpr float zNew = -1;
			constexpr float wNew = -5;
			vector.Set(std::array<float, 4>{xNew, yNew, zNew, wNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
			Assert::AreEqual(wNew, vector.W());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short xS = 4;
			constexpr short yS = 7;
			constexpr short zS = -1;
			constexpr short wS = -5;
			constexpr auto scale = PonyMath::Core::Vector4<short>(xS, yS, zS, wS);
			vector.Scale(scale);
			Assert::AreEqual(short{x * xS}, vector.X());
			Assert::AreEqual(short{y * yS}, vector.Y());
			Assert::AreEqual(short{z * zS}, vector.Z());
			Assert::AreEqual(short{w * wS}, vector.W());
		}

		TEST_METHOD(ScaleThisFloatTest)
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
			vector.Scale(scale);
			Assert::AreEqual(x * xS, vector.X());
			Assert::AreEqual(y * yS, vector.Y());
			Assert::AreEqual(z * zS, vector.Z());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			const auto intVector = static_cast<PonyMath::Core::Vector4<int>>(floatVector);
			Assert::AreEqual(3, intVector.X());
			Assert::AreEqual(-2, intVector.Y());
			Assert::AreEqual(4, intVector.Z());
			Assert::AreEqual(-2, intVector.W());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);
			Assert::AreEqual(w, vector[3]);

			constexpr  auto vectorC = PonyMath::Core::Vector4<short>(x, y, z, w);
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<short>();
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -2;
			auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			auto copiedVector = PonyMath::Core::Vector4<short>();
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			constexpr short wC = -5;
			auto vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL = vectorC += vectorR;
			Assert::AreEqual(static_cast<short>(xC + xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC + yR), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC + zR), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC + wR), vectorC.W());
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			constexpr short wC = -5;
			auto vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(static_cast<short>(xC - xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC - yR), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC - zR), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC - wR), vectorC.W());
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
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			constexpr short wC = -5;
			auto vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<short>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC * multiplierI), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC * multiplierI), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL1 = vectorC *= multiplierF;
			Assert::AreEqual(static_cast<short>(xC * multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC * multiplierF), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC * multiplierF), vectorC.W());
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
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			constexpr short wC = -5;
			auto vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<short>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC / multiplierI), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC / multiplierI), vectorC.W());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector4<short>(xC, yC, zC, wC);
			PonyMath::Core::Vector4<short>& vectorL1 = vectorC /= multiplierF;
			Assert::AreEqual(static_cast<short>(xC / multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC / multiplierF), vectorC.Z());
			Assert::AreEqual(static_cast<short>(wC / multiplierF), vectorC.W());
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
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr short w = -5;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			PonyMath::Core::Vector4<short> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyMath::Core::Vector4<short>::ComponentCount; ++i)
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

			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::One == PonyMath::Core::Vector4<short>(1, 1, 1, 1));
			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::Zero == PonyMath::Core::Vector4<short>(0, 0, 0, 0));
			Assert::IsTrue(PonyMath::Core::Vector4<short>::Predefined::Negative == PonyMath::Core::Vector4<short>(-1, -1, -1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			short xR = 2;
			short yR = -3;
			short zR = 5;
			short wR = -2;
			auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			short xL = 6;
			short yL = 4;
			short zL = -3;
			short wL = -5;
			auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);
			short dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{-5}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			xL = 6;
			yL = 4;
			zL = 3;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{49}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			wR = 2;
			vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			xL = 3;
			yL = -2;
			zL = -2;
			wL = 5;
			vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{0}, dot);
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -3;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);
			Assert::AreEqual(11.747, static_cast<double>(PonyMath::Core::Distance(vectorL, vectorR)), 0.001);
			Assert::AreEqual(short{138}, PonyMath::Core::DistanceSquared(vectorR, vectorL));
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
			Assert::AreEqual(11.747, static_cast<double>(PonyMath::Core::Distance(vectorL, vectorR)), 0.001);
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
			Assert::AreEqual(1.654, static_cast<double>(angle), 0.001);

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
			Assert::AreEqual(0.618, static_cast<double>(angle), 0.001);

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
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);

			angle = PonyMath::Core::Angle(vectorL, vectorL);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			angle = PonyMath::Core::Angle(vectorL, -vectorL);
			Assert::AreEqual(std::numbers::pi_v<double>, static_cast<double>(angle), 0.001);
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
			Assert::AreEqual(-0.238, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0.357, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-0.595, static_cast<double>(projected.Z()), 0.001);
			Assert::AreEqual(0.238, static_cast<double>(projected.W()), 0.001);

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
			Assert::AreEqual(2.333, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.5, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(5.833, static_cast<double>(projected.Z()), 0.001);
			Assert::AreEqual(2.333, static_cast<double>(projected.W()), 0.001);

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
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.W()), 0.001);

			projected = PonyMath::Core::Project(vectorL, vectorL.Normalized());
			Assert::AreEqual(3., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-2., static_cast<double>(projected.Z()), 0.001);
			Assert::AreEqual(5., static_cast<double>(projected.W()), 0.001);
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);
			const PonyMath::Core::Vector4<short> scaled = PonyMath::Core::Scale(vectorL, vectorR);
			Assert::AreEqual(static_cast<short>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<short>(yL * yR), scaled.Y());
			Assert::AreEqual(static_cast<short>(zL * zR), scaled.Z());
			Assert::AreEqual(static_cast<short>(wL * wR), scaled.W());
		}

		TEST_METHOD(ScaleFloatTest)
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
			const PonyMath::Core::Vector4<float> scaled = PonyMath::Core::Scale(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
			Assert::AreEqual(zL * zR, scaled.Z());
			Assert::AreEqual(wL * wR, scaled.W());
		}

		TEST_METHOD(MinCombinedShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr short z = 1;
			constexpr short w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr short w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<short>(x1, y1, z1, w1);
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
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr short z = 1;
			constexpr short w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr short w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<short>(x1, y1, z1, w1);
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
			constexpr short x = 8;
			constexpr short y = 2;
			constexpr short z = 1;
			constexpr short w = 2;
			constexpr auto vector = PonyMath::Core::Vector4<short>(x, y, z, w);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr short w1 = 4;
			constexpr auto vector1 = PonyMath::Core::Vector4<short>(x1, y1, z1, w1);
			constexpr short x2 = 9;
			constexpr short y2 = 8;
			constexpr short z2 = 5;
			constexpr short w2 = 1;
			constexpr auto vector2 = PonyMath::Core::Vector4<short>(x2, y2, z2, w2);

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

		TEST_METHOD(LerpShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<short> lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.f);
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
			Assert::AreEqual(short{4}, lerped.X());
			Assert::AreEqual(short{1}, lerped.Y());
			Assert::AreEqual(short{1}, lerped.Z());
			Assert::AreEqual(short{-4}, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(short{-2}, lerped.X());
			Assert::AreEqual(short{-10}, lerped.Y());
			Assert::AreEqual(short{12}, lerped.Z());
			Assert::AreEqual(short{1}, lerped.W());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(short{10}, lerped.X());
			Assert::AreEqual(short{11}, lerped.Y());
			Assert::AreEqual(short{-9}, lerped.Z());
			Assert::AreEqual(short{-8}, lerped.W());
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<short> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<short>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<short>(yL + yR), sum.Y());
			Assert::AreEqual(static_cast<short>(zL + zR), sum.Z());
			Assert::AreEqual(static_cast<short>(wL + wR), sum.W());
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);

			const PonyMath::Core::Vector4<short> negated = -vectorR;
			Assert::AreEqual(static_cast<short>(-xR), negated.X());
			Assert::AreEqual(static_cast<short>(-yR), negated.Y());
			Assert::AreEqual(static_cast<short>(-zR), negated.Z());
			Assert::AreEqual(static_cast<short>(-wR), negated.W());
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
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr short wR = -2;
			constexpr auto vectorR = PonyMath::Core::Vector4<short>(xR, yR, zR, wR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);

			const PonyMath::Core::Vector4<short> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<short>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<short>(yL - yR), difference.Y());
			Assert::AreEqual(static_cast<short>(zL - zR), difference.Z());
			Assert::AreEqual(static_cast<short>(wL - wR), difference.W());
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
			constexpr short multiplierI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<short> product = vectorL * multiplierI;
			Assert::AreEqual(static_cast<short>(xL * multiplierI), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierI), product.Y());
			Assert::AreEqual(static_cast<short>(zL * multiplierI), product.Z());
			Assert::AreEqual(static_cast<short>(wL * multiplierI), product.W());
			Assert::IsTrue(multiplierI * vectorL == vectorL * multiplierI);

			constexpr float multiplierF = 4;
			product = vectorL * multiplierF;
			Assert::AreEqual(static_cast<short>(xL * multiplierF), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierF), product.Y());
			Assert::AreEqual(static_cast<short>(zL * multiplierF), product.Z());
			Assert::AreEqual(static_cast<short>(wL * multiplierF), product.W());
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
			constexpr short divisorI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr short wL = -5;
			constexpr auto vectorL = PonyMath::Core::Vector4<short>(xL, yL, zL, wL);

			PonyMath::Core::Vector4<short> product = vectorL / divisorI;
			Assert::AreEqual(static_cast<short>(xL / divisorI), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorI), product.Y());
			Assert::AreEqual(static_cast<short>(zL / divisorI), product.Z());

			constexpr float divisorF = 4;
			product = vectorL / divisorF;
			Assert::AreEqual(static_cast<short>(xL / divisorF), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorF), product.Y());
			Assert::AreEqual(static_cast<short>(zL / divisorF), product.Z());
			Assert::AreEqual(static_cast<short>(wL / divisorF), product.W());
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
			Assert::AreEqual(static_cast<double>(xL / divisor), static_cast<double>(product.X()), 0.001);
			Assert::AreEqual(static_cast<double>(yL / divisor), static_cast<double>(product.Y()), 0.001);
			Assert::AreEqual(static_cast<double>(zL / divisor), static_cast<double>(product.Z()), 0.001);
			Assert::AreEqual(static_cast<double>(wL / divisor), static_cast<double>(product.W()), 0.001);
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

			movedVector.Set(5, 2, 9, 6);
			movedVector.Set(std::array<float, 4>{7, 9, 8, 1});

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

			[[maybe_unused]] constexpr auto intVector = static_cast<PonyMath::Core::Vector4<int>>(vector);

			[[maybe_unused]] constexpr float value = vector[0];

			[[maybe_unused]] constexpr bool equal = arrayVector == vector;
			[[maybe_unused]] constexpr bool notEqual = arrayVector != vector;

			[[maybe_unused]] constexpr float dot = PonyMath::Core::Dot(vector, arrayVector);
			[[maybe_unused]] constexpr float distance = PonyMath::Core::DistanceSquared(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> project = PonyMath::Core::Project(vector, PonyMath::Core::Vector4<float>(1, 0, 0, 0));

			[[maybe_unused]] constexpr PonyMath::Core::Vector4<float> scale = PonyMath::Core::Scale(vector, arrayVector);

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
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<int> productI = PonyMath::Core::Vector4<int>(4, 5, 1, 6) * 3;
			[[maybe_unused]] constexpr PonyMath::Core::Vector4<int> productIL = 3 * PonyMath::Core::Vector4<int>(4, 5, 1, 6);
		}
	};
}
