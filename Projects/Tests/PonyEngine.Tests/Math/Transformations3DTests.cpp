/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <numbers>;

import PonyEngine.Math;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math
{
	TEST_CLASS(Transformations3DTests)
	{
		TEST_METHOD(QuaternionFromRotationMatrixTest)
		{
			auto matrix = PonyEngine::Math::Matrix3x3<float>(0.83f, 0.482f, 0.281f, -0.436f, 0.245f, 0.866f, 0.348f, -0.841f, 0.413f);
			auto quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.541, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.021, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.291, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.789, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.105f, 0.403f, 0.909f, -0.932f, -0.36f, 0.052f, 0.348f, -0.841f, 0.413f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.459, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.288, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.685, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.487, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.888f, -0.436f, -0.141f, 0.299f, -0.318f, -0.9f, 0.348f, -0.841f, 0.413f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.064, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.538, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.227, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.57f, -0.16f, -0.806f, 0.744f, 0.516f, 0.424f, 0.348f, -0.841f, 0.413f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.4, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.365, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.286, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.791, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.261f, 0.482f, -0.837f, 0.957f, 0.245f, -0.157f, 0.129f, -0.841f, -0.525f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.505, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.713, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.339, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.978f, 0.206f, 0.007f, 0.099f, -0.499f, 0.861f, 0.181f, -0.841f, -0.509f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.864, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.088, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.054, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.492, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.763f, -0.206f, 0.612f, -0.62f, -0.499f, 0.605f, 0.181f, -0.841f, -0.509f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.832, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.248, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.238, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.434, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.906f, -0.344f, 0.246f, -0.382f, 0.417f, -0.824f, 0.181f, -0.841f, -0.509f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.216, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.841, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.495, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.019, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.913f, 0.399f, 0.09f, 0.068f, 0.365f, -0.929f, -0.403f, -0.841f, -0.36f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.144, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.812, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.545, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.152, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.378f, 0.511f, -0.772f, 0.833f, -0.175f, -0.524f, -0.403f, -0.841f, -0.36f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.538, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.625, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.546, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.147, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.837f, -0.498f, 0.227f, -0.37f, -0.21f, 0.905f, -0.403f, -0.841f, -0.36f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.776, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.28, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.057, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.563, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.338f, -0.455f, 0.824f, -0.817f, 0.292f, 0.497f, -0.466f, -0.841f, -0.273f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.574, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.554, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.156, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.583, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.727f, 0.298f, 0.618f, -0.661f, 0.546f, 0.515f, -0.184f, -0.783f, 0.594f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.383, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.237, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.283, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.847, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.259f, 0.621f, 0.739f, -0.948f, -0.018f, -0.317f, -0.184f, -0.783f, 0.594f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.203, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.402, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.684, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.574, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.216f, -0.557f, -0.802f, 0.959f, -0.276f, -0.067f, -0.184f, -0.783f, 0.594f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.341, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.294, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.722, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.525, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.69f, -0.533f, -0.489f, 0.7f, 0.32f, 0.639f, -0.184f, -0.783f, 0.594f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.441, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.095, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.382, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.807, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.936f, -0.35f, -0.041f, -0.041f, -0.225f, 0.974f, -0.35f, -0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.772, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.127, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.127, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.61, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.471f, -0.378f, 0.797f, -0.81f, 0.173f, 0.561f, -0.35f, -0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.617, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.481, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.181, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.596, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.921f, 0.378f, -0.097f, 0.173f, 0.173f, -0.97f, -0.35f, -0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.181, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.761, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.617, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.083, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.352f, 0.35f, -0.868f, 0.868f, -0.225f, -0.443f, -0.35f, -0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.524, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.581, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.581, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.223, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.548f, -0.371f, -0.75f, 0.746f, -0.189f, 0.639f, -0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.625, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.15, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.451, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.619, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.924f, -0.359f, 0.132f, -0.058f, 0.21f, 0.976f, -0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.621, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.168, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.099, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.759, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.504f, 0.359f, 0.786f, -0.777f, 0.21f, -0.594f, -0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.168, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.621, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.606, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.469, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.497f, 0.042f, -0.867f, 0.781f, -0.414f, -0.467f, -0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.431, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.477, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.722, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.256, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.871f, -0.287f, 0.398f, -0.313f, -0.302f, -0.901f, 0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.254, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.591, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.766, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.008, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.734f, -0.409f, -0.543f, 0.564f, 0.078f, -0.822f, 0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.061, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.64, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.676, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.36, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.89f, 0.409f, 0.201f, -0.253f, 0.078f, 0.964f, 0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.64, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.061, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.226, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.732, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.268f, 0.287f, 0.92f, -0.886f, -0.302f, 0.352f, 0.378f, -0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.591, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.254, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.549, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.534, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.464f, -0.392f, 0.795f, -0.824f, -0.139f, -0.549f, 0.326f, -0.909f, -0.259f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.483, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.629, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.58, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.186, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.944f, -0.329f, -0.033f, -0.055f, 0.255f, -0.965f, 0.326f, -0.909f, -0.259f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.123, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.784, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.598, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.114, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.182f, 0.329f, -0.927f, 0.928f, 0.255f, 0.273f, 0.326f, -0.909f, -0.259f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.545, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.577, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.276, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.543, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.879f, 0.392f, -0.271f, 0.348f, -0.139f, 0.927f, 0.326f, -0.909f, -0.259f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.754, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.245, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.018, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.609, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.517f, -0.388f, -0.763f, -0.781f, -0.151f, 0.606f, -0.35f, 0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.463, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.631, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.601, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.164, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.937f, -0.337f, 0.098f, 0.013f, 0.245f, 0.969f, -0.35f, 0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.104, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.776, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.606, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.144, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.301f, 0.336f, 0.892f, 0.887f, 0.245f, -0.391f, -0.35f, 0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.566, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.541, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.24, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.575, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.713f, 0.103f, -0.694f, -0.608f, -0.403f, -0.684f, -0.35f, 0.909f, -0.225f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.765, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.165, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.341, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.521, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, -0.395f, 0.072f, 0.134f, -0.131f, 0.982f, -0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.103, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.635, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.745, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.178, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.381f, -0.324f, 0.866f, 0.843f, 0.261f, 0.47f, -0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.214, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.606, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.569, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.513, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, 0.324f, 0.277f, 0.196f, 0.261f, -0.945f, -0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.606, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.214, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.042, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.765, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, 0.395f, -0.646f, -0.656f, -0.131f, -0.744f, -0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.635, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.103, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.403, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.651, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.653f, -0.395f, 0.646f, 0.656f, -0.131f, -0.744f, 0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.635, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.103, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.403, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.651, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.905f, -0.324f, -0.277f, -0.196f, 0.261f, -0.945f, 0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.606, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.214, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.042, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.765, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.382f, 0.324f, -0.866f, -0.843f, 0.261f, 0.47f, 0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.214, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.606, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.569, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.513, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.916f, 0.395f, -0.072f, -0.134f, -0.131f, 0.982f, 0.378f, 0.909f, 0.173f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.103, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.635, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.745, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.178, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.99f, -0.123f, -0.074f, -0.117f, -0.398f, -0.91f, 0.083f, 0.909f, -0.408f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.836, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.072, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.003, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.544, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.518f, -0.31f, -0.797f, -0.851f, 0.277f, 0.446f, 0.083f, 0.909f, -0.408f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.391, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.742, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.456, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.296, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.788f, 0.31f, 0.532f, 0.61f, 0.277f, 0.742f, 0.083f, 0.909f, -0.408f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.293, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.786, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.525, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.143, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.883f, 0.123f, 0.453f, 0.462f, -0.398f, -0.793f, 0.083f, 0.909f, -0.408f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.82, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.178, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.163, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.519, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.376f, 0.244f, -0.894f, -0.614f, 0.788f, -0.043f, 0.694f, 0.565f, 0.446f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.188, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.492, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.265, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.808, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.714f, 0.615f, 0.333f, -0.086f, -0.55f, 0.831f, 0.694f, 0.565f, 0.446f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.312, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.424, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.823, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.213, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.006f, -0.615f, 0.788f, 0.719f, -0.55f, -0.424f, 0.694f, 0.565f, 0.446f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.524, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.05, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.472, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.657f, -0.244f, -0.714f, -0.294f, 0.788f, -0.540f, 0.694f, 0.565f, 0.446f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.325, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.414, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.015, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.85, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.657f, 0.694f, -0.294f, 0.073f, 0.446f, 0.892f, 0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.245, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.782, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.466, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.334, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.294f, 0.75f, 0.592f, 0.592f, -0.343f, 0.729f, 0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.59, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.569, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.569, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.07, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.64f, -0.75f, 0.165f, -0.165f, -0.343f, -0.925f, 0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.763, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.3, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.3, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.488, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, -0.164f, -0.938f, -0.586f, 0.809f, 0.05f, 0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.239, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.784, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.196, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.538, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.269f, 0.736f, 0.622f, 0.604f, 0.374f, -0.704f, -0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.556, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.602, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.058, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.57, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.654f, 0.712f, -0.256f, 0.1f, -0.417f, -0.904f, -0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.777, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.261, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.324, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.473, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.233f, -0.712f, -0.662f, -0.618f, -0.417f, 0.666f, -0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.618, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.538, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.571, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.041, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.465f, -0.082f, 0.881f, 0.469f, 0.821f, 0.325f, -0.75f, 0.565f, -0.343f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.119, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.811, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.274, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.503, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.624f, 0.694f, -0.358f, -0.764f, 0.446f, -0.466f, -0.164f, 0.565f, 0.809f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.303, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.057, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.43, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.848, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.306f, 0.75f, -0.586f, -0.938f, -0.343f, 0.05f, -0.164f, 0.565f, 0.809f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.239, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.196, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.784, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.538, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-0.51f, -0.75f, 0.421f, 0.844f, -0.343f, 0.411f, -0.164f, 0.565f, 0.809f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.079, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.299, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.816, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.489, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.938f, -0.164f, 0.305f, 0.305f, 0.809f, -0.503f, -0.164f, 0.565f, 0.809f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.283, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.124, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.124, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.943, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>::Predefined::Identity;
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, -1.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(1., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);
		}

		TEST_METHOD(QuaternionFromEulerTest)
		{
			auto euler = PonyEngine::Math::Vector3<float>::Predefined::Zero;
			auto quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(1., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(1., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.549, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.027, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.297, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.781, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.495, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.239, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.635, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.543, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.071, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.545, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.802, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.234, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.2, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.512, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.591, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.59, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.611, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.614, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.26, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.427, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.83, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.246, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.024, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.758, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.418, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.339, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.368, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.465, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.73, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.474, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.161, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.29, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.816, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.498, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.051, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.843, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.196, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.226, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.446, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.866, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.011, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.113, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.487, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.458, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.735, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.349, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.358, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.362, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.459, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.427, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.69, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.191, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.553, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.811, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.014, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.449, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.375, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.702, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.406, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.558, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.175, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.038, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.81, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.806, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.187, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.085, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.555, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.278, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.779, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.421, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.371, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.084, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.823, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.498, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.26, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.648, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.515, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.487, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.279, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.364, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.366, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.724, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.457, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.505, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.109, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.006, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.856, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -2.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.464, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.226, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.199, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.833, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -0.9f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.06, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.513, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.808, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.283, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 1.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.161, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.491, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.736, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 2.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.377, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.353, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.436, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.737, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -2.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.514, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.045, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.259, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.816, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -1.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.43, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.286, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.619, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.592, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 0.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.771, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.301, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.383, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.41, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 2.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.163, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.811, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.552, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.101, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -2.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.496, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.662, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.293, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -0.3f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.825, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.06, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.245, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.505, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 1.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.5, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.659, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.541, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.149, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.123, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.818, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.547, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.128, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.462, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.686, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.316, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.464, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -1.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.735, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.381, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.055, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.559, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 0.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.068, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.512, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.853, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.074, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.394, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.334, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.399, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.758, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.516, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.02, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.218, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.828, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -0.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.262, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.445, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.815, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.264, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 0.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.305, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.416, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.784, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 2.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.515, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.032, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.134, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.846, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -2.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.425, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.293, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.321, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.794, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -0.6f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.017, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.516, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.159, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 0.68f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.822, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.097, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.145, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.542, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 2.68f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.362, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.744, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.415, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -2.68f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.007, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.827, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.523, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(-0.203, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -0.68f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.7, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.441, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.454, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.331, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.163, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.542, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.321, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.76, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.544, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.156, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.813, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.141, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.56, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.075, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.801, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.196, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.24, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.512, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.268, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.78, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.363, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.813, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.235, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.39, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.88, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.134, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.455, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.013, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.886, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.089, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.444, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.101, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.404, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.794, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.155, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.428, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.591, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.666, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.258, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.375, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.838, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.301, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.406, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.821, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.123, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.556, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.696, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.326, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.318, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.097, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.054, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.557, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.823, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(-0.111, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.001, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.883, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.455, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.066, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.09, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.888, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(quaternion.W()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f);
			quaternion = PonyEngine::Math::RotationQuaternion(euler);
			Assert::AreEqual(0.015, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.11, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.565, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.817, static_cast<double>(quaternion.W()), 0.001);
		}

		TEST_METHOD(QuaternionFromAngleAxisTest)
		{
			auto axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
			float angle = 0.f;
			auto quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, 1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, 1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(-1.f, 1.f, -1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(1.f, 1.f, -1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, 1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, 1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(-1.f, -1.f, -1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(1.f, -1.f, -1.f).Normalized();
			angle = 0.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(0.f, 0.f, -1.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.479, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(0.f, -1.f, 0.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(1.f, 0.f, 0.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-1.f, 0.f, 0.f);
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.479, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.284, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.309, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.232, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
			angle = 0.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.242, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.162, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.323, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.9, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
			angle = 1.1f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.312, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.156, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.39, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.853, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
			angle = 0.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.243, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.243, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.182, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.921, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
			angle = 1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.284, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.309, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.232, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
			angle = 0.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.242, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.162, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.323, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.9, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
			angle = 1.1f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.312, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.156, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.39, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.853, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
			angle = 0.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.243, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.243, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.182, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.921, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
			angle = 2.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.674, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.449, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.562, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.17, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
			angle = 3.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.682, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.455, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.568, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.071, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
			angle = 2.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.657, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.438, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.602, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
			angle = 2.7f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.538, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.658, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.219, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
			angle = 2.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.674, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.449, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.562, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.17, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
			angle = 3.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.682, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.455, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.568, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.071, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
			angle = 2.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.657, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.602, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
			angle = 2.7f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.538, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.658, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.219, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(12.f, 8.f, 10.f).Normalized();
			angle = -2.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.674, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.449, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.562, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.17, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, 10.f).Normalized();
			angle = -3.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.682, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.455, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.568, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.071, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, 8.f, -11.f).Normalized();
			angle = -2.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.657, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.438, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.602, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(9.f, 8.f, -11.f).Normalized();
			angle = -2.7f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.538, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.658, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.219, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(12.f, -8.f, 10.f).Normalized();
			angle = -2.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.674, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.449, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.562, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.17, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, 10.f).Normalized();
			angle = -3.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.682, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.455, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.568, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.071, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-12.f, -8.f, -11.f).Normalized();
			angle = -2.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.657, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.438, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.602, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(9.f, -8.f, -11.f).Normalized();
			angle = -2.7f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.538, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.479, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.658, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.219, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(1.1f, 1.2f, 0.9f).Normalized();
			angle = -1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.284, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.309, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.232, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-3.f, 2.f, 4.f).Normalized();
			angle = -0.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.242, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.162, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.323, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.9, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-4.f, 2.f, -5.f).Normalized();
			angle = -1.1f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.312, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.156, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.39, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.853, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(4.f, 4.f, -3.f).Normalized();
			angle = -0.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.243, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.243, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.921, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(1.1f, -1.2f, 0.9f).Normalized();
			angle = -1.f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.284, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.309, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.232, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.878, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-3.f, -2.f, 4.f).Normalized();
			angle = -0.9f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.242, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.162, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.323, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.9, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(-4.f, -2.f, -5.f).Normalized();
			angle = -1.1f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(0.312, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.156, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.39, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.853, static_cast<double>(quaternion.W()), 0.001);

			axis = PonyEngine::Math::Vector3<float>(4.f, -4.f, -3.f).Normalized();
			angle = -0.8f;
			quaternion = PonyEngine::Math::RotationQuaternion(axis, angle);
			Assert::AreEqual(-0.243, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.243, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.182, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.921, static_cast<double>(quaternion.W()), 0.001);
		}

		TEST_METHOD(QuaternionFromDirectionsTest)
		{
			auto from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
			auto to = from;
			auto quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			from = PonyEngine::Math::Vector3<float>(-3.f, 4.f, 2.3f).Normalized();
			to = from;
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::IsTrue(quaternion == PonyEngine::Math::Quaternion<float>::Predefined::Identity);

			from = PonyEngine::Math::Vector3<float>(0.f, 0.f, 1.f);
			to = -from;
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(-1., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 0.f, 1.f).Normalized();
			to = -from;
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(-0.707, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(0.f, 1.f, 0.f).Normalized();
			to = -from;
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(1., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
			to = -from;
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(0.981, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.196, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
			to = PonyEngine::Math::Vector3<float>(6.f, 5.f, 3.f).Normalized();
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(0.122, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.037, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(-0.305, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.944, static_cast<double>(quaternion.W()), 0.001);

			from = PonyEngine::Math::Vector3<float>(1.f, 5.f, 1.f).Normalized();
			to = PonyEngine::Math::Vector3<float>(-6.f, -5.f, 3.f).Normalized();
			quaternion = PonyEngine::Math::RotationQuaternion(from, to);
			Assert::AreEqual(0.545, static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(-0.245, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0.682, static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.422, static_cast<double>(quaternion.W()), 0.001);
		}

		TEST_METHOD(RotationMatrixFromQuaternionTest)
		{
			auto quaternion = PonyEngine::Math::Quaternion<float>(0.541f, 0.021f, 0.291f, 0.789f);
			auto matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.83, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.482, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.281, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.436, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.245, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.866, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.348, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.413, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.459f, -0.288f, 0.685f, 0.487f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.105, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.403, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.909, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.932, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.36, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.052, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.348, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.413, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.064f, -0.538f, 0.809f, -0.227f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.888, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.436, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.141, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.299, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.318, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.9, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.348, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.413, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.4f, 0.365f, -0.286f, 0.791f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.57, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.16, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.806, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.744, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.516, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.424, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.348, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.413, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.505f, 0.713f, -0.35f, 0.339f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.261, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.482, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.837, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.957, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.245, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.157, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.129, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.527, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.864f, 0.088f, 0.054f, 0.492f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.978, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.007, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.099, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.86, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.18, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.509, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.832f, -0.248f, 0.238f, 0.434f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.763, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.206, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.612, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.62, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.498, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.605, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.181, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.507, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.216f, 0.841f, -0.495f, -0.019f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.905, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.246, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.382, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.417, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.824, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.181, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.508, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.144f, 0.812f, -0.545f, -0.152f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.913, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.399, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.09, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.068, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.365, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.929, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.403, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.36, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.538f, 0.625f, -0.546f, 0.147f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.511, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.772, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.833, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.175, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.524, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.403, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.36, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.776f, -0.28f, -0.057f, 0.563f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.837, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.498, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.227, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.37, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.21, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.905, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.403, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.361, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.574f, -0.554f, 0.156f, 0.583f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.338, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.455, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.825, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.817, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.292, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.497, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.466, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.842, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.273, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.383f, -0.237f, 0.283f, 0.847f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.727, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.298, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.618, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.661, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.546, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.515, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.184, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.783, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.594, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.203f, -0.402f, 0.684f, 0.574f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.259, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.622, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.739, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.948, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.018, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.317, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.184, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.783, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.594, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.341f, 0.294f, -0.722f, 0.525f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.216, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.557, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.802, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.959, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.276, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.067, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.184, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.783, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.594, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.441f, 0.095f, -0.382f, 0.807f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.69, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.533, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.49, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.7, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.32, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.639, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.184, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.784, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.593, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.772f, -0.127f, -0.127f, 0.61f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.936, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.351, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.041, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.041, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.974, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.351, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.617f, -0.481f, 0.181f, 0.596f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.471, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.797, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.81, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.561, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.181f, 0.761f, -0.617f, -0.083f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.92, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.097, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.97, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.224, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.524f, -0.581f, 0.581f, -0.223f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.351, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.35, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.868, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.868, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.442, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.224, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.625f, 0.15f, -0.451f, 0.619f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.548, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.371, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.746, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.189, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.639, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.621f, -0.168f, -0.099f, 0.759f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.924, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.359, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.132, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.058, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.21, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.976, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.168f, 0.621f, -0.606f, -0.469f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.505, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.359, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.786, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.777, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.21, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.595, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.431f, -0.477f, 0.722f, -0.256f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.497, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.042, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.867, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.781, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.414, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.468, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.254f, -0.591f, 0.766f, 0.008f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.872, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.287, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.398, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.313, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.302, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.901, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.061f, -0.64f, 0.676f, -0.36f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.734, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.409, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.543, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.564, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.078, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.822, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.64f, 0.061f, 0.226f, 0.732f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.89, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.409, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.2, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.253, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.078, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.964, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.591f, -0.254f, 0.549f, 0.534f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.268, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.287, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.92, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.886, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.302, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.352, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.483f, 0.629f, -0.58f, -0.186f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.464, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.392, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.795, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.824, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.139, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.549, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.258, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.123f, 0.784f, -0.598f, 0.114f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.944, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.329, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.032, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.056, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.255, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.965, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.259, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.545f, 0.577f, -0.276f, 0.543f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.182, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.329, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.927, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.928, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.254, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.273, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.259, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.754f, 0.245f, 0.018f, 0.609f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.879, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.392, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.271, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.348, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.138, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.326, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.258, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.463f, 0.631f, 0.601f, 0.164f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.518, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.388, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.763, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.781, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.151, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.606, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.104f, 0.776f, 0.606f, -0.144f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.938, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.336, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.098, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.013, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.244, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.97, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.566f, -0.541f, -0.24f, 0.575f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.3, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.893, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.888, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.245, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.391, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.226, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.765f, 0.165f, 0.341f, 0.521f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.713, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.103, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.694, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.608, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.403, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.684, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.35, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.103f, 0.635f, 0.745f, -0.178f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.916, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.396, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.072, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.134, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.131, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.982, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.214f, -0.606f, -0.569f, 0.513f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.381, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.324, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.866, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.843, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.261, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.47, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.606f, -0.214f, 0.042f, 0.765f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.905, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.324, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.277, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.196, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.261, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.945, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.635f, 0.103f, 0.403f, 0.651f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.653, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.394, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.646, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.656, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.131, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.744, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.635f, -0.103f, -0.403f, 0.651f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.653, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.394, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.646, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.656, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.131, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.744, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.606f, 0.214f, -0.042f, 0.765f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.905, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.324, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.277, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.196, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.261, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.945, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.606f, 0.214f, -0.042f, 0.765f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.905, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.324, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.277, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.196, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.261, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.945, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.378, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.103f, 0.635f, 0.745f, 0.178f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.916, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.396, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.072, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.134, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.131, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.982, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.379, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.173, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.836f, 0.072f, -0.003f, 0.544f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.99, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.123, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.074, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.117, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.398, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.91, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.083, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.91, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.408, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.391f, 0.742f, 0.456f, 0.296f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.517, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.31, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.796, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.851, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.278, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.083, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.407, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.293f, 0.786f, 0.525f, -0.143f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.787, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.31, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.532, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.61, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.277, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.742, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.083, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.407, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.82f, -0.178f, -0.163f, 0.519f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.883, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.123, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.453, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.462, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.398, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.793, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.083, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.909, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.408, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.188f, 0.492f, 0.265f, 0.808f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.376, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.244, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.894, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.614, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.788, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.043, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.695, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.312f, 0.424f, 0.823f, 0.213f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.714, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.615, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.333, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.086, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.55, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.831, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.695, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.524f, 0.05f, 0.707f, -0.472f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.005, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.615, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.788, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.719, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.549, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.424, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.694, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.325f, 0.414f, 0.015f, 0.85f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.657, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.244, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.714, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.294, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.788, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.54, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.694, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.245f, 0.782f, 0.466f, 0.334f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.657, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.694, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.294, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.072, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.892, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.59f, 0.569f, 0.569f, 0.07f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.295, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.751, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.592, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.592, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.73, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.751, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.763f, -0.3f, 0.3f, -0.488f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.64, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.165, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.165, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.925, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.751, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.239f, 0.784f, 0.196f, 0.538f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.306, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.938, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.05, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.556f, -0.602f, 0.058f, 0.57f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.269, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.736, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.622, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.604, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.375, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.704, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.777f, 0.261f, -0.324f, -0.473f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.654, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.712, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.256, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.417, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.904, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.618f, -0.538f, -0.571f, 0.041f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.231, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.712, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.662, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.618, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.416, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.666, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.564, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.119f, -0.811f, -0.274f, 0.503f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.465, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.082, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.881, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.469, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.821, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.325, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.564, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.303f, 0.057f, 0.43f, 0.848f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.624, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.694, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.358, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.764, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.446, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.465, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.563, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.239f, 0.196f, 0.784f, 0.538f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.306, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.938, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.343, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.05, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.564, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.079f, 0.299f, 0.816f, -0.489f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-0.51, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.75, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.421, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.845, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.411, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.283f, -0.124f, -0.124f, 0.943f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0.938, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.305, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.305, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.503, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.164, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.565, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.809, static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>::Predefined::Identity;
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::IsTrue(matrix == PonyEngine::Math::Matrix3x3<float>::Predefined::Identity);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 0.707f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, 1.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.f, -0.707f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			matrix = PonyEngine::Math::Matrix3x3<float>(0.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f);
			quaternion = PonyEngine::Math::RotationQuaternion(matrix);
			Assert::AreEqual(0., static_cast<double>(quaternion.X()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.Y()), 0.001);
			Assert::AreEqual(0., static_cast<double>(quaternion.Z()), 0.001);
			Assert::AreEqual(0.707, static_cast<double>(quaternion.W()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 0.707f, 0.f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, 1.f, 0.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(-1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.f, -0.707f, 0.f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(0.707f, 0.f, 0.f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(1.f, 0.f, 0.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M22()), 0.001);

			quaternion = PonyEngine::Math::Quaternion<float>(-0.707f, 0.f, 0.f, 0.707f);
			matrix = PonyEngine::Math::RotationMatrix(quaternion);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);
		}

		TEST_METHOD(RotationMatrixFromEulerTest)
		{
			auto euler = PonyEngine::Math::Vector3<float>::Predefined::Zero;
			auto matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::IsTrue(PonyEngine::Math::AreAlmostEqual(matrix, PonyEngine::Math::Matrix3x3<float>::Predefined::Identity));

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float> / 2.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, std::numbers::pi_v<float>);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, 0.f, -std::numbers::pi_v<float> / 2.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float> / 2.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, std::numbers::pi_v<float>, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(0.f, -std::numbers::pi_v<float> / 2.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(std::numbers::pi_v<float>, 0.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-std::numbers::pi_v<float> / 2.f, 0.f, 0.f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(1., static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(1., static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0., static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 1.15f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.822, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.493, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.284, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.434, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.221, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.874, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.368, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, 2.15f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.08, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.452, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.888, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.926, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.296, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.233, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.368, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -2.15f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.881, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.452, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.142, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.298, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.296, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.907, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.368, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 0.75f, -1.15f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.493, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.84, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.902, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.221, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.371, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.368, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 1.35f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.111, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.527, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.842, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.972, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.118, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.202, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, 2.35f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.878, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.384, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.285, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.432, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.38, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.818, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -2.35f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.421, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.384, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.822, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.883, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.38, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.275, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, 2.75f, -1.35f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.516, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.527, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.675, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.832, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.118, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.543, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.826, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.423, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.372, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.524, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.782, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, 2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.821, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.129, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.557, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.533, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.525, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.664, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.974, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.129, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.184, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.091, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.525, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.846, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.f, -2.75f, -0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.323, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.423, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.846, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.924, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.185, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.206, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.841, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.499, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 0.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.214, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.256, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.943, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.921, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.374, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.107, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.325, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.891, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.316, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, 2.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.927, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.234, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.295, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.188, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.389, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.902, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.325, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.891, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.316, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -2.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.267, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.234, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.935, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.907, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.389, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.162, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.325, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.891, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.316, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(1.1f, -0.8f, -0.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.936, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.256, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.241, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.134, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.374, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.918, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.325, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.891, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.316, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.916, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.395, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.071, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.207, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.314, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, 2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.57, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.121, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.813, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.746, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.49, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.45, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.851, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.511, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.396, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.49, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.776, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 0.75f, -0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.006, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.918, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.939, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.314, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.141, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.316, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.395, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.862, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.929, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.313, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.197, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, 2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.976, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.121, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.18, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.099, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.49, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.866, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -2.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.819, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.121, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.561, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.541, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.49, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.683, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, 2.75f, -0.9f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.833, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.395, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.388, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.519, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.314, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.795, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 1.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.565, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.486, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.667, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.802, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.135, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.581, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, 2.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.37, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.376, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.849, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.909, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.247, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -2.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.862, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.376, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.341, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.47, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.816, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -2.75f, -1.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.07, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.486, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.871, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.979, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.135, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.154, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 0.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.525, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.149, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.838, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.778, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.482, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.402, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, 2.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.926, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.376, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.017, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.154, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.929, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -2.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.049, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.376, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.925, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.938, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.336, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.087, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(2.1f, -0.75f, -0.3f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.873, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.149, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.465, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.346, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.482, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.805, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(-0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 1.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.455, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.498, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.738, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.821, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.086, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.564, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, 2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.937, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.341, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.076, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.06, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.372, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.926, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.142, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.341, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.929, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.928, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.372, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.005, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 0.75f, -1.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.704, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.498, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.507, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.621, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.086, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.779, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 0.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.98, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.197, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.041, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.056, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.465, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.884, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, 2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.459, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.341, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.82, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.867, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.372, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.331, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.904, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.341, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.257, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.381, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.372, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.846, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, 2.75f, -0.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.723, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.197, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.662, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.663, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.465, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.586, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 0.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.577, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.285, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.766, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.794, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.417, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.443, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, 2.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.962, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.26, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.084, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.194, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.433, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.88, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -2.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.622, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.26, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.738, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.759, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.433, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.487, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -2.75f, -0.6f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.949, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.285, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.136, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.25, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.417, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.874, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.193, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.467, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 0.68f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.939, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.317, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.133, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.003, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.393, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.92, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, 2.68f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.393, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.225, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.892, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.853, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.452, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.262, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -2.68f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.917, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.225, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.329, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.201, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.452, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.869, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-2.1f, -0.75f, -0.68f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.199, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.317, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.918, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.393, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.063, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.344, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.863, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 0.73f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.208, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.664, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.719, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.311, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.742, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.595, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, 2.73f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.369, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.398, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.84, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.06, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.912, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.406, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -2.73f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.295, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.398, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.869, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.23, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.912, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.34, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 1.2f, -0.73f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.332, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.664, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.67, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.172, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.741, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.649, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 0.89f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.433, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.773, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.463, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.407, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.626, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.665, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, 2.89f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.55, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.248, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.798, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.225, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.964, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.144, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -2.89f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.59, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.248, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.768, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.068, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.964, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.258, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, 2.2f, -0.89f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.308, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.773, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.555, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.508, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.626, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.591, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);
			
			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 1.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.02, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.981, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.195, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.594, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.169, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.787, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, 2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.488, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.672, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.556, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.338, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.734, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.589, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -2.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.379, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.672, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.636, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.457, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.734, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.503, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -2.2f, -1.4f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.18, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.981, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.08, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.566, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.169, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.807, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 1.2f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.374, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.927, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.019, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.906, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.221, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.198, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.975, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, 2.2f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.561, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(0.804, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.196, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(-0.103, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.198, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.975, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -2.2f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(-0.593, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.804, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(-0.038, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.781, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(-0.586, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.218, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.198, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.975, static_cast<double>(matrix.M22()), 0.001);

			euler = PonyEngine::Math::Vector3<float>(-0.1f, -0.2f, -1.2f);
			matrix = PonyEngine::Math::RotationMatrix(euler);
			Assert::AreEqual(0.337, static_cast<double>(matrix.M00()), 0.001);
			Assert::AreEqual(-0.927, static_cast<double>(matrix.M10()), 0.001);
			Assert::AreEqual(0.163, static_cast<double>(matrix.M20()), 0.001);
			Assert::AreEqual(0.921, static_cast<double>(matrix.M01()), 0.001);
			Assert::AreEqual(0.361, static_cast<double>(matrix.M11()), 0.001);
			Assert::AreEqual(0.15, static_cast<double>(matrix.M21()), 0.001);
			Assert::AreEqual(-0.198, static_cast<double>(matrix.M02()), 0.001);
			Assert::AreEqual(0.1, static_cast<double>(matrix.M12()), 0.001);
			Assert::AreEqual(0.975, static_cast<double>(matrix.M22()), 0.001);
		}
	};
}
