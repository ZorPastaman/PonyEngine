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

export module PonyEngine.Render.Direct3D12.Detail:IRootSignatureManager;

import <memory>;

import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 root signature manager.
	class IRootSignatureManager
	{
		INTERFACE_BODY(IRootSignatureManager)

		/// @brief Creates a root signature.
		/// @param rootSignatureShader Root signature shader.
		/// @return Root signature.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<RootSignature> CreateRootSignature(const std::shared_ptr<const Shader>& rootSignatureShader) = 0;
	};
}
