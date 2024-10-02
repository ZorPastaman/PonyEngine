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

export module PonyEngine.Render.Direct3D12:Direct3D12IndexBuffer;

import :Direct3D12IndexFormat;

export namespace PonyEngine::Render
{
	class Direct3D12IndexBuffer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexBuffer(const Microsoft::WRL::ComPtr<ID3D12Resource2>& indexResource, const Direct3D12IndexFormat& indexFormat, UINT indexCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexBuffer(const Direct3D12IndexBuffer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexBuffer(Direct3D12IndexBuffer&& other) noexcept = default;

		~Direct3D12IndexBuffer() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2* GetIndexResource() const noexcept;

		[[nodiscard("Pure function")]]
		DXGI_FORMAT IndexFormat() const noexcept;
		[[nodiscard("Pure function")]]
		UINT IndexSize() const noexcept;
		[[nodiscard("Pure function")]]
		UINT IndexCount() const noexcept;

		Direct3D12IndexBuffer& operator =(const Direct3D12IndexBuffer& other) noexcept = default;
		Direct3D12IndexBuffer& operator =(Direct3D12IndexBuffer&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> indexResource;
		Direct3D12IndexFormat indexFormat;
		UINT indexCount;
	};
}

namespace PonyEngine::Render
{
	Direct3D12IndexBuffer::Direct3D12IndexBuffer(const Microsoft::WRL::ComPtr<ID3D12Resource2>& indexResource, const Direct3D12IndexFormat& indexFormat, const UINT indexCount) noexcept :
		indexResource(indexResource),
		indexFormat{indexFormat},
		indexCount{indexCount}
	{
	}

	ID3D12Resource2* Direct3D12IndexBuffer::GetIndexResource() const noexcept
	{
		return indexResource.Get();
	}

	DXGI_FORMAT Direct3D12IndexBuffer::IndexFormat() const noexcept
	{
		return indexFormat.IndexFormat();
	}

	UINT Direct3D12IndexBuffer::IndexSize() const noexcept
	{
		return indexFormat.IndexSize();
	}

	UINT Direct3D12IndexBuffer::IndexCount() const noexcept
	{
		return indexCount;
	}
}
