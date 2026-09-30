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

TEST_CASE("LocalTransform2D static", "[World][Hierarchy][LocalTransform]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform2D::PositionType, PonyEngine::Math::Vector2<double>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform2D::RotationType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform2D::ScaleType, PonyEngine::Math::Vector2<float>>);
}

TEST_CASE("LocalTransform2D default constructor", "[World][Hierarchy][LocalTransform]")
{
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector2<double>::Zero());
	REQUIRE(transform.Rotation() == 0.f);
	REQUIRE(transform.Scale() == PonyEngine::Math::Vector2<float>::One());
}

TEST_CASE("LocalTransform2D main constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	REQUIRE(transform.Scale() == scale);

	constexpr float bigRotation = 10.f;
	transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, bigRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(bigRotation, std::numbers::pi_v<float> *2.f)));
	REQUIRE(transform.Scale() == scale);

	constexpr float negativeRotation = -101.f;
	transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, negativeRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(negativeRotation, std::numbers::pi_v<float> *2.f)));
	REQUIRE(transform.Scale() == scale);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::LocalTransform2D(PonyEngine::Math::Vector2<double>(4.f, -2.f), -0.5f, PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
#endif
}

TEST_CASE("LocalTransform2D copy constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	PonyEngine::World::Hierarchy::LocalTransform2D copy = transform;
	REQUIRE(copy.Position() == transform.Position());
	REQUIRE(copy.Rotation() == transform.Rotation());
	REQUIRE(copy.Scale() == transform.Scale());
}

TEST_CASE("LocalTransform2D move constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	PonyEngine::World::Hierarchy::LocalTransform2D copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform2D predefined", "[World][Hierarchy][LocalTransform]")
{
	REQUIRE(PonyEngine::World::Hierarchy::LocalTransform2D::Identity() == PonyEngine::World::Hierarchy::LocalTransform2D());
}

TEST_CASE("LocalTransform2D position", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	constexpr auto otherPosition = PonyEngine::Math::Vector2<double>(-1., 3.);
	transform.Position(otherPosition);
	REQUIRE(transform.Position() == otherPosition);
}

TEST_CASE("LocalTransform2D rotation", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	constexpr float otherRotation = 1.2f;
	transform.Rotation(otherRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), otherRotation));
	constexpr float bigRotation = 10.f;
	transform.Rotation(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(bigRotation, std::numbers::pi_v<float> *2.f)));
	constexpr float negativeRotation = -101.f;
	transform.Rotation(negativeRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(negativeRotation, std::numbers::pi_v<float> *2.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform2D();
		trans.Rotation(15.f);
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform2D scale", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(transform.Scale() == scale);
	constexpr auto otherScale = PonyEngine::Math::Vector2<float>(1.f, -1.f);
	transform.Scale(otherScale);
	REQUIRE(transform.Scale() == otherScale);
}

TEST_CASE("LocalTransform2D isFinite", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(transform.IsFinite());

	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		auto pos = position;
		pos[i] = std::numeric_limits<float>::quiet_NaN();
		transform.Position(pos);
		REQUIRE(!transform.IsFinite());
		transform.Position(position);
	}

	transform.Rotation(std::numeric_limits<float>::quiet_NaN());
	REQUIRE(!transform.IsFinite());
	transform.Rotation(rotation);

	for (std::size_t i = 0uz; i < 2uz; ++i)
	{
		auto scl = scale;
		scl[i] = std::numeric_limits<float>::quiet_NaN();
		transform.Scale(scl);
		REQUIRE(!transform.IsFinite());
		transform.Scale(static_cast<PonyEngine::Math::Vector<float, 2>>(position));
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::LocalTransform2D(PonyEngine::Math::Vector2<double>(4.f, -2.f), 0.4f, PonyEngine::Math::Vector2<float>(-2.f, 3.f)).IsFinite();
	};
#endif
}

TEST_CASE("LocalTransform2D directions", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left<true>(), PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<float>::Left(), scale), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right<true>(), PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<float>::Right(), scale), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up<true>(), PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<float>::Up(), scale), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down<true>(), PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(PonyEngine::Math::Vector2<float>::Down(), scale), rotation)));
}

TEST_CASE("LocalTransform2D orientations", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Left(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Right(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Up(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Down(), rotation)));
}

TEST_CASE("LocalTransform2D translate", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto translation = PonyEngine::Math::Vector2<double>(-1., 3.);
	transform.Translate(translation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), position + translation));
}

