/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Ext:ServiceData;

import std;

import :IService;
import :ITickableService;

export namespace PonyEngine::Application
{
	/// @brief Service data.
	struct ServiceData final
	{
		std::shared_ptr<IService> service; ///< Service.
		std::unordered_map<std::type_index, void*> publicInterfaces; ///< Service public interfaces.
		ITickableService* tickableService = nullptr; ///< Tickable service. 
		std::int32_t tickOrder = 0; ///< Service tick order. It's used only when the @p tickableService is not nullptr.

		/// @brief Sets a non-tickable service.
		/// @param service Service.
		void SetService(const std::shared_ptr<IService>& service) noexcept;
		/// @brief Sets a tickable service.
		/// @param service Service.
		/// @param tickOrder Tick order.
		void SetService(const std::shared_ptr<ITickableService>& service, std::int32_t tickOrder) noexcept;
		/// @brief Adds the interface.
		/// @tparam T Interface type.
		/// @param interface Interface.
		template<typename T>
		void AddInterface(T* interface) noexcept;
	};
}

namespace PonyEngine::Application
{
	void ServiceData::SetService(const std::shared_ptr<IService>& service) noexcept
	{
		this->service = service;
	}

	void ServiceData::SetService(const std::shared_ptr<ITickableService>& service, const std::int32_t tickOrder) noexcept
	{
		this->service = service;
		tickableService = service.get();
		this->tickOrder = tickOrder;
	}

	template<typename T>
	void ServiceData::AddInterface(T* const interface) noexcept
	{
		publicInterfaces.emplace(typeid(T), interface);
	}
}
