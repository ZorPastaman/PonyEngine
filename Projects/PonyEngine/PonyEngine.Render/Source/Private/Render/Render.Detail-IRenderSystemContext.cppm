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

export module PonyEngine.Render.Detail:IRenderSystemContext;

import PonyDebug.Log;

import :IPipeline;
import :IRenderAgent;

export namespace PonyEngine::Render
{
	/// @brief Render system context.
	class IRenderSystemContext
	{
		INTERFACE_BODY(IRenderSystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the swap chain.
		/// @return Swap chain.
		[[nodiscard("Pure function")]]
		virtual ISwapChain& SwapChain() noexcept = 0;
		/// @brief Gets the swap chain.
		/// @return Swap chain.
		[[nodiscard("Pure function")]]
		virtual const ISwapChain& SwapChain() const noexcept = 0;

		/// @brief Gets the shader manager.
		/// @return Shader manager.
		[[nodiscard("Pure function")]]
		virtual IShaderManager& ShaderManager() noexcept = 0;
		/// @brief Gets the shader manager.
		/// @return Shader manager.
		[[nodiscard("Pure function")]]
		virtual const IShaderManager& ShaderManager() const noexcept = 0;

		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual IRootSignatureManager& RootSignatureManager() noexcept = 0;
		/// @brief Gets the root signature manager.
		/// @return Root signature manager.
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureManager& RootSignatureManager() const noexcept = 0;

		/// @brief Gets the pipeline state manager.
		/// @return Pipeline state manager.
		[[nodiscard("Pure function")]]
		virtual IPipelineStateManager& PipelineStateManager() noexcept = 0;
		/// @brief Gets the pipeline state manager.
		/// @return Pipeline state manager.
		[[nodiscard("Pure function")]]
		virtual const IPipelineStateManager& PipelineStateManager() const noexcept = 0;

		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual IMaterialManager& MaterialManager() noexcept = 0;
		/// @brief Gets the material manager.
		/// @return Material manager.
		[[nodiscard("Pure function")]]
		virtual const IMaterialManager& MaterialManager() const noexcept = 0;

		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual IMeshManager& MeshManager() noexcept = 0;
		/// @brief Gets the mesh manager.
		/// @return Mesh manager.
		[[nodiscard("Pure function")]]
		virtual const IMeshManager& MeshManager() const noexcept = 0;

		/// @brief Gets the texture manager.
		/// @return Texture manager.
		[[nodiscard("Pure function")]]
		virtual ITextureManager& TextureManager() noexcept = 0;
		/// @brief Gets the texture manager.
		/// @return Texture manager.
		[[nodiscard("Pure function")]]
		virtual const ITextureManager& TextureManager() const noexcept = 0;

		/// @brief Gets the camera manager.
		/// @return Camera manager.
		[[nodiscard("Pure function")]]
		virtual ICameraManager& CameraManager() noexcept = 0;
		/// @brief Gets the camera manager.
		/// @return Camera manager.
		[[nodiscard("Pure function")]]
		virtual const ICameraManager& CameraManager() const noexcept = 0;

		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() noexcept = 0;
		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManager& RenderObjectManager() const noexcept = 0;

		/// @brief Gets the pipeline.
		/// @return Pipeline.
		[[nodiscard("Pure function")]]
		virtual IPipeline& Pipeline() noexcept = 0;
		/// @brief Gets the pipeline.
		/// @return Pipeline.
		[[nodiscard("Pure function")]]
		virtual const IPipeline& Pipeline() const noexcept = 0;

		/// @brief Gets the render agent.
		/// @return Render agent.
		[[nodiscard("Pure function")]]
		virtual IRenderAgent& RenderAgent() noexcept = 0;
		/// @brief Gets the render agent.
		/// @return Render agent.
		[[nodiscard("Pure function")]]
		virtual const IRenderAgent& RenderAgent() const noexcept = 0;
	};
}
