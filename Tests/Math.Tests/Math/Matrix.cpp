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
import PonyEngine.Type;

TEST_CASE("Matrix static", "[Math][Matrix]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix2x2<std::int32_t>::ValueType, std::int32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix2x2<std::int32_t>::ColumnType, PonyEngine::Math::Vector<std::int32_t, 2>>);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::Rows == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::Columns == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::ComponentCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::IsSquare);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix2x2<std::uint32_t>::ValueType, std::uint32_t>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix2x2<std::uint32_t>::ColumnType, PonyEngine::Math::Vector<std::uint32_t, 2>>);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::uint32_t>::Rows == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::uint32_t>::Columns == 2uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::uint32_t>::ComponentCount == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::uint32_t>::IsSquare);

	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix3x4<float>::ValueType, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Math::Matrix3x4<float>::ColumnType, PonyEngine::Math::Vector<float, 3>>);
	STATIC_REQUIRE(PonyEngine::Math::Matrix3x4<float>::Rows == 3uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix3x4<float>::Columns == 4uz);
	STATIC_REQUIRE(PonyEngine::Math::Matrix3x4<float>::ComponentCount == 12uz);
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix3x4<float>::IsSquare);
}

TEST_CASE("Matrix default constructor", "[Math][Matrix]")
{
	auto areAllEqual = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const T value) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != value)
			{
				return false;
			}
		}

		return true;
	};

	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>();
	STATIC_REQUIRE(areAllEqual(matrix3x3, 0));

	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<float>();
	STATIC_REQUIRE(areAllEqual(matrix2x3, 0.f));
}

TEST_CASE("Matrix diagonal constructor", "[Math][Matrix]")
{
	auto IsDiagonalEqual = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const T value) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (i == j)
				{
					if (matrix[i, j] != value)
					{
						return false;
					}
				}
				else
				{
					if (matrix[i, j] != T{0})
					{
						return false;
					}
				}
			}
		}

		return true;
	};

	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>(4);
	STATIC_REQUIRE(IsDiagonalEqual(matrix3x3, 4));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(-3.f);
	STATIC_REQUIRE(IsDiagonalEqual(matrix4x4, -3.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(5);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(1.f);
	};
#endif
}

TEST_CASE("Matrix component constructor", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(-4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(-4.f, 2.f, 6.f, 8.f, -1.f, 2.f, 5.f, -6.f, 8.f, 0.f, -3.f, 5.f, -3.f, 1.f, 3.f, -9.f);
	};
#endif
}

TEST_CASE("Matrix column constructor", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto column20 = PonyEngine::Math::Vector2<std::int32_t>(components[0], components[1]);
	constexpr auto column21 = PonyEngine::Math::Vector2<std::int32_t>(components[2], components[3]);
	constexpr auto column22 = PonyEngine::Math::Vector2<std::int32_t>(components[4], components[5]);
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(column20, column21, column22);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto column40 = PonyEngine::Math::Vector4<float>(components[0], components[1], components[2], components[3]);
	constexpr auto column41 = PonyEngine::Math::Vector4<float>(components[4], components[5], components[6], components[7]);
	constexpr auto column42 = PonyEngine::Math::Vector4<float>(components[8], components[9], components[10], components[11]);
	constexpr auto column43 = PonyEngine::Math::Vector4<float>(components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(column40, column41, column42, column43);
	STATIC_REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(PonyEngine::Math::Vector4<std::int32_t>(-4, 2, 6, 8), PonyEngine::Math::Vector4<std::int32_t>(-1, 2, 5, -6), PonyEngine::Math::Vector4<std::int32_t>(8, 0, -3, 5), PonyEngine::Math::Vector4<std::int32_t>(-3, 1, 3, -9));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(PonyEngine::Math::Vector4<float>(-4.f, 2.f, 6.f, 8.f), PonyEngine::Math::Vector4<float>(-1.f, 2.f, 5.f, -6.f), PonyEngine::Math::Vector4<float>(8.f, 0.f, -3.f, 5.f), PonyEngine::Math::Vector4<float>(-3.f, 1.f, 3.f, -9.f));
	};
#endif
}

TEST_CASE("Matrix span constructor", "[Math][Matrix]")
{
	auto convert = []<typename T, typename U, std::size_t Size>(const std::span<const T, Size> source) constexpr
	{
		auto answer = std::array<U, Size>();
		for (std::size_t i = 0; i < Size; ++i)
		{
			answer[i] = static_cast<U>(source[i]);
		}
		return answer;
	};
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int32_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(std::span<const std::int32_t, 6uz>(components.data(), 6uz));
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int32_t, 16uz>(components.data(), components.size())));

	auto fComponents = convert.operator()<std::int32_t, float, 16uz>(components);
	auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(fComponents);
	REQUIRE(checkValues(matrix4x4, std::span<const float, 16uz>(fComponents)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
	};
#endif
}

TEST_CASE("Matrix span md constructor", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	static constexpr std::array<std::int32_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto span = std::mdspan<const std::int32_t, std::extents<std::size_t, 3, 2>>(components.data());
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(span);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int32_t, 16uz>(components.data(), components.size())));

	constexpr std::array<float, 16uz> fComponents = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	auto fSpan = std::mdspan<const float, std::extents<std::size_t, 4, 4>>(fComponents.data());
	auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(fSpan);
	REQUIRE(checkValues(matrix4x4, std::span<const std::int32_t, 16uz>(components)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		constexpr std::array<std::int32_t, 16uz> benchComponents = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::mdspan<const std::int32_t, std::extents<std::size_t, 4, 4>>(benchComponents.data()));
	};
	BENCHMARK("Float")
	{
		constexpr std::array<float, 16uz> benchComponents = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
		return PonyEngine::Math::Matrix4x4<float>(std::mdspan<const float, std::extents<std::size_t, 4, 4>>(benchComponents.data()));
	};
