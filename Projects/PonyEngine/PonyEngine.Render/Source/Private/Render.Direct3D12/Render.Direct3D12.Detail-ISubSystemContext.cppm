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

export module PonyEngine.Render.Direct3D12.Detail:ISubSystemContext;

import PonyDebug.Log;

import :IBackManagerPrivate;
import :ICopyPipeline;
import :IDepthStencilPrivate;
import :IDescriptorHeapManager;
import :IGraphicsPipeline;
import :IMaterialManagerPrivate;
import :IMeshManagerPrivate;
import :IRenderObjectManagerPrivate;
import :IRenderTargetPrivate;
import :IRenderViewPrivate;
import :IRootSignatureManagerPrivate;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 sub-system context.
	class ISubSystemContext
	{
		INTERFACE_BODY(ISubSystemContext)

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
		virtual IBackManagerPrivate& BackPrivate() noexcept = 0;
		/// @brief Gets the back.
		/// @return Back.
		[[nodiscard("Pure function")]]
		virtual const IBackManagerPrivate& BackPrivate() const noexcept = 0;

		/// @brief Gets the render target.
		/// @return Render target.
		[[nodiscard("Pure function")]]
		virtual IRenderTargetPrivate& RenderTargetPrivate() noexcept = 0;
		/// @brief Gets the render target.
		/// @return Render target.
		[[nodiscard("Pure function")]]
		virtual const IRenderTargetPrivate& RenderTargetPrivate() const noexcept = 0;

		/// @brief Gets the depth stencil.
		/// @return Depth stencil.
		[[nodiscard("Pure function")]]
		virtual IDepthStencilPrivate& DepthStencilPrivate() noexcept = 0;
		/// @brief Gets the depth stencil.
		/// @return Depth stencil.
		[[nodiscard("Pure function")]]
		virtual const IDepthStencilPrivate& DepthStencilPrivate() const noexcept = 0;

		/// @brief Gets the render view.
		/// @return Render view.
		[[nodiscard("Pure function")]]
		virtual IRenderViewPrivate& RenderViewPrivate() noexcept = 0;
		/// @brief Gets the render view.
		/// @return Render view.
		[[nodiscard("Pure function")]]
		virtual const IRenderViewPrivate& RenderViewPrivate() const noexcept = 0;

		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual IMeshManagerPrivate& MeshManagerPrivate() noexcept = 0;
		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual const IMeshManagerPrivate& MeshManagerPrivate() const noexcept = 0;

		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual IRootSignatureManagerPrivate& RootSignatureManagerPrivate() noexcept = 0;
		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureManagerPrivate& RootSignatureManagerPrivate() const noexcept = 0;

		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual IMaterialManagerPrivate& MaterialManagerPrivate() noexcept = 0;
		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual const IMaterialManagerPrivate& MaterialManagerPrivate() const noexcept = 0;

		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual IDescriptorHeapManager& DescriptorHeapManager() noexcept = 0;
		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual const IDescriptorHeapManager& DescriptorHeapManager() const noexcept = 0;

		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManagerPrivate& RenderObjectManagerPrivate() noexcept = 0;
		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManagerPrivate& RenderObjectManagerPrivate() const noexcept = 0;

		/// @brief Gets the copy pipeline.
		/// @return Copy pipeline.
		[[nodiscard("Pure function")]]
		virtual ICopyPipeline& CopyPipeline() noexcept = 0;
		/// @brief Gets the copy pipeline.
		/// @return Copy pipeline.
		[[nodiscard("Pure function")]]
		virtual const ICopyPipeline& CopyPipeline() const noexcept = 0;

		/// @brief Gets the graphics pipeline.
		/// @return Graphics pipeline.
		[[nodiscard("Pure function")]]
		virtual IGraphicsPipeline& GraphicsPipeline() noexcept = 0;
		/// @brief Gets the graphics pipeline.
		/// @return Graphics pipeline.
		[[nodiscard("Pure function")]]
		virtual const IGraphicsPipeline& GraphicsPipeline() const noexcept = 0;
	};
}
