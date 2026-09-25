/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

import std;

import PonyEngine.Math;
import PonyEngine.World.Hierarchy;

TEST_CASE("WorldTransform2D static", "[World][Hierarchy][WorldTransform]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform2D::PositionType, PonyEngine::Math::Vector2<double>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform2D::RSMatrixType, PonyEngine::Math::Matrix<float, 2, 2>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform2D::ScaleType, PonyEngine::Math::Vector2<float>>);
}

TEST_CASE("WorldTransform3D static", "[World][Hierarchy][WorldTransform]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform3D::PositionType, PonyEngine::Math::Vector3<double>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform3D::RSMatrixType, PonyEngine::Math::Matrix<float, 3, 3>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::WorldTransform3D::ScaleType, PonyEngine::Math::Vector3<float>>);
}

TEST_CASE("WorldTransform2D default constructor", "[World][Hierarchy][WorldTransform]")
{
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector2<double>::Zero());
	REQUIRE(transform.RotationScaling() == PonyEngine::Math::Matrix2x2<float>::Identity());
}

TEST_CASE("WorldTransform3D default constructor", "[World][Hierarchy][WorldTransform]")
{
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector3<double>::Zero());
	REQUIRE(transform.RotationScaling() == PonyEngine::Math::Matrix3x3<float>::Identity());
}

TEST_CASE("WorldTransform2D position constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position);
	REQUIRE(transform.Position() == position);
	REQUIRE(transform.RotationScaling() == PonyEngine::Math::Matrix2x2<float>::Identity());
}

TEST_CASE("WorldTransform3D position constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 1004.);
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position);
	REQUIRE(transform.Position() == position);
	REQUIRE(transform.RotationScaling() == PonyEngine::Math::Matrix3x3<float>::Identity());
}

TEST_CASE("WorldTransform2D rotation-scaling constructor", "[World][Hierarchy][WorldTransform]")
{
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.2f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(rotationScaling);
	REQUIRE(transform.Position() == PonyEngine::Math::Vector2<double>::Zero());
	REQUIRE(transform.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform3D rotation-scaling constructor", "[World][Hierarchy][WorldTransform]")
{
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 1.1f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, 0.5f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(rotationScaling);
	REQUIRE(transform.Position() == PonyEngine::Math::Vector3<double>::Zero());
	REQUIRE(transform.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform2D position and rotation-scaling constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.2f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);
	REQUIRE(transform.Position() == position);
	REQUIRE(transform.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform3D position and rotation-scaling constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 1004.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 1.1f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, 0.5f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);
	REQUIRE(transform.Position() == position);
	REQUIRE(transform.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform2D local transform constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	constexpr float rotation = 3.f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(2.f, -3.f);
	const auto localTransform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(localTransform);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.RotationScaling(), PonyEngine::Math::RSMatrix(rotation, scale)));
}

TEST_CASE("WorldTransform3D local transform constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., -111.);
	const PonyEngine::Math::Quaternion<float> rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-10.f, 3.f, 0.1f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(2.f, -3.f, 4.f);
	const auto localTransform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(localTransform);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.RotationScaling(), PonyEngine::Math::RSMatrix(rotation, scale)));
}

TEST_CASE("WorldTransform2D local transform and parent constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	constexpr float rotation = 3.f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(2.f, -3.f);
	const auto localTransform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	const auto parent = PonyEngine::World::Hierarchy::WorldTransform2D(PonyEngine::Math::Vector2<double>(3., -1.),
		PonyEngine::Math::RSMatrix(3.f, PonyEngine::Math::Vector2<float>(10.f, -2.f)));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(localTransform, parent);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), parent.Position() + static_cast<PonyEngine::Math::Matrix2x2<double>>(parent.RotationScaling()) * localTransform.Position()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.RotationScaling(), parent.RotationScaling() * PonyEngine::Math::RSMatrix(localTransform.Rotation(), localTransform.Scale())));
}

