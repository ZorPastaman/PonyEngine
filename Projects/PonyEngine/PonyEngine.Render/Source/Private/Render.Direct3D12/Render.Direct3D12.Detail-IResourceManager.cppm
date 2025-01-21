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
import <span>;

import PonyBase.Container;

import PonyMath.Color;

import :Buffer;
import :HeapType;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	class IResourceManager
	{
		INTERFACE_BODY(IResourceManager)

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Buffer> CreateBuffer(UINT64 size, HeapType heapType) = 0;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture1D(UINT64 width, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture2D(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture3D(UINT64 width, UINT height, UINT16 depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateRenderTarget(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<FLOAT>& clearColor) = 0;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateDepthStencil(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, D3D12_DEPTH_STENCIL_VALUE depthStencilValue) = 0;
	};
}
