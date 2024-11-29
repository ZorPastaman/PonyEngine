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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12CopyPipeline;

export namespace PonyEngine::Render
{
	class IDirect3D12CopyPipeline
	{
		INTERFACE_BODY(IDirect3D12CopyPipeline)

		virtual void AddCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) = 0;
	};
}
