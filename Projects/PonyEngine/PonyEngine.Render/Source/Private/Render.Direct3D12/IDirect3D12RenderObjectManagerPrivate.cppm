/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderObjectManagerPrivate;

import <memory>;
import <span>;

import PonyEngine.Render.Direct3D12;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	class IDirect3D12RenderObjectManagerPrivate : public IDirect3D12RenderObjectManager
	{
		INTERFACE_BODY(IDirect3D12RenderObjectManagerPrivate)

		[[nodiscard("Pure function")]]
		virtual std::span<const std::weak_ptr<Direct3D12RenderObject>> RenderObjects() noexcept = 0; // TODO: Fill span with simple pointers.
	};
}
