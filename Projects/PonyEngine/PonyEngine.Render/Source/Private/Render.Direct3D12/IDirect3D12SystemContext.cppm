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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12SystemContext;

import PonyDebug.Log;

import :IDirect3D12BackPrivate;
import :IDirect3D12CopyPipeline;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12GraphicsPipeline;
import :IDirect3D12MaterialManagerPrivate;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12RenderObjectManagerPrivate;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12RenderViewPrivate;
import :IDirect3D12RootSignatureManagerPrivate;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 system context.
	class IDirect3D12SystemContext
	{
		INTERFACE_BODY(IDirect3D12SystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the render device.
		/// @return Render device.
		[[nodiscard("Pure function")]]
		virtual ID3D12Device10& Device() noexcept = 0;
		/// @brief Gets the render device.
		/// @return Render device.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Device10& Device() const noexcept = 0;

		/// @brief Gets the back.
		/// @return Back.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12BackPrivate& BackPrivate() noexcept = 0;
		/// @brief Gets the back.
		/// @return Back.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12BackPrivate& BackPrivate() const noexcept = 0;

		/// @brief Gets the render target.
		/// @return Render target.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTargetPrivate& RenderTargetPrivate() noexcept = 0;
		/// @brief Gets the render target.
		/// @return Render target.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTargetPrivate& RenderTargetPrivate() const noexcept = 0;

		/// @brief Gets the depth stencil.
		/// @return Depth stencil.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12DepthStencilPrivate& DepthStencilPrivate() noexcept = 0;
		/// @brief Gets the depth stencil.
		/// @return Depth stencil.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12DepthStencilPrivate& DepthStencilPrivate() const noexcept = 0;

		/// @brief Gets the render view.
		/// @return Render view.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderViewPrivate& RenderViewPrivate() noexcept = 0;
		/// @brief Gets the render view.
		/// @return Render view.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderViewPrivate& RenderViewPrivate() const noexcept = 0;

		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12MeshManagerPrivate& MeshManagerPrivate() noexcept = 0;
		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MeshManagerPrivate& MeshManagerPrivate() const noexcept = 0;

		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RootSignatureManagerPrivate& RootSignatureManagerPrivate() noexcept = 0;
		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RootSignatureManagerPrivate& RootSignatureManagerPrivate() const noexcept = 0;

		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12MaterialManagerPrivate& MaterialManagerPrivate() noexcept = 0;
		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MaterialManagerPrivate& MaterialManagerPrivate() const noexcept = 0;

		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManagerPrivate& RenderObjectManagerPrivate() noexcept = 0;
		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManagerPrivate& RenderObjectManagerPrivate() const noexcept = 0;

		/// @brief Gets the copy pipeline.
		/// @return Copy pipeline.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12CopyPipeline& CopyPipeline() noexcept = 0;
		/// @brief Gets the copy pipeline.
		/// @return Copy pipeline.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12CopyPipeline& CopyPipeline() const noexcept = 0;

		/// @brief Gets the graphics pipeline.
		/// @return Graphics pipeline.
		[[nodiscard("Pure function")]]
		virtual IDirect3D12GraphicsPipeline& GraphicsPipeline() noexcept = 0;
		/// @brief Gets the graphics pipeline.
		/// @return Graphics pipeline.
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12GraphicsPipeline& GraphicsPipeline() const noexcept = 0;
	};
}
