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
		Mesh(std::span<const std::string> dataTypes, std::span<const std::size_t> bufferOffsets, std::span<const std::shared_ptr<class Buffer>> buffers, 
			const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts);
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::optional<std::size_t> FindDataIndex(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t DataCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t BufferOffset(std::size_t dataIndex) const;

		[[nodiscard("Pure function")]]
		class Buffer& Buffer(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer& Buffer(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<class Buffer>& BufferShared(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const class Buffer>& BufferShared(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t BufferCount() const noexcept;

		[[nodiscard("Pure function")]]
		class Buffer& Buffer(std::size_t dataIndex, std::size_t bufferIndex) noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer& Buffer(std::size_t dataIndex, std::size_t bufferIndex) const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<class Buffer>& BufferShared(std::size_t dataIndex, std::size_t bufferIndex) noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const class Buffer>& BufferShared(std::size_t dataIndex, std::size_t bufferIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t BufferCount(std::size_t dataIndex) const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(std::size_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(std::size_t dataIndex) const noexcept;

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

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::size_t> bufferOffsets;
		std::vector<std::shared_ptr<class Buffer>> buffers; ///< Buffers.
		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.

		std::array<UINT, 3> threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Mesh::Mesh(const std::span<const std::string> dataTypes, const std::span<const std::size_t> bufferOffsets, const std::span<const std::shared_ptr<class Buffer>> buffers, 
		const std::shared_ptr<DescriptorHeap>& heap, std::span<const UINT, 3> threadGroupCounts) :
		dataTypes(dataTypes.begin(), dataTypes.end()),
		bufferOffsets(bufferOffsets.begin(), bufferOffsets.end()),
		buffers(buffers.begin(), buffers.end()),
		heap(heap)
	{
		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
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

	std::string_view Mesh::DataType(const std::size_t index) const noexcept
	{
		return dataTypes[index];
	}

	std::size_t Mesh::DataCount() const noexcept
	{
		return dataTypes.size();
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::size_t Mesh::BufferOffset(const std::size_t dataIndex) const
	{
		return bufferOffsets[dataIndex];
	}

	class Buffer& Mesh::Buffer(const std::size_t index) noexcept
	{
		return *BufferShared(index);
	}

	const class Buffer& Mesh::Buffer(const std::size_t index) const noexcept
	{
		return *BufferShared(index);
	}

	const std::shared_ptr<class Buffer>& Mesh::BufferShared(const std::size_t index) noexcept
	{
		return buffers[index];
	}

	const std::shared_ptr<const class Buffer>& Mesh::BufferShared(const std::size_t index) const noexcept
	{
		return buffers[index];
	}

	std::size_t Mesh::BufferCount() const noexcept
	{
		return buffers.size();
	}

	class Buffer& Mesh::Buffer(const std::size_t dataIndex, const std::size_t bufferIndex) noexcept
	{
		return *BufferShared(dataIndex, bufferIndex);
	}

	const class Buffer& Mesh::Buffer(const std::size_t dataIndex, const std::size_t bufferIndex) const noexcept
	{
		return *BufferShared(dataIndex, bufferIndex);
	}

	const std::shared_ptr<class Buffer>& Mesh::BufferShared(const std::size_t dataIndex, const std::size_t bufferIndex) noexcept
	{
		return buffers[bufferOffsets[dataIndex] + bufferIndex];
	}

	const std::shared_ptr<const class Buffer>& Mesh::BufferShared(const std::size_t dataIndex, const std::size_t bufferIndex) const noexcept
	{
		return buffers[bufferOffsets[dataIndex] + bufferIndex];
	}

	std::size_t Mesh::BufferCount(const std::size_t dataIndex) const noexcept
	{
		const std::size_t nextOffset = dataIndex < bufferOffsets.size() - 1 ? bufferOffsets[dataIndex + 1]  : buffers.size();

		return nextOffset - bufferOffsets[dataIndex];
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Mesh::CpuHandle(const std::size_t dataIndex) const noexcept
	{
		return heap->CpuHandle(bufferOffsets[dataIndex]);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Mesh::GpuHandle(const std::size_t dataIndex) const noexcept
	{
		return heap->GpuHandle(bufferOffsets[dataIndex]);
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
		constexpr std::string_view bufferFormat = "{}-{}{}";

		std::size_t longestDataType = 0;
		for (const std::string& dataType : dataTypes)
		{
			longestDataType = std::max(longestDataType, dataType.size());
		}

		auto componentName = std::string();
		componentName.reserve(name.size() + longestDataType);
		for (std::size_t dataTypeIndex = 0; dataTypeIndex < dataTypes.size(); ++dataTypeIndex)
		{
			std::size_t bufferIndex = bufferOffsets[dataTypeIndex];
			const std::size_t bufferCount = BufferCount(dataTypeIndex) + bufferIndex;

			for (; bufferIndex < bufferCount; ++bufferIndex)
			{
				componentName.resize(std::formatted_size(bufferFormat, name, dataTypes[dataTypeIndex], bufferIndex));
				std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, dataTypes[dataTypeIndex], bufferIndex);
				buffers[bufferIndex]->Name(componentName);
			}
		}

		heap->Name(name);
	}
}
