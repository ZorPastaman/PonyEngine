/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:MaterialParams;

import <array>;
import <string>;
import <unordered_map>;

import :Blend;
import :Rasterizer;
import :ThreadGroupCounts;

export namespace PonyEngine::Render
{
	struct MaterialParams final
	{
		std::string rootSignatureShader;
		std::string amplificationShader;
		std::string meshShader;
		std::string pixelShader;

		Blend blend;
		Rasterizer rasterizer;

		std::unordered_map<std::string, std::uint32_t> dataSlots;

		ThreadGroupCounts threadGroupCounts;

		std::string name;
	};
}
