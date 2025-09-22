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

template<std::floating_point T>
constexpr T FixRotation(const T angle)
{
	if (PonyEngine::Math::AreAlmostEqual(angle, -std::numbers::pi_v<T>))
	{
		return std::numbers::pi_v<T>;
	}
	if (PonyEngine::Math::AreAlmostEqual(angle, std::numbers::pi_v<T> * 2.f) || PonyEngine::Math::AreAlmostEqual(angle, -std::numbers::pi_v<T> * 2.f))
	{
		return T{0};
	}

	return angle;
}

template<std::floating_point T>
constexpr PonyEngine::Math::Vector3<T> FixRotation(const PonyEngine::Math::Vector3<T>& vector)
{
	auto copy = vector;
	for (std::size_t i = 0; i < PonyEngine::Math::Vector3<T>::ComponentCount; ++i)
	{
		copy[i] = FixRotation(copy[i]);
	}

	return copy;
}

TEST_CASE("Rotation angle from rotation matrix", "[Math][Transformations]")
{
	auto matrix = PonyEngine::Math::Matrix2x2<float>::Identity();
	float angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, angle));

	matrix = PonyEngine::Math::Matrix2x2<float>(0.f, 1.f, -1.f, 0.f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, angle));

	matrix = -PonyEngine::Math::Matrix2x2<float>::Identity();
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, std::abs(angle)));

	matrix = PonyEngine::Math::Matrix2x2<float>(0.f, -1.f, 1.f, 0.f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-std::numbers::pi_v<float> / 2.f, angle));

	matrix = PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	matrix = PonyEngine::Math::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.147f, angle, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	matrix = PonyEngine::Math::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.478f, angle, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	matrix = PonyEngine::Math::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-0.698f, angle, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationAngle(PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f));
	};
#endif
}

TEST_CASE("Rotation quaternion from rotation matrix", "[Math][Transformations]")
{
	auto matrix = PonyEngine::Math::Matrix3x3<float>(0.83f, 0.482f, 0.281f, -0.436f, 0.245f, 0.866f, 0.348f, -0.841f, 0.413f);
	auto quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.541f, 0.021f, 0.291f, 0.789f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.105f, 0.403f, 0.909f, -0.932f, -0.36f, 0.052f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.459f, -0.288f, 0.685f, 0.487f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.888f, -0.436f, -0.141f, 0.299f, -0.318f, -0.9f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.064f, -0.538f, 0.809f, -0.227f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.57f, -0.16f, -0.806f, 0.744f, 0.516f, 0.424f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.4f, 0.365f, -0.286f, 0.791f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.261f, 0.482f, -0.837f, 0.957f, 0.245f, -0.157f, 0.129f, -0.841f, -0.525f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.505f, 0.713f, -0.35f, 0.339f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.978f, 0.206f, 0.007f, 0.099f, -0.499f, 0.861f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.864f, 0.088f, 0.054f, 0.492f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.763f, -0.206f, 0.612f, -0.62f, -0.499f, 0.605f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.832f, -0.248f, 0.238f, 0.434f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.906f, -0.344f, 0.246f, -0.382f, 0.417f, -0.824f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.216f, 0.841f, -0.495f, -0.019f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.913f, 0.399f, 0.09f, 0.068f, 0.365f, -0.929f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.144f, 0.812f, -0.545f, -0.152f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.378f, 0.511f, -0.772f, 0.833f, -0.175f, -0.524f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, 0.625f, -0.546f, 0.147f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.837f, -0.498f, 0.227f, -0.37f, -0.21f, 0.905f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.776f, -0.28f, -0.057f, 0.563f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.338f, -0.455f, 0.824f, -0.817f, 0.292f, 0.497f, -0.466f, -0.841f, -0.273f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.574f, -0.554f, 0.156f, 0.583f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.727f, 0.298f, 0.618f, -0.661f, 0.546f, 0.515f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.383f, -0.237f, 0.283f, 0.847f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.259f, 0.621f, 0.739f, -0.948f, -0.018f, -0.317f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.203f, -0.402f, 0.684f, 0.574f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.216f, -0.557f, -0.802f, 0.959f, -0.276f, -0.067f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.341f, 0.294f, -0.722f, 0.525f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.69f, -0.533f, -0.489f, 0.7f, 0.32f, 0.639f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.441f, 0.095f, -0.382f, 0.807f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.936f, -0.35f, -0.041f, -0.041f, -0.225f, 0.974f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.772f, -0.127f, -0.127f, 0.61f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.471f, -0.378f, 0.797f, -0.81f, 0.173f, 0.561f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.617f, -0.481f, 0.181f, 0.596f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.921f, 0.378f, -0.097f, 0.173f, 0.173f, -0.97f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.181f, 0.761f, -0.617f, -0.083f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.352f, 0.35f, -0.868f, 0.868f, -0.225f, -0.443f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.524f, -0.581f, 0.581f, -0.223f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.548f, -0.371f, -0.75f, 0.746f, -0.189f, 0.639f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.625f, 0.15f, -0.451f, 0.619f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.924f, -0.359f, 0.132f, -0.058f, 0.21f, 0.976f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.621f, -0.168f, -0.099f, 0.759f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.504f, 0.359f, 0.786f, -0.777f, 0.21f, -0.594f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.168f, 0.621f, -0.606f, -0.469f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.497f, 0.042f, -0.867f, 0.781f, -0.414f, -0.467f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.431f, -0.477f, 0.722f, -0.256f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.871f, -0.287f, 0.398f, -0.313f, -0.302f, -0.901f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.254f, -0.591f, 0.766f, 0.008f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.734f, -0.409f, -0.543f, 0.564f, 0.078f, -0.822f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.061f, -0.64f, 0.676f, -0.36f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.89f, 0.409f, 0.201f, -0.253f, 0.078f, 0.964f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.64f, 0.061f, 0.226f, 0.732f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.268f, 0.287f, 0.92f, -0.886f, -0.302f, 0.352f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.591f, -0.254f, 0.549f, 0.534f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.464f, -0.392f, 0.795f, -0.824f, -0.139f, -0.549f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.483f, 0.629f, -0.58f, -0.186f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.944f, -0.329f, -0.033f, -0.055f, 0.255f, -0.965f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.123f, 0.784f, -0.598f, 0.114f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.182f, 0.329f, -0.927f, 0.928f, 0.255f, 0.273f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.545f, 0.577f, -0.276f, 0.543f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.879f, 0.392f, -0.271f, 0.348f, -0.139f, 0.927f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.754f, 0.245f, 0.018f, 0.609f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.517f, -0.388f, -0.763f, -0.781f, -0.151f, 0.606f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.463f, 0.631f, 0.601f, 0.164f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.337f, 0.098f, 0.013f, 0.245f, 0.969f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.104f, 0.776f, 0.606f, -0.144f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.301f, 0.336f, 0.892f, 0.887f, 0.245f, -0.391f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.566f, -0.541f, -0.24f, 0.575f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.713f, 0.103f, -0.694f, -0.608f, -0.403f, -0.684f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.765f, 0.165f, 0.341f, 0.521f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, -0.395f, 0.072f, 0.134f, -0.131f, 0.982f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.103f, 0.635f, 0.745f, -0.178f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.381f, -0.324f, 0.866f, 0.843f, 0.261f, 0.47f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.214f, -0.606f, -0.569f, 0.513f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, 0.324f, 0.277f, 0.196f, 0.261f, -0.945f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.606f, -0.214f, 0.042f, 0.765f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, 0.395f, -0.646f, -0.656f, -0.131f, -0.744f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.635f, 0.103f, 0.403f, 0.651f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, -0.395f, 0.646f, 0.656f, -0.131f, -0.744f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.635f, -0.103f, -0.403f, 0.651f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, -0.324f, -0.277f, -0.196f, 0.261f, -0.945f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.606f, 0.214f, -0.042f, 0.765f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.382f, 0.324f, -0.866f, -0.843f, 0.261f, 0.47f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.214f, 0.606f, 0.569f, 0.513f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, 0.395f, -0.072f, -0.134f, -0.131f, 0.982f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.103f, 0.635f, 0.745f, 0.178f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.99f, -0.123f, -0.074f, -0.117f, -0.398f, -0.91f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.836f, 0.072f, -0.003f, 0.544f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.518f, -0.31f, -0.797f, -0.851f, 0.277f, 0.446f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.391f, 0.742f, 0.456f, 0.296f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.788f, 0.31f, 0.532f, 0.61f, 0.277f, 0.742f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.293f, 0.786f, 0.525f, -0.143f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.883f, 0.123f, 0.453f, 0.462f, -0.398f, -0.793f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.82f, -0.178f, -0.163f, 0.519f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.376f, 0.244f, -0.894f, -0.614f, 0.788f, -0.043f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.188f, 0.492f, 0.265f, 0.808f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.714f, 0.615f, 0.333f, -0.086f, -0.55f, 0.831f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, 0.424f, 0.823f, 0.213f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.006f, -0.615f, 0.788f, 0.719f, -0.55f, -0.424f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.524f, 0.05f, 0.707f, -0.472f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.657f, -0.244f, -0.714f, -0.294f, 0.788f, -0.540f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.325f, 0.414f, 0.015f, 0.85f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.657f, 0.694f, -0.294f, 0.073f, 0.446f, 0.892f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.245f, 0.782f, 0.466f, 0.334f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.294f, 0.75f, 0.592f, 0.592f, -0.343f, 0.729f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.59f, 0.569f, 0.569f, 0.07f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.64f, -0.75f, 0.165f, -0.165f, -0.343f, -0.925f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.763f, -0.3f, 0.3f, -0.488f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, -0.164f, -0.938f, -0.586f, 0.809f, 0.05f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.239f, 0.784f, 0.196f, 0.538f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.269f, 0.736f, 0.622f, 0.604f, 0.374f, -0.704f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.556f, -0.602f, 0.058f, 0.57f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.654f, 0.712f, -0.256f, 0.1f, -0.417f, -0.904f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.777f, 0.261f, -0.324f, -0.473f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.233f, -0.712f, -0.662f, -0.618f, -0.417f, 0.666f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.618f, -0.538f, -0.571f, 0.041f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.465f, -0.082f, 0.881f, 0.469f, 0.821f, 0.325f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.119f, -0.811f, -0.274f, 0.503f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.624f, 0.694f, -0.358f, -0.764f, 0.446f, -0.466f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.303f, 0.057f, 0.43f, 0.848f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, 0.75f, -0.586f, -0.938f, -0.343f, 0.05f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.239f, 0.196f, 0.784f, 0.538f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.51f, -0.75f, 0.421f, 0.844f, -0.343f, 0.411f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.079f, 0.299f, 0.816f, -0.489f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.938f, -0.164f, 0.305f, 0.305f, 0.809f, -0.503f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.283f, -0.124f, -0.124f, 0.943f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>::Identity();
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(quaternion.IsIdentity());
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Trace")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Matrix3x3<float>(0.83f, 0.482f, 0.281f, -0.436f, 0.245f, 0.866f, 0.348f, -0.841f, 0.413f));
	};
	BENCHMARK("0 > 1 && 0 > 2")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Matrix3x3<float>(0.978f, 0.206f, 0.007f, 0.099f, -0.499f, 0.861f, 0.181f, -0.841f, -0.509f));
	};
	BENCHMARK("1 > 2")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Matrix3x3<float>(-0.261f, 0.482f, -0.837f, 0.957f, 0.245f, -0.157f, 0.129f, -0.841f, -0.525f));
	};
	BENCHMARK("2 > 1")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Matrix3x3<float>(-0.105f, 0.403f, 0.909f, -0.932f, -0.36f, 0.052f, 0.348f, -0.841f, 0.413f));
	};
#endif
}

TEST_CASE("Rotation quaternion from Euler angles", "[Math][Transformations]")
{
	auto euler = PonyEngine::Math::Vector3<float>::Zero();
	auto quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(quaternion.IsAlmostIdentity());
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.549f, 0.027f, 0.297f, 0.781f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.495f, -0.239f, 0.635f, 0.543f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.071f, 0.545f, -0.802f, 0.234f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.2f, 0.512f, -0.591f, 0.59f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.611f, 0.614f, -0.26f, 0.427f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.83f, 0.246f, -0.024f, 0.5f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.758f, 0.418f, -0.339f, -0.368f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.465f, 0.73f, -0.474f, -0.161f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.29f, -0.816f, 0.498f, -0.051f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.843f, -0.196f, 0.226f, -0.446f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.866f, -0.011f, -0.113f, 0.487f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.458f, -0.735f, 0.349f, 0.358f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.362f, -0.459f, 0.427f, 0.69f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.191f, -0.553f, 0.811f, 0.014f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.449f, 0.375f, -0.702f, 0.406f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.558f, -0.175f, -0.038f, 0.81f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.806f, -0.187f, -0.085f, 0.555f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.278f, -0.779f, 0.421f, 0.371f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.084f, 0.823f, -0.498f, -0.26f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.648f, 0.515f, -0.487f, 0.279f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.364f, 0.366f, -0.724f, 0.457f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.505f, -0.109f, -0.006f, 0.856f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.464f, 0.226f, -0.199f, -0.833f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.06f, 0.513f, -0.808f, -0.283f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 1.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.161f, -0.491f, 0.736f, -0.438f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.377f, -0.353f, 0.436f, -0.737f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.514f, -0.045f, 0.259f, 0.816f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -1.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.43f, -0.286f, 0.619f, 0.592f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 0.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.771f, -0.301f, 0.383f, 0.41f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.163f, -0.811f, 0.552f, -0.101f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.496f, 0.662f, -0.293f, 0.479f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -0.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.825f, -0.06f, 0.245f, 0.505f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.5f, 0.659f, 0.541f, 0.149f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.123f, 0.818f, 0.547f, -0.128f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.462f, -0.686f, -0.316f, 0.464f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.735f, -0.381f, -0.055f, 0.559f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 0.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.068f, 0.512f, 0.853f, -0.074f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.394f, 0.334f, 0.399f, -0.758f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.516f, 0.02f, 0.218f, 0.828f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -0.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.262f, 0.445f, 0.815f, 0.264f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.305f, -0.416f, -0.784f, 0.344f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.515f, 0.032f, -0.134f, 0.846f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.425f, -0.293f, -0.321f, -0.794f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.017f, -0.516f, -0.841f, -0.159f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 0.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.822f, 0.097f, -0.145f, 0.542f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 2.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.362f, 0.744f, 0.378f, 0.415f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -2.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.007f, -0.827f, -0.523f, -0.203f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -0.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.7f, -0.441f, -0.454f, 0.331f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.163f, 0.542f, 0.321f, 0.76f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.544f, 0.156f, 0.813f, 0.141f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.56f, 0.075f, -0.801f, 0.196f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.24f, 0.512f, -0.268f, 0.78f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.363f, 0.813f, 0.235f, 0.39f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.88f, 0.134f, 0.455f, 0.013f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.886f, 0.089f, -0.444f, 0.101f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.404f, 0.794f, -0.155f, 0.428f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.591f, -0.666f, 0.258f, 0.375f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.838f, -0.301f, 0.406f, 0.206f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.821f, -0.344f, -0.438f, 0.123f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.556f, -0.696f, -0.326f, 0.318f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.097f, -0.054f, 0.557f, 0.823f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.111f, -0.001f, 0.883f, 0.455f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.066f, -0.09f, -0.888f, 0.446f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.015f, -0.11f, -0.565f, 0.817f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f));
	};
