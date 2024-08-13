/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <array>;
import <cmath>;
import <format>;
import <numbers>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Vector3Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector3<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector3<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector3<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector3<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector3<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector3<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Vector3<float>::ComponentCount);
			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Vector3<short>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyEngine::Math::Vector3<short>();
			Assert::AreEqual(short{}, vector.X());
			Assert::AreEqual(short{}, vector.Y());
			Assert::AreEqual(short{}, vector.Z());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto vector = PonyEngine::Math::Vector3<float>();
			Assert::AreEqual(float{}, vector.X());
			Assert::AreEqual(float{}, vector.Y());
			Assert::AreEqual(float{}, vector.Z());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			const auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			const auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			const auto vector = PonyEngine::Math::Vector3<short>(std::array<short, 3>{x, y, z});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			const auto vector = PonyEngine::Math::Vector3<float>(std::array<float, 3>{x, y, z});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const PonyEngine::Math::Vector3<short> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const PonyEngine::Math::Vector3<float> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const PonyEngine::Math::Vector3<short> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const PonyEngine::Math::Vector3<float> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
			Assert::AreEqual(z, copiedVector.Z());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());

			constexpr auto vectorC = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());

			constexpr auto vectorC = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
			Assert::AreEqual(z, vectorC.Z());
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);

			constexpr auto vectorC = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
		}

		TEST_METHOD(SpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);
			Assert::AreEqual(z, vector.Span()[2]);

			constexpr auto vectorC = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
			Assert::AreEqual(z, vectorC.Span()[2]);
		}

		TEST_METHOD(MagnitudeShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5; 
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(6.164, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<short>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(6.164, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<float>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(short{38}, vector.MagnitudeSquared());

			Assert::AreEqual(short{0}, PonyEngine::Math::Vector3<short>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(MagnitudeSquaredFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(38.f, vector.MagnitudeSquared());

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<float>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(NormalizeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const PonyEngine::Math::Vector3<float> normalized = vector.Normalized();
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
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const short min = vector.Min();
			Assert::AreEqual(short{-3}, min);
			constexpr auto cVector = PonyEngine::Math::Vector3<short>(x, y, z);
			const short cMin = cVector.Min();
			Assert::AreEqual(short{-3}, cMin);
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const float min = vector.Min();
			Assert::AreEqual(-3.f, min);
			constexpr auto cVector = PonyEngine::Math::Vector3<float>(x, y, z);
			const float cMin = cVector.Min();
			Assert::AreEqual(-3.f, cMin);
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const short max = vector.Max();
			Assert::AreEqual(short{5}, max);
			constexpr auto cVector = PonyEngine::Math::Vector3<short>(x, y, z);
			const short cMax = cVector.Max();
			Assert::AreEqual(short{5}, cMax);
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const float max = vector.Max();
			Assert::AreEqual(float{5}, max);
			constexpr auto cVector = PonyEngine::Math::Vector3<float>(x, y, z);
			const float cMax = cVector.Max();
			Assert::AreEqual(float{5}, cMax);
		}

		TEST_METHOD(SumThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const short sum = vector.Sum();
			Assert::AreEqual(short{4}, sum);
		}

		TEST_METHOD(SumThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const float sum = vector.Sum();
			Assert::AreEqual(4.f, sum);
		}

		TEST_METHOD(SwapShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			const PonyEngine::Math::Vector3<short> swapped = vector.Swapped();
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
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const PonyEngine::Math::Vector3<float> swapped = vector.Swapped();
			Assert::AreEqual(z, swapped.X());
			Assert::AreEqual(y, swapped.Y());
			Assert::AreEqual(x, swapped.Z());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Zero.IsZero());

			auto matrix = PonyEngine::Math::Vector3<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyEngine::Math::Vector3<short>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsZero());

			auto matrix = PonyEngine::Math::Vector3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyEngine::Math::Vector3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyEngine::Math::Vector3<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyEngine::Math::Vector3<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsUnitShortTest)
		{
			Assert::IsFalse(PonyEngine::Math::Vector3<short>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyEngine::Math::Vector3<short>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<short>(1, 0, 0).IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<short>(0, 1, 0).IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<short>(0, 0, 1).IsUnit());
		}

		TEST_METHOD(IsUnitFloatTest)
		{
			Assert::IsFalse(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(1, 0, 0).IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(0, 1, 0).IsUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(0, 0, 1).IsUnit());
		}

		TEST_METHOD(IsAlmostUnitTest)
		{
			Assert::IsFalse(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsAlmostUnit());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>::Predefined::One.IsAlmostUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(1, 0, 0).IsAlmostUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(0, 1, 0).IsAlmostUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(0, 0, 1).IsAlmostUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.Normalized().IsAlmostUnit());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.IsAlmostUnit(5.f));
		}

		TEST_METHOD(IsUniformShortTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<short>(1, 0, 0).IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<short>(0, 1, 0).IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<short>(0, 0, 1).IsUniform());
		}

		TEST_METHOD(IsUniformFloatTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(1, 0, 0).IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(0, 1, 0).IsUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(0, 0, 1).IsUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.Normalized().IsUniform());
		}

		TEST_METHOD(IsAlmostUniformyTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Zero.IsAlmostUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.IsAlmostUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(1, 0, 0).IsAlmostUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(0, 1, 0).IsAlmostUniform());
			Assert::IsFalse(PonyEngine::Math::Vector3<float>(0, 0, 1).IsAlmostUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One.Normalized().IsAlmostUniform());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>(1, 0, 0).IsAlmostUniform(5.f));
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
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
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
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
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
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
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
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
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
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
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			constexpr short xS = 4;
			constexpr short yS = 7;
			constexpr short zS = -1;
			constexpr auto scale = PonyEngine::Math::Vector3<short>(xS, yS, zS);
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
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr float zS = -1;
			constexpr auto scale = PonyEngine::Math::Vector3<float>(xS, yS, zS);
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
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
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
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			const std::string expectedString = std::format("({}, {}, {})", x, y, z);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatVector = PonyEngine::Math::Vector3<float>(3.1f, -2.2f, 4.4f);
			const auto intVector = static_cast<PonyEngine::Math::Vector3<int>>(floatVector);
			Assert::AreEqual(3, intVector.X());
			Assert::AreEqual(-2, intVector.Y());
			Assert::AreEqual(4, intVector.Z());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);

			constexpr  auto vectorC = PonyEngine::Math::Vector3<short>(x, y, z);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
		}

		TEST_METHOD(AccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr float z = 5;
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);

			constexpr  auto vectorC = PonyEngine::Math::Vector3<float>(x, y, z);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
			Assert::AreEqual(z, vectorC[2]);
		}

		TEST_METHOD(CopyAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr short z = 5;
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			auto copiedVector = PonyEngine::Math::Vector3<short>();
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
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto copiedVector = PonyEngine::Math::Vector3<float>();
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
			auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			auto copiedVector = PonyEngine::Math::Vector3<short>();
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
			auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			auto copiedVector = PonyEngine::Math::Vector3<float>();
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
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL = vectorC += vectorR;
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
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyEngine::Math::Vector3<float>(xC, yC, zC);
			PonyEngine::Math::Vector3<float>& vectorL = vectorC += vectorR;
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
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			constexpr short zC = -2;
			auto vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL = vectorC -= vectorR;
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
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			constexpr float zC = -2;
			auto vectorC = PonyEngine::Math::Vector3<float>(xC, yC, zC);
			PonyEngine::Math::Vector3<float>& vectorL = vectorC -= vectorR;
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
			auto vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<short>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC * multiplierI), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL1 = vectorC *= multiplierF;
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
			auto vectorC = PonyEngine::Math::Vector3<float>(xC, yC, zC);
			PonyEngine::Math::Vector3<float>& vectorL = vectorC *= multiplier;
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
			auto vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<short>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(static_cast<short>(zC / multiplierI), vectorC.Z());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyEngine::Math::Vector3<short>(xC, yC, zC);
			PonyEngine::Math::Vector3<short>& vectorL1 = vectorC /= multiplierF;
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
			auto vectorC = PonyEngine::Math::Vector3<float>(xC, yC, zC);
			PonyEngine::Math::Vector3<float>& vectorL = vectorC /= multiplier;
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
			constexpr auto vector = PonyEngine::Math::Vector3<short>(x, y, z);
			PonyEngine::Math::Vector3<short> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<short>::ComponentCount; ++i)
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
			constexpr auto vector = PonyEngine::Math::Vector3<float>(x, y, z);
			PonyEngine::Math::Vector3<float> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<float>::ComponentCount; ++i)
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
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Forward == PonyEngine::Math::Vector3<float>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Back == PonyEngine::Math::Vector3<float>(0, 0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Up == PonyEngine::Math::Vector3<float>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Down == PonyEngine::Math::Vector3<float>(0, -1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Right == PonyEngine::Math::Vector3<float>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Left == PonyEngine::Math::Vector3<float>(-1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::One == PonyEngine::Math::Vector3<float>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Zero == PonyEngine::Math::Vector3<float>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Predefined::Negative == PonyEngine::Math::Vector3<float>(-1, -1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Forward == PonyEngine::Math::Vector3<short>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Back == PonyEngine::Math::Vector3<short>(0, 0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Up == PonyEngine::Math::Vector3<short>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Down == PonyEngine::Math::Vector3<short>(0, -1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Right == PonyEngine::Math::Vector3<short>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Left == PonyEngine::Math::Vector3<short>(-1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::One == PonyEngine::Math::Vector3<short>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Zero == PonyEngine::Math::Vector3<short>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Predefined::Negative == PonyEngine::Math::Vector3<short>(-1, -1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			short xR = 2;
			short yR = -3;
			short zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			short xL = 6;
			short yL = 4;
			short zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);
			short dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{-10}, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);
			dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{34}, dot);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);
			dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{0}, dot);
		}

		TEST_METHOD(DotFloatTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			float dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(-10.f, dot);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(34.f, dot);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(0.f, dot);
		}

		TEST_METHOD(CrossShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);
			PonyEngine::Math::Vector3<short> cross = PonyEngine::Math::Cross(vectorL, vectorR);
			Assert::AreEqual(short{14}, cross.X());
			Assert::AreEqual(short{-34}, cross.Y());
			Assert::AreEqual(short{-26}, cross.Z());

			cross = PonyEngine::Math::Cross(vectorR, vectorL);
			Assert::AreEqual(short{-14}, cross.X());
			Assert::AreEqual(short{34}, cross.Y());
			Assert::AreEqual(short{26}, cross.Z());

			cross = PonyEngine::Math::Cross(vectorL, vectorL);
			Assert::AreEqual(short{0}, cross.X());
			Assert::AreEqual(short{0}, cross.Y());
			Assert::AreEqual(short{0}, cross.Z());

			cross = PonyEngine::Math::Cross(vectorL, -vectorL);
			Assert::AreEqual(short{0}, cross.X());
			Assert::AreEqual(short{0}, cross.Y());
			Assert::AreEqual(short{0}, cross.Z());
		}

		TEST_METHOD(CrossFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			PonyEngine::Math::Vector3<float> cross = PonyEngine::Math::Cross(vectorL, vectorR);
			Assert::AreEqual(14.f, cross.X());
			Assert::AreEqual(-34.f, cross.Y());
			Assert::AreEqual(-26.f, cross.Z());

			cross = PonyEngine::Math::Cross(vectorR, vectorL);
			Assert::AreEqual(-14.f, cross.X());
			Assert::AreEqual(34.f, cross.Y());
			Assert::AreEqual(26.f, cross.Z());

			cross = PonyEngine::Math::Cross(vectorL, vectorL);
			Assert::AreEqual(0.f, cross.X());
			Assert::AreEqual(0.f, cross.Y());
			Assert::AreEqual(0.f, cross.Z());

			cross = PonyEngine::Math::Cross(vectorL, -vectorL);
			Assert::AreEqual(0.f, cross.X());
			Assert::AreEqual(0.f, cross.Y());
			Assert::AreEqual(0.f, cross.Z());
		}

		TEST_METHOD(AngleTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL).Normalized();
			float angle = PonyEngine::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL).Normalized();
			angle = PonyEngine::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(0.742, static_cast<double>(angle), 0.001);

			angle = PonyEngine::Math::Angle(vectorL, vectorL);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			angle = PonyEngine::Math::Angle(vectorL, -vectorL);
			Assert::AreEqual(std::numbers::pi_v<double>, std::abs(static_cast<double>(angle)), 0.001);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			angle = PonyEngine::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., std::abs(static_cast<double>(angle)), 0.001);
		}

		TEST_METHOD(AngleSignedTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL).Normalized();
			float angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Up);
			Assert::AreEqual(-1.789, static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorR, vectorL, PonyEngine::Math::Vector3<float>::Predefined::Up);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Down);
			Assert::AreEqual(1.789, static_cast<double>(angle), 0.001);

			xR = 2;
			yR = 3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = 4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL).Normalized();
			angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Right);
			Assert::AreEqual(0.742, static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorR, vectorL, PonyEngine::Math::Vector3<float>::Predefined::Right);
			Assert::AreEqual(-0.742, static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Left);
			Assert::AreEqual(-0.742, static_cast<double>(angle), 0.001);

			angle = PonyEngine::Math::AngleSigned(vectorL, vectorL, PonyEngine::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(0., static_cast<double>(angle), 0.001);

			angle = PonyEngine::Math::AngleSigned(vectorL, -vectorL, PonyEngine::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(std::numbers::pi_v<double>, std::abs(static_cast<double>(angle)), 0.001);

			xR = 2;
			yR = 3;
			zR = 12;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			xL = 6;
			yL = 4;
			zL = -2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorR, vectorL, PonyEngine::Math::Vector3<float>::Predefined::Forward);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorL, vectorR, PonyEngine::Math::Vector3<float>::Predefined::Back);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(ProjectTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			PonyEngine::Math::Vector3<float> projected = PonyEngine::Math::Project(vectorL, vectorR);
			Assert::AreEqual(-0.526, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0.789, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-1.316, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::Project(vectorL, vectorR);
			Assert::AreEqual(1.789, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2.684, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(4.474, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::Project(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(10., static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::Project(vectorL, vectorR);
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Z()), 0.001);
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			PonyEngine::Math::Vector3<float> projected = PonyEngine::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(6.526, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.211, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-0.684, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4.211, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-1.316, static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-2.474, static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			projected = PonyEngine::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(projected.Y()), 0.001);
			Assert::AreEqual(-13., static_cast<double>(projected.Z()), 0.001);
		}

		TEST_METHOD(ReflectTest)
		{
			float xR = 2;
			float yR = -3;
			float zR = 5;
			auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			float xL = 6;
			float yL = 4;
			float zL = -2;
			auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			PonyEngine::Math::Vector3<float> reflected = PonyEngine::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(7.053, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(2.421, static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(0.632, static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 6;
			yL = -4;
			zL = 2;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyEngine::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(2.421, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(1.368, static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-6.947, static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 5;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = 10;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyEngine::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(-4., static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(6., static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-10., static_cast<double>(reflected.Z()), 0.001);

			xR = 2;
			yR = -3;
			zR = 2;
			vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR).Normalized();
			xL = 4;
			yL = -6;
			zL = -13;
			vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			reflected = PonyEngine::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(4., static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(reflected.Y()), 0.001);
			Assert::AreEqual(-13., static_cast<double>(reflected.Z()), 0.001);
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);
			const PonyEngine::Math::Vector3<short> scaled = PonyEngine::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(static_cast<short>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<short>(yL * yR), scaled.Y());
			Assert::AreEqual(static_cast<short>(zL * zR), scaled.Z());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);
			const PonyEngine::Math::Vector3<float> scaled = PonyEngine::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
			Assert::AreEqual(zL * zR, scaled.Z());
		}

		TEST_METHOD(LerpShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);

			PonyEngine::Math::Vector3<short> lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(short{4}, lerped.X());
			Assert::AreEqual(short{1}, lerped.Y());
			Assert::AreEqual(short{1}, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(short{-2}, lerped.X());
			Assert::AreEqual(short{-10}, lerped.Y());
			Assert::AreEqual(short{12}, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(short{10}, lerped.X());
			Assert::AreEqual(short{11}, lerped.Y());
			Assert::AreEqual(short{-9}, lerped.Z());
		}

		TEST_METHOD(LerpFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);

			PonyEngine::Math::Vector3<float> lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());
			Assert::AreEqual(zL, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());
			Assert::AreEqual(zR, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(4.f, lerped.X());
			Assert::AreEqual(0.5f, lerped.Y());
			Assert::AreEqual(1.5f, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(-2.f, lerped.X());
			Assert::AreEqual(-10.f, lerped.Y());
			Assert::AreEqual(12.f, lerped.Z());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(10.f, lerped.X());
			Assert::AreEqual(11.f, lerped.Y());
			Assert::AreEqual(-9.f, lerped.Z());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			PonyEngine::Math::Vector3<float> vectorL = vectorR;

			for (std::size_t i = 0; i < PonyEngine::Math::Vector3<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] = std::nextafter(vectorL.Span()[i], 0.f);
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Span()[i] += 1;
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR, 5.f));
				vectorL.Span()[i] = vectorR.Span()[i];
			}
		}

		TEST_METHOD(SumShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);

			const PonyEngine::Math::Vector3<short> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<short>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<short>(yL + yR), sum.Y());
			Assert::AreEqual(static_cast<short>(zL + zR), sum.Z());
		}

		TEST_METHOD(SumFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);

			const PonyEngine::Math::Vector3<float> sum = vectorL + vectorR;
			Assert::AreEqual(xL + xR, sum.X());
			Assert::AreEqual(yL + yR, sum.Y());
			Assert::AreEqual(zL + zR, sum.Z());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);

			const PonyEngine::Math::Vector3<short> negated = -vectorR;
			Assert::AreEqual(static_cast<short>(-xR), negated.X());
			Assert::AreEqual(static_cast<short>(-yR), negated.Y());
			Assert::AreEqual(static_cast<short>(-zR), negated.Z());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);

			const PonyEngine::Math::Vector3<float> negated = -vectorR;
			Assert::AreEqual(-xR, negated.X());
			Assert::AreEqual(-yR, negated.Y());
			Assert::AreEqual(-zR, negated.Z());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr short zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<short>(xR, yR, zR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr short zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);

			const PonyEngine::Math::Vector3<short> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<short>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<short>(yL - yR), difference.Y());
			Assert::AreEqual(static_cast<short>(zL - zR), difference.Z());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr float zR = 5;
			constexpr auto vectorR = PonyEngine::Math::Vector3<float>(xR, yR, zR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr float zL = -2;
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);

			const PonyEngine::Math::Vector3<float> difference = vectorL - vectorR;
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
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);

			PonyEngine::Math::Vector3<short> product = vectorL * multiplierI;
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
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);

			const PonyEngine::Math::Vector3<float> product = vectorL * multiplier;
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
			constexpr auto vectorL = PonyEngine::Math::Vector3<short>(xL, yL, zL);

			PonyEngine::Math::Vector3<short> product = vectorL / divisorI;
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
			constexpr auto vectorL = PonyEngine::Math::Vector3<float>(xL, yL, zL);

			const PonyEngine::Math::Vector3<float> product = vectorL / divisor;
			Assert::AreEqual(xL / divisor, product.X());
			Assert::AreEqual(yL / divisor, product.Y());
			Assert::AreEqual(zL / divisor, product.Z());
		}

		static constexpr PonyEngine::Math::Vector3<float> VectorConstexpr()
		{
			[[maybe_unused]] auto vector = PonyEngine::Math::Vector3<float>(4, 5, 1);
			PonyEngine::Math::Vector3<float> movedVector = std::move(vector);

			movedVector.X() += 2;
			movedVector.Y() *= 3;
			movedVector.Z() /= 4;
			movedVector.Span()[1] -= 6;

			[[maybe_unused]] constexpr auto constVector = PonyEngine::Math::Vector3<float>(4, 5, 1);

			[[maybe_unused]] const float min = movedVector.Min();
			[[maybe_unused]] const float max = movedVector.Max();

			movedVector.Swap();

			movedVector.Set(5, 2, 9);
			movedVector.Set(std::array<float, 3>{7, 9, 8});

			movedVector[1] -= 4;

			movedVector += PonyEngine::Math::Vector3<float>(4, 5, 1);
			movedVector -= PonyEngine::Math::Vector3<float>(4, 5, 1);
			movedVector *= 4.f;
			movedVector /= 4.f;
			movedVector *= 3;
			movedVector /= 5;

			[[maybe_unused]] auto movedVector1 = PonyEngine::Math::Vector3<float>();
			movedVector1 = constVector;
			movedVector1 = std::move(movedVector);

			return movedVector1;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto forward = PonyEngine::Math::Vector3<float>::Predefined::Forward;
			[[maybe_unused]] constexpr auto back = PonyEngine::Math::Vector3<float>::Predefined::Back;
			[[maybe_unused]] constexpr auto up = PonyEngine::Math::Vector3<float>::Predefined::Up;
			[[maybe_unused]] constexpr auto down = PonyEngine::Math::Vector3<float>::Predefined::Down;
			[[maybe_unused]] constexpr auto right = PonyEngine::Math::Vector3<float>::Predefined::Right;
			[[maybe_unused]] constexpr auto left = PonyEngine::Math::Vector3<float>::Predefined::Left;
			[[maybe_unused]] constexpr auto one = PonyEngine::Math::Vector3<float>::Predefined::One;
			[[maybe_unused]] constexpr auto zero = PonyEngine::Math::Vector3<float>::Predefined::Zero;
			[[maybe_unused]] constexpr auto negative = PonyEngine::Math::Vector3<float>::Predefined::Negative;

			[[maybe_unused]] constexpr auto defaultVector = PonyEngine::Math::Vector3<float>();
			[[maybe_unused]] constexpr auto vector = PonyEngine::Math::Vector3<float>(4, 5, 1);
			[[maybe_unused]] constexpr auto arrayVector = PonyEngine::Math::Vector3<float>(std::array<float, 3>{4, 5, 1});
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> copiedVector = vector;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> movedVector = VectorConstexpr();

			[[maybe_unused]] constexpr float x = vector.X();
			[[maybe_unused]] constexpr float y = vector.Y();
			[[maybe_unused]] constexpr float z = vector.Z();

			[[maybe_unused]] constexpr auto span = vector.Span();

			[[maybe_unused]] constexpr float magnitudeSquared = vector.MagnitudeSquared();
			[[maybe_unused]] constexpr float min = vector.Min();
			[[maybe_unused]] constexpr float max = vector.Max();
			[[maybe_unused]] constexpr float thisSum = vector.Sum();
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> swapped = vector.Swapped();

			[[maybe_unused]] constexpr bool isZero = vector.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = vector.IsAlmostZero();
			[[maybe_unused]] constexpr bool isUnit = vector.IsUnit();
			[[maybe_unused]] constexpr bool isUniform = vector.IsUniform();

			[[maybe_unused]] constexpr auto intVector = static_cast<PonyEngine::Math::Vector3<int>>(vector);

			[[maybe_unused]] constexpr float value = vector[0];

			[[maybe_unused]] constexpr bool equal = arrayVector == vector;
			[[maybe_unused]] constexpr bool notEqual = arrayVector != vector;

			[[maybe_unused]] constexpr float dot = PonyEngine::Math::Dot(vector, arrayVector);
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> cross = PonyEngine::Math::Cross(vector, arrayVector);

			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> project = PonyEngine::Math::Project(vector, PonyEngine::Math::Vector3<float>::Predefined::Back);
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, PonyEngine::Math::Vector3<float>::Predefined::Left);

			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> reflect = PonyEngine::Math::Reflect(vector, PonyEngine::Math::Vector3<float>::Predefined::Forward);

			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> scale = PonyEngine::Math::Scale(vector, arrayVector);

			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> lerp = PonyEngine::Math::Lerp(vector, arrayVector, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, arrayVector);

			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> sum = vector + arrayVector;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> difference = vector - arrayVector;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> product = vector * 3.f;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> productL = 3.f * vector;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<float> quotient = vector / 2.f;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<int> productI = PonyEngine::Math::Vector3<int>(4, 5, 1) * 3;
			[[maybe_unused]] constexpr PonyEngine::Math::Vector3<int> productIL = 3 * PonyEngine::Math::Vector3<int>(4, 5, 1);
		}
	};
}
