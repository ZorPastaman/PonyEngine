/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:SystemInfo;

import <concepts>;
import <cstddef>;
import <memory>;
import <typeinfo>;

import PonyBase.Utility;

import :ISystemInfo;
import :System;
import :SystemData;
import :TickableSystem;

export namespace PonyEngine::Core
{
	/// @brief System info.
	/// @tparam System System type.
	/// @tparam Interfaces System public interface types.
	template<typename System, typename... Interfaces> requires (std::derived_from<System, Core::System> && (std::derived_from<System, Interfaces> && ...))
	class SystemInfo final : public ISystemInfo 
	{
	public:
		[[nodiscard("Pure function")]]
		virtual const std::type_info& SystemType() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t InterfaceCount() const noexcept override;

		/// @brief Creates a system data.
		/// @param system System.
		/// @return System data.
		[[nodiscard("Pure function")]]
		SystemData CreateSystemData(std::unique_ptr<System>&& system) const;
	};
}

namespace PonyEngine::Core
{
	template<typename System, typename... Interfaces> requires (std::derived_from<System, Core::System> && (std::derived_from<System, Interfaces> && ...))
	const std::type_info& SystemInfo<System, Interfaces...>::SystemType() const noexcept
	{
		return typeid(System);
	}

	template<typename System, typename... Interfaces> requires (std::derived_from<System, Core::System> && (std::derived_from<System, Interfaces> && ...))
	bool SystemInfo<System, Interfaces...>::IsTickable() const noexcept
	{
		return std::is_base_of_v<TickableSystem, System>;
	}

	template<typename System, typename... Interfaces> requires (std::derived_from<System, Core::System> && (std::derived_from<System, Interfaces> && ...))
	std::size_t SystemInfo<System, Interfaces...>::InterfaceCount() const noexcept
	{
		return sizeof...(Interfaces);
	}

	template<typename System, typename... Interfaces> requires (std::derived_from<System, Core::System> && (std::derived_from<System, Interfaces> && ...))
	SystemData SystemInfo<System, Interfaces...>::CreateSystemData(std::unique_ptr<System>&& system) const
	{
		SystemData data;
		data.publicInterfaces.AddInterfaces<System, Interfaces...>(*system);

		if constexpr (std::is_base_of_v<TickableSystem, System>)
		{
			data.system = std::unique_ptr<TickableSystem>(std::move(system));
		}
		else
		{
			data.system = std::unique_ptr<Core::System>(std::move(system));
		}

		return data;
	}
}
