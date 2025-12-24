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

export module PonyEngine.RenderDevice:IRenderDeviceService;

import std;

import :IRenderAPI;

export namespace PonyEngine::Render
{
	class IRenderDeviceService
	{
		INTERFACE_BODY(IRenderDeviceService)

		static constexpr std::size_t EmptyRenderApiIndex = 0uz;

		[[nodiscard("Pure function")]]
		virtual std::size_t RenderApiCount() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderAPI& RenderApi(std::size_t index) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderAPI& ActiveRenderApi(std::size_t index) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t ActiveRenderApiIndex() const noexcept = 0;
		virtual void SwitchToRenderApi(std::size_t index) = 0;
	};
}