TEST_CASE("LocalTransform2D rotate", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);

	constexpr float smallRotation = -0.2f;
	transform.Rotate(smallRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation, std::numbers::pi_v<float> *2.f)));

	constexpr float bigRotation = 11.f;
	transform.Rotate(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation + bigRotation, std::numbers::pi_v<float> *2.f)));

	constexpr float negativeRotation = -12.f;
	transform.Rotate(negativeRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation + bigRotation + negativeRotation, std::numbers::pi_v<float> *2.f), PonyEngine::Math::Tolerance{ .absolute = 0.001f }));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform2D();
		trans.Rotate(15.f);
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform2D stretch", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto stretch = PonyEngine::Math::Vector2<float>(-2.f, 5.f);
	transform.Stretch(stretch);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Scale(), PonyEngine::Math::Multiply(scale, stretch)));
}

TEST_CASE("LocalTransform2D look-in", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector2<double>(10., 3.);
	const auto direction = static_cast<PonyEngine::Math::Vector<float, 2>>((point - position).Normalized());
	transform.LookIn(direction);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform2D();
		trans.LookIn(direction);
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform2D look-at", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector2<double>(10., 3.);
	const auto direction = static_cast<PonyEngine::Math::Vector<float, 2>>((point - position).Normalized());
	transform.LookAt(point);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

	transform.LookAt(position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform2D();
		trans.LookAt(point);
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform2D copy-assignment", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	auto copy = PonyEngine::World::Hierarchy::LocalTransform2D();
	copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform2D move-assignment", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	auto copy = PonyEngine::World::Hierarchy::LocalTransform2D();
	copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform2D equal", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<double>();
		pos[i] = 0.000001f;
		transform.Translate(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
		pos[i] = 1.f;
		transform.Translate(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
	}
	transform.Rotate(0.000001f);
	REQUIRE(transform != copy);
	transform.Rotation(rotation);
	transform.Rotate(1.f);
	REQUIRE(transform != copy);
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<float>();
		pos[i] = 0.000001f;
		transform.Scale(scale + pos);
		REQUIRE(transform != copy);
		transform.Scale(scale);
		pos[i] = 1.f;
		transform.Scale(scale + pos);
		REQUIRE(transform != copy);
		transform.Scale(scale);
	}
}

TEST_CASE("LocalTransform2D TransformPoint", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector2<double>(1., 1.);
	const auto expectedTransformedPoint = position + PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(point, static_cast<PonyEngine::Math::Vector2<double>>(scale)), static_cast<double>(rotation));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformPoint(transform, point), expectedTransformedPoint));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, PonyEngine::Math::Vector2<float>(-3.f, 1.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, PonyEngine::Math::Vector2<double>(-3., 1.));
	};
#endif
}

TEST_CASE("LocalTransform2D TransformDirection", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto direction = PonyEngine::Math::Vector2<float>(0.5f, -0.7f);
	const auto expectedTransformedDir = PonyEngine::Math::Rotate(PonyEngine::Math::Multiply(direction, scale), rotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformDirection(transform, direction), expectedTransformedDir));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, PonyEngine::Math::Vector2<float>(-3.f, 1.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, PonyEngine::Math::Vector2<double>(-3., 1.));
	};
#endif
}

TEST_CASE("LocalTransform2D TransformOrientation", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(2.f, 3.f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	constexpr auto direction = PonyEngine::Math::Vector2<float>(0.5f, -0.7f);
	const auto expectedTransformedDir = PonyEngine::Math::Rotate(direction, rotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformOrientation(transform, direction), expectedTransformedDir));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformOrientation(transform, PonyEngine::Math::Vector2<float>(-3.f, 1.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformOrientation(transform, PonyEngine::Math::Vector2<double>(-3., 1.));
	};
#endif
}

TEST_CASE("LocalTransform2D are almost equal", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector2<double>(4., -2.);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<double>();
		pos[i] = 0.000001f;
		transform.Translate(pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Position(position);
		pos[i] = 1.f;
		transform.Translate(pos);
		REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
		transform.Position(position);
	}
	transform.Rotate(0.0000001f);
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
	transform.Rotation(rotation);
	transform.Rotate(1.f);
	REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<float>();
		pos[i] = 0.000001f;
		transform.Scale(scale + pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Scale(scale);
		pos[i] = 1.f;
		transform.Scale(scale + pos);
		REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
		transform.Scale(scale);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy);
	};
#endif
}

TEST_CASE("LocalTransform3D static", "[World][Hierarchy][LocalTransform]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform3D::PositionType, PonyEngine::Math::Vector3<double>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform3D::RotationType, PonyEngine::Math::Quaternion<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::World::Hierarchy::LocalTransform3D::ScaleType, PonyEngine::Math::Vector3<float>>);
}

TEST_CASE("LocalTransform3D default constructor", "[World][Hierarchy][LocalTransform]")
{
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform3D();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector3<double>::Zero());
	REQUIRE(transform.Rotation() == PonyEngine::Math::Quaternion<float>::Identity());
	REQUIRE(transform.Scale() == PonyEngine::Math::Vector3<float>::One());
}

