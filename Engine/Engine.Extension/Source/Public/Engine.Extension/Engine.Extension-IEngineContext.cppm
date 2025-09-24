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

export module PonyEngine.Engine.Extension:IEngineContext;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace PonyEngine::Engine
{
	/// @brief Engine context.
	class IEngineContext
	{
		INTERFACE_BODY(IEngineContext)

		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Tries to find a system of the type described by the @p typeInfo.
		/// @param typeInfo System type info.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) noexcept = 0;
		/// @brief Tries to find a system of the type @p T.
		/// @tparam T System type.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindSystem() noexcept;
		/// @brief Tries to find a system of the type described by the @p typeInfo.
		/// @param typeInfo System type info.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual const void* FindSystem(const std::type_info& typeInfo) const noexcept = 0;
		/// @brief Tries to find a system of the type @p T.
		/// @tparam T System type.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		const T* FindSystem() const noexcept;
	};
}

namespace PonyEngine::Engine
{
	template<typename T>
	T* IEngineContext::FindSystem() noexcept
	{
		return static_cast<T*>(FindSystem(typeid(T)));
	}

	template<typename T>
	const T* IEngineContext::FindSystem() const noexcept
	{
		return static_cast<const T*>(FindSystem(typeid(T)));
	}
}
