/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:QueryParams;

import std;

import :Component;
import :Entity;

namespace PonyEngine::World
{
	/// @brief Tail for the @p AreUnique checker.
	template<Component...>
	struct AreUnique : std::true_type
	{
	};
	/// @brief Checks if the @p T is unique and not mentioned in the @p Rest.
	/// @tparam T Type.
	/// @tparam Rest Types.
	template<Component T, Component... Rest>
	struct AreUnique<T, Rest...> : std::bool_constant<!(std::same_as<T, Rest> || ...) && AreUnique<Rest...>::value>
	{
	};
}

export namespace PonyEngine::World
{
	/// @brief Query parameters.
	/// @note All the types must satisfy the @p Component concept and must be unique within the query parameters.
	struct QueryParams final
	{
		std::span<const std::type_index> requiredComponentTypes; ///< Required component types.
		std::span<const std::type_index> excludedComponentTypes; ///< Excluded component types.
		std::span<const std::type_index> optionalComponentTypes; ///< Optional component types.
	};

	/// @brief Query item. This object is returned in a query callback when a satisfying entity is found.
	struct QueryItem final
	{
		std::span<void* const> requiredComponents; ///< Required components. Returned in the same order as they're set in a @p QueryParams. Can't be nullptr.
		std::span<void* const> optionalComponents; ///< Optional components. Returned in the same order as they're set in a @p QueryParams. Can be nullptr.
		Entity entity; ///< Entity.
		bool terminate = false; ///< Should the query terminate? If set to @a true, the query stops immediately.
	};

	/// @brief Required component wrapper.
	template<Component...>
	struct Required final
	{
	};
	/// @brief Excluded component wrapper.
	template<Component...>
	struct Excluded final
	{
	};
	/// @brief Optional component wrapper.
	template<Component...>
	struct Optional final
	{
	};

	/// @brief Query helper prototype.
	template<typename, typename, typename>
	struct Query final
	{
		static_assert(false, "Invalid query.");
	};
	/// @brief Query helper.
	/// @tparam RequiredComponents Required component types.
	/// @tparam ExcludedComponents Excluded component types.
	/// @tparam OptionalComponents Optional component types.
	template<Component... RequiredComponents, Component... ExcludedComponents, Component... OptionalComponents>
	struct Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> final
	{
		static_assert(AreUnique<RequiredComponents..., ExcludedComponents..., OptionalComponents...>::value, "Duplicate component type.");

		inline static const std::array<std::type_index, sizeof...(RequiredComponents)> RequiredComponentTypes = std::array<std::type_index, sizeof...(RequiredComponents)>{ typeid(RequiredComponents)... }; /// Required component types.
		inline static const std::array<std::type_index, sizeof...(ExcludedComponents)> ExcludedComponentTypes = std::array<std::type_index, sizeof...(ExcludedComponents)>{ typeid(ExcludedComponents)... }; /// Excluded component types.
		inline static const std::array<std::type_index, sizeof...(OptionalComponents)> OptionalComponentTypes = std::array<std::type_index, sizeof...(OptionalComponents)>{ typeid(OptionalComponents)... }; /// Optional component types.

		/// @brief Query parameters.
		inline static const QueryParams QueryParams
		{
			.requiredComponentTypes = RequiredComponentTypes,
			.excludedComponentTypes = ExcludedComponentTypes,
			.optionalComponentTypes = OptionalComponentTypes
		};

		/// @brief Gets a required component.
		/// @tparam Component Required component type.
		/// @param item Query item. Must be an item that is returned from a query that took the @p QueryParams from this struct.
		/// @return Component.
		template<Component Component>
		static constexpr Component& GetRequired(const QueryItem& item) noexcept requires (std::same_as<Component, RequiredComponents> || ...)
		{
			constexpr std::size_t index = []() consteval
			{
				std::size_t i = 0uz;
				((std::same_as<Component, RequiredComponents> ? true : (++i, false)) || ...);
				return i;
			}();

			return *static_cast<Component*>(item.requiredComponents[index]);
		}

		/// @brief Gets an optional component.
		/// @tparam Component Optional component type.
		/// @param item Query item. Must be an item that is returned from a query that took the @p QueryParams from this struct.
		/// @return Component. May be nullptr.
		template<Component Component>
		static constexpr Component* GetOptional(const QueryItem& item) noexcept requires (std::same_as<Component, OptionalComponents> || ...)
		{
			constexpr std::size_t index = []() consteval
			{
				std::size_t i = 0uz;
				((std::same_as<Component, OptionalComponents> ? true : (++i, false)) || ...);
				return i;
			}();

			return static_cast<Component*>(item.optionalComponents[index]);
		}
	};

	/// @brief Makes an empty query helper.
	/// @return Query helper.
	constexpr Query<Required<>, Excluded<>, Optional<>> MakeQuery() noexcept
	{
		return Query<Required<>, Excluded<>, Optional<>>();
	}
	/// @brief Makes a query helper.
	/// @tparam RequiredComponents Required component types.
	/// @return Query helper.
	template<Component... RequiredComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<>, Optional<>> MakeQuery(Required<RequiredComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<>, Optional<>>();
	}
	/// @brief Makes a query helper.
	/// @tparam ExcludedComponents Excluded component types.
	/// @return Query helper.
	template<Component... ExcludedComponents>
	constexpr Query<Required<>, Excluded<ExcludedComponents...>, Optional<>> MakeQuery(Excluded<ExcludedComponents...>) noexcept
	{
		return Query<Required<>, Excluded<ExcludedComponents...>, Optional<>>();
	}
	/// @brief Makes a query helper.
	/// @tparam OptionalComponents Optional component types.
	/// @return Query helper.
	template<Component... OptionalComponents>
	constexpr Query<Required<>, Excluded<>, Optional<OptionalComponents...>> MakeQuery(Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<>, Excluded<>, Optional<OptionalComponents...>>();
	}
	/// @brief Makes a query helper.
	/// @tparam RequiredComponents Required component types.
	/// @tparam ExcludedComponents Excluded component types.
	/// @return Query helper.
	template<Component... RequiredComponents, Component... ExcludedComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<>> MakeQuery(
		Required<RequiredComponents...>, Excluded<ExcludedComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<>>();
	}
	/// @brief Makes a query helper.
	/// @tparam RequiredComponents Required component types.
	/// @tparam OptionalComponents Optional component types.
	/// @return Query helper.
	template<Component... RequiredComponents, Component... OptionalComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<>, Optional<OptionalComponents...>> MakeQuery(
		Required<RequiredComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<>, Optional<OptionalComponents...>>();
	}
	/// @brief Makes a query helper.
	/// @tparam ExcludedComponents Excluded component types.
	/// @tparam OptionalComponents Optional component types.
	/// @return Query helper.
	template<Component... ExcludedComponents, Component... OptionalComponents>
	constexpr Query<Required<>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> MakeQuery(
		Excluded<ExcludedComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>>();
	}
	/// @brief Makes a query helper.
	/// @tparam RequiredComponents Required component types.
	/// @tparam ExcludedComponents Excluded component types.
	/// @tparam OptionalComponents Optional component types.
	/// @return Query helper.
	template<Component... RequiredComponents, Component... ExcludedComponents, Component... OptionalComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> MakeQuery(
		Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>>();
	}
}
