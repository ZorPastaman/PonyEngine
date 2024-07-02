/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

 // TODO: Add text to asserts

#include <cassert>

export module PonyEngine.Core.Factories:ObjectInterfaces;

import <typeinfo>;
import <utility>;
import <vector>;

export namespace PonyEngine::Core
{
	/// @brief Object interfaces holder.
	class ObjectInterfaces final
	{
	public:
		/// @brief Object interfaces iterator.
		class ObjectInterfacesIterator final
		{
		public:
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(const ObjectInterfacesIterator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(ObjectInterfacesIterator&& other) noexcept = default;

			~ObjectInterfacesIterator() noexcept = default;

			/// @brief Checks if the currently pointed interface is actually an end.
			/// @return @a True if the end is reached; @false otherwise.
			[[nodiscard("Pure function")]]
			bool IsEnd() const noexcept;

			/// @brief Gets a currently pointed interface.
			/// @return Currently pointed interface.
			[[nodiscard("Pure operator")]]
			std::pair<const std::type_info&, void*> operator *() const noexcept;
			/// @brief Moves a pointer to the next interface.
			/// @return New iterator.
			ObjectInterfacesIterator& operator ++() noexcept;
			/// @brief Moves a pointer to the next interface.
			/// @return Previous iterator.
			ObjectInterfacesIterator operator ++(int) noexcept;

			ObjectInterfacesIterator& operator =(const ObjectInterfacesIterator& other) noexcept = default;
			ObjectInterfacesIterator& operator =(ObjectInterfacesIterator&& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			bool operator ==(const ObjectInterfacesIterator& other) const noexcept = default;

		private:
			/// @brief Creates a @p ObjectInterfacesIterator.
			/// @param begin Interfaces begin.
			/// @param end Interfaces end.
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& begin, const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& end) noexcept;

			std::vector<std::pair<const std::type_info&, void*>>::const_iterator current; ///< Current interface.
			std::vector<std::pair<const std::type_info&, void*>>::const_iterator end; ///< Interfaces iterator end.

			friend ObjectInterfaces;
		};

		[[nodiscard("Pure constructor")]]
		ObjectInterfaces() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(const ObjectInterfaces& other) = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(ObjectInterfaces&& other) noexcept = default;

		~ObjectInterfaces() noexcept = default;

		// TODO: Add a template function.

		/// @brief Adds an interface.
		/// @param typeInfo Interface type info.
		/// @param pointer Pointer to the interface object.
		void AddObjectInterface(const std::type_info& typeInfo, void* pointer);
		/// @brief Gets an interfaces iterator.
		/// @return Interfaces iterator.
		[[nodiscard("Pure function")]]
		ObjectInterfacesIterator GetObjectInterfacesIterator() const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const ObjectInterfaces& other) const noexcept = default;

	private:
		std::vector<std::pair<const std::type_info&, void*>> interfaces; ///< Interfaces.
	};
}

namespace PonyEngine::Core
{
	ObjectInterfaces::ObjectInterfacesIterator::ObjectInterfacesIterator(const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& begin, const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& end) noexcept :
		current(begin),
		end(end)
	{
	}

	bool ObjectInterfaces::ObjectInterfacesIterator::IsEnd() const noexcept
	{
		return current == end;
	}

	std::pair<const std::type_info&, void*> ObjectInterfaces::ObjectInterfacesIterator::operator *() const noexcept
	{
		return *current;
	}

	ObjectInterfaces::ObjectInterfacesIterator& ObjectInterfaces::ObjectInterfacesIterator::operator ++() noexcept
	{
		++current;

		return *this;
	}

	ObjectInterfaces::ObjectInterfacesIterator ObjectInterfaces::ObjectInterfacesIterator::operator ++(int) noexcept
	{
		const ObjectInterfacesIterator temp = *this;
		++(*this);

		return temp;
	}

	void ObjectInterfaces::AddObjectInterface(const std::type_info& typeInfo, void* const pointer)
	{
		assert((pointer));

		const auto pair = std::pair<const std::type_info&, void*>(typeInfo, pointer);
		interfaces.push_back(pair);
	}

	ObjectInterfaces::ObjectInterfacesIterator ObjectInterfaces::GetObjectInterfacesIterator() const noexcept
	{
		return ObjectInterfacesIterator(interfaces.cbegin(), interfaces.cend());
	}
}
