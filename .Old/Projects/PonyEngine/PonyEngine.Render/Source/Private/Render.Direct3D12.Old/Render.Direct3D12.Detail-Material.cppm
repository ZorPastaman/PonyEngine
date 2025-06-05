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
import :Texture;

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
		/// @param types Data type.
		/// @param heapIndices Heap indices.
		[[nodiscard("Pure constructor")]]
		Material(const std::shared_ptr<class PipelineState>& pipelineState, 
			const std::shared_ptr<class Buffer>& dataBuffer, std::span<const std::span<const std::uint64_t>> bufferOffsets, 
			std::span<const std::span<const std::shared_ptr<class Texture>>> textures,
			const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::string_view> types, std::span<const std::uint32_t> heapIndices);
		/// @brief Creates a material.
		/// @param pipelineState Pipeline state.
		/// @param dataBuffer Data buffer.
		/// @param bufferOffsets Buffer offsets.
		/// @param heap Data heap.
		/// @param dataTypes Data type.
		/// @param heapIndices Data heap indices.
		[[nodiscard("Pure constructor")]]
		Material(std::shared_ptr<class PipelineState>&& pipelineState, 
			std::shared_ptr<class Buffer>&& dataBuffer, std::vector<std::vector<std::uint64_t>>&& bufferOffsets,
			std::vector<std::vector<std::shared_ptr<class Texture>>>&& textures,
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

		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;
		/// @brief Gets a data count by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Gets a data count.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		/// @brief Gets a buffer offset.
		/// @param dataTypeIndex Data type index. Must be a buffer index.
		/// @param dataIndex Buffer index.
		/// @return Buffer offset.
		[[nodiscard("Pure function")]]
		std::uint64_t BufferOffset(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;

		[[nodiscard("Pure function")]]
		class Texture* Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex) noexcept;
		[[nodiscard("Pure function")]]
		const class Texture* Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex) const noexcept;
		void Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex, const std::shared_ptr<class Texture>& texture) noexcept;
		void Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex, std::shared_ptr<class Texture>&& texture) noexcept;

		[[nodiscard("Pure function")]]
		std::uint32_t TextureTypeCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t TextureCount(std::uint32_t textureTypeIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t TextureCount() const noexcept;

		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		DescriptorHeap* Heap() noexcept;
		/// @brief Gets the heap.
		/// @return Heap.
		[[nodiscard("Pure function")]]
		const DescriptorHeap* Heap() const noexcept;

		/// @brief Tries to find a data index by the @p dataType.
		/// @param type Data type.
		/// @return Data index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> TypeIndex(std::string_view type) const noexcept;
		/// @brief Gets a data type by the data type index.
		/// @param index Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view Type(std::uint32_t index) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t TypeCount() const noexcept;

		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> Types() const noexcept;

		/// @brief Gets a heap index.
		/// @param typeIndex Data type index.
		/// @return Heap index.
		[[nodiscard("Pure function")]]
		std::uint32_t HeapIndex(std::uint32_t typeIndex) const noexcept;
		/// @brief Tries to find a heap index.
		/// @param type Data type.
		/// @return Heap index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> HeapIndex(std::string_view type) const noexcept;

		/// @brief Gets a cpu handle.
		/// @param typeIndex Data type index.
		/// @return Cpu handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(std::uint32_t typeIndex) const noexcept;
		/// @brief Gets a gpu handle.
		/// @param typeIndex Data type index.
		/// @return Gpu handle.
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(std::uint32_t typeIndex) const noexcept;
		/// @brief Tries to find a cpu handle.
		/// @param type Data type.
		/// @return Cpu handle; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CpuHandle(std::string_view type) const noexcept;
		/// @brief Tries to find a gpu handle.
		/// @param type Data type.
		/// @return Gpu handle; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> GpuHandle(std::string_view type) const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Material& operator =(const Material& other) = default;
		Material& operator =(Material&& other) noexcept = default;

	private:
		std::shared_ptr<class PipelineState> pipelineState; ///< Pipeline state.

		std::shared_ptr<class Buffer> dataBuffer; ///< Data buffer.
		std::vector<std::vector<std::uint64_t>> bufferOffsets; ///< Buffer offsets. <DataTypeIndex, BufferIndex> as a key.

		std::vector<std::vector<std::shared_ptr<class Texture>>> textures; ///< Textures. <TextureTypeIndex, TextureIndex> as a key.

		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap. Contains both buffers and textures.
		std::vector<std::string> types; ///< Data and texture types.
		std::vector<std::uint32_t> heapIndices; ///< Heap indices.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Material::Material(const std::shared_ptr<class PipelineState>& pipelineState,
		const std::shared_ptr<class Buffer>& dataBuffer, std::span<const std::span<const std::uint64_t>> bufferOffsets,
		const std::span<const std::span<const std::shared_ptr<class Texture>>> textures,
		const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::string_view> types, std::span<const std::uint32_t> heapIndices) :
		pipelineState(pipelineState),
		dataBuffer(dataBuffer),
		heap(heap),
		types(types.begin(), types.end()),
		heapIndices(heapIndices.begin(), heapIndices.end())
	{
		this->bufferOffsets.reserve(bufferOffsets.size());
		for (std::size_t i = 0; i < bufferOffsets.size(); ++i)
		{
			this->bufferOffsets.push_back(std::vector<std::uint64_t>(bufferOffsets[i].begin(), bufferOffsets[i].end()));
		}

		this->textures.reserve(textures.size());
		for (std::size_t i = 0; i < textures.size(); ++i)
		{
			this->textures.push_back(std::vector<std::shared_ptr<class Texture>>(textures[i].begin(), textures[i].end()));
		}
	}

	Material::Material(std::shared_ptr<class PipelineState>&& pipelineState,
		std::shared_ptr<class Buffer>&& dataBuffer, std::vector<std::vector<std::uint64_t>>&& bufferOffsets,
		std::vector<std::vector<std::shared_ptr<class Texture>>>&& textures,
		std::shared_ptr<DescriptorHeap>&& heap, std::vector<std::string>&& dataTypes, std::vector<std::uint32_t>&& heapIndices) noexcept :
		pipelineState(std::move(pipelineState)),
		dataBuffer(std::move(dataBuffer)),
		bufferOffsets(std::move(bufferOffsets)),
		textures(std::move(textures)),
		heap(std::move(heap)),
		types(std::move(dataTypes)),
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

	std::uint32_t Material::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(bufferOffsets.size());
	}

	std::uint32_t Material::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferOffsets[dataTypeIndex].size());
	}

	std::uint32_t Material::DataCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0; i < DataTypeCount(); ++i)
		{
			count += DataCount(i);
		}

		return count;
	}

	std::uint64_t Material::BufferOffset(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferOffsets[dataTypeIndex][dataIndex];
	}

	class Texture* Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex) noexcept
	{
		return textures[textureTypeIndex][textureIndex].get();
	}

	const class Texture* Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex) const noexcept
	{
		return textures[textureTypeIndex][textureIndex].get();
	}

	void Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex, const std::shared_ptr<class Texture>& texture) noexcept
	{
		textures[textureTypeIndex][textureIndex] = texture;
	}

	void Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex, std::shared_ptr<class Texture>&& texture) noexcept
	{
		textures[textureTypeIndex][textureIndex] = std::move(texture);
	}

	std::uint32_t Material::TextureTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(textures.size());
	}

	std::uint32_t Material::TextureCount(const std::uint32_t textureTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(textures[textureTypeIndex].size());
	}

	std::uint32_t Material::TextureCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0; i < TextureTypeCount(); ++i)
		{
			count += TextureCount(i);
		}

		return count;
	}

	DescriptorHeap* Material::Heap() noexcept
	{
		return heap.get();
	}

	const DescriptorHeap* Material::Heap() const noexcept
	{
		return heap.get();
	}

	std::optional<std::uint32_t> Material::TypeIndex(const std::string_view type) const noexcept
	{
		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(types.size()); ++i)
		{
			if (types[i] == type)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view Material::Type(const std::uint32_t index) const noexcept
	{
		return types[index];
	}

	std::uint32_t Material::TypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(types.size());
	}

	std::span<const std::string> Material::Types() const noexcept
	{
		return types;
	}

	std::uint32_t Material::HeapIndex(const std::uint32_t typeIndex) const noexcept
	{
		return heapIndices[typeIndex];
	}

	std::optional<std::uint32_t> Material::HeapIndex(const std::string_view type) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = TypeIndex(type))
		{
			return HeapIndex(dataIndex.value());
		}

		return std::nullopt;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Material::CpuHandle(const std::uint32_t typeIndex) const noexcept
	{
		return heap->CpuHandle(HeapIndex(typeIndex));
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Material::GpuHandle(const std::uint32_t typeIndex) const noexcept
	{
		return heap->GpuHandle(HeapIndex(typeIndex));
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Material::CpuHandle(const std::string_view type) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = TypeIndex(type))
		{
			return CpuHandle(dataIndex.value());
		}

		return std::nullopt;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Material::GpuHandle(const std::string_view type) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = TypeIndex(type))
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
