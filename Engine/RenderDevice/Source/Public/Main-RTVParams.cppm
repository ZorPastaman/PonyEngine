/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RTVParams;

import :RTVLayout;
import :TextureDimension;
import :TextureFormatId;

export namespace PonyEngine::RenderDevice
{
	struct RTVParams final
	{
		TextureFormatId format;
		bool srgb = false;
		TextureDimension dimension = TextureDimension::Texture2D;
		RTVLayout layout;
	};
}
