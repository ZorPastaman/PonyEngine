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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:ServiceManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :LoggerManager;
import :ThreadManager;

export namespace PonyEngine::Application
{
	class ServiceManager final
	{
	public:
		void AddService(IService& service);
		void RemoveService(IService& service);

		void Begin() const;
		void End() const noexcept;

	private:
		void Begin(std::size_t& count) const;
		void End(std::size_t count) const noexcept;

		const LoggerManager* loggerManager; ///< Logger manager.
		const ThreadManager* threadManager; ///< Thread manager.

		std::vector<IService*> services;
	};
}

namespace PonyEngine::Application
{
	void ServiceManager::AddService(IService& service)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (std::ranges::find(services, &service) != services.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Service was already added");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Adding service. Service: '{}'.", typeid(service).name());
		services.push_back(&service);
	}

	void ServiceManager::RemoveService(IService& service)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Removing service. Service: '{}'.", typeid(service).name());
		if (const auto position = std::ranges::find(services, &service); position != services.cend()) [[likely]]
		{
			services.erase(position);
		}
#ifndef NDEBUG
		else [[unlikely]]
		{
			throw std::invalid_argument("Service wasn't added");
		}
#endif
	}

	void ServiceManager::Begin() const
	{
		std::size_t count = 0uz;
		try
		{
			Begin(count);
		}
		catch (...)
		{
			End(count);
			throw;
		}
	}

	void ServiceManager::End() const noexcept
	{
		End(services.size());
	}

	void ServiceManager::Begin(std::size_t& count) const
	{
		for (IService* const service : services)
		{
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning service... Service: '{}'.", typeid(*service).name());
			service->Begin();
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning service done. Service: '{}'.", typeid(*service).name());
			++count;
		}
	}

	void ServiceManager::End(const std::size_t count) const noexcept
	{
		for (std::size_t i = count; i-- > 0uz; )
		{
			IService* const service = services[i];

			try
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending service... Service: '{}'.", typeid(*service).name());
				service->End();
				PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending service done. Service: '{}'.", typeid(*service).name());
			}
			catch (...)
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Error, std::current_exception(), "On ending service. Service: '{}'.", typeid(*service).name());
			}
		}
	}
}
