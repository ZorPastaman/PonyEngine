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
import <optional>;
import <string>;
import <unordered_map>;
import <vector>;

import PonyBase.Container;

import PonyMath.Shape;

import PonyShader.Core;

export namespace PonyEngine::Render
{
	struct MeshParams final
	{
		std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>> bufferTables;
		PonyShader::Core::ThreadGroupCounts threadGroupCounts;
		std::optional<PonyMath::Shape::Box<float>> boundingBox = std::nullopt;
		std::string name;
	};
}