#endif
}

TEST_CASE("Rotation quaternion from axis-angle", "[Math][Transformations]")
{
	auto axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	float angle = 0.f;
	auto quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(quaternion.IsIdentity());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance<float>{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -1.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -1.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, 0.577f, 0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, 0.577f, 0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, 0.577f, -0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, 0.577f, -0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, -0.577f, 0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, -0.577f, 0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, -0.577f, -0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, -0.577f, -0.577f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.479f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.479f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.479f, 0.f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.479f, 0.f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.479f, 0.f, 0.f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.479f, 0.f, 0.f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.284f, 0.309f, 0.232f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = 0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.242f, 0.162f, 0.323f, 0.9f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = 1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.312f, 0.156f, -0.39f, 0.853f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = 0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.243f, 0.243f, -0.182f, 0.921f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.284f, -0.309f, 0.232f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = 0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.242f, -0.162f, 0.323f, 0.9f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = 1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.312f, -0.156f, -0.39f, 0.853f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = 0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.243f, -0.243f, -0.182f, 0.921f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = 2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.674f, 0.449f, 0.562f, 0.17f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = 3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.682f, 0.455f,  0.568f, 0.071f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = 2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.657f, 0.438f, -0.602f, 0.121f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = 2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, 0.479f, -0.658f, 0.219f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = 2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.674f, -0.449f, 0.562f, 0.17f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = 3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.682f, -0.455f, 0.568f, 0.071f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = 2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.657f, -0.438f, -0.602f, 0.121f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = 2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, -0.479f, -0.658f, 0.219f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = -2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.674f, -0.449f, -0.562f, 0.17f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = -3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.682f, -0.455f, -0.568f, 0.071f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = -2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.657f, -0.438f, 0.602f, 0.121f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = -2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.538f, -0.479f, 0.658f, 0.219f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = -2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.674f, 0.449f, -0.562f, 0.17f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = -3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.682f, 0.455f, -0.568f, 0.071f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = -2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.657f, 0.438f, 0.602f, 0.121f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = -2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.538f, 0.479f, 0.658f, 0.219f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = -1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.284f, -0.309f, -0.232f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = -0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.242f, -0.162f, -0.323f, 0.9f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = -1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, -0.156f, 0.39f, 0.853f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = -0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.243f, -0.243f, 0.182f, 0.921f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = -1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.284f, 0.309f, -0.232f, 0.878f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = -0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.242f, 0.162f, -0.323f, 0.9f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = -1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, 0.156f, 0.39f, 0.853f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = -0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.243f, 0.243f, 0.182f, 0.921f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), 2.9f);
	};
#endif
}

TEST_CASE("Rotation quaternion from from-to", "[Math][Transformations]")
{
	auto from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	auto to = from;
	auto quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(quaternion.IsIdentity());
	
	from = PonyEngine::Math::Vector3<float>(-3.f, 4.f, 2.3f).Normalized();
	to = from;
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(quaternion.IsIdentity());
	
	from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	to = -from;
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 0.f, 1.f).Normalized();
	to = -from;
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.707f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f).Normalized();
	to = -from;
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = -from;
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.981f, -0.196f, 0.f, 0.f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(6.f, 5.f, 3.f).Normalized();
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.122f, 0.037f, -0.305f, 0.944f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(-6.f, -5.f, 3.f).Normalized();
	quaternion = PonyEngine::Math::FromToRotationQuaternion(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.545f, -0.245f, 0.682f, 0.422f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::FromToRotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::FromToRotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::FromToRotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
	};
#endif
}

TEST_CASE("Rotation quaternion from look-in", "[Math][Transformations]")
{
	const auto forward = PonyEngine::Math::Vector3<float>(-3.f, 2.4f, 1.7f).Normalized();
	const auto up = PonyEngine::Math::Vector3<float>(1.f, 1.2f, 0.7f).Normalized();
	auto quaternion = PonyEngine::Math::LookInRotationQuaternion(forward, up);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.076f, -0.54f, -0.427f, 0.721f).Normalized(), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	quaternion = PonyEngine::Math::LookInRotationQuaternion(forward, forward);
	auto expectedQuaternion = PonyEngine::Math::FromToRotationQuaternion(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedQuaternion, quaternion));

	quaternion = PonyEngine::Math::LookInRotationQuaternion(forward, -forward);
	expectedQuaternion = PonyEngine::Math::FromToRotationQuaternion(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedQuaternion, quaternion));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::LookInRotationQuaternion(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
	};
	BENCHMARK("Collinear")
	{
		return PonyEngine::Math::LookInRotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f));
	};
	BENCHMARK("Collinear-forward")
	{
		return PonyEngine::Math::LookInRotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
	};
#endif
}

