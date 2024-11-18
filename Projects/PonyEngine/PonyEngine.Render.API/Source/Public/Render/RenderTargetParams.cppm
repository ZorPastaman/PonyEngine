/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderTargetParams;

import PonyMath.Color;

export namespace PonyEngine::Render
{
	struct RenderTargetParams final
	{
		PonyMath::Color::RGBA<float> clearColor = PonyMath::Color::RGBA<float>::Predefined::Black;
	};
}
