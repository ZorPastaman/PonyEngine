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

export module PonyEngine.Render.Direct3D12:BufferAgent;

import <cstddef>;
import <cstdint>;
import <memory>;
import <span>;
import <unordered_map>;

import PonyEngine.Render.Core;

import :Buffer;
import :DescriptorHeap;
import :IRenderSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Buffer agent.
	class BufferAgent final : public Core::IBufferAgent
	{
	public:
		/// @brief Creates a buffer agent.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit BufferAgent(IRenderSystemContext& renderSystem) noexcept;
		BufferAgent(const BufferAgent&) = delete;
		BufferAgent(BufferAgent&&) = delete;

		~BufferAgent() noexcept = default;

		virtual void Create(const IBuffer& buffer) override;
		virtual void Destroy(const IBuffer& buffer) override;
		virtual void Update(const IBuffer& buffer, Core::BufferDirtyFlag dirtyFlags) override;

		BufferAgent& operator =(const BufferAgent&) = delete;
		BufferAgent& operator =(BufferAgent&&) = delete;

	private:
		/// @brief Buffer data.
		struct BufferData final
		{
			std::shared_ptr<Buffer> upload; ///< Upload buffer.
			std::shared_ptr<Buffer> gpu; ///< GPU buffer.
			std::shared_ptr<DescriptorHeap> heap; ///< Descriptor heap.
			bool isUploadDirty; ///< Is the upload buffer dirty?
		};

		/// @brief Buffer info. Used to sort sub-buffers.
		struct BufferInfo final
		{
			std::uint64_t offset; ///< Offset in element indices.
			std::uint32_t dataTypeIndex; ///< Data type index.
			std::uint32_t dataIndex; ///< Data index.
		};

		/// @brief Calculates a buffer order.
		/// @param source Source buffer.
		/// @return Buffer infos in the order they must appear in a render buffer.
		[[nodiscard("Pure function")]]
		static std::vector<BufferInfo> CalculateBufferOrder(const IBuffer& source);
		/// @brief Calculates a buffer size by the buffer infos.
		/// @param source Source buffer.
		/// @param bufferInfos Buffer infos.
		/// @return Required size.
		[[nodiscard("Pure function")]]
		static std::uint64_t CalculateBufferSize(const IBuffer& source, std::span<const BufferInfo> bufferInfos) noexcept;

		/// @brief Creates data.
		/// @param source Source buffer.
		/// @param bufferData Buffer data.
		void CreateData(const IBuffer& source, BufferData& bufferData);

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::unordered_map<const IBuffer*, BufferData> buffers; ///< Buffers.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	BufferAgent::BufferAgent(IRenderSystemContext& renderSystem) noexcept :
		renderSystem(&renderSystem)
	{
	}

	void BufferAgent::Create(const IBuffer& buffer)
	{
		buffers.emplace(&buffer, BufferData{});
	}

	void BufferAgent::Destroy(const IBuffer& buffer)
	{
		buffers.erase(&buffer);
	}

	void BufferAgent::Update(const IBuffer& buffer, const Core::BufferDirtyFlag dirtyFlags)
	{
		BufferData& bufferData = buffers[&buffer];

		if ((dirtyFlags & Core::BufferDirtyFlag::DataStructure) != Core::BufferDirtyFlag::None)
		{
			CreateData(buffer, bufferData);
		}
	}

	std::vector<BufferAgent::BufferInfo> BufferAgent::CalculateBufferOrder(const IBuffer& source)
	{
		std::vector<BufferInfo> answer;
		answer.reserve(source.DataCount());
		for (std::uint32_t dataTypeIndex = 0u; dataTypeIndex < source.DataTypeCount(); ++dataTypeIndex)
		{
			for (std::uint32_t bufferIndex = 0u; bufferIndex < source.DataCount(dataTypeIndex); ++bufferIndex)
			{
				answer.push_back(BufferInfo{.offset = 0ULL, .dataTypeIndex = dataTypeIndex, .dataIndex = bufferIndex});
			}
		}

		std::ranges::sort(answer, [&](const BufferInfo& left, const BufferInfo& right)
		{
			return source.ElementSize(left.dataTypeIndex, left.dataIndex) > source.ElementSize(right.dataTypeIndex, right.dataIndex);
		});

		for (std::size_t i = 1; i < answer.size(); ++i)
		{
			const BufferInfo& prev = answer[i - 1];
			BufferInfo& current = answer[i];
			const std::uint64_t prevEnd = prev.offset * source.ElementSize(prev.dataTypeIndex, prev.dataIndex) + source.DataSize(prev.dataTypeIndex, prev.dataIndex);
			current.offset = PonyMath::Core::DivideCeil(prevEnd, static_cast<std::uint64_t>(source.ElementSize(current.dataTypeIndex, current.dataIndex)));
		}

		return answer;
	}

	std::uint64_t BufferAgent::CalculateBufferSize(const IBuffer& source, const std::span<const BufferInfo> bufferInfos) noexcept
	{
		if (bufferInfos.size() == 0)
		{
			return 1ULL;
		}

		const BufferInfo& last = bufferInfos.back();

		return last.offset * source.ElementSize(last.dataTypeIndex, last.dataIndex) + source.DataSize(last.dataTypeIndex, last.dataIndex);
	}

	void BufferAgent::CreateData(const IBuffer& source, BufferData& bufferData)
	{
		const std::vector<BufferInfo> bufferInfos = CalculateBufferOrder(source);
		const std::uint64_t bufferSize = CalculateBufferSize(source, bufferInfos);
	}
}
