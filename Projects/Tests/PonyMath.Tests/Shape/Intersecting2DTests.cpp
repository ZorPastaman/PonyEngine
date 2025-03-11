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

		TEST_METHOD(AabrAabrTest)
		{
			constexpr auto aabr0Center = PonyMath::Core::Vector2<float>(3.f, 4.f);
			constexpr auto aabr0Extents = PonyMath::Core::Vector2<float>(4.f, 5.f);
			const auto aabr0 = PonyMath::Shape::AABR<float>(aabr0Center, aabr0Extents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr0, aabr0));

			auto aabr1Center = PonyMath::Core::Vector2<float>(1.f, 3.f);
			auto aabr1Extents = PonyMath::Core::Vector2<float>(1.f, 2.f);
			auto aabr1 = PonyMath::Shape::AABR<float>(aabr1Center, aabr1Extents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr0, aabr1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr1, aabr0));

			aabr1Center = PonyMath::Core::Vector2<float>(5.f, 3.f);
			aabr1Extents = PonyMath::Core::Vector2<float>(10.f, 2.f);
			aabr1 = PonyMath::Shape::AABR<float>(aabr1Center, aabr1Extents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr0, aabr1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr1, aabr0));

			aabr1Center = PonyMath::Core::Vector2<float>(10.f, 3.f);
			aabr1Extents = PonyMath::Core::Vector2<float>(2.f, 2.f);
			aabr1 = PonyMath::Shape::AABR<float>(aabr1Center, aabr1Extents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr0, aabr1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr1, aabr0));

			aabr1Center = PonyMath::Core::Vector2<float>(2.f, 12.f);
			aabr1Extents = PonyMath::Core::Vector2<float>(2.f, 2.f);
			aabr1 = PonyMath::Shape::AABR<float>(aabr1Center, aabr1Extents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr0, aabr1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr1, aabr0));
		}

		TEST_METHOD(AabrRayTest)
		{
			auto aabrCenter = PonyMath::Core::Vector2<float>(-0.5f, 1.f);
			auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			constexpr auto rayOrigin = PonyMath::Core::Vector2<float>(5.f, 7.f);
			const auto rayDirection = PonyMath::Core::Vector2<float>(-0.4f, -0.7f).Normalized();
			const auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr, ray, 100.f));

			aabrExtents = PonyMath::Core::Vector2<float>(0.1f, 0.1f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray, 100.f));

			aabrCenter = PonyMath::Core::Vector2<float>(0.f, 100.f);
			aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, ray, 100.f));
		}

		TEST_METHOD(AabrLineTest)
		{
			auto aabrCenter = PonyMath::Core::Vector2<float>(-0.5f, 1.f);
			auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			const auto lineNormal = PonyMath::Core::Vector2<float>(1.f, 1.5f).Normalized();
			const auto line = PonyMath::Shape::Line<float>(lineNormal, -4.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr, line));

			aabrExtents = PonyMath::Core::Vector2<float>(0.1f, 0.1f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, line));

			aabrCenter = PonyMath::Core::Vector2<float>(0.f, 100.f);
			aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, line));
		}

		TEST_METHOD(AabrObrTest)
		{
			auto aabrCenter = PonyMath::Core::Vector2<float>(-0.5f, 1.f);
			auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			constexpr auto obrCenter = PonyMath::Core::Vector2<float>(1.f, 2.f);
			constexpr auto obrExtents = PonyMath::Core::Vector2<float>(3.f, 3.f);
			const auto obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 105.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabr, obr));

			aabrCenter = PonyMath::Core::Vector2<float>(3.6f, 1.f);
			aabrExtents = PonyMath::Core::Vector2<float>(1.f, 0.5f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabr, obr));
		}

		TEST_METHOD(ObrObrTest)
		{
			constexpr auto obr0Center = PonyMath::Core::Vector2<float>(5.f, 1.f);
			auto obr0Extents = PonyMath::Core::Vector2<float>(2.f, 1.5f);
			auto obr0 = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obr0Center, obr0Extents), 0.f);
			constexpr auto obr1Center = PonyMath::Core::Vector2<float>(-3.f, 0.f);
			constexpr auto obr1Extents = PonyMath::Core::Vector2<float>(1.f, 1.f);
			const auto obr1 = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obr1Center, obr1Extents), 0.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr0, obr1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr1, obr0));

			obr0 = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obr0Center, obr0Extents), 170.f * PonyMath::Core::DegToRad<float>);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr0, obr1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr1, obr0));

			obr0Extents = PonyMath::Core::Vector2<float>(0.5f, 0.5f);
			obr0 = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obr0Center, obr0Extents), 170.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr0, obr1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr1, obr0));
		}

		TEST_METHOD(ObrRayTest)
		{
			auto aabrCenter = PonyMath::Core::Vector2<float>(-0.5f, 1.f);
			auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			auto obr = PonyMath::Shape::OBR<float>(aabr, 15.f * PonyMath::Core::DegToRad<float>);
			constexpr auto rayOrigin = PonyMath::Core::Vector2<float>(5.f, 7.f);
			const auto rayDirection = PonyMath::Core::Vector2<float>(-0.4f, -0.7f).Normalized();
			const auto ray = PonyMath::Shape::Ray2D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr, ray, 100.f));

			aabrExtents = PonyMath::Core::Vector2<float>(0.1f, 0.1f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			obr = PonyMath::Shape::OBR<float>(aabr, 15.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 100.f));

			aabrCenter = PonyMath::Core::Vector2<float>(0.f, 100.f);
			aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			obr = PonyMath::Shape::OBR<float>(aabr, 15.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 100.f));

			aabrCenter = PonyMath::Core::Vector2<float>(-1.f, 1.f);
			aabrExtents = PonyMath::Core::Vector2<float>(2.f, 1.f);
			aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			obr = PonyMath::Shape::OBR<float>(aabr, 45.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, ray, 100.f));
		}

		TEST_METHOD(ObrLineTest)
		{
			auto obrCenter = PonyMath::Core::Vector2<float>(6.f, 4.f);
			auto obrExtents = PonyMath::Core::Vector2<float>(4.f, 3.f);
			auto obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 5.f * PonyMath::Core::DegToRad<float>);
			auto lineNormal = PonyMath::Core::Vector2<float>(1.f, -1.f).Normalized();
			auto line = PonyMath::Shape::Line<float>(lineNormal, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr, line));

			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 105.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, line));

			obrCenter = PonyMath::Core::Vector2<float>(-6.f, 4.f);
			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 5.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, line));

			obrCenter = PonyMath::Core::Vector2<float>(6.f, 4.f);
			obrExtents = PonyMath::Core::Vector2<float>(0.3f, 0.2f);
			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 5.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, line));
		}

		TEST_METHOD(ObrAabrTest)
		{
			auto obrCenter = PonyMath::Core::Vector2<float>(4.f, 2.f);
			auto obrExtents = PonyMath::Core::Vector2<float>(3.f, 3.f);
			auto obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 105.f * PonyMath::Core::DegToRad<float>);
			auto aabrCenter = PonyMath::Core::Vector2<float>(-5.f, 1.f);
			auto aabrExtents = PonyMath::Core::Vector2<float>(4.f, 6.f);
			auto aabr = PonyMath::Shape::AABR<float>(aabrCenter, aabrExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obr, aabr));

			obrCenter = PonyMath::Core::Vector2<float>(4.f, -20.f);
			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 105.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, aabr));

			obrCenter = PonyMath::Core::Vector2<float>(4.f, 2.f);
			obrExtents = PonyMath::Core::Vector2<float>(0.3f, 0.1f);
			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 50.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, aabr));

			obrCenter = PonyMath::Core::Vector2<float>(4.f, 2.f);
			obrExtents = PonyMath::Core::Vector2<float>(3.f, 3.f);
			obr = PonyMath::Shape::OBR<float>(PonyMath::Shape::AABR<float>(obrCenter, obrExtents), 5.f * PonyMath::Core::DegToRad<float>);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obr, aabr));
		}
	};
}
