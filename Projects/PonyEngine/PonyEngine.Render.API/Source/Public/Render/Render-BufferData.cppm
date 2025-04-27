/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:BufferData;

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
		/// @param bufferTables Buffer tables.
		[[nodiscard("Pure constructor")]]
		explicit BufferData(const std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>>& bufferTables);
		[[nodiscard("Pure constructor")]]
		BufferData(const BufferData& other) = default;
		[[nodiscard("Pure constructor")]]
		BufferData(BufferData&& other) noexcept = default;

		~BufferData() noexcept = default;

		/// @brief Tries to find a data index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;
		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		/// @brief Gets the buffer count by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets the buffer count of all the tables.
		/// @return Buffer count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount() const noexcept;

		/// @brief Gets the buffer.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;

		/// @brief Creates a buffer table or overrides an existing one if their data types are the same.
		/// @param dataType Data type.
		/// @param bufferParams Buffer parameters.
		/// @return Data type index.
		std::uint32_t CreateBufferTable(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		/// @brief Destroys a buffer table.
		/// @param dataIndex Data type index.
		void DestroyBufferTable(std::uint32_t dataIndex) noexcept;

		/// @brief Sets the data to a buffer.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param data Data.
		/// @param offset Data offset in bytes.
		void SetData(std::uint32_t dataIndex, std::uint32_t bufferIndex, std::span<const std::byte> data, std::size_t offset = 0);
		/// @brief Sets a value to a buffer.
		/// @tparam T Value type.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param value Value.
		/// @param index Value index.
		template<typename T>
		void SetData(std::uint32_t dataIndex, std::uint32_t bufferIndex, const T& value, std::size_t index = 0);
		/// @brief Sets the data to a buffer.
		/// @tparam T Value type.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param data Data.
		/// @param startIndex Start index.
		template<typename T>
		void SetData(std::uint32_t dataIndex, std::uint32_t bufferIndex, std::span<const T> data, std::size_t startIndex = 0);

		BufferData& operator =(const BufferData& other) = default;
		BufferData& operator =(BufferData&& other) noexcept = default;

	private:
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<PonyBase::Container::Buffer>> bufferTables; ///< Buffer tables.
	};
}

namespace PonyEngine::Render
{
	BufferData::BufferData(const std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>>& bufferTables)
	{
		std::size_t bufferCount = 0;
		for (const auto& [dataType, bufferTable] : bufferTables)
		{
			if (bufferTable.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data table of '{}' is empty.", dataType));
			}
			bufferCount += bufferTable.size();
		}
		if (bufferCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		dataTypes.reserve(bufferTables.size());
		this->bufferTables.reserve(bufferTables.size());

		for (const auto& [dataType, bufferTable] : bufferTables)
		{
			dataTypes.push_back(dataType);
			this->bufferTables.push_back(bufferTable);
		}
	}

	std::optional<std::uint32_t> BufferData::DataIndex(const std::string_view dataType) const noexcept
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

	std::string_view BufferData::DataType(const std::uint32_t dataIndex) const noexcept
	{
		return dataTypes[dataIndex];
	}

	std::uint32_t BufferData::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::span<const std::string> BufferData::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::uint32_t BufferData::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferTables[dataIndex].size());
	}

	std::uint32_t BufferData::BufferCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(dataTypes.size()); ++i)
		{
			count += BufferCount(i);
		}

		return count;
	}

	const PonyBase::Container::Buffer& BufferData::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferTables[dataIndex][bufferIndex];
	}

	std::uint32_t BufferData::CreateBufferTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
	{
		if (bufferParams.size() == 0) [[unlikely]]
		{
			throw std::invalid_argument("Buffer params is empty.");
		}
		if (bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		auto buffers = std::vector<PonyBase::Container::Buffer>();
		buffers.reserve(bufferParams.size());
		for (const PonyBase::Container::BufferParams& bufferParam : bufferParams)
		{
			buffers.push_back(PonyBase::Container::Buffer(bufferParam));
		}

		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (BufferCount() - BufferCount(dataIndex.value()) + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
			}
			bufferTables[dataIndex.value()] = std::move(buffers);

			return dataIndex.value();
		}

		if (BufferCount() + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
		}

		const std::size_t currentSize = dataTypes.size();
		try
		{
			dataTypes.push_back(std::string(dataType));
			bufferTables.push_back(std::move(buffers));
		}
		catch (...)
		{
			dataTypes.resize(currentSize);
			bufferTables.resize(currentSize);

			throw;
		}

		return static_cast<std::uint32_t>(currentSize);
	}

	void BufferData::DestroyBufferTable(const std::uint32_t dataIndex) noexcept
	{
		dataTypes.erase(dataTypes.begin() + dataIndex);
		bufferTables.erase(bufferTables.begin() + dataIndex);
	}

	void BufferData::SetData(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const std::byte> data, const std::size_t offset)
	{
		if (data.size() + offset > bufferTables[dataIndex][bufferIndex].Size()) [[unlikely]]
		{
			throw std::invalid_argument("Data size exceeds buffer size.");
		}

		std::ranges::copy(data, bufferTables[dataIndex][bufferIndex].Data() + offset);
	}

	template <typename T>
	void BufferData::SetData(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const T& value, const std::size_t index)
	{
		bufferTables[dataIndex][bufferIndex].Get<T>(index) = value;
	}

	template <typename T>
	void BufferData::SetData(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const T> data, const std::size_t startIndex)
	{
		const std::span<T> bufferSpan = bufferTables[dataIndex][bufferIndex].Span<T>();
		if (data.size() + startIndex > bufferSpan.size()) [[unlikely]]
		{
			throw std::invalid_argument("Data size exceeds buffer size.");
		}

		std::ranges::copy(data, bufferSpan.data() + startIndex);
	}
}
