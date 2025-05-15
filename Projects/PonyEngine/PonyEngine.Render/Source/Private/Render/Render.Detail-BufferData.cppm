/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render.Detail:BufferData;

import <cstddef>;
import <cstdint>;
import <limits>;
import <optional>;
import <span>;
import <stdexcept>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyBase.Container;
import PonyBase.Utility;

export namespace PonyEngine::Render
{
	class BufferData final
	{
	public:
		/// @brief Creates an empty buffer data.
		[[nodiscard("Pure constructor")]]
		BufferData() noexcept = default;
		/// @brief Creates a buffer data.
		/// @param bufferParams Buffer parameters.
		[[nodiscard("Pure constructor")]]
		explicit BufferData(const std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>>& bufferParams);
		[[nodiscard("Pure constructor")]]
		BufferData(const BufferData& other) = default;
		[[nodiscard("Pure constructor")]]
		BufferData(BufferData&& other) noexcept = default;

		~BufferData() noexcept = default;

		/// @brief Tries to find a data type index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data type index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataTypeIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;

		/// @brief Gets a data size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data size in bytes.
		[[nodiscard("Pure function")]]
		std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;
		/// @brief Gets the data count by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Gets the data count.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		/// @brief Gets a data element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data element size in bytes.
		[[nodiscard("Pure function")]]
		std::uint32_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;
		/// @brief Gets a data element count.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data element count.
		[[nodiscard("Pure function")]]
		std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;

		/// @brief Gets the buffer.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		PonyBase::Container::Buffer& Buffer(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) noexcept;
		/// @brief Gets the buffer.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Buffer(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;

		/// @brief Creates a new data type.
		/// @note Throws if such a data type already exists.
		/// @param dataType Data type.
		/// @param bufferParams Buffer parameters.
		/// @return Data type index.
		std::uint32_t Create(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		/// @brief Destroys a data.
		/// @param dataIndex Data type index.
		void Destroy(std::uint32_t dataIndex) noexcept;

		/// @brief Gets a data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> GetData(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;
		/// @brief Gets a data element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> GetData(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept;

		/// @brief Sets the data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param data Data.
		void SetData(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const std::byte> data);
		/// @brief Sets the data element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @param data Data.
		void SetData(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, std::span<const std::byte> data);

		BufferData& operator =(const BufferData& other) = default;
		BufferData& operator =(BufferData&& other) noexcept = default;

	private:
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<PonyBase::Container::Buffer>> dataBuffers; ///< Data buffers.
	};
}

namespace PonyEngine::Render
{
	BufferData::BufferData(const std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>>& bufferParams)
	{
		std::size_t bufferCount = 0;
		for (const auto& [dataType, params] : bufferParams)
		{
			if (params.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data of type '{}' is empty.", dataType));
			}
			for (std::size_t i = 0; i < params.size(); ++i)
			{
				if (params[i].stride == 0 || params[i].count == 0) [[unlikely]]
				{
					throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data buffer of type '{}' at '{}' is empty.", dataType, i));
				}
			}
			++bufferCount;
		}
		if (bufferCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		dataTypes.reserve(bufferParams.size());
		dataBuffers.reserve(bufferParams.size());

		for (const auto& [dataType, params] : bufferParams)
		{
			dataTypes.push_back(dataType);
			std::vector<PonyBase::Container::Buffer> buffers;
			buffers.reserve(params.size());
			for (const PonyBase::Container::BufferParams& param : params)
			{
				buffers.push_back(PonyBase::Container::Buffer(param));
			}
			dataBuffers.push_back(std::move(buffers));
		}
	}

	std::optional<std::uint32_t> BufferData::DataTypeIndex(const std::string_view dataType) const noexcept
	{
		for (std::uint32_t i = 0; i < dataTypes.size(); ++i)
		{
			if (dataTypes[i] == dataType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view BufferData::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return dataTypes[dataTypeIndex];
	}

	std::uint32_t BufferData::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::size_t BufferData::DataSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Buffer(dataTypeIndex, dataIndex).Size();
	}

	std::uint32_t BufferData::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(dataBuffers[dataTypeIndex].size());
	}

	std::uint32_t BufferData::DataCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(dataTypes.size()); ++i)
		{
			count += DataCount(i);
		}

		return count;
	}

	std::uint32_t BufferData::ElementSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Buffer(dataTypeIndex, dataIndex).Stride();
	}

	std::uint32_t BufferData::ElementCount(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Buffer(dataTypeIndex, dataIndex).Count();
	}

	PonyBase::Container::Buffer& BufferData::Buffer(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) noexcept
	{
		return dataBuffers[dataTypeIndex][dataIndex];
	}

	const PonyBase::Container::Buffer& BufferData::Buffer(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return dataBuffers[dataTypeIndex][dataIndex];
	}

	std::uint32_t BufferData::Create(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
	{
		if (bufferParams.size() == 0) [[unlikely]]
		{
			throw std::invalid_argument("Buffer params is empty.");
		}
		if (DataCount() + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}
		for (std::size_t i = 0; i < bufferParams.size(); ++i)
		{
			if (bufferParams[i].stride == 0 || bufferParams[i].count == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data buffer at '{}' is empty.", i));
			}
		}
		if (DataTypeIndex(dataType)) [[unlikely]]
		{
			throw std::invalid_argument("Such data type already exists.");
		}

		auto buffers = std::vector<PonyBase::Container::Buffer>();
		buffers.reserve(bufferParams.size());
		for (const PonyBase::Container::BufferParams& bufferParam : bufferParams)
		{
			buffers.push_back(PonyBase::Container::Buffer(bufferParam));
		}

		const std::size_t currentSize = dataTypes.size();
		try
		{
			dataTypes.push_back(std::string(dataType));
			dataBuffers.push_back(std::move(buffers));
		}
		catch (...)
		{
			dataTypes.resize(currentSize);
			dataBuffers.resize(currentSize);

			throw;
		}

		return static_cast<std::uint32_t>(currentSize);
	}

	void BufferData::Destroy(const std::uint32_t dataIndex) noexcept
	{
		dataTypes.erase(dataTypes.begin() + dataIndex);
		dataBuffers.erase(dataBuffers.begin() + dataIndex);
	}

	std::span<const std::byte> BufferData::GetData(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Buffer(dataTypeIndex, dataIndex).Span();
	}

	std::span<const std::byte> BufferData::GetData(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		return Buffer(dataTypeIndex, dataIndex).Span(elementIndex);
	}

	void BufferData::SetData(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const std::byte> data)
	{
		PonyBase::Container::Buffer& buffer = Buffer(dataTypeIndex, dataIndex);

		if (data.size() != buffer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid data size.");
		}

		std::ranges::copy(data, buffer.Data());
	}

	void BufferData::SetData(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const std::span<const std::byte> data)
	{
		PonyBase::Container::Buffer& buffer = Buffer(dataTypeIndex, dataIndex);

		if (data.size() != buffer.Stride()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid data size.");
		}

		std::ranges::copy(data, buffer.Span(elementIndex).data());
	}
}