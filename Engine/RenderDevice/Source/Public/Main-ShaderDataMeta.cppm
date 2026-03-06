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
	/// @brief Empty shader data meta. It means no shader data view was created.
	struct EmptyShaderDataMeta final
	{
	};

	/// @brief Shader data resource meta.
	/// @tparam Resource Resource type.
	/// @tparam Params View parameter type.
	template<std::derived_from<IResource> Resource, typename Params>
	struct ShaderDataResourceMeta final
	{
		const Resource* resource = nullptr; ///< Target resource. May be nullptr.
		Params params; ///< View parameters.
	};
	using CBVMeta = ShaderDataResourceMeta<IBuffer, CBVParams>; ///< Constant buffer view meta.
	using BufferSRVMeta = ShaderDataResourceMeta<IBuffer, BufferSRVParams>; ///< Buffer shader resource view meta.
	using TextureSRVMeta = ShaderDataResourceMeta<ITexture, TextureSRVParams>; ///< Texture shader resource view meta.
	using BufferUAVMeta = ShaderDataResourceMeta<IBuffer, BufferUAVParams>; ///< Buffer unordered access view meta.
	using TextureUAVMeta = ShaderDataResourceMeta<ITexture, TextureUAVParams>; /// Texture unordered access view meta.

	using ShaderDataMeta = std::variant<EmptyShaderDataMeta, CBVMeta, BufferSRVMeta, TextureSRVMeta, BufferUAVMeta, TextureUAVMeta>; ///< Shader data meta.
}
