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
	using BufferCBVMeta = ResourceViewMeta<IBuffer, CBVParams>;
	using BufferSRVMeta = ResourceViewMeta<IBuffer, BufferSRVParams>;
	using Texture1DSRVMeta = ResourceViewMeta<ITexture, Texture1DSRVParams>;
	using Texture1DArraySRVMeta = ResourceViewMeta<ITexture, Texture1DArraySRVParams>;
	using Texture2DSRVMeta = ResourceViewMeta<ITexture, Texture2DSRVParams>;
	using Texture2DArraySRVMeta = ResourceViewMeta<ITexture, Texture2DArraySRVParams>;
	using Texture2DMSSRVMeta = ResourceViewMeta<ITexture, Texture2DMSSRVParams>;
	using Texture2DMSArraySRVMeta = ResourceViewMeta<ITexture, Texture2DMSArraySRVParams>;
	using Texture3DSRVMeta = ResourceViewMeta<ITexture, Texture3DSRVParams>;
	using TextureCubeSRVMeta = ResourceViewMeta<ITexture, TextureCubeSRVParams>;
	using TextureCubeArraySRVMeta = ResourceViewMeta<ITexture, TextureCubeArraySRVParams>;

	using ShaderDataMeta = std::variant<EmptyShaderDataMeta, BufferCBVMeta, BufferSRVMeta, Texture1DSRVMeta, Texture1DArraySRVMeta, Texture2DSRVMeta, Texture2DArraySRVMeta,
		Texture2DMSSRVMeta, Texture2DMSArraySRVMeta, Texture3DSRVMeta, TextureCubeSRVMeta, TextureCubeArraySRVMeta>;
}
