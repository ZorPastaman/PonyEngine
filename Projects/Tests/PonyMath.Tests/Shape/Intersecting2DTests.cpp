/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyMath.Core;
import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(Intersecting2DTests)
	{
		TEST_METHOD(RayRayTest)
		{
			auto origin0 = PonyMath::Core::Vector2<float>(-2.f, 1.f);
			auto direction0 = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			auto ray0 = PonyMath::Shape::Ray2D<float>(origin0, direction0);
			auto origin1 = PonyMath::Core::Vector2<float>(1.f, -0.5f);
			auto direction1 = PonyMath::Core::Vector2<float>(-0.5f, 0.5f).Normalized();
			auto ray1 = PonyMath::Shape::Ray2D<float>(origin1, direction1);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray0, ray1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray1, ray0));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 100.f));

			direction1 = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			ray1 = PonyMath::Shape::Ray2D<float>(origin1, direction1);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray1, ray0));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 100.f));

			origin1 = origin0;
			ray1 = PonyMath::Shape::Ray2D<float>(origin1, direction1);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray1, ray0));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 100.f));

			origin1 = PonyMath::Core::Vector2<float>(1.f, -50.f);
			direction1 = PonyMath::Core::Vector2<float>(-0.5f, 0.5f).Normalized();
			ray1 = PonyMath::Shape::Ray2D<float>(origin1, direction1);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray1, ray0));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 100.f));

			origin0 = PonyMath::Core::Vector2<float>(0.f, 0.f);
			direction0 = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray0 = PonyMath::Shape::Ray2D<float>(origin0, direction0);
			origin1 = PonyMath::Core::Vector2<float>(1.f, -0.000001f);
			direction1 = PonyMath::Core::Vector2<float>(0.f, 1.f);
			ray1 = PonyMath::Shape::Ray2D<float>(origin1, direction1);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray1, ray0));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray0, ray1, 100.f, 100.f));
		}

		TEST_METHOD(RayLineTest)
		{
			auto rayOrigin = PonyMath::Core::Vector2<float>(-2.f, 1.f);
			auto rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			auto lineNormal = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			auto linePoint = PonyMath::Core::Vector2<float>(5.f, 2.f);
			auto line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, line, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(7.f, 2.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, line, 100.f));

			rayOrigin = linePoint;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(7.f, 2.f);
			rayDirection = PonyMath::Core::Vector2<float>(-lineNormal.Y(), lineNormal.X());
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-0.000001f, 1.f);
			rayDirection = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			lineNormal = PonyMath::Core::Vector2<float>(1.f, 0.f);
			linePoint = PonyMath::Core::Vector2<float>(0.f, 0.f);
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, line, 100.f));
		}

		TEST_METHOD(RayAabrTest)
		{
			auto rayOrigin = PonyMath::Core::Vector2<float>(-2.f, 1.f);
			auto rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			constexpr auto aabrCenter = PonyMath::Core::Vector2<float>(1.f, 1.f);
			constexpr auto aabrExtents = PonyMath::Core::Vector2<float>(1.5f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 2.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 4.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.8f, -1.f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 4.f);
			rayDirection = PonyMath::Core::Vector2<float>(-0.8f, -1.f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 0.f);
			rayDirection = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 8.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 0.f);
			rayDirection = PonyMath::Core::Vector2<float>(-1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, -8.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(0.f,-10.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.f, 1.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 0.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(0.f, 10.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.f, -1.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 0.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = aabr.Center();
			rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(aabr.MinX() - 0.000001f, aabr.Center().Y());
			rayDirection = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabr, 100.f));
		}

		TEST_METHOD(RayObrTest)
		{
			auto rayOrigin = PonyMath::Core::Vector2<float>(-2.f, -1.f);
			auto rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			constexpr auto aabrCenter = PonyMath::Core::Vector2<float>(1.f, 1.f);
			constexpr auto aabrExtents = PonyMath::Core::Vector2<float>(1.5f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			auto obr = PonyMath::Shape::OBR<float>(aabr, 30.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 2.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 4.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.8f, -1.f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 4.f);
			rayDirection = PonyMath::Core::Vector2<float>(-0.8f, -1.f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 0.f);
			rayDirection = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 8.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, 0.f);
			rayDirection = PonyMath::Core::Vector2<float>(-1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(4.f, -8.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(0.f, -10.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.f, 1.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(-4.f, 0.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(0.f, 10.f);
			rayDirection = PonyMath::Core::Vector2<float>(0.f, -1.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(5.f, 0.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = obr.Center();
			rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));

			rayOrigin = PonyMath::Core::Vector2<float>(obr.LeftTop().X() - 0.000001f, obr.LeftTop().Y());
			rayDirection = PonyMath::Core::Vector2<float>(1.f, 0.f);
			ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obr, 100.f));
		}

		TEST_METHOD(LineLineTest)
		{
			const auto line0Normal = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			const auto line0 = PonyMath::Shape::Line<float>(line0Normal, 1.f);
			auto line1Normal = PonyMath::Core::Vector2<float>(0.5f, 0.7f).Normalized();
			auto line1 = PonyMath::Shape::Line<float>(line1Normal, 2.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line0, line1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line1, line0));

			line1 = PonyMath::Shape::Line<float>(line0Normal, 2.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line0, line1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line1, line0));

			line1 = PonyMath::Shape::Line<float>(-line0Normal, 2.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line0, line1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line1, line0));

			line1Normal = PonyMath::Core::Vector2<float>(-line0Normal.Y(), line0Normal.X());
			line1 = PonyMath::Shape::Line<float>(line1Normal, 2.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line0, line1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line1, line0));
		}

		TEST_METHOD(LineRayTest)
		{
			auto lineNormal = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			auto linePoint = PonyMath::Core::Vector2<float>(5.f, 2.f);
			auto line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			constexpr auto rayOrigin = PonyMath::Core::Vector2<float>(-2.f, 1.f);
			auto rayDirection = PonyMath::Core::Vector2<float>(0.8f, 0.7f).Normalized();
			const auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, ray, 100.f));

			line = PonyMath::Shape::Line<float>(lineNormal, rayOrigin);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 100.f));

			lineNormal = PonyMath::Core::Vector2<float>(-rayDirection.Y(), rayDirection.X());
			linePoint = rayOrigin + rayDirection * 0.00001f;
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 100.f));

			linePoint = rayOrigin - rayDirection * 2.f;
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, ray, 100.f));
		}

		TEST_METHOD(LineAabrTest)
		{
			auto lineNormal = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			auto linePoint = PonyMath::Core::Vector2<float>(5.f, 2.f);
			auto line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			constexpr auto aabrCenter = PonyMath::Core::Vector2<float>(3.f, 4.f);
			constexpr auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 5.f);
			const auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, aabr));

			lineNormal = -lineNormal;
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, aabr));

			lineNormal = PonyMath::Core::Vector2<float>(-0.1f, 0.5f).Normalized();
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, aabr));

			linePoint = PonyMath::Core::Vector2<float>(-7.f, 12.f);
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, aabr));

			linePoint = PonyMath::Core::Vector2<float>(9.f, 10.f);
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, aabr));
		}

		TEST_METHOD(LineObrTest)
		{
			auto lineNormal = PonyMath::Core::Vector2<float>(0.5f, 0.5f).Normalized();
			auto linePoint = PonyMath::Core::Vector2<float>(-5.f, 2.f);
			auto line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			constexpr auto aabrCenter = PonyMath::Core::Vector2<float>(3.f, 4.f);
			constexpr auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 5.f);
			const auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			const auto obr = PonyMath::Shape::OBR<float>(aabr, 105.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, obr));

			lineNormal = -lineNormal;
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, obr));

			lineNormal = PonyMath::Core::Vector2<float>(-0.1f, 0.5f).Normalized();
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, obr));

			linePoint = PonyMath::Core::Vector2<float>(-7.f, 12.f);
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(line, obr));

			linePoint = PonyMath::Core::Vector2<float>(2.f, 5.f);
			line = PonyMath::Shape::Line<float>(lineNormal, linePoint);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(line, obr));
		}
	};
}
