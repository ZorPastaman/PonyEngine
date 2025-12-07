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
	/// @brief Interface container.
	class InterfaceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		InterfaceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit InterfaceContainer(std::size_t reserve);
		[[nodiscard("Pure constructor")]]
		InterfaceContainer(const InterfaceContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		InterfaceContainer(InterfaceContainer&& other) noexcept = default;

		~InterfaceContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds the @p type index.
		/// @param type Type.
		/// @return Type index or @p Size if it's not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::type_index type) const noexcept;
		/// @brief Finds the @p interface index.
		/// @param interface Interface.
		/// @return Interface index or @p Size if it's not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(void* interface) const noexcept;

		/// @brief Gets a type at the @p index.
		/// @param index Type index.
		/// @return Type.
		[[nodiscard("Pure function")]]
		std::type_index Type(std::size_t index) const noexcept;
		/// @brief Gets an interface at the @p index.
		/// @param index Interface index.
		/// @return Interface.
		[[nodiscard("Pure function")]]
		void* Interface(std::size_t index) const noexcept;

		/// @brief Adds data.
		/// @param type Type.
		/// @param interface Interface.
		void Add(std::type_index type, void* interface);
		/// @brief Removes data.
		/// @param index Data index to remove.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears data.
		void Clear() noexcept;

		InterfaceContainer& operator =(const InterfaceContainer& other) = delete;
		InterfaceContainer& operator =(InterfaceContainer&& other) noexcept = default;

	private:
		std::vector<std::type_index> types; ///< Types.
		std::vector<void*> interfaces; ///< Interfaces.
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

	std::size_t InterfaceContainer::IndexOf(void* const interface) const noexcept
	{
		return std::ranges::find(interfaces, interface) - interfaces.cbegin();
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
