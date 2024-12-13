/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderObjectManagerPrivate;

import <cstddef>;

import PonyEngine.Render.Direct3D12;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render object manager.
	class IDirect3D12RenderObjectManagerPrivate : public IDirect3D12RenderObjectManager
	{
		INTERFACE_BODY(IDirect3D12RenderObjectManagerPrivate)
	};
}
