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

export module PonyEngine.Render:IMaterialManager;

import <memory>;

import :IMaterial;
import :MaterialParams;

export namespace PonyEngine::Render
{
	/// @brief Material manager.
	class IMaterialManager
	{
		INTERFACE_BODY(IMaterialManager)

		/// @brief Creates a material.
		/// @param params Material parameters.
		/// @return Material.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IMaterial> CreateMaterial(const MaterialParams& params) = 0;
	};
}
