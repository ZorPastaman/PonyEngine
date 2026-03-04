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

export module PonyEngine.RenderDevice:IDepthStencilContainer;

import std;

import :DSVMeta;

export namespace PonyEngine::RenderDevice
{
	/// @brief Container of DSVs.
	class IDepthStencilContainer
	{
		PONY_INTERFACE_BODY(IDepthStencilContainer)

		/// @brief Gets the container size.
		/// @return Container size.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept = 0;

		/// @brief Gets the meta at the @p index.
		/// @param index Container element index.
		/// @return Container element meta.
		[[nodiscard("Pure function")]]
		virtual const DSVMeta& Meta(std::uint32_t index) const noexcept = 0;

		/// @brief Gets the container name.
		/// @return Container name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the container name.
		/// @param name Container name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
