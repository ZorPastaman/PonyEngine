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
	TEST_CLASS(Vector4Tests)
	{
		TEST_METHOD(ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector4<float>();
			Assert::AreEqual(float{}, defaultFloatVector.X());
			Assert::AreEqual(float{}, defaultFloatVector.Y());
			Assert::AreEqual(float{}, defaultFloatVector.Z());
			Assert::AreEqual(float{}, defaultFloatVector.W());

			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;
			float wf = -6.f;

			auto floatVector = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(xf, floatVector.X());
			Assert::AreEqual(yf, floatVector.Y());
			Assert::AreEqual(zf, floatVector.Z());
			Assert::AreEqual(wf, floatVector.W());

			PonyEngine::Math::Vector4<float> copiedFloatVector = floatVector;
			Assert::AreEqual(xf, copiedFloatVector.X());
			Assert::AreEqual(yf, copiedFloatVector.Y());
			Assert::AreEqual(zf, copiedFloatVector.Z());
			Assert::AreEqual(wf, copiedFloatVector.W());

			PonyEngine::Math::Vector4<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(xf, movedFloatVector.X());
			Assert::AreEqual(yf, movedFloatVector.Y());
			Assert::AreEqual(zf, movedFloatVector.Z());
			Assert::AreEqual(wf, movedFloatVector.W());

			auto defaultShortVector = PonyEngine::Math::Vector4<short>();
			Assert::AreEqual(short{}, defaultShortVector.X());
			Assert::AreEqual(short{}, defaultShortVector.Y());
			Assert::AreEqual(short{}, defaultShortVector.Z());
			Assert::AreEqual(short{}, defaultShortVector.W());

			short xi = 4;
			short yi = -14;
			short zi = 7;
			short wi = -6;

			auto shortVector = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, shortVector.X());
			Assert::AreEqual(yi, shortVector.Y());
			Assert::AreEqual(zi, shortVector.Z());
			Assert::AreEqual(wi, shortVector.W());

			PonyEngine::Math::Vector4<short> copiedShortVector = shortVector;
			Assert::AreEqual(xi, copiedShortVector.X());
			Assert::AreEqual(yi, copiedShortVector.Y());
			Assert::AreEqual(zi, copiedShortVector.Z());
			Assert::AreEqual(wi, copiedShortVector.W());

			PonyEngine::Math::Vector4<short> movedShortVector = std::move(shortVector);
			Assert::AreEqual(xi, movedShortVector.X());
			Assert::AreEqual(yi, movedShortVector.Y());
			Assert::AreEqual(zi, movedShortVector.Z());
			Assert::AreEqual(wi, movedShortVector.W());
		}

		TEST_METHOD(DataTest)
		{
			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;
			float wf = -6.f;
			auto floatVector = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(floatVector.X(), floatVector.Data()[0]);
			Assert::AreEqual(floatVector.Y(), floatVector.Data()[1]);
			Assert::AreEqual(floatVector.Z(), floatVector.Data()[2]);
			Assert::AreEqual(floatVector.W(), floatVector.Data()[3]);

			short xi = 4;
			short yi = -14;
			short zi = 7;
			short wi = -6;
			auto shortVector = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(shortVector.X(), shortVector.Data()[0]);
			Assert::AreEqual(shortVector.Y(), shortVector.Data()[1]);
			Assert::AreEqual(shortVector.Z(), shortVector.Data()[2]);
			Assert::AreEqual(shortVector.W(), shortVector.Data()[3]);
		}

		TEST_METHOD(MagnitudeTest)
		{
			float xf = 7.f;
			float yf = -17.f;
			float zf = -43.f;
			float wf = 11.f;
			float magnitudeSquaredF = std::pow(xf, 2.f) + std::pow(yf, 2.f) + std::pow(zf, 2.f) + std::pow(wf, 2.f);
			float magnitudeF = std::sqrt(magnitudeSquaredF);
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);

			Assert::AreEqual(magnitudeSquaredF, vectorF.MagnitudeSquared());
			Assert::AreEqual(magnitudeF, vectorF.Magnitude());

			Assert::AreEqual(0.f, PonyEngine::Math::Vector4Zero<float>.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector4Zero<float>.Magnitude());

			short xi = 7;
			short yi = -17;
			short zi = -43;
			short wi = 11;
			short magnitudeSquaredI = static_cast<short>(xi * xi + yi * yi + zi * zi + wi * wi);
			float magnitudeI = std::sqrt(static_cast<float>(magnitudeSquaredI));
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);

			Assert::AreEqual(magnitudeSquaredI, vectorI.MagnitudeSquared());
			Assert::AreEqual(magnitudeI, vectorI.Magnitude());

			Assert::AreEqual(short{0}, PonyEngine::Math::Vector4Zero<short>.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector4Zero<short>.Magnitude());
		}

		TEST_METHOD(NormalizationTest)
		{
			float xf = -5.f;
			float yf = 15.f;
			float zf = 7.f;
			float wf = 14.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			float magnitudeF = vectorF.Magnitude();
			float normXF = xf / magnitudeF;
			float normYF = yf / magnitudeF;
			float normZF = zf / magnitudeF;
			float normWF = wf / magnitudeF;
			auto normVectorF = vectorF.Normalized();

			Assert::AreEqual(static_cast<double>(normXF), static_cast<double>(normVectorF.X()), 0.00001);
			Assert::AreEqual(static_cast<double>(normYF), static_cast<double>(normVectorF.Y()), 0.00001);
			Assert::AreEqual(static_cast<double>(normZF), static_cast<double>(normVectorF.Z()), 0.00001);
			Assert::AreEqual(static_cast<double>(normWF), static_cast<double>(normVectorF.W()), 0.00001);

			vectorF.Normalize();
			Assert::AreEqual(static_cast<double>(normVectorF.X()), static_cast<double>(vectorF.X()), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.Y()), static_cast<double>(vectorF.Y()), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.Z()), static_cast<double>(vectorF.Z()), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.W()), static_cast<double>(vectorF.W()), 0.00001);

			auto zeroNormalizedF = PonyEngine::Math::Vector4Zero<float>.Normalized();
			Assert::IsFalse(std::isnormal(zeroNormalizedF.X()));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.Y()));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.Z()));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.W()));

			short xi = -5;
			short yi = 15;
			short zi = 7;
			short wi = 14;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			float magnitudeI = vectorI.Magnitude();
			short normXI = static_cast<short>(xi / magnitudeI);
			short normYI = static_cast<short>(yi / magnitudeI);
			short normZI = static_cast<short>(zi / magnitudeI);
			short normWI = static_cast<short>(wi / magnitudeI);
			auto normVectorI = vectorI.Normalized();

			Assert::AreEqual(normXI, normVectorI.X());
			Assert::AreEqual(normYI, normVectorI.Y());
			Assert::AreEqual(normZI, normVectorI.Z());
			Assert::AreEqual(normWI, normVectorI.W());

			vectorI.Normalize();
			Assert::AreEqual(normVectorI.X(), vectorI.X());
			Assert::AreEqual(normVectorI.Y(), vectorI.Y());
			Assert::AreEqual(normVectorI.Z(), vectorI.Z());
			Assert::AreEqual(normVectorI.W(), vectorI.W());

			auto zeroNormalizedI = PonyEngine::Math::Vector4Zero<short>.Normalized();
			Assert::AreEqual(short{0}, zeroNormalizedI.X());
			Assert::AreEqual(short{0}, zeroNormalizedI.Y());
			Assert::AreEqual(short{0}, zeroNormalizedI.Z());
			Assert::AreEqual(short{0}, zeroNormalizedI.W());
		}

		TEST_METHOD(InverseTest)
		{
			float xf = -5.f;
			float yf = 15.f;
			float zf = 7.f;
			float wf = 14.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			auto inversedF = vectorF.Swapped();
			Assert::AreEqual(wf, inversedF.X());
			Assert::AreEqual(zf, inversedF.Y());
			Assert::AreEqual(yf, inversedF.Z());
			Assert::AreEqual(xf, inversedF.W());

			short xi = -5;
			short yi = 15;
			short zi = 7;
			short wi = 14;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			auto swappedI = vectorI.Swapped();
			Assert::AreEqual(wi, swappedI.X());
			Assert::AreEqual(zi, swappedI.Y());
			Assert::AreEqual(yi, swappedI.Z());
			Assert::AreEqual(xi, swappedI.W());
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4Zero<float>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector4One<float>.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector4<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.X() = 0.f;
			vector.Y() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.Y() = 0.f;
			vector.Z() = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.Z() = 0.f;
			vector.W() = nan;
			Assert::IsFalse(vector.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Vector4Zero<short>.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector4One<short>.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			auto vectorF = PonyEngine::Math::Vector4<float>();
			float xf = 3.f;
			float yf = -7.f;
			float zf = 5.f;
			float wf = -18.f;
			vectorF.Set(xf, yf, zf, wf);
			Assert::AreEqual(xf, vectorF.X());
			Assert::AreEqual(yf, vectorF.Y());
			Assert::AreEqual(zf, vectorF.Z());
			Assert::AreEqual(wf, vectorF.W());

			auto vectorI = PonyEngine::Math::Vector4<short>();
			short xi = 3;
			short yi = -7;
			short zi = 5;
			short wi = -18;
			vectorI.Set(xi, yi, zi, wi);
			Assert::AreEqual(xi, vectorI.X());
			Assert::AreEqual(yi, vectorI.Y());
			Assert::AreEqual(zi, vectorI.Z());
			Assert::AreEqual(wi, vectorI.W());
		}

		TEST_METHOD(ToStringTest)
		{
			float xf = 3.f;
			float yf = 2.f;
			float zf = -1.f;
			float wf = -5.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			std::string expected = std::format("({}, {}, {}, {})", xf, yf, zf, wf);
			std::string vectorString = vectorF.ToString();
			Assert::AreEqual(expected, vectorString);

			std::ostringstream ssF;
			ssF << vectorF;
			Assert::AreEqual(expected, ssF.str());

			short xi = 3;
			short yi = 2;
			short zi = -1;
			short wi = -5;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			expected = std::format("({}, {}, {}, {})", xi, yi, zi, wi);
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
			float wf = -7.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(xf, vectorF[0]);
			Assert::AreEqual(yf, vectorF[1]);
			Assert::AreEqual(zf, vectorF[2]);
			Assert::AreEqual(wf, vectorF[3]);

			float xf1 = 20.f;
			float yf1 = -34.f;
			float zf1 = 55.f;
			float wf1 = -30.f;
			vectorF[0] = xf1;
			vectorF[1] = yf1;
			vectorF[2] = zf1;
			vectorF[3] = wf1;
			Assert::AreEqual(xf1, vectorF[0]);
			Assert::AreEqual(yf1, vectorF[1]);
			Assert::AreEqual(zf1, vectorF[2]);
			Assert::AreEqual(wf1, vectorF[3]);

			const auto vectorFC = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(xf, vectorFC[0]);
			Assert::AreEqual(yf, vectorFC[1]);
			Assert::AreEqual(zf, vectorFC[2]);
			Assert::AreEqual(wf, vectorFC[3]);

			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Vector4<float>::ComponentCount);

			short xi = 2;
			short yi = -5;
			short zi = 7;
			short wi = -7;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, vectorI[0]);
			Assert::AreEqual(yi, vectorI[1]);
			Assert::AreEqual(zi, vectorI[2]);
			Assert::AreEqual(wi, vectorI[3]);

			short xi1 = 20;
			short yi1 = -34;
			short zi1 = 55;
			short wi1 = -40;
			vectorI[0] = xi1;
			vectorI[1] = yi1;
			vectorI[2] = zi1;
			vectorI[3] = wi1;
			Assert::AreEqual(xi1, vectorI[0]);
			Assert::AreEqual(yi1, vectorI[1]);
			Assert::AreEqual(zi1, vectorI[2]);
			Assert::AreEqual(wi1, vectorI[3]);

			const auto vectorIC = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, vectorIC[0]);
			Assert::AreEqual(yi, vectorIC[1]);
			Assert::AreEqual(zi, vectorIC[2]);
			Assert::AreEqual(wi, vectorIC[3]);

			Assert::AreEqual(std::size_t{4}, PonyEngine::Math::Vector4<short>::ComponentCount);
		}

		TEST_METHOD(AssignmentOperatorsTest)
		{
			PonyEngine::Math::Vector4<float> leftF, centralF, rightF;
			float xf = 8.f;
			float yf = 22.f;
			float zf = -98.f;
			float wf = 23.f;

			leftF = centralF = rightF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(xf, leftF.X());
			Assert::AreEqual(xf, centralF.X());
			Assert::AreEqual(xf, rightF.X());
			Assert::AreEqual(yf, leftF.Y());
			Assert::AreEqual(yf, centralF.Y());
			Assert::AreEqual(yf, rightF.Y());
			Assert::AreEqual(zf, leftF.Z());
			Assert::AreEqual(zf, centralF.Z());
			Assert::AreEqual(zf, rightF.Z());
			Assert::AreEqual(wf, leftF.W());
			Assert::AreEqual(wf, centralF.W());
			Assert::AreEqual(wf, rightF.W());

			float xf1 = 6.f;
			float yf1 = -90.f;
			float zf1 = 32.f;
			float wf1 = -87.f;
			rightF = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);
			leftF = centralF += rightF;
			Assert::AreEqual(xf + xf1, leftF.X());
			Assert::AreEqual(yf + yf1, leftF.Y());
			Assert::AreEqual(zf + zf1, leftF.Z());
			Assert::AreEqual(wf + wf1, leftF.W());
			Assert::AreEqual(xf + xf1, centralF.X());
			Assert::AreEqual(yf + yf1, centralF.Y());
			Assert::AreEqual(zf + zf1, centralF.Z());
			Assert::AreEqual(wf + wf1, centralF.W());

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			rightF = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);
			leftF = centralF -= rightF;
			Assert::AreEqual(xf - xf1, leftF.X());
			Assert::AreEqual(yf - yf1, leftF.Y());
			Assert::AreEqual(zf - zf1, leftF.Z());
			Assert::AreEqual(wf - wf1, leftF.W());
			Assert::AreEqual(xf - xf1, centralF.X());
			Assert::AreEqual(yf - yf1, centralF.Y());
			Assert::AreEqual(zf - zf1, centralF.Z());
			Assert::AreEqual(wf - wf1, centralF.W());

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			float multiplier = 3.f;
			leftF = centralF *= multiplier;
			Assert::AreEqual(xf * multiplier, leftF.X());
			Assert::AreEqual(yf * multiplier, leftF.Y());
			Assert::AreEqual(zf * multiplier, leftF.Z());
			Assert::AreEqual(wf * multiplier, leftF.W());
			Assert::AreEqual(xf * multiplier, centralF.X());
			Assert::AreEqual(yf * multiplier, centralF.Y());
			Assert::AreEqual(zf * multiplier, centralF.Z());
			Assert::AreEqual(wf * multiplier, centralF.W());

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			leftF = centralF /= multiplier;
			Assert::AreEqual(xf / multiplier, leftF.X());
			Assert::AreEqual(yf / multiplier, leftF.Y());
			Assert::AreEqual(zf / multiplier, leftF.Z());
			Assert::AreEqual(wf / multiplier, leftF.W());
			Assert::AreEqual(xf / multiplier, centralF.X());
			Assert::AreEqual(yf / multiplier, centralF.Y());
			Assert::AreEqual(zf / multiplier, centralF.Z());
			Assert::AreEqual(wf / multiplier, centralF.W());

			PonyEngine::Math::Vector4<short> leftI, centralI, rightI;
			short xi = 8;
			short yi = 22;
			short zi = -98;
			short wi = -42;

			leftI = centralI = rightI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, leftI.X());
			Assert::AreEqual(xi, centralI.X());
			Assert::AreEqual(xi, rightI.X());
			Assert::AreEqual(yi, leftI.Y());
			Assert::AreEqual(yi, centralI.Y());
			Assert::AreEqual(yi, rightI.Y());
			Assert::AreEqual(zi, leftI.Z());
			Assert::AreEqual(zi, centralI.Z());
			Assert::AreEqual(zi, rightI.Z());
			Assert::AreEqual(wi, leftI.W());
			Assert::AreEqual(wi, centralI.W());
			Assert::AreEqual(wi, rightI.W());

			short xi1 = 6;
			short yi1 = -90;
			short zi1 = 32;
			short wi1 = -77;
			rightI = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);
			leftI = centralI += rightI;
			Assert::AreEqual(static_cast<short>(xi + xi1), leftI.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), leftI.Z());
			Assert::AreEqual(static_cast<short>(wi + wi1), leftI.W());
			Assert::AreEqual(static_cast<short>(xi + xi1), centralI.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), centralI.Z());
			Assert::AreEqual(static_cast<short>(wi + wi1), centralI.W());

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			rightI = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);
			leftI = centralI -= rightI;
			Assert::AreEqual(static_cast<short>(xi - xi1), leftI.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), leftI.Z());
			Assert::AreEqual(static_cast<short>(wi - wi1), leftI.W());
			Assert::AreEqual(static_cast<short>(xi - xi1), centralI.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), centralI.Z());
			Assert::AreEqual(static_cast<short>(wi - wi1), centralI.W());

			short multiplierI = short{3};
			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI *= multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), leftI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), leftI.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplierI), leftI.W());
			Assert::AreEqual(static_cast<short>(xi * multiplierI), centralI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), centralI.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplierI), centralI.W());

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI *= multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), leftI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), leftI.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplier), leftI.W());
			Assert::AreEqual(static_cast<short>(xi * multiplier), centralI.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), centralI.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplier), centralI.W());

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI /= multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), leftI.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), leftI.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), leftI.Z());
			Assert::AreEqual(static_cast<short>(wi / multiplier), leftI.W());
			Assert::AreEqual(static_cast<short>(xi / multiplier), centralI.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), centralI.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), centralI.Z());
			Assert::AreEqual(static_cast<short>(wi / multiplier), centralI.W());
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4One<float> == PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector4Zero<float> == PonyEngine::Math::Vector4<float>(0.f, 0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector4Negative<float> == PonyEngine::Math::Vector4<float>(-1.f, -1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector4One<short> == PonyEngine::Math::Vector4<short>(1, 1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector4Zero<short> == PonyEngine::Math::Vector4<short>(0, 0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector4Negative<short> == PonyEngine::Math::Vector4<short>(-1, -1, -1, -1));
		}

		TEST_METHOD(DotTest)
		{
			float xf = 5.f;
			float yf = -1.f;
			float zf = -15.f;
			float wf = 6.f;
			float xf1 = 14.f;
			float yf1 = 100.f;
			float zf1 = -2.f;
			float wf1 = 10.f;
			float dotF = xf * xf1 + yf * yf1 + zf * zf1 + wf * wf1;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);

			float vectorDotF = PonyEngine::Math::Dot(vectorF, vectorF1);
			Assert::AreEqual(dotF, vectorDotF);

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4Zero<float>, PonyEngine::Math::Vector4Zero<float>));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4One<float>.Normalized(), PonyEngine::Math::Vector4One<float>.Normalized()));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4One<float>.Normalized(), PonyEngine::Math::Vector4Negative<float>.Normalized()));

			short xi = 5;
			short yi = -1;
			short zi = -15;
			short wi = 6;
			short xi1 = 14;
			short yi1 = 100;
			short zi1 = -2;
			short wi1 = 10;
			float dotI = static_cast<float>(xi) * xi1 + static_cast<float>(yi) * yi1 + static_cast<float>(zi) * zi1 + static_cast<float>(wi) * wi1;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);

			float vectorDotI = PonyEngine::Math::Dot(vectorI, vectorI1);
			Assert::AreEqual(dotI, vectorDotI);

			Assert::AreEqual(short{0}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4Zero<short>, PonyEngine::Math::Vector4Zero<short>));
			Assert::AreEqual(short{4}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4One<short>, PonyEngine::Math::Vector4One<short>));
			Assert::AreEqual(short{-4}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4One<short>, PonyEngine::Math::Vector4Negative<short>));
		}

		TEST_METHOD(ProjectTest)
		{
			auto vectorF = PonyEngine::Math::Vector4<float>(3.f, 0.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(0.f, 0.f, 3.f, 0.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorF, vectorF1).Magnitude());

			vectorF.Set(-4.f, 2.f, 7.f, 10.f);
			vectorF1.Set(3.f, 1.f, 2.f, 5.f);
			auto projectedF = PonyEngine::Math::Project(vectorF, vectorF1);
			Assert::AreEqual(4.154, static_cast<double>(projectedF.X()), 0.001);
			Assert::AreEqual(1.385, static_cast<double>(projectedF.Y()), 0.001);
			Assert::AreEqual(2.769, static_cast<double>(projectedF.Z()), 0.001);
			Assert::AreEqual(6.923, static_cast<double>(projectedF.W()), 0.001);

			auto vectorI = PonyEngine::Math::Vector4<short>(3, 0, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(0, 0, 3, 0);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorI, vectorI1).Magnitude());

			vectorI.Set(2, 2, 7, 10);
			vectorI1.Set(3, 1, 0, 5);
			auto projectedI = PonyEngine::Math::Project(vectorI, vectorI1);
			Assert::AreEqual(short{4}, projectedI.X());
			Assert::AreEqual(short{1}, projectedI.Y());
			Assert::AreEqual(short{0}, projectedI.Z());
			Assert::AreEqual(short{8}, projectedI.W());
		}

		TEST_METHOD(ScaleTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector4<float>(-2.f, 2.f, 4.f, 6.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(2.f, 4.f, -8.f, 10.f);

			auto scaledF = PonyEngine::Math::Scale(vectorF0, vectorF1);
			Assert::AreEqual(-4.f, scaledF.X());
			Assert::AreEqual(8.f, scaledF.Y());
			Assert::AreEqual(-32.f, scaledF.Z());
			Assert::AreEqual(60.f, scaledF.W());

			auto vectorI0 = PonyEngine::Math::Vector4<short>(-2, 2, 4, 6);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(2, 4, -8, 10);
			auto scaledI = PonyEngine::Math::Scale(vectorI0, vectorI1);
			Assert::AreEqual(short{-4}, scaledI.X());
			Assert::AreEqual(short{8}, scaledI.Y());
			Assert::AreEqual(short{-32}, scaledI.Z());
			Assert::AreEqual(short{60}, scaledI.W());

			vectorF0.Scale(vectorF1);
			Assert::AreEqual(scaledF.X(), vectorF0.X());
			Assert::AreEqual(scaledF.Y(), vectorF0.Y());
			Assert::AreEqual(scaledF.Z(), vectorF0.Z());
			Assert::AreEqual(scaledF.W(), vectorF0.W());

			vectorI0.Scale(vectorI1);
			Assert::AreEqual(scaledI.X(), vectorI0.X());
			Assert::AreEqual(scaledI.Y(), vectorI0.Y());
			Assert::AreEqual(scaledI.Z(), vectorI0.Z());
			Assert::AreEqual(scaledI.W(), vectorI0.W());
		}

		TEST_METHOD(LerpTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector4<float>(-2.f, 2.f, 4.f, 6.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(2.f, 4.f, -8.f, 10.f);
			auto lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.f);
			Assert::AreEqual(vectorF0.X(), lerpedF.X());
			Assert::AreEqual(vectorF0.Y(), lerpedF.Y());
			Assert::AreEqual(vectorF0.Z(), lerpedF.Z());
			Assert::AreEqual(vectorF0.W(), lerpedF.W());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 1.f);
			Assert::AreEqual(vectorF1.X(), lerpedF.X());
			Assert::AreEqual(vectorF1.Y(), lerpedF.Y());
			Assert::AreEqual(vectorF1.Z(), lerpedF.Z());
			Assert::AreEqual(vectorF1.W(), lerpedF.W());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.5f);
			Assert::AreEqual(0.f, lerpedF.X());
			Assert::AreEqual(3.f, lerpedF.Y());
			Assert::AreEqual(-2.f, lerpedF.Z());
			Assert::AreEqual(8.f, lerpedF.W());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 2.f);
			Assert::AreEqual(6.f, lerpedF.X());
			Assert::AreEqual(6.f, lerpedF.Y());
			Assert::AreEqual(-20.f, lerpedF.Z());
			Assert::AreEqual(14.f, lerpedF.W());

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, -1.f);
			Assert::AreEqual(-6.f, lerpedF.X());
			Assert::AreEqual(0.f, lerpedF.Y());
			Assert::AreEqual(16.f, lerpedF.Z());
			Assert::AreEqual(2.f, lerpedF.W());

			auto vectorI0 = PonyEngine::Math::Vector4<short>(-2, 2, 4, 6);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(2, 4, -8, 10);
			auto lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.f);
			Assert::AreEqual(vectorI0.X(), lerpedI.X());
			Assert::AreEqual(vectorI0.Y(), lerpedI.Y());
			Assert::AreEqual(vectorI0.Z(), lerpedI.Z());
			Assert::AreEqual(vectorI0.W(), lerpedI.W());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 1.f);
			Assert::AreEqual(vectorI1.X(), lerpedI.X());
			Assert::AreEqual(vectorI1.Y(), lerpedI.Y());
			Assert::AreEqual(vectorI1.Z(), lerpedI.Z());
			Assert::AreEqual(vectorI1.W(), lerpedI.W());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.5f);
			Assert::AreEqual(short{0}, lerpedI.X());
			Assert::AreEqual(short{3}, lerpedI.Y());
			Assert::AreEqual(short{-2}, lerpedI.Z());
			Assert::AreEqual(short{8}, lerpedI.W());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 2.f);
			Assert::AreEqual(short{6}, lerpedI.X());
			Assert::AreEqual(short{6}, lerpedI.Y());
			Assert::AreEqual(short{-20}, lerpedI.Z());
			Assert::AreEqual(short{14}, lerpedI.W());

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, -1.f);
			Assert::AreEqual(short{-6}, lerpedI.X());
			Assert::AreEqual(short{0}, lerpedI.Y());
			Assert::AreEqual(short{16}, lerpedI.Z());
			Assert::AreEqual(short{2}, lerpedI.W());
		}

		TEST_METHOD(AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f);
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
			float wf = -8.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			vectorF1.W() *= 4.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.W() = wf;
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
			short wi = -8;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::IsTrue(vectorI == vectorI1);
			Assert::IsFalse(vectorI != vectorI1);

			vectorI1.W() *= 4;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.W() = wi;
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
			float wf = 44.f;
			float xf1 = -75.f;
			float yf1 = 60.f;
			float zf1 = -95.f;
			float wf1 = -33.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);

			auto vectorF2 = vectorF + vectorF1;
			Assert::AreEqual(xf + xf1, vectorF2.X());
			Assert::AreEqual(yf + yf1, vectorF2.Y());
			Assert::AreEqual(zf + zf1, vectorF2.Z());
			Assert::AreEqual(wf + wf1, vectorF2.W());

			vectorF2 = vectorF - vectorF1;
			Assert::AreEqual(xf - xf1, vectorF2.X());
			Assert::AreEqual(yf - yf1, vectorF2.Y());
			Assert::AreEqual(zf - zf1, vectorF2.Z());
			Assert::AreEqual(wf - wf1, vectorF2.W());

			float multiplier = 3.3f;
			vectorF2 = vectorF * multiplier;
			Assert::AreEqual(xf * multiplier, vectorF2.X());
			Assert::AreEqual(yf * multiplier, vectorF2.Y());
			Assert::AreEqual(zf * multiplier, vectorF2.Z());
			Assert::AreEqual(wf * multiplier, vectorF2.W());

			vectorF2 = multiplier * vectorF;
			Assert::AreEqual(xf * multiplier, vectorF2.X());
			Assert::AreEqual(yf * multiplier, vectorF2.Y());
			Assert::AreEqual(zf * multiplier, vectorF2.Z());
			Assert::AreEqual(wf * multiplier, vectorF2.W());

			vectorF2 = vectorF / multiplier;
			Assert::AreEqual(xf / multiplier, vectorF2.X());
			Assert::AreEqual(yf / multiplier, vectorF2.Y());
			Assert::AreEqual(zf / multiplier, vectorF2.Z());
			Assert::AreEqual(wf / multiplier, vectorF2.W());

			short xi = 90;
			short yi = 100;
			short zi = -80;
			short wi = 33;
			short xi1 = -75;
			short yi1 = 60;
			short zi1 = -95;
			short wi1 = 44;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);

			auto vectorI2 = vectorI + vectorI1;
			Assert::AreEqual(static_cast<short>(xi + xi1), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi + yi1), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi + zi1), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi + wi1), vectorI2.W());

			vectorI2 = vectorI - vectorI1;
			Assert::AreEqual(static_cast<short>(xi - xi1), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi - yi1), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi - zi1), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi - wi1), vectorI2.W());

			short multiplierI = short{3};
			vectorI2 = vectorI * multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplierI), vectorI2.W());

			vectorI2 = vectorI * multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplier), vectorI2.W());

			vectorI2 = multiplierI * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplierI), vectorI2.W());

			vectorI2 = multiplier * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi * multiplier), vectorI2.W());

			vectorI2 = vectorI / multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), vectorI2.X());
			Assert::AreEqual(static_cast<short>(yi / multiplier), vectorI2.Y());
			Assert::AreEqual(static_cast<short>(zi / multiplier), vectorI2.Z());
			Assert::AreEqual(static_cast<short>(wi / multiplier), vectorI2.W());
		}

		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<char, PonyEngine::Math::Vector4<char>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<char>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<short, PonyEngine::Math::Vector4<short>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<short>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<int, PonyEngine::Math::Vector4<int>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<int>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<float>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyEngine::Math::Vector4<float>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<long long, PonyEngine::Math::Vector4<long long>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<long long>::ComputationalType>);

			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<double>::ValueType>);
			Assert::IsTrue(std::is_same_v<double, PonyEngine::Math::Vector4<double>::ComputationalType>);
		}

		TEST_METHOD(ConstexprTest)
		{
			constexpr auto defaultVector = PonyEngine::Math::Vector4<float>();
			constexpr auto vector = PonyEngine::Math::Vector4<float>(3.f, 2.f, 1.f, 3.f);
			constexpr PonyEngine::Math::Vector4<float> copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector4<float>(0.f, 1.f, 0.f, 7.f);

			constexpr auto x = vector.X();
			constexpr auto y = vector.Y();
			constexpr auto z = vector.Z();
			constexpr auto w = vector.W();

			constexpr auto one = PonyEngine::Math::Vector4One<float>;
			constexpr auto zero = PonyEngine::Math::Vector4Zero<float>;
			constexpr auto negative = PonyEngine::Math::Vector4Negative<float>;

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr std::size_t size = vector.ComponentCount;

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
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

			constexpr auto intVector = PonyEngine::Math::Vector4<int>();
			constexpr auto multipliedI = intVector * 3;
			constexpr auto multipliedLI = 3 * intVector;
			constexpr auto multipliedIF = intVector * 3.f;
			constexpr auto multipliedLIF = 3.f * intVector;
		}
	};
}
