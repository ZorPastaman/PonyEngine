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
		TEST_METHOD(ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector2<float>();
			Assert::AreEqual(float{}, defaultFloatVector.x);
			Assert::AreEqual(float{}, defaultFloatVector.y);

			float xf = 4.f;
			float yf = -14.f;

			auto floatVector = PonyEngine::Math::Vector2<float>(xf, yf);
			Assert::AreEqual(xf, floatVector.x);
			Assert::AreEqual(yf, floatVector.y);

			PonyEngine::Math::Vector2<float> copiedFloatVector = floatVector;
			Assert::AreEqual(xf, copiedFloatVector.x);
			Assert::AreEqual(yf, copiedFloatVector.y);

			PonyEngine::Math::Vector2<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(xf, movedFloatVector.x);
			Assert::AreEqual(yf, movedFloatVector.y);

			auto defaultShortVector = PonyEngine::Math::Vector2<short>();
			Assert::AreEqual(short{}, defaultShortVector.x);
			Assert::AreEqual(short{}, defaultShortVector.y);

			short xi = 4;
			short yi = -14;

			auto shortVector = PonyEngine::Math::Vector2<short>(xi, yi);
			Assert::AreEqual(xi, shortVector.x);
			Assert::AreEqual(yi, shortVector.y);

			PonyEngine::Math::Vector2<short> copiedShortVector = shortVector;
			Assert::AreEqual(xi, copiedShortVector.x);
			Assert::AreEqual(yi, copiedShortVector.y);

			PonyEngine::Math::Vector2<short> movedShortVector = std::move(shortVector);
			Assert::AreEqual(xi, movedShortVector.x);
			Assert::AreEqual(yi, movedShortVector.y);
		}

		TEST_METHOD(MagnitudeTest)
		{
			float xf = 7.f;
			float yf = -17.f;
			float magnitudeSquaredF = std::pow(xf, 2.f) + std::pow(yf, 2.f);
			float magnitudeF = std::sqrt(magnitudeSquaredF);
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);

			Assert::AreEqual(magnitudeSquaredF, vectorF.MagnitudeSquared());
			Assert::AreEqual(magnitudeF, vectorF.Magnitude());

			Assert::AreEqual(0.f, PonyEngine::Math::Vector2<float>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector2<float>::Zero.Magnitude());

			short xi = 7;
			short yi = -17;
			short magnitudeSquaredI = xi * xi + yi * yi;
			float magnitudeI = std::sqrt(static_cast<float>(magnitudeSquaredI));
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);

			Assert::AreEqual(magnitudeSquaredI, vectorI.MagnitudeSquared());
			Assert::AreEqual(magnitudeI, vectorI.Magnitude());

			Assert::AreEqual(short{0}, PonyEngine::Math::Vector2<short>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector2<short>::Zero.Magnitude());
		}

		TEST_METHOD(NormalizationTest)
		{
			float xf = -5.f;
			float yf = 15.f;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			float magnitudeF = vectorF.Magnitude();
			float normXF = xf / magnitudeF;
			float normYF = yf / magnitudeF;
			auto normVectorF = vectorF.Normalized();

			Assert::AreEqual(normXF, normVectorF.x);
			Assert::AreEqual(normYF, normVectorF.y);

			vectorF.Normalize();
			Assert::AreEqual(normVectorF.x, vectorF.x);
			Assert::AreEqual(normVectorF.y, vectorF.y);

			auto zeroNormalizedF = PonyEngine::Math::Vector2<float>::Zero.Normalized();
			Assert::IsFalse(std::isnormal(zeroNormalizedF.x));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.y));

			short xi = -5;
			short yi = 15;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			float magnitudeI = vectorI.Magnitude();
			short normXI = PonyEngine::Math::RoundToIntegral<float, short>(xi / magnitudeI);
			short normYI = PonyEngine::Math::RoundToIntegral<float, short>(yi / magnitudeI);
			auto normVectorI = vectorI.Normalized();

			Assert::AreEqual(normXI, normVectorI.x);
			Assert::AreEqual(normYI, normVectorI.y);

			vectorI.Normalize();
			Assert::AreEqual(normVectorI.x, vectorI.x);
			Assert::AreEqual(normVectorI.y, vectorI.y);

			auto zeroNormalizedI = PonyEngine::Math::Vector2<short>::Zero.Normalized();
			Assert::AreEqual(short{0}, zeroNormalizedI.x);
			Assert::AreEqual(short{0}, zeroNormalizedI.y);
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::One.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector2<float>(nan, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.x = 0.f;
			vector.y = nan;
			Assert::IsFalse(vector.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::One.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			auto vectorF = PonyEngine::Math::Vector2<float>();
			float xf = 3.f;
			float yf = -7.f;
			vectorF.Set(xf, yf);
			Assert::AreEqual(xf, vectorF.x);
			Assert::AreEqual(yf, vectorF.y);

			auto vectorI = PonyEngine::Math::Vector2<short>();
			short xi = 3;
			short yi = -7;
			vectorI.Set(xi, yi);
			Assert::AreEqual(xi, vectorI.x);
			Assert::AreEqual(yi, vectorI.y);
		}

		TEST_METHOD(ToStringTest)
		{
			float xf = 3.f;
			float yf = 2.f;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			std::string expected = std::format("({}, {})", xf, yf);
			std::string vectorString = vectorF.ToString();
			Assert::AreEqual(expected, vectorString);

			std::ostringstream ssF;
			ssF << vectorF;
			Assert::AreEqual(expected, ssF.str());

			short xi = 3;
			short yi = 2;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			expected = std::format("({}, {})", xi, yi);
			vectorString = vectorF.ToString();
			Assert::AreEqual(expected, vectorString);

			std::ostringstream ssI;
			ssI << vectorI;
			Assert::AreEqual(expected, ssI.str());
		}

		TEST_METHOD(AccessOperatorsTest)
		{
			float xf = 2.f;
			float yf = -5.f;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			Assert::AreEqual(xf, vectorF[0]);
			Assert::AreEqual(yf, vectorF[1]);

			float xf1 = 20.f;
			float yf1 = -34.f;
			vectorF[0] = xf1;
			vectorF[1] = yf1;
			Assert::AreEqual(xf1, vectorF[0]);
			Assert::AreEqual(yf1, vectorF[1]);

			const auto vectorFC = PonyEngine::Math::Vector2<float>(xf, yf);
			Assert::AreEqual(xf, vectorFC[0]);
			Assert::AreEqual(yf, vectorFC[1]);

			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Vector2<float>::ComponentCount);

			short xi = 2;
			short yi = -5;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			Assert::AreEqual(xi, vectorI[0]);
			Assert::AreEqual(yi, vectorI[1]);

			short xi1 = 20;
			short yi1 = -34;
			vectorI[0] = xi1;
			vectorI[1] = yi1;
			Assert::AreEqual(xi1, vectorI[0]);
			Assert::AreEqual(yi1, vectorI[1]);

			const auto vectorIC = PonyEngine::Math::Vector2<short>(xi, yi);
			Assert::AreEqual(xi, vectorIC[0]);
			Assert::AreEqual(yi, vectorIC[1]);

			Assert::AreEqual(std::size_t{2}, PonyEngine::Math::Vector2<short>::ComponentCount);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			PonyEngine::Math::Vector2<float> leftF, centralF, rightF;
			float xf = 8.f;
			float yf = 22.f;

			leftF = centralF = rightF = PonyEngine::Math::Vector2<float>(xf, yf);
			Assert::AreEqual(xf, leftF.x);
			Assert::AreEqual(xf, centralF.x);
			Assert::AreEqual(xf, rightF.x);
			Assert::AreEqual(yf, leftF.y);
			Assert::AreEqual(yf, centralF.y);
			Assert::AreEqual(yf, rightF.y);

			float xf1 = 6.f;
			float yf1 = -90.f;
			rightF = PonyEngine::Math::Vector2<float>(xf1, yf1);
			leftF = centralF += rightF;
			Assert::AreEqual(xf + xf1, leftF.x);
			Assert::AreEqual(yf + yf1, leftF.y);
			Assert::AreEqual(xf + xf1, centralF.x);
			Assert::AreEqual(yf + yf1, centralF.y);

			leftF = centralF = PonyEngine::Math::Vector2<float>(xf, yf);
			rightF = PonyEngine::Math::Vector2<float>(xf1, yf1);
			leftF = centralF -= rightF;
			Assert::AreEqual(xf - xf1, leftF.x);
			Assert::AreEqual(yf - yf1, leftF.y);
			Assert::AreEqual(xf - xf1, centralF.x);
			Assert::AreEqual(yf - yf1, centralF.y);

			leftF = centralF = PonyEngine::Math::Vector2<float>(xf, yf);
			float multiplier = 3.f;
			leftF = centralF *= multiplier;
			Assert::AreEqual(xf * multiplier, leftF.x);
			Assert::AreEqual(yf * multiplier, leftF.y);
			Assert::AreEqual(xf * multiplier, centralF.x);
			Assert::AreEqual(yf * multiplier, centralF.y);

			leftF = centralF = PonyEngine::Math::Vector2<float>(xf, yf);
			leftF = centralF /= multiplier;
			Assert::AreEqual(xf / multiplier, leftF.x);
			Assert::AreEqual(yf / multiplier, leftF.y);
			Assert::AreEqual(xf / multiplier, centralF.x);
			Assert::AreEqual(yf / multiplier, centralF.y);

			PonyEngine::Math::Vector2<short> leftI, centralI, rightI;
			short xi = 8;
			short yi = 22;

			leftI = centralI = rightI = PonyEngine::Math::Vector2<short>(xi, yi);
			Assert::AreEqual(xi, leftI.x);
			Assert::AreEqual(xi, centralI.x);
			Assert::AreEqual(xi, rightI.x);
			Assert::AreEqual(yi, leftI.y);
			Assert::AreEqual(yi, centralI.y);
			Assert::AreEqual(yi, rightI.y);

			short xi1 = 6;
			short yi1 = -90;
			rightI = PonyEngine::Math::Vector2<short>(xi1, yi1);
			leftI = centralI += rightI;
			Assert::AreEqual(static_cast<short>(xi + xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(xi + xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), centralI.y);

			leftI = centralI = PonyEngine::Math::Vector2<short>(xi, yi);
			rightI = PonyEngine::Math::Vector2<short>(xi1, yi1);
			leftI = centralI -= rightI;
			Assert::AreEqual(static_cast<short>(xi - xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(xi - xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), centralI.y);

			leftI = centralI = PonyEngine::Math::Vector2<short>(xi, yi);
			leftI = centralI *= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), centralI.y);

			short multiplierI = short{3};
			leftI = centralI = PonyEngine::Math::Vector2<short>(xi, yi);
			leftI = centralI *= multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), leftI.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), leftI.y);
			Assert::AreEqual(static_cast<short>(xi * multiplierI), centralI.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), centralI.y);

			leftI = centralI = PonyEngine::Math::Vector2<short>(xi, yi);
			leftI = centralI /= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), centralI.y);
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Up == PonyEngine::Math::Vector2<float>(0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Down == PonyEngine::Math::Vector2<float>(0.f, -1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Right == PonyEngine::Math::Vector2<float>(1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Left == PonyEngine::Math::Vector2<float>(-1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::One == PonyEngine::Math::Vector2<float>(1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Zero == PonyEngine::Math::Vector2<float>(0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector2<float>::Negative == PonyEngine::Math::Vector2<float>(-1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Up == PonyEngine::Math::Vector2<short>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Down == PonyEngine::Math::Vector2<short>(0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Right == PonyEngine::Math::Vector2<short>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Left == PonyEngine::Math::Vector2<short>(-1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::One == PonyEngine::Math::Vector2<short>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Zero == PonyEngine::Math::Vector2<short>(0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<short>::Negative == PonyEngine::Math::Vector2<short>(-1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Up == PonyEngine::Math::Vector2<unsigned char>(0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Right == PonyEngine::Math::Vector2<unsigned char>(1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::One == PonyEngine::Math::Vector2<unsigned char>(1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector2<unsigned char>::Zero == PonyEngine::Math::Vector2<unsigned char>(0, 0));
		}

		TEST_METHOD(DotTest)
		{
			float xf = 5.f;
			float yf = -1.f;
			float xf1 = 14.f;
			float yf1 = 100.f;
			float dotF = xf * xf1 + yf * yf1;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(xf1, yf1);

			float vectorDotF = PonyEngine::Math::Dot(vectorF, vectorF1);
			Assert::AreEqual(dotF, vectorDotF);

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<float>::Zero, PonyEngine::Math::Vector2<float>::Zero));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<float>::Up, PonyEngine::Math::Vector2<float>::Up));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<float>::Up, PonyEngine::Math::Vector2<float>::Down));

			short xi = 5;
			short yi = -1;
			short xi1 = 14;
			short yi1 = 100;
			short dotI = xi * xi1 + yi * yi1;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(xi1, yi1);

			short vectorDotI = PonyEngine::Math::Dot(vectorI, vectorI1);
			Assert::AreEqual(dotI, vectorDotI);

			Assert::AreEqual(short{0}, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<short>::Zero, PonyEngine::Math::Vector2<short>::Zero));
			Assert::AreEqual(short{1}, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<short>::Up, PonyEngine::Math::Vector2<short>::Up));
			Assert::AreEqual(short{-1}, PonyEngine::Math::Dot(PonyEngine::Math::Vector2<short>::Up, PonyEngine::Math::Vector2<short>::Down));
		}

		TEST_METHOD(AngleTest)
		{
			auto vectorF = PonyEngine::Math::Vector2<float>(1.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(1.f, 0.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1));

			vectorF1.Set(0.f, 1.f);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorF, vectorF1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1));
			Assert::AreEqual(-std::numbers::pi_v<float> *0.5f, PonyEngine::Math::AngleSigned(vectorF1, vectorF));
			Assert::AreEqual(-90.f, PonyEngine::Math::AngleSignedDegrees(vectorF1, vectorF));

			vectorF1.Set(-1.f, 0.f);
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1));

			vectorF.Set(1.f, 0.f);
			vectorF1.Set(0.5f, 0.5f);
			vectorF1.Normalize();
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(45.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF, vectorF1));
			Assert::AreEqual(45.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF1, vectorF));
			Assert::AreEqual(-45.f, PonyEngine::Math::AngleSignedDegrees(vectorF1, vectorF));

			auto vectorI = PonyEngine::Math::Vector2<short>(1, 0);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(1, 0);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleDegrees(vectorI, vectorI1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorI1, vectorI));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSignedDegrees(vectorI1, vectorI));

			vectorI1.Set(0, 1);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleDegrees(vectorI, vectorI1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI, vectorI1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI1, vectorI));
			Assert::AreEqual(-90.f, PonyEngine::Math::AngleSignedDegrees(vectorI1, vectorI));

			vectorI1.Set(-1, 0);
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::Angle(vectorI, vectorI1)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleDegrees(vectorI, vectorI1)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI, vectorI1)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI1, vectorI)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleSignedDegrees(vectorI1, vectorI)));
		}

		TEST_METHOD(ProjectTest)
		{
			auto vectorF = PonyEngine::Math::Vector2<float>(3.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(0.f, 3.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorF, vectorF1).Magnitude());

			vectorF.Set(5.f, 2.f);
			vectorF1.Set(3.f, 1.f);
			auto projectedF = PonyEngine::Math::Project(vectorF, vectorF1);
			Assert::AreEqual(5.1, static_cast<double>(projectedF.x), 0.001);
			Assert::AreEqual(1.7, static_cast<double>(projectedF.y), 0.001);

			auto vectorI = PonyEngine::Math::Vector2<short>(3, 0);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(0, 3);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorI, vectorI1).Magnitude());

			vectorI.Set(2, 2);
			vectorI1.Set(3, 1);
			auto projectedI = PonyEngine::Math::Project(vectorI, vectorI1);
			Assert::AreEqual(short{2}, projectedI.x);
			Assert::AreEqual(short{1}, projectedI.y);
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			auto vectorF = PonyEngine::Math::Vector2<float>(2.f, 0.f);
			auto normalF = PonyEngine::Math::Vector2<float>(-1.f, 0.f);
			auto projectionF = PonyEngine::Math::ProjectOnPlane(vectorF, normalF);
			Assert::AreEqual(0.f, projectionF.Magnitude());

			vectorF.Set(20.f, -30.f);
			normalF.Set(0.5f, 0.1f);
			normalF.Normalize();
			auto expectedF = vectorF - normalF * PonyEngine::Math::Dot(vectorF, normalF);
			projectionF = PonyEngine::Math::ProjectOnPlane(vectorF, normalF);
			Assert::AreEqual(expectedF.x, projectionF.x);
			Assert::AreEqual(expectedF.y, projectionF.y);

			auto vectorI = PonyEngine::Math::Vector2<short>(2, 0);
			auto normalI = PonyEngine::Math::Vector2<short>(-1, 0);
			auto projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(0.f, projectionI.Magnitude());

			vectorI.Set(20, -30);
			normalI.Set(5, 1);
			normalI.Normalize();
			auto expectedI = vectorI - normalI * PonyEngine::Math::Dot(vectorI, normalI);
			projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(expectedI.x, projectionI.x);
			Assert::AreEqual(expectedI.y, projectionI.y);
		}

		TEST_METHOD(ReflectTest)
		{
			auto vectorF = PonyEngine::Math::Vector2<float>(0.5f, -0.5f);
			auto normalF = PonyEngine::Math::Vector2<float>(0.f, 1.f);
			auto reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.5f, reflectionF.x);
			Assert::AreEqual(0.5f, reflectionF.y);

			vectorF.Set(0.f, 5.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.x);
			Assert::AreEqual(-5.f, reflectionF.y);

			vectorF.Set(0.f, -4.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.x);
			Assert::AreEqual(4.f, reflectionF.y);

			vectorF.Set(3.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(3.f, reflectionF.x);
			Assert::AreEqual(0.f, reflectionF.y);

			vectorF.Set(-14.f, 39.f);
			normalF.Set(10.f, -17.f);
			normalF.Normalize();
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			auto expectedF = vectorF - 2.f * PonyEngine::Math::Dot(vectorF, normalF) * normalF;
			Assert::AreEqual(expectedF.x, reflectionF.x);
			Assert::AreEqual(expectedF.y, reflectionF.y);

			auto vectorI = PonyEngine::Math::Vector2<short>(1, -1);
			auto normalI = PonyEngine::Math::Vector2<short>(0, 1);
			auto reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{1}, reflectionI.x);
			Assert::AreEqual(short{1}, reflectionI.y);

			vectorI.Set(0, 5);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.x);
			Assert::AreEqual(short{-5}, reflectionI.y);

			vectorI.Set(0, -4);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.x);
			Assert::AreEqual(short{4}, reflectionI.y);

			vectorI.Set(3, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{3}, reflectionI.x);
			Assert::AreEqual(short{0}, reflectionI.y);
		}

		TEST_METHOD(ScaleTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector2<float>(-2.f, 2.f);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(2.f, 4.f);

			auto scaledF = PonyEngine::Math::Scale(vectorF0, vectorF1);
			Assert::AreEqual(-4.f, scaledF.x);
			Assert::AreEqual(8.f, scaledF.y);

			auto vectorI0 = PonyEngine::Math::Vector2<short>(-2, 2);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(2, 4);
			auto scaledI = PonyEngine::Math::Scale(vectorI0, vectorI1);
			Assert::AreEqual(short{-4}, scaledI.x);
			Assert::AreEqual(short{8}, scaledI.y);

			vectorF0.Scale(vectorF1);
			Assert::AreEqual(scaledF.x, vectorF0.x);
			Assert::AreEqual(scaledF.y, vectorF0.y);

			vectorI0.Scale(vectorI1);
			Assert::AreEqual(scaledI.x, vectorI0.x);
			Assert::AreEqual(scaledI.y, vectorI0.y);
		}

		TEST_METHOD(LerpTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector2<float>(-2.f, 2.f);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(2.f, 4.f);
			auto lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.f);
			Assert::AreEqual(vectorF0.x, lerpedF.x);
			Assert::AreEqual(vectorF0.y, lerpedF.y);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 1.f);
			Assert::AreEqual(vectorF1.x, lerpedF.x);
			Assert::AreEqual(vectorF1.y, lerpedF.y);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.5f);
			Assert::AreEqual(0.f, lerpedF.x);
			Assert::AreEqual(3.f, lerpedF.y);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 2.f);
			Assert::AreEqual(6.f, lerpedF.x);
			Assert::AreEqual(6.f, lerpedF.y);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, -1.f);
			Assert::AreEqual(-6.f, lerpedF.x);
			Assert::AreEqual(0.f, lerpedF.y);

			auto vectorI0 = PonyEngine::Math::Vector2<short>(-2, 2);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(2, 4);
			auto lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.f);
			Assert::AreEqual(vectorI0.x, lerpedI.x);
			Assert::AreEqual(vectorI0.y, lerpedI.y);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 1.f);
			Assert::AreEqual(vectorI1.x, lerpedI.x);
			Assert::AreEqual(vectorI1.y, lerpedI.y);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.5f);
			Assert::AreEqual(short{0}, lerpedI.x);
			Assert::AreEqual(short{3}, lerpedI.y);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 2.f);
			Assert::AreEqual(short{6}, lerpedI.x);
			Assert::AreEqual(short{6}, lerpedI.y);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, -1.f);
			Assert::AreEqual(short{-6}, lerpedI.x);
			Assert::AreEqual(short{0}, lerpedI.y);
		}

		TEST_METHOD(AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector2<float>(1.f, 1.f);
			auto vector1 = vector0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = std::nextafter(vector1.x, 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.x = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vector0, vector1));
		}

		TEST_METHOD(EqualityOperatorsTest)
		{
			float xf = 10.f;
			float yf = 15.f;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(xf, yf);
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			vectorF1.y *= 3.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.y = yf;
			vectorF1.x *= 0.5f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF.y *= 3.5f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF = vectorF1;
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			short xi = 10;
			short yi = 15;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(xi, yi);
			Assert::IsTrue(vectorI == vectorI1);
			Assert::IsFalse(vectorI != vectorI1);

			vectorI1.y *= 3;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.y = yi;
			vectorI1.x *= 5;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI.y *= 3;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI = vectorI1;
			Assert::IsTrue(vectorI == vectorI1);
			Assert::IsFalse(vectorI != vectorI1);
		}

		TEST_METHOD(ComputationOperatorsTest)
		{
			float xf = 90.f;
			float yf = 100.f;
			float xf1 = -75.f;
			float yf1 = 60.f;
			auto vectorF = PonyEngine::Math::Vector2<float>(xf, yf);
			auto vectorF1 = PonyEngine::Math::Vector2<float>(xf1, yf1);

			auto vectorF2 = vectorF + vectorF1;
			Assert::AreEqual(xf + xf1, vectorF2.x);
			Assert::AreEqual(yf + yf1, vectorF2.y);

			vectorF2 = vectorF - vectorF1;
			Assert::AreEqual(xf - xf1, vectorF2.x);
			Assert::AreEqual(yf - yf1, vectorF2.y);

			float multiplier = 3.3f;
			vectorF2 = vectorF * multiplier;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);

			vectorF2 = multiplier * vectorF;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);

			vectorF2 = vectorF / multiplier;
			Assert::AreEqual(xf / multiplier, vectorF2.x);
			Assert::AreEqual(yf / multiplier, vectorF2.y);

			short xi = 90;
			short yi = 100;
			short xi1 = -75;
			short yi1 = 60;
			auto vectorI = PonyEngine::Math::Vector2<short>(xi, yi);
			auto vectorI1 = PonyEngine::Math::Vector2<short>(xi1, yi1);

			auto vectorI2 = vectorI + vectorI1;
			Assert::AreEqual(static_cast<short>(xi + xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), vectorI2.y);

			vectorI2 = vectorI - vectorI1;
			Assert::AreEqual(static_cast<short>(xi - xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), vectorI2.y);

			short multiplierI = 3;
			vectorI2 = vectorI * multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.y);

			vectorI2 = vectorI * multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);

			vectorI2 = multiplierI * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.y);

			vectorI2 = multiplier * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);

			vectorI2 = vectorI / multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi / multiplier), vectorI2.y);
		}

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

		TEST_METHOD(ConstexprTest)
		{
#pragma warning(disable:4189)
			constexpr auto defaultVector = PonyEngine::Math::Vector2<float>();
			constexpr auto vector = PonyEngine::Math::Vector2<float>(3.f, 2.f);
			constexpr PonyEngine::Math::Vector2<float> copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector2<float>(0.f, 1.f);

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr std::size_t size = vector.ComponentCount;

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
			constexpr auto projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, normal);
			constexpr auto reflection = PonyEngine::Math::Reflect(vector, normal);
			constexpr auto scaled = PonyEngine::Math::Scale(vector, normal);
			constexpr auto lerped = PonyEngine::Math::Lerp(vector, copiedVector, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, copiedVector);

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negative = -vector;
			constexpr auto sub = vector - copiedVector;
			constexpr auto multiplied = vector * 3.f;
			constexpr auto multipliedL = 3.f * vector;
			constexpr auto divided = vector / 3.f;

			constexpr auto intVector = PonyEngine::Math::Vector2<int>();
			constexpr auto multipliedI = intVector * 3;
			constexpr auto multipliedLI = 3 * intVector;
			constexpr auto multipliedIF = intVector * 3.f;
			constexpr auto multipliedLIF = 3.f * intVector;
#pragma warning(default:4189)
		}
	};
}
