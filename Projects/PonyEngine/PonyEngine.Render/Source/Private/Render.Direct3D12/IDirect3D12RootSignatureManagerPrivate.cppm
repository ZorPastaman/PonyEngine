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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RootSignatureManagerPrivate;

import <memory>;

import :Direct3D12RootSignature;
import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 root signature manager.
	class IDirect3D12RootSignatureManagerPrivate
	{
		INTERFACE_BODY(IDirect3D12RootSignatureManagerPrivate)

		/// @brief Creates a root signature.
		/// @param rootSignatureShader Root signature shader.
		/// @param mvpIndex Model-view-projection matrix slot index.
		/// @return 
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Direct3D12RootSignature> CreateRootSignature(const Direct3D12Shader& rootSignatureShader, UINT mvpIndex) = 0;
	};
}