TEST_CASE("LocalTransform3D main constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	REQUIRE(transform.Scale() == scale);

	constexpr auto bigRotation = PonyEngine::Math::Quaternion<float>(4.f, -3.f, 5.f, -1.f);
	transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, bigRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), bigRotation.Normalized()));
	REQUIRE(transform.Scale() == scale);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::LocalTransform3D(PonyEngine::Math::Vector3<double>(4., -2., 2.), PonyEngine::Math::Quaternion<float>(4.f, -3.f, 5.f, -1.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f));
	};
#endif
}

TEST_CASE("LocalTransform3D copy constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	PonyEngine::World::Hierarchy::LocalTransform3D copy = transform;
	REQUIRE(copy.Position() == transform.Position());
	REQUIRE(copy.Rotation() == transform.Rotation());
	REQUIRE(copy.Scale() == transform.Scale());
}

TEST_CASE("LocalTransform3D move constructor", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	PonyEngine::World::Hierarchy::LocalTransform3D copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform3D predefined", "[World][Hierarchy][LocalTransform]")
{
	REQUIRE(PonyEngine::World::Hierarchy::LocalTransform3D::Identity() == PonyEngine::World::Hierarchy::LocalTransform3D());
}

TEST_CASE("LocalTransform3D position", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	constexpr auto otherPosition = PonyEngine::Math::Vector3<double>(-1., 3., -4.);
	transform.Position(otherPosition);
	REQUIRE(transform.Position() == otherPosition);
}

TEST_CASE("LocalTransform3D rotation", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	const auto otherRotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 0.7f));
	transform.Rotation(otherRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), otherRotation));
	constexpr auto bigRotation = PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f);
	transform.Rotation(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), bigRotation.Normalized()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform3D();
		trans.Rotation(PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f));
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform3D scale", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(transform.Scale() == scale);
	constexpr auto otherScale = PonyEngine::Math::Vector3<float>(1.f, -1.f, 4.f);
	transform.Scale(otherScale);
	REQUIRE(transform.Scale() == otherScale);
}

TEST_CASE("LocalTransform3D isFinite", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(transform.IsFinite());

	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		auto pos = position;
		pos[i] = std::numeric_limits<float>::quiet_NaN();
		transform.Position(pos);
		REQUIRE(!transform.IsFinite());
		transform.Position(position);
	}

	for (std::size_t i = 0uz; i < 3uz; ++i)
	{
		auto scl = scale;
		scl[i] = std::numeric_limits<float>::quiet_NaN();
		transform.Scale(scl);
		REQUIRE(!transform.IsFinite());
		transform.Scale(static_cast<PonyEngine::Math::Vector3<float>>(position));
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::LocalTransform3D(PonyEngine::Math::Vector3<double>(4., -2., 2.), PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f)).IsFinite();
	};
#endif
}

TEST_CASE("LocalTransform3D directions", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Left(), scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Right(), scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Up(), scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Down(), scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Forward(), scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Back<true>(), rotation * PonyEngine::Math::Multiply(PonyEngine::Math::Vector3<float>::Back(), scale)));
}

TEST_CASE("LocalTransform3D orientations", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), rotation * PonyEngine::Math::Vector3<float>::Left()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), rotation * PonyEngine::Math::Vector3<float>::Right()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), rotation * PonyEngine::Math::Vector3<float>::Up()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), rotation * PonyEngine::Math::Vector3<float>::Down()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), rotation * PonyEngine::Math::Vector3<float>::Forward()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Back(), rotation * PonyEngine::Math::Vector3<float>::Back()));
}

TEST_CASE("LocalTransform3D translate", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	constexpr auto translation = PonyEngine::Math::Vector3<double>(-1., 3., -2.);
	transform.Translate(translation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), position + translation));
}

TEST_CASE("LocalTransform3D rotate", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);

	const auto otherRotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 0.7f));
	transform.Rotate(otherRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation * otherRotation));

	constexpr auto bigRotation = PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f);
	transform.Rotate(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), (rotation * otherRotation * bigRotation).Normalized()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform3D();
		trans.Rotate(PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f));
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform3D stretch", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	constexpr auto stretch = PonyEngine::Math::Vector3<float>(-2.f, 5.f, -1.f);
	transform.Stretch(stretch);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Scale(), PonyEngine::Math::Multiply(scale, stretch)));
}

