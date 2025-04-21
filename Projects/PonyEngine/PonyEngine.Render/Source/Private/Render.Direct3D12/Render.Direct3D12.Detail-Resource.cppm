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
	/// @brief Direct3D12 resource wrapper.
	class Resource
	{
	public:
		/// @brief Creates a resource.
		/// @param resource Direct3D12 resource.
		[[nodiscard("Pure constructor")]]
		explicit Resource(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		Resource(const Resource& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Resource(Resource&& other) noexcept = default;

		virtual ~Resource() noexcept = default;

		/// @brief Gets the Direct3D12 resource.
		/// @return Direct3D12 resource.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& Data() noexcept;
		/// @brief Gets the Direct3D12 resource.
		/// @return Direct3D12 resource.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Data() const noexcept;

		/// @brief Sets the resource name.
		/// @param name Resource name to set.
		void Name(std::string_view name);

		Resource& operator =(const Resource& other) noexcept = default;
		Resource& operator =(Resource&& other) noexcept = default;

	protected:
		/// @brief Maps the resource to CPU-accessible memory.
		/// @note You must unmap the resource after using it.
		/// @return A pointer to the mapped memory.
		[[nodiscard("Redundant call")]]
		void* Map();
		/// @brief Maps the resource to CPU-accessible memory.
		/// @note You must unmap the resource after using it.
		/// @return A pointer to the mapped memory.
		[[nodiscard("Redundant call")]]
		const void* Map() const;
		/// @brief Unmaps the resource from CPU-accessible memory.
		void Unmap() const;

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource; ///< Direct3D12 resource.
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

	void* Resource::Map()
	{
		void* resourceData;
		if (const HRESULT result = resource->Map(0, nullptr, &resourceData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resourceData;
	}

	const void* Resource::Map() const
	{
		void* resourceData;
		if (const HRESULT result = resource->Map(0, nullptr, &resourceData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resourceData;
	}

	void Resource::Unmap() const
	{
		resource->Unmap(0, nullptr);
	}
}
