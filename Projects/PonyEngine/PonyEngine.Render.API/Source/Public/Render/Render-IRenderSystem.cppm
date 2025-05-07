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

export module PonyEngine.Render:IRenderSystem;

import :ICameraManager;
import :IMaterialManager;
import :IMeshManager;
import :IPipelineStateManager;
import :IRootSignatureManager;
import :IRenderObjectManager;
import :IShaderManager;
import :ITextureManager;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)

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
	};
}
