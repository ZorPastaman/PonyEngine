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
import <ranges>;
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

import :IMeshObserver;
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
			BufferAccess(PonyBase::Container::Buffer& buffer, Mesh& mesh, std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept;

			PonyBase::Container::Buffer* buffer;
			Mesh* mesh;
			std::uint32_t dataIndex;
			std::uint32_t bufferIndex;

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
			BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, Mesh& mesh, std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept;

			PonyBase::Container::BufferView<T> bufferView;
			Mesh* mesh;
			std::uint32_t dataIndex;
			std::uint32_t bufferIndex;

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
			BufferTableAccess(std::span<PonyBase::Container::Buffer> buffers, Mesh& mesh, std::uint32_t dataIndex) noexcept;

			std::span<PonyBase::Container::Buffer> buffers;
			Mesh* mesh;
			std::uint32_t dataIndex;

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
		std::span<const std::uint32_t, 3> ThreadGroupCounts() const noexcept;
		void ThreadGroupCounts(std::span<const std::uint32_t, 3> threadGroupCountsToSet);

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view nameToSet);
		void Name(std::string&& nameToSet);

		void AddObserver(IMeshObserver& observer) const;
		void RemoveObserver(IMeshObserver& observer) const noexcept;

		Mesh& operator =(const Mesh& other);
		Mesh& operator =(Mesh&& other) noexcept;

	private:
		void OnMeshChanged() const noexcept;
		void OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;
		void OnThreadGroupCountsChanged() const noexcept;
		void OnNameChanged() const noexcept;

		std::vector<std::string> dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> bufferTables;
		std::array<std::uint32_t, 3> threadGroupCounts;

		std::string name;

		mutable std::vector<IMeshObserver*> meshObservers;
	};
}

namespace PonyEngine::Render
{
	Mesh::BufferAccess::BufferAccess(PonyBase::Container::Buffer& buffer, Mesh& mesh, const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept :
		buffer{&buffer},
		mesh{&mesh},
		dataIndex{dataIndex},
		bufferIndex{bufferIndex}
	{
	}

	const PonyBase::Container::Buffer& Mesh::BufferAccess::Buffer() const noexcept
	{
		return *buffer;
	}

	void Mesh::BufferAccess::Set(const std::size_t index, const std::byte value) noexcept
	{
		buffer->Data()[index] = value;
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	void Mesh::BufferAccess::Set(const std::size_t offset, std::span<const std::byte> data) noexcept
	{
		std::ranges::copy(data, buffer->Data() + offset);
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t index, const T& value) noexcept
	{
		buffer->Get<T>(index) = value;
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t offset, const std::span<const T> data) noexcept
	{
		std::ranges::copy(data, &buffer->Get<T>(offset));
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	Mesh::BufferViewAccess<T>::BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, Mesh& mesh, const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept :
		bufferView(bufferView),
		mesh{&mesh},
		dataIndex{dataIndex},
		bufferIndex{bufferIndex}
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
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferViewAccess<T>::Set(const std::size_t offset, std::span<const T> data) noexcept
	{
		std::ranges::copy(data, bufferView.Data() + offset);
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	Mesh::BufferTableAccess::BufferTableAccess(const std::span<PonyBase::Container::Buffer> buffers, Mesh& mesh, std::uint32_t dataIndex) noexcept :
		buffers(buffers),
		mesh{&mesh},
		dataIndex{dataIndex}
	{
	}

	Mesh::BufferAccess Mesh::BufferTableAccess::Buffer(const std::uint32_t index) noexcept
	{
		return BufferAccess(buffers[index], *mesh, dataIndex, index);
	}

	const PonyBase::Container::Buffer& Mesh::BufferTableAccess::Buffer(const std::uint32_t index) const noexcept
	{
		return buffers[index];
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index)
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(&buffers[index]), *mesh, dataIndex, index);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index) const
	{
		return PonyBase::Container::BufferView<const T>(&buffers[index]);
	}

	Mesh::Mesh() noexcept :
		threadGroupCounts{ 1u, 1u, 1u }
	{
	}

	Mesh::Mesh(const MeshParams& params) :
		threadGroupCounts(params.threadGroupCounts),
		name(params.name)
	{
		std::size_t bufferCount = 0;
		for (const auto& [dataType, bufferTable] : params.bufferTables)
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

		if (std::ranges::find(threadGroupCounts, 0u) != threadGroupCounts.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count is zero.");
		}

		dataTypes.reserve(params.bufferTables.size());
		bufferTables.reserve(params.bufferTables.size());

		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			dataTypes.push_back(std::string(dataType));
			bufferTables.push_back(bufferTable);
		}
	}

	Mesh::Mesh(const std::span<const std::uint32_t, 3> threadGroupCounts) noexcept
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
		threadGroupCounts(other.threadGroupCounts)
	{
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		dataTypes(std::move(other.dataTypes)),
		bufferTables(std::move(other.bufferTables)),
		threadGroupCounts(std::move(other.threadGroupCounts))
	{
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

		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (BufferCount() - BufferCount(dataIndex.value()) + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
			}
			bufferTables[dataIndex.value()] = std::move(buffers);

			OnMeshChanged();

			return BufferTableAccess(bufferTables[dataIndex.value()], *this, dataIndex.value());
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

		OnMeshChanged();

		return BufferTableAccess(bufferTables.back(), *this, static_cast<std::uint32_t>(currentSize));
	}

	void Mesh::DestroyBufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = DataIndex(dataType))
		{
			dataTypes.erase(dataTypes.begin() + tableIndex.value());
			bufferTables.erase(bufferTables.begin() + tableIndex.value());
			OnMeshChanged();
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
		return BufferAccess(bufferTables[dataIndex][bufferIndex], *this, dataIndex, bufferIndex);
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
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(bufferTables[dataIndex], *this, dataIndex, bufferIndex));
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
		return BufferTableAccess(bufferTables[dataIndex], *this, dataIndex);
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

	std::span<const std::uint32_t, 3> Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Mesh::ThreadGroupCounts(std::span<const std::uint32_t, 3> threadGroupCountsToSet)
	{
		if (std::memcmp(threadGroupCounts.data(), threadGroupCountsToSet.data(), sizeof(threadGroupCounts)) == 0)
		{
			return;
		}

		if (std::ranges::find(threadGroupCountsToSet, 0u) != threadGroupCountsToSet.end()) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count is zero.");
		}

		std::ranges::copy(threadGroupCountsToSet, threadGroupCounts.begin());
		OnThreadGroupCountsChanged();
	}

