/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Mesh;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
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

import :MeshParams;

export namespace PonyEngine::Render
{
	class Mesh final
	{
	public:
		static constexpr std::uint32_t InitialVersion = 1u;

		class BufferTableAccess;

		class BufferAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferAccess(const BufferAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferAccess(BufferAccess&& other) noexcept = default;

			~BufferAccess() noexcept = default;

			[[nodiscard("Pure function")]]
			const PonyBase::Container::Buffer& Buffer() const noexcept;

			void Set(std::size_t index, std::byte value) noexcept;
			void Set(std::size_t offset, std::span<const std::byte> data) noexcept;
			template<typename T>
			void Set(std::size_t index, const T& value) noexcept;
			template<typename T>
			void Set(std::size_t offset, std::span<const T> data) noexcept;

			BufferAccess& operator =(const BufferAccess& other) noexcept = default;
			BufferAccess& operator =(BufferAccess&& other) noexcept = default;

		private:
			[[nodiscard("Pure constructor")]]
			BufferAccess(PonyBase::Container::Buffer& buffer, std::uint64_t& version) noexcept;

			PonyBase::Container::Buffer* buffer;
			std::uint64_t* version;

			friend Mesh;
			friend BufferTableAccess;
		};

		template<typename T>
		class BufferViewAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(const BufferViewAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(BufferViewAccess&& other) noexcept = default;

			~BufferViewAccess() noexcept = default;

			[[nodiscard("Pure function")]]
			const PonyBase::Container::BufferView<T>& BufferView() const noexcept;

			void Set(std::size_t index, const T& value) noexcept;
			void Set(std::size_t offset, std::span<const T> data) noexcept;

			BufferViewAccess& operator =(const BufferViewAccess& other) noexcept = default;
			BufferViewAccess& operator =(BufferViewAccess&& other) noexcept = default;

		private:
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, std::uint64_t& version) noexcept;

			PonyBase::Container::BufferView<T> bufferView;
			std::uint64_t* version;

			friend Mesh;
			friend BufferTableAccess;
		};

		class BufferTableAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(const BufferTableAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(BufferTableAccess&& other) noexcept = default;

			~BufferTableAccess() noexcept = default;

			[[nodiscard("Pure function")]]
			BufferAccess Buffer(std::uint32_t index) noexcept;
			[[nodiscard("Pure function")]]
			const PonyBase::Container::Buffer& Buffer(std::uint32_t index) const noexcept;

			template<typename T> [[nodiscard("Pure function")]]
			BufferViewAccess<T> BufferView(std::uint32_t index);
			template<typename T> [[nodiscard("Pure function")]]
			PonyBase::Container::BufferView<const T> BufferView(std::uint32_t index) const;

			BufferTableAccess& operator =(const BufferTableAccess& other) noexcept = default;
			BufferTableAccess& operator =(BufferTableAccess&& other) noexcept = default;

		private:
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(std::span<PonyBase::Container::Buffer> buffers, std::span<std::uint64_t> versions) noexcept;

			std::span<PonyBase::Container::Buffer> buffers;
			std::span<std::uint64_t> versions;

			friend Mesh;
		};

