/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderObjectManager;

import PonyEngine.Render;

import :IDirect3D12RenderObject;

export namespace PonyEngine::Render
{
	class IDirect3D12RenderObjectManager : public IRenderObjectManager
	{
		INTERFACE_BODY(IDirect3D12RenderObjectManager)

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObject* FindRenderObject(RenderObjectHandle handle) const noexcept override = 0;
	};
}
