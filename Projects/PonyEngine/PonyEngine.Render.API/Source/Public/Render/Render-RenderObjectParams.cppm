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
import <string>;

import PonyMath.Core;

import :PipelineState;
import :Mesh;

export namespace PonyEngine::Render
{
	/// @brief Render object parameters.
	struct RenderObjectParams final
	{
		std::shared_ptr<const PipelineState> pipelineState; ///< Render object pipeline state.
		std::shared_ptr<const Mesh> mesh; ///< Render object mesh.
		PonyMath::Core::Matrix4x4<float> modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity; ///< Render object model matrix.

		std::string name; ///< Render object name.
	};
}
