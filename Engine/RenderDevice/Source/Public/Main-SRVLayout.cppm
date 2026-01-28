/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SRVLayout;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	struct TextureSingleSRVLayout final
	{
		MipRange mipRange;
	};
	struct TextureArraySRVLayout final
	{
		MipRange mipRange;
		ArrayRange arrayRange;
	};
	struct TextureMSSRVLayout final
	{
	};
	struct TextureMSArraySRVLayout final
	{
		ArrayRange arrayRange;
	};
	using TextureSRVLayout = std::variant<TextureSingleSRVLayout, TextureArraySRVLayout, TextureMSSRVLayout, TextureMSArraySRVLayout>;
}
