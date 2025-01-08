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
			BufferAccess Buffer(std::size_t index) noexcept;
			[[nodiscard("Pure function")]]
			const PonyBase::Container::Buffer& Buffer(std::size_t index) const noexcept;

			template<typename T> [[nodiscard("Pure function")]]
			BufferViewAccess<T> BufferView(std::size_t index);
			template<typename T> [[nodiscard("Pure function")]]
			PonyBase::Container::BufferView<const T> BufferView(std::size_t index) const;

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
		Mesh() noexcept = default;
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
		std::span<const std::string> DataTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::size_t> BufferCount(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t BufferCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<BufferAccess> FindBuffer(std::string_view dataType, std::size_t index = 0) noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* FindBuffer(std::string_view dataType, std::size_t index = 0) const noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* FindBufferConst(std::string_view dataType, std::size_t index = 0) const noexcept;

		template<typename T> [[nodiscard("Pure function")]]
		std::optional<BufferViewAccess<T>> FindBuffer(std::string_view dataType, std::size_t index = 0) noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> FindBuffer(std::string_view dataType, std::size_t index = 0) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> FindBufferConst(std::string_view dataType, std::size_t index = 0) noexcept;

		[[nodiscard("Pure function")]]
		std::optional<BufferTableAccess> FindBufferTable(std::string_view dataType) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> FindBufferTable(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> FindBufferTableConst(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::uint64_t> BufferVersion(std::string_view dataType, std::size_t index = 0) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint64_t> BufferVersions(std::string_view dataType) const noexcept;
		[[nodiscard("Pure function")]]
		std::uint64_t MeshVersion() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<std::uint32_t, 3> ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint32_t, 3> ThreadGroupCounts() const noexcept;

		Mesh& operator =(const Mesh& other);
		Mesh& operator =(Mesh&& other) noexcept;

	private:
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> IndexOf(std::string_view dataType) const noexcept;

		std::vector<std::string> dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> bufferTables;
		std::vector<std::vector<std::uint64_t>> bufferVersions;
		std::uint64_t meshVersion;

		std::array<std::uint32_t, 3> threadGroupCounts;
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

	Mesh::BufferAccess Mesh::BufferTableAccess::Buffer(const std::size_t index) noexcept
	{
		return BufferAccess(buffers[index], versions[index]);
	}

	const PonyBase::Container::Buffer& Mesh::BufferTableAccess::Buffer(const std::size_t index) const noexcept
	{
		return buffers[index];
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::BufferTableAccess::BufferView(const std::size_t index)
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(&buffers[index]), versions[index]);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferTableAccess::BufferView(const std::size_t index) const
	{
		return PonyBase::Container::BufferView<const T>(&buffers[index]);
	}

	Mesh::Mesh(const MeshParams& params) :
		meshVersion{0UL},
		threadGroupCounts(params.threadGroupCounts)
	{
		dataTypes.reserve(params.bufferTables.size());
		bufferTables.reserve(params.bufferTables.size());
		bufferVersions.reserve(params.bufferTables.size());

		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			if (bufferTable.size() == 0)
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data table of '{}' is empty.", dataType));
			}

			dataTypes.push_back(std::string(dataType));
			bufferTables.push_back(bufferTable);
			bufferVersions.push_back(std::vector<std::uint64_t>(bufferTable.size(), 0UL));
		}
	}

	Mesh::Mesh(const std::span<const std::uint32_t, 3> threadGroupCounts) noexcept :
		meshVersion{0UL}
	{
		std::ranges::copy(threadGroupCounts, this->threadGroupCounts.begin());
	}

	Mesh::Mesh(const Mesh& other) :
		dataTypes(other.dataTypes),
		bufferTables(other.bufferTables),
		bufferVersions(other.bufferVersions),
		meshVersion{0UL},
		threadGroupCounts(other.threadGroupCounts)
	{
		for (std::vector<std::uint64_t>& versions : bufferVersions)
		{
			std::ranges::fill(versions, 0UL);
		}
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		dataTypes(std::move(other.dataTypes)),
		bufferTables(std::move(other.bufferTables)),
		bufferVersions(std::move(other.bufferVersions)),
		meshVersion{0UL},
		threadGroupCounts(std::move(other.threadGroupCounts))
	{
		for (std::vector<std::uint64_t>& versions : bufferVersions)
		{
			std::ranges::fill(versions, 0UL);
		}
	}

	Mesh::BufferTableAccess Mesh::CreateBufferTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
	{
		if (bufferParams.size() == 0)
		{
			throw std::invalid_argument("Buffer params is empty.");
		}

		auto buffers = std::vector<PonyBase::Container::Buffer>();
		buffers.reserve(bufferParams.size());
		for (const PonyBase::Container::BufferParams& bufferParam : bufferParams)
		{
			buffers.push_back(PonyBase::Container::Buffer(bufferParam));
		}
		auto versions = std::vector<std::uint64_t>(buffers.size(), 0UL);

		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			++meshVersion;
			bufferTables[tableIndex.value()] = std::move(buffers);
			bufferVersions[tableIndex.value()] = std::move(versions);

			return BufferTableAccess(bufferTables[tableIndex.value()], bufferVersions[tableIndex.value()]);
		}

		const std::size_t newSize = dataTypes.size() + 1;
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
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			++meshVersion;
			dataTypes.erase(dataTypes.begin() + tableIndex.value());
			bufferTables.erase(bufferTables.begin() + tableIndex.value());
			bufferVersions.erase(bufferVersions.begin() + tableIndex.value());
		}
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::optional<std::size_t> Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> index = IndexOf(dataType))
		{
			return bufferTables[index.value()].size();
		}

		return std::nullopt;
	}

	std::size_t Mesh::BufferCount() const noexcept
	{
		std::size_t count = 0;
		for (const std::string& dataType : dataTypes)
		{
			count += BufferCount(dataType).value();
		}

		return count;
	}

	std::optional<Mesh::BufferAccess> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType) && index < bufferTables[tableIndex.value()].size())
		{
			return BufferAccess(bufferTables[tableIndex.value()][index], bufferVersions[tableIndex.value()][index]);
		}

		return std::nullopt;
	}

	const PonyBase::Container::Buffer* Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType) && index < bufferTables[tableIndex.value()].size())
		{
			return &bufferTables[tableIndex.value()][index];
		}

		return nullptr;
	}

	const PonyBase::Container::Buffer* Mesh::FindBufferConst(const std::string_view dataType, const std::size_t index) const noexcept
	{
		return FindBuffer(dataType, index);
	}

	template<typename T>
	std::optional<Mesh::BufferViewAccess<T>> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			if (std::vector<PonyBase::Container::Buffer>& table = bufferTables[tableIndex.value()]; index < table.size() && table[index].Stride() == sizeof(T))
			{
				return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(table[index]), &bufferVersions[tableIndex.value()][index]);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::FindBuffer(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			if (const std::vector<PonyBase::Container::Buffer>& table = bufferTables[tableIndex.value()]; index < table.size() && table[index].Stride() == sizeof(T))
			{
				return PonyBase::Container::BufferView<const T>(table[index]);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::FindBufferConst(const std::string_view dataType, const std::size_t index) noexcept
	{
		return FindBuffer<T>(dataType, index);
	}

	std::optional<Mesh::BufferTableAccess> Mesh::FindBufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			return BufferTableAccess(bufferTables[tableIndex.value()], bufferVersions[tableIndex.value()]);
		}

		return std::nullopt;
	}

	std::span<const PonyBase::Container::Buffer> Mesh::FindBufferTable(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			return bufferTables[tableIndex.value()];
		}

		return std::span<const PonyBase::Container::Buffer>();
	}

	std::span<const PonyBase::Container::Buffer> Mesh::FindBufferTableConst(const std::string_view dataType) const noexcept
	{
		return FindBufferTable(dataType);
	}

	std::optional<std::uint64_t> Mesh::BufferVersion(const std::string_view dataType, const std::size_t index) const noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType); tableIndex && index < bufferVersions[tableIndex.value()].size())
		{
			return bufferVersions[tableIndex.value()][index];
		}

		return std::nullopt;
	}

	std::span<const std::uint64_t> Mesh::BufferVersions(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::size_t> tableIndex = IndexOf(dataType))
		{
			return bufferVersions[tableIndex.value()];
		}

		return std::span<const std::uint64_t>();
	}

	std::uint64_t Mesh::MeshVersion() const noexcept
	{
		return meshVersion;
	}

	std::span<std::uint32_t, 3> Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	std::span<const std::uint32_t, 3> Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	Mesh& Mesh::operator =(const Mesh& other)
	{
		std::vector<std::string> newDataTypes = other.dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> newBufferTables = other.bufferTables;
		std::vector<std::vector<std::uint64_t>> newBufferVersions = other.bufferVersions;
		for (std::vector<std::uint64_t> versions : newBufferVersions)
		{
			std::ranges::fill(versions, 0UL);
		}

		++meshVersion;
		dataTypes = std::move(newDataTypes);
		bufferTables = std::move(newBufferTables);
		bufferVersions = std::move(newBufferVersions);
		threadGroupCounts = other.threadGroupCounts;

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
			std::ranges::fill(versions, 0UL);
		}
		threadGroupCounts = std::move(other.threadGroupCounts);

		return *this;
	}

	std::optional<std::size_t> Mesh::IndexOf(const std::string_view dataType) const noexcept
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
}
