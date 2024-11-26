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

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 index format.
	class Direct3D12IndexFormat final
	{
	public:
		/// @brief Creates a @p Direct3D12IndexFormat.
		/// @param indexSize Index size in bytes. Must be 2 or 4.
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12IndexFormat(UINT indexSize);
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexFormat(const Direct3D12IndexFormat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexFormat(Direct3D12IndexFormat&& other) noexcept = default;

		~Direct3D12IndexFormat() noexcept = default;

		/// @brief Gets the index size.
		/// @return Index size in bytes.
		[[nodiscard("Pure function")]]
		UINT IndexSize() const noexcept;
		/// @brief Gets the index format.
		/// @return Index format.
		[[nodiscard("Pure function")]]
		DXGI_FORMAT IndexFormat() const noexcept;

		Direct3D12IndexFormat& operator =(const Direct3D12IndexFormat& other) noexcept = default;
		Direct3D12IndexFormat& operator =(Direct3D12IndexFormat&&) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Direct3D12IndexFormat&) const noexcept = default;

	private:
		UINT indexSize; ///< Index size.
	};
}

namespace PonyEngine::Render
{
	/// @brief Gets an index format by the index size.
	/// @param indexSize Index size in bytes. Must be 2 or 4.
	/// @return Index format.
	[[nodiscard("Pure constructor")]]
	DXGI_FORMAT GetFormat(UINT indexSize); // TODO: Move functions like this to Utility sub-module.

	Direct3D12IndexFormat::Direct3D12IndexFormat(const UINT indexSize) :
		indexSize{indexSize}
	{
		[[maybe_unused]] const DXGI_FORMAT format = GetFormat(indexSize); // Throws an exception if the indexSize is incorrect to invalidate the instance.
	}

	UINT Direct3D12IndexFormat::IndexSize() const noexcept
	{
		return indexSize;
	}

	DXGI_FORMAT Direct3D12IndexFormat::IndexFormat() const noexcept
	{
		return GetFormat(indexSize);
	}

	DXGI_FORMAT GetFormat(const UINT indexSize)
	{
		switch (indexSize)
		{
		case 2:
			return DXGI_FORMAT_R16_UINT;
		case 4:
			return DXGI_FORMAT_R32_UINT;
		default: [[unlikely]]
			throw std::invalid_argument("Unsupported index size.");
		}
	}
}
