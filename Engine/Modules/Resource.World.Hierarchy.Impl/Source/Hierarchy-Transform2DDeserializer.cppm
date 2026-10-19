/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Hierarchy.Impl:Transform2DDeserializer;

import std;

import PonyEngine.Math;
import PonyEngine.Resource.World.Ext;
import PonyEngine.World.Hierarchy;

export namespace PonyEngine::Resource::World::Hierarchy
{
	class Transform2DDeserializer final : public IInlineComponentDeserializer
	{
	public:
		[[nodiscard("Pure constructor")]]
		Transform2DDeserializer() noexcept = default;
		Transform2DDeserializer(const Transform2DDeserializer&) = delete;
		Transform2DDeserializer(Transform2DDeserializer&&) = delete;

		~Transform2DDeserializer() noexcept = default;

		virtual void Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output) override;

		Transform2DDeserializer& operator =(const Transform2DDeserializer&) = delete;
		Transform2DDeserializer& operator =(Transform2DDeserializer&&) = delete;

	private:
		static constexpr std::size_t InputComponentSize = sizeof(double) * 2uz + sizeof(float) * 3uz;

		template<typename T>
		T Read(const std::byte*& input) noexcept;
	};
}

namespace PonyEngine::Resource::World::Hierarchy
{
	void Transform2DDeserializer::Deserialize(const std::size_t entityCount, const std::span<const std::byte> input, const std::span<std::byte> output)
	{
		if (InputComponentSize * entityCount != input.size()) [[unlikely]]
		{
			throw std::runtime_error("Invalid component table input");
		}

		const std::byte* inputData = input.data();
		std::byte* outputData = output.data();
		for (std::size_t i = 0uz; i < entityCount; ++i, outputData += sizeof(PonyEngine::World::Hierarchy::LocalTransform2D))
		{
			const double positionX = Read<double>(inputData);
			const double positionY = Read<double>(inputData);
			const float rotation = Read<float>(inputData);
			const float scaleX = Read<float>(inputData);
			const float scaleY = Read<float>(inputData);
			const auto outputTransform = PonyEngine::World::Hierarchy::LocalTransform2D(Math::Vector2<double>(positionX, positionY),
				rotation, Math::Vector2<float>(scaleX, scaleY));
			std::memcpy(outputData, &outputTransform, sizeof(PonyEngine::World::Hierarchy::LocalTransform2D));
		}
	}

	template<typename T>
	T Transform2DDeserializer::Read(const std::byte*& input) noexcept
	{
		if constexpr (sizeof(T) == 1uz)
		{
			return static_cast<T>(*input++);
		}
		else
		{
			T value;
			std::memcpy(&value, input, sizeof(T));
			input += sizeof(T);
			return value;
		}
	}
}