TEST_CASE("WorldTransform3D local transform and parent constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., -111.);
	const PonyEngine::Math::Quaternion<float> rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-10.f, 3.f, 0.1f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(2.f, -3.f, 4.f);
	const auto localTransform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	const auto parent = PonyEngine::World::Hierarchy::WorldTransform3D(PonyEngine::Math::Vector3<double>(3., -1., 25.), 
		PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(-1.f, -0.8f, 1.2f), PonyEngine::Math::Vector3<float>(10.f, -2.f, -5.f)));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(localTransform, parent);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), parent.Position() + static_cast<PonyEngine::Math::Matrix3x3<double>>(parent.RotationScaling()) * localTransform.Position()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.RotationScaling(), parent.RotationScaling() * PonyEngine::Math::RSMatrix(localTransform.Rotation(), localTransform.Scale())));
}

TEST_CASE("WorldTransform2D copy constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.2f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(copy.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform3D copy constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 1004.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 1.1f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, 0.5f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(copy.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform2D move constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.2f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);
	const auto copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(copy.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform3D move constructor", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 1004.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 1.1f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, 0.5f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);
	const auto copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(copy.RotationScaling() == rotationScaling);
}

TEST_CASE("WorldTransform2D predefined", "[World][Hierarchy][WorldTransform]")
{
	REQUIRE(PonyEngine::World::Hierarchy::WorldTransform2D::Identity() == PonyEngine::World::Hierarchy::WorldTransform2D());
}

TEST_CASE("WorldTransform3D predefined", "[World][Hierarchy][WorldTransform]")
{
	REQUIRE(PonyEngine::World::Hierarchy::WorldTransform3D::Identity() == PonyEngine::World::Hierarchy::WorldTransform3D());
}

TEST_CASE("WorldTransform2D is finite", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	REQUIRE(transform.IsFinite());

	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		auto pos = position;
		pos[i] = std::numeric_limits<double>::quiet_NaN();
		transform.Position(pos);
		REQUIRE(!transform.IsFinite());
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		for (std::size_t j = 0uz; j < 2uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] = std::numeric_limits<float>::quiet_NaN();
			transform.RotationScaling(rot);
			REQUIRE(!transform.IsFinite());
			transform.RotationScaling(rotationScaling);
		}
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling).IsFinite();
	};
#endif
}

TEST_CASE("WorldTransform3D is finite", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 1000.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	REQUIRE(transform.IsFinite());

	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		auto pos = position;
		pos[i] = std::numeric_limits<double>::quiet_NaN();
		transform.Position(pos);
		REQUIRE(!transform.IsFinite());
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		for (std::size_t j = 0uz; j < 3uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] = std::numeric_limits<float>::quiet_NaN();
			transform.RotationScaling(rot);
			REQUIRE(!transform.IsFinite());
			transform.RotationScaling(rotationScaling);
		}
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling).IsFinite();
	};
#endif
}

TEST_CASE("WorldTransform2D directions", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), rotationScaling * PonyEngine::Math::Vector2<float>::Right()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), rotationScaling * PonyEngine::Math::Vector2<float>::Left()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), rotationScaling * PonyEngine::Math::Vector2<float>::Up()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), rotationScaling * PonyEngine::Math::Vector2<float>::Down()));
}

TEST_CASE("WorldTransform3D directions", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 6.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), rotationScaling * PonyEngine::Math::Vector3<float>::Right()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), rotationScaling * PonyEngine::Math::Vector3<float>::Left()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), rotationScaling * PonyEngine::Math::Vector3<float>::Up()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), rotationScaling * PonyEngine::Math::Vector3<float>::Down()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), rotationScaling * PonyEngine::Math::Vector3<float>::Forward()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Back(), rotationScaling * PonyEngine::Math::Vector3<float>::Back()));
}

TEST_CASE("WorldTransform2D equal", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = position;
		pos[i] += 0.000001f;
		transform.Position(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
		pos[i] += 1.f;
		transform.Position(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		for (std::size_t j = 0uz; j < 2uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] += 0.000001f;
			transform.RotationScaling(rot);
			REQUIRE(transform != copy);
			transform.RotationScaling(rotationScaling);
			rot[i, j] += 1.f;
			transform.RotationScaling(rot);
			REQUIRE(transform != copy);
			transform.RotationScaling(rotationScaling);
		}
	}
}

