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

export module PonyEngine.RenderDevice:ISamplerContainer;

import std;

import :IContainer;
import :SamplerMeta;

export namespace PonyEngine::RenderDevice
{
	/// @brief Container of samplers.
	class ISamplerContainer : public IContainer
	{
		PONY_INTERFACE_BODY(ISamplerContainer)

		/// @brief Checks if the container is shader visible.
		/// @return @a True if it's shader visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsShaderVisible() const noexcept = 0;

		/// @brief Gets the meta at the @p index.
		/// @param index Container element index.
		/// @return Container element meta.
		[[nodiscard("Pure function")]]
		virtual const SamplerMeta& Meta(std::uint32_t index) const noexcept = 0;
	};
}