#endif
}

TEST_CASE("Matrix column span constructor", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<PonyEngine::Math::Vector2<std::int32_t>, 3> columns = { PonyEngine::Math::Vector2<std::int32_t>(components[0], components[1]), PonyEngine::Math::Vector2<std::int32_t>(components[2], components[3]), PonyEngine::Math::Vector2<std::int32_t>(components[4], components[5]) };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(columns);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	std::array<PonyEngine::Math::Vector4<float>, 4uz> fColumns = { PonyEngine::Math::Vector4<float>(components[0], components[1], components[2], components[3]), PonyEngine::Math::Vector4<float>(components[4], components[5], components[6], components[7]), PonyEngine::Math::Vector4<float>(components[8], components[9], components[10], components[11]), PonyEngine::Math::Vector4<float>(components[12], components[13], components[14], components[15]) };
	auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(fColumns);
	REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array{ PonyEngine::Math::Vector4<std::int32_t>(-4, 2, 6, 8), PonyEngine::Math::Vector4<std::int32_t>(-1, 2, 5, -6), PonyEngine::Math::Vector4<std::int32_t>(8, 0, -3, 5), PonyEngine::Math::Vector4<std::int32_t>(-3, 1, 3, -9) });
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array{ PonyEngine::Math::Vector4<float>(-4.f, 2.f, 6.f, 8.f), PonyEngine::Math::Vector4<float>(-1.f, 2.f, 5.f, -6.f), PonyEngine::Math::Vector4<float>(8.f, 0.f, -3.f, 5.f), PonyEngine::Math::Vector4<float>(-3.f, 1.f, 3.f, -9.f) });
	};
#endif
}

TEST_CASE("Matrix predefined", "[Math][Matrix]")
{
	STATIC_REQUIRE(PonyEngine::Math::Matrix3x4<float>::Zero() == PonyEngine::Math::Matrix3x4<float>());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<std::int32_t>::Zero() == PonyEngine::Math::Matrix4x4<std::int32_t>());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Identity() == PonyEngine::Math::Matrix4x4<float>(1.f));
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::Identity() == PonyEngine::Math::Matrix2x2<std::int32_t>(1));
}

TEST_CASE("Matrix component", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Component(i) != values[i])
			{
				return false;
			}
		}
		auto copy = matrix;
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (copy.Component(i) != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Component(11uz);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Component(11uz);
	};
#endif
}

TEST_CASE("Matrix span", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (matrix.Span()[i] != values[i])
			{
				return false;
			}
		}
		auto copy = matrix;
		for (std::size_t i = 0; i < RowCount * ColumnCount; ++i)
		{
			if (copy.Span()[i] != values[i])
			{
				return false;
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));
}

TEST_CASE("Matrix spanMD", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (matrix.SpanMD()[j, i] != values[i + j * RowCount])
				{
					return false;
				}
			}
		}
		auto copy = matrix;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (copy.SpanMD()[j, i] != values[i + j * RowCount])
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));
}

TEST_CASE("Matrix column span", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U, std::size_t ComponentCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, std::span<const U, ComponentCount> values) constexpr
	{
		for (std::size_t j = 0; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0; i < RowCount; ++i)
			{
				if (matrix.Span(j)[i] != values[i + j * RowCount])
				{
					return false;
				}
			}
		}
		auto copy = matrix;
		for (std::size_t j = 0; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0; i < RowCount; ++i)
			{
				if (copy.Span(j)[i] != values[i + j * RowCount])
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(checkValues(matrix2x3, std::span<const std::int16_t, 16uz>(components.data(), components.size())));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(checkValues(matrix4x4, std::span<const std::int16_t, 16uz>(components.data(), components.size())));
}

TEST_CASE("Matrix row", "[Math][Matrix]")
{
	auto rowTest = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Vector4<T>& row0, const PonyEngine::Math::Vector4<T>& row1, const PonyEngine::Math::Vector4<T>& row2, const PonyEngine::Math::Vector4<T>& row3) constexpr
	{
		auto matrix = PonyEngine::Math::Matrix<T, RowCount, ColumnCount>();
		matrix.Row(0uz, row0);
		if (RowCount > 1uz)
		{
			matrix.Row(1uz, row1);
		}
		if (RowCount > 2uz)
		{
			matrix.Row(2uz, row2);
		}
		if (RowCount > 3uz)
		{
			matrix.Row(3uz, row3);
		}
		return matrix;
	};

	constexpr auto row0 = PonyEngine::Math::Vector4<std::int32_t>(-3, -4, 2, 1);
	constexpr auto row1 = PonyEngine::Math::Vector4<std::int32_t>(8, 10, 2, 5);
	constexpr auto row2 = PonyEngine::Math::Vector4<std::int32_t>(4, -2, -5, -3);
	constexpr auto row3 = PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4);

	constexpr auto matrix3x4 = rowTest.operator()<std::int32_t, 3, 4>(row0, row1, row2, row3);
	STATIC_REQUIRE(matrix3x4.Row(0uz) == row0);
	STATIC_REQUIRE(matrix3x4.Row(1uz) == row1);
	STATIC_REQUIRE(matrix3x4.Row(2uz) == row2);

	constexpr auto matrix4x4 = rowTest.operator()<float, 4, 4 >(static_cast<PonyEngine::Math::Vector4<float>>(row0), static_cast<PonyEngine::Math::Vector4<float>>(row1), static_cast<PonyEngine::Math::Vector4<float>>(row2), static_cast<PonyEngine::Math::Vector4<float>>(row3));
	STATIC_REQUIRE(matrix4x4.Row(0uz) == static_cast<PonyEngine::Math::Vector4<float>>(row0));
	STATIC_REQUIRE(matrix4x4.Row(1uz) == static_cast<PonyEngine::Math::Vector4<float>>(row1));
	STATIC_REQUIRE(matrix4x4.Row(2uz) == static_cast<PonyEngine::Math::Vector4<float>>(row2));
	STATIC_REQUIRE(matrix4x4.Row(3uz) == static_cast<PonyEngine::Math::Vector4<float>>(row3));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Row(1uz, PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4));
		return matrix.Row(2uz);
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Row(1uz, PonyEngine::Math::Vector4<float>(9.f, 0.f, -1.f, -4.f));
		return matrix.Row(2uz);
	};
