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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12SystemContext;

import PonyEngine.Render.Detail;
import PonyEngine.Render.Direct3D12;

import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12RenderObjectManagerPrivate;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12MaterialManagerPrivate;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12RootSignatureManagerPrivate;

export namespace PonyEngine::Render
{
	class IDirect3D12SystemContext : public IRenderSystemContext
	{
		INTERFACE_BODY(IDirect3D12SystemContext)

		[[nodiscard("Pure function")]]
		virtual ID3D12Device10& Device() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Device10& Device() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTargetPrivate& RenderTarget() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTargetPrivate& RenderTarget() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12DepthStencilPrivate& DepthStencil() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12DepthStencilPrivate& DepthStencil() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderView& RenderView() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderView& RenderView() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RootSignatureManagerPrivate& RootSignatureManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RootSignatureManagerPrivate& RootSignatureManager() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MaterialManagerPrivate& MaterialManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MaterialManagerPrivate& MaterialManager() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MeshManagerPrivate& MeshManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MeshManagerPrivate& MeshManager() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManagerPrivate& RenderObjectManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManagerPrivate& RenderObjectManager() const noexcept = 0;
	};
}
