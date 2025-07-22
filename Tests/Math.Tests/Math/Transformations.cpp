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
	REQUIRE(PonyEngine::Math::AreAlmostEqual(1.065f, angle, 0.001f));

	matrix = PonyEngine::Math::Matrix2x2<float>(-0.545f, 0.839f, -0.839f, -0.545f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(2.147f, angle, 0.001f));

	matrix = PonyEngine::Math::Matrix2x2<float>(-0.788f, -0.616f, 0.616f, -0.788f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-2.478f, angle, 0.001f));

	matrix = PonyEngine::Math::Matrix2x2<float>(0.766f, -0.643f, 0.643f, 0.766f);
	angle = PonyEngine::Math::RotationAngle(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(-0.698f, angle, 0.001f));

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
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.541f, 0.021f, 0.291f, 0.789f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.105f, 0.403f, 0.909f, -0.932f, -0.36f, 0.052f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.459f, -0.288f, 0.685f, 0.487f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.888f, -0.436f, -0.141f, 0.299f, -0.318f, -0.9f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.064f, -0.538f, 0.809f, -0.227f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.57f, -0.16f, -0.806f, 0.744f, 0.516f, 0.424f, 0.348f, -0.841f, 0.413f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.4f, 0.365f, -0.286f, 0.791f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.261f, 0.482f, -0.837f, 0.957f, 0.245f, -0.157f, 0.129f, -0.841f, -0.525f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.505f, 0.713f, -0.35f, 0.339f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.978f, 0.206f, 0.007f, 0.099f, -0.499f, 0.861f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.864f, 0.088f, 0.054f, 0.492f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.763f, -0.206f, 0.612f, -0.62f, -0.499f, 0.605f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.832f, -0.248f, 0.238f, 0.434f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.906f, -0.344f, 0.246f, -0.382f, 0.417f, -0.824f, 0.181f, -0.841f, -0.509f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.216f, 0.841f, -0.495f, -0.019f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.913f, 0.399f, 0.09f, 0.068f, 0.365f, -0.929f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.144f, 0.812f, -0.545f, -0.152f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.378f, 0.511f, -0.772f, 0.833f, -0.175f, -0.524f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, 0.625f, -0.546f, 0.147f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.837f, -0.498f, 0.227f, -0.37f, -0.21f, 0.905f, -0.403f, -0.841f, -0.36f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.776f, -0.28f, -0.057f, 0.563f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.338f, -0.455f, 0.824f, -0.817f, 0.292f, 0.497f, -0.466f, -0.841f, -0.273f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.574f, -0.554f, 0.156f, 0.583f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.727f, 0.298f, 0.618f, -0.661f, 0.546f, 0.515f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.383f, -0.237f, 0.283f, 0.847f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.259f, 0.621f, 0.739f, -0.948f, -0.018f, -0.317f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.203f, -0.402f, 0.684f, 0.574f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.216f, -0.557f, -0.802f, 0.959f, -0.276f, -0.067f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.341f, 0.294f, -0.722f, 0.525f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.69f, -0.533f, -0.489f, 0.7f, 0.32f, 0.639f, -0.184f, -0.783f, 0.594f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.441f, 0.095f, -0.382f, 0.807f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.936f, -0.35f, -0.041f, -0.041f, -0.225f, 0.974f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.772f, -0.127f, -0.127f, 0.61f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.471f, -0.378f, 0.797f, -0.81f, 0.173f, 0.561f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.617f, -0.481f, 0.181f, 0.596f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.921f, 0.378f, -0.097f, 0.173f, 0.173f, -0.97f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.181f, 0.761f, -0.617f, -0.083f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.352f, 0.35f, -0.868f, 0.868f, -0.225f, -0.443f, -0.35f, -0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.524f, -0.581f, 0.581f, -0.223f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.548f, -0.371f, -0.75f, 0.746f, -0.189f, 0.639f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.625f, 0.15f, -0.451f, 0.619f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.924f, -0.359f, 0.132f, -0.058f, 0.21f, 0.976f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.621f, -0.168f, -0.099f, 0.759f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.504f, 0.359f, 0.786f, -0.777f, 0.21f, -0.594f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.168f, 0.621f, -0.606f, -0.469f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.497f, 0.042f, -0.867f, 0.781f, -0.414f, -0.467f, -0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.431f, -0.477f, 0.722f, -0.256f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.871f, -0.287f, 0.398f, -0.313f, -0.302f, -0.901f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.254f, -0.591f, 0.766f, 0.008f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.734f, -0.409f, -0.543f, 0.564f, 0.078f, -0.822f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.061f, -0.64f, 0.676f, -0.36f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.89f, 0.409f, 0.201f, -0.253f, 0.078f, 0.964f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.64f, 0.061f, 0.226f, 0.732f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.268f, 0.287f, 0.92f, -0.886f, -0.302f, 0.352f, 0.378f, -0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.591f, -0.254f, 0.549f, 0.534f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.464f, -0.392f, 0.795f, -0.824f, -0.139f, -0.549f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.483f, 0.629f, -0.58f, -0.186f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.944f, -0.329f, -0.033f, -0.055f, 0.255f, -0.965f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.123f, 0.784f, -0.598f, 0.114f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.182f, 0.329f, -0.927f, 0.928f, 0.255f, 0.273f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.545f, 0.577f, -0.276f, 0.543f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.879f, 0.392f, -0.271f, 0.348f, -0.139f, 0.927f, 0.326f, -0.909f, -0.259f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.754f, 0.245f, 0.018f, 0.609f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.517f, -0.388f, -0.763f, -0.781f, -0.151f, 0.606f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.463f, 0.631f, 0.601f, 0.164f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.337f, 0.098f, 0.013f, 0.245f, 0.969f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.104f, 0.776f, 0.606f, -0.144f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.301f, 0.336f, 0.892f, 0.887f, 0.245f, -0.391f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.566f, -0.541f, -0.24f, 0.575f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.713f, 0.103f, -0.694f, -0.608f, -0.403f, -0.684f, -0.35f, 0.909f, -0.225f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.765f, 0.165f, 0.341f, 0.521f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, -0.395f, 0.072f, 0.134f, -0.131f, 0.982f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.103f, 0.635f, 0.745f, -0.178f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.381f, -0.324f, 0.866f, 0.843f, 0.261f, 0.47f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.214f, -0.606f, -0.569f, 0.513f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, 0.324f, 0.277f, 0.196f, 0.261f, -0.945f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.606f, -0.214f, 0.042f, 0.765f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, 0.395f, -0.646f, -0.656f, -0.131f, -0.744f, -0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.635f, 0.103f, 0.403f, 0.651f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, -0.395f, 0.646f, 0.656f, -0.131f, -0.744f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.635f, -0.103f, -0.403f, 0.651f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, -0.324f, -0.277f, -0.196f, 0.261f, -0.945f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.606f, 0.214f, -0.042f, 0.765f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.382f, 0.324f, -0.866f, -0.843f, 0.261f, 0.47f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.214f, 0.606f, 0.569f, 0.513f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, 0.395f, -0.072f, -0.134f, -0.131f, 0.982f, 0.378f, 0.909f, 0.173f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.103f, 0.635f, 0.745f, 0.178f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.99f, -0.123f, -0.074f, -0.117f, -0.398f, -0.91f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.836f, 0.072f, -0.003f, 0.544f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.518f, -0.31f, -0.797f, -0.851f, 0.277f, 0.446f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.391f, 0.742f, 0.456f, 0.296f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.788f, 0.31f, 0.532f, 0.61f, 0.277f, 0.742f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.293f, 0.786f, 0.525f, -0.143f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.883f, 0.123f, 0.453f, 0.462f, -0.398f, -0.793f, 0.083f, 0.909f, -0.408f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.82f, -0.178f, -0.163f, 0.519f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.376f, 0.244f, -0.894f, -0.614f, 0.788f, -0.043f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.188f, 0.492f, 0.265f, 0.808f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.714f, 0.615f, 0.333f, -0.086f, -0.55f, 0.831f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, 0.424f, 0.823f, 0.213f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.006f, -0.615f, 0.788f, 0.719f, -0.55f, -0.424f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.524f, 0.05f, 0.707f, -0.472f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.657f, -0.244f, -0.714f, -0.294f, 0.788f, -0.540f, 0.694f, 0.565f, 0.446f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.325f, 0.414f, 0.015f, 0.85f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.657f, 0.694f, -0.294f, 0.073f, 0.446f, 0.892f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.245f, 0.782f, 0.466f, 0.334f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.294f, 0.75f, 0.592f, 0.592f, -0.343f, 0.729f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.59f, 0.569f, 0.569f, 0.07f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.64f, -0.75f, 0.165f, -0.165f, -0.343f, -0.925f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.763f, -0.3f, 0.3f, -0.488f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, -0.164f, -0.938f, -0.586f, 0.809f, 0.05f, 0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.239f, 0.784f, 0.196f, 0.538f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.269f, 0.736f, 0.622f, 0.604f, 0.374f, -0.704f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.556f, -0.602f, 0.058f, 0.57f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.654f, 0.712f, -0.256f, 0.1f, -0.417f, -0.904f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.777f, 0.261f, -0.324f, -0.473f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.233f, -0.712f, -0.662f, -0.618f, -0.417f, 0.666f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.618f, -0.538f, -0.571f, 0.041f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.465f, -0.082f, 0.881f, 0.469f, 0.821f, 0.325f, -0.75f, 0.565f, -0.343f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.119f, -0.811f, -0.274f, 0.503f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.624f, 0.694f, -0.358f, -0.764f, 0.446f, -0.466f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.303f, 0.057f, 0.43f, 0.848f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, 0.75f, -0.586f, -0.938f, -0.343f, 0.05f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.239f, 0.196f, 0.784f, 0.538f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-0.51f, -0.75f, 0.421f, 0.844f, -0.343f, 0.411f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.079f, 0.299f, 0.816f, -0.489f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.938f, -0.164f, 0.305f, 0.305f, 0.809f, -0.503f, -0.164f, 0.565f, 0.809f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.283f, -0.124f, -0.124f, 0.943f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>::Identity();
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(quaternion.IsIdentity());
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));

	matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(matrix);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));

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
	REQUIRE(quaternion.IsIdentity());
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.549f, 0.027f, 0.297f, 0.781f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.495f, -0.239f, 0.635f, 0.543f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.071f, 0.545f, -0.802f, 0.234f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.2f, 0.512f, -0.591f, 0.59f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.611f, 0.614f, -0.26f, 0.427f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.83f, 0.246f, -0.024f, 0.5f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.758f, 0.418f, -0.339f, -0.368f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.465f, 0.73f, -0.474f, -0.161f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.29f, -0.816f, 0.498f, -0.051f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.843f, -0.196f, 0.226f, -0.446f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.866f, -0.011f, -0.113f, 0.487f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.458f, -0.735f, 0.349f, 0.358f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.362f, -0.459f, 0.427f, 0.69f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.191f, -0.553f, 0.811f, 0.014f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.449f, 0.375f, -0.702f, 0.406f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.558f, -0.175f, -0.038f, 0.81f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.806f, -0.187f, -0.085f, 0.555f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.278f, -0.779f, 0.421f, 0.371f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.084f, 0.823f, -0.498f, -0.26f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.648f, 0.515f, -0.487f, 0.279f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.364f, 0.366f, -0.724f, 0.457f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.505f, -0.109f, -0.006f, 0.856f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -2.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.464f, 0.226f, -0.199f, -0.833f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -0.9f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.06f, 0.513f, -0.808f, -0.283f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 1.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.161f, -0.491f, 0.736f, -0.438f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.377f, -0.353f, 0.436f, -0.737f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.514f, -0.045f, 0.259f, 0.816f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -1.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.43f, -0.286f, 0.619f, 0.592f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 0.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.771f, -0.301f, 0.383f, 0.41f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.163f, -0.811f, 0.552f, -0.101f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -2.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.496f, 0.662f, -0.293f, 0.479f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -0.3f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.825f, -0.06f, 0.245f, 0.505f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.5f, 0.659f, 0.541f, 0.149f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.123f, 0.818f, 0.547f, -0.128f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.462f, -0.686f, -0.316f, 0.464f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.735f, -0.381f, -0.055f, 0.559f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 0.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);

	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.394f, 0.334f, 0.399f, -0.758f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.516f, 0.02f, 0.218f, 0.828f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -0.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.262f, 0.445f, 0.815f, 0.264f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.305f, -0.416f, -0.784f, 0.344f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.515f, 0.032f, -0.134f, 0.846f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -2.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.425f, -0.293f, -0.321f, -0.794f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -0.6f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.017f, -0.516f, -0.841f, -0.159f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 0.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.822f, 0.097f, -0.145f, 0.542f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 2.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.362f, 0.744f, 0.378f, 0.415f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -2.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.007f, -0.827f, -0.523f, -0.203f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -0.68f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.7f, -0.441f, -0.454f, 0.331f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.163f, 0.542f, 0.321f, 0.76f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.544f, 0.156f, 0.813f, 0.141f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.56f, 0.075f, -0.801f, 0.196f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.24f, 0.512f, -0.268f, 0.78f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.363f, 0.813f, 0.235f, 0.39f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.88f, 0.134f, 0.455f, 0.013f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.886f, 0.089f, -0.444f, 0.101f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.404f, 0.794f, -0.155f, 0.428f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.591f, -0.666f, 0.258f, 0.375f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.838f, -0.301f, 0.406f, 0.206f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.821f, -0.344f, -0.438f, 0.123f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.556f, -0.696f, -0.326f, 0.318f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.097f, -0.054f, 0.557f, 0.823f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.111f, -0.001f, 0.883f, 0.455f).Normalized(), quaternion, 0.001f));
	
	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.066f, -0.09f, -0.888f, 0.446f).Normalized(), quaternion, 0.001f));

	euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f);
	quaternion = PonyEngine::Math::RotationQuaternion(euler);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.015f, -0.11f, -0.565f, 0.817f).Normalized(), quaternion, 0.001f));

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
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -1.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -1.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-1.f, 0.f, 0.f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, 0.577f, 0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, 0.577f, 0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, 0.577f, -0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, 0.577f, -0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, -0.577f, 0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, -0.577f, 0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.577f, -0.577f, -0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = std::numbers::pi_v<float>;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.577f, -0.577f, -0.577f, 0.f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, -0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, -0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
	angle = -std::numbers::pi_v<float> / 2.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.408f, 0.408f, 0.408f, 0.707f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.479f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.479f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, 0.479f, 0.f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.f, -0.479f, 0.f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.479f, 0.f, 0.f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.479f, 0.f, 0.f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.284f, 0.309f, 0.232f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = 0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.242f, 0.162f, 0.323f, 0.9f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = 1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.312f, 0.156f, -0.39f, 0.853f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = 0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.243f, 0.243f, -0.182f, 0.921f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = 1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.284f, -0.309f, 0.232f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = 0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.242f, -0.162f, 0.323f, 0.9f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = 1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.312f, -0.156f, -0.39f, 0.853f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = 0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.243f, -0.243f, -0.182f, 0.921f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = 2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.674f, 0.449f, 0.562f, 0.17f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = 3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.682f, 0.455f,  0.568f, 0.071f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = 2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.657f, 0.438f, -0.602f, 0.121f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = 2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, 0.479f, -0.658f, 0.219f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = 2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.674f, -0.449f, 0.562f, 0.17f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = 3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.682f, -0.455f, 0.568f, 0.071f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = 2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.657f, -0.438f, -0.602f, 0.121f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = 2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.538f, -0.479f, -0.658f, 0.219f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
	angle = -2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.674f, -0.449f, -0.562f, 0.17f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
	angle = -3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.682f, -0.455f, -0.568f, 0.071f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
	angle = -2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.657f, -0.438f, 0.602f, 0.121f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
	angle = -2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.538f, -0.479f, 0.658f, 0.219f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
	angle = -2.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.674f, 0.449f, -0.562f, 0.17f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
	angle = -3.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.682f, 0.455f, -0.568f, 0.071f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
	angle = -2.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.657f, 0.438f, 0.602f, 0.121f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
	angle = -2.7f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.538f, 0.479f, 0.658f, 0.219f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
	angle = -1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.284f, -0.309f, -0.232f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
	angle = -0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.242f, -0.162f, -0.323f, 0.9f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
	angle = -1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, -0.156f, 0.39f, 0.853f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
	angle = -0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.243f, -0.243f, 0.182f, 0.921f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
	angle = -1.f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.284f, 0.309f, -0.232f, 0.878f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
	angle = -0.9f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.242f, 0.162f, -0.323f, 0.9f).Normalized(), quaternion, 0.001f));
	
	axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
	angle = -1.1f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(0.312f, 0.156f, 0.39f, 0.853f).Normalized(), quaternion, 0.001f));

	axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
	angle = -0.8f;
	quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
	REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Quaternion<float>(-0.243f, 0.243f, 0.182f, 0.921f).Normalized(), quaternion, 0.001f));

#if PONY_ENGINE_TESTING_BENCHMARK
	BENCHMARK("Bench")
	{
		return PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f), 2.9f);
	};
#endif
}