#endif
}

TEST_CASE("Matrix column", "[Math][Matrix]")
{
	auto columnTest = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Vector4<T>& column0, const PonyEngine::Math::Vector4<T>& column1, const PonyEngine::Math::Vector4<T>& column2, const PonyEngine::Math::Vector4<T>& column3) constexpr
	{
		auto matrix = PonyEngine::Math::Matrix<T, RowCount, ColumnCount>();
		matrix.Column(0uz, column0);
		if (ColumnCount > 1uz)
		{
			matrix.Column(1uz, column1);
		}
		if (ColumnCount > 2uz)
		{
			matrix.Column(2uz, column2);
		}
		if (ColumnCount > 3uz)
		{
			matrix.Column(3uz, column3);
		}
		return matrix;
	};

	constexpr auto column0 = PonyEngine::Math::Vector4<std::int32_t>(-3, -4, 2, 1);
	constexpr auto column1 = PonyEngine::Math::Vector4<std::int32_t>(8, 10, 2, 5);
	constexpr auto column2 = PonyEngine::Math::Vector4<std::int32_t>(4, -2, -5, -3);
	constexpr auto column3 = PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4);

	constexpr auto matrix4x3 = columnTest.operator()<std::int32_t, 4, 3>(column0, column1, column2, column3);
	STATIC_REQUIRE(matrix4x3.Column(0uz) == column0);
	STATIC_REQUIRE(matrix4x3.Column(1uz) == column1);
	STATIC_REQUIRE(matrix4x3.Column(2uz) == column2);

	constexpr auto matrix4x4 = columnTest.operator()<float, 4, 4>(static_cast<PonyEngine::Math::Vector4<float>>(column0), static_cast<PonyEngine::Math::Vector4<float>>(column1), static_cast<PonyEngine::Math::Vector4<float>>(column2), static_cast<PonyEngine::Math::Vector4<float>>(column3));
	STATIC_REQUIRE(matrix4x4.Column(0uz) == static_cast<PonyEngine::Math::Vector4<float>>(column0));
	STATIC_REQUIRE(matrix4x4.Column(1uz) == static_cast<PonyEngine::Math::Vector4<float>>(column1));
	STATIC_REQUIRE(matrix4x4.Column(2uz) == static_cast<PonyEngine::Math::Vector4<float>>(column2));
	STATIC_REQUIRE(matrix4x4.Column(3uz) == static_cast<PonyEngine::Math::Vector4<float>>(column3));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Column(1uz, PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4));
		return matrix.Column(2uz);
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Column(1uz, PonyEngine::Math::Vector4<float>(9.f, 0.f, -1.f, -4.f));
		return matrix.Column(2uz);
	};
#endif
}

TEST_CASE("Matrix diagonal", "[Math][Matrix]")
{
	auto diagonal = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Matrix<T, Size, Size>& matrix, const PonyEngine::Math::Vector<T, Size>& diagonal) constexpr
	{
		auto copy = matrix;
		copy.Diagonal(diagonal);
		return copy;
	};
	auto diagCheck = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Matrix<T, Size, Size>& matrix, const PonyEngine::Math::Vector<T, Size>& diagonal) constexpr
	{
		auto copy = matrix;
		for (std::size_t j = 0uz; j < Size; ++j)
		{
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				copy[i, j] = i == j ? diagonal[j] : matrix[i, j];
			}
		}
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8]);
	constexpr auto diag3 = PonyEngine::Math::Vector3<std::int32_t>(-8, 2, 4);
	constexpr auto matrix3x3D = diagonal(matrix3x3, diag3);
	STATIC_REQUIRE(matrix3x3D.Diagonal() == diag3);
	STATIC_REQUIRE(matrix3x3D == diagCheck(matrix3x3, diag3));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto diag4 = PonyEngine::Math::Vector4<float>(6.f, 2.f, -5.f, -3.f);
	constexpr auto matrix4x4D = diagonal(matrix4x4, diag4);
	STATIC_REQUIRE(matrix4x4D.Diagonal() == diag4);
	STATIC_REQUIRE(matrix4x4D == diagCheck(matrix4x4, diag4));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Diagonal(PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4));
		return matrix.Diagonal();
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.Diagonal(PonyEngine::Math::Vector4<float>(9.f, 0.f, -1.f, -4.f));
		return matrix.Diagonal();
	};
#endif
}

TEST_CASE("Matrix counterdiagonal", "[Math][Matrix]")
{
	auto counterdiagonal = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Matrix<T, Size, Size>& matrix, const PonyEngine::Math::Vector<T, Size>& counterdiagonal) constexpr
	{
		auto copy = matrix;
		copy.CounterDiagonal(counterdiagonal);
		return copy;
	};
	auto diagCheck = []<PonyEngine::Type::Arithmetic T, std::size_t Size>(const PonyEngine::Math::Matrix<T, Size, Size>& matrix, const PonyEngine::Math::Vector<T, Size>& counterdiagonal) constexpr
	{
		auto copy = matrix;
		for (std::size_t j = 0uz; j < Size; ++j)
		{
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				copy[i, j] = i + j == Size - 1uz ? counterdiagonal[j] : matrix[i, j];
			}
		}
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8]);
	constexpr auto diag3 = PonyEngine::Math::Vector3<std::int32_t>(-8, 2, 4);
	constexpr auto matrix3x3D = counterdiagonal(matrix3x3, diag3);
	STATIC_REQUIRE(matrix3x3D.CounterDiagonal() == diag3);
	STATIC_REQUIRE(matrix3x3D == diagCheck(matrix3x3, diag3));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto diag4 = PonyEngine::Math::Vector4<float>(6.f, 2.f, -5.f, -3.f);
	constexpr auto matrix4x4D = counterdiagonal(matrix4x4, diag4);
	STATIC_REQUIRE(matrix4x4D.CounterDiagonal() == diag4);
	STATIC_REQUIRE(matrix4x4D == diagCheck(matrix4x4, diag4));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.CounterDiagonal(PonyEngine::Math::Vector4<std::int32_t>(9, 0, -1, -4));
		return matrix.CounterDiagonal();
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		matrix.CounterDiagonal(PonyEngine::Math::Vector4<float>(9.f, 0.f, -1.f, -4.f));
		return matrix.CounterDiagonal();
	};
