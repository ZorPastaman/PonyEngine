/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RootSignatureParams;

import <memory>;
import <string>;
import <vector>;

import :IShader;

export namespace PonyEngine::Render
{
	/// @brief Root signature parameters.
	struct RootSignatureParams final
	{
		std::shared_ptr<const IShader> shader; ///< Root signature shader.
		std::vector<std::string> slots; ///< Root signature slots.

		std::string name; ///< Root signature name.
	};
}
