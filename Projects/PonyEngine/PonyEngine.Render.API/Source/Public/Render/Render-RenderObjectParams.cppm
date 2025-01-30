/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderObjectParams;

import <memory>;

import PonyMath.Core;

import :Material;
import :Mesh;

export namespace PonyEngine::Render
{
	struct RenderObjectParams final
	{
		std::shared_ptr<const Material> material;
		std::shared_ptr<const Mesh> mesh;
		PonyMath::Core::Matrix4x4<float> modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
	};
}
