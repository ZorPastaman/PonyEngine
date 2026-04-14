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

export module PonyEngine.RenderDevice:IRenderTargetContainer;

import std;

import :IContainer;
import :RTVMeta;

export namespace PonyEngine::RenderDevice
{
	/// @brief Container of RTVs.
	class IRenderTargetContainer : public IContainer
	{
		PONY_INTERFACE_BODY(IRenderTargetContainer)

		/// @brief Gets the meta at the @p index.
		/// @param index Container element index.
		/// @return Container element meta.
		[[nodiscard("Pure function")]]
		virtual const RTVMeta& Meta(std::uint32_t index) const noexcept = 0;
	};
}
