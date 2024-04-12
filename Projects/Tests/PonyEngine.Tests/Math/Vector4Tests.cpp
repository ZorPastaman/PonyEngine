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
			Assert::AreEqual(float{}, defaultFloatVector.x);
			Assert::AreEqual(float{}, defaultFloatVector.y);
			Assert::AreEqual(float{}, defaultFloatVector.z);
			Assert::AreEqual(float{}, defaultFloatVector.w);

			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;
			float wf = -6.f;

			auto floatVector = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::AreEqual(xf, floatVector.x);
			Assert::AreEqual(yf, floatVector.y);
			Assert::AreEqual(zf, floatVector.z);
			Assert::AreEqual(wf, floatVector.w);

			PonyEngine::Math::Vector4<float> copiedFloatVector = floatVector;
			Assert::AreEqual(xf, copiedFloatVector.x);
			Assert::AreEqual(yf, copiedFloatVector.y);
			Assert::AreEqual(zf, copiedFloatVector.z);
			Assert::AreEqual(wf, copiedFloatVector.w);

			PonyEngine::Math::Vector4<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(xf, movedFloatVector.x);
			Assert::AreEqual(yf, movedFloatVector.y);
			Assert::AreEqual(zf, movedFloatVector.z);
			Assert::AreEqual(wf, movedFloatVector.w);

			auto defaultShortVector = PonyEngine::Math::Vector4<short>();
			Assert::AreEqual(short{}, defaultShortVector.x);
			Assert::AreEqual(short{}, defaultShortVector.y);
			Assert::AreEqual(short{}, defaultShortVector.z);
			Assert::AreEqual(short{}, defaultShortVector.w);

			short xi = 4;
			short yi = -14;
			short zi = 7;
			short wi = -6;

			auto shortVector = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, shortVector.x);
			Assert::AreEqual(yi, shortVector.y);
			Assert::AreEqual(zi, shortVector.z);
			Assert::AreEqual(wi, shortVector.w);

			PonyEngine::Math::Vector4<short> copiedShortVector = shortVector;
			Assert::AreEqual(xi, copiedShortVector.x);
			Assert::AreEqual(yi, copiedShortVector.y);
			Assert::AreEqual(zi, copiedShortVector.z);
			Assert::AreEqual(wi, copiedShortVector.w);

			PonyEngine::Math::Vector4<short> movedShortVector = std::move(shortVector);
			Assert::AreEqual(xi, movedShortVector.x);
			Assert::AreEqual(yi, movedShortVector.y);
			Assert::AreEqual(zi, movedShortVector.z);
			Assert::AreEqual(wi, movedShortVector.w);
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

			Assert::AreEqual(0.f, PonyEngine::Math::Vector4<float>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector4<float>::Zero.Magnitude());

			short xi = 7;
			short yi = -17;
			short zi = -43;
			short wi = 11;
			short magnitudeSquaredI = static_cast<short>(xi * xi + yi * yi + zi * zi + wi * wi);
			float magnitudeI = std::sqrt(magnitudeSquaredI);
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);

			Assert::AreEqual(magnitudeSquaredI, vectorI.MagnitudeSquared());
			Assert::AreEqual(magnitudeI, vectorI.Magnitude());

			Assert::AreEqual(short{0}, PonyEngine::Math::Vector4<short>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector4<short>::Zero.Magnitude());
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

			Assert::AreEqual(static_cast<double>(normXF), static_cast<double>(normVectorF.x), 0.00001);
			Assert::AreEqual(static_cast<double>(normYF), static_cast<double>(normVectorF.y), 0.00001);
			Assert::AreEqual(static_cast<double>(normZF), static_cast<double>(normVectorF.z), 0.00001);
			Assert::AreEqual(static_cast<double>(normWF), static_cast<double>(normVectorF.w), 0.00001);

			vectorF.Normalize();
			Assert::AreEqual(static_cast<double>(normVectorF.x), static_cast<double>(vectorF.x), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.y), static_cast<double>(vectorF.y), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.z), static_cast<double>(vectorF.z), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.w), static_cast<double>(vectorF.w), 0.00001);

			auto zeroNormalizedF = PonyEngine::Math::Vector4<float>::Zero.Normalized();
			Assert::IsFalse(std::isnormal(zeroNormalizedF.x));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.y));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.z));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.w));

			short xi = -5;
			short yi = 15;
			short zi = 7;
			short wi = 14;
			auto vectorI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			float magnitudeI = vectorI.Magnitude();
			short normXI = PonyEngine::Math::RoundToIntegral<float, short>(xi / magnitudeI);
			short normYI = PonyEngine::Math::RoundToIntegral<float, short>(yi / magnitudeI);
			short normZI = PonyEngine::Math::RoundToIntegral<float, short>(zi / magnitudeI);
			short normWI = PonyEngine::Math::RoundToIntegral<float, short>(wi / magnitudeI);
			auto normVectorI = vectorI.Normalized();

			Assert::AreEqual(normXI, normVectorI.x);
			Assert::AreEqual(normYI, normVectorI.y);
			Assert::AreEqual(normZI, normVectorI.z);
			Assert::AreEqual(normWI, normVectorI.w);

			vectorI.Normalize();
			Assert::AreEqual(normVectorI.x, vectorI.x);
			Assert::AreEqual(normVectorI.y, vectorI.y);
			Assert::AreEqual(normVectorI.z, vectorI.z);
			Assert::AreEqual(normVectorI.w, vectorI.w);

			auto zeroNormalizedI = PonyEngine::Math::Vector4<short>::Zero.Normalized();
			Assert::AreEqual(short{0}, zeroNormalizedI.x);
			Assert::AreEqual(short{0}, zeroNormalizedI.y);
			Assert::AreEqual(short{0}, zeroNormalizedI.z);
			Assert::AreEqual(short{0}, zeroNormalizedI.w);
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::One.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector4<float>(nan, 0.f, 0.f, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.x = 0.f;
			vector.y = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.y = 0.f;
			vector.z = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.z = 0.f;
			vector.w = nan;
			Assert::IsFalse(vector.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Vector4<short>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector4<short>::One.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			auto vectorF = PonyEngine::Math::Vector4<float>();
			float xf = 3.f;
			float yf = -7.f;
			float zf = 5.f;
			float wf = -18.f;
			vectorF.Set(xf, yf, zf, wf);
			Assert::AreEqual(xf, vectorF.x);
			Assert::AreEqual(yf, vectorF.y);
			Assert::AreEqual(zf, vectorF.z);
			Assert::AreEqual(wf, vectorF.w);

			auto vectorI = PonyEngine::Math::Vector4<short>();
			short xi = 3;
			short yi = -7;
			short zi = 5;
			short wi = -18;
			vectorI.Set(xi, yi, zi, wi);
			Assert::AreEqual(xi, vectorI.x);
			Assert::AreEqual(yi, vectorI.y);
			Assert::AreEqual(zi, vectorI.z);
			Assert::AreEqual(wi, vectorI.w);
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
			Assert::AreEqual(xf, leftF.x);
			Assert::AreEqual(xf, centralF.x);
			Assert::AreEqual(xf, rightF.x);
			Assert::AreEqual(yf, leftF.y);
			Assert::AreEqual(yf, centralF.y);
			Assert::AreEqual(yf, rightF.y);
			Assert::AreEqual(zf, leftF.z);
			Assert::AreEqual(zf, centralF.z);
			Assert::AreEqual(zf, rightF.z);
			Assert::AreEqual(wf, leftF.w);
			Assert::AreEqual(wf, centralF.w);
			Assert::AreEqual(wf, rightF.w);

			float xf1 = 6.f;
			float yf1 = -90.f;
			float zf1 = 32.f;
			float wf1 = -87.f;
			rightF = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);
			leftF = centralF += rightF;
			Assert::AreEqual(xf + xf1, leftF.x);
			Assert::AreEqual(yf + yf1, leftF.y);
			Assert::AreEqual(zf + zf1, leftF.z);
			Assert::AreEqual(wf + wf1, leftF.w);
			Assert::AreEqual(xf + xf1, centralF.x);
			Assert::AreEqual(yf + yf1, centralF.y);
			Assert::AreEqual(zf + zf1, centralF.z);
			Assert::AreEqual(wf + wf1, centralF.w);

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			rightF = PonyEngine::Math::Vector4<float>(xf1, yf1, zf1, wf1);
			leftF = centralF -= rightF;
			Assert::AreEqual(xf - xf1, leftF.x);
			Assert::AreEqual(yf - yf1, leftF.y);
			Assert::AreEqual(zf - zf1, leftF.z);
			Assert::AreEqual(wf - wf1, leftF.w);
			Assert::AreEqual(xf - xf1, centralF.x);
			Assert::AreEqual(yf - yf1, centralF.y);
			Assert::AreEqual(zf - zf1, centralF.z);
			Assert::AreEqual(wf - wf1, centralF.w);

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			float multiplier = 3.f;
			leftF = centralF *= multiplier;
			Assert::AreEqual(xf * multiplier, leftF.x);
			Assert::AreEqual(yf * multiplier, leftF.y);
			Assert::AreEqual(zf * multiplier, leftF.z);
			Assert::AreEqual(wf * multiplier, leftF.w);
			Assert::AreEqual(xf * multiplier, centralF.x);
			Assert::AreEqual(yf * multiplier, centralF.y);
			Assert::AreEqual(zf * multiplier, centralF.z);
			Assert::AreEqual(wf * multiplier, centralF.w);

			leftF = centralF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			leftF = centralF /= multiplier;
			Assert::AreEqual(xf / multiplier, leftF.x);
			Assert::AreEqual(yf / multiplier, leftF.y);
			Assert::AreEqual(zf / multiplier, leftF.z);
			Assert::AreEqual(wf / multiplier, leftF.w);
			Assert::AreEqual(xf / multiplier, centralF.x);
			Assert::AreEqual(yf / multiplier, centralF.y);
			Assert::AreEqual(zf / multiplier, centralF.z);
			Assert::AreEqual(wf / multiplier, centralF.w);

			PonyEngine::Math::Vector4<short> leftI, centralI, rightI;
			short xi = 8;
			short yi = 22;
			short zi = -98;
			short wi = -42;

			leftI = centralI = rightI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			Assert::AreEqual(xi, leftI.x);
			Assert::AreEqual(xi, centralI.x);
			Assert::AreEqual(xi, rightI.x);
			Assert::AreEqual(yi, leftI.y);
			Assert::AreEqual(yi, centralI.y);
			Assert::AreEqual(yi, rightI.y);
			Assert::AreEqual(zi, leftI.z);
			Assert::AreEqual(zi, centralI.z);
			Assert::AreEqual(zi, rightI.z);
			Assert::AreEqual(wi, leftI.w);
			Assert::AreEqual(wi, centralI.w);
			Assert::AreEqual(wi, rightI.w);

			short xi1 = 6;
			short yi1 = -90;
			short zi1 = 32;
			short wi1 = -77;
			rightI = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);
			leftI = centralI += rightI;
			Assert::AreEqual(static_cast<short>(xi + xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), leftI.z);
			Assert::AreEqual(static_cast<short>(wi + wi1), leftI.w);
			Assert::AreEqual(static_cast<short>(xi + xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), centralI.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), centralI.z);
			Assert::AreEqual(static_cast<short>(wi + wi1), centralI.w);

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			rightI = PonyEngine::Math::Vector4<short>(xi1, yi1, zi1, wi1);
			leftI = centralI -= rightI;
			Assert::AreEqual(static_cast<short>(xi - xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), leftI.z);
			Assert::AreEqual(static_cast<short>(wi - wi1), leftI.w);
			Assert::AreEqual(static_cast<short>(xi - xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), centralI.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), centralI.z);
			Assert::AreEqual(static_cast<short>(wi - wi1), centralI.w);

			short multiplierI = short{3};
			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI *= multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), leftI.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), leftI.y);
			Assert::AreEqual(static_cast<short>(zi * multiplierI), leftI.z);
			Assert::AreEqual(static_cast<short>(wi * multiplierI), leftI.w);
			Assert::AreEqual(static_cast<short>(xi * multiplierI), centralI.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), centralI.y);
			Assert::AreEqual(static_cast<short>(zi * multiplierI), centralI.z);
			Assert::AreEqual(static_cast<short>(wi * multiplierI), centralI.w);

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI *= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi * multiplier), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(wi * multiplier), leftI.w);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi * multiplier), centralI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(wi * multiplier), centralI.w);

			leftI = centralI = PonyEngine::Math::Vector4<short>(xi, yi, zi, wi);
			leftI = centralI /= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi / multiplier), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(wi / multiplier), leftI.w);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi / multiplier), centralI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(wi / multiplier), centralI.w);
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::One == PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Zero == PonyEngine::Math::Vector4<float>(0.f, 0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector4<float>::Negative == PonyEngine::Math::Vector4<float>(-1.f, -1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector4<short>::One == PonyEngine::Math::Vector4<short>(1, 1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector4<short>::Zero == PonyEngine::Math::Vector4<short>(0, 0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector4<short>::Negative == PonyEngine::Math::Vector4<short>(-1, -1, -1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector4<unsigned char>::One == PonyEngine::Math::Vector4<unsigned char>(1, 1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector4<unsigned char>::Zero == PonyEngine::Math::Vector4<unsigned char>(0, 0, 0, 0));
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

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<float>::Zero, PonyEngine::Math::Vector4<float>::Zero));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<float>::One.Normalized(), PonyEngine::Math::Vector4<float>::One.Normalized()));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<float>::One.Normalized(), PonyEngine::Math::Vector4<float>::Negative.Normalized()));

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

			Assert::AreEqual(short{0}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<short>::Zero, PonyEngine::Math::Vector4<short>::Zero));
			Assert::AreEqual(short{4}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<short>::One, PonyEngine::Math::Vector4<short>::One));
			Assert::AreEqual(short{-4}, PonyEngine::Math::Dot(PonyEngine::Math::Vector4<short>::One, PonyEngine::Math::Vector4<short>::Negative));
		}

		TEST_METHOD(ProjectTest)
		{
			auto vectorF = PonyEngine::Math::Vector4<float>(3.f, 0.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(0.f, 0.f, 3.f, 0.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorF, vectorF1).Magnitude());

			vectorF.Set(-4.f, 2.f, 7.f, 10.f);
			vectorF1.Set(3.f, 1.f, 2.f, 5.f);
			auto projectedF = PonyEngine::Math::Project(vectorF, vectorF1);
			Assert::AreEqual(4.154, static_cast<double>(projectedF.x), 0.001);
			Assert::AreEqual(1.385, static_cast<double>(projectedF.y), 0.001);
			Assert::AreEqual(2.769, static_cast<double>(projectedF.z), 0.001);
			Assert::AreEqual(6.923, static_cast<double>(projectedF.w), 0.001);

			auto vectorI = PonyEngine::Math::Vector4<short>(3, 0, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(0, 0, 3, 0);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorI, vectorI1).Magnitude());

			vectorI.Set(2, 2, 7, 10);
			vectorI1.Set(3, 1, 0, 5);
			auto projectedI = PonyEngine::Math::Project(vectorI, vectorI1);
			Assert::AreEqual(short{5}, projectedI.x);
			Assert::AreEqual(short{2}, projectedI.y);
			Assert::AreEqual(short{0}, projectedI.z);
			Assert::AreEqual(short{8}, projectedI.w);
		}

		TEST_METHOD(ScaleTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector4<float>(-2.f, 2.f, 4.f, 6.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(2.f, 4.f, -8.f, 10.f);

			auto scaledF = PonyEngine::Math::Scale(vectorF0, vectorF1);
			Assert::AreEqual(-4.f, scaledF.x);
			Assert::AreEqual(8.f, scaledF.y);
			Assert::AreEqual(-32.f, scaledF.z);
			Assert::AreEqual(60.f, scaledF.w);

			auto vectorI0 = PonyEngine::Math::Vector4<short>(-2, 2, 4, 6);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(2, 4, -8, 10);
			auto scaledI = PonyEngine::Math::Scale(vectorI0, vectorI1);
			Assert::AreEqual(short{-4}, scaledI.x);
			Assert::AreEqual(short{8}, scaledI.y);
			Assert::AreEqual(short{-32}, scaledI.z);
			Assert::AreEqual(short{60}, scaledI.w);

			vectorF0.Scale(vectorF1);
			Assert::AreEqual(scaledF.x, vectorF0.x);
			Assert::AreEqual(scaledF.y, vectorF0.y);
			Assert::AreEqual(scaledF.z, vectorF0.z);
			Assert::AreEqual(scaledF.w, vectorF0.w);

			vectorI0.Scale(vectorI1);
			Assert::AreEqual(scaledI.x, vectorI0.x);
			Assert::AreEqual(scaledI.y, vectorI0.y);
			Assert::AreEqual(scaledI.z, vectorI0.z);
			Assert::AreEqual(scaledI.w, vectorI0.w);
		}

		TEST_METHOD(LerpTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector4<float>(-2.f, 2.f, 4.f, 6.f);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(2.f, 4.f, -8.f, 10.f);
			auto lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.f);
			Assert::AreEqual(vectorF0.x, lerpedF.x);
			Assert::AreEqual(vectorF0.y, lerpedF.y);
			Assert::AreEqual(vectorF0.z, lerpedF.z);
			Assert::AreEqual(vectorF0.w, lerpedF.w);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 1.f);
			Assert::AreEqual(vectorF1.x, lerpedF.x);
			Assert::AreEqual(vectorF1.y, lerpedF.y);
			Assert::AreEqual(vectorF1.z, lerpedF.z);
			Assert::AreEqual(vectorF1.w, lerpedF.w);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.5f);
			Assert::AreEqual(0.f, lerpedF.x);
			Assert::AreEqual(3.f, lerpedF.y);
			Assert::AreEqual(-2.f, lerpedF.z);
			Assert::AreEqual(8.f, lerpedF.w);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 2.f);
			Assert::AreEqual(6.f, lerpedF.x);
			Assert::AreEqual(6.f, lerpedF.y);
			Assert::AreEqual(-20.f, lerpedF.z);
			Assert::AreEqual(14.f, lerpedF.w);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, -1.f);
			Assert::AreEqual(-6.f, lerpedF.x);
			Assert::AreEqual(0.f, lerpedF.y);
			Assert::AreEqual(16.f, lerpedF.z);
			Assert::AreEqual(2.f, lerpedF.w);

			auto vectorI0 = PonyEngine::Math::Vector4<short>(-2, 2, 4, 6);
			auto vectorI1 = PonyEngine::Math::Vector4<short>(2, 4, -8, 10);
			auto lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.f);
			Assert::AreEqual(vectorI0.x, lerpedI.x);
			Assert::AreEqual(vectorI0.y, lerpedI.y);
			Assert::AreEqual(vectorI0.z, lerpedI.z);
			Assert::AreEqual(vectorI0.w, lerpedI.w);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 1.f);
			Assert::AreEqual(vectorI1.x, lerpedI.x);
			Assert::AreEqual(vectorI1.y, lerpedI.y);
			Assert::AreEqual(vectorI1.z, lerpedI.z);
			Assert::AreEqual(vectorI1.w, lerpedI.w);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.5f);
			Assert::AreEqual(short{0}, lerpedI.x);
			Assert::AreEqual(short{3}, lerpedI.y);
			Assert::AreEqual(short{-2}, lerpedI.z);
			Assert::AreEqual(short{8}, lerpedI.w);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 2.f);
			Assert::AreEqual(short{6}, lerpedI.x);
			Assert::AreEqual(short{6}, lerpedI.y);
			Assert::AreEqual(short{-20}, lerpedI.z);
			Assert::AreEqual(short{14}, lerpedI.w);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, -1.f);
			Assert::AreEqual(short{-6}, lerpedI.x);
			Assert::AreEqual(short{0}, lerpedI.y);
			Assert::AreEqual(short{16}, lerpedI.z);
			Assert::AreEqual(short{2}, lerpedI.w);
		}

		TEST_METHOD(AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector4<float>(1.f, 1.f, 1.f, 1.f);
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
			float zf = -7.f;
			float wf = -8.f;
			auto vectorF = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			auto vectorF1 = PonyEngine::Math::Vector4<float>(xf, yf, zf, wf);
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

			vectorF1.w *= 4.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.w = wf;
			vectorF1.z *= 2.f;
			Assert::IsFalse(vectorF == vectorF1);
			Assert::IsTrue(vectorF != vectorF1);

			vectorF1.z = zf;
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

			vectorF.z *= 0.2f;
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

			vectorI1.w *= 4;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.w = wi;
			vectorI1.z *= 2;
			Assert::IsFalse(vectorI == vectorI1);
			Assert::IsTrue(vectorI != vectorI1);

			vectorI1.z = zi;
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

			vectorI.z *= 2;
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
			Assert::AreEqual(xf + xf1, vectorF2.x);
			Assert::AreEqual(yf + yf1, vectorF2.y);
			Assert::AreEqual(zf + zf1, vectorF2.z);
			Assert::AreEqual(wf + wf1, vectorF2.w);

			vectorF2 = vectorF - vectorF1;
			Assert::AreEqual(xf - xf1, vectorF2.x);
			Assert::AreEqual(yf - yf1, vectorF2.y);
			Assert::AreEqual(zf - zf1, vectorF2.z);
			Assert::AreEqual(wf - wf1, vectorF2.w);

			float multiplier = 3.3f;
			vectorF2 = vectorF * multiplier;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);
			Assert::AreEqual(zf * multiplier, vectorF2.z);
			Assert::AreEqual(wf * multiplier, vectorF2.w);

			vectorF2 = multiplier * vectorF;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);
			Assert::AreEqual(zf * multiplier, vectorF2.z);
			Assert::AreEqual(wf * multiplier, vectorF2.w);

			vectorF2 = vectorF / multiplier;
			Assert::AreEqual(xf / multiplier, vectorF2.x);
			Assert::AreEqual(yf / multiplier, vectorF2.y);
			Assert::AreEqual(zf / multiplier, vectorF2.z);
			Assert::AreEqual(wf / multiplier, vectorF2.w);

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
			Assert::AreEqual(static_cast<short>(xi + xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi + wi1), vectorI2.w);

			vectorI2 = vectorI - vectorI1;
			Assert::AreEqual(static_cast<short>(xi - xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi - wi1), vectorI2.w);

			short multiplierI = short{3};
			vectorI2 = vectorI * multiplierI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi * multiplierI), vectorI2.w);

			vectorI2 = vectorI * multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi * multiplier + 1), vectorI2.w);

			vectorI2 = multiplierI * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplierI), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplierI), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplierI), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi * multiplierI), vectorI2.w);

			vectorI2 = multiplier * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi * multiplier + 1), vectorI2.w);

			vectorI2 = vectorI / multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi / multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi / multiplier), vectorI2.z);
			Assert::AreEqual(static_cast<short>(wi / multiplier), vectorI2.w);
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
#pragma warning(disable:4189)
			constexpr auto defaultVector = PonyEngine::Math::Vector4<float>();
			constexpr auto vector = PonyEngine::Math::Vector4<float>(3.f, 2.f, 1.f, 3.f);
			constexpr PonyEngine::Math::Vector4<float> copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector4<float>(0.f, 1.f, 0.f, 7.f);

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr std::size_t size = vector.ComponentCount;

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
			constexpr auto lerped = PonyEngine::Math::Lerp(vector, copiedVector, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, copiedVector);

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negative = -vector;
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
#pragma warning(default:4189)
		}
	};
}