TEST_CASE("Rotation matrix from angle", "[Math][Transformations]")
{
	float angle = 0.f;
	auto matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(1.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(0.f, 1.f, -1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(-1.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(0.f, -1.f, 1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = 1.065f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(0.485f, 0.875f, -0.875f, 0.485f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = 2.147f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = -2.478f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	angle = -0.698f;
	matrix = PonyEngine::Math::RotationMatrix(angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationMatrix(2.147f);
	};
#endif
}

TEST_CASE("Rotation matrix from quaternion", "[Math][Transformations]")
{
	auto quaternion = PonyEngine::Math::Quaternion<float>(0.541f, 0.021f, 0.291f, 0.789f).Normalized();
	auto matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.83f, 0.482f, 0.282f, -0.436f, 0.245f, 0.866f, 0.348f, -0.841f, 0.414f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.459f, -0.288f, 0.685f, 0.487f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.1043f, 0.4028f, 0.9093f, -0.9316f, -0.3598f, 0.0525f, 0.3483f, -0.8416f, 0.4128f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.064f, -0.538f, 0.809f, -0.227f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.889f, -0.436f, -0.141f, 0.299f, -0.318f, -0.9f, 0.348f, -0.842f, 0.413f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4f, 0.365f, -0.286f, 0.791f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.5703f, -0.1603f, -0.8057f, 0.7439f, 0.5167f, 0.4237f, 0.3484f, -0.841f, 0.414f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.505f, 0.713f, -0.35f, 0.339f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.2607f, 0.4824f, -0.8362f, 0.9567f, 0.2456f, -0.1566f, 0.1298f, -0.8408f, -0.5256f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.864f, 0.088f, 0.054f, 0.492f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9787f, 0.2054f, 0.0067f, 0.099f, -0.5f, 0.8604f, 0.18f, -0.8413f, -0.5097f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.832f, -0.248f, 0.238f, 0.434f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.7634f, -0.2064f, 0.6121f, -0.62f, -0.5f, 0.6049f, 0.181f, -0.8413f, -0.5094f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.216f, 0.841f, -0.495f, -0.019f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9059f, -0.3447f, 0.246f, -0.3824f, 0.4162f, -0.825f, 0.182f, -0.8414f, -0.5089f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.144f, 0.812f, -0.545f, -0.152f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9123f, 0.3995f, 0.0899f, 0.0682f, 0.3646f, -0.9287f, -0.4037f, -0.8411f, -0.3599f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.538f, 0.625f, -0.546f, 0.147f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3778f, 0.5121f, -0.7714f, 0.8332f, -0.1754f, -0.5244f, -0.4038f, -0.8408f, -0.3604f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.776f, -0.28f, -0.057f, 0.563f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8368f, -0.4983f, 0.2266f, -0.3701f, -0.2099f, 0.9045f, -0.4034f, -0.8412f, -0.3601f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.574f, -0.554f, 0.156f, 0.583f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.3379f, -0.4538f, 0.8245f, -0.8174f, 0.2928f, 0.4961f, -0.4666f, -0.8416f, -0.272f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.383f, -0.237f, 0.283f, 0.847f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.7276f, 0.2978f, 0.618f, -0.6607f, 0.5466f, 0.5145f, -0.1846f, -0.7827f, 0.5944f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.203f, -0.402f, 0.684f, 0.574f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.259f, 0.622f, 0.739f, -0.948f, -0.018f, -0.317f, -0.184f, -0.783f, 0.594f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.341f, 0.294f, -0.722f, 0.525f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.2159f, -0.5578f, -0.8014f, 0.959f, -0.2756f, -0.0665f, -0.1839f, -0.7829f, 0.5944f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.441f, 0.095f, -0.382f, 0.807f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.6903f, -0.5324f, -0.49f, 0.6999f, 0.3197f, 0.6388f, -0.1835f, -0.7839f, 0.5933f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.772f, -0.127f, -0.127f, 0.61f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9355f, -0.3509f, -0.0411f, -0.0411f, -0.2238f, 0.9738f, -0.3509f, -0.9093f, -0.2238f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.617f, -0.481f, 0.181f, 0.596f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.4718f, -0.3778f, 0.7967f, -0.8093f, 0.1731f, 0.5613f, -0.35f, -0.9096f, -0.2241f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.181f, 0.761f, -0.617f, -0.083f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9207f, 0.3781f, -0.0971f, 0.1732f, 0.1727f, -0.9696f, -0.3499f, -0.9095f, -0.2244f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.524f, -0.581f, 0.581f, -0.223f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.351f, 0.35f, -0.8685f, 0.8685f, -0.225f, -0.4417f, -0.35f, -0.9093f, -0.225f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.625f, 0.15f, -0.451f, 0.619f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.548f, -0.371f, -0.75f, 0.746f, -0.189f, 0.639f, -0.378f, -0.909f, 0.173f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.621f, -0.168f, -0.099f, 0.759f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9239f, -0.359f, 0.1321f, -0.0584f, 0.2089f, 0.9762f, -0.3781f, -0.9096f, 0.1721f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.168f, 0.621f, -0.606f, -0.469f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.5042f, 0.3594f, 0.7853f, -0.7763f, 0.21f, -0.5944f, -0.3785f, -0.9093f, 0.1731f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.431f, -0.477f, 0.722f, -0.256f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.4976f, 0.0415f, -0.8666f, 0.7808f, -0.4141f, -0.4681f, -0.3781f, -0.9095f, 0.1734f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.254f, -0.591f, 0.766f, 0.008f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.8709f, -0.2878f, 0.3983f, -0.3123f, -0.3017f, -0.9008f, 0.3794f, -0.9089f, 0.1729f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.061f, -0.64f, 0.676f, -0.36f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.7333f, -0.4087f, -0.5433f, 0.5649f, 0.0785f, -0.8214f, 0.3784f, -0.9093f, 0.1733f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.64f, 0.061f, 0.226f, 0.732f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8904f, 0.4089f, 0.1999f, -0.2528f, 0.0789f, 0.9643f, 0.3785f, -0.9092f, 0.1735f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.591f, -0.254f, 0.549f, 0.534f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.2682f, 0.2861f, 0.9202f, -0.8866f, -0.3014f, 0.3523f, 0.3776f, -0.9101f, 0.1724f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.483f, 0.629f, -0.58f, -0.186f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.4641f, -0.3919f, 0.7943f, -0.8234f, -0.1394f, -0.55f, 0.3263f, -0.9093f, -0.2579f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.123f, 0.784f, -0.598f, 0.114f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9438f, -0.3291f, -0.0316f, -0.0565f, 0.2548f, -0.9653f, 0.3257f, -0.9093f, -0.2591f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.545f, 0.577f, -0.276f, 0.543f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.1826f, 0.3289f, -0.9266f, 0.9278f, 0.2543f, 0.2731f, 0.3255f, -0.9095f, -0.2587f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.754f, 0.245f, 0.018f, 0.609f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8793f, 0.3915f, -0.2713f, 0.3476f, -0.138f, 0.9274f, 0.3256f, -0.9098f, -0.2574f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.463f, 0.631f, 0.601f, 0.164f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.5178f, -0.3869f, -0.763f, -0.7809f, -0.1504f, 0.6062f, -0.3493f, 0.9098f, -0.2243f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.104f, 0.776f, 0.606f, -0.144f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.3356f, 0.0973f, 0.0131f, 0.2446f, 0.9695f, -0.3492f, 0.9097f, -0.2248f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.566f, -0.541f, -0.24f, 0.575f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.3003f, 0.336f, 0.8927f, 0.8873f, 0.245f, -0.3907f, -0.35f, 0.9094f, -0.2245f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.765f, 0.165f, 0.341f, 0.521f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.713f, 0.1029f, -0.6935f, -0.6077f, -0.4028f, -0.6844f, -0.3497f, 0.9095f, -0.2247f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.103f, 0.635f, 0.745f, -0.178f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9155f, -0.3958f, 0.0726f, 0.1343f, -0.1307f, 0.9823f, -0.3793f, 0.909f, 0.1728f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.214f, -0.606f, -0.569f, 0.513f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.382f, -0.3244f, 0.8653f, 0.8432f, 0.2609f, 0.4701f, -0.3782f, 0.9092f, 0.1739f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.606f, -0.214f, 0.042f, 0.765f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9049f, 0.3236f, 0.2765f, 0.1951f, 0.262f, -0.9451f, -0.3783f, 0.9091f, 0.174f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.635f, 0.103f, 0.403f, 0.651f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.654f, 0.3939f, -0.6459f, -0.6555f, -0.1312f, -0.7438f, -0.3777f, 0.9097f, 0.1724f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.635f, -0.103f, -0.403f, 0.651f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.654f, -0.3939f, 0.6459f, 0.6555f, -0.1312f, -0.7437f, 0.3777f, 0.9097f, 0.1724f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.606f, 0.214f, -0.042f, 0.765f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9049f, -0.3236f, -0.2765f, -0.1951f, 0.262f, -0.9451f, 0.3783f, 0.9092f, 0.174f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.103f, 0.635f, 0.745f, 0.178f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9155f, 0.3958f, -0.0726f, -0.1343f, -0.1307f, 0.9823f, 0.3793f, 0.909f, 0.1728f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.836f, 0.072f, -0.003f, 0.544f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9897f, -0.1236f, -0.0733f, -0.1171f, -0.3978f, -0.91f, 0.0833f, 0.9091f, -0.4081f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.391f, 0.742f, 0.456f, 0.296f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.5185f, -0.3106f, -0.7967f, -0.851f, 0.2776f, 0.4457f, 0.0828f, 0.9091f, -0.4083f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.293f, 0.786f, 0.525f, -0.143f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.7873f, 0.3105f, 0.5326f, 0.6109f, 0.2769f, 0.7417f, 0.0829f, 0.9094f, -0.4077f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.82f, -0.178f, -0.163f, 0.519f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8835f, 0.1227f, 0.4521f, 0.4611f, -0.3979f, -0.7931f, 0.0826f, 0.9092f, -0.4081f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.188f, 0.492f, 0.265f, 0.808f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.3757f, 0.2431f, -0.8943f, -0.6129f, 0.789f, -0.043f, 0.6951f, 0.5643f, 0.4455f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.312f, 0.424f, 0.823f, 0.213f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.7145f, 0.6152f, 0.333f, -0.086f, -0.5496f, 0.831f, 0.6943f, 0.5651f, 0.4457f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.524f, 0.05f, 0.707f, -0.472f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.005f, -0.6152f, 0.7884f, 0.72f, -0.5493f, -0.4241f, 0.6939f, 0.5656f, 0.4457f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.325f, 0.414f, 0.015f, 0.85f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.657f, -0.244f, -0.714f, -0.294f, 0.788f, -0.54f, 0.694f, 0.565f, 0.446f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.245f, 0.782f, 0.466f, 0.334f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.657f, 0.694f, -0.294f, 0.072f, 0.446f, 0.892f, 0.75f, 0.565f, -0.343f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.59f, 0.569f, 0.569f, 0.07f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.2943f, 0.7507f, 0.5915f, 0.5915f, -0.343f, 0.7298f, 0.7507f, 0.5647f, -0.343f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.763f, -0.3f, 0.3f, -0.488f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.6401f, -0.7504f, 0.1649f, -0.1649f, -0.3439f, -0.9244f, 0.7504f, 0.5645f, -0.3439f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.239f, 0.784f, 0.196f, 0.538f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.306f, -0.164f, -0.938f, -0.586f, 0.809f, 0.05f, 0.7504f, 0.5645f, -0.3439f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.556f, -0.602f, 0.058f, 0.57f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.2683f, 0.7357f, 0.6219f, 0.6034f, 0.3749f, -0.7038f, -0.7509f, 0.5641f, -0.3433f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.777f, 0.261f, -0.324f, -0.473f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.654f, 0.7117f, -0.2564f, 0.099f, -0.4166f, -0.9037f, -0.75f, 0.5656f, -0.343f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.618f, -0.538f, -0.571f, 0.041f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.2321f, -0.7124f, -0.6622f, -0.6187f, -0.4172f, 0.6657f, -0.7506f, 0.5642f, -0.344f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.119f, -0.811f, -0.274f, 0.503f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.4656f, -0.0826f, 0.8811f, 0.4687f, 0.8215f, 0.3247f, -0.7507f, 0.5642f, -0.3438f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.303f, 0.057f, 0.43f, 0.848f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.6233f, 0.6953f, -0.3576f, -0.7645f, 0.4461f, -0.4653f, -0.1641f, 0.5634f, 0.8097f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.239f, 0.196f, 0.784f, 0.538f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3066f, 0.7502f, -0.5859f, -0.9376f, -0.344f, 0.0502f, -0.1639f, 0.5647f, 0.8089f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.079f, 0.299f, 0.816f, -0.489f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.5096f, -0.7503f, 0.4211f, 0.8448f, -0.3434f, 0.4105f, -0.1634f, 0.5649f, 0.8088f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.283f, -0.124f, -0.124f, 0.943f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9385f, -0.1637f, 0.304f, 0.304f, 0.8091f, -0.5029f, -0.1637f, 0.5644f, 0.8091f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>::Identity();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(matrix.IsIdentity());
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	quaternion = PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized();
	matrix = PonyEngine::Math::RotationMatrix(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	constexpr auto quaternionC = PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f);
	constexpr auto matrixC = PonyEngine::Math::RotationMatrix(quaternionC);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationMatrix(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f));
	};
#endif
}

TEST_CASE("Rotation matrix from Euler angles", "[Math][Transformations]")
{
	auto euler = PonyEngine::Math::Vector3<float>::Zero();
	auto matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(matrix.IsAlmostIdentity());
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8224f, 0.4932f, 0.2835f, -0.4336f, 0.2207f, 0.8737f, 0.3683f, -0.8415f, 0.3953f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.08f, 0.452f, 0.888f, -0.926f, -0.296f, 0.233f, 0.3683f, -0.8415f, 0.3953f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.881f, -0.452f, -0.142f, 0.298f, -0.296f, -0.907f, 0.3683f, -0.8415f, 0.3953f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.225f, -0.493f, -0.84f, 0.902f, 0.221f, -0.371f, 0.3683f, -0.8415f, 0.3953f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.111f, 0.527f, -0.842f, 0.972f, 0.118f, 0.202f, 0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.878f, 0.384f, -0.285f, 0.432f, -0.38f, 0.818f, 0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.421f, -0.384f, 0.822f, -0.883f, -0.38f, 0.275f, 0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.516f, -0.527f, 0.675f, -0.832f, 0.118f, -0.543f, 0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.826f, 0.423f, -0.372f, 0.524f, 0.336f, -0.782f, -0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.821f, 0.129f, -0.557f, 0.533f, -0.525f, 0.664f, -0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.9743f, -0.1293f, -0.1845f, 0.091f, -0.5246f, 0.8465f, -0.2062f, -0.8415f, -0.4994f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.323f, -0.423f, 0.846f, -0.924f, 0.336f, -0.185f, -0.206f, -0.8415f, -0.499f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.214f, 0.256f, 0.943f, -0.921f, 0.374f, 0.107f, -0.325f, -0.891f, 0.316f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9266f, 0.2338f, -0.2946f, 0.1887f, -0.3887f, -0.9018f, -0.3254f, -0.8912f, 0.316f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.2674f, -0.2338f, -0.9348f, 0.907f, -0.3887f, -0.1623f, -0.3254f, -0.8912f, 0.316f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.936f, -0.256f, 0.241f, -0.134f, 0.374f, 0.918f, -0.3254f, -0.8912f, 0.316f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.916f, -0.395f, 0.071f, -0.207f, -0.314f, 0.927f, -0.344f, -0.863f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.57f, -0.121f, 0.813f, -0.746f, 0.49f, -0.45f, -0.344f, -0.863f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.851f, 0.121f, 0.511f, -0.396f, 0.49f, -0.776f, -0.344f, -0.863f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.006f, 0.395f, -0.918f, 0.939f, -0.314f, -0.141f, -0.344f, -0.863f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3165f, -0.3955f, -0.8622f, 0.9288f, -0.3138f, -0.197f, -0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.976f, -0.121f, 0.18f, -0.099f, 0.49f, 0.866f, -0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -2.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.121f, 0.561f, -0.541f, 0.49f, 0.683f, -0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -0.9f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.833f, 0.395f, 0.388f, -0.519f, -0.314f, -0.795f, -0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 1.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.565f, -0.486f, -0.667f, 0.802f, -0.135f, -0.581f, 0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 2.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.37f, -0.376f, -0.849f, 0.909f, 0.336f, 0.247f, 0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -2.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.862f, 0.376f, 0.341f, -0.47f, 0.336f, 0.816f, 0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -1.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.07f, 0.486f, 0.871f, -0.979f, -0.135f, 0.154f, 0.1927f, -0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 0.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.525f, -0.149f, 0.838f, -0.778f, -0.482f, 0.402f, 0.344f, -0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 2.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.926f, -0.376f, 0.017f, -0.154f, 0.336f, -0.929f, 0.344f, -0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -2.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.049f, 0.376f, -0.925f, 0.938f, 0.336f, 0.087f, 0.344f, -0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -0.3f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.873f, 0.149f, 0.465f, -0.346f, -0.482f, 0.805f, 0.344f, -0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 1.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.455f, -0.498f, -0.738f, -0.821f, -0.086f, 0.564f, -0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.341f, 0.076f, -0.06f, 0.372f, 0.926f, -0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.142f, 0.341f, 0.929f, 0.928f, 0.372f, 0.005f, -0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -1.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.704f, 0.498f, 0.507f, 0.621f, -0.086f, -0.779f, -0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 0.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.9797f, -0.1966f, -0.0408f, 0.0565f, -0.465f, 0.8835f, -0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.459f, -0.341f, 0.82f, 0.867f, 0.372f, -0.331f, -0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.904f, 0.341f, -0.257f, -0.381f, 0.372f, -0.846f, -0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -0.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.723f, 0.197f, -0.662f, -0.663f, -0.465f, 0.586f, -0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 0.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.577f, -0.285f, 0.766f, 0.794f, -0.417f, 0.443f, 0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 2.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.962f, -0.26f, 0.084f, 0.194f, 0.433f, -0.88f, 0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -2.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.622f, 0.26f, -0.738f, -0.759f, 0.433f, -0.487f, 0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -0.6f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.949f, 0.285f, -0.136f, -0.25f, -0.417f, 0.874f, 0.1927f, 0.8632f, 0.4666f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 0.68f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.939f, -0.317f, 0.133f, -0.003f, -0.393f, -0.92f, 0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 2.68f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.393f, -0.225f, -0.892f, -0.853f, 0.452f, 0.262f, 0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -2.68f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.917f, 0.225f, -0.329f, -0.201f, 0.452f, 0.869f, 0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -0.68f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.199f, 0.317f, 0.927f, 0.918f, -0.393f, -0.063f, 0.344f, 0.8632f, -0.369f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.208f, 0.6635f, -0.7187f, -0.311f, 0.7415f, 0.595f, 0.9274f, 0.0998f, 0.3605f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.369f, 0.398f, 0.84f, -0.06f, -0.912f, 0.406f, 0.927f, 0.1f, 0.361f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.295f, -0.398f, 0.869f, 0.23f, -0.912f, -0.34f, 0.927f, 0.1f, 0.361f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.3321f, -0.6635f, -0.6704f, 0.1723f, 0.7415f, -0.6485f, 0.9274f, 0.0998f, 0.3605f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.433f, 0.773f, -0.463f, 0.407f, 0.626f, 0.665f, 0.804f, 0.1f, -0.586f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.55f, 0.248f, 0.798f, 0.225f, -0.964f, 0.144f, 0.804f, 0.1f, -0.586f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.59f, -0.248f, 0.768f, -0.068f, -0.964f, -0.258f, 0.804f, 0.1f, -0.586f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.308f, -0.773f, -0.555f, -0.508f, 0.626f, -0.591f, 0.804f, 0.1f, -0.586f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0205f, 0.9805f, 0.1953f, 0.5937f, 0.1691f, -0.7867f, -0.8044f, 0.0998f, -0.5856f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.488f, 0.672f, -0.556f, 0.338f, -0.734f, -0.589f, -0.8044f, 0.0998f, -0.5856f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.379f, -0.672f, -0.636f, -0.457f, -0.734f, 0.503f, -0.8044f, 0.0998f, -0.5856f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.18f, -0.981f, 0.08f, -0.566f, 0.169f, 0.807f, -0.8044f, 0.0998f, -0.5856f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.374f, 0.927f, -0.019f, -0.906f, 0.361f, -0.221f, -0.198f, 0.0998f, 0.975f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.561f, 0.804f, -0.196f, -0.804f, -0.586f, -0.103f, -0.198f, 0.0998f, 0.975f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.593f, -0.804f, -0.038f, 0.781f, -0.586f, 0.218f, -0.198f, 0.0998f, 0.975f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f);
	matrix = PonyEngine::Math::RotationMatrix(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.337f, -0.927f, 0.163f, 0.921f, 0.361f, 0.15f, -0.198f, 0.0998f, 0.975f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f));
	};
#endif
}

