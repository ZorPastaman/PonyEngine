/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DSVParams;

import :DSVDimension;
import :DSVFlag;
import :DSVLayout;
import :TextureFormatId;

export namespace PonyEngine::RenderDevice
{
	struct DSVParams final
	{
		TextureFormatId format;
		DSVDimension dimension = DSVDimension::Texture2D;
		DSVFlag flags = DSVFlag::None;
		DSVLayout layout;
	};
}