TEST_CASE("LocalTransform3D look-in", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector3<double>(10., 3., -5.);
	const auto direction = static_cast<PonyEngine::Math::Vector3<float>>((point - position).Normalized());
	transform.LookIn(direction, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform3D();
		trans.LookIn(direction, PonyEngine::Math::Vector3<float>::Up());
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform3D look-at", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector3<double>(10., 3., -5.);
	const auto direction = static_cast<PonyEngine::Math::Vector<float, 3>>((point - position).Normalized());
	transform.LookAt(point, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

	transform.LookAt(position, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::World::Hierarchy::LocalTransform3D();
		trans.LookAt(point, PonyEngine::Math::Vector3<float>::Up());
		return trans;
	};
#endif
}

TEST_CASE("LocalTransform3D copy-assignment", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	auto copy = PonyEngine::World::Hierarchy::LocalTransform3D();
	copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform3D move-assignment", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	auto copy = PonyEngine::World::Hierarchy::LocalTransform3D();
	copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("LocalTransform3D equal", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<double>();
		pos[i] = 0.000001f;
		transform.Translate(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
		pos[i] = 1.f;
		transform.Translate(pos);
		REQUIRE(transform != copy);
		transform.Position(position);
	}
	transform.Rotate(PonyEngine::Math::Quaternion<float>(0.000001f, 0.000001f, 0.000001f, 0.999999f));
	REQUIRE(transform != copy);
	transform.Rotation(rotation);
	transform.Rotate(PonyEngine::Math::Quaternion<float>(1.000001f, 0.000001f, 2.000001f, 1.5f));
	REQUIRE(transform != copy);
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<float>();
		pos[i] = 0.000001f;
		transform.Scale(scale + pos);
		REQUIRE(transform != copy);
		transform.Scale(scale);
		pos[i] = 1.f;
		transform.Scale(scale + pos);
		REQUIRE(transform != copy);
		transform.Scale(scale);
	}
}

TEST_CASE("LocalTransform3D TransformPoint", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(2.f, 3.f, 0.5f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);

	constexpr auto point = PonyEngine::Math::Vector3<double>(1., 1., 1.);
	const auto expectedTransformedPoint = position + (static_cast<PonyEngine::Math::Quaternion<double>>(rotation) * PonyEngine::Math::Multiply(point, static_cast<PonyEngine::Math::Vector3<double>>(scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformPoint(transform, point), expectedTransformedPoint));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, PonyEngine::Math::Vector3<float>(-3.f, 1.f, 10.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformPoint(transform, PonyEngine::Math::Vector3<double>(-3., 1., 10.));
	};
#endif
}

TEST_CASE("LocalTransform3D TransformDirection", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(2.f, 3.f, 0.5f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);

	constexpr auto direction = PonyEngine::Math::Vector3<float>(0.5f, -0.7f, 0.2f);
	const auto expectedTransformedDir = rotation * PonyEngine::Math::Multiply(direction, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformDirection(transform, direction), expectedTransformedDir));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, PonyEngine::Math::Vector3<float>(-3.f, 1.f, 10.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformDirection(transform, PonyEngine::Math::Vector3<double>(-3., 1., 10.));
	};
#endif
}

TEST_CASE("LocalTransform3D TransformOrientation", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(2.f, 3.f, 0.5f);
	const auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);

	constexpr auto direction = PonyEngine::Math::Vector3<float>(0.5f, -0.7f, 0.2f);
	const auto expectedTransformedDir = rotation * direction;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::World::Hierarchy::TransformOrientation(transform, direction), expectedTransformedDir));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Float")
	{
		return PonyEngine::World::Hierarchy::TransformOrientation(transform, PonyEngine::Math::Vector3<float>(-3.f, 1.f, 10.f));
	};
	BENCHMARK("Double")
	{
		return PonyEngine::World::Hierarchy::TransformOrientation(transform, PonyEngine::Math::Vector3<double>(-3., 1., 10.));
	};
#endif
}

TEST_CASE("LocalTransform3D are almost equal", "[World][Hierarchy][LocalTransform]")
{
	constexpr auto position = PonyEngine::Math::Vector3<double>(4., -2., 2.);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<double>();
		pos[i] = 0.000001f;
		transform.Translate(pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Position(position);
		pos[i] = 1.f;
		transform.Translate(pos);
		REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
		transform.Position(position);
	}
	transform.Rotate(PonyEngine::Math::Quaternion<float>(0.000001f, 0.000001f, 0.000001f, 0.999999f));
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
	transform.Rotation(rotation);
	transform.Rotate(PonyEngine::Math::Quaternion<float>(1.000001f, 0.000001f, 2.000001f, 1.5f));
	REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
	REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<float>();
		pos[i] = 0.000001f;
		transform.Scale(scale + pos);
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		transform.Scale(scale);
		pos[i] = 1.f;
		transform.Scale(scale + pos);
		REQUIRE(!PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy, PonyEngine::Math::Tolerance{.absolute = 10.}));
		transform.Scale(scale);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::World::Hierarchy::AreAlmostEqual(transform, copy);
	};
#endif
}
