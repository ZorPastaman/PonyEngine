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

export namespace PonyEngine::Render
{
	struct MaterialParams final
	{
		std::string rootSignatureShader;
		std::string amplificationShader;
		std::string meshShader;
		std::string pixelShader;
		std::unordered_map<std::string, std::uint32_t> dataSlots;
		std::array<std::uint32_t, 3> threadGroupCounts;
		std::string name;
	};
}
