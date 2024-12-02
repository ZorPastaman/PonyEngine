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

import :Direct3D12Utility;

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
}
