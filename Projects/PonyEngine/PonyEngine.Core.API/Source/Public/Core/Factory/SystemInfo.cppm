/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemInfo;

import <memory>;
import <type_traits>;

import PonyEngine.Core;

import :ISystemDestroyer;
import :ObjectInterfaces;
import :SystemDeleter;

export namespace PonyEngine::Core
{
	using SystemUniquePtr = std::unique_ptr<ISystem, SystemDeleter>; ///< Engine system unique_ptr typedef.

	/// @brief System info.
	class SystemInfo final
	{
	public:
		/// @brief Creates a @p SystemInfo.
		/// @param system Engine system.
		/// @param destroyer System destroyer.
		/// @param interfaces System public interfaces.
		/// @param isTickable Is the system tickable?
		/// @note The @p destroyer must be appropriate to destroy the @p system, and its lifetime must exceed the lifetime of the system.
		[[nodiscard("Pure constructor")]]
		SystemInfo(ISystem& system, ISystemDestroyer& destroyer, const ObjectInterfaces& interfaces, bool isTickable) noexcept;
		SystemInfo(const SystemInfo&) = delete;
		[[nodiscard("Pure constructor")]]
		SystemInfo(SystemInfo&& other) noexcept = default;

		~SystemInfo() noexcept = default;

		/// @brief Creates a system info.
		/// @tparam System System type.
		/// @tparam Interfaces System public interface types.
		/// @param system Engine system.
		/// @param destroyer System destroyer.
		/// @param isTickable Is the system tickable?
		/// @note The @p destroyer must be appropriate to destroy the @p system, and its lifetime must exceed the lifetime of the system.
		template<typename System, typename... Interfaces> [[nodiscard("Pure function")]]
		static SystemInfo Create(System& system, ISystemDestroyer& destroyer, bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...));
		/// @brief Creates a system info.
		/// @tparam Interfaces System public interface types.
		/// @tparam System System type.
		/// @param system Engine system.
		/// @param destroyer System destroyer.
		/// @param isTickable Is the system tickable?
		/// @note The @p destroyer must be appropriate to destroy the @p system, and its lifetime must exceed the lifetime of the system.
		template<typename... Interfaces, typename System> [[nodiscard("Pure function")]]
		static SystemInfo CreateDeduced(System& system, ISystemDestroyer& destroyer, bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (... && std::is_convertible_v<System*, Interfaces*>));

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

		SystemInfo& operator =(const SystemInfo&) = delete;
		SystemInfo& operator =(SystemInfo&& other) noexcept = default;

	private:
		std::unique_ptr<ISystem, SystemDeleter> system; ///< System.
		ObjectInterfaces interfaces; ///< System public interfaces.
		bool isTickable; ///< Is the system tickable?
	};
}

namespace PonyEngine::Core
{
	SystemInfo::SystemInfo(ISystem& system, ISystemDestroyer& destroyer, const ObjectInterfaces& interfaces, const bool isTickable) noexcept :
		system(&system, SystemDeleter(destroyer)),
		interfaces(interfaces),
		isTickable{isTickable}
	{
	}

	template<typename System, typename... Interfaces>
	SystemInfo SystemInfo::Create(System& system, ISystemDestroyer& destroyer, const bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...))
	{
		auto interfaces = ObjectInterfaces();
		interfaces.AddObjectInterfaces<System, Interfaces...>(system);

		return SystemInfo(system, destroyer, interfaces, isTickable);
	}

	template<typename... Interfaces, typename System>
	SystemInfo SystemInfo::CreateDeduced(System& system, ISystemDestroyer& destroyer, const bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (... && std::is_convertible_v<System*, Interfaces*>))
	{
		return Create<System, Interfaces...>(system, destroyer, isTickable);
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
