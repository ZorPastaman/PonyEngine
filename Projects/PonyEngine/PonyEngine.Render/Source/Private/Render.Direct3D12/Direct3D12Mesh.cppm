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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Mesh;

import <array>;
import <cstddef>;
import <optional>;
import <span>;
import <string>;
import <unordered_map>;
import <vector>;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh.
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(std::span<const Microsoft::WRL::ComPtr<ID3D12Resource2>> buffers, const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& heap, 
			const std::unordered_map<std::string, D3D12_GPU_DESCRIPTOR_HANDLE>& handles, std::span<const UINT, 3> threadGroupCounts) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t BufferCount() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12Resource2& Buffer(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Buffer(std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& Heap() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12DescriptorHeap& Heap() const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> FindHandle(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const UINT, 3> ThreadGroupCounts() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12Mesh& operator =(const Direct3D12Mesh& other) noexcept = default;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> meshBuffers; ///< Mesh buffers.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> meshHeap; ///< Mesh descriptor heap.
		std::unordered_map<std::string, D3D12_GPU_DESCRIPTOR_HANDLE> meshHandles; ///< Mesh handles.
		std::array<UINT, 3> threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(std::span<const Microsoft::WRL::ComPtr<ID3D12Resource2>> buffers, const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& heap,
		const std::unordered_map<std::string, D3D12_GPU_DESCRIPTOR_HANDLE>& handles, const std::span<const UINT, 3> threadGroupCounts) noexcept :
		meshBuffers(buffers.begin(), buffers.end()),
		meshHeap(heap),
		meshHandles(handles)
	{
		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
	}

	std::size_t Direct3D12Mesh::BufferCount() const noexcept
	{
		return meshBuffers.size();
	}

	ID3D12Resource2& Direct3D12Mesh::Buffer(const std::size_t index) noexcept
	{
		return *meshBuffers[index].Get();
	}

	const ID3D12Resource2& Direct3D12Mesh::Buffer(const std::size_t index) const noexcept
	{
		return *meshBuffers[index].Get();
	}

	ID3D12DescriptorHeap& Direct3D12Mesh::Heap() noexcept
	{
		return *meshHeap.Get();
	}

	const ID3D12DescriptorHeap& Direct3D12Mesh::Heap() const noexcept
	{
		return *meshHeap.Get();
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Direct3D12Mesh::FindHandle(const std::string_view dataType) const noexcept
	{
		if (const auto position = std::ranges::find_if(meshHandles, [&](const std::pair<std::string, D3D12_GPU_DESCRIPTOR_HANDLE>& p) { return p.first == dataType; }); position != meshHandles.cend())
		{
			return position->second;
		}

		return std::nullopt;
	}

	std::span<const UINT, 3> Direct3D12Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Direct3D12Mesh::Name(std::string_view name)
	{
		// TODO: Seems buffers and handles must be united so that I can set dataTypes as their names.
	}
}
