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

import PonyEngine.Render;

import :Material;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class IMaterialManager
	{
		INTERFACE_BODY(IMaterialManager)

		/// @brief Creates a render material.
		/// @param material Source material.
		/// @return Render material.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<const Render::Material>& material) = 0;
	};
}