#endif
}

TEST_CASE("Matrix trace", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8]);
	STATIC_REQUIRE(matrix3x3.Trace() == 3);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Trace(), -14.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Trace();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Trace();
	};
#endif
}

TEST_CASE("Matrix determinant", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 25uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9, 10, -1, 0, 3, 4, -5, 3, -6, 8 };

	constexpr auto matrix1x1 = PonyEngine::Math::Matrix<std::uint32_t, 1, 1>(components[0]);
	STATIC_REQUIRE(matrix1x1.Determinant() == -4);

	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<float>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix2x2.Determinant(), -44.f));

	constexpr auto matrix3x3 = PonyEngine::Math::Matrix3x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8]);
	STATIC_REQUIRE(matrix3x3.Determinant() == -382);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Determinant(), -120.f));

	constexpr auto matrix5x5 = PonyEngine::Math::Matrix<std::int32_t, 5, 5>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15], components[16], components[17], components[18], components[19], components[20], components[21], components[22], components[23], components[24]);
	STATIC_REQUIRE(matrix5x5.Determinant() == -10123);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int 1x1")
	{
		return PonyEngine::Math::Matrix<std::int32_t, 1, 1>(std::array<std::int32_t, 1uz>{ -4 }).Determinant();
	};
	BENCHMARK("Int 2x2")
	{
		return PonyEngine::Math::Matrix2x2<std::int32_t>(std::array<std::int32_t, 4uz>{ -4, 2, 6, 8 }).Determinant();
	};
	BENCHMARK("Int 3x3")
	{
		return PonyEngine::Math::Matrix3x3<std::int32_t>(std::array<std::int32_t, 9uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8 }).Determinant();
	};
	BENCHMARK("Int 4x4")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Determinant();
	};
	BENCHMARK("Int 5x5")
	{
		return PonyEngine::Math::Matrix<std::int32_t, 5, 5>(std::array<std::int32_t, 25uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9, 10, -1, 0, 3, 4, -5, 3, -6, 8 }).Determinant();
	};
	BENCHMARK("Float 1x1")
	{
		return PonyEngine::Math::Matrix<float, 1, 1>(std::array<float, 1uz>{ -4 }).Determinant();
	};
	BENCHMARK("Float 2x2")
	{
		return PonyEngine::Math::Matrix2x2<float>(std::array<float, 4uz>{ -4, 2, 6, 8 }).Determinant();
	};
	BENCHMARK("Float 3x3")
	{
		return PonyEngine::Math::Matrix3x3<float>(std::array<float, 9uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8 }).Determinant();
	};
	BENCHMARK("Float 4x4")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Determinant();
	};
	BENCHMARK("Float 5x5")
	{
		return PonyEngine::Math::Matrix<float, 5, 5>(std::array<float, 25uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9, 10, -1, 0, 3, 4, -5, 3, -6, 8 }).Determinant();
	};
#endif
}

TEST_CASE("Matrix transpose", "[Math][Matrix]")
{
	auto checkValues = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, ColumnCount, RowCount>& matrixT) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (matrix[i, j] != matrixT[j, i])
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3T = matrix2x3.Transpose();
	STATIC_REQUIRE(checkValues(matrix2x3, matrix2x3T));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4T = matrix4x4.Transpose();
	STATIC_REQUIRE(checkValues(matrix4x4, matrix4x4T));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Transpose();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Transpose();
	};
#endif
}

TEST_CASE("Matrix submatrix", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto expectedSubMatrix2x3 = PonyEngine::Math::Matrix<std::int32_t, 1, 2>(components[0], components[2]);
	STATIC_REQUIRE(matrix2x3.Submatrix(1uz, 2uz) == expectedSubMatrix2x3);
	REQUIRE(matrix2x3.Submatrix(1uz, 2uz) == expectedSubMatrix2x3);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto expectedSubMatrix4x4 = PonyEngine::Math::Matrix<float, 3, 3>(components[0], components[2], components[3], components[4], components[6], components[7], components[12], components[14], components[15]);
	STATIC_REQUIRE(matrix4x4.Submatrix(1uz, 2uz) == expectedSubMatrix4x4);
	REQUIRE(matrix4x4.Submatrix(1uz, 2uz) == expectedSubMatrix4x4);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Submatrix(1uz, 1uz);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Submatrix(1uz, 1uz);
	};
#endif
}

TEST_CASE("Matrix minor", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE(matrix2x2.Minor(1, 0) == 6);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Minor(2uz, 1uz), 198.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Minor(2uz, 1uz);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Minor(2uz, 1uz);
	};
#endif
}

TEST_CASE("Matrix minor matrix", "[Math][Matrix]")
{
	auto check = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& minors) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_floating_point_v<T>)
				{
					if (!PonyEngine::Math::AreAlmostEqual(minors[i, j], matrix.Minor(i, j)))
					{
						return false;
					}
				}
				else if (minors[i, j] != matrix.Minor(i, j))
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE(check(matrix2x2, matrix2x2.MinorMatrix()));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(check(matrix4x4, matrix4x4.MinorMatrix()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).MinorMatrix();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).MinorMatrix();
	};
