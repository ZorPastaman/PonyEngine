/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IPipelineLayout;

import std;

import :DescriptorSetMeta;

export namespace PonyEngine::RenderDevice
{
	/// @brief Pipeline layout.
	class IPipelineLayout
	{
		PONY_INTERFACE_BODY(IPipelineLayout)

		/// @brief Gets the descriptor sets.
		/// @return Descriptor sets.
		[[nodiscard("Pure function")]]
		virtual std::span<const DescriptorSetMeta> DescriptorSets() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
