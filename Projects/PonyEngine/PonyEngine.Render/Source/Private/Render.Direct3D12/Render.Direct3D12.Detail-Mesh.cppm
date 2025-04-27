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

import PonyMath.Shape;

import PonyShader.Core;

import :Buffer;
import :DescriptorHeap;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 mesh.
	class Mesh final
	{
	public:
		/// @brief Creates an empty mesh.
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		/// @brief Creates a mesh.
		/// @param buffer Mesh buffer.
		/// @param heap Mesh heap.
		/// @param dataTypes Data types.
		/// @param bufferOffsets Buffer offsets.
		/// @param heapIndices Heap indices.
		/// @param threadGroupCounts Thread group counts.
		/// @param boundingBox Bounding box.
		[[nodiscard("Pure constructor")]]
		Mesh(const std::shared_ptr<class Buffer>& buffer, const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::string_view> dataTypes,
			std::span<const std::span<const std::uint64_t>> bufferOffsets, std::span<const std::uint32_t> heapIndices,
			std::span<const std::uint32_t, 3> threadGroupCounts, const std::optional<PonyMath::Shape::AABB<float>>& boundingBox);
		/// @brief Creates a mesh.
		/// @param buffer Mesh buffer.
		/// @param heap Mesh heap.
		/// @param dataTypes Data types.
		/// @param bufferOffsets Buffer offsets.
		/// @param heapIndices Heap indices.
		/// @param threadGroupCounts Thread group counts.
		/// @param boundingBox Bounding box.
		[[nodiscard("Pure constructor")]]
		Mesh(std::shared_ptr<class Buffer>&& buffer, std::shared_ptr<DescriptorHeap>&& heap, std::vector<std::string>&& dataTypes,
			std::vector<std::vector<std::uint64_t>>&& bufferOffsets, std::vector<std::uint32_t>&& heapIndices,
			std::span<const std::uint32_t, 3> threadGroupCounts, const std::optional<PonyMath::Shape::AABB<float>>& boundingBox) noexcept;
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

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
		std::optional<std::uint32_t> DataIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the data index.
		/// @param index Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t index) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		/// @brief Gets a buffer count by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Buffer count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount(std::uint32_t dataIndex) const noexcept;
		/// @brief Tries to find a buffer count by the @p dataType.
		/// @param dataType Data type.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> BufferCount(std::string_view dataType) const noexcept;

		/// @brief Gets a buffer offset.
		/// @param dataIndex Data type index.
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

		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() noexcept;
		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		const PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() const noexcept;

		/// @brief Gets the bounding box.
		/// @return Bounding box.
		[[nodiscard("Pure function")]]
		std::optional<PonyMath::Shape::AABB<float>>& BoundingBox() noexcept;
		/// @brief Gets the bounding box.
		/// @return Bounding box.
		[[nodiscard("Pure function")]]
		const std::optional<PonyMath::Shape::AABB<float>>& BoundingBox() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::shared_ptr<class Buffer> buffer; ///< Buffer.
		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<std::uint64_t>> bufferOffsets; ///< Buffer offsets.
		std::vector<std::uint32_t> heapIndices; ///< Heap indices.

		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::optional<PonyMath::Shape::AABB<float>> boundingBox; ///< Bounding box.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Mesh::Mesh(const std::shared_ptr<class Buffer>& buffer, const std::shared_ptr<DescriptorHeap>& heap, const std::span<const std::string_view> dataTypes,
		const std::span<const std::span<const std::size_t>> bufferOffsets, const std::span<const std::uint32_t> heapIndices, 
		const std::span<const std::uint32_t, 3> threadGroupCounts, const std::optional<PonyMath::Shape::AABB<float>>& boundingBox) :
		buffer(buffer),
		heap(heap),
		dataTypes(dataTypes.begin(), dataTypes.end()),
		heapIndices(heapIndices.begin(), heapIndices.end()),
		threadGroupCounts(threadGroupCounts),
		boundingBox(boundingBox)
	{
		this->bufferOffsets.reserve(bufferOffsets.size());
		for (std::size_t i = 0; i < bufferOffsets.size(); ++i)
		{
			this->bufferOffsets.push_back(std::vector<std::uint64_t>(bufferOffsets[i].begin(), bufferOffsets[i].end()));
		}
	}

	Mesh::Mesh(std::shared_ptr<class Buffer>&& buffer, std::shared_ptr<DescriptorHeap>&& heap, std::vector<std::string>&& dataTypes,
		std::vector<std::vector<std::size_t>>&& bufferOffsets, std::vector<std::uint32_t>&& heapIndices, 
		const std::span<const std::uint32_t, 3> threadGroupCounts, const std::optional<PonyMath::Shape::AABB<float>>& boundingBox) noexcept :
		buffer(std::move(buffer)),
		heap(std::move(heap)),
		dataTypes(std::move(dataTypes)),
		bufferOffsets(std::move(bufferOffsets)),
		heapIndices(std::move(heapIndices)),
		threadGroupCounts(threadGroupCounts),
		boundingBox(boundingBox)
	{
	}

	class Buffer* Mesh::Buffer() noexcept
	{
		return buffer.get();
	}

	const class Buffer* Mesh::Buffer() const noexcept
	{
		return buffer.get();
	}

	DescriptorHeap* Mesh::Heap() noexcept
	{
		return heap.get();
	}

	const DescriptorHeap* Mesh::Heap() const noexcept
	{
		return heap.get();
	}

	std::optional<std::uint32_t> Mesh::DataIndex(const std::string_view dataType) const noexcept
	{
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(dataTypes.size()); ++i)
		{
			if (dataTypes[i] == dataType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view Mesh::DataType(const std::uint32_t index) const noexcept
	{
		return dataTypes[index];
	}

	std::uint32_t Mesh::DataCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::uint32_t Mesh::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferOffsets[dataIndex].size());
	}

	std::optional<std::uint32_t> Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferCount(dataIndex.value());
		}

		return std::nullopt;
	}

	std::uint64_t Mesh::BufferOffset(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferOffsets[dataIndex][bufferIndex];
	}

	std::optional<std::uint64_t> Mesh::BufferOffset(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferOffset(dataIndex.value(), bufferIndex);
		}

		return std::nullopt;
	}

	std::uint32_t Mesh::HeapIndex(const std::uint32_t dataIndex) const noexcept
	{
		return heapIndices[dataIndex];
	}

	std::optional<std::uint32_t> Mesh::HeapIndex(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return HeapIndex(dataIndex.value());
		}

		return std::nullopt;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Mesh::CpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->CpuHandle(HeapIndex(dataIndex));
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Mesh::GpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->GpuHandle(HeapIndex(dataIndex));
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Mesh::CpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return CpuHandle(dataIndex.value());
		}

		return std::nullopt;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Mesh::GpuHandle(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return GpuHandle(dataIndex.value());
		}

		return std::nullopt;
	}

	PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	const PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	std::optional<PonyMath::Shape::AABB<float>>& Mesh::BoundingBox() noexcept
	{
		return boundingBox;
	}

	const std::optional<PonyMath::Shape::AABB<float>>& Mesh::BoundingBox() const noexcept
	{
		return boundingBox;
	}

	void Mesh::Name(const std::string_view name)
	{
		buffer->Name(name);
		heap->Name(name);
	}
}
