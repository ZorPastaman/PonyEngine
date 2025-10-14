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

TEST_CASE("Serialized text length", "[Serialization][Basic]")
{
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(false) == 1);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(true) == 1);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(std::uint8_t{1}) == 1);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(std::int8_t{-43}) == 3);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(576724) == 6);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(-516161687613199749) == 19);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(76.f) == 15);
	STATIC_REQUIRE(PonyEngine::Serialization::GetSerializedTextLength(6678e+245) == 24);

	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<bool> == 1);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::uint8_t> == 3);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::int8_t> == 4);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::uint16_t> == 5);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::int16_t> == 6);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::uint32_t> == 10);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::int32_t> == 11);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::uint64_t> == 20);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<std::int64_t> == 20);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<float> == 15);
	STATIC_REQUIRE(PonyEngine::Serialization::SerializedTextLength<double> == 24);
}

TEST_CASE("Serialize binary", "[Serialization][Basic]")
{
	auto test = []<PonyEngine::Type::Arithmetic T>(const T value)
	{
		std::array<std::byte, sizeof(T)> data;
		PonyEngine::Serialization::SerializeBinary(value, data);
		T deserialized;
		PonyEngine::Serialization::DeserializeBinary(data, deserialized);
		REQUIRE(deserialized == value);
	};

	test(false);
	test(true);

	test(std::numeric_limits<std::uint8_t>::min());
	test(std::numeric_limits<std::uint8_t>::max());
	test(std::uint8_t{123});

	test(std::numeric_limits<std::int8_t>::min());
	test(std::numeric_limits<std::int8_t>::max());
	test(std::int8_t{123});
	test(std::int8_t{-24});
	test(std::int8_t{0});

	test(std::numeric_limits<std::uint16_t>::min());
	test(std::numeric_limits<std::uint16_t>::max());
	test(std::uint16_t{12987});

	test(std::numeric_limits<std::int16_t>::min());
	test(std::numeric_limits<std::int16_t>::max());
	test(std::int16_t{8596});
	test(std::int16_t{-458});
	test(std::int16_t{0});

	test(std::numeric_limits<std::uint32_t>::min());
	test(std::numeric_limits<std::uint32_t>::max());
	test(std::uint32_t{1298790});

	test(std::numeric_limits<std::int32_t>::min());
	test(std::numeric_limits<std::int32_t>::max());
	test(std::int32_t{78596298});
	test(std::int32_t{-7845856});
	test(std::int32_t{0});

	test(std::numeric_limits<std::uint64_t>::min());
	test(std::numeric_limits<std::uint64_t>::max());
	test(std::uint64_t{147812987908756});

	test(std::numeric_limits<std::int64_t>::min());
	test(std::numeric_limits<std::int64_t>::max());
	test(std::int64_t{4587859629826});
	test(std::int64_t{-78458562462268});
	test(std::int64_t{0});

	test(std::numeric_limits<float>::min());
	test(std::numeric_limits<float>::max());
	test(78596298.5445f);
	test(-7845856.549f);
	test(0.f);
	test(std::numeric_limits<float>::infinity());
	test(-std::numeric_limits<float>::infinity());
	test(std::numeric_limits<float>::quiet_NaN());

	test(std::numeric_limits<double>::min());
	test(std::numeric_limits<double>::max());
	test(78596298.5489);
	test(-7845856.4668);
	test(0.);
	test(std::numeric_limits<double>::infinity());
	test(-std::numeric_limits<double>::infinity());
	test(std::numeric_limits<double>::quiet_NaN());
}

TEST_CASE("Serialize text", "[Serialization][Basic]")
{
	auto test = []<PonyEngine::Type::Arithmetic T>(const T value)
	{
		std::array<char, PonyEngine::Serialization::SerializedTextLength<T>> data;
		char* const serializedPoint = PonyEngine::Serialization::SerializeText(value, data);
		T deserialized;
		const char* const deserializedPoint = PonyEngine::Serialization::DeserializeText<T>(data, deserialized);
		REQUIRE(deserialized == value);
		REQUIRE(serializedPoint == deserializedPoint);

		if constexpr (!std::is_floating_point_v<T>)
		{
			REQUIRE(serializedPoint - data.data() == PonyEngine::Serialization::GetSerializedTextLength(value));
		}
	};
	
	test(false);
	test(true);

	test(std::numeric_limits<std::uint8_t>::min());
	test(std::numeric_limits<std::uint8_t>::max());
	test(std::uint8_t{123});

	test(std::numeric_limits<std::int8_t>::min());
	test(std::numeric_limits<std::int8_t>::max());
	test(std::int8_t{123});
	test(std::int8_t{-24});
	test(std::int8_t{0});

	test(std::numeric_limits<std::uint16_t>::min());
	test(std::numeric_limits<std::uint16_t>::max());
	test(std::uint16_t{12987});

	test(std::numeric_limits<std::int16_t>::min());
	test(std::numeric_limits<std::int16_t>::max());
	test(std::int16_t{8596});
	test(std::int16_t{-458});
	test(std::int16_t{0});

	test(std::numeric_limits<std::uint32_t>::min());
	test(std::numeric_limits<std::uint32_t>::max());
	test(std::uint32_t{1298790});

	test(std::numeric_limits<std::int32_t>::min());
	test(std::numeric_limits<std::int32_t>::max());
	test(std::int32_t{78596298});
	test(std::int32_t{-7845856});
	test(std::int32_t{0});

	test(std::numeric_limits<std::uint64_t>::min());
	test(std::numeric_limits<std::uint64_t>::max());
	test(std::uint64_t{147812987908756});

	test(std::numeric_limits<std::int64_t>::min());
	test(std::numeric_limits<std::int64_t>::max());
	test(std::int64_t{4587859629826});
	test(std::int64_t{-78458562462268});
	test(std::int64_t{0});

	test(std::numeric_limits<float>::lowest());
	test(std::numeric_limits<float>::max());
	test(-1.06338233e+37f);
	test(78596298.5445f);
	test(-7845856.549f);
	test(0.f);
	test(std::numeric_limits<float>::infinity());
	test(-std::numeric_limits<float>::infinity());
	test(std::numeric_limits<float>::quiet_NaN());

	test(std::numeric_limits<double>::lowest());
	test(std::numeric_limits<double>::max());
	test(-1.7976931348623157e+308);
	test(78596298.5489);
	test(-7845856.4668);
	test(0.);
	test(std::numeric_limits<double>::infinity());
	test(-std::numeric_limits<double>::infinity());
	test(std::numeric_limits<double>::quiet_NaN());
}
