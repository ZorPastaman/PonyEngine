/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:Layout;

import std;

export namespace PonyEngine::Render
{
	enum class Layout : std::uint8_t
	{
		Common,
		Present,
		ShaderResource,
		RenderTarget,
		DepthStencilRead,
		DepthStencilWrite,
		UnorderedAccess,
		CopySource,
		CopyDestination,
		ResolveSource,
		ResolveDestination
	};
}
