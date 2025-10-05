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

export module PonyEngine.Application:IModuleContext;

import std;

import PonyEngine.Log;

import :IApplicationContext;
import :IServiceFactory;

export namespace PonyEngine::Application
{
	/// @brief Module context. It exists only on an application start-up and shut-down.
	class IModuleContext
	{
		INTERFACE_BODY(IModuleContext)

		/// @brief Gets the application context.
		/// @return Application.
		[[nodiscard("Pure function")]]
		virtual IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application.
		[[nodiscard("Pure function")]]
		virtual const IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets a data count.
		/// @param type Data type.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		virtual std::size_t DataCount(const std::type_info& type) const noexcept = 0;
		/// @brief Gets a data count.
		/// @tparam T Data type.
		/// @return Data count.
		template<typename T> [[nodiscard("Pure function")]]
		std::size_t DataCount() const noexcept;
		/// @brief Gets a data.
		/// @param type Data type.
		/// @param index Data index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const = 0;
		/// @brief Gets a data.
		/// @tparam T Data type.
		/// @param index Data index.
		/// @return Data.
		template<typename T>
		std::shared_ptr<T> GetData(std::size_t index) const;
		/// @brief Adds a data.
		/// @param type Data type.
		/// @param data Data.
		virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) = 0;
		/// @brief Adds a data.
		/// @tparam T Data type.
		/// @param data Data.
		template<typename T>
		void AddData(const std::shared_ptr<T>& data);

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
		/// @brief Adds a service.
		/// @param factory Service factory.
		virtual void AddService(const std::shared_ptr<IServiceFactory>& factory) = 0;
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	std::size_t IModuleContext::DataCount() const noexcept
	{
		return DataCount(typeid(T));
	}

	template<typename T>
	std::shared_ptr<T> IModuleContext::GetData(const std::size_t index) const
	{
		return std::static_pointer_cast<T>(GetData(typeid(T), index));
	}

	template<typename T>
	void IModuleContext::AddData(const std::shared_ptr<T>& data)
	{
		AddData(typeid(T), data);
	}

	template<typename T>
	T* IModuleContext::FindService() noexcept
	{
		return static_cast<T*>(FindService(typeid(T)));
	}

	template<typename T>
	const T* IModuleContext::FindService() const noexcept
	{
		return static_cast<const T*>(FindService(typeid(T)));
	}
}
