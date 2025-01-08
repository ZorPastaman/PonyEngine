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

export module PonyEngine.Render.Direct3D12.Detail:IRenderObjectManagerPrivate;

import <cstddef>;

import PonyEngine.Render.Direct3D12;

import :RenderObject;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render object manager.
	class IRenderObjectManagerPrivate : public IRenderObjectManager
	{
		INTERFACE_BODY(IRenderObjectManagerPrivate)
	};
}