	std::string_view Mesh::Name() const noexcept
	{
		return name;
	}

	void Mesh::Name(const std::string_view nameToSet)
	{
		if (name == nameToSet)
		{
			return;
		}

		name = nameToSet;
		OnNameChanged();
	}

	void Mesh::Name(std::string&& nameToSet)
	{
		if (name == nameToSet)
		{
			return;
		}

		name = std::move(nameToSet);
		OnNameChanged();
	}

	void Mesh::AddObserver(IMeshObserver& observer) const
	{
		meshObservers.push_back(&observer);
	}

	void Mesh::RemoveObserver(IMeshObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(meshObservers, &observer); position != meshObservers.cend()) [[likely]]
		{
			meshObservers.erase(position);
		}
	}

	void Mesh::OnMeshChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnMeshChanged();
		}
	}

	void Mesh::OnBufferChanged(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnBufferChanged(dataIndex, bufferIndex);
		}
	}

	void Mesh::OnThreadGroupCountsChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnThreadGroupCountsChanged();
		}
	}

	void Mesh::OnNameChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnNameChanged();
		}
	}

	Mesh& Mesh::operator =(const Mesh& other)
	{
		std::vector<std::string> newDataTypes = other.dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> newBufferTables = other.bufferTables;
		dataTypes = std::move(newDataTypes);
		bufferTables = std::move(newBufferTables);
		OnMeshChanged();

		ThreadGroupCounts(other.threadGroupCounts);
		Name(other.name);

		return *this;
	}

	Mesh& Mesh::operator =(Mesh&& other) noexcept
	{
		dataTypes = std::move(other.dataTypes);
		bufferTables = std::move(other.bufferTables);
		OnMeshChanged();

		ThreadGroupCounts(other.threadGroupCounts);
		Name(std::move(other.name));

		return *this;
	}
}
