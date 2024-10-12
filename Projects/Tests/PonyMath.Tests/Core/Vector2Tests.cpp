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
	TEST_CLASS(Vector2Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyMath::Core::Vector2<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector2<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyMath::Core::Vector2<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector2<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyMath::Core::Vector2<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector2<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector2<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Core::Vector2<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyMath::Core::Vector2<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector2<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector2<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyMath::Core::Vector2<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{2}, PonyMath::Core::Vector2<float>::ComponentCount);
			Assert::AreEqual(std::size_t{2}, PonyMath::Core::Vector2<short>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyMath::Core::Vector2<short>();
			Assert::AreEqual(short{}, vector.X());
			Assert::AreEqual(short{}, vector.Y());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto vector = PonyMath::Core::Vector2<float>();
			Assert::AreEqual(float{}, vector.X());
			Assert::AreEqual(float{}, vector.Y());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			const auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			const auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			const auto vector = PonyMath::Core::Vector2<short>(std::array<short, 2>{x, y});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			const auto vector = PonyMath::Core::Vector2<float>(std::array<float, 2>{x, y});
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			const PonyMath::Core::Vector2<short> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			const PonyMath::Core::Vector2<float> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			const PonyMath::Core::Vector2<short> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const PonyMath::Core::Vector2<float> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());

			constexpr auto vectorC = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());

			constexpr auto vectorC = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
		}

		TEST_METHOD(SpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);

			constexpr auto vectorC = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
		}

		TEST_METHOD(SpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.Span()[0]);
			Assert::AreEqual(y, vector.Span()[1]);

			constexpr auto vectorC = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC.Span()[0]);
			Assert::AreEqual(y, vectorC.Span()[1]);
		}

		TEST_METHOD(MagnitudeShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(3.606, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::Vector2<short>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(3.606, static_cast<double>(vector.Magnitude()), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::Vector2<float>::Predefined::Zero.Magnitude());
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(short{13}, vector.MagnitudeSquared());

			Assert::AreEqual(short{0}, PonyMath::Core::Vector2<short>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(MagnitudeSquaredFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(13.f, vector.MagnitudeSquared());

			Assert::AreEqual(0.f, PonyMath::Core::Vector2<float>::Predefined::Zero.MagnitudeSquared());
		}

		TEST_METHOD(NormalizeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const PonyMath::Core::Vector2<float> normalized = vector.Normalized();
			Assert::AreEqual(0.555, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.832, static_cast<double>(normalized.Y()), 0.001);
			vector.Normalize();
			Assert::IsTrue(vector == normalized);
		}

		TEST_METHOD(MinShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			const short min = vector.Min();
			Assert::AreEqual(short{-3}, min);
			constexpr auto cVector = PonyMath::Core::Vector2<short>(x, y);
			const short cMin = cVector.Min();
			Assert::AreEqual(short{-3}, cMin);
		}

		TEST_METHOD(MinFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const float min = vector.Min();
			Assert::AreEqual(float{-3}, min);
			constexpr auto cVector = PonyMath::Core::Vector2<float>(x, y);
			const float cMin = cVector.Min();
			Assert::AreEqual(float{-3}, cMin);
		}

		TEST_METHOD(MaxShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			const short max = vector.Max();
			Assert::AreEqual(short{2}, max);
			constexpr auto cVector = PonyMath::Core::Vector2<short>(x, y);
			const short cMax = cVector.Max();
			Assert::AreEqual(short{2}, cMax);
		}

		TEST_METHOD(MaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const float max = vector.Max();
			Assert::AreEqual(float{2}, max);
			constexpr auto cVector = PonyMath::Core::Vector2<float>(x, y);
			const float cMax = cVector.Max();
			Assert::AreEqual(float{2}, cMax);
		}

		TEST_METHOD(MinMaxShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(x, pair.second);
			constexpr auto cVector = PonyMath::Core::Vector2<short>(x, y);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(x, pair.second);
		}

		TEST_METHOD(MinMaxFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			auto pair = vector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(x, pair.second);
			constexpr auto cVector = PonyMath::Core::Vector2<float>(x, y);
			auto cPair = cVector.MinMax();
			Assert::AreEqual(y, pair.first);
			Assert::AreEqual(x, pair.second);
		}

		TEST_METHOD(SumThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			const short sum = vector.Sum();
			Assert::AreEqual(short{-1}, sum);
		}

		TEST_METHOD(SumThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			const float sum = vector.Sum();
			Assert::AreEqual(-1.f, sum);
		}

		TEST_METHOD(SwapShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			const PonyMath::Core::Vector2<short> swapped = vector.Swapped();
			Assert::AreEqual(y, swapped.X());
			Assert::AreEqual(x, swapped.Y());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(SwapFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const PonyMath::Core::Vector2<float> swapped = vector.Swapped();
			Assert::AreEqual(y, swapped.X());
			Assert::AreEqual(x, swapped.Y());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(IsZeroShortTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Vector2<short>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<float>::ComponentCount; ++i)
			{
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Vector2<short>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsZeroFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero.IsZero());

			auto matrix = PonyMath::Core::Vector2<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsZero());
				matrix.Span()[i] = PonyMath::Core::Vector2<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsAlmostZeroTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero.IsAlmostZero());

			auto matrix = PonyMath::Core::Vector2<float>::Predefined::Zero;
			Assert::IsTrue(matrix.IsAlmostZero());

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] = std::nextafter(matrix.Span()[i], 0.5f);
				Assert::IsTrue(matrix.IsAlmostZero());
				matrix.Span()[i] += 1;
				Assert::IsFalse(matrix.IsAlmostZero());
				Assert::IsTrue(matrix.IsAlmostZero(5.f));
				matrix.Span()[i] = PonyMath::Core::Vector2<float>::Predefined::Zero.Span()[i];
			}
		}

		TEST_METHOD(IsUnitShortTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector2<short>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyMath::Core::Vector2<short>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<short>(1, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<short>(0, 1).IsUnit());
		}

		TEST_METHOD(IsUnitFloatTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector2<float>::Predefined::Zero.IsUnit());
			Assert::IsFalse(PonyMath::Core::Vector2<float>::Predefined::One.IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(1, 0).IsUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(0, 1).IsUnit());
		}

		TEST_METHOD(IsAlmostUnitTest)
		{
			Assert::IsFalse(PonyMath::Core::Vector2<float>::Predefined::Zero.IsAlmostUnit());
			Assert::IsFalse(PonyMath::Core::Vector2<float>::Predefined::One.IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(1, 0).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(0, 1).IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.Normalized().IsAlmostUnit());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.IsAlmostUnit(5.f));
		}

		TEST_METHOD(IsUniformShortTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<short>(1, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<short>(0, 1).IsUniform());
		}

		TEST_METHOD(IsUniformFloatTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero.IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<float>(1, 0).IsUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<float>(0, 1).IsUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.Normalized().IsUniform());
		}

		TEST_METHOD(IsAlmostUniformyTest)
		{
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero.IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<float>(1, 0).IsAlmostUniform());
			Assert::IsFalse(PonyMath::Core::Vector2<float>(0, 1).IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One.Normalized().IsAlmostUniform());
			Assert::IsTrue(PonyMath::Core::Vector2<float>(1, 0).IsAlmostUniform(5.f));
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			const float nan = std::numeric_limits<float>::quiet_NaN();
			Assert::IsTrue(vector.IsFinite());
			vector.X() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.X() = x;
			vector.Y() = nan;
			Assert::IsFalse(vector.IsFinite());
		}

		TEST_METHOD(SetShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			vector.Set(xNew, yNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(SetFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			vector.Set(xNew, yNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(SetSpanShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			vector.Set(std::array<short, 2>{xNew, yNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(SetSpanFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			vector.Set(std::array<float, 2>{xNew, yNew});
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short xS = 4;
			constexpr short yS = 7;
			constexpr auto scale = PonyMath::Core::Vector2<short>(xS, yS);
			vector.Scale(scale);
			Assert::AreEqual(short{x * xS}, vector.X());
			Assert::AreEqual(short{y * yS}, vector.Y());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr auto scale = PonyMath::Core::Vector2<float>(xS, yS);
			vector.Scale(scale);
			Assert::AreEqual(x * xS, vector.X());
			Assert::AreEqual(y * yS, vector.Y());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			const std::string expectedString = std::format("({}, {})", x, y);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(ToStringFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			const std::string expectedString = std::format("({}, {})", x, y);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr auto floatVector = PonyMath::Core::Vector2<float>(3.1f, -2.2f);
			const auto intVector = static_cast<PonyMath::Core::Vector2<int>>(floatVector);
			Assert::AreEqual(3, intVector.X());
			Assert::AreEqual(-2, intVector.Y());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);

			constexpr  auto vectorC = PonyMath::Core::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
		}

		TEST_METHOD(AccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);

			constexpr  auto vectorC = PonyMath::Core::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
		}

		TEST_METHOD(CopyAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			auto copiedVector = PonyMath::Core::Vector2<short>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(CopyAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			auto copiedVector = PonyMath::Core::Vector2<float>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(MoveAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyMath::Core::Vector2<short>(x, y);
			auto copiedVector = PonyMath::Core::Vector2<short>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(MoveAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyMath::Core::Vector2<float>(x, y);
			auto copiedVector = PonyMath::Core::Vector2<float>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(SumAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL = vectorC += vectorR;
			Assert::AreEqual(static_cast<short>(xC + xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC + yR), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SumAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyMath::Core::Vector2<float>(xC, yC);
			PonyMath::Core::Vector2<float>& vectorL = vectorC += vectorR;
			Assert::AreEqual(xC + xR, vectorC.X());
			Assert::AreEqual(yC + yR, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(static_cast<short>(xC - xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC - yR), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyMath::Core::Vector2<float>(xC, yC);
			PonyMath::Core::Vector2<float>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(xC - xR, vectorC.X());
			Assert::AreEqual(yC - yR, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(MultiplyAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<short>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL1 = vectorC *= multiplierF;
			Assert::AreEqual(static_cast<short>(xC * multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierF), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(MultiplyAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyMath::Core::Vector2<float>(xC, yC);
			PonyMath::Core::Vector2<float>& vectorL = vectorC *= multiplier;
			Assert::AreEqual(xC * multiplier, vectorC.X());
			Assert::AreEqual(yC * multiplier, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(DivideAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<short>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyMath::Core::Vector2<short>(xC, yC);
			PonyMath::Core::Vector2<short>& vectorL1 = vectorC /= multiplierF;
			Assert::AreEqual(static_cast<short>(xC / multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierF), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(DivideAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyMath::Core::Vector2<float>(xC, yC);
			PonyMath::Core::Vector2<float>& vectorL = vectorC /= multiplier;
			Assert::AreEqual(xC / multiplier, vectorC.X());
			Assert::AreEqual(yC / multiplier, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(EqualityShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			PonyMath::Core::Vector2<short> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<short>::ComponentCount; ++i)
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
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			PonyMath::Core::Vector2<float> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<float>::ComponentCount; ++i)
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
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Up == PonyMath::Core::Vector2<float>(0, 1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Down == PonyMath::Core::Vector2<float>(0, -1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Right == PonyMath::Core::Vector2<float>(1, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Left == PonyMath::Core::Vector2<float>(-1, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::One == PonyMath::Core::Vector2<float>(1, 1));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Zero == PonyMath::Core::Vector2<float>(0, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<float>::Predefined::Negative == PonyMath::Core::Vector2<float>(-1, -1));

			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Up == PonyMath::Core::Vector2<short>(0, 1));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Down == PonyMath::Core::Vector2<short>(0, -1));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Right == PonyMath::Core::Vector2<short>(1, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Left == PonyMath::Core::Vector2<short>(-1, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::One == PonyMath::Core::Vector2<short>(1, 1));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Zero == PonyMath::Core::Vector2<short>(0, 0));
			Assert::IsTrue(PonyMath::Core::Vector2<short>::Predefined::Negative == PonyMath::Core::Vector2<short>(-1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			short xR = 2;
			short yR = -3;
			auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			short xL = 6;
			short yL = 1;
			auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);
			short dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{9}, dot);

			xR = -2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			xL = 6;
			yL = 1;
			vectorL = PonyMath::Core::Vector2<short>(xL, yL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{-15}, dot);

			xR = 1;
			yR = 6;
			vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			xL = 6;
			yL = -1;
			vectorL = PonyMath::Core::Vector2<short>(xL, yL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(short{0}, dot);
		}

		TEST_METHOD(DotFloatTest)
		{
			float xR = 2;
			float yR = -3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			float xL = 6;
			float yL = 1;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			float dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(9.f, dot);

			xR = -2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			xL = 6;
			yL = 1;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(-15.f, dot);

			xR = 1;
			yR = 6;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			xL = 6;
			yL = -1;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			dot = PonyMath::Core::Dot(vectorL, vectorR);
			Assert::AreEqual(0.f, dot);
		}

		TEST_METHOD(DistanceShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);
			Assert::AreEqual(8.062, static_cast<double>(PonyMath::Core::Distance(vectorL, vectorR)), 0.001);
			Assert::AreEqual(short{65}, PonyMath::Core::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(DistanceFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			Assert::AreEqual(8.062, static_cast<double>(PonyMath::Core::Distance(vectorL, vectorR)), 0.001);
			Assert::AreEqual(65.f, PonyMath::Core::DistanceSquared(vectorR, vectorL));
		}

		TEST_METHOD(AngleTest)
		{
			float xR = 2;
			float yR = 3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			float xL = 6;
			float yL = 4;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			float angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(0.395, static_cast<double>(angle), 0.001);

			xR = -3;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 6;
			yL = 4;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(2.944, static_cast<double>(angle), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::Angle(vectorL, vectorL));

			Assert::AreEqual(std::numbers::pi_v<float>, PonyMath::Core::Angle(vectorL, -vectorL));

			xR = 2;
			yR = 3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = -3;
			yL = 2;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			angle = PonyMath::Core::Angle(vectorL, vectorR);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(AngleSignedTest)
		{
			float xR = 2;
			float yR = 3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			float xL = 6;
			float yL = 4;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			float angle = PonyMath::Core::AngleSigned(vectorL, vectorR);
			Assert::AreEqual(0.395, static_cast<double>(angle), 0.001);
			angle = PonyMath::Core::AngleSigned(vectorR, vectorL);
			Assert::AreEqual(-0.395, static_cast<double>(angle), 0.001);

			xR = -3;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 6;
			yL = 4;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			angle = PonyMath::Core::AngleSigned(vectorL, vectorR);
			Assert::AreEqual(-2.944, static_cast<double>(angle), 0.001);
			angle = PonyMath::Core::AngleSigned(vectorR, vectorL);
			Assert::AreEqual(2.944, static_cast<double>(angle), 0.001);

			Assert::AreEqual(0.f, PonyMath::Core::AngleSigned(vectorL, vectorL));

			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyMath::Core::AngleSigned(vectorL, -vectorL)));

			xR = 2;
			yR = 3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = -3;
			yL = 2;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL).Normalized();
			angle = PonyMath::Core::AngleSigned(vectorL, vectorR);
			Assert::AreEqual(-std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);

			angle = PonyMath::Core::AngleSigned(vectorR, vectorL);
			Assert::AreEqual(std::numbers::pi_v<double> / 2., static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(ProjectTest)
		{
			float xR = 2;
			float yR = -3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			float xL = 6;
			float yL = 1;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			PonyMath::Core::Vector2<float> projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(1.385, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2.077, static_cast<double>(projected.Y()), 0.001);

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 3;
			yL = 2;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(0., static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(projected.Y()), 0.001);

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 4;
			yL = -6;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(4.f, projected.X());
			Assert::AreEqual(-6.f, projected.Y());

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = -6;
			yL = 1;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::Project(vectorL, vectorR);
			Assert::AreEqual(-2.308, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.462, static_cast<double>(projected.Y()), 0.001);
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			float xR = 2;
			float yR = -3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			float xL = 6;
			float yL = 1;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			PonyMath::Core::Vector2<float> projected = PonyMath::Core::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4.615, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.077, static_cast<double>(projected.Y()), 0.001);

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 4;
			yL = -6;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(0.f, projected.X());
			Assert::AreEqual(0.f, projected.Y());

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 3;
			yL = 2;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(3.f, projected.X());
			Assert::AreEqual(2.f, projected.Y());

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = -6;
			yL = 1;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			projected = PonyMath::Core::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(-3.692, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2.462, static_cast<double>(projected.Y()), 0.001);
		}

		TEST_METHOD(ReflectTest)
		{
			float xR = 2;
			float yR = -3;
			auto vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			float xL = 6;
			float yL = 1;
			auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			PonyMath::Core::Vector2<float> reflected = PonyMath::Core::Reflect(vectorL, vectorR);
			Assert::AreEqual(3.231, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(5.154, static_cast<double>(reflected.Y()), 0.001);

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 4;
			yL = -6;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			reflected = PonyMath::Core::Reflect(vectorL, vectorR);
			Assert::AreEqual(-4.f, reflected.X());
			Assert::AreEqual(6.f, reflected.Y());

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = 3;
			yL = 2;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			reflected = PonyMath::Core::Reflect(vectorL, vectorR);
			Assert::AreEqual(3., static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(2., static_cast<double>(reflected.Y()), 0.001);

			xR = 2;
			yR = -3;
			vectorR = PonyMath::Core::Vector2<float>(xR, yR).Normalized();
			xL = -6;
			yL = 1;
			vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			reflected = PonyMath::Core::Reflect(vectorL, vectorR);
			Assert::AreEqual(-1.385, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(-5.923, static_cast<double>(reflected.Y()), 0.001);
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);
			const PonyMath::Core::Vector2<short> scaled = PonyMath::Core::Scale(vectorL, vectorR);
			Assert::AreEqual(static_cast<short>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<short>(yL * yR), scaled.Y());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);
			const PonyMath::Core::Vector2<float> scaled = PonyMath::Core::Scale(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
		}

		TEST_METHOD(MinCombinedShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr auto vector1 = PonyMath::Core::Vector2<short>(x1, y1);
			auto min = PonyMath::Core::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
		}

		TEST_METHOD(MinCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr auto vector1 = PonyMath::Core::Vector2<float>(x1, y1);
			auto min = PonyMath::Core::Min(vector, vector1);
			Assert::AreEqual(x, min.X());
			Assert::AreEqual(y1, min.Y());
		}

		TEST_METHOD(MaxCombinedShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 12;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr auto vector1 = PonyMath::Core::Vector2<short>(x1, y1);
			auto min = PonyMath::Core::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
		}

		TEST_METHOD(MaxCombinedFloatTest)
		{
			constexpr float x = 8;
			constexpr float y = 12;
			constexpr auto vector = PonyMath::Core::Vector2<float>(x, y);
			constexpr float x1 = 10;
			constexpr float y1 = 6;
			constexpr auto vector1 = PonyMath::Core::Vector2<float>(x1, y1);
			auto min = PonyMath::Core::Max(vector, vector1);
			Assert::AreEqual(x1, min.X());
			Assert::AreEqual(y, min.Y());
		}

		TEST_METHOD(ClampShortTest)
		{
			constexpr short x = 8;
			constexpr short y = 2;
			constexpr auto vector = PonyMath::Core::Vector2<short>(x, y);
			constexpr short x1 = 10;
			constexpr short y1 = 6;
			constexpr auto vector1 = PonyMath::Core::Vector2<short>(x1, y1);
			constexpr short x2 = 9;
			constexpr short y2 = 8;
			constexpr auto vector2 = PonyMath::Core::Vector2<short>(x2, y2);

			auto clamped = PonyMath::Core::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
		}

		TEST_METHOD(ClampFloatTest)
		{
			constexpr float x = 0.8;
			constexpr float y = 0.2;
			constexpr float z = 0.1;
			constexpr auto vector = PonyMath::Core::Vector3<float>(x, y, z);
			constexpr float x1 = 0.9;
			constexpr float y1 = 0.6;
			constexpr float z1 = 0.1;
			constexpr auto vector1 = PonyMath::Core::Vector3<float>(x1, y1, z1);
			constexpr float x2 = 0.85;
			constexpr float y2 = 0.8;
			constexpr float z2 = 0.5;
			constexpr auto vector2 = PonyMath::Core::Vector3<float>(x2, y2, z2);

			auto clamped = PonyMath::Core::Clamp(vector2, vector, vector1);
			Assert::AreEqual(x2, clamped.X());
			Assert::AreEqual(y1, clamped.Y());
			Assert::AreEqual(z, clamped.Z());
		}

		TEST_METHOD(LerpShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);

			PonyMath::Core::Vector2<short> lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(short{ 4 }, lerped.X());
			Assert::AreEqual(short{ 1 }, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(short{ -2 }, lerped.X());
			Assert::AreEqual(short{ -10 }, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(short{ 10 }, lerped.X());
			Assert::AreEqual(short{ 11 }, lerped.Y());
		}

		TEST_METHOD(LerpFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);

			PonyMath::Core::Vector2<float> lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(4.f, lerped.X());
			Assert::AreEqual(0.5f, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(-2.f, lerped.X());
			Assert::AreEqual(-10.f, lerped.Y());

			lerped = PonyMath::Core::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(10.f, lerped.X());
			Assert::AreEqual(11.f, lerped.Y());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			PonyMath::Core::Vector2<float> vectorL = vectorR;

			for (std::size_t i = 0; i < PonyMath::Core::Vector2<float>::ComponentCount; ++i)
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
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);

			const PonyMath::Core::Vector2<short> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<short>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<short>(yL + yR), sum.Y());
		}

		TEST_METHOD(SumFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);

			const PonyMath::Core::Vector2<float> sum = vectorL + vectorR;
			Assert::AreEqual(xL + xR, sum.X());
			Assert::AreEqual(yL + yR, sum.Y());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);

			const PonyMath::Core::Vector2<short> negated = -vectorR;
			Assert::AreEqual(static_cast<short>(-xR), negated.X());
			Assert::AreEqual(static_cast<short>(-yR), negated.Y());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);

			const PonyMath::Core::Vector2<float> negated = -vectorR;
			Assert::AreEqual(-xR, negated.X());
			Assert::AreEqual(-yR, negated.Y());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);

			const PonyMath::Core::Vector2<short> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<short>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<short>(yL - yR), difference.Y());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyMath::Core::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);

			const PonyMath::Core::Vector2<float> difference = vectorL - vectorR;
			Assert::AreEqual(xL - xR, difference.X());
			Assert::AreEqual(yL - yR, difference.Y());
		}

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);

			PonyMath::Core::Vector2<short> product = vectorL * multiplierI;
			Assert::AreEqual(static_cast<short>(xL * multiplierI), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierI), product.Y());
			Assert::IsTrue(multiplierI * vectorL == vectorL * multiplierI);

			constexpr float multiplierF = 4;
			product = vectorL * multiplierF;
			Assert::AreEqual(static_cast<short>(xL * multiplierF), product.X());
			Assert::AreEqual(static_cast<short>(yL * multiplierF), product.Y());
			Assert::IsTrue(multiplierF * vectorL == vectorL * multiplierF);
		}

		TEST_METHOD(MultiplyFloatTest)
		{
			constexpr float multiplier = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);

			const PonyMath::Core::Vector2<float> product = vectorL * multiplier;
			Assert::AreEqual(xL * multiplier, product.X());
			Assert::AreEqual(yL * multiplier, product.Y());
			Assert::IsTrue(multiplier * vectorL == vectorL * multiplier);
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short divisorI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<short>(xL, yL);

			PonyMath::Core::Vector2<short> product = vectorL / divisorI;
			Assert::AreEqual(static_cast<short>(xL / divisorI), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorI), product.Y());

			constexpr float divisorF = 4;
			product = vectorL / divisorF;
			Assert::AreEqual(static_cast<short>(xL / divisorF), product.X());
			Assert::AreEqual(static_cast<short>(yL / divisorF), product.Y());
		}

		TEST_METHOD(DivideFloatTest)
		{
			constexpr float divisor = 3;
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyMath::Core::Vector2<float>(xL, yL);

			const PonyMath::Core::Vector2<float> product = vectorL / divisor;
			Assert::AreEqual(xL / divisor, product.X());
			Assert::AreEqual(yL / divisor, product.Y());
		}

		static constexpr PonyMath::Core::Vector2<float> VectorConstexpr()
		{
			[[maybe_unused]] auto vector = PonyMath::Core::Vector2<float>(4, 5);
			PonyMath::Core::Vector2<float> movedVector = std::move(vector);

			movedVector.X() += 2;
			movedVector.Y() *= 3;
			movedVector.Span()[1] -= 6;

			[[maybe_unused]] constexpr auto constVector = PonyMath::Core::Vector2<float>(4, 5);

			movedVector.Swap();

			[[maybe_unused]] const float min = movedVector.Min();
			[[maybe_unused]] const float max = movedVector.Max();
			[[maybe_unused]] const auto minMax = movedVector.MinMax();

			movedVector.Set(5, 2);
			movedVector.Set(std::array<float, 2>{7, 9});

			movedVector[1] -= 4;

			movedVector += PonyMath::Core::Vector2<float>(4, 5);
			movedVector -= PonyMath::Core::Vector2<float>(4, 5);
			movedVector *= 4.f;
			movedVector /= 4.f;
			movedVector *= 3;
			movedVector /= 5;

			[[maybe_unused]] auto movedVector1 = PonyMath::Core::Vector2<float>();
			movedVector1 = constVector;
			movedVector1 = std::move(movedVector);

			return movedVector1;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto up = PonyMath::Core::Vector2<float>::Predefined::Up;
			[[maybe_unused]] constexpr auto down = PonyMath::Core::Vector2<float>::Predefined::Down;
			[[maybe_unused]] constexpr auto right = PonyMath::Core::Vector2<float>::Predefined::Right;
			[[maybe_unused]] constexpr auto left = PonyMath::Core::Vector2<float>::Predefined::Left;
			[[maybe_unused]] constexpr auto one = PonyMath::Core::Vector2<float>::Predefined::One;
			[[maybe_unused]] constexpr auto zero = PonyMath::Core::Vector2<float>::Predefined::Zero;
			[[maybe_unused]] constexpr auto negative = PonyMath::Core::Vector2<float>::Predefined::Negative;

			[[maybe_unused]] constexpr auto defaultVector = PonyMath::Core::Vector2<float>();
			[[maybe_unused]] constexpr auto vector = PonyMath::Core::Vector2<float>(4, 5);
			[[maybe_unused]] constexpr auto arrayVector = PonyMath::Core::Vector2<float>(std::array<float, 2>{4, 5});
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> copiedVector = vector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> movedVector = VectorConstexpr();

			[[maybe_unused]] constexpr float x = vector.X();
			[[maybe_unused]] constexpr float y = vector.Y();
			[[maybe_unused]] constexpr auto spanElement = vector.Span()[0];

			[[maybe_unused]] constexpr float magnitudeSquared = vector.MagnitudeSquared();
			[[maybe_unused]] constexpr float min = vector.Min();
			[[maybe_unused]] constexpr float max = vector.Max();
			[[maybe_unused]] constexpr std::pair<float, float> minMax = vector.MinMax();
			[[maybe_unused]] constexpr float thisSum = vector.Sum();
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> swapped = vector.Swapped();

			[[maybe_unused]] constexpr bool isZero = vector.IsZero();
			[[maybe_unused]] constexpr bool isAlmostZero = vector.IsAlmostZero();
			[[maybe_unused]] constexpr bool isUnit = vector.IsUnit();
			[[maybe_unused]] constexpr bool isUniform = vector.IsUniform();

			[[maybe_unused]] constexpr auto intVector = static_cast<PonyMath::Core::Vector2<int>>(vector);

			[[maybe_unused]] constexpr float value = vector[0];

			[[maybe_unused]] constexpr bool equal = arrayVector == vector;
			[[maybe_unused]] constexpr bool notEqual = arrayVector != vector;

			[[maybe_unused]] constexpr float dot = PonyMath::Core::Dot(vector, arrayVector);
			[[maybe_unused]] constexpr float distance = PonyMath::Core::DistanceSquared(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> project = PonyMath::Core::Project(vector, PonyMath::Core::Vector2<float>::Predefined::Down);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> projectOnPlane = PonyMath::Core::ProjectOnPlane(vector, PonyMath::Core::Vector2<float>::Predefined::Left);

			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> reflect = PonyMath::Core::Reflect(vector, PonyMath::Core::Vector2<float>::Predefined::Up);

			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> scale = PonyMath::Core::Scale(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> minCombined = PonyMath::Core::Min(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> maxCombined = PonyMath::Core::Max(defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> clamped = PonyMath::Core::Clamp(vector, defaultVector, arrayVector);
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> lerp = PonyMath::Core::Lerp(vector, arrayVector, 0.5f);

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Core::AreAlmostEqual(vector, arrayVector);

			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> sum = vector + arrayVector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> difference = vector - arrayVector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> product = vector * 3.f;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> productL = 3.f * vector;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<float> quotient = vector / 2.f;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<int> productI = PonyMath::Core::Vector2<int>(4, 5) * 3;
			[[maybe_unused]] constexpr PonyMath::Core::Vector2<int> productIL = 3 * PonyMath::Core::Vector2<int>(4, 5);
		}
	};
}