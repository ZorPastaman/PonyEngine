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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12IndexArray;

import :Direct3D12IndexFormat;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 index array.
	class Direct3D12IndexArray final
	{
	public:
		/// @brief Creates a @p Direct3D12IndexArray.
		/// @param indexResource Index resource.
		/// @param indexFormat Index format.
		/// @param indexCount Index count.
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexArray(ID3D12Resource2& indexResource, const Direct3D12IndexFormat& indexFormat, UINT indexCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexArray(const Direct3D12IndexArray& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexArray(Direct3D12IndexArray&& other) noexcept = default;

		~Direct3D12IndexArray() noexcept = default;

		/// @brief Gets the index resource.
		/// @return Index resource.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& IndexResource() noexcept;
		/// @brief Gets the index resource.
		/// @return Index resource.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& IndexResource() const noexcept;

		/// @brief Gets the index format.
		/// @return Index format.
		[[nodiscard("Pure function")]]
		DXGI_FORMAT IndexFormat() const noexcept;
		/// @brief Gets the index size.
		/// @return Index size.
		[[nodiscard("Pure function")]]
		UINT IndexSize() const noexcept;
		/// @brief Gets the index count.
		/// @return Index count.
		[[nodiscard("Pure function")]]
		UINT IndexCount() const noexcept;

		Direct3D12IndexArray& operator =(const Direct3D12IndexArray& other) noexcept = default;
		Direct3D12IndexArray& operator =(Direct3D12IndexArray&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> indexResource; ///< Index resource.
		Direct3D12IndexFormat indexFormat; ///< Index format.
		UINT indexCount; ///< Index count.
	};
}

namespace PonyEngine::Render
{
	Direct3D12IndexArray::Direct3D12IndexArray(ID3D12Resource2& indexResource, const Direct3D12IndexFormat& indexFormat, const UINT indexCount) noexcept :
		indexResource(&indexResource),
		indexFormat(indexFormat),
		indexCount{indexCount}
	{
	}

	ID3D12Resource2& Direct3D12IndexArray::IndexResource() noexcept
	{
		return *indexResource.Get();
	}

	const ID3D12Resource2& Direct3D12IndexArray::IndexResource() const noexcept
	{
		return *indexResource.Get();
	}

	DXGI_FORMAT Direct3D12IndexArray::IndexFormat() const noexcept
	{
		return indexFormat.IndexFormat();
	}

	UINT Direct3D12IndexArray::IndexSize() const noexcept
	{
		return indexFormat.IndexSize();
	}

	UINT Direct3D12IndexArray::IndexCount() const noexcept
	{
		return indexCount;
	}
}