TEST_CASE("Rotation matrix from axis-angle", "[Math][Transformations]")
{
	auto axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	float angle = 0.f;
	auto matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(matrix.IsIdentity());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, -0.244f, -0.244f, 0.333f, 0.911f, 0.911f, -0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, -0.911f, -0.911f, 0.333f, -0.244f, 0.244f, 0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, -0.244f, 0.244f, 0.333f, -0.911f, 0.911f, 0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, -0.911f, 0.911f, 0.333f, 0.244f, 0.244f, -0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, 0.911f, -0.911f, 0.333f, 0.244f, -0.244f, -0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, 0.244f, -0.244f, 0.333f, -0.911f, -0.911f, 0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, 0.911f, 0.911f, 0.333f, -0.244f, -0.244f, 0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, 0.244f, 0.244f, 0.333f, 0.911f, -0.911f, -0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, 0.6667f, 0.6667f, 0.6667f, -0.3333f, 0.6667f, 0.6667f, 0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, -0.6667f, -0.6667f, -0.6667f, -0.3333f, 0.6667f, -0.6667f, 0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, -0.6667f, 0.6667f, -0.6667f, -0.3333f, -0.6667f, 0.6667f, -0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, 0.6667f, -0.6667f, 0.6667f, -0.3333f, -0.6667f, -0.6667f, -0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, -0.6667f, 0.6667f, -0.6667f, -0.3333f, -0.6667f, 0.6667f, -0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, 0.6667f, -0.6667f, 0.6667f, -0.3333f, -0.6667f, -0.6667f, -0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, 0.6667f, 0.6667f, 0.6667f, -0.3333f, 0.6667f, 0.6667f, 0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3333f, -0.6667f, -0.6667f, -0.6667f, -0.3333f, 0.6667f, -0.6667f, 0.6667f, -0.3333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, 0.911f, 0.911f, 0.333f, -0.244f, -0.244f, 0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, 0.244f, 0.244f, 0.333f, 0.911f, -0.911f, -0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, 0.911f, -0.911f, 0.333f, 0.244f, -0.244f, -0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, 0.244f, -0.244f, 0.333f, -0.911f, -0.911f, 0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, -0.244f, 0.244f, 0.333f, -0.911f, 0.911f, 0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, -0.911f, 0.911f, 0.333f, 0.244f, 0.244f, -0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, -0.244f, -0.244f, 0.333f, 0.911f, 0.911f, -0.244f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, -0.911f, -0.911f, 0.333f, -0.244f, 0.244f, 0.911f, 0.333f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.841f, 0.f, -0.841f, 0.54f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.54f, -0.841f, 0.f, 0.841f, 0.54f, 0.f, 0.f, 0.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.f, -0.841f, 0.f, 1.f, 0.f, 0.841f, 0.f, 0.54f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.f, 0.841f, 0.f, 1.f, 0.f, -0.841f, 0.f, 0.54f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.54f, 0.841f, 0.f, -0.841f, 0.54f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.54f, -0.841f, 0.f, 0.841f, 0.54f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.701f, 0.583f, -0.411f, -0.232f, 0.732f, 0.641f, 0.674f, -0.354f, 0.648f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = 0.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.739f, 0.504f, -0.447f, -0.66f, 0.674f, -0.332f, 0.134f, 0.541f, 0.83f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = 1.1f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.648f, -0.761f, -0.023f, 0.567f, 0.502f, -0.653f, 0.509f, 0.41f, 0.757f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = 0.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.815f, -0.218f, -0.537f, 0.454f, 0.815f, 0.359f, 0.359f, -0.537f, 0.763f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = 1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.701f, 0.232f, 0.674f, -0.583f, 0.732f, 0.354f, -0.411f, -0.641f, 0.648f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = 0.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.739f, 0.66f, 0.134f, -0.504f, 0.674f, -0.541f, -0.447f, 0.332f, 0.83f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = 1.1f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.648f, -0.567f, 0.509f, 0.761f, 0.502f, -0.41f, -0.023f, 0.653f, 0.757f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = 0.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.815f, -0.454f, 0.359f, 0.218f, 0.815f, 0.537f, -0.537f, -0.359f, 0.763f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = 2.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0342f, 0.7962f, 0.604f, 0.4144f, -0.5386f, 0.7335f, 0.9094f, 0.2754f, -0.3116f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = 3.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.06f, -0.54f, -0.84f, -0.701f, -0.576f, 0.42f, -0.711f, 0.613f, -0.344f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = 2.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.1083f, -0.7202f, 0.6853f, -0.43f, -0.5876f, -0.6855f, 0.8963f, -0.3689f, -0.2461f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = 2.7f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.3243f, 0.2271f, -0.9183f, 0.8036f, -0.4459f, -0.3941f, -0.499f, -0.8658f, -0.0379f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = 2.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0342f, -0.4145f, 0.9094f, -0.7962f, -0.5386f, -0.2754f, 0.604f, -0.7335f, -0.3116f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = 3.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.06f, 0.701f, -0.711f, 0.54f, -0.576f, -0.613f, -0.84f, -0.42f, -0.344f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = 2.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.1083f, 0.43f, 0.8963f, 0.7202f, -0.5875f, 0.3689f, 0.6853f, 0.6853f, -0.2461f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = 2.7f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.324f, -0.804f, -0.499f, -0.227f, -0.446f, 0.866f, -0.918f, 0.394f, -0.038f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = -2.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0342f, 0.4145f, 0.9094f, 0.7962f, -0.5386f, 0.2754f, 0.604f, 0.7335f, -0.3116f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = -3.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.06f, -0.701f, -0.711f, -0.54f, -0.576f, 0.613f, -0.84f, 0.42f, -0.344f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = -2.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.1083f, -0.43f, 0.8963f, -0.7202f, -0.5875f, -0.3689f, 0.6853f, -0.6855f, -0.2461f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = -2.7f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.324f, 0.804f, -0.499f, 0.227f, -0.446f, -0.865f, -0.918f, -0.394f, -0.038f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = -2.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0342f, -0.7962f, 0.604f, -0.4145f, -0.5386f, -0.7335f, 0.909f, -0.2754f, -0.3112f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = -3.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.06f, 0.54f, -0.84f, 0.701f, -0.576f, -0.42f, -0.711f, -0.613f, -0.344f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = -2.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.108f, 0.72f, 0.685f, 0.43f, -0.588f, 0.685f, 0.896f, 0.369f, -0.246f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = -2.7f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.324f, -0.227f, -0.918f, -0.804f, -0.446f, 0.394f, -0.499f, 0.866f, -0.038f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = -1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.701f, -0.232f, 0.674f, 0.583f, 0.732f, -0.354f, -0.411f, 0.641f, 0.648f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = -0.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.739f, -0.66f, 0.134f, 0.504f, 0.674f, 0.541f, -0.447f, -0.332f, 0.83f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = -1.1f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.648f, 0.567f, 0.509f, -0.761f, 0.502f, 0.41f, -0.023f, -0.653f, 0.757f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = -0.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.815f, 0.454f, 0.359f, -0.218f, 0.815f, -0.537f, -0.537f, 0.359f, 0.763f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = -1.f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.701f, -0.583f, -0.411f, 0.232f, 0.732f, -0.641f, 0.674f, 0.354f, 0.648f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = -0.9f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.739f, -0.504f, -0.447f, 0.66f, 0.674f, 0.332f, 0.134f, -0.541f, 0.83f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = -1.1f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.648f, 0.761f, -0.023f, -0.567f, 0.502f, 0.653f, 0.509f, -0.41f, 0.757f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = -0.8f;
	matrix = PonyEngine::Math::RotationMatrix(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.815f, 0.218f, -0.537f, -0.454f, 0.815f, -0.359f, 0.359f, 0.537f, 0.763f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationMatrix(axis, angle);
	};
#endif
}

TEST_CASE("Rotation matrix from from-to", "[Math][Transformations]")
{
	auto from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	auto to = from;
	auto matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(matrix.IsIdentity());

	from = PonyEngine::Math::Vector3<float>(-3.f, 4.f, 2.3f).Normalized();
	to = from;
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(matrix.IsIdentity());

	from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	to = -from;
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 0.f, 1.f).Normalized();
	to = -from;
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, -1.f, 0.f, -1.f, 0.f, 0.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f).Normalized();
	to = -from;
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = -from;
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.923f, -0.384f, 0.f, -0.384f, -0.923f, 0.f, 0.f, 0.f, -1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(6.f, 5.f, 3.f).Normalized();
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.8118f, -0.5661f, -0.1432f, 0.584f, 0.7847f, 0.2078f, -0.0052f, -0.2522f, 0.9676f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(-6.f, -5.f, 3.f).Normalized();
	matrix = PonyEngine::Math::FromToRotationMatrix(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.0495f, 0.3075f, 0.9503f, -0.8426f, -0.5237f, 0.1256f, 0.5362f, -0.7945f, 0.285f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::FromToRotationMatrix(from, to);
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::FromToRotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::FromToRotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
	};
#endif
}

TEST_CASE("Rotation matrix from look-in", "[Math][Transformations]")
{
	const auto forward = PonyEngine::Math::Vector3<float>(-3.f, 2.4f, 1.7f).Normalized();
	const auto up = PonyEngine::Math::Vector3<float>(1.f, 1.2f, 0.7f).Normalized();
	auto matrix = PonyEngine::Math::LookInRotationMatrix(forward, up);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.051f, -0.534f, 0.844f, 0.698f, 0.623f, 0.353f, -0.714f, 0.571f, 0.405f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	matrix = PonyEngine::Math::LookInRotationMatrix(forward, forward);
	auto expectedMatrix = PonyEngine::Math::FromToRotationMatrix(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedMatrix, matrix));

	matrix = PonyEngine::Math::LookInRotationMatrix(forward, -forward);
	expectedMatrix = PonyEngine::Math::FromToRotationMatrix(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedMatrix, matrix));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::LookInRotationMatrix(forward, up);
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::LookInRotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::LookInRotationMatrix(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f));
	};
#endif
}

TEST_CASE("Euler from quaternion", "[Math][Transformations]")
{
	auto quaternion = PonyEngine::Math::Quaternion<float>::Identity();
	auto euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(euler.IsZero());

	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f);
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6408564f, 0.2988362f, -0.2988362f, 0.6408564f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.873f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6408564f, -0.2988362f, 0.2988362f, 0.6408564f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -0.873f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5f, 0.5f, -0.5f, 0.5f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4545195f, 0.5416752f, -0.5416752f, 0.4545195f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 1.745f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4545195f, -0.5416752f, 0.5416752f, 0.4545195f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -1.745f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.1830127f, -0.6830127f, 0.6830127f, 0.1830127f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -2.618f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5f, -0.5f, 0.5f, 0.5f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6123724f, -0.3535534f, 0.3535534f, 0.6123724f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -1.047f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6123724f, 0.3535534f, -0.3535534f, 0.6123724f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 1.047f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f);
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.7071068f, 0.f, 0.f, 0.7071068f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> * 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.549f, 0.027f, 0.297f, 0.781f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.9995f, 0.7491f, 1.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.495f, -0.239f, 0.635f, 0.543f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.7503f, 2.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.071f, 0.545f, -0.802f, 0.234f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.7503f, -2.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2f, 0.512f, -0.591f, 0.59f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.748f, -1.148f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.611f, 0.614f, -0.26f, 0.427f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.83f, 0.246f, -0.024f, 0.5f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.758f, 0.418f, -0.339f, -0.368f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.465f, 0.73f, -0.474f, -0.161f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.29f, -0.816f, 0.498f, -0.051f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.843f, -0.196f, 0.226f, -0.446f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.866f, -0.011f, -0.113f, 0.487f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.458f, -0.735f, 0.349f, 0.358f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.362f, -0.459f, 0.427f, 0.69f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.798f, 0.603f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.191f, -0.553f, 0.811f, 0.014f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.798f, 2.603f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.449f, 0.375f, -0.702f, 0.406f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.802f, -2.601f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.558f, -0.175f, -0.038f, 0.81f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.098f, -0.8f, -0.601f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.806f, -0.187f, -0.085f, 0.555f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.391f, -2.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.278f, -0.779f, 0.421f, 0.371f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.392f, -0.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.084f, 0.823f, -0.498f, -0.26f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.392f, 0.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.648f, 0.515f, -0.487f, 0.279f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.392f, 2.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.364f, 0.366f, -0.724f, 0.457f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.391f, -2.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.505f, -0.109f, -0.006f, 0.856f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.391f, -0.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.464f, 0.226f, -0.199f, -0.833f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.391f, 0.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.06f, 0.513f, -0.808f, -0.283f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.391f, 2.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.161f, -0.491f, 0.736f, -0.438f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.042f, 0.393f, -1.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.377f, -0.353f, 0.436f, -0.737f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.042f, 0.393f, -0.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.514f, -0.045f, 0.259f, 0.816f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.042f, 0.393f, 0.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.43f, -0.286f, 0.619f, 0.592f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 0.393f, 1.843f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.771f, -0.301f, 0.383f, 0.41f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.393f, -2.843f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.163f, -0.811f, 0.552f, -0.101f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.393f, -0.843f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.496f, 0.662f, -0.293f, 0.479f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.393f, 0.843f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.825f, -0.06f, 0.245f, 0.505f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.393f, 2.843f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5f, 0.659f, 0.541f, 0.149f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, -1.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.123f, 0.818f, 0.547f, -0.128f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, -0.743f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.462f, -0.686f, -0.316f, 0.464f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, 0.743f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.735f, -0.381f, -0.055f, 0.559f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, 1.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.068f, 0.512f, 0.853f, -0.074f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.042f, -0.39f, -2.743f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.394f, 0.334f, 0.399f, -0.758f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.042f, -0.39f, -0.744f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.516f, 0.02f, 0.218f, 0.828f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.042f, -0.39f, 0.744f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.262f, 0.445f, 0.815f, 0.264f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.042f, -0.39f, 2.741f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.305f, -0.416f, -0.784f, 0.344f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.04f, 0.389f, -2.54f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.515f, 0.032f, -0.134f, 0.846f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 0.39f, -0.54f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.425f, -0.293f, -0.321f, -0.794f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.04f, 0.389f, 0.542f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.017f, -0.516f, -0.841f, -0.159f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.04f, 0.389f, 2.542f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.822f, 0.097f, -0.145f, 0.542f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.394f, -2.464f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.362f, 0.744f, 0.378f, 0.415f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.394f, -0.464f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.007f, -0.827f, -0.523f, -0.203f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.394f, 0.464f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.7f, -0.441f, -0.454f, 0.331f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.394f, 2.464f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.163f, 0.542f, 0.321f, 0.76f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.201f, 0.731f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.544f, 0.156f, 0.813f, 0.141f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.201f, 2.729f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.56f, 0.075f, -0.801f, 0.196f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.201f, -2.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.24f, 0.512f, -0.268f, 0.78f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.201f, -0.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.363f, 0.813f, 0.235f, 0.39f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.88f, 0.134f, 0.455f, 0.013f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.886f, 0.089f, -0.444f, 0.101f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.404f, 0.794f, -0.155f, 0.428f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.591f, -0.666f, 0.258f, 0.375f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.838f, -0.301f, 0.406f, 0.206f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.821f, -0.344f, -0.438f, 0.123f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.556f, -0.696f, -0.326f, 0.318f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.097f, -0.054f, 0.557f, 0.823f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.111f, -0.001f, 0.883f, 0.455f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.066f, -0.09f, -0.888f, 0.446f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	quaternion = PonyEngine::Math::Quaternion<float>(0.015f, -0.11f, -0.565f, 0.817f).Normalized();
	euler = PonyEngine::Math::Euler(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::Euler(quaternion);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::Euler(PonyEngine::Math::Quaternion<float>(0.707106829f, 0.f, 0.f, 0.707106829f));
	};
#endif
}

