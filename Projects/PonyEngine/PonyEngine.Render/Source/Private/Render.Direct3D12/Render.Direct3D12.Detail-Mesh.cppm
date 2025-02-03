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
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Mesh(std::span<const std::string> dataTypes, std::span<const std::uint32_t> bufferOffsets, std::span<const std::shared_ptr<class Buffer>> buffers, const std::shared_ptr<DescriptorHeap>& heap);
		[[nodiscard("Pure constructor")]]
		Mesh(std::span<const std::string> dataTypes, std::span<const std::uint32_t> bufferOffsets, std::span<const std::shared_ptr<class Buffer>> buffers, const std::shared_ptr<DescriptorHeap>& heap, 
			std::span<const std::uint32_t, 3> threadGroupCounts);
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataIndex(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::uint32_t BufferOffset(std::uint32_t dataIndex) const;
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> BufferOffset(std::string_view dataType) const;

		[[nodiscard("Pure function")]]
		class Buffer& Buffer(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer& Buffer(std::uint32_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount() const noexcept;

		[[nodiscard("Pure function")]]
		class Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		class Buffer* Buffer(std::string_view dataType, std::uint32_t bufferIndex) noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer* Buffer(std::string_view dataType, std::uint32_t bufferIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> BufferCount(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CpuHandle(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> GpuHandle(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		DescriptorHeap* Heap() noexcept;
		[[nodiscard("Pure function")]]
		const DescriptorHeap* Heap() const noexcept;

		[[nodiscard("Pure function")]]
		PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		const PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::uint32_t> bufferOffsets;
		std::vector<std::shared_ptr<class Buffer>> buffers; ///< Buffers.
		std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.

		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Mesh::Mesh(std::span<const std::string> dataTypes, std::span<const std::uint32_t> bufferOffsets, std::span<const std::shared_ptr<class Direct3D12::Buffer>> buffers, const std::shared_ptr<DescriptorHeap>& heap) :
		dataTypes(dataTypes.begin(), dataTypes.end()),
		bufferOffsets(bufferOffsets.begin(), bufferOffsets.end()),
		buffers(buffers.begin(), buffers.end()),
		heap(heap),
		threadGroupCounts{ 1u, 1u, 1u }
	{
	}

	Mesh::Mesh(const std::span<const std::string> dataTypes, const std::span<const std::uint32_t> bufferOffsets, const std::span<const std::shared_ptr<class Buffer>> buffers,
		const std::shared_ptr<DescriptorHeap>& heap, std::span<const std::uint32_t, 3> threadGroupCounts) :
		dataTypes(dataTypes.begin(), dataTypes.end()),
		bufferOffsets(bufferOffsets.begin(), bufferOffsets.end()),
		buffers(buffers.begin(), buffers.end()),
		heap(heap),
		threadGroupCounts(threadGroupCounts)
	{
	}

	std::optional<std::uint32_t> Mesh::DataIndex(const std::string_view dataType) const noexcept
	{
		for (std::uint32_t i = 0u; i < dataTypes.size(); ++i)
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

	std::uint32_t Mesh::BufferOffset(const std::uint32_t dataIndex) const
	{
		return bufferOffsets[dataIndex];
	}

	std::optional<std::uint32_t> Mesh::BufferOffset(const std::string_view dataType) const
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferOffset(dataIndex.value());
		}

		return std::nullopt;
	}

	class Buffer& Mesh::Buffer(const std::uint32_t index) noexcept
	{
		return *buffers[index];
	}

	const class Buffer& Mesh::Buffer(const std::uint32_t index) const noexcept
	{
		return *buffers[index];
	}

	std::uint32_t Mesh::BufferCount() const noexcept
	{
		return static_cast<std::uint32_t>(buffers.size());
	}

	class Buffer& Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept
	{
		return *buffers[bufferOffsets[dataIndex] + bufferIndex];
	}

	const class Buffer& Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return *buffers[bufferOffsets[dataIndex] + bufferIndex];
	}

	std::uint32_t Mesh::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		const std::uint32_t nextOffset = static_cast<std::uint32_t>(dataIndex < bufferOffsets.size() - 1 ? bufferOffsets[dataIndex + 1]  : buffers.size());

		return nextOffset - bufferOffsets[dataIndex];
	}

	class Buffer* Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType); dataIndex && bufferIndex < BufferCount(dataIndex.value()))
		{
			return &Buffer(dataIndex.value(), bufferIndex);
		}

		return nullptr;
	}

	const class Buffer* Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType); dataIndex && bufferIndex < BufferCount(dataIndex.value()))
		{
			return &Buffer(dataIndex.value(), bufferIndex);
		}

		return nullptr;
	}

	std::optional<std::uint32_t> Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferCount(dataIndex.value());
		}

		return std::nullopt;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Mesh::CpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->CpuHandle(bufferOffsets[dataIndex]);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Mesh::GpuHandle(const std::uint32_t dataIndex) const noexcept
	{
		return heap->GpuHandle(bufferOffsets[dataIndex]);
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

	DescriptorHeap* Mesh::Heap() noexcept
	{
		return heap.get();
	}

	const DescriptorHeap* Mesh::Heap() const noexcept
	{
		return heap.get();
	}

	PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	const PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() const noexcept
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
		for (std::uint32_t dataTypeIndex = 0; dataTypeIndex < dataTypes.size(); ++dataTypeIndex)
		{
			std::uint32_t bufferIndex = bufferOffsets[dataTypeIndex];
			const std::uint32_t bufferCount = BufferCount(dataTypeIndex) + bufferIndex;

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
