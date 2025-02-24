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

export module PonyEngine.Render:IMaterialObserver;

export namespace PonyEngine::Render
{
	class IMaterialObserver
	{
		INTERFACE_BODY(IMaterialObserver)

		virtual void OnRootSignatureChanged() noexcept = 0;
		virtual void OnAmplificationShaderChanged() noexcept = 0;
		virtual void OnMeshShaderChanged() noexcept = 0;
		virtual void OnPixelShaderChanged() noexcept = 0;

		virtual void OnBlendChanged() noexcept = 0;
		virtual void OnRasterizerChanged() noexcept = 0;
		virtual void OnDepthStencilChanged() noexcept = 0;

		virtual void OnDataSlotsChanged() noexcept = 0;

		virtual void OnThreadGroupCountsChanged() noexcept = 0;
		virtual void OnRenderQueueChanged() noexcept = 0;
		virtual void OnCameraCullingChanged() noexcept = 0;

		virtual void OnNameChanged() noexcept = 0;
	};
}
