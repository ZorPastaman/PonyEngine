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

export module PonyEngine.Render.Direct3D12.Detail:IRootSignatureManagerPrivate;

import <memory>;

import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 root signature manager.
	class IRootSignatureManagerPrivate
	{
		INTERFACE_BODY(IRootSignatureManagerPrivate)

		/// @brief Creates a root signature.
		/// @param rootSignatureShader Root signature shader.
		/// @param mvpIndex Model-view-projection matrix slot index.
		/// @return 
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<RootSignature> CreateRootSignature(const Shader& rootSignatureShader, const std::unordered_map<std::string, UINT>& meshDataSlots, UINT mvpIndex) = 0;
	};
}
