/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Texture;

import :Resource;

export namespace PonyEngine::Render::Direct3D12
{
	class Texture final : public Resource
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Texture(ID3D12Resource2& resource) noexcept;
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		virtual ~Texture() noexcept override = default;

		Texture& operator =(const Texture&) = delete;
		Texture& operator =(Texture&&) = delete;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Texture::Texture(ID3D12Resource2& resource) noexcept :
		Resource(resource)
	{
	}
}
