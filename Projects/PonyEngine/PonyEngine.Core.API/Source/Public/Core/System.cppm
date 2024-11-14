/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:System;

import <string_view>;

import :IEngineContext;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief System.
	class System
	{
	public:
		System(const System&) = delete;
		System(System&&) = delete;

		virtual ~System() noexcept = default;

		/// @brief Begins the system.
		/// @details It's called once before a first engine tick.
		virtual void Begin() = 0;
		/// @brief Ends the system.
		/// @details It's called once after a last engine tick.
		virtual void End() = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0; // TODO: Replace with typeid().name. So, no need for such a function.

		System& operator =(const System&) = delete;
		System& operator =(System&&) = delete;

	protected:
		/// @brief Creates a system.
		/// @param engine Engine context.
		/// @param params System parameters.
		[[nodiscard("Pure constructor")]]
		System(IEngineContext& engine, const SystemParams& params) noexcept;

		// TODO: Make private
		IEngineContext* engine; ///< Engine context.
	};
}

namespace PonyEngine::Core
{
	System::System(IEngineContext& engine, const SystemParams&) noexcept :
		engine{&engine}
	{
	}
}
