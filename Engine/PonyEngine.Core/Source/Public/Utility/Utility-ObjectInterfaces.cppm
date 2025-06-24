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

export module PonyEngine.Utility:ObjectInterfaces;

import std;

export namespace PonyEngine::Utility
{
	/// @brief Object interfaces.
	class ObjectInterfaces final
	{
	public:
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
		void AddInterface(Source& object) requires (std::derived_from<Source, Target>);
		/// @brief Adds the interfaces.
		/// @tparam Source Object source type.
		/// @tparam Targets Interface types.
		/// @param object Object source.
		template<typename Source, typename... Targets>
		void AddInterfaces(Source& object) requires (std::derived_from<Source, Targets> && ...);
		/// @brief Adds the interfaces.
		/// @tparam Targets Interface types.
		/// @tparam Source Object source type.
		/// @param object Object source.
		template<typename... Targets, typename Source>
		void AddInterfacesDeduced(Source& object) requires (... && std::derived_from<Source, Targets>);

		/// @brief Gets the interface count.
		/// @return Interface count.
		[[nodiscard("Pure function")]]
		std::size_t Count() const noexcept;

		/// @brief Gets interfaces.
		/// @return Interfaces. Pairs of types and object pointers.
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::reference_wrapper<const std::type_info>, void*>> Span() const noexcept;

		/// @brief Reserves a space for the @p count of elements.
		/// @param count Count of elements to reserve for.
		void Reserve(std::size_t count);

		/// @brief Gets an interface by the @p index.
		/// @param index Interface index.
		/// @return Interface.
		[[nodiscard("Pure function")]]
		const std::pair<std::reference_wrapper<const std::type_info>, void*>& operator [](std::size_t index) const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

	private:
		std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>> interfaces; ///< Interfaces.
	};
}

namespace PonyEngine::Utility
{
	void ObjectInterfaces::AddInterface(const std::type_info& typeInfo, void* const pointer)
	{
		assert(pointer && "The object pointer is nullptr.");
		interfaces.emplace_back(typeInfo, pointer);
	}

	template<typename Target, typename Source>
	void ObjectInterfaces::AddInterface(Source& object) requires (std::derived_from<Source, Target>)
	{
		AddInterface(typeid(Target), static_cast<Target*>(&object));
	}

	template<typename Source, typename... Targets>
	void ObjectInterfaces::AddInterfaces(Source& object) requires (std::derived_from<Source, Targets> && ...)
	{
		Reserve(interfaces.size() + sizeof...(Targets));
		(AddInterface<Targets, Source>(object), ...);
	}

	template<typename... Targets, typename Source>
	void ObjectInterfaces::AddInterfacesDeduced(Source& object) requires (... && std::derived_from<Source, Targets>)
	{
		AddInterfaces<Source, Targets...>(object);
	}

	std::size_t ObjectInterfaces::Count() const noexcept
	{
		return interfaces.size();
	}

	std::span<const std::pair<std::reference_wrapper<const std::type_info>, void*>> ObjectInterfaces::Span() const noexcept
	{
		return interfaces;
	}

	void ObjectInterfaces::Reserve(const std::size_t count)
	{
		interfaces.reserve(count);
	}

	const std::pair<std::reference_wrapper<const std::type_info>, void*>& ObjectInterfaces::operator [](const std::size_t index) const noexcept
	{
		return interfaces[index];
	}
}
