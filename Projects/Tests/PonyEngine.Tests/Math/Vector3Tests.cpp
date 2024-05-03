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
	TEST_CLASS(Vector3Tests)
	{
		TEST_METHOD(ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector3<float>();
			Assert::AreEqual(float{}, defaultFloatVector.X());
			Assert::AreEqual(float{}, defaultFloatVector.Y());
			Assert::AreEqual(float{}, defaultFloatVector.Z());

			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;

			auto floatVector = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(xf, floatVector.X());
			Assert::AreEqual(yf, floatVector.Y());
			Assert::AreEqual(zf, floatVector.Z());

			PonyEngine::Math::Vector3<float> copiedFloatVector = floatVector;
			Assert::AreEqual(xf, copiedFloatVector.X());
			Assert::AreEqual(yf, copiedFloatVector.Y());
			Assert::AreEqual(zf, copiedFloatVector.Z());

			PonyEngine::Math::Vector3<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(xf, movedFloatVector.X());
			Assert::AreEqual(yf, movedFloatVector.Y());
			Assert::AreEqual(zf, movedFloatVector.Z());

			auto defaultShortVector = PonyEngine::Math::Vector3<short>();
			Assert::AreEqual(short{}, defaultShortVector.X());
			Assert::AreEqual(short{}, defaultShortVector.Y());
			Assert::AreEqual(short{}, defaultShortVector.Z());

			short xi = 4;
			short yi = -14;
			short zi = 7;

			auto shortVector = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, shortVector.X());
			Assert::AreEqual(yi, shortVector.Y());
			Assert::AreEqual(zi, shortVector.Z());

			PonyEngine::Math::Vector3<short> copiedShortVector = shortVector;
			Assert::AreEqual(xi, copiedShortVector.X());
			Assert::AreEqual(yi, copiedShortVector.Y());
			Assert::AreEqual(zi, copiedShortVector.Z());

			PonyEngine::Math::Vector3<short> movedShortVector = std::move(shortVector);
			Assert::AreEqual(xi, movedShortVector.X());
			Assert::AreEqual(yi, movedShortVector.Y());
			Assert::AreEqual(zi, movedShortVector.Z());
		}

		TEST_METHOD(DataTest)
		{
			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;
			auto floatVector = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(floatVector.X(), floatVector.Data()[0]);
			Assert::AreEqual(floatVector.Y(), floatVector.Data()[1]);
			Assert::AreEqual(floatVector.Z(), floatVector.Data()[2]);

			short xi = 4;
			short yi = -14;
			short zi = 7;
			auto shortVector = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(shortVector.X(), shortVector.Data()[0]);
			Assert::AreEqual(shortVector.Y(), shortVector.Data()[1]);
			Assert::AreEqual(shortVector.Z(), shortVector.Data()[2]);
		}

		TEST_METHOD(MagnitudeTest)
		{
			float xf = 7.f;
			float yf = -17.f;
			float zf = -43.f;
			float magnitudeSquaredF = std::pow(xf, 2.f) + std::pow(yf, 2.f) + std::pow(zf, 2.f);
			float magnitudeF = std::sqrt(magnitudeSquaredF);
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);

			Assert::AreEqual(magnitudeSquaredF, vectorF.MagnitudeSquared());
			Assert::AreEqual(magnitudeF, vectorF.Magnitude());

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3Zero<float>.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector3Zero<float>.Magnitude());

			short xi = 7;
			short yi = -17;
			short zi = -43;
			short magnitudeSquaredI = static_cast<short>(xi * xi + yi * yi + zi * zi);
			float magnitudeI = std::sqrt(static_cast<float>(magnitudeSquaredI));
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);

			Assert::AreEqual(magnitudeSquaredI, vectorI.MagnitudeSquared());
			Assert::AreEqual(magnitudeI, vectorI.Magnitude());

			Assert::AreEqual(short{0}, PonyEngine::Math::Vector3Zero<short>.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector3Zero<short>.Magnitude());
		}

		TEST_METHOD(NormalizationTest)
		{
			float xf = -5.f;
			float yf = 15.f;
			float zf = 7.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			float magnitudeF = vectorF.Magnitude();
			float normXF = xf / magnitudeF;
			float normYF = yf / magnitudeF;
			float normZF = zf / magnitudeF;
			auto normVectorF = vectorF.Normalized();

			Assert::AreEqual(static_cast<double>(normXF), static_cast<double>(normVectorF.X()), 0.00001);
			Assert::AreEqual(static_cast<double>(normYF), static_cast<double>(normVectorF.Y()), 0.00001);
			Assert::AreEqual(static_cast<double>(normZF), static_cast<double>(normVectorF.Z()), 0.00001);

			vectorF.Normalize();
			Assert::AreEqual(static_cast<double>(normVectorF.X()), static_cast<double>(vectorF.X()), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.Y()), static_cast<double>(vectorF.Y()), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.Z()), static_cast<double>(vectorF.Z()), 0.00001);

			auto zeroNormalizedF = PonyEngine::Math::Vector3Zero<float>.Normalized();
			Assert::IsFalse(std::isnormal(zeroNormalizedF.X()));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.Y()));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.Z()));

			short xi = -5;
			short yi = 15;
			short zi = 7;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			float magnitudeI = vectorI.Magnitude();
			short normXI = static_cast<short>(xi / magnitudeI);
			short normYI = static_cast<short>(yi / magnitudeI);
			short normZI = static_cast<short>(zi / magnitudeI);
			auto normVectorI = vectorI.Normalized();

			Assert::AreEqual(normXI, normVectorI.X());
			Assert::AreEqual(normYI, normVectorI.Y());
			Assert::AreEqual(normZI, normVectorI.Z());

			vectorI.Normalize();
			Assert::AreEqual(normVectorI.X(), vectorI.X());
			Assert::AreEqual(normVectorI.Y(), vectorI.Y());
			Assert::AreEqual(normVectorI.Z(), vectorI.Z());

			auto zeroNormalizedI = PonyEngine::Math::Vector3Zero<short>.Normalized();
			Assert::AreEqual(short{0}, zeroNormalizedI.X());
			Assert::AreEqual(short{0}, zeroNormalizedI.Y());
			Assert::AreEqual(short{0}, zeroNormalizedI.Z());
		}

		TEST_METHOD(InverseTest)
		{
			float xf = -5.f;
			float yf = 15.f;
			float zf = 7.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto swappedF = vectorF.Swapped();
			Assert::AreEqual(zf, swappedF.X());
			Assert::AreEqual(yf, swappedF.Y());
			Assert::AreEqual(xf, swappedF.Z());

			short xi = -5;
			short yi = 15;
			short zi = 7;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto swappedI = vectorI.Swapped();
			Assert::AreEqual(zi, swappedI.X());
			Assert::AreEqual(yi, swappedI.Y());
			Assert::AreEqual(xi, swappedI.Z());
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3Zero<float>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector3One<float>.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector3<float>(nan, 0.f, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.X() = 0.f;
			vector.Y() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.Y() = 0.f;
			vector.Z() = nan;
			Assert::IsFalse(vector.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Vector3Zero<short>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector3One<short>.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>();
			float xf = 3.f;
			float yf = -7.f;
			float zf = 5.f;
			vectorF.Set(xf, yf, zf);
			Assert::AreEqual(xf, vectorF.X());
			Assert::AreEqual(yf, vectorF.Y());
			Assert::AreEqual(zf, vectorF.Z());

			auto vectorI = PonyEngine::Math::Vector3<short>();
			short xi = 3;
			short yi = -7;
			short zi = 5;
			vectorI.Set(xi, yi, zi);
			Assert::AreEqual(xi, vectorI.X());
			Assert::AreEqual(yi, vectorI.Y());
			Assert::AreEqual(zi, vectorI.Z());
		}

		TEST_METHOD(ToStringTest)
		{
			float xf = 3.f;
			float yf = 2.f;
			float zf = -1.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			std::string expected = std::format("({}, {}, {})", xf, yf, zf);
			std::string vectorString = vectorF.ToString();
			Assert::AreEqual(expected, vectorString);

			std::ostringstream ssF;
			ssF << vectorF;
			Assert::AreEqual(expected, ssF.str());

			short xi = 3;
			short yi = 2;
			short zi = -1;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			expected = std::format("({}, {}, {})", xi, yi, zi);
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
			float zf = 7.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(xf, vectorF[0]);
			Assert::AreEqual(yf, vectorF[1]);
			Assert::AreEqual(zf, vectorF[2]);

			float xf1 = 20.f;
			float yf1 = -34.f;
			float zf1 = 55.f;
			vectorF[0] = xf1;
			vectorF[1] = yf1;
			vectorF[2] = zf1;
			Assert::AreEqual(xf1, vectorF[0]);
			Assert::AreEqual(yf1, vectorF[1]);
			Assert::AreEqual(zf1, vectorF[2]);

			const auto vectorFC = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(xf, vectorFC[0]);
			Assert::AreEqual(yf, vectorFC[1]);
			Assert::AreEqual(zf, vectorFC[2]);

			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Vector3<float>::ComponentCount);

			short xi = 2;
			short yi = -5;
			short zi = 7;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, vectorI[0]);
			Assert::AreEqual(yi, vectorI[1]);
			Assert::AreEqual(zi, vectorI[2]);

			short xi1 = 20;
			short yi1 = -34;
			short zi1 = 55;
			vectorI[0] = xi1;
			vectorI[1] = yi1;
			vectorI[2] = zi1;
			Assert::AreEqual(xi1, vectorI[0]);
			Assert::AreEqual(yi1, vectorI[1]);
			Assert::AreEqual(zi1, vectorI[2]);

			const auto vectorIC = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, vectorIC[0]);
			Assert::AreEqual(yi, vectorIC[1]);
			Assert::AreEqual(zi, vectorIC[2]);

			Assert::AreEqual(std::size_t{3}, PonyEngine::Math::Vector3<short>::ComponentCount);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			PonyEngine::Math::Vector3<float> leftF, centralF, rightF;
			float xf = 8.f;
			float yf = 22.f;
			float zf = -98.f;

			leftF = centralF = rightF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(xf, leftF.X());
			Assert::AreEqual(xf, centralF.X());
			Assert::AreEqual(xf, rightF.X());
			Assert::AreEqual(yf, leftF.Y());
			Assert::AreEqual(yf, centralF.Y());
			Assert::AreEqual(yf, rightF.Y());
			Assert::AreEqual(zf, leftF.Z());
			Assert::AreEqual(zf, centralF.Z());
			Assert::AreEqual(zf, rightF.Z());

			float xf1 = 6.f;
			float yf1 = -90.f;
			float zf1 = 32.f;
			rightF = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);
			leftF = centralF += rightF;
			Assert::AreEqual(xf + xf1, leftF.X());
			Assert::AreEqual(yf + yf1, leftF.Y());
			Assert::AreEqual(zf + zf1, leftF.Z());
			Assert::AreEqual(xf + xf1, centralF.X());
			Assert::AreEqual(yf + yf1, centralF.Y());
			Assert::AreEqual(zf + zf1, centralF.Z());

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			rightF = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);
			leftF = centralF -= rightF;
			Assert::AreEqual(xf - xf1, leftF.X());
			Assert::AreEqual(yf - yf1, leftF.Y());
			Assert::AreEqual(zf - zf1, leftF.Z());
			Assert::AreEqual(xf - xf1, centralF.X());
			Assert::AreEqual(yf - yf1, centralF.Y());
			Assert::AreEqual(zf - zf1, centralF.Z());

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			float multiplier = 3.f;
			leftF = centralF *= multiplier;
			Assert::AreEqual(xf * multiplier, leftF.X());
			Assert::AreEqual(yf * multiplier, leftF.Y());
			Assert::AreEqual(zf * multiplier, leftF.Z());
			Assert::AreEqual(xf * multiplier, centralF.X());
			Assert::AreEqual(yf * multiplier, centralF.Y());
			Assert::AreEqual(zf * multiplier, centralF.Z());

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			leftF = centralF /= multiplier;
			Assert::AreEqual(xf / multiplier, leftF.X());
			Assert::AreEqual(yf / multiplier, leftF.Y());
			Assert::AreEqual(zf / multiplier, leftF.Z());
			Assert::AreEqual(xf / multiplier, centralF.X());
			Assert::AreEqual(yf / multiplier, centralF.Y());
			Assert::AreEqual(zf / multiplier, centralF.Z());

			PonyEngine::Math::Vector3<short> leftI, centralI, rightI;
			short xi = 8;
			short yi = 22;
			short zi = -98;

			leftI = centralI = rightI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, leftI.X());
			Assert::AreEqual(xi, centralI.X());
			Assert::AreEqual(xi, rightI.X());
			Assert::AreEqual(yi, leftI.Y());
			Assert::AreEqual(yi, centralI.Y());
			Assert::AreEqual(yi, rightI.Y());
			Assert::AreEqual(zi, leftI.Z());
			Assert::AreEqual(zi, centralI.Z());
			Assert::AreEqual(zi, rightI.Z());

			short xi1 = 6;
			short yi1 = -90;
			short zi1 = 32;
			rightI = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);
			leftI = centralI += rightI;
			Assert::AreEqual(static_cast<short>(xi + xi1), leftI.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), leftI.Z());
			Assert::AreEqual(static_cast<short>(xi + xi1), centralI.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), centralI.Z());

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			rightI = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);
			leftI = centralI -= rightI;
			Assert::AreEqual(static_cast<short>(xi - xi1), leftI.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), leftI.Z());
			Assert::AreEqual(static_cast<short>(xi - xi1), centralI.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), centralI.Z());

			short multiplierI = short{3};
			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI *= multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), leftI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), leftI.Z());
			Assert::AreEqual(static_cast<short>(xi * multiplierI), centralI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), centralI.Z());

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI *= multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), leftI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), leftI.Z());
			Assert::AreEqual(static_cast<short>(xi * multiplier), centralI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), centralI.Z());

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI /= multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), leftI.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), leftI.Z());
			Assert::AreEqual(static_cast<short>(xi / multiplier), centralI.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), centralI.Z());
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3Forward<float> == PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Back<float> == PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Up<float> == PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Down<float> == PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Right<float> == PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Left<float> == PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3One<float> == PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Zero<float> == PonyEngine::Math::Vector3<float>(0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3Negative<float> == PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector3Forward<short> == PonyEngine::Math::Vector3<short>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3Back<short> == PonyEngine::Math::Vector3<short>(0, 0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector3Up<short> == PonyEngine::Math::Vector3<short>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3Down<short> == PonyEngine::Math::Vector3<short>(0, -1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3Right<short> == PonyEngine::Math::Vector3<short>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3Left<short> == PonyEngine::Math::Vector3<short>(-1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3One<short> == PonyEngine::Math::Vector3<short>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3Zero<short> == PonyEngine::Math::Vector3<short>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3Negative<short> == PonyEngine::Math::Vector3<short>(-1, -1, -1));
		}

		TEST_METHOD(DotTest)
		{
			float xf = 5.f;
			float yf = -1.f;
			float zf = -15.f;
			float xf1 = 14.f;
			float yf1 = 100.f;
			float zf1 = -2.f;
			float dotF = xf * xf1 + yf * yf1 + zf * zf1;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);

			float vectorDotF = PonyEngine::Math::Dot(vectorF, vectorF1);
			Assert::AreEqual(dotF, vectorDotF);

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Zero<float>, PonyEngine::Math::Vector3Zero<float>));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Forward<float>, PonyEngine::Math::Vector3Forward<float>));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Forward<float>, PonyEngine::Math::Vector3Back<float>));

			short xi = 5;
			short yi = -1;
			short zi = -15;
			short xi1 = 14;
			short yi1 = 100;
			short zi1 = -2;
			float dotI = static_cast<float>(xi) * xi1 + static_cast<float>(yi) * yi1 + static_cast<float>(zi) * zi1;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);

			float vectorDotI = PonyEngine::Math::Dot(vectorI, vectorI1);
			Assert::AreEqual(dotI, vectorDotI);

			Assert::AreEqual(short{0}, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Zero<short>, PonyEngine::Math::Vector3Zero<short>));
			Assert::AreEqual(short{1}, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Forward<short>, PonyEngine::Math::Vector3Forward<short>));
			Assert::AreEqual(short{-1}, PonyEngine::Math::Dot(PonyEngine::Math::Vector3Forward<short>, PonyEngine::Math::Vector3Back<short>));
		}

		TEST_METHOD(CrossTest)
		{
			float xf = 5.f;
			float yf = -1.f;
			float zf = -15.f;
			float xf1 = 14.f;
			float yf1 = 100.f;
			float zf1 = -2.f;
			auto crossF = PonyEngine::Math::Vector3<float>(yf * zf1 - zf * yf1, zf * xf1 - xf * zf1, xf * yf1 - yf * xf1);
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);

			auto vectorCrossF = PonyEngine::Math::Cross(vectorF, vectorF1);
			Assert::AreEqual(crossF.X(), vectorCrossF.X());
			Assert::AreEqual(crossF.Y(), vectorCrossF.Y());
			Assert::AreEqual(crossF.Z(), vectorCrossF.Z());

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3Zero<float>, PonyEngine::Math::Vector3Zero<float>);
			Assert::AreEqual(0.f, vectorCrossF.X());
			Assert::AreEqual(0.f, vectorCrossF.Y());
			Assert::AreEqual(0.f, vectorCrossF.Z());

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<float>, PonyEngine::Math::Vector3Zero<float>);
			Assert::AreEqual(0.f, vectorCrossF.X());
			Assert::AreEqual(0.f, vectorCrossF.Y());
			Assert::AreEqual(0.f, vectorCrossF.Z());

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<float>, PonyEngine::Math::Vector3One<float>);
			Assert::AreEqual(0.f, vectorCrossF.X());
			Assert::AreEqual(0.f, vectorCrossF.Y());
			Assert::AreEqual(0.f, vectorCrossF.Z());

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<float>, PonyEngine::Math::Vector3Negative<float>);
			Assert::AreEqual(0.f, vectorCrossF.X());
			Assert::AreEqual(0.f, vectorCrossF.Y());
			Assert::AreEqual(0.f, vectorCrossF.Z());

			short xi = 5;
			short yi = -1;
			short zi = -15;
			short xi1 = 14;
			short yi1 = 100;
			short zi1 = -2;
			short crossXI = PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(yi) * zi1 - static_cast<float>(zi) * yi1);
			short crossYI = PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(zi) * xi1 - static_cast<float>(xi) * zi1);
			short crossZI = PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(xi) * yi1 - static_cast<float>(yi) * xi1);
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);

			auto vectorCrossI = PonyEngine::Math::Cross(vectorI, vectorI1);
			Assert::AreEqual(crossXI, vectorCrossI.X());
			Assert::AreEqual(crossYI, vectorCrossI.Y());
			Assert::AreEqual(crossZI, vectorCrossI.Z());

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3Zero<short>, PonyEngine::Math::Vector3Zero<short>);
			Assert::AreEqual(short{0}, vectorCrossI.X());
			Assert::AreEqual(short{0}, vectorCrossI.Y());
			Assert::AreEqual(short{0}, vectorCrossI.Z());

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<short>, PonyEngine::Math::Vector3Zero<short>);
			Assert::AreEqual(short{0}, vectorCrossI.X());
			Assert::AreEqual(short{0}, vectorCrossI.Y());
			Assert::AreEqual(short{0}, vectorCrossI.Z());

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<short>, PonyEngine::Math::Vector3One<short>);
			Assert::AreEqual(short{0}, vectorCrossI.X());
			Assert::AreEqual(short{0}, vectorCrossI.Y());
			Assert::AreEqual(short{0}, vectorCrossI.Z());

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3One<short>, PonyEngine::Math::Vector3Negative<short>);
			Assert::AreEqual(short{0}, vectorCrossI.X());
			Assert::AreEqual(short{0}, vectorCrossI.Y());
			Assert::AreEqual(short{0}, vectorCrossI.Z());
		}

		TEST_METHOD(AngleTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Forward<float>));

			vectorF1.Set(0.f, 1.f, 0.f);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Forward<float>));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Back<float>));

			vectorF1.Set(-1.f, 0.f, 0.f);
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Forward<float>));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Back<float>));

			vectorF.Set(0.f, 0.f, 1.f);
			vectorF1.Set(0.f, 0.5f, 0.5f);
			vectorF1.Normalize();
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Left<float>));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3Right<float>));

			auto vectorI = PonyEngine::Math::Vector3<short>(1, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(1, 0, 0);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3Forward<short>));

			vectorI1.Set(0, 1, 0);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3Forward<short>));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3Back<short>));

			vectorI1.Set(-1, 0, 0);
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::Angle(vectorI, vectorI1)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3Forward<short>)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3Back<short>)));
		}

		TEST_METHOD(ProjectTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(3.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(0.f, 0.f, 3.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorF, vectorF1).Magnitude());

			vectorF.Set(-4.f, 2.f, 7.f);
			vectorF1.Set(3.f, 1.f, 2.f);
			auto projectedF = PonyEngine::Math::Project(vectorF, vectorF1);
			Assert::AreEqual(0.857, static_cast<double>(projectedF.X()), 0.001);
			Assert::AreEqual(0.286, static_cast<double>(projectedF.Y()), 0.001);
			Assert::AreEqual(0.571, static_cast<double>(projectedF.Z()), 0.001);

			auto vectorI = PonyEngine::Math::Vector3<short>(3, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(0, 0, 3);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorI, vectorI1).Magnitude());

			vectorI.Set(2, 2, 7);
			vectorI1.Set(3, 1, 0);
			auto projectedI = PonyEngine::Math::Project(vectorI, vectorI1);
			Assert::AreEqual(short{2}, projectedI.X());
			Assert::AreEqual(short{0}, projectedI.Y());
			Assert::AreEqual(short{0}, projectedI.Z());
		}

		TEST_METHOD(ProjectOnPlaneTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(2.f, 0.f, 0.f);
			auto normalF = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
			auto projectionF = PonyEngine::Math::ProjectOnPlane(vectorF, normalF);
			Assert::AreEqual(0.f, projectionF.Magnitude());

			vectorF.Set(20.f, -30.f, 15.f);
			normalF.Set(0.5f, 0.1f, -0.24f);
			normalF.Normalize();
			auto expectedF = vectorF - normalF * PonyEngine::Math::Dot(vectorF, normalF);
			projectionF = PonyEngine::Math::ProjectOnPlane(vectorF, normalF);
			Assert::AreEqual(expectedF.X(), projectionF.X());
			Assert::AreEqual(expectedF.Y(), projectionF.Y());
			Assert::AreEqual(expectedF.Z(), projectionF.Z());

			auto vectorI = PonyEngine::Math::Vector3<short>(2, 0, 0);
			auto normalI = PonyEngine::Math::Vector3<short>(-1, 0, 0);
			auto projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(0.f, projectionI.Magnitude());

			vectorI.Set(20, -30, 15);
			normalI.Set(5, 1, -1);
			normalI.Normalize();
			auto expectedI = vectorI - normalI * PonyEngine::Math::Dot(vectorI, normalI);
			projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(expectedI.X(), projectionI.X());
			Assert::AreEqual(expectedI.Y(), projectionI.Y());
			Assert::AreEqual(expectedI.Z(), projectionI.Z());
		}

		TEST_METHOD(ReflectTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(0.5f, -0.5f, 0.f);
			auto normalF = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
			auto reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.5f, reflectionF.X());
			Assert::AreEqual(0.5f, reflectionF.Y());
			Assert::AreEqual(0.f, reflectionF.Z());

			vectorF.Set(0.f, 5.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.X());
			Assert::AreEqual(-5.f, reflectionF.Y());
			Assert::AreEqual(0.f, reflectionF.Z());

			vectorF.Set(0.f, -4.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.X());
			Assert::AreEqual(4.f, reflectionF.Y());
			Assert::AreEqual(0.f, reflectionF.Z());

			vectorF.Set(3.f, 0.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(3.f, reflectionF.X());
			Assert::AreEqual(0.f, reflectionF.Y());
			Assert::AreEqual(0.f, reflectionF.Z());

			vectorF.Set(-14.f, 39.f, -1.f);
			normalF.Set(10.f, -17.f, -34.f);
			normalF.Normalize();
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			auto expectedF = vectorF - 2.f * PonyEngine::Math::Dot(vectorF, normalF) * normalF;
			Assert::AreEqual(expectedF.X(), reflectionF.X());
			Assert::AreEqual(expectedF.Y(), reflectionF.Y());
			Assert::AreEqual(expectedF.Z(), reflectionF.Z());

			auto vectorI = PonyEngine::Math::Vector3<short>(1, -1, 0);
			auto normalI = PonyEngine::Math::Vector3<short>(0, 1, 0);
			auto reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{1}, reflectionI.X());
			Assert::AreEqual(short{1}, reflectionI.Y());
			Assert::AreEqual(short{0}, reflectionI.Z());

			vectorI.Set(0, 5, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.X());
			Assert::AreEqual(short{-5}, reflectionI.Y());
			Assert::AreEqual(short{0}, reflectionI.Z());

			vectorI.Set(0, -4, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.X());
			Assert::AreEqual(short{4}, reflectionI.Y());
			Assert::AreEqual(short{0}, reflectionI.Z());

			vectorI.Set(3, 0, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{3}, reflectionI.X());
			Assert::AreEqual(short{0}, reflectionI.Y());
			Assert::AreEqual(short{0}, reflectionI.Z());
		}

		TEST_METHOD(ScaleTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector3<float>(-2.f, 2.f, 4.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, -8.f);

			auto scaledF = PonyEngine::Math::Scale(vectorF0, vectorF1);
			Assert::AreEqual(-4.f, scaledF.X());
			Assert::AreEqual(8.f, scaledF.Y());
			Assert::AreEqual(-32.f, scaledF.Z());

			auto vectorI0 = PonyEngine::Math::Vector3<short>(-2, 2, 4);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(2, 4, -8);
			auto scaledI = PonyEngine::Math::Scale(vectorI0, vectorI1);
			Assert::AreEqual(short{-4}, scaledI.X());
			Assert::AreEqual(short{8}, scaledI.Y());
			Assert::AreEqual(short{-32}, scaledI.Z());

			vectorF0.Scale(vectorF1);
			Assert::AreEqual(scaledF.X(), vectorF0.X());
			Assert::AreEqual(scaledF.Y(), vectorF0.Y());
			Assert::AreEqual(scaledF.Z(), vectorF0.Z());

			vectorI0.Scale(vectorI1);
			Assert::AreEqual(scaledI.X(), vectorI0.X());
			Assert::AreEqual(scaledI.Y(), vectorI0.Y());
			Assert::AreEqual(scaledI.Z(), vectorI0.Z());
		}

		TEST_METHOD(LerpTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector3<float>(-2.f, 2.f, 4.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, -8.f);
			auto lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.f);
			Assert::AreEqual(vectorF0.X(), lerpedF.X());
			Assert::AreEqual(vectorF0.Y(), lerpedF.Y());
			Assert::AreEqual(vectorF0.Z(), lerpedF.Z());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 1.f);
			Assert::AreEqual(vectorF1.X(), lerpedF.X());
			Assert::AreEqual(vectorF1.Y(), lerpedF.Y());
			Assert::AreEqual(vectorF1.Z(), lerpedF.Z());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.5f);
			Assert::AreEqual(0.f, lerpedF.X());
			Assert::AreEqual(3.f, lerpedF.Y());
			Assert::AreEqual(-2.f, lerpedF.Z());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 2.f);
			Assert::AreEqual(6.f, lerpedF.X());
			Assert::AreEqual(6.f, lerpedF.Y());
			Assert::AreEqual(-20.f, lerpedF.Z());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, -1.f);
			Assert::AreEqual(-6.f, lerpedF.X());
			Assert::AreEqual(0.f, lerpedF.Y());
			Assert::AreEqual(16.f, lerpedF.Z());

			auto vectorI0 = PonyEngine::Math::Vector3<short>(-2, 2, 4);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(2, 4, -8);
			auto lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.f);
			Assert::AreEqual(vectorI0.X(), lerpedI.X());
			Assert::AreEqual(vectorI0.Y(), lerpedI.Y());
			Assert::AreEqual(vectorI0.Z(), lerpedI.Z());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 1.f);
			Assert::AreEqual(vectorI1.X(), lerpedI.X());
			Assert::AreEqual(vectorI1.Y(), lerpedI.Y());
			Assert::AreEqual(vectorI1.Z(), lerpedI.Z());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.5f);
			Assert::AreEqual(short{0}, lerpedI.X());
			Assert::AreEqual(short{3}, lerpedI.Y());
			Assert::AreEqual(short{-2}, lerpedI.Z());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 2.f);
			Assert::AreEqual(short{6}, lerpedI.X());
			Assert::AreEqual(short{6}, lerpedI.Y());
			Assert::AreEqual(short{-20}, lerpedI.Z());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, -1.f);
			Assert::AreEqual(short{-6}, lerpedI.X());
			Assert::AreEqual(short{0}, lerpedI.Y());
			Assert::AreEqual(short{16}, lerpedI.Z());
		}

		TEST_METHOD(AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f);
			auto vector1 = vector0;

			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.X() = std::nextafter(vector1.X(), 0.f);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1));

			vector1.X() = 0.f;
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(vector0, vector1, 5.f));

			Assert::IsFalse(PonyEngine::Math::AreAlmostEqual(vector0, vector1));
		}

		TEST_METHOD(EqualityOperatorsTest)
		{
			float xf = 10.f;
			float yf = 15.f;
			float zf = -7.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			vectorF1.Z() *= 2.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.Z() = zf;
			vectorF1.Y() *= 3.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.Y() = yf;
			vectorF1.X() *= 0.5f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF.Y() *= 3.5f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF.Z() *= 0.2f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF = vectorF1;
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			short xi = 10;
			short yi = 15;
			short zi = -7;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::IsTrue(vectorI == vectorI1);
			Assert::IsFalse(vectorI != vectorI1);

			vectorI1.Z() *= 2;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.Z() = zi;
			vectorI1.Y() *= 3;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.Y() = yi;
			vectorI1.X() *= 5;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI.Y() *= 3;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI.Z() *= 2;
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
			float zf = -80.f;
			float xf1 = -75.f;
			float yf1 = 60.f;
			float zf1 = -95.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);

			auto vectorF2 = vectorF + vectorF1;
			Assert::AreEqual(xf + xf1, vectorF2.X());
			Assert::AreEqual(yf + yf1, vectorF2.Y());
			Assert::AreEqual(zf + zf1, vectorF2.Z());

			vectorF2 = vectorF - vectorF1;
			Assert::AreEqual(xf - xf1, vectorF2.X());
			Assert::AreEqual(yf - yf1, vectorF2.Y());
			Assert::AreEqual(zf - zf1, vectorF2.Z());

			float multiplier = 3.3f;
			vectorF2 = vectorF * multiplier;
			Assert::AreEqual(xf * multiplier, vectorF2.X());
			Assert::AreEqual(yf * multiplier, vectorF2.Y());
			Assert::AreEqual(zf * multiplier, vectorF2.Z());

			vectorF2 = multiplier * vectorF;
			Assert::AreEqual(xf * multiplier, vectorF2.X());
			Assert::AreEqual(yf * multiplier, vectorF2.Y());
			Assert::AreEqual(zf * multiplier, vectorF2.Z());

			vectorF2 = vectorF / multiplier;
			Assert::AreEqual(xf / multiplier, vectorF2.X());
			Assert::AreEqual(yf / multiplier, vectorF2.Y());
			Assert::AreEqual(zf / multiplier, vectorF2.Z());

			short xi = 90;
			short yi = 100;
			short zi = -80;
			short xi1 = -75;
			short yi1 = 60;
			short zi1 = -95;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);

			auto vectorI2 = vectorI + vectorI1;
			Assert::AreEqual(static_cast<short>(xi + xi1), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), vectorI2.Z());

			vectorI2 = vectorI - vectorI1;
			Assert::AreEqual(static_cast<short>(xi - xi1), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), vectorI2.Z());

			short multiplierI = short{3};
			vectorI2 = vectorI * multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.Z());

			vectorI2 = vectorI * multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.Z());

			vectorI2 = multiplierI * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.Z());

			vectorI2 = multiplier * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.Z());

			vectorI2 = vectorI / multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), vectorI2.Z());
		}

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

		TEST_METHOD(ConstexprTest)
		{
			constexpr auto defaultVector = PonyEngine::Math::Vector3<float>();
			constexpr auto vector = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
			constexpr PonyEngine::Math::Vector3<float> copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);

			constexpr auto x = vector.X();
			constexpr auto y = vector.Y();
			constexpr auto z = vector.Z();

			static constexpr PonyEngine::Math::Vector3<float> StaticVector(0.f, 1.f, 0.f);
			constexpr auto pointer = StaticVector.Data();

			constexpr auto forward = PonyEngine::Math::Vector3Forward<float>;
			Assert::AreEqual(0.f, forward.X());
			Assert::AreEqual(0.f, forward.Y());
			Assert::AreEqual(1.f, forward.Z());
			constexpr auto back = PonyEngine::Math::Vector3Back<float>;
			Assert::AreEqual(0.f, back.X());
			Assert::AreEqual(0.f, back.Y());
			Assert::AreEqual(-1.f, back.Z());
			constexpr auto up = PonyEngine::Math::Vector3Up<float>;
			Assert::AreEqual(0.f, up.X());
			Assert::AreEqual(1.f, up.Y());
			Assert::AreEqual(0.f, up.Z());
			constexpr auto down = PonyEngine::Math::Vector3Down<float>;
			Assert::AreEqual(0.f, down.X());
			Assert::AreEqual(-1.f, down.Y());
			Assert::AreEqual(0.f, down.Z());
			constexpr auto right = PonyEngine::Math::Vector3Right<float>;
			Assert::AreEqual(1.f, right.X());
			Assert::AreEqual(0.f, right.Y());
			Assert::AreEqual(0.f, right.Z());
			constexpr auto left = PonyEngine::Math::Vector3Left<float>;
			Assert::AreEqual(-1.f, left.X());
			Assert::AreEqual(0.f, left.Y());
			Assert::AreEqual(0.f, left.Z());
			constexpr auto one = PonyEngine::Math::Vector3One<float>;
			Assert::AreEqual(1.f, one.X());
			Assert::AreEqual(1.f, one.Y());
			Assert::AreEqual(1.f, one.Z());
			constexpr auto zero = PonyEngine::Math::Vector3Zero<float>;
			Assert::AreEqual(0.f, zero.X());
			Assert::AreEqual(0.f, zero.Y());
			Assert::AreEqual(0.f, zero.Z());
			constexpr auto negative = PonyEngine::Math::Vector3Negative<float>;
			Assert::AreEqual(-1.f, negative.X());
			Assert::AreEqual(-1.f, negative.Y());
			Assert::AreEqual(-1.f, negative.Z());

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr std::size_t size = vector.ComponentCount;

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto cross = PonyEngine::Math::Cross(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
			constexpr auto projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, normal);
			constexpr auto reflection = PonyEngine::Math::Reflect(vector, normal);
			constexpr auto lerped = PonyEngine::Math::Lerp(vector, copiedVector, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, copiedVector);

			constexpr auto component = vector[1];

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negated = -vector;
			constexpr auto sub = vector - copiedVector;
			constexpr auto multiplied = vector * 3.f;
			constexpr auto multipliedL = 3.f * vector;
			constexpr auto scaled = PonyEngine::Math::Scale(vector, normal);
			constexpr auto divided = vector / 3.f;

			constexpr auto intVector = PonyEngine::Math::Vector3<int>();
			constexpr auto multipliedI = intVector * 3;
			constexpr auto multipliedLI = 3 * intVector;
			constexpr auto multipliedIF = intVector * 3.f;
			constexpr auto multipliedLIF = 3.f * intVector;
		}
	};
}
