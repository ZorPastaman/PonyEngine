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

export module PonyEngine.File.Impl.Windows:ServiceContext;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :Worker;

export namespace PonyEngine::File
{
	/// @brief Service context.
	class ServiceContext final
	{
	public:
		/// @brief Creates a service context.
		/// @param application Application.
		/// @param worker Worker.
		[[nodiscard("Pure constructor")]]
		ServiceContext(Application::IApplication& application, class Worker& worker) noexcept;
		ServiceContext(const ServiceContext&) = delete;
		ServiceContext(ServiceContext&&) = delete;

		~ServiceContext() noexcept = default;

		/// @brief Gets the application.
		/// @return Application.
		[[nodiscard("Pure function")]]
		Application::IApplication& Application() const noexcept;
		/// @brief Gets the log service.
		/// @return Log service.
		[[nodiscard("Pure function")]]
		const Log::ILogService* LogService() const noexcept;
		/// @brief Gets the worker.
		/// @return Worker.
		[[nodiscard("Pure function")]]
		class Worker& Worker() const noexcept;

		/// @brief Increments the file count.
		void IncrementFileCount() const noexcept;
		/// @brief Decrements the file count.
		void DecrementFileCount() const noexcept;

		/// @brief Validates that all the counts are zeroes.
		void EnsureZeroCounts() const noexcept;

		ServiceContext& operator =(const ServiceContext&) = delete;
		ServiceContext& operator =(ServiceContext&&) = delete;

	private:
		Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.
		class Worker* worker; ///< Worker.

#ifndef NDEBUG
		mutable std::atomic_size_t fileCount; ///< File count.
#endif
	};
}

namespace PonyEngine::File
{
	ServiceContext::ServiceContext(Application::IApplication& application, class Worker& worker) noexcept :
#ifndef NDEBUG
		fileCount(0uz),
#endif
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		worker{&worker}
	{
	}

	Application::IApplication& ServiceContext::Application() const noexcept
	{
		return *application;
	}

	const Log::ILogService* ServiceContext::LogService() const noexcept
	{
		return logService;
	}

	class Worker& ServiceContext::Worker() const noexcept
	{
		return *worker;
	}

	void ServiceContext::IncrementFileCount() const noexcept
	{
#ifndef NDEBUG
		fileCount.fetch_add(1uz, std::memory_order::relaxed);
#endif
	}

	void ServiceContext::DecrementFileCount() const noexcept
	{
#ifndef NDEBUG
		const std::size_t prev = fileCount.fetch_sub(1uz, std::memory_order::relaxed);
		assert(prev != 0uz && "Invalid file count decrement.");
#endif
	}

	void ServiceContext::EnsureZeroCounts() const noexcept
	{
#ifndef NDEBUG
		assert(fileCount.load(std::memory_order::relaxed) == 0uz && "File count is not zero.");
#endif
	}
}
