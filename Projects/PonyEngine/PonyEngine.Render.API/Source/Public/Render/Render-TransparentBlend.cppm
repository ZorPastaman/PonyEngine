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
		BlendFactor sourceBlend;
		BlendFactor destinationBlend;
		BlendOperation blendOperation;

		BlendFactor sourceBlendAlpha;
		BlendFactor destinationBlendAlpha;
		BlendOperation blendOperationAlpha;
	};
}
