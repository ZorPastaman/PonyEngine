/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.World.Ext:IComponentDeserializer;

import std;

import :IWorldDeserializationRequest;

export namespace PonyEngine::Resource::World
{
	/// @brief Component deserializer that executes immediately.
	class IInlineComponentDeserializer
	{
		PONY_INTERFACE_BODY(IInlineComponentDeserializer)

		/// @brief Deserializes a component.
		/// @param entityCount Entity count in the component table.
		/// @param input Input bytes.
		/// @param output Output bytes.
		virtual void Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output) = 0;
	};

	/// @brief Component deserializer that executes in async manner.
	class IComponentDeserializer
	{
		PONY_INTERFACE_BODY(IComponentDeserializer)

		/// @brief Creates a deserialization request.
		/// @param entityCount Entity count in the component table.
		/// @param input Input bytes.
		/// @param output Output bytes.
		/// @param callback Callback.
		/// @return Deserialization request.
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IWorldDeserializationRequest> Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output,
			std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback = nullptr) = 0;
	};
}
