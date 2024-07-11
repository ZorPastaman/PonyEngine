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

export module PonyEngine.Core.Factory:SystemInfo;

import <functional>;
import <memory>;
import <type_traits>;

import PonyEngine.Core;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	using SystemUniquePtr = std::unique_ptr<ISystem, std::function<void(ISystem*)>>; ///< Engine system unique_ptr typedef.

	/// @brief System info.
	class SystemInfo final
	{
	public:
		SystemInfo(const SystemInfo& other) = delete;
		[[nodiscard("Pure constructor")]]
		SystemInfo(SystemInfo&& other) noexcept = default;

		~SystemInfo() noexcept = default;

		/// @brief Creates a system info.
		/// @tparam System System type.
		/// @tparam Interfaces System public interface types.
		/// @param system Engine system.
		/// @param deleter Deleter function.
		/// @param isTickable Is the system tickable?
		template<typename System, typename... Interfaces>
		static SystemInfo Create(System* system, const std::function<void(ISystem*)>& deleter, bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...));

		/// @brief Gets the system.
		/// @return System.
		[[nodiscard("Pure function")]]
		SystemUniquePtr& GetSystem() noexcept;
		/// @brief Gets the system public interfaces.
		/// @return System public interfaces.
		[[nodiscard("Pure function")]]
		ObjectInterfaces::Iterator GetInterfaces() const noexcept;
		/// @brief Is the system tickable?
		/// @return @a True if it's tickable; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool GetIsTickable() const noexcept;

		SystemInfo& operator =(const SystemInfo& other) = delete;
		SystemInfo& operator =(SystemInfo&& other) noexcept = default;

	private:
		[[nodiscard("Pure constructor")]]
		SystemInfo() noexcept = default;

		std::unique_ptr<ISystem, std::function<void(ISystem*)>> system; ///< System.
		ObjectInterfaces interfaces; ///< System public interfaces.
		bool isTickable; ///< Is the system tickable?
	};
}

namespace PonyEngine::Core
{
	template<typename System, typename... Interfaces>
	SystemInfo SystemInfo::Create(System* const system, const std::function<void(ISystem*)>& deleter, const bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...))
	{
		assert((system && "The system is nullptr."));

		SystemInfo info;
		info.system = std::unique_ptr<ISystem, std::function<void(ISystem*)>>(system, deleter);
		info.interfaces.AddObjectInterfaces<System, Interfaces...>(system);
		info.isTickable = isTickable;

		return info;
	}

	SystemUniquePtr& SystemInfo::GetSystem() noexcept
	{
		return system;
	}

	ObjectInterfaces::Iterator SystemInfo::GetInterfaces() const noexcept
	{
		return interfaces.GetObjectInterfaces();
	}

	bool SystemInfo::GetIsTickable() const noexcept
	{
		return isTickable;
	}
}
