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

export module  PonyEngine.Render.Direct3D12:Direct3D12IndexFormat;

import <stdexcept>;

export namespace PonyEngine::Render
{
	class Direct3D12IndexFormat final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12IndexFormat(UINT indexSize);
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexFormat(const Direct3D12IndexFormat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexFormat(Direct3D12IndexFormat&& other) noexcept = default;

		~Direct3D12IndexFormat() noexcept = default;

		[[nodiscard("Pure function")]]
		UINT IndexSize() const noexcept;
		[[nodiscard("Pure function")]]
		DXGI_FORMAT IndexFormat() const noexcept;

		Direct3D12IndexFormat& operator =(const Direct3D12IndexFormat& other) noexcept = default;
		Direct3D12IndexFormat& operator =(Direct3D12IndexFormat&&) noexcept = default;

	private:
		[[nodiscard("Pure constructor")]]
		static DXGI_FORMAT GetFormat(UINT indexSize);

		UINT indexSize;
		DXGI_FORMAT indexFormat;
	};
}

namespace PonyEngine::Render
{
	Direct3D12IndexFormat::Direct3D12IndexFormat(const UINT indexSize) :
		indexSize{indexSize},
		indexFormat{GetFormat(this->indexSize)}
	{
	}

	UINT Direct3D12IndexFormat::IndexSize() const noexcept
	{
		return indexSize;
	}

	DXGI_FORMAT Direct3D12IndexFormat::IndexFormat() const noexcept
	{
		return indexFormat;
	}

	DXGI_FORMAT Direct3D12IndexFormat::GetFormat(const UINT indexSize)
	{
		switch (indexSize)
		{
		case 1:
			return DXGI_FORMAT_R8_UINT;
		case 2:
			return DXGI_FORMAT_R16_UINT;
		case 4:
			return DXGI_FORMAT_R32_UINT;
		default: [[unlikely]]
			throw std::invalid_argument("Unsupported index size.");
		}
	}
}