TEST_CASE("Euler from rotation matrix", "[Math][Transformations]")
{
	auto matrix = PonyEngine::Math::Matrix3x3<float>::Identity();
	auto euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(euler.IsAlmostZero());
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.629f, 0.f, -0.777f, 0.777f, 0.f, 0.629f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.89f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.883f, 0.f, -0.469f, 0.469f, 0.f, -0.883f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 2.653f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.643f, 0.f, 0.766f, -0.766f, 0.f, -0.643f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -2.269f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, -1.f, 0.f, 0.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.f, 0.574f, -0.574f, 0.f, 0.819f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -0.611f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.629f, 0.f, 0.777f, -0.777f, 0.f, 0.629f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -0.89f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, -1.f, 0.f, 0.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.883f, 0.f, 0.469f, -0.469f, 0.f, -0.883f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, -2.653f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.643f, 0.f, -0.766f, 0.766f, 0.f, -0.643f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 2.269f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.f, -0.574f, 0.574f, 0.f, 0.819f, 0.f, -1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.611f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.629f, 0.f, -0.777f, 0.777f, 0.f, 0.629f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.89f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.883f, 0.f, -0.469f, 0.469f, 0.f, -0.883f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 2.653f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.643f, 0.f, 0.766f, -0.766f, 0.f, -0.643f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -2.269f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, -1.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.f, 0.574f, -0.574f, 0.f, 0.819f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -0.611f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.629f, 0.f, 0.777f, -0.777f, 0.f, 0.629f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -0.89f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, -1.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.883f, 0.f, 0.469f, -0.469f, 0.f, -0.883f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -2.653f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.643f, 0.f, -0.766f, 0.766f, 0.f, -0.643f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 2.269f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.f, -0.574f, 0.574f, 0.f, 0.819f, 0.f, 1.f, 0.f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.611f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.822f, 0.493f, 0.284f, -0.434f, 0.221f, 0.874f, 0.368f, -0.841f, 0.395f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.08f, 0.452f, 0.888f, -0.926f, -0.296f, 0.233f, 0.368f, -0.841f, 0.395f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.881f, -0.452f, -0.142f, 0.298f, -0.296f, -0.907f, 0.368f, -0.841f, 0.395f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.225f, -0.493f, -0.84f, 0.902f, 0.221f, -0.371f, 0.368f, -0.841f, 0.395f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.111f, 0.527f, -0.842f, 0.972f, 0.118f, 0.202f, 0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.878f, 0.384f, -0.285f, 0.432f, -0.38f, 0.818f, 0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.421f, -0.384f, 0.822f, -0.883f, -0.38f, 0.275f, 0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.516f, -0.527f, 0.675f, -0.832f, 0.118f, -0.543f, 0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.826f, 0.423f, -0.372f, 0.524f, 0.336f, -0.782f, -0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.821f, 0.129f, -0.557f, 0.533f, -0.525f, 0.664f, -0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.974f, -0.129f, -0.184f, 0.091f, -0.525f, 0.846f, -0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.323f, -0.423f, 0.846f, -0.924f, 0.336f, -0.185f, -0.206f, -0.841f, -0.499f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.214f, 0.256f, 0.943f, -0.921f, 0.374f, 0.107f, -0.325f, -0.891f, 0.316f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.927f, 0.234f, -0.295f, 0.188f, -0.389f, -0.902f, -0.325f, -0.891f, 0.316f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.267f, -0.234f, -0.935f, 0.907f, -0.389f, -0.162f, -0.325f, -0.891f, 0.316f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.936f, -0.256f, 0.241f, -0.134f, 0.374f, 0.918f, -0.325f, -0.891f, 0.316f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.916f, -0.395f, 0.071f, -0.207f, -0.314f, 0.927f, -0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.042f, -2.392f, -2.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.57f, -0.121f, 0.813f, -0.746f, 0.49f, -0.45f, -0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.042f, -2.392f, -0.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.851f, 0.121f, 0.511f, -0.396f, 0.49f, -0.776f, -0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.391f, 0.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.006f, 0.395f, -0.918f, 0.939f, -0.314f, -0.141f, -0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -2.391f, 2.242f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.316f, -0.395f, -0.862f, 0.929f, -0.313f, -0.197f, -0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.392f, -2.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.976f, -0.121f, 0.18f, -0.099f, 0.49f, 0.866f, -0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.392f, -0.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.819f, 0.121f, 0.561f, -0.541f, 0.49f, 0.683f, -0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.392f, 0.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.833f, 0.395f, 0.388f, -0.519f, -0.314f, -0.795f, -0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, -0.392f, 2.241f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.565f, -0.486f, -0.667f, 0.802f, -0.135f, -0.581f, 0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 0.392f, -1.842f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.37f, -0.376f, -0.849f, 0.909f, 0.336f, 0.247f, 0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 0.392f, -0.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.862f, 0.376f, 0.341f, -0.47f, 0.336f, 0.816f, 0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 0.392f, 0.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.07f, 0.486f, 0.871f, -0.979f, -0.135f, 0.154f, 0.193f, -0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 0.392f, 1.841f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.525f, -0.149f, 0.838f, -0.778f, -0.482f, 0.402f, 0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.391f, -2.842f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.926f, -0.376f, 0.017f, -0.154f, 0.336f, -0.929f, 0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.391f, -0.842f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.049f, 0.376f, -0.925f, 0.938f, 0.336f, 0.087f, 0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.391f, 0.842f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.873f, 0.149f, 0.465f, -0.346f, -0.482f, 0.805f, 0.344f, -0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.041f, 2.391f, 2.842f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.455f, -0.498f, -0.738f, -0.821f, -0.086f, 0.564f, -0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, -1.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.341f, 0.076f, -0.06f, 0.372f, 0.926f, -0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, -0.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.142f, 0.341f, 0.929f, 0.928f, 0.372f, 0.005f, -0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, 0.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.704f, 0.498f, 0.507f, 0.621f, -0.086f, -0.779f, -0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -2.391f, 1.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.98f, -0.197f, -0.041f, 0.056f, -0.465f, 0.884f, -0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -0.391f, -2.741f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.459f, -0.341f, 0.82f, 0.867f, 0.372f, -0.331f, -0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -0.391f, -0.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.904f, 0.341f, -0.257f, -0.381f, 0.372f, -0.846f, -0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -0.391f, 0.742f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.723f, 0.197f, -0.662f, -0.663f, -0.465f, 0.586f, -0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, -0.391f, 2.741f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.577f, -0.285f, 0.766f, 0.794f, -0.417f, 0.443f, 0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 0.391f, -2.542f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.962f, -0.26f, 0.084f, 0.194f, 0.433f, -0.88f, 0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 0.392f, -0.542f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.622f, 0.26f, -0.738f, -0.759f, 0.433f, -0.487f, 0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 0.392f, 0.541f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.949f, 0.285f, -0.136f, -0.25f, -0.417f, 0.874f, 0.193f, 0.863f, 0.467f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 0.392f, 2.542f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.939f, -0.317f, 0.133f, -0.003f, -0.393f, -0.92f, 0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.392f, -2.462f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.393f, -0.225f, -0.892f, -0.853f, 0.452f, 0.262f, 0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.392f, -0.462f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.917f, 0.225f, -0.329f, -0.201f, 0.452f, 0.452f, 0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.391f, 0.322f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.199f, 0.317f, 0.927f, 0.918f, -0.393f, -0.063f, 0.344f, 0.863f, -0.369f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.041f, 2.392f, 2.462f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.208f, 0.664f, -0.719f, -0.311f, 0.742f, 0.595f, 0.927f, 0.1f, 0.361f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.369f, 0.398f, 0.84f, -0.06f, -0.912f, 0.406f, 0.927f, 0.1f, 0.361f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.295f, -0.398f, 0.869f, 0.23f, -0.912f, -0.34f, 0.927f, 0.1f, 0.361f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.332f, -0.664f, -0.67f, 0.172f, 0.741f, -0.649f, 0.927f, 0.1f, 0.361f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.433f, 0.773f, -0.463f, 0.407f, 0.626f, 0.665f, 0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.55f, 0.248f, 0.798f, 0.225f, -0.964f, 0.144f, 0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.59f, -0.248f, 0.768f, -0.068f, -0.964f, -0.258f, 0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.308f, -0.773f, -0.555f, -0.508f, 0.626f, -0.59f, 0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.02f, 0.981f, 0.195f, 0.594f, 0.169f, -0.787f, -0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.488f, 0.672f, -0.556f, 0.338f, -0.734f, -0.589f, -0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.379f, -0.672f, -0.636f, -0.457f, -0.734f, 0.503f, -0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.18f, -0.981f, 0.08f, -0.566f, 0.169f, 0.807f, -0.804f, 0.1f, -0.586f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.374f, 0.927f, -0.019f, -0.906f, 0.361f, -0.221f, -0.198f, 0.1f, 0.975f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.561f, 0.804f, -0.196f, -0.804f, -0.586f, -0.103f, -0.198f, 0.1f, 0.975f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.593f, -0.804f, -0.038f, 0.781f, -0.586f, 0.218f, -0.198f, 0.1f, 0.975f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.337f, -0.927f, 0.163f, 0.921f, 0.361f, 0.15f, -0.198f, 0.1f, 0.975f));
	euler = PonyEngine::Math::Euler(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::Euler(matrix);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::Euler(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f));
	};
#endif
}

TEST_CASE("Euler from axis-angle", "[Math][Transformations]")
{
	auto axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	float angle = 0.f;
	auto euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());

	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = 0.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(euler.IsAlmostZero());
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float> * 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.247f, 1.22f, 1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.145f, 0.632f, 0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.247f, 1.22f, -1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.145f, 0.632f, -0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.145f, -0.632f, 0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.247f, -1.22f, 1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.145f, -0.632f, -0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.247f, -1.22f, -1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float>, -std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.73f, 2.034f, 2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.73f, -2.034f, -2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.73f, 2.034f, -2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.73f, -2.034f, 2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.73f, 2.034f, -2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.73f, -2.034f, 2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.73f, 2.034f, 2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.73f, -2.034f, -2.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, std::numbers::pi_v<float> * 2.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.145f, -0.632f, -0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.247f, -1.22f, -1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.145f, -0.632f, 0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.247f, -1.22f, 1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.247f, 1.22f, -1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.145f, 0.632f, -0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.247f, 1.22f, 1.22f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.145f, 0.632f, 0.632f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.362f, 0.805f, 0.672f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = 0.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.571f, 0.16f, 0.642f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = 1.1f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.422f, 0.591f, -0.988f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = 0.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.567f, 0.44f, -0.261f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = 1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.696f, -0.566f, 0.307f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = 0.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.338f, -0.494f, 0.775f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = 1.1f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.711f, -0.03f, -0.846f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = 0.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.368f, -0.613f, -0.509f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = 2.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.279f, 1.9f, 2.166f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = 3.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.66f, -2.021f, -2.389f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = 2.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.378f, 1.839f, -2.255f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = 2.7f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.047f, -1.647f, 2.671f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = 2.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.823f, 2.047f, -2.486f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = 3.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.434f, -1.96f, 2.259f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = 2.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.755f, 1.916f, 2.51f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = 2.7f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.405f, -1.612f, -2.077f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = -2.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.823f, 2.047f, 2.486f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = -3.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.434f, -1.96f, -2.259f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = -2.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.755f, 1.916f, -2.51f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = -2.7f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.405f, -1.612f, 2.077f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = -2.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.279f, 1.901f, -2.166f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = -3.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.66f, -2.021f, 2.389f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = -2.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.378f, 1.839f, 2.255f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = -2.7f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.047f, -1.647f, -2.671f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = -1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.696f, -0.566f, -0.307f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = -0.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.338f, -0.494f, -0.775f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = -1.1f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.711f, -0.03f, 0.846f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = -0.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.368f, -0.613f, 0.509f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = -1.f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.362f, 0.805f, -0.672f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = -0.9f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.571f, 0.16f, -0.642f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = -1.1f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.422f, 0.591f, 0.988f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = -0.8f;
	euler = PonyEngine::Math::Euler(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.567f, 0.44f, 0.261f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::Euler(axis, angle);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::Euler(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), std::numbers::pi_v<float> / 2.f);
	};
#endif
}

TEST_CASE("Euler from from-to", "[Math][Transformations]")
{
	auto from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	auto to = from;
	auto euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(euler.IsAlmostZero());
	
	from = PonyEngine::Math::Vector3<float>(-3.f, 4.f, 2.3f).Normalized();
	to = from;
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(euler.IsAlmostZero());
	
	from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	to = -from;
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float>, -std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	to = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 0.f, 1.f).Normalized();
	to = -from;
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, -std::numbers::pi_v<float>), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f).Normalized();
	to = -from;
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, std::numbers::pi_v<float>), FixRotation(euler), PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = -from;
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, -2.747f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));
	
	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(6.f, 5.f, 3.f).Normalized();
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.255f, -0.005f, -0.625f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(-6.f, -5.f, 3.f).Normalized();
	euler = PonyEngine::Math::FromToEuler(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.918f, 1.082f, 2.611f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::FromToEuler(from, to);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::FromToEuler(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f));
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::FromToEuler(from, from);
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::FromToEuler(from, -from);
	};
#endif
}

TEST_CASE("Euler from look-in", "[Math][Transformations]")
{
	const auto forward = PonyEngine::Math::Vector3<float>(-3.f, 2.4f, 1.7f).Normalized();
	const auto up = PonyEngine::Math::Vector3<float>(1.f, 1.2f, 0.7f).Normalized();
	auto euler = PonyEngine::Math::LookInEuler(forward, up);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.608f, -1.055f, -0.708f), euler, PonyEngine::Math::Tolerance{.absolute = 0.01f}));

	euler = PonyEngine::Math::LookInEuler(forward, forward);
	auto expectedEuler = PonyEngine::Math::FromToEuler(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedEuler, euler));

	euler = PonyEngine::Math::LookInEuler(forward, -forward);
	expectedEuler = PonyEngine::Math::FromToEuler(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedEuler, euler));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::LookInEuler(forward, up);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::LookInEuler(PonyEngine::Math::Vector3<float>::Down(), PonyEngine::Math::Vector3<float>::Forward());
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::LookInEuler(PonyEngine::Math::Vector3<float>::Forward(), PonyEngine::Math::Vector3<float>::Forward());
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::LookInEuler(PonyEngine::Math::Vector3<float>::Forward(), -PonyEngine::Math::Vector3<float>::Forward());
	};
#endif
}

