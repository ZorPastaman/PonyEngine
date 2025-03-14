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
	TEST_CLASS(Intersecting3DTests)
	{
		TEST_METHOD(RayPlaneTest)
		{
			auto rayOrigin = PonyMath::Core::Vector3<float>(3.f, 2.f, 5.f);
			auto rayDirection = PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			const auto planeNormal = PonyMath::Core::Vector3<float>(1.f, 0.5f, 0.5f).Normalized();
			const auto plane = PonyMath::Shape::Plane<float>(planeNormal, -16.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(30.f, 20.f, 50.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayDirection = -planeNormal;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(3.f, 2.f, 5.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayOrigin = plane.Project(rayOrigin);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));

			rayOrigin -= rayDirection * 0.00001f;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, plane, 100.f));
		}

		TEST_METHOD(RayAabbTest)
		{
			auto rayOrigin = PonyMath::Core::Vector3<float>(-5.f, 2.f, -5.f);
			auto rayDirection = PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			constexpr auto aabbCenter = PonyMath::Core::Vector3<float>(1.f, -2.f, 3.f);
			constexpr auto aabbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			const auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(7.f, -4.f, 9.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = aabbCenter;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(-5.f, -1.f, 4.f);
			rayDirection = PonyMath::Core::Vector3<float>(1.f, 0.f, 0.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(-5.f, -6.f, 4.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));

			rayOrigin = PonyMath::Core::Vector3<float>(-5.f, -2.f, 4.f);
			rayDirection = PonyMath::Core::Vector3<float>(1.f, 0.f, 1.f).Normalized();
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = aabbCenter;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = aabbCenter;
			rayOrigin.Z() += aabbExtents.Z() * 2.f;
			rayDirection = PonyMath::Core::Vector3<float>(0.f, 0.f, -1.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));

			rayOrigin = aabbCenter;
			rayOrigin.Z() += aabbExtents.Z() * 1.00001f;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, aabb, 100.f));
		}

		TEST_METHOD(RayObbTest)
		{
			auto rayOrigin = PonyMath::Core::Vector3<float>(-5.f, 2.f, -5.f);
			auto rayDirection = PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f).Normalized();
			auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			constexpr auto obbCenter = PonyMath::Core::Vector3<float>(1.f, -2.f, 3.f);
			constexpr auto obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			const auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(110.f, 40.f, -60.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(8.f, -12.f, 9.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = obb.Center();
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(-10.f, -2.f, -1.f);
			rayDirection = PonyMath::Core::Vector3<float>(1.f, 0.f, 0.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = PonyMath::Core::Vector3<float>(-5.f, -6.f, 4.f);
			rayDirection = -rayDirection;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));

			rayOrigin = PonyMath::Core::Vector3<float>(-7.f, -2.5f, -4.5f);
			rayDirection = PonyMath::Core::Vector3<float>(1.f, 0.f, 1.f).Normalized();
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = obb.Center();
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = obb.Center();
			rayOrigin.Z() += obbExtents.Z() * 2.f;
			rayDirection = PonyMath::Core::Vector3<float>(0.f, 0.f, -1.f);
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));

			rayOrigin = obbCenter;
			rayOrigin.Z() += obbExtents.Z() * 1.00001f;
			ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(ray, obb, 100.f));
		}

		TEST_METHOD(PlanePlaneTest)
		{
			auto plane0Normal = PonyMath::Core::Vector3<float>(3.f, 2.f, 1.f).Normalized();
			auto plane0 = PonyMath::Shape::Plane<float>(plane0Normal, -3.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane0, plane0));
			auto plane1Normal = PonyMath::Core::Vector3<float>(2.f, 2.f, 1.f).Normalized();
			const auto plane1 = PonyMath::Shape::Plane<float>(plane1Normal, -3.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane0, plane1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane1, plane0));

			plane0Normal = PonyMath::Core::Vector3<float>(-plane1Normal.Y(), plane1Normal.X(), plane1Normal.Z());
			plane0 = PonyMath::Shape::Plane<float>(plane0Normal, 3.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane0, plane1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane1, plane0));

			plane0Normal = plane1Normal;
			plane0 = PonyMath::Shape::Plane<float>(plane0Normal, 2.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane0, plane1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane1, plane0));

			plane0Normal = -plane1Normal;
			plane0 = PonyMath::Shape::Plane<float>(plane0Normal, -2.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane0, plane1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane1, plane0));
		}

		TEST_METHOD(PlaneRayTest)
		{
			auto planeNormal = PonyMath::Core::Vector3<float>(-3.f, 2.f, 1.f).Normalized();
			auto plane = PonyMath::Shape::Plane<float>(planeNormal, -3.f);
			constexpr auto rayOrigin = PonyMath::Core::Vector3<float>(10.f, 1.f, 0.5f);
			const auto rayDirection = PonyMath::Core::Vector3<float>(-1.f, 0.1f, 1.5f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray, 0.5f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane, ray, 100.f));

			plane = PonyMath::Shape::Plane<float>(planeNormal, 30.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray, 0.5f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray, 100.f));

			planeNormal = PonyMath::Core::Vector3<float>(rayDirection.Z(), rayDirection.Y(), -rayDirection.X());
			plane = PonyMath::Shape::Plane<float>(planeNormal, -3.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray, 0.5f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, ray, 100.f));
		}

		TEST_METHOD(PlaneAabbTest)
		{
			const auto planeNormal = PonyMath::Core::Vector3<float>(-1.f, -2.f, 1.f).Normalized();
			auto plane = PonyMath::Shape::Plane<float>(planeNormal, 3.f);
			constexpr auto aabbCenter = PonyMath::Core::Vector3<float>(-2.f, -1.f, 0.f);
			constexpr auto aabbExtents = PonyMath::Core::Vector3<float>(4.f, 5.f, 2.f);
			const auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane, aabb));

			plane = PonyMath::Shape::Plane<float>(planeNormal, 30.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, aabb));

			plane = PonyMath::Shape::Plane<float>(planeNormal, -30.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, aabb));
		}

		TEST_METHOD(PlaneObbTest)
		{
			const auto planeNormal = PonyMath::Core::Vector3<float>(-1.f, -2.f, 1.f).Normalized();
			auto plane = PonyMath::Shape::Plane<float>(planeNormal, 3.f);
			constexpr auto obbCenter = PonyMath::Core::Vector3<float>(-2.f, -1.f, 0.f);
			constexpr auto obbExtents = PonyMath::Core::Vector3<float>(4.f, 5.f, 2.f);
			const auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.1f, -0.1f, -0.15f)));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(plane, obb));

			plane = PonyMath::Shape::Plane<float>(planeNormal, 30.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, obb));

			plane = PonyMath::Shape::Plane<float>(planeNormal, -30.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(plane, obb));
		}

		TEST_METHOD(AabbAabbTest)
		{
			auto aabb0Center = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			auto aabb0Extents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			auto aabb0 = PonyMath::Shape::AABB<float>(aabb0Center, aabb0Extents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb0, aabb0));
			constexpr auto aabb1Center = PonyMath::Core::Vector3<float>(12.f, -1.f, 1.f);
			constexpr auto aabb1Extents = PonyMath::Core::Vector3<float>(4.f, 5.f, 3.f);
			const auto aabb1 = PonyMath::Shape::AABB<float>(aabb1Center, aabb1Extents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb0, aabb1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb1, aabb0));

			aabb0Extents = PonyMath::Core::Vector3<float>(0.1f, 0.2f, 0.1f);
			aabb0 = PonyMath::Shape::AABB<float>(aabb0Center, aabb0Extents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb0, aabb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb1, aabb0));

			aabb0Center = PonyMath::Core::Vector3<float>(40.f, 30.f, -40.f);
			aabb0Extents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			aabb0 = PonyMath::Shape::AABB<float>(aabb0Center, aabb0Extents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb0, aabb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb1, aabb0));
		}

		TEST_METHOD(AabbRayTest)
		{
			auto aabbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			auto aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			constexpr auto rayOrigin = PonyMath::Core::Vector3<float>(5.f, -5.f, -5.f);
			const auto rayDirection = PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb, ray, 100.f));

			aabbExtents = PonyMath::Core::Vector3<float>(0.1f, 0.1f, 0.1f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray, 100.f));

			aabbCenter = PonyMath::Core::Vector3<float>(4.f, 30.f, -4.f);
			aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, ray, 100.f));
		}

		TEST_METHOD(AabbPlaneTest)
		{
			auto aabbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			auto aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			const auto planeNormal = PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f).Normalized();
			const auto plane = PonyMath::Shape::Plane<float>(planeNormal, 1.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb, plane));

			aabbExtents = PonyMath::Core::Vector3<float>(0.1f, 0.1f, 0.1f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, plane));

			aabbCenter = PonyMath::Core::Vector3<float>(4.f, 30.f, -4.f);
			aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, plane));
		}

		TEST_METHOD(AabbObbTest)
		{
			auto aabbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			auto aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			auto obbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, 4.f);
			constexpr auto obbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 4.f);
			auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 175.f, 0.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(aabb, obb));

			aabbExtents = PonyMath::Core::Vector3<float>(0.1f, 0.1f, 0.1f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, obb));

			aabbCenter = PonyMath::Core::Vector3<float>(4.f, 30.f, -4.f);
			aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, obb));

			aabbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			obbCenter = PonyMath::Core::Vector3<float>(11.f, 4.f, 6.f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 155.f, 0.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, obb));

			obbCenter = PonyMath::Core::Vector3<float>(11.8f, -4.5f, 5.3f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 155.f, 26.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(aabb, obb));
		}

		TEST_METHOD(ObbObbTest)
		{
			auto obb0Center = PonyMath::Core::Vector3<float>(-5.f, 2.f, 6.f);
			auto obb0Extents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			auto obb0 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb0Center, obb0Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb0, obb0));
			auto obb1Center = PonyMath::Core::Vector3<float>(-3.6f, -0.5f, 5.3f);
			constexpr auto obb1Extents = PonyMath::Core::Vector3<float>(6.f, 5.f, 4.f);
			auto obb1 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb1Center, obb1Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 155.f, 26.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb0, obb1));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb1, obb0));

			obb0Extents = PonyMath::Core::Vector3<float>(0.1f, 0.1f, 0.1f);
			obb0 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb0Center, obb0Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb0, obb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb1, obb0));

			obb0Center = PonyMath::Core::Vector3<float>(-5.f, 2.f, 60.f);
			obb0Extents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			obb0 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb0Center, obb0Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb0, obb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb1, obb0));

			obb0Center = PonyMath::Core::Vector3<float>(6.7f, 2.f, 13.5f);
			obb0 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb0Center, obb0Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb0, obb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb1, obb0));

			obb1Center = PonyMath::Core::Vector3<float>(-5.f, -0.46f, 4.96f);
			obb1 = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obb1Center, obb1Extents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(-8.8f, 173.5f, 24.5f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb0, obb1));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb1, obb0));
		}

		TEST_METHOD(ObbRayTest)
		{
			auto obbCenter = PonyMath::Core::Vector3<float>(6.7f, 2.f, 13.55f);
			auto obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			constexpr auto rayOrigin = PonyMath::Core::Vector3<float>(10.f, -15.f, 15.f);
			const auto rayDirection = PonyMath::Core::Vector3<float>(8.f, 9.f, -30.f).Normalized();
			const auto ray = PonyMath::Shape::Ray3D<float>(rayOrigin, rayDirection);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 1.f));
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb, ray, 100.f));

			obbExtents = PonyMath::Core::Vector3<float>(0.2f, 0.1f, 0.3f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 100.f));

			obbCenter = PonyMath::Core::Vector3<float>(16.f, 2.f, 13.55f);
			obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 100.f));

			obbCenter = PonyMath::Core::Vector3<float>(6.7f, 2.f, 13.55f);
			obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 145.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 1.f));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, ray, 100.f));
		}

		TEST_METHOD(ObbPlaneTest)
		{
			auto obbCenter = PonyMath::Core::Vector3<float>(6.7f, 2.f, 13.55f);
			auto obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			const auto planeNormal = PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f).Normalized();
			const auto plane = PonyMath::Shape::Plane<float>(planeNormal, -3.f);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb, plane));

			obbExtents = PonyMath::Core::Vector3<float>(0.1f, 0.1f, 0.2f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, plane));

			obbCenter = PonyMath::Core::Vector3<float>(16.7f, 2.f, 13.55f);
			obbExtents = PonyMath::Core::Vector3<float>(4.f, 2.f, 4.f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(11.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, plane));

			obbCenter = PonyMath::Core::Vector3<float>(6.7f, 2.f, 13.55f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(110.f, 65.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, plane));
		}

		TEST_METHOD(ObbAabbTest)
		{
			auto obbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, 4.f);
			auto obbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 4.f);
			auto obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(15.f, 175.f, -80.f) * PonyMath::Core::DegToRad<float>));
			constexpr auto aabbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			constexpr auto aabbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 3.f);
			const auto aabb = PonyMath::Shape::AABB<float>(aabbCenter, aabbExtents);
			Assert::IsTrue(PonyMath::Shape::AreIntersecting(obb, aabb));

			obbExtents = PonyMath::Core::Vector3<float>(0.6f, 0.2f, 0.3f);
			obb = PonyMath::Shape::OBB<float>(PonyMath::Shape::AABB<float>(obbCenter, obbExtents), PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(15.f, 175.f, -80.f) * PonyMath::Core::DegToRad<float>));
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, aabb));

			obbCenter = PonyMath::Core::Vector3<float>(4.f, 3.f, -4.f);
			obbExtents = PonyMath::Core::Vector3<float>(6.f, 5.f, 4.f);
			Assert::IsFalse(PonyMath::Shape::AreIntersecting(obb, aabb));
		}
	};
}
