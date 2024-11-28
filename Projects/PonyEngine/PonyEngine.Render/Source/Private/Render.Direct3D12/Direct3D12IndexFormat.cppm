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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12IndexFormat;

import <stdexcept>;

import PonyBase.StringUtility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 index format.
	class Direct3D12IndexFormat final
	{
	public:
		/// @brief Creates a @p Direct3D12IndexFormat.
		/// @param indexSize Index size in bytes. Must be 2 or 4.
		[[nodiscard("Pure constructor")]]
		constexpr explicit Direct3D12IndexFormat(UINT indexSize);
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12IndexFormat(const Direct3D12IndexFormat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12IndexFormat(Direct3D12IndexFormat&& other) noexcept = default;

		constexpr ~Direct3D12IndexFormat() noexcept = default;

		/// @brief Gets the index size.
		/// @return Index size in bytes.
		[[nodiscard("Pure function")]]
		constexpr UINT IndexSize() const noexcept;
		/// @brief Gets the index format.
		/// @return Index format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT IndexFormat() const noexcept;

		constexpr Direct3D12IndexFormat& operator =(const Direct3D12IndexFormat& other) noexcept = default;
		constexpr Direct3D12IndexFormat& operator =(Direct3D12IndexFormat&&) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Direct3D12IndexFormat&) const noexcept = default;

	private:
		UINT indexSize; ///< Index size.
		DXGI_FORMAT indexFormat; ///< Index format.
	};
}

namespace PonyEngine::Render
{
	/// @brief Gets an index format by the index size.
	/// @param indexSize Index size in bytes. Must be 2 or 4.
	/// @return Index format.
	[[nodiscard("Pure constructor")]]
	constexpr DXGI_FORMAT GetFormat(UINT indexSize); // TODO: Move functions like this to Utility sub-module.

	constexpr Direct3D12IndexFormat::Direct3D12IndexFormat(const UINT indexSize) :
		indexSize{indexSize},
		indexFormat{GetFormat(this->indexSize)}
	{
	}

	constexpr UINT Direct3D12IndexFormat::IndexSize() const noexcept
	{
		return indexSize;
	}

	constexpr DXGI_FORMAT Direct3D12IndexFormat::IndexFormat() const noexcept
	{
		return indexFormat;
	}

	constexpr DXGI_FORMAT GetFormat(const UINT indexSize)
	{
		switch (indexSize)
		{
		case 2:
			return DXGI_FORMAT_R16_UINT;
		case 4:
			return DXGI_FORMAT_R32_UINT;
		default: [[unlikely]]
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported index size. Index size: '{}'. But supported index sizes are 2 and 4 only.", indexSize));
		}
	}
}