TEST_CASE("WorldTransform3D equal", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 6.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = position;
		pos[i] += 0.000001f;
		transform.Position(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
		pos[i] += 1.f;
		transform.Position(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		for (std::size_t j = 0uz; j < 3uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] += 0.000001f;
			transform.RotationScaling(rot);
			REQUIRE(transform != copy);
			transform.RotationScaling(rotationScaling);
			rot[i, j] += 1.f;
			transform.RotationScaling(rot);
			REQUIRE(transform != copy);
			transform.RotationScaling(rotationScaling);
		}
	}
}

TEST_CASE("WorldTransform2D transform point", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	constexpr auto point = PonyEngine::Math::Vector2<double>(-3., 6.);
	const auto expected = position + static_cast<PonyEngine::Math::Matrix2x2<double>>(rotationScaling) * point;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformPoint(transform, point), expected));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, point);
	};
#endif
}

TEST_CASE("WorldTransform3D transform point", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 6.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	constexpr auto point = PonyEngine::Math::Vector3<double>(-3., 6., 20.);
	const auto expected = position + static_cast<PonyEngine::Math::Matrix3x3<double>>(rotationScaling) * point;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformPoint(transform, point), expected));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, point);
	};
#endif
}

TEST_CASE("WorldTransform2D transform direction", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	constexpr auto direction = PonyEngine::Math::Vector2<double>(-3., 6.);
	const auto expected = static_cast<PonyEngine::Math::Matrix2x2<double>>(rotationScaling) * direction;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformDirection(transform, direction), expected));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, direction);
	};
#endif
}

TEST_CASE("WorldTransform3D transform direction", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 6.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	constexpr auto direction = PonyEngine::Math::Vector3<double>(-3., 6., 20.);
	const auto expected = static_cast<PonyEngine::Math::Matrix3x3<double>>(rotationScaling) * direction;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformDirection(transform, direction), expected));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, direction);
	};
#endif
}

TEST_CASE("WorldTransform2D combine", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	constexpr auto otherPosition = PonyEngine::Math::Vector2<double>(5., 10.);
	const auto otherRotationScaling = PonyEngine::Math::RSMatrix(-1.f, PonyEngine::Math::Vector2<float>(4.f, 1.f));
	const auto otherTransform = PonyEngine::World::Hierarchy::WorldTransform2D(otherPosition, otherRotationScaling);

	const auto result = PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	const auto resultMatrix = PonyEngine::Math::TRSMatrix(result.Position(), static_cast<PonyEngine::Math::Matrix2x2<double>>(result.RotationScaling()));
	const auto expectedMatrix = PonyEngine::Math::TRSMatrix(position, static_cast<PonyEngine::Math::Matrix2x2<double>>(rotationScaling)) *
		PonyEngine::Math::TRSMatrix(otherPosition, static_cast<PonyEngine::Math::Matrix2x2<double>>(otherRotationScaling));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(resultMatrix, expectedMatrix));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	};
#endif
}

TEST_CASE("WorldTransform3D combine", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 35., -1.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 3.f, 4.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	constexpr auto otherPosition = PonyEngine::Math::Vector3<double>(5., 10., 5.);
	const auto otherRotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(-11.f, 22.f, 91.f), PonyEngine::Math::Vector3<float>(4.f, 1.f, -12.f));
	const auto otherTransform = PonyEngine::World::Hierarchy::WorldTransform3D(otherPosition, otherRotationScaling);

	const auto result = PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	const auto resultMatrix = PonyEngine::Math::TRSMatrix(result.Position(), static_cast<PonyEngine::Math::Matrix3x3<double>>(result.RotationScaling()));
	const auto expectedMatrix = PonyEngine::Math::TRSMatrix(position, static_cast<PonyEngine::Math::Matrix3x3<double>>(rotationScaling)) *
		PonyEngine::Math::TRSMatrix(otherPosition, static_cast<PonyEngine::Math::Matrix3x3<double>>(otherRotationScaling));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(resultMatrix, expectedMatrix));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	};
#endif
}

