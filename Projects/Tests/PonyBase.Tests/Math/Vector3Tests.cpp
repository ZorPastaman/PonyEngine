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

import PonyBase.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Vector3Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyBase::Math::Vector3<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Vector3<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyBase::Math::Vector3<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Vector3<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyBase::Math::Vector3<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Vector3<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Vector3<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyBase::Math::Vector3<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyBase::Math::Vector3<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Vector3<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Vector3<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyBase::Math::Vector3<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyBase::Math::Vector3<float>::ComponentCount);
			Assert::AreEqual(std::size_t{3}, PonyBase::Math::Vector3<short>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyBase::Math::Vector3<short>();
			Assert::AreEqual(short{}, vector.X());
			Assert::AreEqual(short{}, vector.Y());
			Assert::AreEqual(short{}, vector.Z());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto vector = PonyBase::Math::Vector3<float>();
			Assert::AreEqual(float{}, vector.X());
			Assert::AreEqual(float{}, vector.Y());
			Assert::AreEqual(float{}, vector.Z());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			const auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			const auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			const auto vector = PonyBase::Math::Vector3<short>(std::array<short, 3>{x, y, z});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			const auto vector = PonyBase::Math::Vector3<float>(std::array<float, 3>{x, y, z});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const PonyBase::Math::Vector3<short> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const PonyBase::Math::Vector3<float> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const PonyBase::Math::Vector3<short> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const PonyBase::Math::Vector3<float> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());

			constexpr auto vectorC = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());

			constexpr auto vectorC = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);

			constexpr auto vectorC = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
		}

		TEST_METHOD(SpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);

			constexpr auto vectorC = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
		}

		TEST_METHOD(MagnitudeShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5; 
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(6.164, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyBase::Math::Vector3<short>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(6.164, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyBase::Math::Vector3<float>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(short{38}, vector.MagnitudeSquared());

			Assert::AreEqual(short{0}, PonyBase::Math::Vector3<short>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(MagnitudeSquaredFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(38.f, vector.MagnitudeSquared());

			Assert::AreEqual(0.f, PonyBase::Math::Vector3<float>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(NormalizeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const PonyBase::Math::Vector3<float> normalized = vector.Normalized();
			Assert::AreEqual(0.324, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.487, static_cast<double>(normalized.Y()), 0.001);
			Assert::AreEqual(0.811, static_cast<double>(normalized.Z()), 0.001);
			vector.Normalize();
			Assert::IsTrue(vector == normalized);
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const short min = vector.Min();
			Assert::AreEqual(short{-3}, min);
			constexpr auto cVector = PonyBase::Math::Vector3<short>(x, y, z);
			const short cMin = cVector.Min();
			Assert::AreEqual(short{-3}, cMin);
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const float min = vector.Min();
			Assert::AreEqual(-3.f, min);
			constexpr auto cVector = PonyBase::Math::Vector3<float>(x, y, z);
			const float cMin = cVector.Min();
			Assert::AreEqual(-3.f, cMin);
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const short max = vector.Max();
			Assert::AreEqual(short{5}, max);
			constexpr auto cVector = PonyBase::Math::Vector3<short>(x, y, z);
			const short cMax = cVector.Max();
			Assert::AreEqual(short{5}, cMax);
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const float max = vector.Max();
			Assert::AreEqual(float{5}, max);
			constexpr auto cVector = PonyBase::Math::Vector3<float>(x, y, z);
			const float cMax = cVector.Max();
			Assert::AreEqual(float{5}, cMax);
		}

		TEST_METHOD(MinMaxShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
			constexpr auto cVector = PonyBase::Math::Vector3<short>(x, y, z);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
		}

		TEST_METHOD(MinMaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
			constexpr auto cVector = PonyBase::Math::Vector3<float>(x, y, z);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(z, pair.second);
		}

		TEST_METHOD(SumThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const short sum = vector.Sum();
			Assert::AreEqual(short{4}, sum);
		}

		TEST_METHOD(SumThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const float sum = vector.Sum();
			Assert::AreEqual(4.f, sum);
		}

		TEST_METHOD(SwapShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const PonyBase::Math::Vector3<short> swapped = vector.Swapped();
			Assert::AreEqual(z, swapped.X());
			Assert::AreEqual(y, swapped.Y());
			Assert::AreEqual(x, swapped.Z());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(SwapFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const PonyBase::Math::Vector3<float> swapped = vector.Swapped();
			Assert::AreEqual(z, swapped.X());
			Assert::AreEqual(y, swapped.Y());
			Assert::AreEqual(x, swapped.Z());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Zero.IsZero());

			auto matrix = PonyBase::Math::Vector3<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyBase::Math::Vector3<short>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Zero.IsZero());

			auto matrix = PonyBase::Math::Vector3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyBase::Math::Vector3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyBase::Math::Vector3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyBase::Math::Vector3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsUnitShortTest)
		{
			Assert::IsFalse(PonyBase::Math::Vector3<short>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyBase::Math::Vector3<short>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<short>(1, 0, 0).IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<short>(0, 1, 0).IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<short>(0, 0, 1).IsUnit());
		}

		TEST_METHOD(IsUnitFloatTest)
		{
			Assert::IsFalse(PonyBase::Math::Vector3<float>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyBase::Math::Vector3<float>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(1, 0, 0).IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(0, 1, 0).IsUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(0, 0, 1).IsUnit());
		}

		TEST_METHOD(IsAlmostUnitTest)
		{
			Assert::IsFalse(PonyBase::Math::Vector3<float>::Predefined::Zero.IsAlmostUnit());
			Assert::IsFalse(PonyBase::Math::Vector3<float>::Predefined::One.IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(1, 0, 0).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(0, 1, 0).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(0, 0, 1).IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.Normalized().IsAlmostUnit());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.IsAlmostUnit(5.f));
		}

		TEST_METHOD(IsUniformShortTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<short>(1, 0, 0).IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<short>(0, 1, 0).IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<short>(0, 0, 1).IsUniform());
		}

		TEST_METHOD(IsUniformFloatTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(1, 0, 0).IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(0, 1, 0).IsUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(0, 0, 1).IsUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.Normalized().IsUniform());
		}

		TEST_METHOD(IsAlmostUniformyTest)
		{
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Zero.IsAlmostUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.IsAlmostUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(1, 0, 0).IsAlmostUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(0, 1, 0).IsAlmostUniform());
			Assert::IsFalse(PonyBase::Math::Vector3<float>(0, 0, 1).IsAlmostUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One.Normalized().IsAlmostUniform());
			Assert::IsTrue(PonyBase::Math::Vector3<float>(1, 0, 0).IsAlmostUniform(5.f));
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
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
		}

		TEST_METHOD(SetShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			constexpr short zNew = -1;
			vector.Set(xNew, yNew, zNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			constexpr float zNew = -1;
			vector.Set(xNew, yNew, zNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
		}

		TEST_METHOD(SetSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			constexpr short zNew = -1;
			vector.Set(std::array<short, 3>{xNew, yNew, zNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
		}

		TEST_METHOD(SetSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			constexpr float zNew = -1;
			vector.Set(std::array<float, 3>{xNew, yNew, zNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
			Assert::AreEqual(zNew, vector.Z());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short xS = 4;
			constexpr short yS = 7;
			constexpr short zS = -1;
			constexpr auto scale = PonyBase::Math::Vector3<short>(xS, yS, zS);
			vector.Scale(scale);
			Assert::AreEqual(short{x * xS}, vector.X());
			Assert::AreEqual(short{y * yS}, vector.Y());
			Assert::AreEqual(short{z * zS}, vector.Z());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr float zS = -1;
			constexpr auto scale = PonyBase::Math::Vector3<float>(xS, yS, zS);
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
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			const std::string expectedString = std::format("({}, {}, {})", x, y, z);
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
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			const std::string expectedString = std::format("({}, {}, {})", x, y, z);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatVector = PonyBase::Math::Vector3<float>(3.1f, -2.2f, 4.4f);
			const auto intVector = static_cast<PonyBase::Math::Vector3<int>>(floatVector);
			Assert::AreEqual(3, intVector.X());
			Assert::AreEqual(-2, intVector.Y());
			Assert::AreEqual(4, intVector.Z());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);

			constexpr  auto vectorC = PonyBase::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
		}

		TEST_METHOD(AccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);

			constexpr  auto vectorC = PonyBase::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
		}

		TEST_METHOD(CopyAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			auto copiedVector = PonyBase::Math::Vector3<short>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(CopyAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			auto copiedVector = PonyBase::Math::Vector3<float>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(MoveAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			auto copiedVector = PonyBase::Math::Vector3<short>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(MoveAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			auto copiedVector = PonyBase::Math::Vector3<float>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(SumAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL = vectorC += vectorR;
			Assert::AreEqual(static_cast<short>(xC + xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC + yR), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC + zR), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SumAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyBase::Math::Vector3<float>(xC, yC, zC);
			PonyBase::Math::Vector3<float>& vectorL = vectorC += vectorR;
			Assert::AreEqual(xC + xR, vectorC.X());
			Assert::AreEqual(yC + yR, vectorC.Y());
			Assert::AreEqual(zC + zR, vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(static_cast<short>(xC - xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC - yR), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC - zR), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyBase::Math::Vector3<float>(xC, yC, zC);
			PonyBase::Math::Vector3<float>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(xC - xR, vectorC.X());
			Assert::AreEqual(yC - yR, vectorC.Y());
			Assert::AreEqual(zC - zR, vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(MultiplyAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<short>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC * multiplierI), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL1 = vectorC *= multiplierF;
			Assert::AreEqual(static_cast<short>(xC * multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC * multiplierF), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(MultiplyAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyBase::Math::Vector3<float>(xC, yC, zC);
			PonyBase::Math::Vector3<float>& vectorL = vectorC *= multiplier;
			Assert::AreEqual(xC * multiplier, vectorC.X());
			Assert::AreEqual(yC * multiplier, vectorC.Y());
			Assert::AreEqual(zC * multiplier, vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(DivideAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<short>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC / multiplierI), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyBase::Math::Vector3<short>(xC, yC, zC);
			PonyBase::Math::Vector3<short>& vectorL1 = vectorC /= multiplierF;
			Assert::AreEqual(static_cast<short>(xC / multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierF), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC / multiplierF), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(DivideAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyBase::Math::Vector3<float>(xC, yC, zC);
			PonyBase::Math::Vector3<float>& vectorL = vectorC /= multiplier;
			Assert::AreEqual(xC / multiplier, vectorC.X());
			Assert::AreEqual(yC / multiplier, vectorC.Y());
			Assert::AreEqual(zC / multiplier, vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(EqualityShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			PonyBase::Math::Vector3<short> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<short>::ComponentCount; ++i)
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
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			PonyBase::Math::Vector3<float> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<float>::ComponentCount; ++i)
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
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Forward == PonyBase::Math::Vector3<float>(0, 0, 1));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Back == PonyBase::Math::Vector3<float>(0, 0, -1));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Up == PonyBase::Math::Vector3<float>(0, 1, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Down == PonyBase::Math::Vector3<float>(0, -1, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Right == PonyBase::Math::Vector3<float>(1, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Left == PonyBase::Math::Vector3<float>(-1, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::One == PonyBase::Math::Vector3<float>(1, 1, 1));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Zero == PonyBase::Math::Vector3<float>(0, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<float>::Predefined::Negative == PonyBase::Math::Vector3<float>(-1, -1, -1));

			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Forward == PonyBase::Math::Vector3<short>(0, 0, 1));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Back == PonyBase::Math::Vector3<short>(0, 0, -1));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Up == PonyBase::Math::Vector3<short>(0, 1, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Down == PonyBase::Math::Vector3<short>(0, -1, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Right == PonyBase::Math::Vector3<short>(1, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Left == PonyBase::Math::Vector3<short>(-1, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::One == PonyBase::Math::Vector3<short>(1, 1, 1));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Zero == PonyBase::Math::Vector3<short>(0, 0, 0));
			Assert::IsTrue(PonyBase::Math::Vector3<short>::Predefined::Negative == PonyBase::Math::Vector3<short>(-1, -1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			short xR = 2;
			short yR = -3;
			short zR = 5;
			auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			short xL = 6;
			short yL = 4;
			short zL = -2;
			auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			short dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{-10}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{34}, dot);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{0}, dot);
		}

		TEST_METHOD(DotFloatTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			float dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(-10.f, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(34.f, dot);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			dot = PonyBase::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(0.f, dot);
		}

		TEST_METHOD(CrossShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			PonyBase::Math::Vector3<short> cross = PonyBase::Math::Cross(vectorL, vectorR);
			Assert::AreEqual(short{14}, cross.X());
			Assert::AreEqual(short{-34}, cross.Y());
			Assert::AreEqual(short{-26}, cross.Z());

			cross = PonyBase::Math::Cross(vectorR, vectorL);
			Assert::AreEqual(short{-14}, cross.X());
			Assert::AreEqual(short{34}, cross.Y());
			Assert::AreEqual(short{26}, cross.Z());

			cross = PonyBase::Math::Cross(vectorL, vectorL);
			Assert::AreEqual(short{0}, cross.X());
			Assert::AreEqual(short{0}, cross.Y());
			Assert::AreEqual(short{0}, cross.Z());

			cross = PonyBase::Math::Cross(vectorL, -vectorL);
			Assert::AreEqual(short{0}, cross.X());
			Assert::AreEqual(short{0}, cross.Y());
			Assert::AreEqual(short{0}, cross.Z());
		}

		TEST_METHOD(CrossFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			PonyBase::Math::Vector3<float> cross = PonyBase::Math::Cross(vectorL, vectorR);
			Assert::AreEqual(14.f, cross.X());
			Assert::AreEqual(-34.f, cross.Y());
			Assert::AreEqual(-26.f, cross.Z());

			cross = PonyBase::Math::Cross(vectorR, vectorL);
			Assert::AreEqual(-14.f, cross.X());
			Assert::AreEqual(34.f, cross.Y());
			Assert::AreEqual(26.f, cross.Z());

			cross = PonyBase::Math::Cross(vectorL, vectorL);
			Assert::AreEqual(0.f, cross.X());
			Assert::AreEqual(0.f, cross.Y());
			Assert::AreEqual(0.f, cross.Z());

			cross = PonyBase::Math::Cross(vectorL, -vectorL);
			Assert::AreEqual(0.f, cross.X());
			Assert::AreEqual(0.f, cross.Y());
			Assert::AreEqual(0.f, cross.Z());
		}

		TEST_METHOD(DistanceShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -3;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			Assert::AreEqual(11.358, static_cast<double>(PonyBase::Math::Distance(vectorL, vectorR)), 0.001);
			Assert::AreEqual(short{129}, PonyBase::Math::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(DistanceFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -3;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			Assert::AreEqual(11.358, static_cast<double>(PonyBase::Math::Distance(vectorL, vectorR)), 0.001);
			Assert::AreEqual(129.f, PonyBase::Math::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(AngleTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL).Normalized();
			float angle = PonyBase::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL).Normalized();
			angle = PonyBase::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(0.742, static_cast<double>(angle), 0.001);

			angle = PonyBase::Math::Angle(vectorL, vectorL);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			angle = PonyBase::Math::Angle(vectorL, -vectorL);
			Assert::AreEqual(std::numbers::pi_v<double>, std::abs(static_cast<double>(angle)), 0.001);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			angle = PonyBase::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., std::abs(static_cast<double>(angle)), 0.001);
		}

		TEST_METHOD(AngleSignedTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL).Normalized();
			float angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Up);
			Assert::AreEqual(-1.789, static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorR, vectorL, PonyBase::Math::Vector3<float>::Predefined::Up);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Down);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL).Normalized();
			angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Right);
			Assert::AreEqual(0.742, static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorR, vectorL, PonyBase::Math::Vector3<float>::Predefined::Right);
			Assert::AreEqual(-0.742, static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Left);
			Assert::AreEqual(-0.742, static_cast<double>(angle), 0.001);

			angle = PonyBase::Math::AngleSigned(vectorL, vectorL, PonyBase::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			angle = PonyBase::Math::AngleSigned(vectorL, -vectorL, PonyBase::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(std::numbers::pi_v<double>, std::abs(static_cast<double>(angle)), 0.001);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorR, vectorL, PonyBase::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
			angle = PonyBase::Math::AngleSigned(vectorL, vectorR, PonyBase::Math::Vector3<float>::Predefined::Back);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(ProjectTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			PonyBase::Math::Vector3<float> projected = PonyBase::Math::Project(vectorL, vectorR);
			Assert::AreEqual(-0.526, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0.789, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-1.316, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::Project(vectorL, vectorR);
			Assert::AreEqual(1.789, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2.684, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(4.474, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::Project(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(10., static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::Project(vectorL, vectorR);
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Z()), 0.001);
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			PonyBase::Math::Vector3<float> projected = PonyBase::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(6.526, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.211, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-0.684, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4.211, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-1.316, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-2.474, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			projected = PonyBase::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-13., static_cast<double>(projected.Z()), 0.001);
		}

		TEST_METHOD(ReflectTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			PonyBase::Math::Vector3<float> reflected = PonyBase::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(7.053, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(2.421, static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(0.632, static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyBase::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(2.421, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(1.368, static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-6.947, static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyBase::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(-4., static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(6., static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-10., static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyBase::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-13., static_cast<double>(reflected.Z()), 0.001);
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);
			const PonyBase::Math::Vector3<short> scaled = PonyBase::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(static_cast<short>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<short>(yL * yR), scaled.Y());
			Assert::AreEqual(static_cast<short>(zL * zR), scaled.Z());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);
			const PonyBase::Math::Vector3<float> scaled = PonyBase::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
			Assert::AreEqual(zL * zR, scaled.Z());
		}

		TEST_METHOD(MinCombinedShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr short z = 1;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr auto vector1 = PonyBase::Math::Vector3<short>(x1, y1, z1);
			auto min = PonyBase::Math::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
			Assert::AreEqual(z, min.Z());
		}

		TEST_METHOD(MinCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr float z = 1;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr float z1 = 1;
			constexpr auto vector1 = PonyBase::Math::Vector3<float>(x1, y1, z1);
			auto min = PonyBase::Math::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
			Assert::AreEqual(z, min.Z());
		}

		TEST_METHOD(MaxCombinedShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr short z = 1;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr auto vector1 = PonyBase::Math::Vector3<short>(x1, y1, z1);
			auto min = PonyBase::Math::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
			Assert::AreEqual(z, min.Z());
		}

		TEST_METHOD(MaxCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr float z = 1;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr float z1 = 1;
			constexpr auto vector1 = PonyBase::Math::Vector3<float>(x1, y1, z1);
			auto min = PonyBase::Math::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
			Assert::AreEqual(z, min.Z());
		}

		TEST_METHOD(ClampShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 2;
			constexpr short z = 1;
			constexpr auto vector = PonyBase::Math::Vector3<short>(x, y, z);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr short z1 = 1;
			constexpr auto vector1 = PonyBase::Math::Vector3<short>(x1, y1, z1);
			constexpr short x2 = 9;
			constexpr short y2 = 8;
			constexpr short z2 = 5;
			constexpr auto vector2 = PonyBase::Math::Vector3<short>(x2, y2, z2);

			auto clamped = PonyBase::Math::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
			Assert::AreEqual(z, clamped.Z());
		}

		TEST_METHOD(ClampFloatTest)
		{
			constexpr float x = 0.8;
			constexpr float y = 0.2;
			constexpr float z = 0.1;
			constexpr auto vector = PonyBase::Math::Vector3<float>(x, y, z);
			constexpr float x1 = 0.9;
			constexpr float y1 = 0.6;
			constexpr float z1 = 0.1;
			constexpr auto vector1 = PonyBase::Math::Vector3<float>(x1, y1, z1);
			constexpr float x2 = 0.85;
			constexpr float y2 = 0.8;
			constexpr float z2 = 0.5;
			constexpr auto vector2 = PonyBase::Math::Vector3<float>(x2, y2, z2);

			auto clamped = PonyBase::Math::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
			Assert::AreEqual(z, clamped.Z());
		}

		TEST_METHOD(LerpShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);

			PonyBase::Math::Vector3<short> lerped = PonyBase::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(short{4}, lerped.X());
			Assert::AreEqual(short{1}, lerped.Y());
			Assert::AreEqual(short{1}, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(short{-2}, lerped.X());
			Assert::AreEqual(short{-10}, lerped.Y());
			Assert::AreEqual(short{12}, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(short{10}, lerped.X());
			Assert::AreEqual(short{11}, lerped.Y());
			Assert::AreEqual(short{-9}, lerped.Z());
		}

		TEST_METHOD(LerpFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);

			PonyBase::Math::Vector3<float> lerped = PonyBase::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(4.f, lerped.X());
			Assert::AreEqual(0.5f, lerped.Y());
			Assert::AreEqual(1.5f, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(-2.f, lerped.X());
			Assert::AreEqual(-10.f, lerped.Y());
			Assert::AreEqual(12.f, lerped.Z());

			lerped = PonyBase::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(10.f, lerped.X());
			Assert::AreEqual(11.f, lerped.Y());
			Assert::AreEqual(-9.f, lerped.Z());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			PonyBase::Math::Vector3<float> vectorL = vectorR;

			for (std::size_t i = 0; i < PonyBase::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] = std::nextafter(vectorL.Span()[i], 0.f);
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] += 1;
				Assert::IsFalse(PonyBase::Math::AreAlmostEqual(vectorL, vectorR));
				Assert::IsTrue(PonyBase::Math::AreAlmostEqual(vectorL, vectorR, 5.f));
				vectorL.Span()[i] = vectorR.Span()[i];
			}
		}

		TEST_METHOD(SumShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);

			const PonyBase::Math::Vector3<short> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<short>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<short>(yL + yR), sum.Y());
			Assert::AreEqual(static_cast<short>(zL + zR), sum.Z());
		}

		TEST_METHOD(SumFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);

			const PonyBase::Math::Vector3<float> sum = vectorL + vectorR;
			Assert::AreEqual(xL + xR, sum.X());
			Assert::AreEqual(yL + yR, sum.Y());
			Assert::AreEqual(zL + zR, sum.Z());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);

			const PonyBase::Math::Vector3<short> negated = -vectorR;
			Assert::AreEqual(static_cast<short>(-xR), negated.X());
			Assert::AreEqual(static_cast<short>(-yR), negated.Y());
			Assert::AreEqual(static_cast<short>(-zR), negated.Z());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);

			const PonyBase::Math::Vector3<float> negated = -vectorR;
			Assert::AreEqual(-xR, negated.X());
			Assert::AreEqual(-yR, negated.Y());
			Assert::AreEqual(-zR, negated.Z());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);

			const PonyBase::Math::Vector3<short> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<short>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<short>(yL - yR), difference.Y());
			Assert::AreEqual(static_cast<short>(zL - zR), difference.Z());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyBase::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);

			const PonyBase::Math::Vector3<float> difference = vectorL - vectorR;
			Assert::AreEqual(xL - xR, difference.X());
			Assert::AreEqual(yL - yR, difference.Y());
			Assert::AreEqual(zL - zR, difference.Z());
		}

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);

			PonyBase::Math::Vector3<short> product = vectorL * multiplierI;
			Assert::AreEqual(static_cast<short>(xL * multiplierI), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierI), product.Y());
			Assert::AreEqual(static_cast<short>(zL * multiplierI), product.Z());
			Assert::IsTrue(multiplierI * vectorL == vectorL * multiplierI);

			constexpr float multiplierF = 4;
			product = vectorL * multiplierF;
			Assert::AreEqual(static_cast<short>(xL * multiplierF), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierF), product.Y());
			Assert::AreEqual(static_cast<short>(zL * multiplierF), product.Z());
			Assert::IsTrue(multiplierF * vectorL == vectorL * multiplierF);
		}

		TEST_METHOD(MultiplyFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);

			const PonyBase::Math::Vector3<float> product = vectorL * multiplier;
			Assert::AreEqual(xL * multiplier, product.X());
			Assert::AreEqual(yL * multiplier, product.Y());
			Assert::AreEqual(zL * multiplier, product.Z());
			Assert::IsTrue(multiplier * vectorL == vectorL * multiplier);
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short divisorI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<short>(xL, yL, zL);

			PonyBase::Math::Vector3<short> product = vectorL / divisorI;
			Assert::AreEqual(static_cast<short>(xL / divisorI), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorI), product.Y());
			Assert::AreEqual(static_cast<short>(zL / divisorI), product.Z());

			constexpr float divisorF = 4;
			product = vectorL / divisorF;
			Assert::AreEqual(static_cast<short>(xL / divisorF), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorF), product.Y());
			Assert::AreEqual(static_cast<short>(zL / divisorF), product.Z());
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float divisor = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyBase::Math::Vector3<float>(xL, yL, zL);

			const PonyBase::Math::Vector3<float> product = vectorL / divisor;
			Assert::AreEqual(xL / divisor, product.X());
			Assert::AreEqual(yL / divisor, product.Y());
			Assert::AreEqual(zL / divisor, product.Z());
		}

		static constexpr PonyBase::Math::Vector3<float> VectorConstexpr()
		{
			[[maybe_unused]] auto vector = PonyBase::Math::Vector3<float>(4, 5, 1);
			PonyBase::Math::Vector3<float> movedVector = std::move(vector);

			movedVector.X() += 2;
			movedVector.Y() *= 3;
			movedVector.Z() /= 4;
			movedVector.Span()[1] -= 6;

			[[maybe_unused]] constexpr auto constVector = PonyBase::Math::Vector3<float>(4, 5, 1);

			[[maybe_unused]] const float min = movedVector.Min();
			[[maybe_unused]] const float max = movedVector.Max();
			[[maybe_unused]] const auto minMax = movedVector.MinMax();

			movedVector.Swap();

			movedVector.Set(5, 2, 9);
			movedVector.Set(std::array<float, 3>{7, 9, 8});

			movedVector[1] -= 4;

			movedVector += PonyBase::Math::Vector3<float>(4, 5, 1);
			movedVector -= PonyBase::Math::Vector3<float>(4, 5, 1);
			movedVector *= 4.f;
			movedVector /= 4.f;
			movedVector *= 3;
			movedVector /= 5;

			[[maybe_unused]] auto movedVector1 = PonyBase::Math::Vector3<float>();
			movedVector1 = constVector;
			movedVector1 = std::move(movedVector);

			return movedVector1;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto forward = PonyBase::Math::Vector3<float>::Predefined::Forward;
			[[maybe_unused]] constexpr auto back = PonyBase::Math::Vector3<float>::Predefined::Back;
			[[maybe_unused]] constexpr auto up = PonyBase::Math::Vector3<float>::Predefined::Up;
			[[maybe_unused]] constexpr auto down = PonyBase::Math::Vector3<float>::Predefined::Down;
			[[maybe_unused]] constexpr auto right = PonyBase::Math::Vector3<float>::Predefined::Right;
			[[maybe_unused]] constexpr auto left = PonyBase::Math::Vector3<float>::Predefined::Left;
			[[maybe_unused]] constexpr auto one = PonyBase::Math::Vector3<float>::Predefined::One;
			[[maybe_unused]] constexpr auto zero = PonyBase::Math::Vector3<float>::Predefined::Zero;
			[[maybe_unused]] constexpr auto negative = PonyBase::Math::Vector3<float>::Predefined::Negative;

			[[maybe_unused]] constexpr auto defaultVector = PonyBase::Math::Vector3<float>();
			[[maybe_unused]] constexpr auto vector = PonyBase::Math::Vector3<float>(4, 5, 1);
			[[maybe_unused]] constexpr auto arrayVector = PonyBase::Math::Vector3<float>(std::array<float, 3>{4, 5, 1});
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> copiedVector = vector;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> movedVector = VectorConstexpr();

			[[maybe_unused]] constexpr float x = vector.X();
			[[maybe_unused]] constexpr float y = vector.Y();
			[[maybe_unused]] constexpr float z = vector.Z();

			[[maybe_unused]] constexpr auto spanElement = vector.Span()[0];

			[[maybe_unused]] constexpr float magnitudeSquared = vector.MagnitudeSquared();
			[[maybe_unused]] constexpr float min = vector.Min();
			[[maybe_unused]] constexpr float max = vector.Max();
			[[maybe_unused]] constexpr std::pair<float, float> minMax = vector.MinMax();
			[[maybe_unused]] constexpr float thisSum = vector.Sum();
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> swapped = vector.Swapped();

			[[maybe_unused]] constexpr bool isZero = vector.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = vector.IsAlmostZero();
			[[maybe_unused]] constexpr bool isUnit = vector.IsUnit();
			[[maybe_unused]] constexpr bool isUniform = vector.IsUniform();

			[[maybe_unused]] constexpr auto intVector = static_cast<PonyBase::Math::Vector3<int>>(vector);

			[[maybe_unused]] constexpr float value = vector[0];

			[[maybe_unused]] constexpr bool equal = arrayVector == vector;
			[[maybe_unused]] constexpr bool notEqual = arrayVector != vector;

			[[maybe_unused]] constexpr float dot = PonyBase::Math::Dot(vector, arrayVector);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> cross = PonyBase::Math::Cross(vector, arrayVector);
			[[maybe_unused]] constexpr float distance = PonyBase::Math::DistanceSquared(vector, arrayVector);

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> project = PonyBase::Math::Project(vector, PonyBase::Math::Vector3<float>::Predefined::Back);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> projectOnPlane = PonyBase::Math::ProjectOnPlane(vector, PonyBase::Math::Vector3<float>::Predefined::Left);

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> reflect = PonyBase::Math::Reflect(vector, PonyBase::Math::Vector3<float>::Predefined::Forward);

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> scale = PonyBase::Math::Scale(vector, arrayVector);

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> minCombined = PonyBase::Math::Min(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> maxCombined = PonyBase::Math::Max(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> clamped = PonyBase::Math::Clamp(vector, defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> lerp = PonyBase::Math::Lerp(vector, arrayVector, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyBase::Math::AreAlmostEqual(vector, arrayVector);

			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> sum = vector + arrayVector;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> difference = vector - arrayVector;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> product = vector * 3.f;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> productL = 3.f * vector;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<float> quotient = vector / 2.f;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> productI = PonyBase::Math::Vector3<int>(4, 5, 1) * 3;
			[[maybe_unused]] constexpr PonyBase::Math::Vector3<int> productIL = 3 * PonyBase::Math::Vector3<int>(4, 5, 1);
		}
	};
}
