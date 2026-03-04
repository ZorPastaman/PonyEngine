/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ComponentMapping;

import :ComponentSwizzle;

export namespace PonyEngine::RenderDevice
{
	/// @brief Component mapping. It sets what data a shader will get in different channels.
	struct ComponentMapping final
	{
		ComponentSwizzle red = ComponentSwizzle::Red; ///< Red channel component.
		ComponentSwizzle green = ComponentSwizzle::Green; ///< Green channel component.
		ComponentSwizzle blue = ComponentSwizzle::Blue; ///< Blue channel component.
		ComponentSwizzle alpha = ComponentSwizzle::Alpha; ///< Alpha channel component.
	};
}
