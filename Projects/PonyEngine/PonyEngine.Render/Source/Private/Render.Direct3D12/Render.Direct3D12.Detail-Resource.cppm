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

export module PonyEngine.Render.Direct3D12.Detail:Resource;

import <string_view>;

import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	class Resource
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Resource(ID3D12Resource2& resource) noexcept;
		Resource(const Resource&) = delete;
		Resource(Resource&&) = delete;

		virtual ~Resource() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Data() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Data() const noexcept;

		void Name(std::string_view name);

		Resource& operator =(const Resource&) = delete;
		Resource& operator =(Resource&&) = delete;

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Resource::Resource(ID3D12Resource2& resource) noexcept :
		resource(&resource)
	{
	}

	ID3D12Resource2& Resource::Data() noexcept
	{
		return *resource.Get();
	}

	const ID3D12Resource2& Resource::Data() const noexcept
	{
		return *resource.Get();
	}

	void Resource::Name(const std::string_view name)
	{
		SetName(*resource.Get(), name);
	}
}
