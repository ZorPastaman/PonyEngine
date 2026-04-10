/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application.Ext:IModuleContext;

import std;

import PonyEngine.Log;

import :ILoggerModuleContext;
import :ModuleDataHandle;
import :IServiceModuleContext;

export namespace PonyEngine::Application
{
	/// @brief Module context. It's a context used by modules.
	class IModuleContext
	{
		PONY_INTERFACE_BODY(IModuleContext)

		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the logger module context.
		/// @return Logger module context.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual ILoggerModuleContext& LoggerModuleContext() noexcept = 0;
		/// @brief Gets the logger module context.
		/// @return Logger module context.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual const ILoggerModuleContext& LoggerModuleContext() const noexcept = 0;
		/// @brief Gets the service module context.
		/// @return Service module context.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual IServiceModuleContext& ServiceModuleContext() noexcept = 0;
		/// @brief Gets the service module context.
		/// @return Service module context.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual const IServiceModuleContext& ServiceModuleContext() const noexcept = 0;

		/// @brief Gets a data.
		/// @param type Data type.
		/// @return Data.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual void* GetData(std::type_index type) const = 0;
		/// @brief Gets a data.
		/// @tparam T Data type.
		/// @return Data.
		/// @note The function must be called on a main thread.
		template<typename T>
		T* GetData() const;
		/// @brief Adds a data.
		/// @param type Data type.
		/// @param data Data.
		/// @return Module data handle.
		/// @note The function must be called on a main thread.
		virtual ModuleDataHandle AddData(std::type_index type, const std::shared_ptr<void>& data) = 0;
		/// @brief Adds a data.
		/// @tparam T Data type.
		/// @param data Data.
		/// @return Module data handle.
		/// @note The function must be called on a main thread.
		template<typename T>
		ModuleDataHandle AddData(const std::shared_ptr<T>& data);
		/// @brief Removes a data.
		/// @param handle Module data handle.
		/// @note The function must be called on a main thread.
		virtual void RemoveData(ModuleDataHandle handle) = 0;
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	T* IModuleContext::GetData() const
	{
		return static_cast<T*>(GetData(typeid(T)));
	}

	template<typename T>
	ModuleDataHandle IModuleContext::AddData(const std::shared_ptr<T>& data)
	{
		return AddData(typeid(T), data);
	}
}
