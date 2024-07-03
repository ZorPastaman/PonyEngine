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

export module PonyEngine.Core.Factories:SystemInfo;

import <functional>;
import <memory>;

import PonyEngine.Core;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System info.
	class SystemInfo final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SystemInfo() noexcept = default;
		SystemInfo(const SystemInfo& other) = delete;
		[[nodiscard("Pure constructor")]]
		SystemInfo(SystemInfo&& other) noexcept = default;

		~SystemInfo() noexcept = default;

		SystemInfo& operator =(const SystemInfo& other) = delete;
		SystemInfo& operator =(SystemInfo&& other) noexcept = default;

		/// @brief Gets a system.
		/// @return System.
		[[nodiscard("Pure function")]]
		std::unique_ptr<ISystem, std::function<void(ISystem*)>>& GetSystem() noexcept;
		/// @brief Gets system public interfaces.
		/// @return System public interfaces.
		[[nodiscard("Pure function")]]
		ObjectInterfaces::ObjectInterfacesIterator GetInterfaces() const noexcept;
		/// @brief Is the system tickable?
		/// @return @a True if it's tickable; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool GetIsTickable() const noexcept;

		/// @brief Sets data.
		/// @tparam System System type.
		/// @tparam Interfaces System public interface types.
		/// @param system Engine system.
		/// @param deleter Deleter function.
		/// @param isTickable Is the system tickable?
		template<typename System, typename... Interfaces>
		void Set(System* system, const std::function<void(ISystem*)>& deleter, bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...));

	private:
		std::unique_ptr<ISystem, std::function<void(ISystem*)>> system; ///< System.
		ObjectInterfaces interfaces; ///< System public interfaces.
		bool isTickable; ///< Is the system tickable?
	};
}

namespace PonyEngine::Core
{
	std::unique_ptr<ISystem, std::function<void(ISystem*)>>& SystemInfo::GetSystem() noexcept
	{
		return system;
	}

	ObjectInterfaces::ObjectInterfacesIterator SystemInfo::GetInterfaces() const noexcept
	{
		return interfaces.GetObjectInterfacesIterator();
	}

	bool SystemInfo::GetIsTickable() const noexcept
	{
		return isTickable;
	}

	template<typename System, typename... Interfaces>
	void SystemInfo::Set(System* const system, const std::function<void(ISystem*)>& deleter, const bool isTickable) requires(std::is_convertible_v<System*, ISystem*> && (std::is_convertible_v<System*, Interfaces*> && ...))
	{
		assert((system && "The system is nullptr."));
		this->system = std::unique_ptr<ISystem, std::function<void(ISystem*)>>(system, deleter);
		interfaces.AddObjectInterfaces<System, Interfaces...>(system);
		this->isTickable = isTickable;
	}
}
