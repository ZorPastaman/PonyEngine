/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Hierarchy.Impl:Transform3DDeserializer;

import std;

import PonyEngine.Math;
import PonyEngine.Resource.World.Ext;
import PonyEngine.World.Hierarchy;

export namespace PonyEngine::Resource::World::Hierarchy
{
	/// @brief Transform 3D deserializer.
	class Transform3DDeserializer final : public IInlineComponentDeserializer
	{
	public:
		[[nodiscard("Pure constructor")]]
		Transform3DDeserializer() noexcept = default;
		Transform3DDeserializer(const Transform3DDeserializer&) = delete;
		Transform3DDeserializer(Transform3DDeserializer&&) = delete;

		~Transform3DDeserializer() noexcept = default;

		virtual void Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output) override;

		Transform3DDeserializer& operator =(const Transform3DDeserializer&) = delete;
		Transform3DDeserializer& operator =(Transform3DDeserializer&&) = delete;

	private:
		/// @brief Input transform.
		struct InputTransform final
		{
			Math::Vector3<double> position; ///< Position.
			Math::Vector3<float> rotation; ///< Rotation in radians in Euler angles.
			Math::Vector3<float> scale; ///< Scale.
		};

		static constexpr std::size_t InputComponentSize = sizeof(double) * 3uz + sizeof(float) * 6uz; ///< Transform 3D input data size.
		static_assert(sizeof(InputTransform) == InputComponentSize, "Invalid input transform");
	};
}

namespace PonyEngine::Resource::World::Hierarchy
{
	void Transform3DDeserializer::Deserialize(const std::size_t entityCount, const std::span<const std::byte> input, const std::span<std::byte> output)
	{
		if (InputComponentSize * entityCount != input.size()) [[unlikely]]
		{
			throw std::runtime_error("Invalid component table input");
		}

		const std::byte* inputData = input.data();
		std::byte* outputData = output.data();
		for (std::size_t i = 0uz; i < entityCount; ++i, inputData += InputComponentSize, outputData += sizeof(PonyEngine::World::Hierarchy::LocalTransform3D))
		{
			InputTransform inputTransform;
			std::memcpy(&inputTransform, inputData, InputComponentSize);
			const auto outputTransform = PonyEngine::World::Hierarchy::LocalTransform3D(inputTransform.position, 
				Math::RotationQuaternion(inputTransform.rotation), inputTransform.scale);
			std::memcpy(outputData, &outputTransform, sizeof(PonyEngine::World::Hierarchy::LocalTransform3D));
		}
	}
}
