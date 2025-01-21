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

import :IBackManager;
import :ICopyPipeline;
import :IDescriptorHeapManager;
import :IFrameManager;
import :IGraphicsPipeline;
import :IMaterialManagerPrivate;
import :IMeshManagerPrivate;
import :IResourceManager;
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

		/// @brief Gets the back manager.
		/// @return Back manager.
		[[nodiscard("Pure function")]]
		virtual IBackManager& BackManager() noexcept = 0;
		/// @brief Gets the back manager.
		/// @return Back manager.
		[[nodiscard("Pure function")]]
		virtual const IBackManager& BackManager() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IFrameManager& FrameManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IFrameManager& FrameManager() const noexcept = 0;

		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual IMeshManager& MeshManager() noexcept = 0;
		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual const IMeshManager& MeshManager() const noexcept = 0;

		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual IRootSignatureManager& RootSignatureManager() noexcept = 0;
		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureManager& RootSignatureManager() const noexcept = 0;

		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual IMaterialManager& MaterialManager() noexcept = 0;
		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual const IMaterialManager& MaterialManager() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IResourceManager& ResourceManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const IResourceManager& ResourceManager() const noexcept = 0;

		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual IDescriptorHeapManager& DescriptorHeapManager() noexcept = 0;
		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual const IDescriptorHeapManager& DescriptorHeapManager() const noexcept = 0;

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
