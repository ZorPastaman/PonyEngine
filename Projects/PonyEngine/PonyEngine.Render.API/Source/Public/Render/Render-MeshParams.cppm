/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:MeshParams;

import <memory>;
import <optional>;
import <string>;
import <unordered_map>;
import <vector>;

import PonyBase.Container;

import PonyMath.Shape;

import PonyShader.Core;

import :ITexture;

export namespace PonyEngine::Render
{
	/// @brief Mesh parameters.
	struct MeshParams final
	{
		/// @brief Map of data types to buffer parameters. Can't use the same types as the @p textures.
		/// @note Don't use strings starting with "Pony_" as data types.
		std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>> data;
		/// @brief Map of texture types to textures. Can't use the same types as the @p data.
		/// @note Don't use strings starting with "Pony_" as types.
		std::unordered_map<std::string, std::vector<std::shared_ptr<ITexture>>> textures;

		/// @brief How many thread group counts are required for a mesh.
		/// @details Usually these numbers correspond to a meshlet count or a grid size.
		PonyShader::Core::ThreadGroupCounts threadGroupCounts;
		std::optional<PonyMath::Shape::AABB<float>> boundingBox = std::nullopt; ///< Bounding box. If it's std::nullopt, no bounding box check is done.

		std::string name; ///< Mesh name.
	};
}
