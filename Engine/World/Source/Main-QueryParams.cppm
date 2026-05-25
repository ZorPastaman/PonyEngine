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
	template<Component...>
	struct AreUnique : std::true_type
	{
	};
	template<Component T, Component... Rest>
	struct AreUnique<T, Rest...> : std::bool_constant<!(std::same_as<T, Rest> || ...) && AreUnique<Rest...>::value>
	{
	};
}

export namespace PonyEngine::World
{
	struct QueryParams final
	{
		std::span<const std::type_index> requiredComponentTypes;
		std::span<const std::type_index> excludedComponentTypes;
		std::span<const std::type_index> optionalComponentTypes;
	};

	struct QueryItem final
	{
		std::span<void* const> requiredComponents;
		std::span<void* const> optionalComponents;
		Entity entity;
		bool terminate = false;
	};

	template<Component...>
	struct Required final
	{
	};
	template<Component...>
	struct Excluded final
	{
	};
	template<Component...>
	struct Optional final
	{
	};

	template<typename, typename, typename>
	struct Query final
	{
		static_assert(false, "Invalid query.");
	};
	template<Component... RequiredComponents, Component... ExcludedComponents, Component... OptionalComponents>
	struct Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> final
	{
		static_assert(AreUnique<RequiredComponents..., ExcludedComponents..., OptionalComponents...>::value, "Duplicate component type.");

		inline static const std::array<std::type_index, sizeof...(RequiredComponents)> RequiredComponentTypes = std::array<std::type_index, sizeof...(RequiredComponents)>{ typeid(RequiredComponents)... };
		inline static const std::array<std::type_index, sizeof...(ExcludedComponents)> ExcludedComponentTypes = std::array<std::type_index, sizeof...(ExcludedComponents)>{ typeid(ExcludedComponents)... };
		inline static const std::array<std::type_index, sizeof...(OptionalComponents)> OptionalComponentTypes = std::array<std::type_index, sizeof...(OptionalComponents)>{ typeid(OptionalComponents)... };

		inline static const QueryParams QueryParams
		{
			.requiredComponentTypes = RequiredComponentTypes,
			.excludedComponentTypes = ExcludedComponentTypes,
			.optionalComponentTypes = OptionalComponentTypes
		};

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

	constexpr Query<Required<>, Excluded<>, Optional<>> MakeQuery() noexcept
	{
		return Query<Required<>, Excluded<>, Optional<>>();
	}
	template<Component... RequiredComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<>, Optional<>> MakeQuery(Required<RequiredComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<>, Optional<>>();
	}
	template<Component... ExcludedComponents>
	constexpr Query<Required<>, Excluded<ExcludedComponents...>, Optional<>> MakeQuery(Excluded<ExcludedComponents...>) noexcept
	{
		return Query<Required<>, Excluded<ExcludedComponents...>, Optional<>>();
	}
	template<Component... OptionalComponents>
	constexpr Query<Required<>, Excluded<>, Optional<OptionalComponents...>> MakeQuery(Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<>, Excluded<>, Optional<OptionalComponents...>>();
	}
	template<Component... RequiredComponents, Component... ExcludedComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<>> MakeQuery(
		Required<RequiredComponents...>, Excluded<ExcludedComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<>>();
	}
	template<Component... RequiredComponents, Component... OptionalComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<>, Optional<OptionalComponents...>> MakeQuery(
		Required<RequiredComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<>, Optional<OptionalComponents...>>();
	}
	template<Component... ExcludedComponents, Component... OptionalComponents>
	constexpr Query<Required<>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> MakeQuery(
		Excluded<ExcludedComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>>();
	}
	template<Component... RequiredComponents, Component... ExcludedComponents, Component... OptionalComponents>
	constexpr Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>> MakeQuery(
		Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>) noexcept
	{
		return Query<Required<RequiredComponents...>, Excluded<ExcludedComponents...>, Optional<OptionalComponents...>>();
	}
}
