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

export module PonyEngine.Render:IPipelineStateObserver;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state observer.
	class IPipelineStateObserver
	{
		INTERFACE_BODY(IPipelineStateObserver)

		/// @brief Invoked when a root signature shader is changed.
		virtual void OnRootSignatureShaderChanged() noexcept = 0;
		/// @brief Invoked when an amplification shader is changed.
		virtual void OnAmplificationShaderChanged() noexcept = 0;
		/// @brief Invoked when a mesh shader is changed.
		virtual void OnMeshShaderChanged() noexcept = 0;
		/// @brief Invoked when a pixel shader is changed.
		virtual void OnPixelShaderChanged() noexcept = 0;

		/// @brief Invoked when blend parameters are changed.
		virtual void OnBlendChanged() noexcept = 0;
		/// @brief Invoked when rasterizer parameters are changed.
		virtual void OnRasterizerChanged() noexcept = 0;
		/// @brief Invoked when depth stencil parameters are changed.
		virtual void OnDepthStencilChanged() noexcept = 0;

		/// @brief Invoked when data slots are changed.
		virtual void OnDataSlotsChanged() noexcept = 0;

		/// @brief Invoked when thread group counts are changed.
		virtual void OnThreadGroupCountsChanged() noexcept = 0;
		/// @brief Invoked when a reader queue is changed.
		virtual void OnRenderQueueChanged() noexcept = 0;
		/// @brief Invoked when a camera culling is changed.
		virtual void OnCameraCullingChanged() noexcept = 0;

		/// @brief Invoked when a name is changed.
		virtual void OnNameChanged() noexcept = 0;
	};
}
