/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ShaderDataMeta;

import std;

import :CBVParams;
import :IBuffer;

export namespace PonyEngine::RenderDevice
{
	struct EmptyShaderDataMeta final
	{
	};

	struct BufferCBVMeta final
	{
		const IBuffer* buffer = nullptr;
		CBVParams params;
	};

	using ShaderDataMeta = std::variant<EmptyShaderDataMeta, BufferCBVMeta>;
}
