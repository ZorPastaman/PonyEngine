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
import :ITexture;
import :SRVParams;
import :UAVParams;

export namespace PonyEngine::RenderDevice
{
	struct EmptyShaderDataMeta final
	{
	};

	template<std::derived_from<IResource> Resource, typename Params>
	struct ResourceViewMeta final
	{
		const Resource* resource = nullptr;
		Params params;
	};
	using CBVMeta = ResourceViewMeta<IBuffer, CBVParams>;
	using BufferSRVMeta = ResourceViewMeta<IBuffer, BufferSRVParams>;
	using TextureSRVMeta = ResourceViewMeta<ITexture, TextureSRVParams>;
	using BufferUAVMeta = ResourceViewMeta<IBuffer, BufferUAVParams>;
	using TextureUAVMeta = ResourceViewMeta<ITexture, TextureUAVParams>;

	using ShaderDataMeta = std::variant<EmptyShaderDataMeta, CBVMeta, BufferSRVMeta, TextureSRVMeta, BufferUAVMeta, TextureUAVMeta>;
}
