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
		Mesh(const std::unordered_map<std::string, std::vector<std::shared_ptr<Buffer>>>& data, const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts);
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
		std::size_t BufferCount() const noexcept;

		[[nodiscard("Pure function")]]
		const std::shared_ptr<Buffer>* FindBuffer(std::string_view dataType, std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<const Buffer> FindBuffer(std::string_view dataType, std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<UINT> FindHandleIndex(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> FindCpuHandle(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> FindGpuHandle(std::string_view dataType) const noexcept;

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
		std::vector<std::vector<std::shared_ptr<Buffer>>> buffers; ///< Buffers.
		std::vector<UINT> handleIndices; ///< Handle indices.
		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.

		std::array<UINT, 3> threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Mesh::Mesh(const std::unordered_map<std::string, std::vector<std::shared_ptr<Buffer>>>& data, const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts) :
		heap(heap)
	{
		for (UINT handleIndex = 0u; const auto& [dataType, dataBuffers] : data)
		{
			dataTypes.push_back(dataType);
			buffers.push_back(dataBuffers);
			handleIndices.push_back(handleIndex);
			handleIndex += static_cast<UINT>(dataBuffers.size());
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
			return buffers[dataIndex.value()].size();
		}

		return std::nullopt;
	}

	std::size_t Mesh::BufferCount() const noexcept
	{
		std::size_t bufferCount = 0;
		for (const std::vector<std::shared_ptr<Buffer>>& dataBuffer : buffers)
		{
			bufferCount += dataBuffer.size();
		}

		return bufferCount;
	}

	const std::shared_ptr<Buffer>* Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			if (const std::vector<std::shared_ptr<Buffer>>& dataBuffers = buffers[dataIndex.value()]; index < dataBuffers.size())
			{
				return &dataBuffers[index];
			}
		}

		return nullptr;
	}

	std::shared_ptr<const Buffer> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			if (const std::vector<std::shared_ptr<Buffer>>& dataBuffers = buffers[dataIndex.value()]; index < dataBuffers.size())
			{
				return dataBuffers[index];
			}
		}

		return nullptr;
	}

	std::optional<UINT> Mesh::FindHandleIndex(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = FindDataIndex(dataType))
		{
			return handleIndices[dataIndex.value()];
		}

		return std::nullopt;
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Mesh::FindCpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<UINT> handleIndex = FindHandleIndex(dataType))
		{
			return heap->CpuHandle(handleIndex.value());
		}

		return std::nullopt;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Mesh::FindGpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<UINT> handleIndex = FindHandleIndex(dataType))
		{
			return heap->GpuHandle(handleIndex.value());
		}

		return std::nullopt;
	}

	DescriptorHeap& Mesh::Heap() noexcept
	{
		return *heap;
	}

	const DescriptorHeap& Mesh::Heap() const noexcept
	{
		return *heap;
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
		componentName.reserve(name.size() + bufferFormat.size());

		for (std::size_t i = 0; i < buffers.size(); ++i)
		{
			for (std::size_t j = 0; j < buffers[i].size(); ++j)
			{
				componentName.resize(std::min(componentName.capacity(), std::formatted_size(bufferFormat, name, i, j)));
				std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, i, j);
				SetName(buffers[i][j]->Data(), componentName);
			}
		}

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(heap->Heap(), componentName);
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
