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

TEST_CASE("Transform3D static", "[Math][Transform3D]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform3D<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform3D<float>::PositionType, PonyEngine::Math::Vector3<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform3D<float>::RotationType, PonyEngine::Math::Quaternion<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform3D<float>::ScaleType, PonyEngine::Math::Vector3<float>>);
}

TEST_CASE("Transform3D default constructor", "[Math][Transform3D]")
{
	const auto transform = PonyEngine::Math::Transform3D<float>();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector3<float>::Zero());
	REQUIRE(transform.Rotation() == PonyEngine::Math::Quaternion<float>::Identity());
	REQUIRE(transform.Scale() == PonyEngine::Math::Vector3<float>::One());
}

TEST_CASE("Transform3D main constructor", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	REQUIRE(transform.Scale() == scale);

	constexpr auto bigRotation = PonyEngine::Math::Quaternion<float>(4.f, -3.f, 5.f, -1.f);
	transform = PonyEngine::Math::Transform3D<float>(position, bigRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), bigRotation.Normalized()));
	REQUIRE(transform.Scale() == scale);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform3D<float>(PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f), PonyEngine::Math::Quaternion<float>(4.f, -3.f, 5.f, -1.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f));
	};
#endif
}

TEST_CASE("Transform3D copy constructor", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	PonyEngine::Math::Transform3D<float> copy = transform;
	REQUIRE(copy.Position() == transform.Position());
	REQUIRE(copy.Rotation() == transform.Rotation());
	REQUIRE(copy.Scale() == transform.Scale());
}

TEST_CASE("Transform3D move constructor", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	PonyEngine::Math::Transform3D<float> copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform3D position", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	constexpr auto otherPosition = PonyEngine::Math::Vector3<float>(-1.f, 3.f, -4.f);
	transform.Position(otherPosition);
	REQUIRE(transform.Position() == otherPosition);
}

TEST_CASE("Transform3D rotation", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
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
		auto trans = PonyEngine::Math::Transform3D<float>();
		trans.Rotation(PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f));
		return trans;
	};
#endif
}

TEST_CASE("Transform3D scale", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	REQUIRE(transform.Scale() == scale);
	constexpr auto otherScale = PonyEngine::Math::Vector3<float>(1.f, -1.f, 4.f);
	transform.Scale(otherScale);
	REQUIRE(transform.Scale() == otherScale);
}

TEST_CASE("Transform3D trs", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.TrsMatrix(), PonyEngine::Math::TrsMatrix(position, rotation, scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.TrsMatrixCompact(), PonyEngine::Math::TrsMatrixCompact(position, rotation, scale)));
}

TEST_CASE("Transform3D isFinite", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
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
		transform.Scale(position);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform3D<float>(PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f), PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f), PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f)).IsFinite();
	};
#endif
}

TEST_CASE("Transform3D directions", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), rotation * PonyEngine::Math::Vector3<float>::Left()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), rotation * PonyEngine::Math::Vector3<float>::Right()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), rotation * PonyEngine::Math::Vector3<float>::Up()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), rotation * PonyEngine::Math::Vector3<float>::Down()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), rotation * PonyEngine::Math::Vector3<float>::Forward()));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Back(), rotation * PonyEngine::Math::Vector3<float>::Back()));
}

TEST_CASE("Transform3D translate", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-1.f, 3.f, -2.f);
	transform.Translate(translation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), position + translation));
}

TEST_CASE("Transform3D rotate", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);

	const auto otherRotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(1.f, -0.5f, 0.7f));
	transform.Rotate(otherRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), otherRotation * rotation));

	constexpr auto bigRotation = PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f);
	transform.Rotate(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), (bigRotation * otherRotation * rotation).Normalized()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform3D<float>();
		trans.Rotate(PonyEngine::Math::Quaternion<float>(4.f, 6.f, -2.f, -3.f));
		return trans;
	};
#endif
}

TEST_CASE("Transform3D look-in", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector3<float>(10.f, 3.f, -5.f);
	const auto direction = (point - position).Normalized();
	transform.LookIn(direction, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform3D<float>();
		trans.LookIn(direction, PonyEngine::Math::Vector3<float>::Up());
		return trans;
	};
#endif
}

TEST_CASE("Transform3D look-at", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector3<float>(10.f, 3.f, -5.f);
	const auto direction = (point - position).Normalized();
	transform.LookAt(point, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

	transform.LookAt(position, PonyEngine::Math::Vector3<float>::Up());
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Forward(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform3D<float>();
		trans.LookAt(point, PonyEngine::Math::Vector3<float>::Up());
		return trans;
	};
#endif
}

TEST_CASE("Transform3D toString", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	const std::string expected = std::format("Position: {}, Rotation: {}, Scale: {}", position, transform.Rotation(), scale);
	REQUIRE(transform.ToString() == expected);

	std::ostringstream oss;
	oss << transform;
	REQUIRE(oss.str() == expected);

	REQUIRE(std::format("{}", transform) == expected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform3D<float>().ToString();
	};
#endif
}

TEST_CASE("Transform3D copy-assignment", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	auto copy = PonyEngine::Math::Transform3D<float>();
	copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform3D move-assignment", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	auto copy = PonyEngine::Math::Transform3D<float>();
	copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform3D equal", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<float>();
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

TEST_CASE("Transform3D are almost equal", "[Math][Transform3D]")
{
	constexpr auto position = PonyEngine::Math::Vector3<float>(4.f, -2.f, 2.f);
	const auto rotation = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-1.f, 0.5f, 2.7f));
	constexpr auto scale = PonyEngine::Math::Vector3<float>(-2.f, 3.f, 0.5f);
	auto transform = PonyEngine::Math::Transform3D<float>(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<float>();
		pos[i] = 0.000001f;
		transform.Translate(pos);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));
		transform.Position(position);
		pos[i] = 1.f;
		transform.Translate(pos);
		REQUIRE(!PonyEngine::Math::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy, 10.f));
		transform.Position(position);
	}
	transform.Rotate(PonyEngine::Math::Quaternion<float>(0.000001f, 0.000001f, 0.000001f, 0.999999f));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));
	transform.Rotation(rotation);
	transform.Rotate(PonyEngine::Math::Quaternion<float>(1.000001f, 0.000001f, 2.000001f, 1.5f));
	REQUIRE(!PonyEngine::Math::AreAlmostEqual(transform, copy));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy, 10.f));
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 3; ++i)
	{
		auto pos = PonyEngine::Math::Vector3<float>();
		pos[i] = 0.000001f;
		transform.Scale(scale + pos);
		REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));
		transform.Scale(scale);
		pos[i] = 1.f;
		transform.Scale(scale + pos);
		REQUIRE(!PonyEngine::Math::AreAlmostEqual(transform, copy));
		REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy, 10.f));
		transform.Scale(scale);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(transform, copy);
	};
#endif
}
