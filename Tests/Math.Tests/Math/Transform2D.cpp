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

TEST_CASE("Transform2D static", "[Math][Transform2D]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform2D<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform2D<float>::PositionType, PonyEngine::Math::Vector2<float>>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform2D<float>::RotationType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Transform2D<float>::ScaleType, PonyEngine::Math::Vector2<float>>);
}

TEST_CASE("Transform2D default constructor", "[Math][Transform2D]")
{
	const auto transform = PonyEngine::Math::Transform2D<float>();
	REQUIRE(transform.Position() == PonyEngine::Math::Vector2<float>::Zero());
	REQUIRE(transform.Rotation() == 0.f);
	REQUIRE(transform.Scale() == PonyEngine::Math::Vector2<float>::One());
}

TEST_CASE("Transform2D main constructor", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	REQUIRE(transform.Scale() == scale);

	constexpr float bigRotation = 10.f;
	transform = PonyEngine::Math::Transform2D<float>(position, bigRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(bigRotation, std::numbers::pi_v<float> * 2.f)));
	REQUIRE(transform.Scale() == scale);

	constexpr float negativeRotation = -101.f;
	transform = PonyEngine::Math::Transform2D<float>(position, negativeRotation, scale);
	REQUIRE(transform.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(negativeRotation, std::numbers::pi_v<float> * 2.f)));
	REQUIRE(transform.Scale() == scale);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform2D<float>(PonyEngine::Math::Vector2<float>(4.f, -2.f), -0.5f, PonyEngine::Math::Vector2<float>(-2.f, 3.f));
	};
#endif
}

TEST_CASE("Transform2D copy constructor", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	PonyEngine::Math::Transform2D<float> copy = transform;
	REQUIRE(copy.Position() == transform.Position());
	REQUIRE(copy.Rotation() == transform.Rotation());
	REQUIRE(copy.Scale() == transform.Scale());
}

TEST_CASE("Transform2D move constructor", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	PonyEngine::Math::Transform2D<float> copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform2D position", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(transform.Position() == position);
	constexpr auto otherPosition = PonyEngine::Math::Vector2<float>(-1.f, 3.f);
	transform.Position(otherPosition);
	REQUIRE(transform.Position() == otherPosition);
}

TEST_CASE("Transform2D rotation", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), rotation));
	constexpr float otherRotation = 1.2f;
	transform.Rotation(otherRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), otherRotation));
	constexpr float bigRotation = 10.f;
	transform.Rotation(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(bigRotation, std::numbers::pi_v<float> * 2.f)));
	constexpr float negativeRotation = -101.f;
	transform.Rotation(negativeRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(negativeRotation, std::numbers::pi_v<float> * 2.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Set")
	{
		auto trans = PonyEngine::Math::Transform2D<float>();
		trans.Rotation(15.f);
		return trans;
	};
#endif
}

TEST_CASE("Transform2D scale", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(transform.Scale() == scale);
	constexpr auto otherScale = PonyEngine::Math::Vector2<float>(1.f, -1.f);
	transform.Scale(otherScale);
	REQUIRE(transform.Scale() == otherScale);
}

TEST_CASE("Transform2D trs", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.TrsMatrix(), PonyEngine::Math::TrsMatrix(position, rotation, scale)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.TrsMatrixCompact(), PonyEngine::Math::TrsMatrixCompact(position, rotation, scale)));
}

TEST_CASE("Transform2D isFinite", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
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
		transform.Scale(position);
	}

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform2D<float>(PonyEngine::Math::Vector2<float>(4.f, -2.f), 0.4f, PonyEngine::Math::Vector2<float>(-2.f, 3.f)).IsFinite();
	};
#endif
}

TEST_CASE("Transform2D directions", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Left(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Left(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Right(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Up(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Up(), rotation)));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Down(), PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>::Down(), rotation)));
}

TEST_CASE("Transform2D translate", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	constexpr auto translation = PonyEngine::Math::Vector2<float>(-1.f, 3.f);
	transform.Translate(translation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Position(), position + translation));
}

TEST_CASE("Transform2D rotate", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);

	constexpr float smallRotation = -0.2f;
	transform.Rotate(smallRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation, std::numbers::pi_v<float> * 2.f)));

	constexpr float bigRotation = 11.f;
	transform.Rotate(bigRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation + bigRotation, std::numbers::pi_v<float> * 2.f)));

	constexpr float negativeRotation = -12.f;
	transform.Rotate(negativeRotation);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Rotation(), std::fmod(rotation + smallRotation + bigRotation + negativeRotation, std::numbers::pi_v<float> * 2.f), 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform2D<float>();
		trans.Rotate(15.f);
		return trans;
	};
#endif
}

TEST_CASE("Transform2D look-in", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector2<float>(10.f, 3.f);
	const auto direction = (point - position).Normalized();
	transform.LookIn(direction);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform2D<float>();
		trans.LookIn(direction);
		return trans;
	};
#endif
}

TEST_CASE("Transform2D look-at", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	constexpr auto point = PonyEngine::Math::Vector2<float>(10.f, 3.f);
	const auto direction = (point - position).Normalized();
	transform.LookAt(point);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

	transform.LookAt(position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform.Right(), direction));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		auto trans = PonyEngine::Math::Transform2D<float>();
		trans.LookAt(point);
		return trans;
	};
#endif
}

TEST_CASE("Transform2D toString", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	const std::string expected = std::format("Position: {}, Rotation: {}, Scale: {}", position, rotation, scale);
	REQUIRE(transform.ToString() == expected);

	std::ostringstream oss;
	oss << transform;
	REQUIRE(oss.str() == expected);

	REQUIRE(std::format("{}", transform) == expected);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Transform2D<float>().ToString();
	};
#endif
}

TEST_CASE("Transform2D copy-assignment", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	const auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	auto copy = PonyEngine::Math::Transform2D<float>();
	copy = transform;
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform2D move-assignment", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	auto copy = PonyEngine::Math::Transform2D<float>();
	copy = std::move(transform);
	REQUIRE(copy.Position() == position);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(copy.Rotation(), rotation));
	REQUIRE(copy.Scale() == scale);
}

TEST_CASE("Transform2D equal", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(transform == copy);

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<float>();
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

TEST_CASE("Transform2D are almost equal", "[Math][Transform2D]")
{
	constexpr auto position = PonyEngine::Math::Vector2<float>(4.f, -2.f);
	constexpr float rotation = 0.4f;
	constexpr auto scale = PonyEngine::Math::Vector2<float>(-2.f, 3.f);
	auto transform = PonyEngine::Math::Transform2D<float>(position, rotation, scale);
	const auto copy = transform;
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));

	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<float>();
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
	transform.Rotate(0.000001f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy));
	transform.Rotation(rotation);
	transform.Rotate(1.f);
	REQUIRE(!PonyEngine::Math::AreAlmostEqual(transform, copy));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(transform, copy, 10.f));
	transform.Rotation(rotation);
	for (std::size_t i = 0; i < 2; ++i)
	{
		auto pos = PonyEngine::Math::Vector2<float>();
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
