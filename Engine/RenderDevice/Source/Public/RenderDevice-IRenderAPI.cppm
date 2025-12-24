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

export module PonyEngine.RenderDevice:IRenderAPI;

import std;

import PonyEngine.Meta;

export namespace PonyEngine::Render
{
	class IRenderAPI
	{
		INTERFACE_BODY(IRenderAPI)

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual Meta::Version Version() const noexcept = 0;
	};
}
