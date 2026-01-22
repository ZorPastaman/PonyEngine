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
	struct ComponentMapping final
	{
		ComponentSwizzle red = ComponentSwizzle::Red;
		ComponentSwizzle green = ComponentSwizzle::Green;
		ComponentSwizzle blue = ComponentSwizzle::Blue;
		ComponentSwizzle alpha = ComponentSwizzle::Alpha;
	};
}
