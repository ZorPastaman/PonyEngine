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

export module PonyEngine.World.Impl:ServiceContext;

import std;

import PonyEngine.Application;

import :TypeRegistry;

export namespace PonyEngine::World
{
	/// @brief World service context.
	class ServiceContext final
	{
	public:
		/// @brief Creates a world service context.
		/// @param application Application.
		/// @param typeRegistry Type registry.
		[[nodiscard("Pure constructor")]]
		ServiceContext(Application::IApplication& application, const class TypeRegistry& typeRegistry) noexcept;
		ServiceContext(const ServiceContext&) = delete;
		ServiceContext(ServiceContext&&) = delete;

		~ServiceContext() noexcept = default;

		/// @brief Gets the application.
		/// @return Application.
		[[nodiscard("Pure function")]]
		Application::IApplication& Application() const noexcept;
		/// @brief Gets the type registry.
		/// @return Type registry.
		[[nodiscard("Pure function")]]
		const TypeRegistry& TypeRegistry() const noexcept;

		/// @brief Increments world count. Must be called on successful world creation.
		void IncrementWorldCount() const noexcept;
		/// @brief Decrements world count. Must be called on world destruction.
		void DecrementWorldCount() const noexcept;

		/// @brief Ensures that counts are zero. Must be called on world service destruction.
		void EnsureZeroCounts() const noexcept;

		ServiceContext& operator =(const ServiceContext&) = delete;
		ServiceContext& operator =(ServiceContext&&) = delete;

	private:
		Application::IApplication* application = nullptr; ///< Application.
		const class TypeRegistry* typeRegistry = nullptr; ///< Type registry.

#ifndef NDEBUG
		mutable std::atomic_size_t worldCount; ///< World count.
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::atomic_size_t is not lock free.");
	};
}

namespace PonyEngine::World
{
	ServiceContext::ServiceContext(Application::IApplication& application, const class TypeRegistry& typeRegistry) noexcept :
#ifndef NDEBUG
		worldCount(0uz),
#endif
		application{&application},
		typeRegistry{&typeRegistry}
	{
	}

	Application::IApplication& ServiceContext::Application() const noexcept
	{
		return *application;
	}

	const TypeRegistry& ServiceContext::TypeRegistry() const noexcept
	{
		return *typeRegistry;
	}

	void ServiceContext::IncrementWorldCount() const noexcept
	{
#ifndef NDEBUG
		worldCount.fetch_add(1uz, std::memory_order::relaxed);
#endif
	}

	void ServiceContext::DecrementWorldCount() const noexcept
	{
#ifndef NDEBUG
		const std::size_t prev = worldCount.fetch_sub(1uz, std::memory_order::relaxed);
		assert(prev > 0uz && "Invalid world count decrement.");
#endif
	}

	void ServiceContext::EnsureZeroCounts() const noexcept
	{
#ifndef NDEBUG
		assert(worldCount.load(std::memory_order::relaxed) == 0uz && "World count is not zero.");
#endif
	}
}
