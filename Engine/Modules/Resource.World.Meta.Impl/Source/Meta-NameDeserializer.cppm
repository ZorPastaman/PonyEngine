/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Meta.Impl:NameDeserializer;

import std;

import PonyEngine.Resource.World.Ext;
import PonyEngine.World.Meta;

export namespace PonyEngine::Resource::World::Meta
{
	/// @brief Name deserializer.
	class NameDeserializer final : public IInlineComponentDeserializer
	{
	public:
		[[nodiscard("Pure constructor")]]
		NameDeserializer() noexcept = default;
		NameDeserializer(const NameDeserializer&) = delete;
		NameDeserializer(NameDeserializer&&) = delete;

		~NameDeserializer() noexcept = default;

		virtual void Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output) override;

		NameDeserializer& operator =(const NameDeserializer&) = delete;
		NameDeserializer& operator =(NameDeserializer&&) = delete;

	private:
		/// @brief Validates if the input has enough data.
		/// @param inputData Current input pointer.
		/// @param inputDataEnd End input pointer.
		/// @param requiredSize Required size.
		static void ValidateSize(const std::byte* inputData, const std::byte* inputDataEnd, std::size_t requiredSize);

		/// @brief Reads the input as a data of type @p T.
		/// @tparam T Data type.
		/// @param inputData Input pointer.
		/// @return Read data.
		template<typename T>
		static T Read(const std::byte*& inputData) noexcept;
		/// @brief Reads the input as a string.
		/// @param inputData Input pointer.
		/// @param length String length.
		/// @return Read string.
		static std::string_view ReadString(const std::byte*& inputData, std::size_t length) noexcept;
	};
}

namespace PonyEngine::Resource::World::Meta
{
	void NameDeserializer::Deserialize(const std::size_t entityCount, const std::span<const std::byte> input, const std::span<std::byte> output)
	{
		const std::byte* inputData = input.data();
		const std::byte* const inputDataEnd = input.data() + input.size();
		std::byte* outputData = output.data();
		for (std::size_t i = 0uz; i < entityCount; ++i, outputData += sizeof(PonyEngine::World::Meta::Name))
		{
			ValidateSize(inputData, inputDataEnd, sizeof(std::uint8_t));
			const std::uint8_t length = Read<std::uint8_t>(inputData);
			if (length > PonyEngine::World::Meta::Name::MaxLength) [[unlikely]]
			{
				throw std::runtime_error("Invalid name length");
			}

			ValidateSize(inputData, inputDataEnd, length);
			const std::string_view nameString = ReadString(inputData, length);

			const auto name = PonyEngine::World::Meta::Name(nameString);
			std::memcpy(outputData, &name, sizeof(PonyEngine::World::Meta::Name));
		}

		if (inputData != inputDataEnd) [[unlikely]]
		{
			throw std::runtime_error("Invalid component table input");
		}
	}

	void NameDeserializer::ValidateSize(const std::byte* const inputData, const std::byte* const inputDataEnd, const std::size_t requiredSize)
	{
		if (static_cast<std::size_t>(inputDataEnd - inputData) < requiredSize) [[unlikely]]
		{
			throw std::runtime_error("Invalid component table input");
		}
	}

	template<typename T>
	T NameDeserializer::Read(const std::byte*& inputData) noexcept
	{
		if constexpr (sizeof(T) == 1uz)
		{
			return static_cast<T>(*inputData++);
		}
		else
		{
			T value;
			std::memcpy(&value, inputData, sizeof(T));
			inputData += sizeof(T);
			return value;
		}
	}

	std::string_view NameDeserializer::ReadString(const std::byte*& inputData, const std::size_t length) noexcept
	{
		const auto string = std::string_view(reinterpret_cast<const char*>(inputData), length);
		inputData += length;
		return string;
	}
}