#endif
}

TEST_CASE("Matrix cofactor", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE(matrix2x2.Cofactor(1, 0) == -6);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Cofactor(2uz, 2uz), 106.f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Cofactor(2uz, 1uz);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Cofactor(2uz, 1uz);
	};
#endif
}

TEST_CASE("Matrix cofactor matrix", "[Math][Matrix]")
{
	auto check = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& cofactors) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_floating_point_v<T>)
				{
					if (!PonyEngine::Math::AreAlmostEqual(cofactors[i, j], matrix.Cofactor(i, j)))
					{
						return false;
					}
				}
				else if (cofactors[i, j] != matrix.Cofactor(i, j))
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE(check(matrix2x2, matrix2x2.CofactorMatrix()));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(check(matrix4x4, matrix4x4.CofactorMatrix()));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).CofactorMatrix();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).CofactorMatrix();
	};
#endif
}

TEST_CASE("Matrix adjugate", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	constexpr auto matrix2x2A = PonyEngine::Math::Matrix2x2<std::int32_t>(8, -2, -6, -4);
	STATIC_REQUIRE(matrix2x2.Adjugate() == matrix2x2A);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4A = PonyEngine::Math::Matrix4x4<float>(31.f, -78.f, 26.f, 94.f, -183.f, 414.f, -258.f, -582.f, 71.f, -198.f, 106.f, 254.f, -7.f, 6.f, -2.f, 2.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Adjugate(), matrix4x4A));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Adjugate();
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Adjugate();
	};
#endif
}

TEST_CASE("Matrix inverse", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<float>(components[0], components[1], components[2], components[3]);
	constexpr auto matrix2x2I = PonyEngine::Math::Matrix2x2<float>(-2.f/11.f, 1.f/22.f, 3.f/22.f, 1.f/11.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix2x2.Inverse(), matrix2x2I));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4I = PonyEngine::Math::Matrix4x4<float>(-31.f/120.f, 13.f/20.f, -13.f/60.f, -47.f/60.f, 61.f/40.f, -69.f/20.f, 43.f/20.f, 97.f/20.f, -71/120.f, 33.f/20.f, -53.f/60.f, -127.f/60.f, 7.f/120.f, -1.f/20.f, 1.f/60.f, -1.f/60.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4.Inverse(), matrix4x4I));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).Inverse();
	};
#endif
}

TEST_CASE("Matrix isZero, isIdentity", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE_FALSE(matrix2x3.IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x3<std::int32_t>::Zero().IsZero());

	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	STATIC_REQUIRE_FALSE(matrix2x2.IsZero());
	STATIC_REQUIRE_FALSE(matrix2x2.IsIdentity());
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::Zero().IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix2x2<std::int32_t>::Zero().IsIdentity());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix2x2<std::int32_t>::Identity().IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Matrix2x2<std::int32_t>::Identity().IsIdentity());

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE_FALSE(matrix4x4.IsZero());
	STATIC_REQUIRE_FALSE(matrix4x4.IsAlmostZero());
	STATIC_REQUIRE(matrix4x4.IsAlmostZero(100.f));
	STATIC_REQUIRE_FALSE(matrix4x4.IsIdentity());
	STATIC_REQUIRE_FALSE(matrix4x4.IsAlmostIdentity());
	STATIC_REQUIRE(matrix4x4.IsAlmostIdentity(100.f));
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Zero().IsZero());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Zero().IsAlmostZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix4x4<float>::Zero().IsIdentity());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix4x4<float>::Zero().IsAlmostIdentity());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Zero().IsAlmostIdentity(10.f));
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix4x4<float>::Identity().IsZero());
	STATIC_REQUIRE_FALSE(PonyEngine::Math::Matrix4x4<float>::Identity().IsAlmostZero());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Identity().IsAlmostZero(10.f));
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Identity().IsIdentity());
	STATIC_REQUIRE(PonyEngine::Math::Matrix4x4<float>::Identity().IsAlmostIdentity());
}

TEST_CASE("Matrix isFinite", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix) constexpr
	{
		if (!matrix.IsFinite())
		{
			return false;
		}
		auto copy = matrix;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				copy[i, j] = std::numeric_limits<T>::quiet_NaN();
				if (copy.IsFinite())
				{
					return false;
				}
				copy[i, j] = matrix[i, j];
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(test(matrix4x4));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, std::numeric_limits<float>::quiet_NaN() }).IsFinite();
	};
#endif
}

TEST_CASE("Matrix multiply this", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrixM) constexpr
	{
		auto copy = matrix;
		copy.Multiply(matrixM);
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_integral_v<T>)
				{
					if (copy[i, j] != matrix[i, j] * matrixM[i, j])
					{
						return false;
					}
				}
				else if (!PonyEngine::Math::AreAlmostEqual(copy[i, j], matrix[i, j] * matrixM[i, j]))
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 0, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(test(matrix2x3, matrix2x3M));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(test(matrix4x4, matrix4x4M));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 0, 3, -4, 4, 7, -1, 2, 5, 8 });
		matrix.Multiply(matrixM);
		return matrix;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 0, 3, -4, 4, 7, -1, 2, 5, 8 });
		matrix.Multiply(matrixM);
		return matrix;
	};
#endif
}

TEST_CASE("Matrix divide this", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrixM) constexpr
	{
		auto copy = matrix;
		copy.Divide(matrixM);
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_integral_v<T>)
				{
					if (copy[i, j] != matrix[i, j] / matrixM[i, j])
					{
						return false;
					}
				}
				else if (!PonyEngine::Math::AreAlmostEqual(copy[i, j], matrix[i, j] / matrixM[i, j]))
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]) * 10;
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(test(matrix2x3, matrix2x3M));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(test(matrix4x4, matrix4x4M));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		matrix.Divide(matrixM);
		return matrix;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		matrix.Divide(matrixM);
		return matrix;
	};
