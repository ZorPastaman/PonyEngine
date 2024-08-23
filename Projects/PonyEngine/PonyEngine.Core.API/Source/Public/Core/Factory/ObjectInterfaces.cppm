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
		using Iterator = std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::iterator; ///< Interfaces iterator.
		using ConstIterator = std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>>::const_iterator; ///< Interfaces const iterator.

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
		void AddInterface(const std::type_info& typeInfo, void* pointer);
		/// @brief Adds the interface.
		/// @tparam Target Interface type.
		/// @tparam Source Object source type.
		/// @param object Object source.
		template<typename Target, typename Source>
		void AddInterface(Source& object) requires (std::is_convertible_v<Source*, Target*>);
		/// @brief Adds the interfaces.
		/// @tparam Source Object source type.
		/// @tparam Targets Interface types.
		/// @param object Object source.
		template<typename Source, typename... Targets>
		void AddInterfaces(Source& object) requires (std::is_convertible_v<Source*, Targets*> && ...);
		/// @brief Adds the interfaces.
		/// @tparam Targets Interface types.
		/// @tparam Source Object source type.
		/// @param object Object source.
		template<typename... Targets, typename Source>
		void AddInterfacesDeduced(Source& object) requires (... && std::is_convertible_v<Source*, Targets*>);

		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		Iterator Begin() noexcept;
		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		ConstIterator Begin() const noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		Iterator End() noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		ConstIterator End() const noexcept;

		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		Iterator begin() noexcept;
		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		ConstIterator begin() const noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		Iterator end() noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		ConstIterator end() const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

	private:
		std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>> interfaces; ///< Interfaces.
	};
}

namespace PonyEngine::Core
{
	void ObjectInterfaces::AddInterface(const std::type_info& typeInfo, void* const pointer)
	{
		assert(pointer && "The object pointer is nullptr.");
		interfaces.emplace_back(typeInfo, pointer);
	}

	template<typename Target, typename Source>
	void ObjectInterfaces::AddInterface(Source& object) requires (std::is_convertible_v<Source*, Target*>)
	{
		AddInterface(typeid(Target), static_cast<Target*>(&object));
	}

	template<typename Source, typename... Targets>
	void ObjectInterfaces::AddInterfaces(Source& object) requires (std::is_convertible_v<Source*, Targets*> && ...)
	{
		(AddInterface<Targets, Source>(object),...);
	}

	template<typename... Targets, typename Source>
	void ObjectInterfaces::AddInterfacesDeduced(Source& object) requires (... && std::is_convertible_v<Source*, Targets*>)
	{
		AddInterfaces<Source, Targets...>(object);
	}

	ObjectInterfaces::Iterator ObjectInterfaces::Begin() noexcept
	{
		return interfaces.begin();
	}

	ObjectInterfaces::ConstIterator ObjectInterfaces::Begin() const noexcept
	{
		return interfaces.begin();
	}

	ObjectInterfaces::Iterator ObjectInterfaces::End() noexcept
	{
		return interfaces.end();
	}

	ObjectInterfaces::ConstIterator ObjectInterfaces::End() const noexcept
	{
		return interfaces.end();
	}

	ObjectInterfaces::Iterator ObjectInterfaces::begin() noexcept
	{
		return Begin();
	}

	ObjectInterfaces::ConstIterator ObjectInterfaces::begin() const noexcept
	{
		return Begin();
	}

	ObjectInterfaces::Iterator ObjectInterfaces::end() noexcept
	{
		return End();
	}

	ObjectInterfaces::ConstIterator ObjectInterfaces::end() const noexcept
	{
		return End();
	}
}
