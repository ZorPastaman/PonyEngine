/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:DataTable;

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

import PonyBase.Utility;

export namespace PonyEngine::Render
{
	/// @brief Data table.
	/// @tparam T Data element type.
	template<typename T>
	class DataTable final
	{
	public:
		/// @brief Creates an empty data table.
		[[nodiscard("Pure constructor")]]
		DataTable() noexcept = default;
		/// @brief Creates a data table.
		/// @param data Tables.
		[[nodiscard("Pure constructor")]]
		explicit DataTable(const std::unordered_map<std::string, std::vector<T>>& data);
		[[nodiscard("Pure constructor")]]
		DataTable(const DataTable& other) = default;
		[[nodiscard("Pure constructor")]]
		DataTable(DataTable&& other) noexcept = default;

		~DataTable() noexcept = default;

		/// @brief Tries to find a data type index by the @p dataType.
		/// @param type Data type.
		/// @return Data type index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> TypeIndex(std::string_view type) const noexcept;
		/// @brief Gets a data type by the @p typeIndex.
		/// @param typeIndex Data type index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view Type(std::uint32_t typeIndex) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t TypeCount() const noexcept;
		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> Types() const noexcept;

		/// @brief Gets the data element count by the @p typeIndex.
		/// @param typeIndex Data type index.
		/// @return Data element count.
		[[nodiscard("Pure function")]]
		std::uint32_t ElementCount(std::uint32_t typeIndex) const noexcept;
		/// @brief Gets the data count of all the tables.
		/// @return Data element count.
		[[nodiscard("Pure function")]]
		std::uint32_t ElementCount() const noexcept;

		/// @brief Gets the element.
		/// @param typeIndex Data type index.
		/// @param elementIndex Data element index.
		/// @return Element.
		[[nodiscard("Pure function")]]
		T& Element(std::uint32_t typeIndex, std::uint32_t elementIndex) noexcept;
		/// @brief Gets the element.
		/// @param typeIndex Data type index.
		/// @param elementIndex Data element index.
		/// @return Element.
		[[nodiscard("Pure function")]]
		const T& Element(std::uint32_t typeIndex, std::uint32_t elementIndex) const noexcept;

		/// @brief Sets data.
		/// @param type Data type.
		/// @param elements Data elements.
		/// @return Data type index.
		std::uint32_t SetData(std::string_view type, std::span<const T> elements);
		/// @brief Removes data.
		/// @param typeIndex Data type index.
		void RemoveData(std::uint32_t typeIndex) noexcept;

		DataTable& operator =(const DataTable& other) = default;
		DataTable& operator =(DataTable&& other) noexcept = default;

	private:
		std::vector<std::string> types; ///< Data types.
		std::vector<std::vector<T>> elements; ///< Data elements.
	};
}

namespace PonyEngine::Render
{
	template <typename T>
	DataTable<T>::DataTable(const std::unordered_map<std::string, std::vector<T>>& data)
	{
		if (data.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Data type count exceeds uint32 max value.");
		}

		types.reserve(data.size());
		elements.reserve(data.size());
		std::size_t elementCount = 0;
		for (const auto& [type, typeElements] : data)
		{
			if (typeElements.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Element of '{}' type is empty.", type));
			}
			if (typeElements.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Element count of '{}' type exceeds uint32 max value.", type));
			}

			types.push_back(type);
			elements.push_back(typeElements);

			elementCount += typeElements.size();
			if (elementCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Data element count exceeds uint32 max value.");
			}
		}
	}

	template <typename T>
	std::optional<std::uint32_t> DataTable<T>::TypeIndex(const std::string_view type) const noexcept
	{
		for (std::uint32_t i = 0; i < types.size(); ++i)
		{
			if (types[i] == type)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	template <typename T>
	std::string_view DataTable<T>::Type(const std::uint32_t typeIndex) const noexcept
	{
		return types[typeIndex];
	}

	template <typename T>
	std::uint32_t DataTable<T>::TypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(types.size());
	}

	template <typename T>
	std::span<const std::string> DataTable<T>::Types() const noexcept
	{
		return types;
	}

	template <typename T>
	std::uint32_t DataTable<T>::ElementCount(const std::uint32_t typeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(elements[typeIndex].size());
	}

	template <typename T>
	std::uint32_t DataTable<T>::ElementCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(types.size()); ++i)
		{
			count += ElementCount(i);
		}

		return count;
	}

	template <typename T>
	T& DataTable<T>::Element(std::uint32_t typeIndex, std::uint32_t elementIndex) noexcept
	{
		return elements[typeIndex][elementIndex];
	}

	template <typename T>
	const T& DataTable<T>::Element(std::uint32_t typeIndex, std::uint32_t elementIndex) const noexcept
	{
		return elements[typeIndex][elementIndex];
	}

	template <typename T>
	std::uint32_t DataTable<T>::SetData(const std::string_view type, const std::span<const T> elements)
	{
		if (elements.size() == 0) [[unlikely]]
		{
			throw std::invalid_argument("Elements span is empty.");
		}
		if (elements.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Element count exceeds uint32 max value.");
		}

		auto newElements = std::vector<T>(elements.begin(), elements.end());

		if (const std::optional<std::uint32_t> typeIndex = TypeIndex(type))
		{
			if (ElementCount() - ElementCount(typeIndex.value()) + newElements.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Element count will exceed uint32 max value.");
			}
			this->elements[typeIndex.value()] = std::move(newElements);

			return typeIndex.value();
		}

		if (ElementCount() + newElements.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Element count will exceed uint32 max value.");
		}

		const std::size_t currentSize = types.size();
		try
		{
			types.push_back(std::string(type));
			this->elements.push_back(std::move(newElements));
		}
		catch (...)
		{
			types.resize(currentSize);
			this->elements.resize(currentSize);

			throw;
		}

		return static_cast<std::uint32_t>(currentSize);
	}

	template <typename T>
	void DataTable<T>::RemoveData(const std::uint32_t typeIndex) noexcept
	{
		types.erase(types.cbegin() + typeIndex);
		elements.erase(elements.cbegin() + typeIndex);
	}
}
