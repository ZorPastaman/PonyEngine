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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12MaterialManagerPrivate;

import <memory>;

import :Direct3D12Material;
import :Direct3D12RootSignature;
import :Direct3D12PipelineParams;
import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	class IDirect3D12MaterialManagerPrivate
	{
		INTERFACE_BODY(IDirect3D12MaterialManagerPrivate)

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Direct3D12Material> CreateMaterial(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader,
			const Direct3D12PipelineParams& pipelineParams) = 0;
	};
}
