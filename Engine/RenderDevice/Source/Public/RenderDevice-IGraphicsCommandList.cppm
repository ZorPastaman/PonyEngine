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

export module PonyEngine.RenderDevice:IGraphicsCommandList;

import std;

export namespace PonyEngine::Render
{
	class IGraphicsCommandList
	{
		PONY_INTERFACE_BODY(IGraphicsCommandList)

		virtual void Reset() = 0;
		virtual void Close() = 0;

		virtual void SetName(std::string_view name) = 0;
	};
}
