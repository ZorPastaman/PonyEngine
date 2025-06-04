/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstdint>
#include <iostream>
#include <string_view>

#include "PonyEngine/Core/Module.h"

export module PonyEngine.Application:App;

import PonyEngine.Core;

import :AppLogger;

export namespace PonyEngine::Application
{
	/// @brief Application.
	class App
	{
	public:
		/// @brief Creates application.
		[[nodiscard("Pure constructor")]]
		App();
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept = default;

		App& operator =(const App&) = delete;
		App& operator =(App&&) = delete;

	private:
		AppLogger logger; ///< Application logger.
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) Core::IModule* FirstModule = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_LOG_CHECKPOINT) Core::IModule* LogCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_ENGINE_CHECKPOINT) Core::IModule* EngineCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) Core::IModule* LastModule = nullptr;

	App::App()
	{
		const std::uintptr_t begin = reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(Core::IModule*);
		const std::uintptr_t end = reinterpret_cast<std::uintptr_t>(&LastModule);
		for (std::uintptr_t current = begin; current < end; current += sizeof(Core::IModule*))
		{
			if (auto module = *reinterpret_cast<Core::IModule**>(current))
			{
				std::cout << module->Name() << "\n";
			}
		}
	}
}