#endif
}

TEST_CASE("Matrix to string", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	std::string expected2x3 = std::format("[{}, {}, {}][{}, {}, {}]", matrix2x3[0, 0], matrix2x3[0, 1], matrix2x3[0, 2], matrix2x3[1, 0], matrix2x3[1, 1], matrix2x3[1, 2]);
	REQUIRE(matrix2x3.ToString() == expected2x3);
	std::ostringstream oss;
	oss << matrix2x3;
	REQUIRE(oss.str() == expected2x3);
	REQUIRE(std::format("{}", matrix2x3) == expected2x3);
	expected2x3 = std::format("[{}, {}, {}]\n[{}, {}, {}]\n", matrix2x3[0, 0], matrix2x3[0, 1], matrix2x3[0, 2], matrix2x3[1, 0], matrix2x3[1, 1], matrix2x3[1, 2]);
	REQUIRE(matrix2x3.ToString(true) == expected2x3);
	REQUIRE(std::format("{:m}", matrix2x3) == expected2x3);
	REQUIRE(std::format("{:M}", matrix2x3) == expected2x3);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	std::string expected4x4 = std::format("[{}, {}, {}, {}][{}, {}, {}, {}][{}, {}, {}, {}][{}, {}, {}, {}]", matrix4x4[0, 0], matrix4x4[0, 1], matrix4x4[0, 2], matrix4x4[0, 3], matrix4x4[1, 0], matrix4x4[1, 1], matrix4x4[1, 2], matrix4x4[1, 3], matrix4x4[2, 0], matrix4x4[2, 1], matrix4x4[2, 2], matrix4x4[2, 3], matrix4x4[3, 0], matrix4x4[3, 1], matrix4x4[3, 2], matrix4x4[3, 3]);
	REQUIRE(matrix4x4.ToString() == expected4x4);
	oss = std::ostringstream();
	oss << matrix4x4;
	REQUIRE(oss.str() == expected4x4);
	REQUIRE(std::format("{}", matrix4x4) == expected4x4);
	expected4x4 = std::format("[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n", matrix4x4[0, 0], matrix4x4[0, 1], matrix4x4[0, 2], matrix4x4[0, 3], matrix4x4[1, 0], matrix4x4[1, 1], matrix4x4[1, 2], matrix4x4[1, 3], matrix4x4[2, 0], matrix4x4[2, 1], matrix4x4[2, 2], matrix4x4[2, 3], matrix4x4[3, 0], matrix4x4[3, 1], matrix4x4[3, 2], matrix4x4[3, 3]);
	REQUIRE(matrix4x4.ToString(true) == expected4x4);
	REQUIRE(std::format("{:m}", matrix4x4) == expected4x4);
	REQUIRE(std::format("{:M}", matrix4x4) == expected4x4);

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).ToString();
	};
	BENCHMARK("Int multiline")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).ToString(true);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).ToString();
	};
	BENCHMARK("Float multiline")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }).ToString(true);
	};
#endif
}

TEST_CASE("Matrix cast", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, PonyEngine::Type::Arithmetic U, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<U, RowCount, ColumnCount>& matrixO) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (static_cast<U>(matrix[i, j]) != matrixO[i, j])
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4D = static_cast<PonyEngine::Math::Matrix4x4<double>>(matrix4x4);
	STATIC_REQUIRE(test(matrix4x4, matrix4x4D));
}

TEST_CASE("Matrix access by index", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const std::span<const U, RowCount * ColumnCount> span) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (matrix[i, j] != span[i + j * RowCount])
				{
					return false;
				}
			}
		}
		auto copy = matrix;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (copy[i, j] != span[i + j * RowCount])
				{
					return false;
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(test(matrix2x3, std::span<const std::int16_t, 6>(components.data(), 6)));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(test(matrix4x4, std::span<const std::int16_t, 16>(components.data(), 16)));
}

TEST_CASE("Matrix copy assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix) constexpr
	{
		auto copy = PonyEngine::Math::Matrix<T, RowCount, ColumnCount>();
		copy = matrix;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(assign(matrix2x3) == matrix2x3);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(assign(matrix4x4) == matrix4x4);
}

TEST_CASE("Matrix move assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix) constexpr
	{
		auto copy = matrix;
		auto moved = PonyEngine::Math::Matrix<T, RowCount, ColumnCount>();
		moved = std::move(copy);
		return moved;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(assign(matrix2x3) == matrix2x3);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(assign(matrix4x4) == matrix4x4);
}

TEST_CASE("Matrix sum assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& other) constexpr
	{
		auto copy = matrix;
		copy += other;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(assign(matrix2x3, matrix2x3M) == matrix2x3 + matrix2x3M);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(assign(matrix4x4, matrix4x4M), matrix4x4 + matrix4x4M));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix += matrixM;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix += matrixM;
	};
#endif
}

TEST_CASE("Matrix subtraction assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&other) constexpr
	{
		auto copy = matrix;
		copy -= other;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(assign(matrix2x3, matrix2x3M) == matrix2x3 - matrix2x3M);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(assign(matrix4x4, matrix4x4M), matrix4x4 - matrix4x4M));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix -= matrixM;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix -= matrixM;
	};
#endif
}

TEST_CASE("Matrix product assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const U multiplier) constexpr
	{
		auto copy = matrix;
		copy *= multiplier;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(assign(matrix2x3, 3) == matrix2x3 * 3);
	STATIC_REQUIRE(assign(matrix2x3, 3.f) == matrix2x3 * 3.f);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(assign(matrix4x4, 2.5f), matrix4x4 * 2.5f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix *= 3;
	};
	BENCHMARK("Int by float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix *= 3.f;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix *= 3.f;
	};
#endif
}

TEST_CASE("Matrix product matrix assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& other) constexpr
	{
		auto copy = matrix;
		copy *= other;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x2 = PonyEngine::Math::Matrix2x2<std::int32_t>(components[0], components[1], components[2], components[3]);
	constexpr auto matrix2x2M = PonyEngine::Math::Matrix2x2<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3]);
	STATIC_REQUIRE(assign(matrix2x2, matrix2x2M) == matrix2x2 * matrix2x2M);
	STATIC_REQUIRE(assign(matrix2x2, matrix2x2M) == matrix2x2 * matrix2x2M);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(assign(matrix4x4, matrix4x4M), matrix4x4 * matrix4x4M));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix *= matrixM;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		const auto matrixM = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
		return matrix *= matrixM;
	};
