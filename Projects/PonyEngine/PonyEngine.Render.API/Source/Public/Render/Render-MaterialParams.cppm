/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:MaterialParams;

import <memory>;
import <string>;
import <unordered_map>;
import <vector>;

import PonyBase.Container;

import :IPipelineState;
import :ITexture;

export namespace PonyEngine::Render
{
	/// @brief Material parameters.
	struct MaterialParams final
	{
		std::shared_ptr<const IPipelineState> pipelineState; ///< Pipeline state.

		/// @brief Map of a data type to data buffer parameters.
		/// @note Don't use strings starting with "Pony_" as data types.
		/// @note Don't use the same key in the @p data and @p textures.
		std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>> data;
		/// @brief Map of a data type to a texture.
		/// @note Don't use strings starting with "Pony_" as data types.
		/// @note Don't use the same key in the @p data and @p textures.
		std::unordered_map<std::string, std::shared_ptr<const ITexture>> textures;

		std::string name; ///< Material name.
	};
}
