/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Texture;

import :Resource;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 texture wrapper.
	class Texture final : public Resource
	{
	public:
		/// @brief Creates a texture.
		/// @param resource Texture resource.
		[[nodiscard("Pure constructor")]]
		explicit Texture(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		Texture(const Texture& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Texture(Texture&& other) noexcept = default;

		virtual ~Texture() noexcept override = default;

		Texture& operator =(const Texture& other) noexcept = default;
		Texture& operator =(Texture&& other) noexcept = default;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Texture::Texture(ID3D12Resource2& resource) noexcept :
		Resource(resource)
	{
		const D3D12_RESOURCE_DIMENSION dimension = resource.GetDesc1().Dimension;
		assert((dimension == D3D12_RESOURCE_DIMENSION_TEXTURE1D || dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D || dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D) 
			&& "The resource has a wrong dimension.");
	}
}
