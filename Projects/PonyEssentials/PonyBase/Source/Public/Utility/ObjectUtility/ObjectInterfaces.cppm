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

export module PonyBase.ObjectUtility:ObjectInterfaces;

import <concepts>;
import <functional>;
import <span>;
import <typeinfo>;
import <vector>;

export namespace PonyBase::Utility
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

		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::reference_wrapper<const std::type_info>, void*>> Span() const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

	private:
		std::vector<std::pair<std::reference_wrapper<const std::type_info>, void*>> interfaces; ///< Interfaces.
	};
}

namespace PonyBase::Utility
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
		(AddInterface<Targets, Source>(object), ...);
	}

	template<typename... Targets, typename Source>
	void ObjectInterfaces::AddInterfacesDeduced(Source& object) requires (... && std::derived_from<Source, Targets>)
	{
		AddInterfaces<Source, Targets...>(object);
	}

	std::span<const std::pair<std::reference_wrapper<const std::type_info>, void*>> ObjectInterfaces::Span() const noexcept
	{
		return interfaces;
	}
}
