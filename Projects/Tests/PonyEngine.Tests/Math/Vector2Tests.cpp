/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cmath>;
import <format>;
import <numbers>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Vector2Tests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector2<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector2<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector2<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector2<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector2<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector2<double>::ComputationalType>);
		}

		TEST_METHOD(StaticDataTest)
		{
			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Vector2<float>::ComponentCount);
			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Vector2<short>::ComponentCount);
		}

		TEST_METHOD(DefaultConstructorShortTest)
		{
			const auto vector = PonyEngine::Math::Vector2<short>();
			Assert::AreEqual(short{}, vector.X());
			Assert::AreEqual(short{}, vector.Y());
		}

		TEST_METHOD(DefaultConstructorFloatTest)
		{
			const auto vector = PonyEngine::Math::Vector2<float>();
			Assert::AreEqual(float{}, vector.X());
			Assert::AreEqual(float{}, vector.Y());
		}

		TEST_METHOD(ConstructorShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			const auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			const auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorPointerShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			const auto vector = PonyEngine::Math::Vector2<short>(std::array<short, 2>{x, y}.data());
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorPointerFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			const auto vector = PonyEngine::Math::Vector2<float>(std::array<float, 2>{x, y}.data());
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
		}

		TEST_METHOD(ConstructorCopyShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
			const PonyEngine::Math::Vector2<short> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorCopyFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			const PonyEngine::Math::Vector2<float> copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorMoveShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			const PonyEngine::Math::Vector2<short> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ConstructorMoveFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			const PonyEngine::Math::Vector2<float> copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(ComponentAccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());

			constexpr auto vectorC = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
		}

		TEST_METHOD(ComponentAccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());

			constexpr auto vectorC = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC.X());
			Assert::AreEqual(y, vectorC.Y());
		}

		TEST_METHOD(DataShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vector.Data()[0]);
			Assert::AreEqual(y, vector.Data()[1]);

			constexpr auto vectorC = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC.Data()[0]);
			Assert::AreEqual(y, vectorC.Data()[1]);
		}

		TEST_METHOD(DataFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vector.Data()[0]);
			Assert::AreEqual(y, vector.Data()[1]);

			constexpr auto vectorC = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC.Data()[0]);
			Assert::AreEqual(y, vectorC.Data()[1]);
		}

		TEST_METHOD(MagnitudeShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(3.606, static_cast<double>(vector.Magnitude()), 0.001);
		}

		TEST_METHOD(MagnitudeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(3.606, static_cast<double>(vector.Magnitude()), 0.001);
		}

		TEST_METHOD(MagnitudeSquaredShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(short{13}, vector.MagnitudeSquared());
		}

		TEST_METHOD(MagnitudeSquaredFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(13.f, vector.MagnitudeSquared());
		}

		TEST_METHOD(NormalizeFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			const PonyEngine::Math::Vector2<float> normalized = vector.Normalized();
			Assert::AreEqual(0.555, static_cast<double>(normalized.X()), 0.001);
			Assert::AreEqual(-0.832, static_cast<double>(normalized.Y()), 0.001);
			vector.Normalize();
			Assert::IsTrue(vector == normalized);
		}

		TEST_METHOD(SwapShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			const PonyEngine::Math::Vector2<short> swapped = vector.Swapped();
			Assert::AreEqual(y, swapped.X());
			Assert::AreEqual(x, swapped.Y());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(SwapFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			const PonyEngine::Math::Vector2<float> swapped = vector.Swapped();
			Assert::AreEqual(y, swapped.X());
			Assert::AreEqual(x, swapped.Y());
			vector.Swap();
			Assert::IsTrue(vector == swapped);
		}

		TEST_METHOD(IsFiniteTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
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
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
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
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			vector.Set(xNew, yNew);
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(SetArrayShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			constexpr short xNew = 4;
			constexpr short yNew = 7;
			vector.Set(std::array<short, 2>{xNew, yNew}.data());
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(SetArrayFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			constexpr float xNew = 4;
			constexpr float yNew = 7;
			vector.Set(std::array<float, 2>{xNew, yNew}.data());
			Assert::AreEqual(xNew, vector.X());
			Assert::AreEqual(yNew, vector.Y());
		}

		TEST_METHOD(ScaleThisShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			constexpr short xS = 4;
			constexpr short yS = 7;
			constexpr auto scale = PonyEngine::Math::Vector2<short>(xS, yS);
			vector.Scale(scale);
			Assert::AreEqual(short{x * xS}, vector.X());
			Assert::AreEqual(short{y * yS}, vector.Y());
		}

		TEST_METHOD(ScaleThisFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			constexpr float xS = 4;
			constexpr float yS = 7;
			constexpr auto scale = PonyEngine::Math::Vector2<float>(xS, yS);
			vector.Scale(scale);
			Assert::AreEqual(x * xS, vector.X());
			Assert::AreEqual(y * yS, vector.Y());
		}

		TEST_METHOD(ToStringShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
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
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			const std::string expectedString = std::format("({}, {})", x, y);
			Assert::AreEqual(expectedString, vector.ToString());

			std::ostringstream ss;
			ss << vector;
			Assert::AreEqual(expectedString, ss.str());
		}

		TEST_METHOD(AccessShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);

			constexpr  auto vectorC = PonyEngine::Math::Vector2<short>(x, y);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
		}

		TEST_METHOD(AccessFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);

			constexpr  auto vectorC = PonyEngine::Math::Vector2<float>(x, y);
			Assert::AreEqual(x, vectorC[0]);
			Assert::AreEqual(y, vectorC[1]);
		}

		TEST_METHOD(CopyAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
			auto copiedVector = PonyEngine::Math::Vector2<short>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(CopyAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto copiedVector = PonyEngine::Math::Vector2<float>();
			copiedVector = vector;
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(MoveAssignmentShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			auto vector = PonyEngine::Math::Vector2<short>(x, y);
			auto copiedVector = PonyEngine::Math::Vector2<short>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(MoveAssignmentFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			auto vector = PonyEngine::Math::Vector2<float>(x, y);
			auto copiedVector = PonyEngine::Math::Vector2<float>();
			copiedVector = std::move(vector);
			Assert::AreEqual(x, copiedVector.X());
			Assert::AreEqual(y, copiedVector.Y());
		}

		TEST_METHOD(SumAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL = vectorC += vectorR;
			Assert::AreEqual(static_cast<short>(xC + xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC + yR), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SumAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<float>(xC, yC);
			PonyEngine::Math::Vector2<float>& vectorL = vectorC += vectorR;
			Assert::AreEqual(xC + xR, vectorC.X());
			Assert::AreEqual(yC + yR, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(static_cast<short>(xC - xR), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC - yR), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(SubtractAssignmentFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<float>(xC, yC);
			PonyEngine::Math::Vector2<float>& vectorL = vectorC -= vectorR;
			Assert::AreEqual(xC - xR, vectorC.X());
			Assert::AreEqual(yC - yR, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(MultiplyAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL = vectorC *= multiplierI;
			Assert::AreEqual(static_cast<short>(xC * multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierI), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL1 = vectorC *= multiplierF;
			Assert::AreEqual(static_cast<short>(xC * multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC * multiplierF), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(MultiplyAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<float>(xC, yC);
			PonyEngine::Math::Vector2<float>& vectorL = vectorC *= multiplier;
			Assert::AreEqual(xC * multiplier, vectorC.X());
			Assert::AreEqual(yC * multiplier, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(DivideAssignmentShortTest)
		{
			constexpr short multiplierI = 4;
			constexpr short xC = 6;
			constexpr short yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL = vectorC /= multiplierI;
			Assert::AreEqual(static_cast<short>(xC / multiplierI), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierI), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));

			constexpr float multiplierF = -3;
			vectorC = PonyEngine::Math::Vector2<short>(xC, yC);
			PonyEngine::Math::Vector2<short>& vectorL1 = vectorC /= multiplierF;
			Assert::AreEqual(static_cast<short>(xC / multiplierF), vectorC.X());
			Assert::AreEqual(static_cast<short>(yC / multiplierF), vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL1));
		}

		TEST_METHOD(DivideAssignmentFloatTest)
		{
			constexpr float multiplier = 4;
			constexpr float xC = 6;
			constexpr float yC = 4;
			auto vectorC = PonyEngine::Math::Vector2<float>(xC, yC);
			PonyEngine::Math::Vector2<float>& vectorL = vectorC /= multiplier;
			Assert::AreEqual(xC / multiplier, vectorC.X());
			Assert::AreEqual(yC / multiplier, vectorC.Y());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&vectorC), reinterpret_cast<std::uintptr_t>(&vectorL));
		}

		TEST_METHOD(EqualityShortTest)
		{
			constexpr short x = 2;
			constexpr short y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<short>(x, y);
			PonyEngine::Math::Vector2<short> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyEngine::Math::Vector2<short>::ComponentCount; ++i)
			{
				otherVector.Data()[i] += 1;
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Data()[i] = vector.Data()[i];
			}
		}

		TEST_METHOD(EqualityFloatTest)
		{
			constexpr float x = 2;
			constexpr float y = -3;
			constexpr auto vector = PonyEngine::Math::Vector2<float>(x, y);
			PonyEngine::Math::Vector2<float> otherVector = vector;

			Assert::IsTrue(vector == otherVector);
			Assert::IsFalse(vector != otherVector);

			for (std::size_t i = 0; i < PonyEngine::Math::Vector2<float>::ComponentCount; ++i)
			{
				otherVector.Data()[i] = std::nextafter(otherVector.Data()[i], 0.f);
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Data()[i] += 1;
				Assert::IsFalse(vector == otherVector);
				Assert::IsTrue(vector != otherVector);
				otherVector.Data()[i] = vector.Data()[i];
			}
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector2Up<float> == PonyEngine::Math::Vector2<float>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2Down<float> == PonyEngine::Math::Vector2<float>(0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector2Right<float> == PonyEngine::Math::Vector2<float>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2Left<float> == PonyEngine::Math::Vector2<float>(-1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2One<float> == PonyEngine::Math::Vector2<float>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2Zero<float> == PonyEngine::Math::Vector2<float>(0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2Negative<float> == PonyEngine::Math::Vector2<float>(-1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector2Up<short> == PonyEngine::Math::Vector2<short>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2Down<short> == PonyEngine::Math::Vector2<short>(0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector2Right<short> == PonyEngine::Math::Vector2<short>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2Left<short> == PonyEngine::Math::Vector2<short>(-1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2One<short> == PonyEngine::Math::Vector2<short>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2Zero<short> == PonyEngine::Math::Vector2<short>(0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2Negative<short> == PonyEngine::Math::Vector2<short>(-1, -1));
		}

		TEST_METHOD(DotShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 1;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);
			const short dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(short{9}, dot);
		}

		TEST_METHOD(DotFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 1;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);
			const float dot = PonyEngine::Math::Dot(vectorL, vectorR);
			Assert::AreEqual(9.f, dot);
		}

		TEST_METHOD(AngleTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			const auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR).Normalized();
			constexpr float xL = 6;
			constexpr float yL = 4;
			const auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL).Normalized();
			const float angle = PonyEngine::Math::Angle(vectorL, vectorR);
			Assert::AreEqual(1.571, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(AngleSignedTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			const auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR).Normalized();
			constexpr float xL = 6;
			constexpr float yL = 4;
			const auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL).Normalized();
			float angle = PonyEngine::Math::AngleSigned(vectorL, vectorR);
			Assert::AreEqual(-1.571, static_cast<double>(angle), 0.001);
			angle = PonyEngine::Math::AngleSigned(vectorR, vectorL);
			Assert::AreEqual(1.571, static_cast<double>(angle), 0.001);
		}

		TEST_METHOD(ProjectTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			const auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR).Normalized();
			constexpr float xL = 6;
			constexpr float yL = 1;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);
			const PonyEngine::Math::Vector2<float> projected = PonyEngine::Math::Project(vectorL, vectorR);
			Assert::AreEqual(1.385, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(-2.077, static_cast<double>(projected.Y()), 0.001);
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			const auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR).Normalized();
			constexpr float xL = 6;
			constexpr float yL = 1;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);
			const PonyEngine::Math::Vector2<float> projected = PonyEngine::Math::ProjectOnPlane(vectorL, vectorR);
			Assert::AreEqual(4.615, static_cast<double>(projected.X()), 0.001);
			Assert::AreEqual(3.077, static_cast<double>(projected.Y()), 0.001);
		}

		TEST_METHOD(ReflectTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			const auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR).Normalized();
			constexpr float xL = 6;
			constexpr float yL = 1;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);
			const PonyEngine::Math::Vector2<float> reflected = PonyEngine::Math::Reflect(vectorL, vectorR);
			Assert::AreEqual(3.231, static_cast<double>(reflected.X()), 0.001);
			Assert::AreEqual(5.154, static_cast<double>(reflected.Y()), 0.001);
		}

		TEST_METHOD(ScaleShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);
			const PonyEngine::Math::Vector2<short> scaled = PonyEngine::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(static_cast<short>(xL * xR), scaled.X());
			Assert::AreEqual(static_cast<short>(yL * yR), scaled.Y());
		}

		TEST_METHOD(ScaleFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);
			const PonyEngine::Math::Vector2<float> scaled = PonyEngine::Math::Scale(vectorL, vectorR);
			Assert::AreEqual(xL * xR, scaled.X());
			Assert::AreEqual(yL * yR, scaled.Y());
		}

		TEST_METHOD(LerpShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);

			PonyEngine::Math::Vector2<short> lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(short{ 4 }, lerped.X());
			Assert::AreEqual(short{ 1 }, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(short{ -2 }, lerped.X());
			Assert::AreEqual(short{ -10 }, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(short{ 10 }, lerped.X());
			Assert::AreEqual(short{ 11 }, lerped.Y());
		}

		TEST_METHOD(LerpFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);

			PonyEngine::Math::Vector2<float> lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.f);
			Assert::AreEqual(xL, lerped.X());
			Assert::AreEqual(yL, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 1.f);
			Assert::AreEqual(xR, lerped.X());
			Assert::AreEqual(yR, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 0.5f);
			Assert::AreEqual(4.f, lerped.X());
			Assert::AreEqual(0.5f, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, 2.f);
			Assert::AreEqual(-2.f, lerped.X());
			Assert::AreEqual(-10.f, lerped.Y());

			lerped = PonyEngine::Math::Lerp(vectorL, vectorR, -1.f);
			Assert::AreEqual(10.f, lerped.X());
			Assert::AreEqual(11.f, lerped.Y());
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			PonyEngine::Math::Vector2<float> vectorL = vectorR;

			for (std::size_t i = 0; i < PonyEngine::Math::Vector2<float>::ComponentCount; ++i)
			{
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Data()[i] = std::nextafter(vectorL.Data()[i], 0.f);
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				vectorL.Data()[i] += 1;
				Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR));
				Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vectorL, vectorR, 5.f));
				vectorL.Data()[i] = vectorR.Data()[i];
			}
		}

		TEST_METHOD(SumShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);

			const PonyEngine::Math::Vector2<short> sum = vectorL + vectorR;
			Assert::AreEqual(static_cast<short>(xL + xR), sum.X());
			Assert::AreEqual(static_cast<short>(yL + yR), sum.Y());
		}

		TEST_METHOD(SumFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);

			const PonyEngine::Math::Vector2<float> sum = vectorL + vectorR;
			Assert::AreEqual(xL + xR, sum.X());
			Assert::AreEqual(yL + yR, sum.Y());
		}

		TEST_METHOD(NegateShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);

			const PonyEngine::Math::Vector2<short> negated = -vectorR;
			Assert::AreEqual(static_cast<short>(-xR), negated.X());
			Assert::AreEqual(static_cast<short>(-yR), negated.Y());
		}

		TEST_METHOD(NegateFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);

			const PonyEngine::Math::Vector2<float> negated = -vectorR;
			Assert::AreEqual(-xR, negated.X());
			Assert::AreEqual(-yR, negated.Y());
		}

		TEST_METHOD(SubtractShortTest)
		{
			constexpr short xR = 2;
			constexpr short yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<short>(xR, yR);
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);

			const PonyEngine::Math::Vector2<short> difference = vectorL - vectorR;
			Assert::AreEqual(static_cast<short>(xL - xR), difference.X());
			Assert::AreEqual(static_cast<short>(yL - yR), difference.Y());
		}

		TEST_METHOD(SubtractFloatTest)
		{
			constexpr float xR = 2;
			constexpr float yR = -3;
			constexpr auto vectorR = PonyEngine::Math::Vector2<float>(xR, yR);
			constexpr float xL = 6;
			constexpr float yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);

			const PonyEngine::Math::Vector2<float> difference = vectorL - vectorR;
			Assert::AreEqual(xL - xR, difference.X());
			Assert::AreEqual(yL - yR, difference.Y());
		}

		TEST_METHOD(MultiplyShortTest)
		{
			constexpr short multiplierI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);

			PonyEngine::Math::Vector2<short> product = vectorL * multiplierI;
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
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);

			const PonyEngine::Math::Vector2<float> product = vectorL * multiplier;
			Assert::AreEqual(xL * multiplier, product.X());
			Assert::AreEqual(yL * multiplier, product.Y());
			Assert::IsTrue(multiplier * vectorL == vectorL * multiplier);
		}

		TEST_METHOD(DivideShortTest)
		{
			constexpr short divisorI = 3;
			constexpr short xL = 6;
			constexpr short yL = 4;
			constexpr auto vectorL = PonyEngine::Math::Vector2<short>(xL, yL);

			PonyEngine::Math::Vector2<short> product = vectorL / divisorI;
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
			constexpr auto vectorL = PonyEngine::Math::Vector2<float>(xL, yL);

			const PonyEngine::Math::Vector2<float> product = vectorL / divisor;
			Assert::AreEqual(xL / divisor, product.X());
			Assert::AreEqual(yL / divisor, product.Y());
		}

		static constexpr PonyEngine::Math::Vector2<float> VectorConstexpr()
		{
			auto vector = PonyEngine::Math::Vector2<float>(4, 5);
			PonyEngine::Math::Vector2<float> movedVector = std::move(vector);

			movedVector.X() += 2;
			movedVector.Y() *= 3;
			movedVector.Data()[1] -= 6;

			constexpr auto constVector = PonyEngine::Math::Vector2<float>(4, 5);
			const float* data = constVector.Data();

			movedVector.Swap();

			movedVector.Set(5, 2);
			movedVector.Set(std::array<float, 3>{7, 9, 8}.data());

			movedVector[1] -= 4;

			movedVector += PonyEngine::Math::Vector2<float>(4, 5);
			movedVector -= PonyEngine::Math::Vector2<float>(4, 5);
			movedVector *= 4.f;
			movedVector /= 4.f;

			auto intVector = PonyEngine::Math::Vector2<int>(4, 5);
			intVector *= 3;
			intVector *= 4.f;
			auto intVector1 = PonyEngine::Math::Vector2<int>(4, 5);
			intVector1 /= 5;
			intVector1 /= 2.f;

			auto movedVector1 = PonyEngine::Math::Vector2<float>();
			movedVector1 = constVector;
			movedVector1 = std::move(movedVector);

			return movedVector1;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			constexpr auto defaultVector = PonyEngine::Math::Vector2<float>();
			constexpr auto vector = PonyEngine::Math::Vector2<float>(4, 5);
			constexpr auto arrayVector = PonyEngine::Math::Vector2<float>(std::array<float, 3>{4, 5, 1}.data());
			constexpr PonyEngine::Math::Vector2<float> copiedVector = vector;
			constexpr PonyEngine::Math::Vector2<float> movedVector = VectorConstexpr();

			constexpr float x = vector.X();
			constexpr float y = vector.Y();

			constexpr float magnitudeSquared = vector.MagnitudeSquared();
			constexpr PonyEngine::Math::Vector2<float> swapped = vector.Swapped();

			constexpr float value = vector[0];

			constexpr bool equal = arrayVector == vector;
			constexpr bool notEqual = arrayVector != vector;

			constexpr float dot = PonyEngine::Math::Dot(vector, arrayVector);

			constexpr PonyEngine::Math::Vector2<float> project = PonyEngine::Math::Project(vector, PonyEngine::Math::Vector2Down<float>);
			constexpr PonyEngine::Math::Vector2<float> projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, PonyEngine::Math::Vector2Left<float>);

			constexpr PonyEngine::Math::Vector2<float> reflect = PonyEngine::Math::Reflect(vector, PonyEngine::Math::Vector2Up<float>);

			constexpr PonyEngine::Math::Vector2<float> scale = PonyEngine::Math::Scale(vector, arrayVector);

			constexpr PonyEngine::Math::Vector2<float> lerp = PonyEngine::Math::Lerp(vector, arrayVector, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, arrayVector);

			constexpr PonyEngine::Math::Vector2<float> sum = vector + arrayVector;
			constexpr PonyEngine::Math::Vector2<float> difference = vector - arrayVector;
			constexpr PonyEngine::Math::Vector2<float> product = vector * 3.f;
			constexpr PonyEngine::Math::Vector2<float> productL = 3.f * vector;
			constexpr PonyEngine::Math::Vector2<float> quotient = vector / 2.f;
			constexpr PonyEngine::Math::Vector2<int> productI = PonyEngine::Math::Vector2<int>(4, 5) * 3;
			constexpr PonyEngine::Math::Vector2<int> productIL = 3 * PonyEngine::Math::Vector2<int>(4, 5);
		}
	};
}
