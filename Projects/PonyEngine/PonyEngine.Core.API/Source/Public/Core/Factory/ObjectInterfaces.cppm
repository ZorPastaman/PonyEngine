/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Core.Factory:ObjectInterfaces;

import <typeinfo>;
import <type_traits>;
import <utility>;
import <vector>;

export namespace PonyEngine::Core
{
	/// @brief Object interfaces.
	class ObjectInterfaces final
	{
	public:
		/// @brief Object interfaces iterator.
		class Iterator final
		{
		public:
			[[nodiscard("Pure constructor")]]
			Iterator(const Iterator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			Iterator(Iterator&& other) noexcept = default;

			~Iterator() noexcept = default;

			/// @brief Checks if the currently pointed interface is actually the end.
			/// @return @a True if the end is reached; @false otherwise.
			[[nodiscard("Pure function")]]
			bool IsEnd() const noexcept;

			/// @brief Gets the currently pointed interface.
			/// @return Currently pointed interface.
			[[nodiscard("Pure operator")]]
			std::pair<std::reference_wrapper<const std::type_info>, void*> operator *() const noexcept;
			/// @brief Moves to the next interface.
			/// @return New iterator.
			Iterator& operator ++() noexcept;
			/// @brief Moves to the next interface.
			/// @return Previous iterator.
			Iterator operator ++(int) noexcept;

			Iterator& operator =(const Iterator& other) noexcept = default;
			Iterator& operator =(Iterator&& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			bool operator ==(const Iterator& other) const noexcept = default;

		private:
			/// @brief Creates an @p Iterator.
			/// @param begin Interfaces begin.
			/// @param end Interfaces end.
			[[nodiscard("Pure constructor")]]
			Iterator(const std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator& begin, const std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator& end) noexcept;

			std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator current; ///< Current interface.
			std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator end; ///< Interfaces iterator end.

			friend ObjectInterfaces;
		};

		[[nodiscard("Pure constructor")]]
		ObjectInterfaces() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(const ObjectInterfaces& other) = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(ObjectInterfaces&& other) noexcept = default;

		~ObjectInterfaces() noexcept = default;

		/// @brief Adds the interface.
		/// @param typeInfo Interface type info.
		/// @param pointer Pointer to the interface object.
		void AddObjectInterface(const std::type_info& typeInfo, void* pointer);
		/// @brief Adds the interface.
		/// @tparam Target Interface type.
		/// @tparam Source Object source type.
		/// @param object Object source.
		template<typename Target, typename Source>
		void AddObjectInterface(Source& object) requires(std::is_convertible_v<Source*, Target*>);
		/// @brief Adds the interfaces.
		/// @tparam Source Object source type.
		/// @tparam Targets Interface types.
		/// @param object Object source.
		template<typename Source, typename... Targets>
		void AddObjectInterfaces(Source& object) requires(std::is_convertible_v<Source*, Targets*> && ...);
		/// @brief Adds the interfaces.
		/// @tparam Targets Interface types.
		/// @tparam Source Object source type.
		/// @param object Object source.
		template<typename... Targets, typename Source>
		void AddObjectInterfacesDeduced(Source& object) requires(... && std::is_convertible_v<Source*, Targets*>);
		/// @brief Gets the object interfaces.
		/// @return Object interfaces iterator.
		[[nodiscard("Pure function")]]
		Iterator GetObjectInterfaces() const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

	private:
		std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>> interfaces; ///< Interfaces.
	};
}

namespace PonyEngine::Core
{
	ObjectInterfaces::Iterator::Iterator(const std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator& begin, const std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator& end) noexcept :
		current(begin),
		end(end)
	{
	}

	bool ObjectInterfaces::Iterator::IsEnd() const noexcept
	{
		return current == end;
	}

	std::pair<std::reference_wrapper<const std::type_info>, void*> ObjectInterfaces::Iterator::operator *() const noexcept
	{
		return *current;
	}

	ObjectInterfaces::Iterator& ObjectInterfaces::Iterator::operator ++() noexcept
	{
		++current;

		return *this;
	}

	ObjectInterfaces::Iterator ObjectInterfaces::Iterator::operator ++(int) noexcept
	{
		const Iterator temp = *this;
		++(*this);

		return temp;
	}

	void ObjectInterfaces::AddObjectInterface(const std::type_info& typeInfo, void* const pointer)
	{
		assert((pointer && "The object pointer is nullptr."));
		interfaces.emplace_back(typeInfo, pointer);
	}

	template<typename Target, typename Source>
	void ObjectInterfaces::AddObjectInterface(Source& object) requires(std::is_convertible_v<Source*, Target*>)
	{
		AddObjectInterface(typeid(Target), static_cast<Target*>(&object));
	}

	template<typename Source, typename... Targets>
	void ObjectInterfaces::AddObjectInterfaces(Source& object) requires(std::is_convertible_v<Source*, Targets*> && ...)
	{
		(AddObjectInterface<Targets, Source>(object),...);
	}

	template<typename... Targets, typename Source>
	void ObjectInterfaces::AddObjectInterfacesDeduced(Source& object) requires(... && std::is_convertible_v<Source*, Targets*>)
	{
		AddObjectInterfaces<Source, Targets...>(object);
	}

	ObjectInterfaces::Iterator ObjectInterfaces::GetObjectInterfaces() const noexcept
	{
		return Iterator(interfaces.cbegin(), interfaces.cend());
	}
}
