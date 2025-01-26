/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:MeshParams;

import <array>;
import <cstdint>;
import <string>;
import <unordered_map>;
import <vector>;

import PonyBase.Container;

export namespace PonyEngine::Render
{
	struct MeshParams final
	{
		std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>> bufferTables;
		std::array<std::uint32_t, 3> threadGroupCounts;
		std::string name;
	};
}