#endif
}

TEST_CASE("Matrix division assignment", "[Math][Matrix]")
{
	auto assign = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, const U multiplier) constexpr
	{
		auto copy = matrix;
		copy /= multiplier;
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(assign(matrix2x3, 3) == matrix2x3 / 3);
	STATIC_REQUIRE(assign(matrix2x3, 3.f) == matrix2x3 / 3.f);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(assign(matrix4x4, 2.5f), matrix4x4 / 2.5f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix /= 3;
	};
	BENCHMARK("Int by float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix /= 3.f;
	};
	BENCHMARK("Float")
	{
		auto matrix = PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
		return matrix /= 3.f;
	};
#endif
}

TEST_CASE("Matrix equals", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix) constexpr
	{
		auto copy = matrix;
		if (copy != matrix)
		{
			return false;
		}
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				const T prev = copy[i, j];
				copy[i, j] -= T{1};
				if (copy == matrix)
				{
					return false;
				}
				copy[i, j] = prev;
			}
		}
		if constexpr (std::is_floating_point_v<T>)
		{
			for (std::size_t j = 0uz; j < ColumnCount; ++j)
			{
				for (std::size_t i = 0uz; i < RowCount; ++i)
				{
					const T prev = copy[i, j];
					copy[i, j] -= T{0.000000000001};
					if (copy == matrix)
					{
						return false;
					}
					copy[i, j] = prev;
				}
			}
		}
		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(test(matrix2x3));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(test(matrix4x4));
}

TEST_CASE("Matrix multiply", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& other, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& result) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_integral_v<T>)
				{
					if (matrix[i, j] * other[i, j] != result[i, j])
					{
						return false;
					}
				}
				else
				{
					if (!PonyEngine::Math::AreAlmostEqual(matrix[i, j] * other[i, j], result[i, j]))
					{
						return false;
					}
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	constexpr auto matrix2x3P = PonyEngine::Math::Multiply(matrix2x3, matrix2x3M);
	STATIC_REQUIRE(test(matrix2x3, matrix2x3M, matrix2x3P));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	constexpr auto matrix4x4P = PonyEngine::Math::Multiply(matrix4x4, matrix4x4M);
	STATIC_REQUIRE(test(matrix4x4, matrix4x4M, matrix4x4P));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 }));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Multiply(PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 }));
	};
#endif
}

TEST_CASE("Matrix divide", "[Math][Matrix]")
{
	auto test = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&matrix, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&other, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&result) constexpr
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if constexpr (std::is_integral_v<T>)
				{
					if (matrix[i, j] / other[i, j] != result[i, j])
					{
						return false;
					}
				}
				else
				{
					if (!PonyEngine::Math::AreAlmostEqual(matrix[i, j] / other[i, j], result[i, j]))
					{
						return false;
					}
				}
			}
		}

		return true;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	constexpr auto matrix2x3P = PonyEngine::Math::Divide(matrix2x3, matrix2x3M);
	STATIC_REQUIRE(test(matrix2x3, matrix2x3M, matrix2x3P));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	constexpr auto matrix4x4P = PonyEngine::Math::Divide(matrix4x4, matrix4x4M);
	STATIC_REQUIRE(test(matrix4x4, matrix4x4M, matrix4x4P));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 }));
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Divide(PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 }));
	};
#endif
}

TEST_CASE("Matrix normalize columns", "[Math][Matrix]")
{
	auto normalize = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix)
	{
		auto copy = matrix;
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			copy.Column(i).Normalize();
		}
		return copy;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<float>(components[0], components[1], components[2], components[3], components[4], components[5]);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalize(matrix2x3), PonyEngine::Math::NormalizeColumns(matrix2x3)));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(normalize(matrix4x4), PonyEngine::Math::NormalizeColumns(matrix4x4)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }));
	};
#endif
}

TEST_CASE("Matrix are almost equal", "[Math][Matrix]")
{
	auto test = []<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix) constexpr
	{
		auto copy = matrix;
		if (!PonyEngine::Math::AreAlmostEqual(copy, matrix))
		{
			return false;
		}
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				const T prev = copy[i, j];
				copy[i, j] -= T{1};
				if (PonyEngine::Math::AreAlmostEqual(copy, matrix))
				{
					return false;
				}
				if (!PonyEngine::Math::AreAlmostEqual(copy, matrix, 100.f))
				{
					return false;
				}
				copy[i, j] = prev;
			}
		}
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				const T prev = copy[i, j];
				copy[i, j] -= T{0.000000000001};
				if (!PonyEngine::Math::AreAlmostEqual(copy, matrix))
				{
					return false;
				}
				copy[i, j] = prev;
			}
		}
		return true;
	};

	constexpr std::array<float, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<float>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(test(matrix2x3));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(test(matrix4x4));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 })) | PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }), PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }));
	};
#endif
}

TEST_CASE("Matrix sum", "[Math][Matrix]")
{
	auto sum = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& lhs, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& rhs) constexpr
	{
		PonyEngine::Math::Matrix<T, RowCount, ColumnCount> result;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				result[i, j] = lhs[i, j] + rhs[i, j];
			}
		}

		return result;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(matrix2x3 + matrix2x3M == sum(matrix2x3, matrix2x3M));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 + matrix4x4M, sum(matrix4x4, matrix4x4M)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) + PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) + PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
