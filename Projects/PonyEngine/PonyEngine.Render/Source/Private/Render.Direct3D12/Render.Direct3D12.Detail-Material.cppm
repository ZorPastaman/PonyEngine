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

export module PonyEngine.Render.Direct3D12.Detail:Material;

import <cstdint>;
import <memory>;
import <optional>;
import <span>;
import <string>;
import <string_view>;
import <utility>;
import <vector>;

import :Buffer;
import :DescriptorHeap;
import :PipelineState;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material.
	class Material final
	{
	public:
		/// @brief Creates an empty material.
		[[nodiscard("Pure constructor")]]
		Material() noexcept = default;
		/// @brief Creates a material.
		/// @param pipelineState Pipeline state.
		/// @param dataBuffer Data buffer.
		/// @param bufferOffsets Buffer offsets.
		/// @param heap Heap.
		/// @param dataTypes Data type.
		/// @param heapIndices Heap indices.
		[[nodiscard("Pure constructor")]]
		explicit Material(const std::shared_ptr<class PipelineState>& pipelineState, 
			const std::shared_ptr<class Buffer>& dataBuffer, std::span<const std::span<const std::uint64_t>> bufferOffsets,
			const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::string_view> dataTypes, std::span<const std::uint32_t> heapIndices);
		/// @brief Creates a material.
		/// @param pipelineState Pipeline state.
		/// @param dataBuffer Data buffer.
		/// @param bufferOffsets Buffer offsets.
		/// @param heap Data heap.
		/// @param dataTypes Data type.
		/// @param heapIndices Data heap indices.
		[[nodiscard("Pure constructor")]]
		explicit Material(std::shared_ptr<class PipelineState>&& pipelineState, 
			std::shared_ptr<class Buffer>&& dataBuffer, std::vector<std::vector<std::uint64_t>>&& bufferOffsets,
			std::shared_ptr<DescriptorHeap>&& heap, std::vector<std::string>&& dataTypes, std::vector<std::uint32_t>&& heapIndices) noexcept;
		[[nodiscard("Pure constructor")]]
		Material(const Material& other) = default;
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept = default;

		~Material() noexcept = default;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		class PipelineState* PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const class PipelineState* PipelineState() const noexcept;
		/// @brief Sets the pipeline state.
		/// @param pipelineState Pipeline state to set.
		void PipelineState(const std::shared_ptr<class PipelineState>& pipelineState) noexcept;
		/// @brief Sets the pipeline state.
		/// @param pipelineState Pipeline state to set.
		void PipelineState(std::shared_ptr<class PipelineState>&& pipelineState) noexcept;

		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		class Buffer* Buffer() noexcept;
		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const class Buffer* Buffer() const noexcept;

		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		DescriptorHeap* Heap() noexcept;
		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		const DescriptorHeap* Heap() const noexcept;

		/// @brief Tries to find a data index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataTypeIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the data type index.
		/// @param index Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t index) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;

		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		/// @brief Gets a data count by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Tries to find a data count by the @p dataType.
		/// @param dataType Data type.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataCount(std::string_view dataType) const noexcept;
		/// @brief Gets a data count.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		/// @brief Gets a buffer offset.
		/// @param dataIndex Data type index. Must be a buffer index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer offset.
		[[nodiscard("Pure function")]]
		std::uint64_t BufferOffset(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;
		/// @brief Tries to find a buffer offset.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer offset; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint64_t> BufferOffset(std::string_view dataType, std::uint32_t bufferIndex) const noexcept;

		/// @brief Gets a heap index.
		/// @param dataIndex Data type index.
		/// @return Heap index.
		[[nodiscard("Pure function")]]
		std::uint32_t HeapIndex(std::uint32_t dataIndex) const noexcept;
		/// @brief Tries to find a heap index.
		/// @param dataType Data type.
		/// @return Heap index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> HeapIndex(std::string_view dataType) const noexcept;

		/// @brief Gets a cpu handle.
		/// @param dataIndex Data type index.
		/// @return Cpu handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets a gpu handle.
		/// @param dataIndex Data type index.
		/// @return Gpu handle.
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(std::uint32_t dataIndex) const noexcept;
		/// @brief Tries to find a cpu handle.
		/// @param dataType Data type.
		/// @return Cpu handle; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CpuHandle(std::string_view dataType) const noexcept;
		/// @brief Tries to find a gpu handle.
		/// @param dataType Data type.
		/// @return Gpu handle; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> GpuHandle(std::string_view dataType) const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Material& operator =(const Material& other) = default;
		Material& operator =(Material&& other) noexcept = default;

	private:
		std::shared_ptr<class PipelineState> pipelineState; ///< Pipeline state.

		std::shared_ptr<class Buffer> dataBuffer; ///< Data buffer.
		std::vector<std::vector<std::uint64_t>> bufferOffsets; ///< Buffer offsets.

		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::uint32_t> heapIndices; ///< Heap indices.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Material::Material(const std::shared_ptr<class PipelineState>& pipelineState,
		const std::shared_ptr<class Buffer>& dataBuffer, std::span<const std::span<const std::uint64_t>> bufferOffsets, 
		const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::string_view> dataTypes, std::span<const std::uint32_t> heapIndices) :
		pipelineState(pipelineState),
		dataBuffer(dataBuffer),
		heap(heap),
		dataTypes(dataTypes.begin(), dataTypes.end()),
		heapIndices(heapIndices.begin(), heapIndices.end())
	{
		this->bufferOffsets.reserve(bufferOffsets.size());
		for (std::size_t i = 0; i < bufferOffsets.size(); ++i)
		{
			this->bufferOffsets.push_back(std::vector<std::uint64_t>(bufferOffsets[i].begin(), bufferOffsets[i].end()));
		}
	}

	Material::Material(std::shared_ptr<class PipelineState>&& pipelineState,
		std::shared_ptr<class Buffer>&& dataBuffer, std::vector<std::vector<std::uint64_t>>&& bufferOffsets, 
		std::shared_ptr<DescriptorHeap>&& heap, std::vector<std::string>&& dataTypes, std::vector<std::uint32_t>&& heapIndices) noexcept :
		pipelineState(std::move(pipelineState)),
		dataBuffer(std::move(dataBuffer)),
		bufferOffsets(std::move(bufferOffsets)),
		heap(std::move(heap)),
		dataTypes(std::move(dataTypes)),
		heapIndices(std::move(heapIndices))
	{
	}

	class PipelineState* Material::PipelineState() noexcept
	{
		return pipelineState.get();
	}

	const class PipelineState* Material::PipelineState() const noexcept
	{
		return pipelineState.get();
	}

	void Material::PipelineState(const std::shared_ptr<class PipelineState>& pipelineState) noexcept
	{
		this->pipelineState = pipelineState;
	}

	void Material::PipelineState(std::shared_ptr<class PipelineState>&& pipelineState) noexcept
	{
		this->pipelineState = std::move(pipelineState);
	}

	class Buffer* Material::Buffer() noexcept
	{
		return dataBuffer.get();
	}

	const class Buffer* Material::Buffer() const noexcept
	{
		return dataBuffer.get();
	}

	DescriptorHeap* Material::Heap() noexcept
	{
		return heap.get();
	}

	const DescriptorHeap* Material::Heap() const noexcept
	{
		return heap.get();
	}

	std::optional<std::uint32_t> Material::DataTypeIndex(const std::string_view dataType) const noexcept
	{
		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(dataTypes.size()); ++i)
		{
			if (dataTypes[i] == dataType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view Material::DataType(const std::uint32_t index) const noexcept
	{
		return dataTypes[index];
	}

	std::uint32_t Material::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::span<const std::string> Material::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::uint32_t Material::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferOffsets[dataTypeIndex].size());
	}

	std::optional<std::uint32_t> Material::DataCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataTypeIndex(dataType))
		{
			return DataCount(dataIndex.value());
		}

		return std::nullopt;
	}

	std::uint32_t Material::DataCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (const std::vector<std::uint64_t>& bufferOffsets : bufferOffsets)
		{
			count += static_cast<std::uint32_t>(bufferOffsets.size());
		}

		return count;
	}

	std::uint64_t Material::BufferOffset(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferOffsets[dataIndex][bufferIndex];
	}

	std::optional<std::uint64_t> Material::BufferOffset(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataTypeIndex(dataType))
		{
			return BufferOffset(dataIndex.value(), bufferIndex);
		}

		return std::nullopt;
	}

	std::uint32_t Material::HeapIndex(const std::uint32_t dataIndex) const noexcept
	{
		return heapIndices[dataIndex];
	}

	std::optional<std::uint32_t> Material::HeapIndex(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataTypeIndex(dataType))
		{
			return HeapIndex(dataIndex.value());
		}

		return std::nullopt;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Material::CpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->CpuHandle(HeapIndex(dataIndex));
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Material::GpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->GpuHandle(HeapIndex(dataIndex));
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Material::CpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataTypeIndex(dataType))
		{
			return CpuHandle(dataIndex.value());
		}

		return std::nullopt;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Material::GpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataTypeIndex(dataType))
		{
			return GpuHandle(dataIndex.value());
		}

		return std::nullopt;
	}

	void Material::Name(const std::string_view name)
	{
		dataBuffer->Name(name);
		heap->Name(name);
	}
}
