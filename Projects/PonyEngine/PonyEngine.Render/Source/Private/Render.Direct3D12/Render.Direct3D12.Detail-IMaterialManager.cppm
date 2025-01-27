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

export module PonyEngine.Render.Direct3D12.Detail:IMaterialManager;

import <memory>;

import :Material;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class IMaterialManager
	{
		INTERFACE_BODY(IMaterialManager)

		/// @brief Creates a material.
		/// @param rootSignature Root signature.
		/// @param meshShader Mesh shader.
		/// @param pixelShader Pixel shader.
		/// @return Material.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<RootSignature>& rootSignature, const std::shared_ptr<const Shader>& amplificationShader, const std::shared_ptr<const Shader>& meshShader, 
			const std::shared_ptr<const Shader>& pixelShader) = 0;
	};
}
