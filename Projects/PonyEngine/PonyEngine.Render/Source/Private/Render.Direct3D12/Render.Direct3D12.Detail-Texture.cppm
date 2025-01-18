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

export namespace PonyEngine::Render::Direct3D12
{
	class Texture final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Texture(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		Texture(const Texture& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Texture(Texture&& other) noexcept = default;

		~Texture() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Resource() const noexcept;

		Texture& operator =(const Texture& other) noexcept = default;
		Texture& operator =(Texture&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
	};


}

namespace PonyEngine::Render::Direct3D12
{
	Texture::Texture(ID3D12Resource2& resource) noexcept :
		resource(&resource)
	{
	}

	ID3D12Resource2& Texture::Resource() noexcept
	{
		return *resource.Get();
	}

	const ID3D12Resource2& Texture::Resource() const noexcept
	{
		return *resource.Get();
	}
}
