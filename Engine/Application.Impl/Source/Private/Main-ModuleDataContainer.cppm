/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:ModuleDataContainer;

import std;

import PonyEngine.Application.Ext;

export namespace PonyEngine::Application
{
	/// @brief Module data container.
	class ModuleDataContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ModuleDataContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ModuleDataContainer(const ModuleDataContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		ModuleDataContainer(ModuleDataContainer&& other) noexcept = default;

		~ModuleDataContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the handle.
		/// @param handle Data handle.
		/// @return Index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ModuleDataHandle handle) const noexcept;
		/// @brief Finds an index of the type.
		/// @param type Data type.
		/// @return Index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::type_index type) const noexcept;

		/// @brief Gets a data handle.
		/// @param index Data index.
		/// @return Data handle.
		[[nodiscard("Pure function")]]
		ModuleDataHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets a data type.
		/// @param index Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::type_index Type(std::size_t index) const noexcept;
		/// @brief Gets a data.
		/// @param index Data index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		void* Data(std::size_t index) const noexcept;

		/// @brief Gets data handles.
		/// @return Data handles.
		[[nodiscard("Pure function")]]
		std::span<const ModuleDataHandle> Handles() const noexcept;
		/// @brief Gets data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::type_index> Types() const noexcept;

		/// @brief Adds data.
		/// @param handle Data handle.
		/// @param type Data type.
		/// @param data Data.
		void Add(ModuleDataHandle handle, std::type_index type, const std::shared_ptr<void>& data);
		/// @brief Removes data.
		/// @param index Data index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		ModuleDataContainer& operator =(const ModuleDataContainer&) = delete;
		ModuleDataContainer& operator =(ModuleDataContainer&& other) noexcept = default;

	private:
		std::vector<ModuleDataHandle> dataHandles; ///< Data handles.
		std::vector<std::type_index> dataTypes; ///< Data types.
		std::vector<std::shared_ptr<void>> data; ///< Data.
	};
}

namespace PonyEngine::Application
{
	std::size_t ModuleDataContainer::Size() const noexcept
	{
		return dataHandles.size();
	}

	std::size_t ModuleDataContainer::IndexOf(const ModuleDataHandle handle) const noexcept
	{
		return std::ranges::find(dataHandles, handle) - dataHandles.cbegin();
	}

	std::size_t ModuleDataContainer::IndexOf(const std::type_index type) const noexcept
	{
		return std::ranges::find(dataTypes, type) - dataTypes.cbegin();
	}

	ModuleDataHandle ModuleDataContainer::Handle(const std::size_t index) const noexcept
	{
		return dataHandles[index];
	}

	std::type_index ModuleDataContainer::Type(const std::size_t index) const noexcept
	{
		return dataTypes[index];
	}

	void* ModuleDataContainer::Data(const std::size_t index) const noexcept
	{
		return data[index].get();
	}

	std::span<const ModuleDataHandle> ModuleDataContainer::Handles() const noexcept
	{
		return dataHandles;
	}

	std::span<const std::type_index> ModuleDataContainer::Types() const noexcept
	{
		return dataTypes;
	}

	void ModuleDataContainer::Add(const ModuleDataHandle handle, const std::type_index type, const std::shared_ptr<void>& data)
	{
		dataHandles.push_back(handle);
		try
		{
			dataTypes.push_back(type);
			try
			{
				this->data.push_back(data);
			}
			catch (...)
			{
				dataTypes.pop_back();
				throw;
			}
		}
		catch (...)
		{
			dataHandles.pop_back();
			throw;
		}
	}

	void ModuleDataContainer::Remove(const std::size_t index) noexcept
	{
		data.erase(data.cbegin() + index);
		dataTypes.erase(dataTypes.cbegin() + index);
		dataHandles.erase(dataHandles.cbegin() + index);
	}

	void ModuleDataContainer::Clear() noexcept
	{
		dataHandles.clear();
		dataTypes.clear();
		data.clear();
	}
}