TEST_CASE("Axis-angle from quaternion", "[Math][Transformations]")
{
	auto quaternion = PonyEngine::Math::Quaternion<float>::Identity();
	std::pair<PonyEngine::Math::Vector3<float>, float> axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.7071068f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.7071068f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Back(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.7071068f, 0.f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Up(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, -0.7071068f, 0.f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Down(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.7071068f, 0.f, 0.f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Right(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.7071068f, 0.f, 0.f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Left(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4082483f, 0.4082483f, 0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.4082483f, 0.4082483f, 0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.4082483f, 0.4082483f, -0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4082483f, 0.4082483f, -0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4082483f, -0.4082483f, 0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.4082483f, -0.4082483f, 0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.4082483f, -0.4082483f, -0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4082483f, -0.4082483f, -0.4082483f, 0.7071068f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Back(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Up(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, -1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Down(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Right(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-1.f, 0.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Left(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5773503f, 0.5773503f, 0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5773503f, 0.5773503f, 0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5773503f, 0.5773503f, -0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5773503f, 0.5773503f, -0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5773503f, -0.5773503f, 0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5773503f, -0.5773503f, 0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5773503f, -0.5773503f, -0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5773503f, -0.5773503f, -0.5773503f, 0.f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.4794255f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.4794255f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.4794255f, 0.f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.f, -0.4794255f, 0.f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.4794255f, 0.f, 0.f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.4794255f, 0.f, 0.f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2835148f, 0.3092889f, 0.2319667f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, 0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.2423132f, 0.1615421f, 0.3230843f, 0.9004471f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, 0.371f, 0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.3116704f, 0.1558352f, -0.3895881f, 0.8525245f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, 0.298f, -0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2432677f, 0.2432677f, -0.1824508f, 0.921061f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, 0.625f, -0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2835148f, -0.3092889f, 0.2319667f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, -0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.2423132f, -0.1615421f, 0.3230843f, 0.9004471f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, -0.371f, 0.742f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.3116704f, -0.1558352f, -0.3895881f, 0.8525245f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, -0.298f, -0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2432677f, -0.2432677f, -0.1824508f, 0.921061f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, -0.625f, -0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6738145f, 0.4492097f, 0.5615121f, 0.1699671f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6820506f, 0.4547004f, 0.5683755f, 0.0707372f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, 0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6567605f, 0.4378403f, -0.6020304f, 0.1205028f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.662f, 0.441f, -0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5384289f, 0.4786035f, -0.6580798f, 0.2190067f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.552f, 0.491f, -0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6738145f, -0.4492097f, 0.5615121f, 0.1699671f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6820506f, -0.4547004f, 0.5683755f, 0.0707372f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, -0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6567605f, -0.4378403f, -0.6020304f, 0.1205028f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.662f, -0.441f, -0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.5384289f, -0.4786035f, -0.6580798f, 0.2190067f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.552f, -0.491f, -0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6738145f, -0.4492097f, -0.5615121f, 0.1699671f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, -0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6820506f, -0.4547004f, -0.5683755f, 0.0707372f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6567605f, -0.4378403f, 0.6020304f, 0.1205028f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, -0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5384289f, -0.4786035f, 0.6580798f, 0.2190067f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, -0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.6738145f, 0.4492097f, -0.5615121f, 0.1699671f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, 0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6820506f, 0.4547004f, -0.5683755f, 0.0707372f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.6567605f, 0.4378403f, 0.6020304f, 0.1205028f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, 0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.5384289f, 0.4786035f, 0.6580798f, 0.2190067f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, 0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.2835148f, -0.3092889f, -0.2319667f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.591f, -0.645f, -0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2423132f, -0.1615421f, -0.3230843f, 0.9004471f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.557f, -0.371f, -0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.3116704f, -0.1558352f, 0.3895881f, 0.8525245f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.596f, -0.298f, 0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.2432677f, -0.2432677f, 0.1824508f, 0.921061f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.625f, -0.625f, 0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(-0.2835148f, 0.3092889f, -0.2319667f, 0.8775826f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.591f, 0.645f, -0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.2423132f, 0.1615421f, -0.3230843f, 0.9004471f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.557f, 0.371f, -0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	quaternion = PonyEngine::Math::Quaternion<float>(0.3116704f, 0.1558352f, 0.3895881f, 0.8525245f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.596f, 0.298f, 0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	quaternion = PonyEngine::Math::Quaternion<float>(-0.2432677f, 0.2432677f, 0.1824508f, 0.921061f).Normalized();
	axisAngle = PonyEngine::Math::AxisAngle(quaternion);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.625f, 0.625f, 0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::AxisAngle(quaternion);
	};
	BENCHMARK("Identity")
	{
		return PonyEngine::Math::AxisAngle(PonyEngine::Math::Quaternion<float>::Identity());
	};
#endif
}

TEST_CASE("Axis-angle from rotation matrix", "[Math][Transformations]")
{
	auto matrix = PonyEngine::Math::Matrix3x3<float>::Identity();
	std::pair<PonyEngine::Math::Vector3<float>, float> axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Back(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Up(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Down(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Right(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Left(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, -0.244f, -0.244f, 0.333f, 0.911f, 0.911f, -0.244f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, -0.911f, -0.911f, 0.333f, -0.244f, 0.244f, 0.911f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, -0.244f, 0.244f, 0.333f, -0.911f, 0.911f, 0.244f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, -0.911f, 0.911f, 0.333f, 0.244f, 0.244f, -0.911f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.244f, 0.911f, -0.911f, 0.333f, 0.244f, -0.244f, -0.911f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, 0.911f, 0.244f, -0.244f, 0.333f, -0.911f, -0.911f, 0.244f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.244f, 0.911f, 0.911f, 0.333f, -0.244f, -0.244f, 0.911f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.333f, -0.911f, 0.244f, 0.244f, 0.333f, 0.911f, -0.911f, -0.244f, 0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Up(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f);
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Right(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, 0.667f, 0.667f, 0.667f, -0.333f, 0.667f, 0.667f, 0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, -0.667f, -0.667f, -0.667f, -0.333f, 0.667f, -0.667f, 0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, -0.667f, 0.667f, -0.667f, -0.333f, -0.667f, 0.667f, -0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}) | PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, 0.667f, -0.667f, 0.667f, -0.333f, -0.667f, -0.667f, -0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, -0.667f, 0.667f, -0.667f, -0.333f, -0.667f, 0.667f, -0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, 0.667f, -0.667f, 0.667f, -0.333f, -0.667f, -0.667f, -0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, 0.667f, 0.667f, 0.667f, -0.333f, 0.667f, 0.667f, 0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.333f, -0.667f, -0.667f, -0.667f, -0.333f, 0.667f, -0.667f, 0.667f, -0.333f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.841f, 0.f, -0.841f, 0.54f, 0.f, 0.f, 0.f, 1.f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.54f, -0.841f, 0.f, 0.841f, 0.54f, 0.f, 0.f, 0.f, 1.f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.f, -0.841f, 0.f, 1.f, 0.f, 0.841f, 0.f, 0.54f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.54f, 0.f, 0.841f, 0.f, 1.f, 0.f, -0.841f, 0.f, 0.54f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.54f, 0.841f, 0.f, -0.841f, 0.54f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.54f, -0.841f, 0.f, 0.841f, 0.54f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.701f, 0.583f, -0.411f, -0.232f, 0.732f, 0.641f, 0.674f, -0.354f, 0.648f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, 0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.739f, 0.503f, -0.447f, -0.66f, 0.674f, -0.332f, 0.134f, 0.541f, 0.83f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, 0.371f, 0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.647f, -0.761f, -0.023f, 0.567f, 0.502f, -0.653f, 0.509f, 0.41f, 0.757f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, 0.298f, -0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.815f, -0.218f, -0.537f, 0.454f, 0.815f, 0.359f, 0.359f, -0.537f, 0.763f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, 0.625f, -0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.701f, 0.232f, 0.674f, -0.583f, 0.732f, 0.354f, -0.411f, -0.641f, 0.648f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, -0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.739f, 0.66f, 0.134f, -0.504f, 0.674f, -0.541f, -0.447f, 0.332f, 0.83f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, -0.371f, 0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.648f, -0.567f, 0.509f, 0.761f, 0.502f, -0.41f, -0.023f, 0.653f, 0.757f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, -0.298f, -0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.815f, -0.454f, 0.359f, 0.218f, 0.815f, 0.537f, -0.537f, -0.359f, 0.763f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, -0.625f, -0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.034f, 0.796f, 0.604f, 0.414f, -0.539f, 0.734f, 0.909f, 0.275f, -0.312f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.06f, -0.54f, -0.84f, -0.701f, -0.576f, 0.42f, -0.711f, 0.613f, -0.344f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.283f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.108f, -0.72f, 0.685f, -0.43f, -0.588f, -0.685f, 0.896f, -0.369f, -0.246f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, -0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.383f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.324f, 0.227f, -0.918f, 0.804f, -0.446f, -0.394f, -0.499f, -0.866f, -0.038f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, -0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.583f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.034f, -0.414f, 0.909f, -0.796f, -0.539f, -0.275f, 0.604f, -0.734f, -0.312f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.06f, 0.701f, -0.711f, 0.54f, -0.576f, -0.613f, -0.84f, -0.42f, -0.344f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.283f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.108f, 0.43f, 0.896f, 0.72f, -0.588f, 0.369f, 0.685f, 0.685f, -0.246f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, 0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.383f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.324f, -0.804f, -0.499f, -0.227f, -0.446f, 0.866f, -0.918f, 0.394f, -0.038f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, 0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.583f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.034f, 0.414f, 0.909f, 0.796f, -0.539f, 0.275f, 0.604f, 0.734f, -0.312f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.483f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.06f, -0.701f, -0.711f, -0.54f, -0.576f, 0.613f, -0.84f, 0.42f, -0.344f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.108f, -0.43f, 0.896f, -0.72f, -0.588f, -0.369f, 0.685f, -0.685f, -0.246f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, -0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.324f, 0.804f, -0.499f, 0.227f, -0.446f, -0.865f, -0.918f, -0.394f, -0.038f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, -0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.034f, -0.796f, 0.604f, -0.414f, -0.539f, -0.734f, 0.909f, -0.275f, -0.312f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.483f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.06f, 0.54f, -0.84f, 0.701f, -0.576f, -0.42f, -0.711f, -0.613f, -0.344f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.108f, 0.72f, 0.685f, 0.43f, -0.588f, 0.685f, 0.896f, 0.369f, -0.246f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, 0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.324f, -0.227f, -0.918f, -0.804f, -0.446f, 0.394f, -0.499f, 0.866f, -0.038f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, 0.491f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.701f, -0.232f, 0.674f, 0.583f, 0.732f, -0.354f, -0.411f, 0.641f, 0.648f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.591f, -0.645f, -0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.739f, -0.66f, 0.134f, 0.504f, 0.674f, 0.541f, -0.447f, -0.332f, 0.83f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.557f, -0.371f, -0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.648f, 0.567f, 0.509f, -0.761f, 0.502f, 0.41f, -0.023f, -0.653f, 0.757f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.596f, -0.298f, 0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.815f, 0.454f, 0.359f, -0.218f, 0.815f, -0.537f, -0.537f, 0.359f, 0.763f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.625f, -0.625f, 0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.701f, -0.583f, -0.411f, 0.232f, 0.732f, -0.641f, 0.674f, 0.354f, 0.648f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.591f, 0.645f, -0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.739f, -0.504f, -0.447f, 0.66f, 0.674f, 0.332f, 0.134f, -0.541f, 0.83f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.557f, 0.371f, -0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.648f, 0.761f, -0.023f, -0.567f, 0.502f, 0.653f, 0.509f, -0.41f, 0.757f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.596f, 0.298f, 0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(0.815f, 0.218f, -0.537f, -0.454f, 0.815f, -0.359f, 0.359f, 0.537f, 0.763f));
	axisAngle = PonyEngine::Math::AxisAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.625f, 0.625f, 0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::AxisAngle(matrix);
	};
	BENCHMARK("Identity")
	{
		return PonyEngine::Math::AxisAngle(PonyEngine::Math::Matrix3x3<float>::Identity());
	};
#endif
}

TEST_CASE("Axis-angle from Euler angles", "[Math][Transformations]")
{
	auto euler = PonyEngine::Math::Vector3<float>::Zero();
	auto axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Forward(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Back(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Up(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Down(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Right(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>::Left(), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.247f, 1.22f, 1.22f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-1.145f, 0.632f, 0.632f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.247f, 1.22f, -1.22f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.145f, 0.632f, -0.632f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.145f, -0.632f, 0.632f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.247f, -1.22f, 1.22f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-1.145f, -0.632f, -0.632f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.247f, -1.22f, -1.22f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float> / 2.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float>);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float>, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float>, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.73f, 2.034f, 2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.73f, -2.034f, -2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.73f, 2.034f, -2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.73f, -2.034f, 2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.73f, 2.034f, -2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, 0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.73f, -2.034f, 2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.577f, -0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.73f, 2.034f, 2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, 0.577f, 0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.73f, -2.034f, -2.034f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.577f, -0.577f, -0.577f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.362f, 0.805f, 0.672f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, 0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.571f, 0.16f, 0.642f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, 0.371f, 0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.422f, 0.591f, -0.988f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, 0.298f, -0.746f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.567f, 0.44f, -0.261f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, 0.625f, -0.468f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.696f, -0.566f, 0.307f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.591f, -0.645f, 0.484f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.338f, -0.494f, 0.775f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.557f, -0.371f, 0.743f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.711f, -0.03f, -0.846f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.596f, -0.298f, -0.745f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.1f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.368f, -0.613f, -0.509f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.625f, -0.624f, -0.469f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.279f, 1.9f, 2.166f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, 0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.8f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.66f, -2.021f, -2.389f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.684f, -0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.283f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.378f, 1.839f, -2.255f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.662f, 0.441f, -0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.9f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(1.047f, -1.647f, 2.671f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.552f, -0.49f, 0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.584f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.823f, 2.047f, -2.486f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, 0.456f, -0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.483f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(0.434f, -1.96f, 2.259f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.684f, -0.456f, 0.57f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.0f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	euler = PonyEngine::Math::Vector3<float>(-0.755f, 1.916f, 2.51f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.662f, 0.441f, 0.606f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(3.383f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	euler = PonyEngine::Math::Vector3<float>(-0.405f, -1.612f, -2.077f);
	axisAngle = PonyEngine::Math::AxisAngle(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.552f, -0.491f, -0.674f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.7f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::AxisAngle(PonyEngine::Math::Vector3<float>(-0.755f, 1.916f, 2.51f));
	};
	BENCHMARK("Identity")
	{
		return PonyEngine::Math::AxisAngle(PonyEngine::Math::Vector3<float>::Zero());
	};
#endif
}

TEST_CASE("Axis-angle from from-to", "[Math][Transformations]")
{
	auto from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	auto to = from;
	auto axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(-3.f, 4.f, 2.3f).Normalized();
	to = from;
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f).Normalized();
	to = -from;
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 0.f, 1.f).Normalized();
	to = -from;
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.707f, 0.f, 0.707f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f).Normalized();
	to = -from;
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = -from;
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.98f, -0.196f, 0.f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(std::numbers::pi_v<float>, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(6.f, 5.f, 3.f).Normalized();
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.369f, 0.111f, -0.922f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(0.673f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
	to = PonyEngine::Math::Vector3<float>(-6.f, -5.f, 3.f).Normalized();
	axisAngle = PonyEngine::Math::FromToAxisAngle(from, to);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.601f, -0.271f, 0.752f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.271f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::FromToAxisAngle(from, to);
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::FromToAxisAngle(from, from);
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::FromToAxisAngle(from, -from);
	};
#endif
}

TEST_CASE("Axis-angle from look-in", "[Math][Transformations]")
{
	const auto forward = PonyEngine::Math::Vector3<float>(-3.f, 2.4f, 1.7f).Normalized();
	const auto up = PonyEngine::Math::Vector3<float>(1.f, 1.2f, 0.7f).Normalized();
	auto axisAngle = PonyEngine::Math::LookInAxisAngle(forward, up);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.11f, -0.78f, -0.617f), axisAngle.first, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.531f, axisAngle.second, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axisAngle = PonyEngine::Math::LookInAxisAngle(forward, forward);
	auto expectedAxisAngle = PonyEngine::Math::FromToAxisAngle(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedAxisAngle.first, axisAngle.first));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedAxisAngle.second, axisAngle.second));

	axisAngle = PonyEngine::Math::LookInAxisAngle(forward, -forward);
	expectedAxisAngle = PonyEngine::Math::FromToAxisAngle(PonyEngine::Math::Vector3<float>::Forward(), forward);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedAxisAngle.first, axisAngle.first));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(expectedAxisAngle.second, axisAngle.second));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::LookInAxisAngle(forward, up);
	};
	BENCHMARK("Singularity")
	{
		return PonyEngine::Math::LookInAxisAngle(PonyEngine::Math::Vector3<float>::Down(), PonyEngine::Math::Vector3<float>::Forward());
	};
	BENCHMARK("Parallel")
	{
		return PonyEngine::Math::LookInAxisAngle(PonyEngine::Math::Vector3<float>::Forward(), PonyEngine::Math::Vector3<float>::Forward());
	};
	BENCHMARK("Anti-parallel")
	{
		return PonyEngine::Math::LookInAxisAngle(PonyEngine::Math::Vector3<float>::Forward(), -PonyEngine::Math::Vector3<float>::Forward());
	};
#endif
}

TEST_CASE("Rs matrix from angle-scaling", "[Math][Transformations]")
{
	float angle = 1.065f;
	auto scaling = PonyEngine::Math::Vector2<float>(2.f, 3.f);
	auto matrix = PonyEngine::Math::RsMatrix(angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(0.969f, 1.7496f, -2.6243f, 1.4535f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = 1.065f;
	scaling = PonyEngine::Math::Vector2<float>(-4.f, 6.f);
	matrix = PonyEngine::Math::RsMatrix(angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(-1.938f, -3.5f, -5.249f, 2.907f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	
	angle = 1.065f;
	scaling = PonyEngine::Math::Vector2<float>(3.f, -2.f);
	matrix = PonyEngine::Math::RsMatrix(angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(1.4535f, 2.6244f, 1.7496f, -0.969f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	angle = 1.065f;
	scaling = PonyEngine::Math::Vector2<float>(-0.5f, -1.f);
	matrix = PonyEngine::Math::RsMatrix(angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x2<float>(-0.2423f, -0.4374f, 0.8748f, -0.4845f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RsMatrix(1.065f, PonyEngine::Math::Vector2<float>(3.f, -2.f));
	};
#endif
}

TEST_CASE("Rs matrix from quaternion-scaling", "[Math][Transformations]")
{
	constexpr auto quaternionC = PonyEngine::Math::Quaternion<float>(0.1563738f, 0.3127476f, 0.4691215f, 0.8109631f);
	constexpr auto scalingC = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto rsMatrixC = PonyEngine::Math::RsMatrix(quaternionC, scalingC);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f), rsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	auto quaternion = PonyEngine::Math::Quaternion<float>(-0.2411412f, -0.4822823f, -0.7234235f, 0.4311765f).Normalized();
	auto scaling = PonyEngine::Math::Vector3<float>(-5.6f, -4.5f, -0.3f);
	auto rsMatrix = PonyEngine::Math::RsMatrix(quaternion, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(2.867f, 2.191f, -4.283f, -3.854f, 0.733f, -2.204f, 0.02f, -0.272f, -0.126f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RsMatrix(quaternion, scaling);
	};
#endif
}

TEST_CASE("Rs matrix from rotation matrix-scaling", "[Math][Transformations]")
{
	constexpr auto matrixC = PonyEngine::Math::Matrix3x3<float>(0.3642279f, 0.8586916f, -0.3605369f, -0.6630694f, 0.5109445f, 0.5470600f, 0.6539702f, 0.0398065f, 0.7554724f);
	constexpr auto scalingC = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto rsMatrixC = PonyEngine::Math::RsMatrix(matrixC, scalingC);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f), rsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	auto matrix = PonyEngine::Math::NormalizeColumns(PonyEngine::Math::Matrix3x3<float>(-0.5118755f, -0.3912502f, 0.7647920f, 0.8564427f, -0.1629812f, 0.4898399f, -0.0670032f, 0.9057375f, 0.4185094f));
	auto scaling = PonyEngine::Math::Vector3<float>(-5.6f, -4.5f, -0.3f);
	auto rsMatrix = PonyEngine::Math::RsMatrix(matrix, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(2.867f, 2.191f, -4.283f, -3.854f, 0.733f, -2.204f, 0.02f, -0.272f, -0.126f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RsMatrix(matrix, scaling);
	};
#endif
}

TEST_CASE("Rs matrix from euler-scaling", "[Math][Transformations]")
{
	auto euler = PonyEngine::Math::Vector3<float>(-0.039817f, 0.7135064f, 1.0340416f);
	auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	auto rsMatrix = PonyEngine::Math::RsMatrix(euler, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	euler = PonyEngine::Math::Vector3<float>(-1.1331166f, -0.1587523f, -1.9655011f);
	scaling = PonyEngine::Math::Vector3<float>(-5.6f, -4.5f, -0.3f);
	rsMatrix = PonyEngine::Math::RsMatrix(euler, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(2.867f, 2.191f, -4.283f, -3.854f, 0.733f, -2.204f, 0.02f, -0.272f, -0.126f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RsMatrix(euler, scaling);
	};
#endif
}

TEST_CASE("Rs matrix from axis-angle-scaling", "[Math][Transformations]")
{
	auto axis = PonyEngine::Math::Vector3<float>(0.2672612f, 0.5345224f, 0.8017838f).Normalized();
	float angle = 1.25f;
	auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	auto rsMatrix = PonyEngine::Math::RsMatrix(axis, angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	axis = PonyEngine::Math::Vector3<float>(-0.2672613f, -0.5345225f, -0.8017837f).Normalized();
	angle = 2.25f;
	scaling = PonyEngine::Math::Vector3<float>(-5.6f, -4.5f, -0.3f);
	rsMatrix = PonyEngine::Math::RsMatrix(axis, angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(2.867f, 2.191f, -4.283f, -3.854f, 0.733f, -2.204f, 0.02f, -0.272f, -0.126f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RsMatrix(axis, angle, scaling);
	};
#endif
}

TEST_CASE("Trs matrix from translation-angle-scaling", "[Math][Transformations]")
{
	constexpr PonyEngine::Math::Vector2<float> translation(-3.f, 7.f);
	constexpr float rotation = 1.065f;
	constexpr PonyEngine::Math::Vector2<float> scaling(-2.f, 3.f);
	const auto matrix = PonyEngine::Math::TrsMatrix(translation, rotation, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(-0.969f, -1.7496f, 0.f, -2.6244f, 1.4535f, 0.f, -3.f, 7.f, 1.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(PonyEngine::Math::Vector2<float>(2.f, -4.f), -1.2f, PonyEngine::Math::Vector2<float>(-3.f, 2.f));
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-angle-scaling", "[Math][Transformations]")
{
	constexpr PonyEngine::Math::Vector2<float> translation(-3.f, 7.f);
	constexpr float rotation = 1.065f;
	constexpr PonyEngine::Math::Vector2<float> scaling(-2.f, 3.f);
	const auto matrix = PonyEngine::Math::TrsMatrixCompact(translation, rotation, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix2x3<float>(-0.969f, -1.7496f, -2.6244f, 1.4535f, -3.f, 7.f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(PonyEngine::Math::Vector2<float>(2.f, -4.f), -1.2f, PonyEngine::Math::Vector2<float>(-3.f, 2.f));
	};
#endif
}

TEST_CASE("Trs matrix from translation-quaternion-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(0.1563738f, 0.3127476f, 0.4691215f, 0.8109631f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto trsMatrix = PonyEngine::Math::TrsMatrix(translation, quaternion, scaling);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(translation, quaternion, scaling);
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-quaternion-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto quaternion = PonyEngine::Math::Quaternion<float>(0.1563738f, 0.3127476f, 0.4691215f, 0.8109631f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(translation, quaternion, scaling);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(translation, quaternion, scaling);
	};
#endif
}

TEST_CASE("Trs matrix from translation-rotation matrix-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto matrix = PonyEngine::Math::Matrix3x3<float>(0.3642279f, 0.8586916f, -0.3605369f, -0.6630694f, 0.5109445f, 0.5470600f, 0.6539702f, 0.0398065f, 0.7554724f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto trsMatrix = PonyEngine::Math::TrsMatrix(translation, matrix, scaling);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(translation, matrix, scaling);
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-rotation matrix-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto matrix = PonyEngine::Math::Matrix3x3<float>(0.3642279f, 0.8586916f, -0.3605369f, -0.6630694f, 0.5109445f, 0.5470600f, 0.6539702f, 0.0398065f, 0.7554724f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	constexpr auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(translation, matrix, scaling);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(translation, matrix, scaling);
	};
#endif
}

TEST_CASE("Trs matrix from translation-euler-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto euler = PonyEngine::Math::Vector3<float>(-0.039817f, 0.7135064f, 1.0340416f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	const auto trsMatrix = PonyEngine::Math::TrsMatrix(translation, euler, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(translation, euler, scaling);
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-euler-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto euler = PonyEngine::Math::Vector3<float>(-0.039817f, 0.7135064f, 1.0340416f);
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	const auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(translation, euler, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(translation, euler, scaling);
	};
#endif
}

TEST_CASE("Trs matrix from translation-axis-angle-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto axis = PonyEngine::Math::Vector3<float>(0.2672612f, 0.5345224f, 0.8017838f);
	constexpr auto angle = 1.25f;
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	const auto trsMatrix = PonyEngine::Math::TrsMatrix(translation, axis, angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(translation, axis, angle, scaling);
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-axis-angle-scaling", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto axis = PonyEngine::Math::Vector3<float>(0.2672612f, 0.5345224f, 0.8017838f);
	constexpr auto angle = 1.25f;
	constexpr auto scaling = PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f);
	const auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(translation, axis, angle, scaling);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(translation, axis, angle, scaling);
	};
#endif
}

TEST_CASE("Trs matrix from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	constexpr auto trsMatrixC = PonyEngine::Math::TrsMatrix(rsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, 0.f, 0.f, 0.f, 1.f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::TrsMatrix(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, 0.f, 0.f, 0.f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(rsMatrix);
	};
#endif
}

TEST_CASE("Trs matrix compact from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	constexpr auto trsMatrixC = PonyEngine::Math::TrsMatrixCompact(rsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, 0.f, 0.f, 0.f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, 0.f, 0.f, 0.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(rsMatrix);
	};
#endif
}

TEST_CASE("Trs matrix from translation-rs matrix", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	constexpr auto trsMatrixC = PonyEngine::Math::TrsMatrix(translation, rsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::TrsMatrix(translation, rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(translation, rsMatrix);
	};
#endif
}

TEST_CASE("Trs matrix compact from translation-rs matrix", "[Math][Transformations]")
{
	constexpr auto translation = PonyEngine::Math::Vector3<float>(-3.1f, 4.6f, 9.5f);
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	constexpr auto trsMatrixC = PonyEngine::Math::TrsMatrixCompact(translation, rsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::TrsMatrixCompact(translation, rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrixCompact(translation, rsMatrix);
	};
#endif
}

TEST_CASE("Trs matrix from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto origMatrix = PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f);
	constexpr auto trsMatrixC = PonyEngine::Math::TrsMatrix(origMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::TrsMatrix(origMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TrsMatrix(origMatrix);
	};
#endif
}

TEST_CASE("Perspective matrix", "[Math][Transformations]")
{
	const auto perspectiveMatrix = PonyEngine::Math::PerspectiveMatrix(80.f * PonyEngine::Math::DegToRad<float>, 1.7f, 0.2f, 1000.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(0.701f, 0.f, 0.f, 0.f, 0.f, 1.192f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, -0.2f, 0.f), perspectiveMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::PerspectiveMatrix(80.f * PonyEngine::Math::DegToRad<float>, 1.7f, 0.2f, 1000.f);
	};
#endif
}

TEST_CASE("Orthographic matrix", "[Math][Transformations]")
{
	const auto orthographicMatrix = PonyEngine::Math::OrthographicMatrix(20.f * 1.7f, 20.f, 0.2f, 1000.f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix4x4<float>(0.0588f, 0.f, 0.f, 0.f, 0.f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.001f, 0.f, 0.f, 0.f, -0.0002f, 1.f), orthographicMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::OrthographicMatrix(20.f * 1.7f, 20.f, 0.2f, 1000.f);
	};
#endif
}

TEST_CASE("Translation from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, -4.2f, -6.4f, 3.1f, 1.f);
	constexpr auto translation = PonyEngine::Math::ExtractTranslationFromTrs(trsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-4.2f, -6.4f, 3.1f), translation, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractTranslationFromTrs(PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, -4.2f, -6.4f, 3.1f, 1.f));
	};
#endif
}

TEST_CASE("Translation from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, -4.2f, -6.4f, 3.1f);
	constexpr auto translation = PonyEngine::Math::ExtractTranslationFromTrs(trsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-4.2f, -6.4f, 3.1f), translation, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractTranslationFromTrs(PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, -4.2f, -6.4f, 3.1f));
	};
#endif
}

TEST_CASE("Angle from rs matrix", "[Math][Transformations]")
{
	auto rsMatrix = PonyEngine::Math::Matrix2x2<float>(0.97f, 1.75f, -2.625f, 1.455f);
	float angle = PonyEngine::Math::ExtractAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	rsMatrix = PonyEngine::Math::Matrix2x2<float>(-1.94f, -3.5f, -5.25f, 2.91f);
	angle = PonyEngine::Math::ExtractAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.077f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	rsMatrix = PonyEngine::Math::Matrix2x2<float>(1.455f, 2.625f, 1.75f, -0.97f);
	angle = PonyEngine::Math::ExtractAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	rsMatrix = PonyEngine::Math::Matrix2x2<float>(-0.243f, -0.438f, 0.875f, -0.485f);
	angle = PonyEngine::Math::ExtractAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.077f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	rsMatrix = PonyEngine::Math::Matrix2x2<float>(0.f, 0.f, 0.875f, -0.485f);
	angle = PonyEngine::Math::ExtractAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.077f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::ExtractAngleFromRs(PonyEngine::Math::Matrix2x2<float>(1.455f, 2.625f, 1.75f, -0.97f));
	};
	BENCHMARK("Zero first column")
	{
		return PonyEngine::Math::ExtractAngleFromRs(PonyEngine::Math::Matrix2x2<float>(0.f, 0.f, 1.75f, -0.97f));
	};
#endif
}

TEST_CASE("Angle from trs matrix", "[Math][Transformations]")
{
	auto trsMatrix = PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
	float angle = PonyEngine::Math::ExtractAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.077f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	trsMatrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f);
	angle = PonyEngine::Math::ExtractAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::ExtractAngleFromTrs(PonyEngine::Math::Matrix3x3<float>(-0.97f, -1.75f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f));
	};
	BENCHMARK("Zero first column")
	{
		return PonyEngine::Math::ExtractAngleFromTrs(PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 0.f, -2.625f, 1.455f, 0.f, -3.f, 7.f, 1.f));
	};
#endif
}

TEST_CASE("Angle from trs matrix compact", "[Math][Transformations]")
{
	auto trsMatrix = PonyEngine::Math::Matrix2x3<float>(-0.97f, -1.75f, -2.625f, 1.455f, -3.f, 7.f);
	float angle = PonyEngine::Math::ExtractAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.077f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

	trsMatrix = PonyEngine::Math::Matrix2x3<float>(0.f, 0.f, -2.625f, 1.455f, -3.f, 7.f);
	angle = PonyEngine::Math::ExtractAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Usual")
	{
		return PonyEngine::Math::ExtractAngleFromTrs(PonyEngine::Math::Matrix2x3<float>(-0.97f, -1.75f, -2.625f, 1.455f, -3.f, 7.f));
	};
	BENCHMARK("Zero first column")
	{
		return PonyEngine::Math::ExtractAngleFromTrs(PonyEngine::Math::Matrix2x3<float>(0.f, 0.f, -2.625f, 1.455f, -3.f, 7.f));
	};
#endif
}

TEST_CASE("Trs matrix compact from trs matrix", "[Math][Transformations]")
{
	constexpr auto origMatrix = PonyEngine::Math::Matrix4x4<float>(1.202f, 2.834f, -1.19f, 0.f, -2.785f, 2.146f, 2.298f, 0.f, 1.57f, 0.096f, 1.813f, 0.f, -3.1f, 4.6f, 9.5f, 1.f);
	constexpr auto trsMatrixC = PonyEngine::Math::ExtractTrsMatrixFromTrs(origMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	auto trsMatrix = PonyEngine::Math::ExtractTrsMatrixFromTrs(origMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.202f, 2.834f, -1.19f, -2.785f, 2.146f, 2.298f, 1.57f, 0.096f, 1.813f, -3.1f, 4.6f, 9.5f), trsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractTrsMatrixFromTrs(origMatrix);
	};
#endif
}

TEST_CASE("Quaternion from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	const auto quaternion = PonyEngine::Math::ExtractRotationQuaternionFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.156f, 0.313f, 0.469f, 0.811f), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationQuaternionFromRs(rsMatrix);
	};
#endif
}

TEST_CASE("Quaternion from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, -4.2f, -6.4f, 3.1f, 1.f);
	const auto quaternion = PonyEngine::Math::ExtractRotationQuaternionFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.156f, 0.313f, 0.469f, 0.811f), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationQuaternionFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Quaternion from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, -4.2f, -6.4f, 3.1f);
	const auto quaternion = PonyEngine::Math::ExtractRotationQuaternionFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.156f, 0.313f, 0.469f, 0.811f), quaternion, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationQuaternionFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Rotation matrix from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	const auto matrix = PonyEngine::Math::ExtractRotationMatrixFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.364f, 0.859f, -0.361f, -0.663f, 0.511f, 0.547f, 0.654f, 0.04f, 0.755f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationMatrixFromRs(rsMatrix);
	};
#endif
}

TEST_CASE("Rotation matrix from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	const auto matrix = PonyEngine::Math::ExtractRotationMatrixFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.364f, 0.859f, -0.361f, -0.663f, 0.511f, 0.547f, 0.654f, 0.04f, 0.755f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationMatrixFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Rotation matrix from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	const auto matrix = PonyEngine::Math::ExtractRotationMatrixFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(0.364f, 0.859f, -0.361f, -0.663f, 0.511f, 0.547f, 0.654f, 0.04f, 0.755f), matrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRotationMatrixFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Euler angles from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	const auto euler = PonyEngine::Math::ExtractEulerFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.04f, 0.714f, 1.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractEulerFromRs(rsMatrix);
	};
#endif
}

TEST_CASE("Euler angles from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	const auto euler = PonyEngine::Math::ExtractEulerFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.04f, 0.714f, 1.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractEulerFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Euler angles from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	const auto euler = PonyEngine::Math::ExtractEulerFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-0.04f, 0.714f, 1.034f), euler, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractEulerFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Axis-angle from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	const auto [axis, angle] = PonyEngine::Math::ExtractAxisAngleFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.267f, 0.535f, 0.802f), axis, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.25f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractAxisAngleFromRs(rsMatrix);
	};
#endif
}

TEST_CASE("Axis-angle from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	const auto [axis, angle] = PonyEngine::Math::ExtractAxisAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.267f, 0.535f, 0.802f), axis, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.25f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractAxisAngleFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Axis-angle from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	const auto [axis, angle] = PonyEngine::Math::ExtractAxisAngleFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(0.267f, 0.535f, 0.802f), axis, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.25f, angle, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractAxisAngleFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Scaling from rs matrix", "[Math][Transformations]")
{
	constexpr auto rsMatrix = PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f);
	const auto scaling = PonyEngine::Math::ExtractScalingFromRs(rsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f), scaling, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractScalingFromRs(rsMatrix);
	};
#endif
}

TEST_CASE("Scaling from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	const auto scaling = PonyEngine::Math::ExtractScalingFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f), scaling, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractScalingFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Scaling from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	const auto scaling = PonyEngine::Math::ExtractScalingFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(3.3f, 4.2f, 2.4f), scaling, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractScalingFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Rs matrix from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	constexpr auto rsMatrixC = PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f), rsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	const auto rsMatrix = PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Rs matrix from trs matrix compact", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	constexpr auto rsMatrixC = PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f), rsMatrixC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	const auto rsMatrix = PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x3<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f), rsMatrix, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractRsMatrixFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Tts matrix compact from trs matrix", "[Math][Transformations]")
{
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.f, -2.78489148f, 2.1459669f, 2.297652f, 0.f, 1.56952848f, 0.0955356f, 1.81313376f, 0.f, 2.f, -3.f, 5.f, 1.f);
	constexpr auto trsMatrixCompactC = PonyEngine::Math::ExtractTrsMatrixFromTrs(trsMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f), trsMatrixCompactC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	const auto trsMatrixCompact = PonyEngine::Math::ExtractTrsMatrixFromTrs(trsMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f), trsMatrixCompact, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractTrsMatrixFromTrs(trsMatrix);
	};
#endif
}

TEST_CASE("Fov from projection matrix", "[Math][Transformations]")
{
	constexpr auto perspectiveMatrix = PonyEngine::Math::Matrix4x4<float>(0.701f, 0.f, 0.f, 0.f, 0.f, 1.192f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, -0.2f, 0.f);
	const float fov = PonyEngine::Math::ExtractFov(perspectiveMatrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(80.f * PonyEngine::Math::DegToRad<float>, fov, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractFov(perspectiveMatrix);
	};
#endif
}

TEST_CASE("Width from projection matrix", "[Math][Transformations]")
{
	constexpr auto orthographicMatrix = PonyEngine::Math::Matrix4x4<float>(0.058f, 0.f, 0.f, 0.f, 0.f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.001f, 0.f, 0.f, 0.f, -0.0002f, 1.f);
	constexpr float width = PonyEngine::Math::ExtractWidth(orthographicMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(34.483f, width, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractWidth(orthographicMatrix);
	};
#endif
}

TEST_CASE("Height from projection matrix", "[Math][Transformations]")
{
	constexpr auto orthographicMatrix = PonyEngine::Math::Matrix4x4<float>(0.058f, 0.f, 0.f, 0.f, 0.f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.001f, 0.f, 0.f, 0.f, -0.0002f, 1.f);
	const float height = PonyEngine::Math::ExtractHeight(orthographicMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(20.f, height, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractHeight(orthographicMatrix);
	};
#endif
}

TEST_CASE("Aspect from projection matrix", "[Math][Transformations]")
{
	constexpr auto perspectiveMatrix = PonyEngine::Math::Matrix4x4<float>(0.701f, 0.f, 0.f, 0.f, 0.f, 1.192f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, -0.2f, 0.f);
	constexpr float aspect = PonyEngine::Math::ExtractAspect(perspectiveMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1.7f, aspect, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractAspect(perspectiveMatrix);
	};
#endif
}

TEST_CASE("Near plane from projection matrix", "[Math][Transformations]")
{
	constexpr auto perspectiveMatrix = PonyEngine::Math::Matrix4x4<float>(0.701f, 0.f, 0.f, 0.f, 0.f, 1.192f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, -0.2f, 0.f);
	constexpr float nearPlane = PonyEngine::Math::ExtractNearPlane(perspectiveMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(0.2f, nearPlane, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractNearPlane(perspectiveMatrix);
	};
#endif
}

TEST_CASE("Far plane from perspective matrix", "[Math][Transformations]")
{
	constexpr auto perspectiveMatrix = PonyEngine::Math::Matrix4x4<float>(0.701f, 0.f, 0.f, 0.f, 0.f, 1.192f, 0.f, 0.f, 0.f, 0.f, 1.00020003f, 1.f, 0.f, 0.f, -0.200040013f, 0.f);
	constexpr float farPlane = PonyEngine::Math::ExtractFarPlanePerspective(perspectiveMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1000.f, farPlane, PonyEngine::Math::Tolerance{.absolute = 0.1f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractFarPlanePerspective(perspectiveMatrix);
	};
#endif
}

TEST_CASE("Far plane from orthographic matrix", "[Math][Transformations]")
{
	constexpr auto orthographicMatrix = PonyEngine::Math::OrthographicMatrix(20.f, 1.7f, 0.2f, 1000.f);
	constexpr float farPlane = PonyEngine::Math::ExtractFarPlaneOrthographic(orthographicMatrix);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(1000.f, farPlane, PonyEngine::Math::Tolerance{.absolute = 0.1f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::ExtractFarPlaneOrthographic(orthographicMatrix);
	};
#endif
}

TEST_CASE("Rotate with angle", "[Math][Transformations]")
{
	constexpr PonyEngine::Math::Vector2<float> vector(-2.f, 3.f);
	constexpr float angle = 1.01f;
	const PonyEngine::Math::Vector2<float> rotated = PonyEngine::Math::Rotate(vector, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(-3.604f, -0.098f), rotated, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Rotate(PonyEngine::Math::Vector2<float>(4.6f, 8.1f), 1.2f);
	};
#endif
}

TEST_CASE("Rotate with Euler angles", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto euler = PonyEngine::Math::Vector3<float>(1.2f, -2.9f, -0.2f);
	const auto rotated = PonyEngine::Math::Rotate(vector, euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-7.168f, 6.18f, -3.521f), rotated, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Rotate(PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f), PonyEngine::Math::Vector3<float>(1.2f, -2.9f, -0.2f));
	};
#endif
}

TEST_CASE("Rotate with Euler axis-angle", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto axis = PonyEngine::Math::Vector3<float>(0.1513236f, -0.8183146f, 0.5544928f);
	constexpr float angle = 2.8305042f;
	const auto rotated = PonyEngine::Math::Rotate(vector, axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-7.168f, 6.18f, -3.521f), rotated, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::Rotate(PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f), PonyEngine::Math::Vector3<float>(0.1513236f, -0.8183146f, 0.5544928f), 2.8305042f);
	};
#endif
}

TEST_CASE("Transform point with transformation matrix", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.556f, -2.78489148f, 2.1459669f, 2.297652f, 0.326f, 1.56952848f, 0.0955356f, 1.81313376f, -0.005f, 2.f, -3.f, 5.f, 1.23f);
	constexpr auto transformed = PonyEngine::Math::TransformPoint(trsMatrix, vector);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-21.15f, 27.045f, 11.067f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformPoint(trsMatrix, vector);
	};
#endif
}

TEST_CASE("Transform point with transformation matrix with perspective division", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.556f, -2.78489148f, 2.1459669f, 2.297652f, 0.326f, 1.56952848f, 0.0955356f, 1.81313376f, -0.005f, 2.f, -3.f, 5.f, 1.23f);
	constexpr auto transformed = PonyEngine::Math::TransformPoint<true>(trsMatrix, vector);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-21.15f, 27.045f, 11.067f) / 6.4477f, transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformPoint<true>(trsMatrix, vector);
	};
#endif
}

TEST_CASE("Transform point with transformation matrix compact", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	constexpr auto transformed = PonyEngine::Math::TransformPoint(trsMatrix, vector);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-21.15f, 27.045f, 11.067f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformPoint(trsMatrix, vector);
	};
#endif
}

TEST_CASE("Transform direction with transformation matrix", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.556f, -2.78489148f, 2.1459669f, 2.297652f, 0.326f, 1.56952848f, 0.0955356f, 1.81313376f, -0.005f, 2.f, -3.f, 5.f, 1.23f);
	constexpr auto transformed = PonyEngine::Math::TransformDirection(trsMatrix, vector);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-23.15f, 30.045f, 6.067f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformDirection(trsMatrix, vector);
	};
#endif
}

