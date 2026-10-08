/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World:CopyComponentDeserializer;

import std;

import :IComponentDeserializer;

export namespace PonyEngine::Resource::World
{
	/// @brief Component deserializer that simply copies input bytes to output bytes as is.
	class CopyComponentDeserializer final : IInlineComponentDeserializer
	{
	public:
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer(const CopyComponentDeserializer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer(CopyComponentDeserializer&& other) noexcept = default;

		~CopyComponentDeserializer() noexcept = default;

		virtual void Deserialize(std::span<const std::byte> input, std::span<std::byte> output) override;

		CopyComponentDeserializer& operator =(const CopyComponentDeserializer& other) noexcept = default;
		CopyComponentDeserializer& operator =(CopyComponentDeserializer&& other) noexcept = default;
	};
}

namespace PonyEngine::Resource::World
{
	void CopyComponentDeserializer::Deserialize(const std::span<const std::byte> input, const std::span<std::byte> output)
	{
		if (input.size() != output.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid input/output size");
		}

		std::memcpy(output.data(), input.data(), output.size());
	}
}