		[[nodiscard("Pure constructor")]]
		Mesh() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit Mesh(const MeshParams& params);
		[[nodiscard("Pure constructor")]]
		explicit Mesh(std::span<const std::uint32_t, 3> threadGroupCounts) noexcept;
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other);
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept;

		~Mesh() noexcept = default;

		BufferTableAccess CreateBufferTable(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		void DestroyBufferTable(std::string_view dataType) noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataIndex(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> BufferCount(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount() const noexcept;

		[[nodiscard("Pure function")]]
		BufferAccess Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& BufferConst(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<BufferAccess> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* BufferConst(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;

		template<typename T> [[nodiscard("Pure function")]]
		BufferViewAccess<T> Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<const T> Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<const T> BufferConst(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<BufferViewAccess<T>> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> BufferConst(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;

		[[nodiscard("Pure function")]]
		BufferTableAccess BufferTable(std::uint32_t dataIndex) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTable(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTableConst(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<BufferTableAccess> BufferTable(std::string_view dataType) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTable(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTableConst(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		std::uint64_t BufferVersion(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint64_t> BufferVersions(std::uint32_t dataIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::optional<std::uint64_t> BufferVersion(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint64_t> BufferVersions(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint64_t MeshVersion() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::uint32_t, 3> ThreadGroupCounts() const noexcept;
		void ThreadGroupCounts(std::span<const std::uint32_t, 3> threadGroupCountsToSet);
		[[nodiscard("Pure function")]]
		std::uint32_t ThreadGroupCountsVersion() const noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view nameToSet);
		[[nodiscard("Pure function")]]
		std::uint64_t NameVersion() const noexcept;

		Mesh& operator =(const Mesh& other);
		Mesh& operator =(Mesh&& other) noexcept;

	private:
		[[nodiscard("Pure function")]]
		std::size_t BufferCountInternal() const noexcept;

		std::vector<std::string> dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> bufferTables;
		std::vector<std::vector<std::uint64_t>> bufferVersions;
		std::uint64_t meshVersion;

		std::array<std::uint32_t, 3> threadGroupCounts;
		std::uint32_t threadGroupCountVersion;

		std::string name;
		std::uint64_t nameVersion;
	};
}

namespace PonyEngine::Render
{
	Mesh::BufferAccess::BufferAccess(PonyBase::Container::Buffer& buffer, std::uint64_t& version) noexcept :
		buffer{&buffer},
		version{&version}
	{
	}

	const PonyBase::Container::Buffer& Mesh::BufferAccess::Buffer() const noexcept
	{
		return *buffer;
	}

	void Mesh::BufferAccess::Set(const std::size_t index, const std::byte value) noexcept
	{
		buffer->Data()[index] = value;
		++*version;
	}

	void Mesh::BufferAccess::Set(const std::size_t offset, std::span<const std::byte> data) noexcept
	{
		std::ranges::copy(data, buffer->Data() + offset);
		++*version;
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t index, const T& value) noexcept
	{
		buffer->Get<T>(index) = value;
		++*version;
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t offset, const std::span<const T> data) noexcept
	{
		std::ranges::copy(data, &buffer->Get<T>(offset));
		++*version;
	}

	template<typename T>
	Mesh::BufferViewAccess<T>::BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, std::uint64_t& version) noexcept :
		bufferView(bufferView),
		version{&version}
	{
	}


	template<typename T>
	const PonyBase::Container::BufferView<T>& Mesh::BufferViewAccess<T>::BufferView() const noexcept
	{
		return bufferView;
	}

	template<typename T>
	void Mesh::BufferViewAccess<T>::Set(const std::size_t index, const T& value) noexcept
	{
		bufferView[index] = value;
		++*version;
	}

	template<typename T>
	void Mesh::BufferViewAccess<T>::Set(const std::size_t offset, std::span<const T> data) noexcept
	{
		std::ranges::copy(data, bufferView.Data() + offset);
		++*version;
	}

	Mesh::BufferTableAccess::BufferTableAccess(const std::span<PonyBase::Container::Buffer> buffers, const std::span<std::uint64_t> versions) noexcept :
		buffers(buffers),
		versions(versions)
	{
	}

	Mesh::BufferAccess Mesh::BufferTableAccess::Buffer(const std::uint32_t index) noexcept
	{
		return BufferAccess(buffers[index], versions[index]);
	}

	const PonyBase::Container::Buffer& Mesh::BufferTableAccess::Buffer(const std::uint32_t index) const noexcept
	{
		return buffers[index];
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index)
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(&buffers[index]), versions[index]);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index) const
	{
		return PonyBase::Container::BufferView<const T>(&buffers[index]);
	}

	Mesh::Mesh() noexcept :
		meshVersion{InitialVersion},
		threadGroupCounts{ 1u, 1u, 1u },
		threadGroupCountVersion{InitialVersion},
		nameVersion{InitialVersion}
	{
	}

	Mesh::Mesh(const MeshParams& params) :
		meshVersion{InitialVersion},
		threadGroupCounts(params.threadGroupCounts),
		threadGroupCountVersion{InitialVersion},
		name(params.name),
		nameVersion{InitialVersion}
	{
		if (params.bufferTables.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer table count exceeds std::uint32_t max value.");
		}

		if (std::ranges::find(threadGroupCounts, 0u) != threadGroupCounts.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count is zero.");
		}

		dataTypes.reserve(params.bufferTables.size());
		bufferTables.reserve(params.bufferTables.size());
		bufferVersions.reserve(params.bufferTables.size());

		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			if (bufferTable.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data table of '{}' is empty.", dataType));
			}
			if (bufferTable.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Buffer table size exceeds std::uint32_t max value.");
			}

			dataTypes.push_back(std::string(dataType));
			bufferTables.push_back(bufferTable);
			bufferVersions.push_back(std::vector<std::uint64_t>(bufferTable.size(), InitialVersion));
		}

		if (BufferCountInternal() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}
	}

	Mesh::Mesh(const std::span<const std::uint32_t, 3> threadGroupCounts) noexcept :
		meshVersion{InitialVersion},
		threadGroupCountVersion{InitialVersion},
		nameVersion{InitialVersion}
	{
		if (std::ranges::find(threadGroupCounts, 0u) != threadGroupCounts.end()) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count is zero.");
		}

		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
	}

	Mesh::Mesh(const Mesh& other) :
		dataTypes(other.dataTypes),
		bufferTables(other.bufferTables),
		bufferVersions(other.bufferVersions),
		meshVersion{InitialVersion},
		threadGroupCounts(other.threadGroupCounts),
		threadGroupCountVersion{InitialVersion},
		nameVersion{InitialVersion}
	{
		for (std::vector<std::uint64_t>& versions : bufferVersions)
		{
			std::ranges::fill(versions, InitialVersion);
		}
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		dataTypes(std::move(other.dataTypes)),
		bufferTables(std::move(other.bufferTables)),
		bufferVersions(std::move(other.bufferVersions)),
		meshVersion{InitialVersion},
		threadGroupCounts(std::move(other.threadGroupCounts)),
		threadGroupCountVersion{InitialVersion},
		nameVersion{InitialVersion}
	{
		for (std::vector<std::uint64_t>& versions : bufferVersions)
		{
			std::ranges::fill(versions, InitialVersion);
		}
	}

	Mesh::BufferTableAccess Mesh::CreateBufferTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
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
		auto versions = std::vector<std::uint64_t>(buffers.size(), InitialVersion);

		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (BufferCountInternal() - BufferCount(dataIndex.value()) + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
			}

			++meshVersion;
			bufferTables[dataIndex.value()] = std::move(buffers);
			bufferVersions[dataIndex.value()] = std::move(versions);

			return BufferTableAccess(bufferTables[dataIndex.value()], bufferVersions[dataIndex.value()]);
		}

		const std::size_t newSize = dataTypes.size() + 1;
		if (BufferCountInternal() + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
		}
		dataTypes.reserve(newSize);
		bufferTables.reserve(newSize);
		bufferVersions.reserve(newSize);

		++meshVersion;
		dataTypes.push_back(std::string(dataType));
		bufferTables.push_back(std::move(buffers));
		bufferVersions.push_back(std::move(versions));

		return BufferTableAccess(bufferTables.back(), bufferVersions.back());
	}

	void Mesh::DestroyBufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = DataIndex(dataType))
		{
			++meshVersion;
			dataTypes.erase(dataTypes.begin() + tableIndex.value());
			bufferTables.erase(bufferTables.begin() + tableIndex.value());
			bufferVersions.erase(bufferVersions.begin() + tableIndex.value());
		}
	}

	std::optional<std::uint32_t> Mesh::DataIndex(const std::string_view dataType) const noexcept
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

	std::string_view Mesh::DataType(const std::uint32_t dataIndex) const noexcept
	{
		return dataTypes[dataIndex];
	}

	std::uint32_t Mesh::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::uint32_t Mesh::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferTables[dataIndex].size());
	}

	std::optional<std::uint32_t> Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferCount(dataIndex.value());
		}

		return std::nullopt;
	}

	std::uint32_t Mesh::BufferCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < dataTypes.size(); ++i)
		{
			count += BufferCount(i);
		}

		return count;
	}

	Mesh::BufferAccess Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept
	{
		return BufferAccess(bufferTables[dataIndex][bufferIndex], bufferVersions[dataIndex][bufferIndex]);
	}

	const PonyBase::Container::Buffer& Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferTables[dataIndex][bufferIndex];
	}

	const PonyBase::Container::Buffer& Mesh::BufferConst(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer(dataIndex, bufferIndex);
	}

	std::optional<Mesh::BufferAccess> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType) && bufferIndex < BufferCount(dataIndex.value()))
		{
			return Buffer(dataIndex.value(), bufferIndex);
		}

		return std::nullopt;
	}

	const PonyBase::Container::Buffer* Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType) && bufferIndex < BufferCount(dataIndex.value()))
		{
			return &Buffer(dataIndex.value(), bufferIndex);
		}

		return nullptr;
	}

	const PonyBase::Container::Buffer* Mesh::BufferConst(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer(dataType, bufferIndex);
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(bufferTables[dataIndex], &bufferVersions[dataIndex][bufferIndex]));
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return PonyBase::Container::BufferView<const T>(bufferTables[dataIndex][bufferIndex]);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferConst(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer<T>(dataIndex, bufferIndex);
	}

	template<typename T>
	std::optional<Mesh::BufferViewAccess<T>> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType); dataIndex && bufferIndex < BufferCount(dataIndex.value()))
		{
			if (const std::vector<PonyBase::Container::Buffer>& table = bufferTables[dataIndex.value()]; bufferIndex < table.size() && table[bufferIndex].Stride() == sizeof(T))
			{
				return Buffer(dataIndex.value(), bufferIndex);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::size_t> dataIndex = DataIndex(dataType))
		{
			if (const std::vector<PonyBase::Container::Buffer>& table = bufferTables[dataIndex.value()]; bufferIndex < table.size() && table[bufferIndex].Stride() == sizeof(T))
			{
				return Buffer(dataIndex.value(), bufferIndex);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::BufferConst(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer<T>(dataType, bufferIndex);
	}

	Mesh::BufferTableAccess Mesh::BufferTable(const std::uint32_t dataIndex) noexcept
	{
		return BufferTableAccess(bufferTables[dataIndex], bufferVersions[dataIndex]);
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTable(const std::uint32_t dataIndex) const noexcept
	{
		return bufferTables[dataIndex];
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTableConst(const std::uint32_t dataIndex) const noexcept
	{
		return bufferTables[dataIndex];
	}

	std::optional<Mesh::BufferTableAccess> Mesh::BufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferTable(dataIndex.value());
		}

		return std::nullopt;
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTable(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferTable(dataIndex.value());
		}

		return std::span<const PonyBase::Container::Buffer>();
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTableConst(const std::string_view dataType) const noexcept
	{
		return BufferTable(dataType);
	}

	std::uint64_t Mesh::BufferVersion(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferVersions[dataIndex][bufferIndex];
	}

	std::span<const std::uint64_t> Mesh::BufferVersions(const std::uint32_t dataIndex) const noexcept
	{
		return bufferVersions[dataIndex];
	}

	std::optional<std::uint64_t> Mesh::BufferVersion(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType); dataIndex && bufferIndex < bufferVersions[dataIndex.value()].size())
		{
			return BufferVersion(dataIndex.value(), bufferIndex);
		}

		return std::nullopt;
	}

	std::span<const std::uint64_t> Mesh::BufferVersions(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> tableIndex = DataIndex(dataType))
		{
			return bufferVersions[tableIndex.value()];
		}

		return std::span<const std::uint64_t>();
	}

	std::uint64_t Mesh::MeshVersion() const noexcept
	{
		return meshVersion;
	}

	std::span<const std::uint32_t, 3> Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Mesh::ThreadGroupCounts(std::span<const std::uint32_t, 3> threadGroupCountsToSet)
	{
		if (std::ranges::find(threadGroupCountsToSet, 0u) != threadGroupCountsToSet.end()) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count is zero.");
		}

		std::ranges::copy(threadGroupCountsToSet, threadGroupCounts.begin());
		++threadGroupCountVersion;
	}

	std::uint32_t Mesh::ThreadGroupCountsVersion() const noexcept
	{
		return threadGroupCountVersion;
	}

	std::string_view Mesh::Name() const noexcept
	{
		return name;
	}

	void Mesh::Name(const std::string_view nameToSet)
	{
		name = nameToSet;
		++nameVersion;
	}

	std::uint64_t Mesh::NameVersion() const noexcept
	{
		return nameVersion;
	}

	Mesh& Mesh::operator =(const Mesh& other)
	{
		std::vector<std::string> newDataTypes = other.dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> newBufferTables = other.bufferTables;
		std::vector<std::vector<std::uint64_t>> newBufferVersions = other.bufferVersions;
		for (std::vector<std::uint64_t> versions : newBufferVersions)
		{
			std::ranges::fill(versions, InitialVersion);
		}

		++meshVersion;
		dataTypes = std::move(newDataTypes);
		bufferTables = std::move(newBufferTables);
		bufferVersions = std::move(newBufferVersions);

		threadGroupCounts = other.threadGroupCounts;
		++threadGroupCountVersion;

		name = other.name;
		++nameVersion;

		return *this;
	}

	Mesh& Mesh::operator =(Mesh&& other) noexcept
	{
		++meshVersion;
		dataTypes = std::move(other.dataTypes);
		bufferTables = std::move(other.bufferTables);
		bufferVersions = std::move(other.bufferVersions);
		for (std::vector<std::uint64_t> versions : bufferVersions)
		{
			std::ranges::fill(versions, InitialVersion);
		}

		threadGroupCounts = std::move(other.threadGroupCounts);
		++threadGroupCountVersion;

		name = std::move(other.name);
		++nameVersion;

		return *this;
	}

	std::size_t Mesh::BufferCountInternal() const noexcept
	{
		std::size_t count = 0u;
		for (std::uint32_t i = 0; i < dataTypes.size(); ++i)
		{
			count += BufferCount(i);
		}

		return count;
	}
}