TEST_CASE("Transform direction with transformation matrix compact", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	constexpr auto transformed = PonyEngine::Math::TransformDirection(trsMatrix, vector);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-23.15f, 30.045f, 6.067f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformDirection(trsMatrix, vector);
	};
#endif
}

TEST_CASE("Transform homogeneous with transformation matrix", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix4x4<float>(1.20195207f, 2.83368228f, -1.18977177f, 0.556f, -2.78489148f, 2.1459669f, 2.297652f, 0.326f, 1.56952848f, 0.0955356f, 1.81313376f, -0.005f, 2.f, -3.f, 5.f, 1.23f);
	constexpr auto transformed = PonyEngine::Math::TransformHomogeneous(trsMatrix, vector, 0.5f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector4<float>(-22.15f, 28.545f, 8.567f, 5.833f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformHomogeneous(trsMatrix, vector, 0.5f);
	};
#endif
}

TEST_CASE("Transform homogeneous with transformation matrix compact", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto trsMatrix = PonyEngine::Math::Matrix3x4<float>(1.20195207f, 2.83368228f, -1.18977177f, -2.78489148f, 2.1459669f, 2.297652f, 1.56952848f, 0.0955356f, 1.81313376f, 2.f, -3.f, 5.f);
	constexpr auto transformed = PonyEngine::Math::TransformHomogeneous(trsMatrix, vector, 0.5f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-22.15f, 28.545f, 8.567f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformHomogeneous(trsMatrix, vector, 0.5f);
	};
#endif
}

TEST_CASE("Create homogeneous with transformation matrix", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	constexpr auto homogeneousC = PonyEngine::Math::CreateHomogeneous(vector, 2.5f);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector4<float>(4.6f, 8.1f, -3.9f, 2.5f), homogeneousC, PonyEngine::Math::Tolerance{.absolute = 0.001f}));
	const auto homogeneous = PonyEngine::Math::CreateHomogeneous(vector, 2.5f);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector4<float>(4.6f, 8.1f, -3.9f, 2.5f), homogeneous, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::CreateHomogeneous(PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f), 2.5f);
	};
#endif
}

TEST_CASE("Transform world to local", "[Math][Transformations]")
{
	constexpr auto vector = PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f);
	const auto matrix = PonyEngine::Math::RotationMatrix(PonyEngine::Math::Vector3<float>(0.4f, 1.f, -2.f));
	const auto transformed = PonyEngine::Math::TransformTranspose(matrix, vector);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector3<float>(-9.808f, 1.854f, -1.53f), transformed, PonyEngine::Math::Tolerance{.absolute = 0.001f}));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::TransformTranspose(matrix, PonyEngine::Math::Vector3<float>(4.6f, 8.1f, -3.9f));
	};
#endif
}
