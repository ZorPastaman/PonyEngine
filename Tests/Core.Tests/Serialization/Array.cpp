/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Serialization;

TEST_CASE("Serialized array text length", "[Serialization][Array]")
{
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<bool>(std::array{ false, true, true, false, false }) == 5);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::uint8_t>(std::array<std::uint8_t, 4>{ 3, 8, 10, 31 }) == 9);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::int8_t>(std::array<std::int8_t, 4>{ 3, -8, -10, 31 }) == 11);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::int32_t>(std::array{ 3649, -8, -10548, 318 }) == 18);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<float>(std::array{ 3649.f, -8.f, -10548.f, 318.f }) == 63);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<double>(std::array{ 3649., -8., -10548., 318. }) == 99);

	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<bool>(5) == 5);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::uint8_t>(4) == 15);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::int8_t>(4) == 19);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<std::int32_t>(5) == 59);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<float>(6) == 95);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedArrayTextLength<double>(3) == 74);
}

TEST_CASE("Serialize array binary", "[Serialization][Array]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const std::span<const T, Size> values)
	{
		std::array<std::byte, sizeof(T) * Size> data;
		std::byte* written = PonyEngine::Serialization::SerializeArrayBinary(values, std::span<std::byte, sizeof(T) * Size>(data.data(), data.size()));
		std::array<T, Size> deserialized;
		const std::byte* read = PonyEngine::Serialization::DeserializeArrayBinary(std::span<const std::byte, sizeof(T) * Size>(data.data(), data.size()), std::span<T, Size>(deserialized.data(), deserialized.size()));
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			REQUIRE(values[i] == deserialized[i]);
		}
		REQUIRE(written == read);

		written = PonyEngine::Serialization::SerializeArrayBinary(std::span<const T>(values.data(), values.size()), std::span<std::byte>(data.data(), data.size()));
		read = PonyEngine::Serialization::DeserializeArrayBinary(std::span<const std::byte>(data.data(), data.size()), std::span<T>(deserialized.data(), deserialized.size()));
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			REQUIRE(values[i] == deserialized[i]);
		}
		REQUIRE(written == read);
	};

	std::array<bool, 6> boolArray{ true, true, false, false, false, true };
	test(std::span<const bool, 6>(boolArray.data(), boolArray.size()));

	std::array<std::uint8_t, 4> uintArray{ 87, 74, 9, 201 };
	test(std::span<const std::uint8_t, 4>(uintArray.data(), uintArray.size()));

	std::array<std::int32_t, 5> intArray{ 87, -74, 9, 201, 2341455 };
	test(std::span<const std::int32_t, 5>(intArray.data(), intArray.size()));

	std::array<float, 6> floatArray{ 87.f, -74.f, 9.f, 201.f, 2341455.f, -46882.766f };
	test(std::span<const float, 6>(floatArray.data(), floatArray.size()));

	std::array<double, 6> doubleArray{ 87., -74., 9., 201., 2341455., -46882.766 };
	test(std::span<const double, 6>(doubleArray.data(), doubleArray.size()));
}

TEST_CASE("Serialize array text", "[Serialization][Array]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const std::span<const T, Size> values)
	{
		std::array<char, PonyEngine::Serialization::GetSerializedArrayTextLength<T>(Size)> data;
		data.fill(' ');
		char* serializedPoint = PonyEngine::Serialization::SerializeArrayText<false, T>(values, data);
		std::array<T, Size> deserialized;
		const char* deserializedPoint = PonyEngine::Serialization::DeserializeArrayText<false, T>(data, deserialized);
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			REQUIRE(values[i] == deserialized[i]);
		}
		REQUIRE(static_cast<void*>(serializedPoint) == static_cast<const void*>(deserializedPoint));

		if constexpr (!std::is_floating_point_v<T>)
		{
			REQUIRE(static_cast<std::uintptr_t>(serializedPoint - data.data()) == PonyEngine::Serialization::GetSerializedArrayTextLength<T>(values));
		}

		serializedPoint = PonyEngine::Serialization::SerializeArrayText<true, T>(values, data);
		deserializedPoint = PonyEngine::Serialization::DeserializeArrayText<true, T>(data, deserialized);
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			REQUIRE(values[i] == deserialized[i]);
		}
		REQUIRE(serializedPoint == deserializedPoint);

		if constexpr (!std::is_floating_point_v<T>)
		{
			REQUIRE(static_cast<std::uintptr_t>(serializedPoint - data.data()) == PonyEngine::Serialization::GetSerializedArrayTextLength<T>(values));
		}
	};

	std::array<bool, 6> boolArray{ true, true, false, false, false, true };
	test(std::span<const bool, 6>(boolArray.data(), boolArray.size()));

	std::array<std::uint8_t, 4> uintArray{ 87, 74, 9, 201 };
	test(std::span<const std::uint8_t, 4>(uintArray.data(), uintArray.size()));

	std::array<std::int32_t, 5> intArray{ 87, -74, 9, 201, 2341455 };
	test(std::span<const std::int32_t, 5>(intArray.data(), intArray.size()));

	std::array<float, 6> floatArray{ 87.f, -74.f, 9.f, 201.f, 2341455.f, -46882.766f };
	test(std::span<const float, 6>(floatArray.data(), floatArray.size()));

	std::array<double, 6> doubleArray{ 87., -74., 9., 201., 2341455., -46882.766 };
	test(std::span<const double, 6>(doubleArray.data(), doubleArray.size()));
}
