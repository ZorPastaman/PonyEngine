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

export module PonyEngine.Render.Direct3D12.Detail:Mesh;

import <array>;
import <cstddef>;
import <format>;
import <memory>;
import <optional>;
import <span>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import :Buffer;
import :DescriptorHeap;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 mesh.
	class Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Mesh(const std::unordered_map<std::string, std::pair<std::vector<std::shared_ptr<Buffer>>, UINT>>& data, const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts);
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh&) = delete;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::size_t> FindBufferCount(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<Buffer> FindBuffer(std::string_view dataType, std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<const Buffer> FindBuffer(std::string_view dataType, std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<UINT> FindHandleIndex(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> FindHandle(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		DescriptorHeap& Heap() noexcept;
		[[nodiscard("Pure function")]]
		const DescriptorHeap& Heap() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<UINT, 3> ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const UINT, 3> ThreadGroupCounts() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Mesh& operator =(const Mesh&) = delete;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> FindDataIndex(std::string_view dataType) const noexcept;

		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<std::shared_ptr<Buffer>>> meshBuffers; ///< Mesh buffers.
		std::vector<UINT> meshHandleIndices; ///< Mesh handle indices.
		std::shared_ptr<DescriptorHeap> meshHeap; ///< Mesh descriptor heap.

		std::array<UINT, 3> threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Mesh::Mesh(const std::unordered_map<std::string, std::pair<std::vector<std::shared_ptr<Buffer>>, UINT>>& data, const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts) :
		meshHeap(heap)
	{
		for (const auto& [dataType, dataPair] : data)
		{
			dataTypes.push_back(dataType);
			meshBuffers.push_back(dataPair.first);
			meshHandleIndices.push_back(dataPair.second);
		}

		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::optional<std::size_t> Mesh::FindBufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			return meshBuffers[dataIndex.value()].size();
		}

		return std::nullopt;
	}

	std::shared_ptr<Buffer> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			return meshBuffers[dataIndex.value()][index];
		}

		return nullptr;
	}

	std::shared_ptr<const Buffer> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			return meshBuffers[dataIndex.value()][index];
		}

		return nullptr;
	}

	std::optional<UINT> Mesh::FindHandleIndex(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			return meshHandleIndices[dataIndex.value()];
		}

		return std::nullopt;
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Mesh::FindHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<UINT> handleIndex = FindHandleIndex(dataType))
		{
			return meshHeap->CpuHandle(handleIndex.value());
		}

		return std::nullopt;
	}

	DescriptorHeap& Mesh::Heap() noexcept
	{
		return *meshHeap;
	}

	const DescriptorHeap& Mesh::Heap() const noexcept
	{
		return *meshHeap;
	}

	std::span<UINT, 3> Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	std::span<const UINT, 3> Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Mesh::Name(const std::string_view name)
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
				SetName(meshBuffers[i][j]->Data(), componentName);
			}
		}

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(meshHeap->Heap(), componentName);
	}

	std::optional<std::size_t> Mesh::FindDataIndex(const std::string_view dataType) const noexcept
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
