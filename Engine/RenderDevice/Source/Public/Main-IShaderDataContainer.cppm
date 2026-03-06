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

export module PonyEngine.RenderDevice:IShaderDataContainer;

import std;

import :IContainer;
import :ShaderDataMeta;

export namespace PonyEngine::RenderDevice
{
	/// @brief Container of CBVs, SRVs and UAVs.
	class IShaderDataContainer : public IContainer
	{
		PONY_INTERFACE_BODY(IShaderDataContainer)

		/// @brief Checks if the container is shader visible.
		/// @return @a True if it's shader visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsShaderVisible() const noexcept = 0;

		/// @brief Gets the meta at the @p index.
		/// @param index Container element index.
		/// @return Container element meta.
		[[nodiscard("Pure function")]]
		virtual const ShaderDataMeta& Meta(std::uint32_t index) const noexcept = 0;
	};
}
