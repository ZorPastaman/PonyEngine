/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:TransparentBlend;

import :BlendFactor;
import :BlendOperation;

export namespace PonyEngine::Render
{
	struct TransparentBlend final
	{
		BlendFactor sourceBlend = BlendFactor::One;
		BlendFactor destinationBlend = BlendFactor::Zero;
		BlendOperation blendOperation = BlendOperation::Add;

		BlendFactor sourceBlendAlpha = BlendFactor::One;
		BlendFactor destinationBlendAlpha = BlendFactor::Zero;
		BlendOperation blendOperationAlpha = BlendOperation::Add;
	};
}
