/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:InterfaceContainer;

import std;

export namespace PonyEngine::Application
{
	class InterfaceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		InterfaceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit InterfaceContainer(std::size_t reserve);
		InterfaceContainer(const InterfaceContainer& other) = default;
		InterfaceContainer(InterfaceContainer&& other) = default;

		~InterfaceContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::type_index type) const noexcept;

		[[nodiscard("Pure function")]]
		std::type_index Type(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		void* Interface(std::size_t index) const noexcept;

		void Add(std::type_index type, void* interface);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		InterfaceContainer& operator =(const InterfaceContainer& other) = default;
		InterfaceContainer& operator =(InterfaceContainer&& other) = default;

	private:
		std::vector<std::type_index> types;
		std::vector<void*> interfaces;
	};
}

namespace PonyEngine::Application
{
	InterfaceContainer::InterfaceContainer(const std::size_t reserve)
	{
		types.reserve(reserve);
		interfaces.reserve(reserve);
	}

	std::size_t InterfaceContainer::Size() const noexcept
	{
		return types.size();
	}

	std::size_t InterfaceContainer::IndexOf(const std::type_index type) const noexcept
	{
		return std::ranges::find(types, type) - types.cbegin();
	}

	std::type_index InterfaceContainer::Type(const std::size_t index) const noexcept
	{
		return types[index];
	}

	void* InterfaceContainer::Interface(const std::size_t index) const noexcept
	{
		return interfaces[index];
	}

	void InterfaceContainer::Add(const std::type_index type, void* const interface)
	{
		types.push_back(type);
		try
		{
			interfaces.push_back(interface);
		}
		catch (...)
		{
			types.pop_back();
			throw;
		}
	}

	void InterfaceContainer::Remove(const std::size_t index) noexcept
	{
		interfaces.erase(interfaces.cbegin() + index);
		types.erase(types.cbegin() + index);
	}

	void InterfaceContainer::Clear() noexcept
	{
		types.clear();
		interfaces.clear();
	}
}
