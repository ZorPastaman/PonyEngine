/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <format>

#include "CppUnitTest.h"

import <cmath>;
import <numbers>;

import PonyEngine.Math.Common;
import PonyEngine.Math.Vector3;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(Vector3Tests)
	{
		TEST_METHOD(ConstructorsTest)
		{
			auto defaultFloatVector = PonyEngine::Math::Vector3<float>();
			Assert::AreEqual(float{}, defaultFloatVector.x);
			Assert::AreEqual(float{}, defaultFloatVector.y);
			Assert::AreEqual(float{}, defaultFloatVector.z);

			float xf = 4.f;
			float yf = -14.f;
			float zf = 7.f;

			auto floatVector = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::AreEqual(xf, floatVector.x);
			Assert::AreEqual(yf, floatVector.y);
			Assert::AreEqual(zf, floatVector.z);

			PonyEngine::Math::Vector3<float> copiedFloatVector = floatVector;
			Assert::AreEqual(xf, copiedFloatVector.x);
			Assert::AreEqual(yf, copiedFloatVector.y);
			Assert::AreEqual(zf, copiedFloatVector.z);

			PonyEngine::Math::Vector3<float> movedFloatVector = std::move(floatVector);
			Assert::AreEqual(xf, movedFloatVector.x);
			Assert::AreEqual(yf, movedFloatVector.y);
			Assert::AreEqual(zf, movedFloatVector.z);

			auto defaultShortVector = PonyEngine::Math::Vector3<short>();
			Assert::AreEqual(short{}, defaultShortVector.x);
			Assert::AreEqual(short{}, defaultShortVector.y);
			Assert::AreEqual(short{}, defaultShortVector.z);

			short xi = 4;
			short yi = -14;
			short zi = 7;

			auto shortVector = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, shortVector.x);
			Assert::AreEqual(yi, shortVector.y);
			Assert::AreEqual(zi, shortVector.z);

			PonyEngine::Math::Vector3<short> copiedShortVector = shortVector;
			Assert::AreEqual(xi, copiedShortVector.x);
			Assert::AreEqual(yi, copiedShortVector.y);
			Assert::AreEqual(zi, copiedShortVector.z);

			PonyEngine::Math::Vector3<short> movedShortVector = std::move(shortVector);
			Assert::AreEqual(xi, movedShortVector.x);
			Assert::AreEqual(yi, movedShortVector.y);
			Assert::AreEqual(zi, movedShortVector.z);
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

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<float>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<float>::Zero.Magnitude());

			short xi = 7;
			short yi = -17;
			short zi = -43;
			float magnitudeSquaredI = std::pow(static_cast<float>(xi), 2.f) + std::pow(static_cast<float>(yi), 2.f) + std::pow(static_cast<float>(zi), 2.f);
			float magnitudeI = std::sqrt(magnitudeSquaredI);
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);

			Assert::AreEqual(magnitudeSquaredI, vectorI.MagnitudeSquared());
			Assert::AreEqual(magnitudeI, vectorI.Magnitude());

			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<short>::Zero.MagnitudeSquared());
			Assert::AreEqual(0.f, PonyEngine::Math::Vector3<short>::Zero.Magnitude());
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

			Assert::AreEqual(static_cast<double>(normXF), static_cast<double>(normVectorF.x), 0.00001);
			Assert::AreEqual(static_cast<double>(normYF), static_cast<double>(normVectorF.y), 0.00001);
			Assert::AreEqual(static_cast<double>(normZF), static_cast<double>(normVectorF.z), 0.00001);

			vectorF.Normalize();
			Assert::AreEqual(static_cast<double>(normVectorF.x), static_cast<double>(vectorF.x), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.y), static_cast<double>(vectorF.y), 0.00001);
			Assert::AreEqual(static_cast<double>(normVectorF.z), static_cast<double>(vectorF.z), 0.00001);

			auto zeroNormalizedF = PonyEngine::Math::Vector3<float>::Zero.Normalized();
			Assert::IsFalse(std::isnormal(zeroNormalizedF.x));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.y));
			Assert::IsFalse(std::isnormal(zeroNormalizedF.z));

			short xi = -5;
			short yi = 15;
			short zi = 7;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			float magnitudeI = vectorI.Magnitude();
			short normXI = PonyEngine::Math::RoundToIntegral<float, short>(xi / magnitudeI);
			short normYI = PonyEngine::Math::RoundToIntegral<float, short>(yi / magnitudeI);
			short normZI = PonyEngine::Math::RoundToIntegral<float, short>(zi / magnitudeI);
			auto normVectorI = vectorI.Normalized();

			Assert::AreEqual(normXI, normVectorI.x);
			Assert::AreEqual(normYI, normVectorI.y);
			Assert::AreEqual(normZI, normVectorI.z);

			vectorI.Normalize();
			Assert::AreEqual(normVectorI.x, vectorI.x);
			Assert::AreEqual(normVectorI.y, vectorI.y);
			Assert::AreEqual(normVectorI.z, vectorI.z);

			auto zeroNormalizedI = PonyEngine::Math::Vector3<short>::Zero.Normalized();
			Assert::AreEqual(short{0}, zeroNormalizedI.x);
			Assert::AreEqual(short{0}, zeroNormalizedI.y);
			Assert::AreEqual(short{0}, zeroNormalizedI.z);
		}

		TEST_METHOD(IsFiniteTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::One.IsFinite());
			float nan = std::numeric_limits<float>::quiet_NaN();
			auto vector = PonyEngine::Math::Vector3<float>(nan, 0.f, 0.f);
			Assert::IsFalse(vector.IsFinite());
			vector.x = 0.f;
			vector.y = nan;
			Assert::IsFalse(vector.IsFinite());
			vector.y = 0.f;
			vector.z = nan;
			Assert::IsFalse(vector.IsFinite());

			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Zero.IsFinite());
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::One.IsFinite());
		}

		TEST_METHOD(SetTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>();
			float xf = 3.f;
			float yf = -7.f;
			float zf = 5.f;
			vectorF.Set(xf, yf, zf);
			Assert::AreEqual(xf, vectorF.x);
			Assert::AreEqual(yf, vectorF.y);
			Assert::AreEqual(zf, vectorF.z);

			auto vectorI = PonyEngine::Math::Vector3<short>();
			short xi = 3;
			short yi = -7;
			short zi = 5;
			vectorI.Set(xi, yi, zi);
			Assert::AreEqual(xi, vectorI.x);
			Assert::AreEqual(yi, vectorI.y);
			Assert::AreEqual(zi, vectorI.z);
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
			Assert::AreEqual(xf, leftF.x);
			Assert::AreEqual(xf, centralF.x);
			Assert::AreEqual(xf, rightF.x);
			Assert::AreEqual(yf, leftF.y);
			Assert::AreEqual(yf, centralF.y);
			Assert::AreEqual(yf, rightF.y);
			Assert::AreEqual(zf, leftF.z);
			Assert::AreEqual(zf, centralF.z);
			Assert::AreEqual(zf, rightF.z);

			float xf1 = 6.f;
			float yf1 = -90.f;
			float zf1 = 32.f;
			rightF = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);
			leftF = centralF += rightF;
			Assert::AreEqual(xf + xf1, leftF.x);
			Assert::AreEqual(yf + yf1, leftF.y);
			Assert::AreEqual(zf + zf1, leftF.z);
			Assert::AreEqual(xf + xf1, centralF.x);
			Assert::AreEqual(yf + yf1, centralF.y);
			Assert::AreEqual(zf + zf1, centralF.z);

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			rightF = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);
			leftF = centralF -= rightF;
			Assert::AreEqual(xf - xf1, leftF.x);
			Assert::AreEqual(yf - yf1, leftF.y);
			Assert::AreEqual(zf - zf1, leftF.z);
			Assert::AreEqual(xf - xf1, centralF.x);
			Assert::AreEqual(yf - yf1, centralF.y);
			Assert::AreEqual(zf - zf1, centralF.z);

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			float multiplier = 3.f;
			leftF = centralF *= multiplier;
			Assert::AreEqual(xf * multiplier, leftF.x);
			Assert::AreEqual(yf * multiplier, leftF.y);
			Assert::AreEqual(zf * multiplier, leftF.z);
			Assert::AreEqual(xf * multiplier, centralF.x);
			Assert::AreEqual(yf * multiplier, centralF.y);
			Assert::AreEqual(zf * multiplier, centralF.z);

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			leftF = centralF /= multiplier;
			Assert::AreEqual(xf / multiplier, leftF.x);
			Assert::AreEqual(yf / multiplier, leftF.y);
			Assert::AreEqual(zf / multiplier, leftF.z);
			Assert::AreEqual(xf / multiplier, centralF.x);
			Assert::AreEqual(yf / multiplier, centralF.y);
			Assert::AreEqual(zf / multiplier, centralF.z);

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			leftF = centralF *= rightF;
			Assert::AreEqual(xf * rightF.x, leftF.x);
			Assert::AreEqual(yf * rightF.y, leftF.y);
			Assert::AreEqual(zf * rightF.z, leftF.z);
			Assert::AreEqual(xf * rightF.x, centralF.x);
			Assert::AreEqual(yf * rightF.y, centralF.y);
			Assert::AreEqual(zf * rightF.z, centralF.z);

			leftF = centralF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			leftF = centralF /= rightF;
			Assert::AreEqual(xf / rightF.x, leftF.x);
			Assert::AreEqual(yf / rightF.y, leftF.y);
			Assert::AreEqual(zf / rightF.z, leftF.z);
			Assert::AreEqual(xf / rightF.x, centralF.x);
			Assert::AreEqual(yf / rightF.y, centralF.y);
			Assert::AreEqual(zf / rightF.z, centralF.z);

			PonyEngine::Math::Vector3<short> leftI, centralI, rightI;
			short xi = 8;
			short yi = 22;
			short zi = -98;

			leftI = centralI = rightI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::AreEqual(xi, leftI.x);
			Assert::AreEqual(xi, centralI.x);
			Assert::AreEqual(xi, rightI.x);
			Assert::AreEqual(yi, leftI.y);
			Assert::AreEqual(yi, centralI.y);
			Assert::AreEqual(yi, rightI.y);
			Assert::AreEqual(zi, leftI.z);
			Assert::AreEqual(zi, centralI.z);
			Assert::AreEqual(zi, rightI.z);

			short xi1 = 6;
			short yi1 = -90;
			short zi1 = 32;
			rightI = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);
			leftI = centralI += rightI;
			Assert::AreEqual(static_cast<short>(xi + xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), leftI.z);
			Assert::AreEqual(static_cast<short>(xi + xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), centralI.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), centralI.z);

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			rightI = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);
			leftI = centralI -= rightI;
			Assert::AreEqual(static_cast<short>(xi - xi1), leftI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), leftI.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), leftI.z);
			Assert::AreEqual(static_cast<short>(xi - xi1), centralI.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), centralI.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), centralI.z);

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI *= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi * multiplier), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi * multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi * multiplier), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi * multiplier), centralI.z);

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI /= multiplier;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi / multiplier), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(xi / multiplier), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(yi / multiplier), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(zi / multiplier), centralI.z);

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI *= rightI;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(xi) * rightI.x), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(yi) * rightI.y), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(zi) * rightI.z), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(xi) * rightI.x), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(yi) * rightI.y), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(zi) * rightI.z), centralI.z);

			leftI = centralI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			leftI = centralI /= rightI;
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(xi) / rightI.x), leftI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(yi) / rightI.y), leftI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(zi) / rightI.z), leftI.z);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(xi) / rightI.x), centralI.x);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(yi) / rightI.y), centralI.y);
			Assert::AreEqual(PonyEngine::Math::RoundToIntegral<float, short>(static_cast<float>(zi) / rightI.z), centralI.z);
		}

		TEST_METHOD(DefaultsTest)
		{
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Forward == PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Back == PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Up == PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Down == PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Right == PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Left == PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::One == PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Zero == PonyEngine::Math::Vector3<float>(0.f, 0.f, 0.f));
			Assert::IsTrue(PonyEngine::Math::Vector3<float>::Negative == PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f));

			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Forward == PonyEngine::Math::Vector3<short>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Back == PonyEngine::Math::Vector3<short>(0, 0, -1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Up == PonyEngine::Math::Vector3<short>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Down == PonyEngine::Math::Vector3<short>(0, -1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Right == PonyEngine::Math::Vector3<short>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Left == PonyEngine::Math::Vector3<short>(-1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::One == PonyEngine::Math::Vector3<short>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Zero == PonyEngine::Math::Vector3<short>(0, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<short>::Negative == PonyEngine::Math::Vector3<short>(-1, -1, -1));

			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Forward == PonyEngine::Math::Vector3<unsigned char>(0, 0, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Up == PonyEngine::Math::Vector3<unsigned char>(0, 1, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Right == PonyEngine::Math::Vector3<unsigned char>(1, 0, 0));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::One == PonyEngine::Math::Vector3<unsigned char>(1, 1, 1));
			Assert::IsTrue(PonyEngine::Math::Vector3<unsigned char>::Zero == PonyEngine::Math::Vector3<unsigned char>(0, 0, 0));
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

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<float>::Zero, PonyEngine::Math::Vector3<float>::Zero));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<float>::Forward, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<float>::Forward, PonyEngine::Math::Vector3<float>::Back));

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

			Assert::AreEqual(0.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<short>::Zero, PonyEngine::Math::Vector3<short>::Zero));
			Assert::AreEqual(1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<short>::Forward, PonyEngine::Math::Vector3<short>::Forward));
			Assert::AreEqual(-1.f, PonyEngine::Math::Dot(PonyEngine::Math::Vector3<short>::Forward, PonyEngine::Math::Vector3<short>::Back));
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
			Assert::AreEqual(crossF.x, vectorCrossF.x);
			Assert::AreEqual(crossF.y, vectorCrossF.y);
			Assert::AreEqual(crossF.z, vectorCrossF.z);

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<float>::Zero, PonyEngine::Math::Vector3<float>::Zero);
			Assert::AreEqual(0.f, vectorCrossF.x);
			Assert::AreEqual(0.f, vectorCrossF.y);
			Assert::AreEqual(0.f, vectorCrossF.z);

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<float>::One, PonyEngine::Math::Vector3<float>::Zero);
			Assert::AreEqual(0.f, vectorCrossF.x);
			Assert::AreEqual(0.f, vectorCrossF.y);
			Assert::AreEqual(0.f, vectorCrossF.z);

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<float>::One, PonyEngine::Math::Vector3<float>::One);
			Assert::AreEqual(0.f, vectorCrossF.x);
			Assert::AreEqual(0.f, vectorCrossF.y);
			Assert::AreEqual(0.f, vectorCrossF.z);

			vectorCrossF = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<float>::One, PonyEngine::Math::Vector3<float>::Negative);
			Assert::AreEqual(0.f, vectorCrossF.x);
			Assert::AreEqual(0.f, vectorCrossF.y);
			Assert::AreEqual(0.f, vectorCrossF.z);

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
			Assert::AreEqual(crossXI, vectorCrossI.x);
			Assert::AreEqual(crossYI, vectorCrossI.y);
			Assert::AreEqual(crossZI, vectorCrossI.z);

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<short>::Zero, PonyEngine::Math::Vector3<short>::Zero);
			Assert::AreEqual(short{0}, vectorCrossI.x);
			Assert::AreEqual(short{0}, vectorCrossI.y);
			Assert::AreEqual(short{0}, vectorCrossI.z);

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<short>::One, PonyEngine::Math::Vector3<short>::Zero);
			Assert::AreEqual(short{0}, vectorCrossI.x);
			Assert::AreEqual(short{0}, vectorCrossI.y);
			Assert::AreEqual(short{0}, vectorCrossI.z);

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<short>::One, PonyEngine::Math::Vector3<short>::One);
			Assert::AreEqual(short{0}, vectorCrossI.x);
			Assert::AreEqual(short{0}, vectorCrossI.y);
			Assert::AreEqual(short{0}, vectorCrossI.z);

			vectorCrossI = PonyEngine::Math::Cross(PonyEngine::Math::Vector3<short>::One, PonyEngine::Math::Vector3<short>::Negative);
			Assert::AreEqual(short{0}, vectorCrossI.x);
			Assert::AreEqual(short{0}, vectorCrossI.y);
			Assert::AreEqual(short{0}, vectorCrossI.z);
		}

		TEST_METHOD(AngleTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));

			vectorF1.Set(0.f, 1.f, 0.f);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Back));
			Assert::AreEqual(-90.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Back));

			vectorF1.Set(-1.f, 0.f, 0.f);
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Forward));
			Assert::AreEqual(std::numbers::pi_v<float>, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Back));
			Assert::AreEqual(180.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Back));

			vectorF.Set(0.f, 0.f, 1.f);
			vectorF1.Set(0.f, 0.5f, 0.5f);
			vectorF1.Normalize();
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::Angle(vectorF, vectorF1));
			Assert::AreEqual(45.f, PonyEngine::Math::AngleDegrees(vectorF, vectorF1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Left));
			Assert::AreEqual(45.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Left));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.25f, PonyEngine::Math::AngleSigned(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Right));
			Assert::AreEqual(-45.f, PonyEngine::Math::AngleSignedDegrees(vectorF, vectorF1, PonyEngine::Math::Vector3<float>::Right));

			auto vectorI = PonyEngine::Math::Vector3<short>(1, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(1, 0, 0);
			Assert::AreEqual(0.f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleDegrees(vectorI, vectorI1));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward));
			Assert::AreEqual(0.f, PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward));

			vectorI1.Set(0, 1, 0);
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::Angle(vectorI, vectorI1));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleDegrees(vectorI, vectorI1));
			Assert::AreEqual(std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward));
			Assert::AreEqual(90.f, PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward));
			Assert::AreEqual(-std::numbers::pi_v<float> * 0.5f, PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Back));
			Assert::AreEqual(-90.f, PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Back));

			vectorI1.Set(-1, 0, 0);
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::Angle(vectorI, vectorI1)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleDegrees(vectorI, vectorI1)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Forward)));
			Assert::AreEqual(std::numbers::pi_v<float>, std::abs(PonyEngine::Math::AngleSigned(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Back)));
			Assert::AreEqual(180.f, std::abs(PonyEngine::Math::AngleSignedDegrees(vectorI, vectorI1, PonyEngine::Math::Vector3<short>::Back)));
		}

		TEST_METHOD(ProjectTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(3.f, 0.f, 0.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(0.f, 0.f, 3.f);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorF, vectorF1).Magnitude());

			vectorF.Set(-4.f, 2.f, 7.f);
			vectorF1.Set(3.f, 1.f, 2.f);
			auto projectedF = PonyEngine::Math::Project(vectorF, vectorF1);
			Assert::AreEqual(0.857, static_cast<double>(projectedF.x), 0.001);
			Assert::AreEqual(0.286, static_cast<double>(projectedF.y), 0.001);
			Assert::AreEqual(0.571, static_cast<double>(projectedF.z), 0.001);

			auto vectorI = PonyEngine::Math::Vector3<short>(3, 0, 0);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(0, 0, 3);
			Assert::AreEqual(0.f, PonyEngine::Math::Project(vectorI, vectorI1).Magnitude());

			vectorI.Set(2, 2, 7);
			vectorI1.Set(3, 1, 0);
			auto projectedI = PonyEngine::Math::Project(vectorI, vectorI1);
			Assert::AreEqual(short{2}, projectedI.x);
			Assert::AreEqual(short{1}, projectedI.y);
			Assert::AreEqual(short{0}, projectedI.z);
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
			Assert::AreEqual(expectedF.x, projectionF.x);
			Assert::AreEqual(expectedF.y, projectionF.y);
			Assert::AreEqual(expectedF.z, projectionF.z);

			auto vectorI = PonyEngine::Math::Vector3<short>(2, 0, 0);
			auto normalI = PonyEngine::Math::Vector3<short>(-1, 0, 0);
			auto projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(0.f, projectionI.Magnitude());

			vectorI.Set(20, -30, 15);
			normalI.Set(5, 1, -1);
			normalI.Normalize();
			auto expectedI = vectorI - normalI * PonyEngine::Math::Dot(vectorI, normalI);
			projectionI = PonyEngine::Math::ProjectOnPlane(vectorI, normalI);
			Assert::AreEqual(expectedI.x, projectionI.x);
			Assert::AreEqual(expectedI.y, projectionI.y);
			Assert::AreEqual(expectedI.z, projectionI.z);
		}

		TEST_METHOD(ReflectTest)
		{
			auto vectorF = PonyEngine::Math::Vector3<float>(0.5f, -0.5f, 0.f);
			auto normalF = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
			auto reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.5f, reflectionF.x);
			Assert::AreEqual(0.5f, reflectionF.y);
			Assert::AreEqual(0.f, reflectionF.z);

			vectorF.Set(0.f, 5.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.x);
			Assert::AreEqual(-5.f, reflectionF.y);
			Assert::AreEqual(0.f, reflectionF.z);

			vectorF.Set(0.f, -4.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(0.f, reflectionF.x);
			Assert::AreEqual(4.f, reflectionF.y);
			Assert::AreEqual(0.f, reflectionF.z);

			vectorF.Set(3.f, 0.f, 0.f);
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			Assert::AreEqual(3.f, reflectionF.x);
			Assert::AreEqual(0.f, reflectionF.y);
			Assert::AreEqual(0.f, reflectionF.z);

			vectorF.Set(-14.f, 39.f, -1.f);
			normalF.Set(10.f, -17.f, -34.f);
			normalF.Normalize();
			reflectionF = PonyEngine::Math::Reflect(vectorF, normalF);
			auto expectedF = vectorF - 2.f * PonyEngine::Math::Dot(vectorF, normalF) * normalF;
			Assert::AreEqual(expectedF.x, reflectionF.x);
			Assert::AreEqual(expectedF.y, reflectionF.y);
			Assert::AreEqual(expectedF.z, reflectionF.z);

			auto vectorI = PonyEngine::Math::Vector3<short>(1, -1, 0);
			auto normalI = PonyEngine::Math::Vector3<short>(0, 1, 0);
			auto reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{1}, reflectionI.x);
			Assert::AreEqual(short{1}, reflectionI.y);
			Assert::AreEqual(short{0}, reflectionI.z);

			vectorI.Set(0, 5, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.x);
			Assert::AreEqual(short{-5}, reflectionI.y);
			Assert::AreEqual(short{0}, reflectionI.z);

			vectorI.Set(0, -4, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{0}, reflectionI.x);
			Assert::AreEqual(short{4}, reflectionI.y);
			Assert::AreEqual(short{0}, reflectionI.z);

			vectorI.Set(3, 0, 0);
			reflectionI = PonyEngine::Math::Reflect(vectorI, normalI);
			Assert::AreEqual(short{3}, reflectionI.x);
			Assert::AreEqual(short{0}, reflectionI.y);
			Assert::AreEqual(short{0}, reflectionI.z);
		}

		TEST_METHOD(LerpTest)
		{
			auto vectorF0 = PonyEngine::Math::Vector3<float>(-2.f, 2.f, 4.f);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(2.f, 4.f, -8.f);
			auto lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.f);
			Assert::AreEqual(vectorF0.x, lerpedF.x);
			Assert::AreEqual(vectorF0.y, lerpedF.y);
			Assert::AreEqual(vectorF0.z, lerpedF.z);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 1.f);
			Assert::AreEqual(vectorF1.x, lerpedF.x);
			Assert::AreEqual(vectorF1.y, lerpedF.y);
			Assert::AreEqual(vectorF1.z, lerpedF.z);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 0.5f);
			Assert::AreEqual(0.f, lerpedF.x);
			Assert::AreEqual(3.f, lerpedF.y);
			Assert::AreEqual(-2.f, lerpedF.z);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, 2.f);
			Assert::AreEqual(6.f, lerpedF.x);
			Assert::AreEqual(6.f, lerpedF.y);
			Assert::AreEqual(-20.f, lerpedF.z);

			lerpedF = PonyEngine::Math::Lerp(vectorF0, vectorF1, -1.f);
			Assert::AreEqual(-6.f, lerpedF.x);
			Assert::AreEqual(0.f, lerpedF.y);
			Assert::AreEqual(16.f, lerpedF.z);

			auto vectorI0 = PonyEngine::Math::Vector3<short>(-2, 2, 4);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(2, 4, -8);
			auto lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.f);
			Assert::AreEqual(vectorI0.x, lerpedI.x);
			Assert::AreEqual(vectorI0.y, lerpedI.y);
			Assert::AreEqual(vectorI0.z, lerpedI.z);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 1.f);
			Assert::AreEqual(vectorI1.x, lerpedI.x);
			Assert::AreEqual(vectorI1.y, lerpedI.y);
			Assert::AreEqual(vectorI1.z, lerpedI.z);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 0.5f);
			Assert::AreEqual(short{0}, lerpedI.x);
			Assert::AreEqual(short{3}, lerpedI.y);
			Assert::AreEqual(short{-2}, lerpedI.z);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, 2.f);
			Assert::AreEqual(short{6}, lerpedI.x);
			Assert::AreEqual(short{6}, lerpedI.y);
			Assert::AreEqual(short{-20}, lerpedI.z);

			lerpedI = PonyEngine::Math::Lerp(vectorI0, vectorI1, -1.f);
			Assert::AreEqual(short{-6}, lerpedI.x);
			Assert::AreEqual(short{0}, lerpedI.y);
			Assert::AreEqual(short{16}, lerpedI.z);
		}

		TEST_METHOD(AreAlmostEqual)
		{
			auto vector0 = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f);
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
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			Assert::IsTrue(vectorF == vectorF1);
			Assert::IsFalse(vectorF != vectorF1);

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
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			Assert::IsTrue(vectorI == vectorI1);
			Assert::IsFalse(vectorI != vectorI1);

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
			float xf1 = -75.f;
			float yf1 = 60.f;
			float zf1 = -95.f;
			auto vectorF = PonyEngine::Math::Vector3<float>(xf, yf, zf);
			auto vectorF1 = PonyEngine::Math::Vector3<float>(xf1, yf1, zf1);

			auto vectorF2 = vectorF + vectorF1;
			Assert::AreEqual(xf + xf1, vectorF2.x);
			Assert::AreEqual(yf + yf1, vectorF2.y);
			Assert::AreEqual(zf + zf1, vectorF2.z);

			vectorF2 = vectorF - vectorF1;
			Assert::AreEqual(xf - xf1, vectorF2.x);
			Assert::AreEqual(yf - yf1, vectorF2.y);
			Assert::AreEqual(zf - zf1, vectorF2.z);

			float multiplier = 3.3f;
			vectorF2 = vectorF * multiplier;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);
			Assert::AreEqual(zf * multiplier, vectorF2.z);

			vectorF2 = multiplier * vectorF;
			Assert::AreEqual(xf * multiplier, vectorF2.x);
			Assert::AreEqual(yf * multiplier, vectorF2.y);
			Assert::AreEqual(zf * multiplier, vectorF2.z);

			vectorF2 = vectorF / multiplier;
			Assert::AreEqual(xf / multiplier, vectorF2.x);
			Assert::AreEqual(yf / multiplier, vectorF2.y);
			Assert::AreEqual(zf / multiplier, vectorF2.z);

			vectorF2 = vectorF * vectorF1;
			Assert::AreEqual(xf * xf1, vectorF2.x);
			Assert::AreEqual(yf * yf1, vectorF2.y);
			Assert::AreEqual(zf * zf1, vectorF2.z);

			vectorF2 = vectorF / vectorF1;
			Assert::AreEqual(xf / xf1, vectorF2.x);
			Assert::AreEqual(yf / yf1, vectorF2.y);
			Assert::AreEqual(zf / zf1, vectorF2.z);

			short xi = 90;
			short yi = 100;
			short zi = -80;
			short xi1 = -75;
			short yi1 = 60;
			short zi1 = -95;
			auto vectorI = PonyEngine::Math::Vector3<short>(xi, yi, zi);
			auto vectorI1 = PonyEngine::Math::Vector3<short>(xi1, yi1, zi1);

			auto vectorI2 = vectorI + vectorI1;
			Assert::AreEqual(static_cast<short>(xi + xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi + yi1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi + zi1), vectorI2.z);

			vectorI2 = vectorI - vectorI1;
			Assert::AreEqual(static_cast<short>(xi - xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi - yi1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi - zi1), vectorI2.z);

			vectorI2 = vectorI * multiplier;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.z);

			vectorI2 = multiplier * vectorI;
			Assert::AreEqual(static_cast<short>(xi * multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * multiplier), vectorI2.z);

			vectorI2 = vectorI / multiplier;
			Assert::AreEqual(static_cast<short>(xi / multiplier), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi / multiplier), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi / multiplier), vectorI2.z);

			vectorI2 = vectorI * vectorI1;
			Assert::AreEqual(static_cast<short>(xi * xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi * yi1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi * zi1), vectorI2.z);

			vectorI2 = vectorI / vectorI1;
			Assert::AreEqual(static_cast<short>(xi / xi1), vectorI2.x);
			Assert::AreEqual(static_cast<short>(yi / yi1 + 1), vectorI2.y);
			Assert::AreEqual(static_cast<short>(zi / zi1 + 1), vectorI2.z);
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
#pragma warning(disable:4189)
			constexpr auto defaultVector = PonyEngine::Math::Vector3<float>();
			constexpr auto vector = PonyEngine::Math::Vector3<float>(3.f, 2.f, 1.f);
			constexpr PonyEngine::Math::Vector3<float> copiedVector = vector;
			constexpr auto normal = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);

			constexpr float magnitudeSquared = vector.MagnitudeSquared();

			constexpr std::size_t size = vector.ComponentCount;

			constexpr float dot = PonyEngine::Math::Dot(vector, copiedVector);
			constexpr auto cross = PonyEngine::Math::Cross(vector, copiedVector);
			constexpr auto project = PonyEngine::Math::Project(vector, normal);
			constexpr auto projectOnPlane = PonyEngine::Math::ProjectOnPlane(vector, normal);
			constexpr auto reflection = PonyEngine::Math::Reflect(vector, normal);
			constexpr auto lerped = PonyEngine::Math::Lerp(vector, copiedVector, 0.5f);

			constexpr bool areAlmostEqual = PonyEngine::Math::AreAlmostEqual(vector, copiedVector);

			constexpr bool equal = vector == copiedVector;
			constexpr bool notEqual = vector != copiedVector;

			constexpr auto sum = vector + copiedVector;
			constexpr auto negative = -vector;
			constexpr auto sub = vector - copiedVector;
			constexpr auto multiplied = vector * 3.f;
			constexpr auto multipliedL = 3.f * vector;
			constexpr auto multipliedV = vector * normal;
			constexpr auto divided = vector / 3.f;
			constexpr auto dividedV = vector / copiedVector;
#pragma warning(default:4189)
		}
	};
}