#endif
}

TEST_CASE("Matrix negate", "[Math][Matrix]")
{
	auto negate = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& lhs) constexpr
	{
		PonyEngine::Math::Matrix<T, RowCount, ColumnCount> result;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				result[i, j] = -lhs[i, j];
			}
		}

		return result;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(-matrix2x3 == negate(matrix2x3));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(-matrix4x4, negate(matrix4x4)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return -PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
	};
	BENCHMARK("Float")
	{
		return -PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 });
	};
#endif
}

TEST_CASE("Matrix subtraction", "[Math][Matrix]")
{
	auto subtract = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& lhs, const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& rhs) constexpr
	{
		PonyEngine::Math::Matrix<T, RowCount, ColumnCount> result;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				result[i, j] = lhs[i, j] - rhs[i, j];
			}
		}

		return result;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix2x3M = PonyEngine::Math::Matrix2x3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	STATIC_REQUIRE(matrix2x3 - matrix2x3M == subtract(matrix2x3, matrix2x3M));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 - matrix4x4M, subtract(matrix4x4, matrix4x4M)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) - PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) - PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
#endif
}

TEST_CASE("Matrix product", "[Math][Matrix]")
{
	auto multiply = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& lhs, const U multiplier) constexpr
	{
		PonyEngine::Math::Matrix<T, RowCount, ColumnCount> result;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				result[i, j] = static_cast<T>(lhs[i, j] * multiplier);
			}
		}

		return result;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(matrix2x3 * 5 == multiply(matrix2x3, 5));
	STATIC_REQUIRE(5 * matrix2x3 == multiply(matrix2x3, 5));
	STATIC_REQUIRE(matrix2x3 * 5.5f == multiply(matrix2x3, 5.5f));
	STATIC_REQUIRE(5.5f * matrix2x3 == multiply(matrix2x3, 5.5f));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 * 2.f, multiply(matrix4x4, 2.f)));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(2.f * matrix4x4, multiply(matrix4x4, 2.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * 3;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * 3.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * 3.f;
	};
#endif
}

TEST_CASE("Matrix product matrix", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto matrix3x2M = PonyEngine::Math::Matrix<std::int32_t, 3, 2>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5]);
	constexpr auto matrix2x2P = PonyEngine::Math::Matrix2x2<std::int32_t>(9, 30, 50, 14);
	STATIC_REQUIRE(matrix2x3 * matrix3x2M == matrix2x2P);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto matrix4x4M = PonyEngine::Math::Matrix4x4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3], componentsM[4], componentsM[5], componentsM[6], componentsM[7], componentsM[8], componentsM[9], componentsM[10], componentsM[11], componentsM[12], componentsM[13], componentsM[14], componentsM[15]);
	constexpr auto matrix4x4P = PonyEngine::Math::Matrix4x4<float>(24.f, 1.f, -3.f, 84.f, -83.f, 15.f, 65.f, -49.f, 3.f, 5.f, 7.f, 5.f, 18.f, 10.f, 13.f, -67.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 * matrix4x4M, matrix4x4P));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 });
	};
#endif
}

TEST_CASE("Matrix product vector", "[Math][Matrix]")
{
	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr std::array<std::int16_t, 16uz> componentsM = { 2, 3, 1, -9, 3, 4, -8, 1, 3, -4, 4, 7, -1, 2, 5, 8 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	constexpr auto vector3 = PonyEngine::Math::Vector3<std::int32_t>(componentsM[0], componentsM[1], componentsM[2]);
	constexpr auto vector2P = PonyEngine::Math::Vector2<std::int32_t>(9, 30);
	STATIC_REQUIRE(matrix2x3 * vector3 == vector2P);

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	constexpr auto vector4 = PonyEngine::Math::Vector4<float>(componentsM[0], componentsM[1], componentsM[2], componentsM[3]);
	constexpr auto vecto4P = PonyEngine::Math::Vector4<float>(24.f, 1.f, -3.f, 84.f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 * vector4, vecto4P));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * PonyEngine::Math::Vector4<std::int32_t>(2, 3, 1, -9);
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) * PonyEngine::Math::Vector4<float>(2.f, 3.f, 1.f, -9.f);
	};
#endif
}

TEST_CASE("Matrix division", "[Math][Matrix]")
{
	auto divide = []<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, PonyEngine::Type::Arithmetic U>(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>&lhs, const U divisor) constexpr
	{
		PonyEngine::Math::Matrix<T, RowCount, ColumnCount> result;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				result[i, j] = static_cast<T>(lhs[i, j] / divisor);
			}
		}

		return result;
	};

	constexpr std::array<std::int16_t, 16uz> components = { -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 };
	constexpr auto matrix2x3 = PonyEngine::Math::Matrix2x3<std::int32_t>(components[0], components[1], components[2], components[3], components[4], components[5]);
	STATIC_REQUIRE(matrix2x3 / 5 == divide(matrix2x3, 5));
	STATIC_REQUIRE(matrix2x3 / 5.5f == divide(matrix2x3, 5.5f));

	constexpr auto matrix4x4 = PonyEngine::Math::Matrix4x4<float>(components[0], components[1], components[2], components[3], components[4], components[5], components[6], components[7], components[8], components[9], components[10], components[11], components[12], components[13], components[14], components[15]);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(matrix4x4 / 2.f, divide(matrix4x4, 2.f)));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Int")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) / 3;
	};
	BENCHMARK("Int by float")
	{
		return PonyEngine::Math::Matrix4x4<std::int32_t>(std::array<std::int32_t, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) / 3.f;
	};
	BENCHMARK("Float")
	{
		return PonyEngine::Math::Matrix4x4<float>(std::array<float, 16uz>{ -4, 2, 6, 8, -1, 2, 5, -6, 8, 0, -3, 5, -3, 1, 3, -9 }) / 3.f;
	};
#endif
}
