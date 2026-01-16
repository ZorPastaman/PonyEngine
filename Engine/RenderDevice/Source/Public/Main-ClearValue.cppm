/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ClearValue;

import std;

import PonyEngine.Math;

import :DepthStencil;

export namespace PonyEngine::RenderDevice
{
	struct NoClear final
	{
	};

	using ClearValue = std::variant<NoClear, Math::ColorRGBA<float>, DepthStencil>;
}
