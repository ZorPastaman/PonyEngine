/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Blend;

import <variant>;

import :LogicBlend;
import :OpaqueBlend;
import :TransparentBlend;

export namespace PonyEngine::Render
{
	struct Blend final
	{
		std::variant<OpaqueBlend, TransparentBlend, LogicBlend> renderTargetBlend;
		bool alphaToCoverage;
	};
}
