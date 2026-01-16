/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureSupportRequest;

import :TextureFormatId;
import :TextureDimension;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	struct TextureSupportRequest final
	{
		TextureFormatId format;
		TextureDimension dimension = TextureDimension::Texture2D;
		TextureUsage usage = TextureUsage::None;
	};
}
