/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application:IServiceManager;

import std;

export namespace PonyEngine::Application
{
	/// @brief Service manager.
	class IServiceManager
	{
		INTERFACE_BODY(IServiceManager)

		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual void* FindService(const std::type_info& type) noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindService() noexcept;
		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual const void* FindService(const std::type_info& type) const noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		const T* FindService() const noexcept;
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	T* IServiceManager::FindService() noexcept
	{
		return static_cast<T*>(FindService(typeid(T)));
	}

	template<typename T>
	const T* IServiceManager::FindService() const noexcept
	{
		return static_cast<const T*>(FindService(typeid(T)));
	}
}
