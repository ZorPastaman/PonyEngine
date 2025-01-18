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
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IResourceManager;

import <memory>;

import PonyBase.Container;

import :Buffer;
import :ResourcePlacement;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	class IResourceManager
	{
		INTERFACE_BODY(IResourceManager)

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Buffer> CreateBuffer(UINT64 size, ResourcePlacement placement) = 0;
	};
}
