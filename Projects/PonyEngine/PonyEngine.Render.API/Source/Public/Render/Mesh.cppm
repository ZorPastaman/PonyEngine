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
import <span>;
import <string>;
import <string_view>;
import <unordered_map>;

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

		void DestroyBuffer(std::string_view dataType) noexcept;
		void DestroyBuffer(const PonyBase::Container::Buffer& buffer) noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Container::Buffer* FindBuffer(std::string_view dataType) noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* FindBuffer(std::string_view dataType) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<T> FindBuffer(std::string_view dataType) noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<const T> FindBuffer(std::string_view dataType) const noexcept;

		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, PonyBase::Container::Buffer>& Buffers() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<std::uint32_t, 3> ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::uint32_t, 3> ThreadGroupCounts() const noexcept;

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::unordered_map<std::string, PonyBase::Container::Buffer> buffers;
		std::array<std::uint32_t, 3> threadGroupCounts;
	};
}

namespace PonyEngine::Render
{
	PonyBase::Container::Buffer& Mesh::CreateBuffer(const std::string_view dataType, const std::uint32_t stride, const std::uint32_t count)
	{
		return buffers[std::string(dataType)] = PonyBase::Container::Buffer(stride, count);
	}

	template<typename T>
	PonyBase::Container::BufferView<T> Mesh::CreateBuffer(const std::string_view dataType, const std::uint32_t count)
	{
		PonyBase::Container::Buffer& buffer = buffers[std::string(dataType)] = PonyBase::Container::Buffer::Create<T>(count);

		return PonyBase::Container::BufferView<T>(&buffer);
	}

	void Mesh::DestroyBuffer(const std::string_view dataType) noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return p.first == dataType; }); position != buffers.cend())
		{
			buffers.erase(position);
		}
	}

	void Mesh::DestroyBuffer(const PonyBase::Container::Buffer& buffer) noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return &p.second == &buffer; }); position != buffers.cend())
		{
			buffers.erase(position);
		}
	}

	PonyBase::Container::Buffer* Mesh::FindBuffer(const std::string_view dataType) noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return p.first == dataType; }); position != buffers.cend())
		{
			return &position->second;
		}

		return nullptr;
	}

	const PonyBase::Container::Buffer* Mesh::FindBuffer(const std::string_view dataType) const noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return p.first == dataType; }); position != buffers.cend())
		{
			return &position->second;
		}

		return nullptr;
	}

	template<typename T>
	PonyBase::Container::BufferView<T> Mesh::FindBuffer(const std::string_view dataType) noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return p.first == dataType; }); 
			position != buffers.cend() && position->second.Stride() == sizeof(T))
		{
			return PonyBase::Container::BufferView<T>(&position->second);
		}

		return PonyBase::Container::BufferView<T>();
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::FindBuffer(const std::string_view dataType) const noexcept
	{
		if (const auto position = std::ranges::find_if(buffers, [&](const std::pair<std::string, PonyBase::Container::Buffer>& p) { return p.first == dataType; }); 
			position != buffers.cend() && position->second.Stride() == sizeof(T))
		{
			return PonyBase::Container::BufferView<const T>(&position->second);
		}

		return PonyBase::Container::BufferView<const T>();
	}

	const std::unordered_map<std::string, PonyBase::Container::Buffer>& Mesh::Buffers() const noexcept
	{
		return buffers;
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
