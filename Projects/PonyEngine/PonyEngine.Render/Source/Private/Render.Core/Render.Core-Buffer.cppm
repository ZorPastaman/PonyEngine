/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render.Core:Buffer;

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

import PonyEngine.Render;

export namespace PonyEngine::Render::Core
{
	class Buffer final : public IBuffer
	{
	public:
		/// @brief Creates an empty buffer data.
		[[nodiscard("Pure constructor")]]
		Buffer() noexcept = default;
		/// @brief Creates a buffer data.
		/// @param bufferParams Buffer parameters.
		[[nodiscard("Pure constructor")]]
		explicit Buffer(const std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>>& bufferParams);
		[[nodiscard("Pure constructor")]]
		Buffer(const Buffer& other) = default;
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		~Buffer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> DataTypeIndex(std::string_view dataType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataTypeCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::size_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;

		/// @brief Creates a new data type.
		/// @note Throws if such a data type already exists.
		/// @param dataType Data type.
		/// @param bufferParams Buffer parameters.
		/// @return Data type index.
		std::uint32_t Create(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		/// @brief Destroys a data.
		/// @param dataIndex Data type index.
		void Destroy(std::uint32_t dataIndex) noexcept;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		/// @brief Sets the data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param data Data.
		void Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const std::byte> data);

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept override;
		/// @brief Sets the data element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @param data Data.
		void Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, std::span<const std::byte> data);

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name) noexcept;

		Buffer& operator =(const Buffer& other) = default;
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		/// @brief Gets the container.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Container.
		[[nodiscard("Pure function")]]
		PonyBase::Container::Buffer& Container(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) noexcept;
		/// @brief Gets the container.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Container.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Container(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;

	private:
		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<PonyBase::Container::Buffer>> dataBuffers; ///< Data buffers.

		std::string_view name; ///< Buffer name.
	};
}

namespace PonyEngine::Render::Core
{
	Buffer::Buffer(const std::unordered_map<std::string, std::vector<PonyBase::Container::BufferParams>>& bufferParams)
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
			bufferCount += params.size();
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
				buffers.emplace_back(param);
			}
			dataBuffers.push_back(std::move(buffers));
		}
	}

	std::optional<std::uint32_t> Buffer::DataTypeIndex(const std::string_view dataType) const noexcept
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

	std::string_view Buffer::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return dataTypes[dataTypeIndex];
	}

	std::uint32_t Buffer::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::size_t Buffer::DataSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Container(dataTypeIndex, dataIndex).Size();
	}

	std::uint32_t Buffer::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(dataBuffers[dataTypeIndex].size());
	}

	std::uint32_t Buffer::DataCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(dataTypes.size()); ++i)
		{
			count += DataCount(i);
		}

		return count;
	}

	std::size_t Buffer::ElementSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Container(dataTypeIndex, dataIndex).Stride();
	}

	std::uint32_t Buffer::ElementCount(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Container(dataTypeIndex, dataIndex).Count();
	}

	std::uint32_t Buffer::Create(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
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
			buffers.emplace_back(bufferParam);
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

	void Buffer::Destroy(const std::uint32_t dataIndex) noexcept
	{
		dataTypes.erase(dataTypes.begin() + dataIndex);
		dataBuffers.erase(dataBuffers.begin() + dataIndex);
	}

	std::span<const std::byte> Buffer::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return Container(dataTypeIndex, dataIndex).Span();
	}

	std::span<const std::byte> Buffer::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		return Container(dataTypeIndex, dataIndex).Span(elementIndex);
	}

	void Buffer::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const std::byte> data)
	{
		PonyBase::Container::Buffer& buffer = Container(dataTypeIndex, dataIndex);

		if (data.size() != buffer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid data size.");
		}

		std::ranges::copy(data, buffer.Data());
	}

	void Buffer::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const std::span<const std::byte> data)
	{
		PonyBase::Container::Buffer& buffer = Container(dataTypeIndex, dataIndex);

		if (data.size() != buffer.Stride()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid data size.");
		}

		std::ranges::copy(data, buffer.Span(elementIndex).data());
	}

	std::string_view Buffer::Name() const noexcept
	{
		return name;
	}

	void Buffer::Name(const std::string_view name) noexcept
	{
		this->name = name;
	}

	PonyBase::Container::Buffer& Buffer::Container(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) noexcept
	{
		return dataBuffers[dataTypeIndex][dataIndex];
	}

	const PonyBase::Container::Buffer& Buffer::Container(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return dataBuffers[dataTypeIndex][dataIndex];
	}
}