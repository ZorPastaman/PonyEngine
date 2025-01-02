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
import <format>;
import <optional>;
import <span>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import :Direct3D12ObjectUtility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh.
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const std::unordered_map<std::string, std::pair<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>, D3D12_GPU_DESCRIPTOR_HANDLE>>& data, ID3D12DescriptorHeap& heap, std::span<const UINT, 3> threadGroupCounts);
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::size_t> BufferCount(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12Resource2* FindBuffer(std::string_view dataType, std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2* FindBuffer(std::string_view dataType, std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> FindHandle(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& Heap() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12DescriptorHeap& Heap() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<UINT, 3> ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const UINT, 3> ThreadGroupCounts() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12Mesh& operator =(const Direct3D12Mesh&) = delete;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> IndexOf(std::string_view dataType) const noexcept;

		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>> meshBuffers; ///< Mesh buffers.
		std::vector<D3D12_GPU_DESCRIPTOR_HANDLE> meshHandles; ///< Mesh handles.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> meshHeap; ///< Mesh descriptor heap.

		std::array<UINT, 3> threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(const std::unordered_map<std::string, std::pair<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>, D3D12_GPU_DESCRIPTOR_HANDLE>>& data, ID3D12DescriptorHeap& heap, std::span<const UINT, 3> threadGroupCounts) :
		meshHeap(&heap)
	{
		for (const auto& [dataType, dataPair] : data)
		{
			dataTypes.push_back(dataType);
			meshBuffers.push_back(dataPair.first);
			meshHandles.push_back(dataPair.second);
		}

		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
	}

	std::span<const std::string> Direct3D12Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::optional<std::size_t> Direct3D12Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> index = IndexOf(dataType))
		{
			return meshBuffers[index.value()].size();
		}

		return std::nullopt;
	}

	ID3D12Resource2* Direct3D12Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const std::optional<std::size_t> dataTypeIndex = IndexOf(dataType))
		{
			return meshBuffers[dataTypeIndex.value()][index].Get();
		}

		return nullptr;
	}

	const ID3D12Resource2* Direct3D12Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> dataTypeIndex = IndexOf(dataType))
		{
			return meshBuffers[dataTypeIndex.value()][index].Get();
		}

		return nullptr;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Direct3D12Mesh::FindHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> dataTypeIndex = IndexOf(dataType))
		{
			return meshHandles[dataTypeIndex.value()];
		}

		return std::nullopt;
	}

	ID3D12DescriptorHeap& Direct3D12Mesh::Heap() noexcept
	{
		return *meshHeap.Get();
	}

	const ID3D12DescriptorHeap& Direct3D12Mesh::Heap() const noexcept
	{
		return *meshHeap.Get();
	}

	std::span<UINT, 3> Direct3D12Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	std::span<const UINT, 3> Direct3D12Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Direct3D12Mesh::Name(const std::string_view name)
	{
		constexpr std::string_view bufferFormat = "{} - MeshBuffer{}-{}";
		constexpr std::string_view heapName = " - MeshHeap";

		auto componentName = std::string();
		componentName.reserve(name.size() + bufferFormat.size() + 3);

		for (std::size_t i = 0; i < meshBuffers.size(); ++i)
		{
			for (std::size_t j = 0; j < meshBuffers[i].size(); ++j)
			{
				componentName.resize(std::min(componentName.capacity(), std::formatted_size(bufferFormat, name, i, j)));
				std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, i, j);
				SetName(*meshBuffers[i][j].Get(), componentName);
			}
		}

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(*meshHeap.Get(), componentName);
	}

	std::optional<std::size_t> Direct3D12Mesh::IndexOf(const std::string_view dataType) const noexcept
	{
		for (std::size_t i = 0; i < dataTypes.size(); ++i)
		{
			if (dataTypes[i] == dataType)
			{
				return i;
			}
		}

		return std::nullopt;
	}
}
