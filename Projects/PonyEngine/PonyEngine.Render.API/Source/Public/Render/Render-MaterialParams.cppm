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

import :PipelineState;

export namespace PonyEngine::Render
{
	/// @brief Material parameters.
	struct MaterialParams final
	{
		std::shared_ptr<PipelineState> pipelineState; ///< Pipeline state.

		/// @brief Map of data types to data tables.
		/// @note Don't use strings starting with "Pony_" as data types.
		std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>> dataTables;

		std::string name; ///< Material name.
	};
}
