/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Mesh;

import <array>;
import <cstdint>;
import <ranges>;
import <span>;
import <string>;
import <string_view>;
import <unordered_map>;
import <vector>;

import PonyBase.Container;

export namespace PonyEngine::Render
{
	class Mesh final
	{
	public:
		using Iterator = std::unordered_map<std::string, PonyBase::Container::Buffer>::iterator;
		using ConstIterator = std::unordered_map<std::string, PonyBase::Container::Buffer>::const_iterator;

		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		PonyBase::Container::Buffer& CreateBuffer(std::string_view dataType, std::uint32_t stride, std::uint32_t count);
		template<typename T>
		PonyBase::Container::BufferView<T> CreateBuffer(std::string_view dataType, std::uint32_t count);

		void DestroyBuffer(std::string_view dataType, std::size_t index) noexcept;
		void DestroyBuffer(const PonyBase::Container::Buffer& buffer) noexcept;
		void DestroyBuffers(std::string_view dataType) noexcept;

		[[nodiscard("Pure function")]]
		std::size_t BufferCount() const noexcept;
		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>>& BufferTables() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<std::uint32_t, 3> ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint32_t, 3> ThreadGroupCounts() const noexcept;

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>> bufferTables;
		std::array<std::uint32_t, 3> threadGroupCounts;
	};
}

namespace PonyEngine::Render
{
	PonyBase::Container::Buffer& Mesh::CreateBuffer(const std::string_view dataType, const std::uint32_t stride, const std::uint32_t count)
	{
		std::vector<PonyBase::Container::Buffer>& bufferTable = bufferTables[std::string(dataType)];
		bufferTable.push_back(PonyBase::Container::Buffer(stride, count));

		return bufferTable.back();
	}

	template<typename T>
	PonyBase::Container::BufferView<T> Mesh::CreateBuffer(const std::string_view dataType, const std::uint32_t count)
	{
		std::vector<PonyBase::Container::Buffer>& bufferTable = bufferTables[std::string(dataType)];
		bufferTable.push_back(PonyBase::Container::Buffer::Create<T>(count));

		return PonyBase::Container::BufferView<T>(&bufferTable.back());
	}

	void Mesh::DestroyBuffer(const std::string_view dataType, const std::size_t index) noexcept
	{
		if (const auto position = std::ranges::find_if(bufferTables, [&](const auto& p) { return p.first == dataType; }); position != bufferTables.cend())
		{
			std::vector<PonyBase::Container::Buffer>& table = position->second;
			table.erase(table.begin() + index);

			if (table.empty())
			{
				bufferTables.erase(position);
			}
		}
	}

	void Mesh::DestroyBuffer(const PonyBase::Container::Buffer& buffer) noexcept
	{
		for (auto& [dataType, bufferTable] : bufferTables)
		{
			if (const auto position = std::ranges::find_if(bufferTable, [&](const PonyBase::Container::Buffer& b) { return &b == &buffer; }); position != bufferTable.cend())
			{
				bufferTable.erase(position);

				if (bufferTable.empty())
				{
					bufferTables.erase(dataType);
				}
			}
		}
	}

	void Mesh::DestroyBuffers(std::string_view dataType) noexcept
	{
		if (const auto position = std::ranges::find_if(bufferTables, [&](const auto& p) { return p.first == dataType; }); position != bufferTables.cend())
		{
			bufferTables.erase(position);
		}
	}

	std::size_t Mesh::BufferCount() const noexcept
	{
		std::size_t count = 0;
		for (const auto& bufferTable : std::ranges::views::values(bufferTables))
		{
			count += bufferTable.size();
		}

		return count;
	}

	const std::unordered_map<std::string, std::vector<PonyBase::Container::Buffer>>& Mesh::BufferTables() const noexcept
	{
		return bufferTables;
	}

	std::span<std::uint32_t, 3> Mesh::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	std::span<const std::uint32_t, 3> Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}
}
