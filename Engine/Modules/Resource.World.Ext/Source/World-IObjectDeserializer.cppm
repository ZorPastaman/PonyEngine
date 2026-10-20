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

export module PonyEngine.Resource.World.Ext:IObjectDeserializer;

import std;

import PonyEngine.World;

import :IWorldDeserializationRequest;

export namespace PonyEngine::Resource::World
{
	/// @brief Object deserializer that executes immediately.
	class IInlineObjectDeserializer
	{
		PONY_INTERFACE_BODY(IInlineObjectDeserializer)

		/// @brief Deserializes an object.
		/// @param input Input bytes.
		/// @param output Output object.
		virtual void Deserialize(std::span<const std::byte> input, PonyEngine::World::Object& output) = 0;
	};

	/// @brief Object deserializer that executes in async manner.
	class IObjectDeserializer
	{
		PONY_INTERFACE_BODY(IObjectDeserializer)

		/// @brief Deserializes an object.
		/// @param input Input bytes.
		/// @param output Output object.
		/// @param callback Callback.
		/// @return Deserialization request.
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IWorldDeserializationRequest> Deserialize(std::span<const std::byte> input, PonyEngine::World::Object& output,
			std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback = nullptr) = 0;
	};
}
