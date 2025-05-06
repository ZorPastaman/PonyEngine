/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:PipelineStateParams;

import <cstdint>;
import <memory>;
import <string>;
import <unordered_map>;

import :Blend;
import :DepthStencil;
import :IRootSignature;
import :IShader;
import :Rasterizer;
import :ThreadGroupCounts;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state parameters.
	struct PipelineStateParams final
	{
		std::shared_ptr<IRootSignature> rootSignature; ///< Root signature.
		std::shared_ptr<IShader> amplificationShader; ///< Amplification shader. It's optional.
		std::shared_ptr<IShader> meshShader; ///< Mesh shader.
		std::shared_ptr<IShader> pixelShader; ///< Pixel shader.

		Blend blend; ///< Blend parameters.
		Rasterizer rasterizer; ///< Rasterizer parameters.
		DepthStencil depthStencil; ///< Depth stencil parameters.

		/// @brief Data slots.
		/// @details The engine automatically binds mesh data to shader slots if their types match.
		/// If a type matches one of the special types declared in @p PonyEngine::Render::DataTypes,
		/// the engine will bind specific data to it automatically.
		std::unordered_map<std::string, std::uint32_t> dataSlots;

		ThreadGroupCounts threadGroupCounts; ///< Thread group counts parameters.
		std::int32_t renderQueue = 0; ///< Render queue.
		bool cameraCulling = true; ///< Is camera culling enabled?

		std::string name; ///< Pipeline state name.
	};
}