TEST_CASE("WorldTransform2D combine local", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);

	constexpr auto otherPosition = PonyEngine::Math::Vector2<double>(5., 10.);
	constexpr float otherRotation = -1.f;
	constexpr auto otherScale = PonyEngine::Math::Vector2<float>(4.f, 1.f);
	const auto otherTransform = PonyEngine::World::Hierarchy::LocalTransform2D(otherPosition, otherRotation, otherScale);

	const auto result = PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	const auto resultMatrix = PonyEngine::Math::TRSMatrix(result.Position(), static_cast<PonyEngine::Math::Matrix2x2<double>>(result.RotationScaling()));
	const auto expectedMatrix = PonyEngine::Math::TRSMatrix(position, static_cast<PonyEngine::Math::Matrix2x2<double>>(rotationScaling)) *
		PonyEngine::Math::TRSMatrix(otherPosition, static_cast<double>(otherRotation), static_cast<PonyEngine::Math::Vector2<double>>(otherScale));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(resultMatrix, expectedMatrix));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	};
#endif
}

TEST_CASE("WorldTransform3D combine local", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 35., -1.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 3.f, 4.f));
	const auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);

	constexpr auto otherPosition = PonyEngine::Math::Vector3<double>(5., 10., -11.);
	const auto otherRotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.6f, 1.3f));
	constexpr auto otherScale = PonyEngine::Math::Vector3<float>(4.f, 1.f, -20.f);
	const auto otherTransform = PonyEngine::World::Hierarchy::LocalTransform3D(otherPosition, otherRotation, otherScale);

	const auto result = PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	const auto resultMatrix = PonyEngine::Math::TRSMatrix(result.Position(), static_cast<PonyEngine::Math::Matrix3x3<double>>(result.RotationScaling()));
	const auto expectedMatrix = PonyEngine::Math::TRSMatrix(position, static_cast<PonyEngine::Math::Matrix3x3<double>>(rotationScaling)) *
		PonyEngine::Math::TRSMatrix(otherPosition, static_cast<PonyEngine::Math::Quaternion<double>>(otherRotation), static_cast<PonyEngine::Math::Vector3<double>>(otherScale));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(resultMatrix, expectedMatrix));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::Combine(transform, otherTransform);
	};
#endif
}

TEST_CASE("WorldTransform2D are almost equal", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(-4., 25.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(1.1f, PonyEngine::Math::Vector2<float>(-6.f, 2.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform2D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = position;
		pos[i] += 0.000001f;
		transform.Position(pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Position(position);
		pos[i] += 1.f;
		transform.Position(pos);
		REQUIRE_FALSE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		for (std::size_t j = 0uz; j < 2uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] += 0.000001f;
			transform.RotationScaling(rot);
			REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
			transform.RotationScaling(rotationScaling);
			rot[i, j] += 1.f;
			transform.RotationScaling(rot);
			REQUIRE_FALSE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
			REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
			transform.RotationScaling(rotationScaling);
		}
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy);
	};
#endif
}

TEST_CASE("WorldTransform3D are almost equal", "[World][Hierarchy][WorldTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(-4., 25., 6.);
	const auto rotationScaling = PonyEngine::Math::RSMatrix(PonyEngine::Math::Vector3<float>(11.f, 2.f, 9.f), PonyEngine::Math::Vector3<float>(-6.f, 2.f, -4.f));
	auto transform = PonyEngine::World::Hierarchy::WorldTransform3D(position, rotationScaling);
	const auto copy = transform;
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = position;
		pos[i] += 0.000001f;
		transform.Position(pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Position(position);
		pos[i] += 1.f;
		transform.Position(pos);
		REQUIRE_FALSE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Position(position);
	}
	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		for (std::size_t j = 0uz; j < 3uz; ++j)
		{
			auto rot = rotationScaling;
			rot[i, j] += 0.00000001f;
			transform.RotationScaling(rot);
			REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
			REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
			transform.RotationScaling(rotationScaling);
			rot[i, j] += 1.f;
			transform.RotationScaling(rot);
			REQUIRE_FALSE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
			REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
			transform.RotationScaling(rotationScaling);
		}
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy);
	};
#endif
}
