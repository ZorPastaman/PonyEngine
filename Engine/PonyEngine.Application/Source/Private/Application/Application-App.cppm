/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstdint>
#include <span>
#include <stdexcept>
#include <vector>

#include "PonyEngine/Core/Module.h"
#include "PonyEngine/Log/Log.h"

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
		class AppContext final : public Core::IApplicationContext
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit AppContext(AppLogger& logger) noexcept;
			AppContext(const AppContext&) = delete;
			AppContext(AppContext&&) = delete;

			~AppContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			AppContext& operator =(const AppContext&) = delete;
			AppContext& operator =(AppContext&&) = delete;

		private:
			AppLogger* logger;
		};

		class ModuleContext final : public Core::IModuleContext
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit ModuleContext(AppLogger& logger) noexcept;
			ModuleContext(const ModuleContext&) = delete;
			ModuleContext(ModuleContext&&) = delete;

			~ModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;
			[[nodiscard("Pure function")]]
			virtual std::span<Core::IModule*> Modules() const noexcept override;

			void AddModule(Core::IModule& module);
			void Clear() noexcept;

			ModuleContext& operator =(const ModuleContext&) = delete;
			ModuleContext& operator =(ModuleContext&&) = delete;

		private:
			AppLogger* logger;
			mutable std::vector<Core::IModule*> modules;
		};

		void FindModules(ModuleContext& context, Core::ILoggerModule*& loggerModule, Core::IEngineModule*& engineModule, std::uintptr_t start, std::uintptr_t end);

		AppLogger logger; ///< Application logger.
		AppContext context; ///< Application context.
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) Core::IModule* FirstModule = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_LOG_CHECKPOINT) Core::IModule* LogCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) Core::IModule* LastModule = nullptr;

	App::App() :
		context(logger)
	{
		auto moduleContext = ModuleContext(logger);

		Core::ILoggerModule* loggerModule = nullptr;
		Core::IEngineModule* engineModule = nullptr;

		PONY_LOG(logger.Logger(), Log::LogType::Info, "Find log modules.");
		FindModules(moduleContext, loggerModule, engineModule, reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(Core::IModule*), reinterpret_cast<std::uintptr_t>(&LogCheckpoint));
		if (loggerModule)
		{
			PONY_LOG(logger.Logger(), Log::LogType::Info, "Update logger.");
			logger.SetLogger(loggerModule->CreateLogger(moduleContext, context));
			PONY_LOG(logger.Logger(), Log::LogType::Info, "Logger updated.");
		}
		if (engineModule) [[unlikely]]
		{
			PONY_LOG(logger.Logger(), Log::LogType::Exception, "Engine module found in logger sector.");
			throw std::logic_error("Engine module found in logger sector.");
		}
		moduleContext.Clear();

		// TODO: Add engine module support
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Log modules found.");
	}

	App::AppContext::AppContext(AppLogger& logger) noexcept :
		logger{&logger}
	{
	}

	Log::ILogger& App::AppContext::Logger() noexcept
	{
		return logger->Logger();
	}

	const Log::ILogger& App::AppContext::Logger() const noexcept
	{
		return logger->Logger();
	}

	App::ModuleContext::ModuleContext(AppLogger& logger) noexcept :
		logger{&logger}
	{
	}

	Log::ILogger& App::ModuleContext::Logger() noexcept
	{
		return logger->Logger();
	}

	const Log::ILogger& App::ModuleContext::Logger() const noexcept
	{
		return logger->Logger();
	}

	std::span<Core::IModule*> App::ModuleContext::Modules() const noexcept
	{
		return modules;
	}

	void App::ModuleContext::AddModule(Core::IModule& module)
	{
		modules.push_back(&module);
	}

	void App::ModuleContext::Clear() noexcept
	{
		modules.clear();
	}

	void App::FindModules(ModuleContext& context, Core::ILoggerModule*& loggerModule, Core::IEngineModule*& engineModule, const std::uintptr_t start, const std::uintptr_t end)
	{
		for (std::uintptr_t current = start; current < end; current += sizeof(Core::IModule*))
		{
			if (const auto module = *reinterpret_cast<Core::IModule**>(current))
			{
				PONY_LOG(logger.Logger(), Log::LogType::Info, "Module '{}' found.", module->Name());
				if (const auto loggerModuleCandidate = dynamic_cast<Core::ILoggerModule*>(module))
				{
					if (!loggerModule) [[unlikely]]
					{
						throw std::logic_error("Second logger module is presented.");
					}

					loggerModule = loggerModuleCandidate;
				}
				if (const auto engineModuleCandidate = dynamic_cast<Core::IEngineModule*>(module))
				{
					if (!engineModule) [[unlikely]]
					{
						throw std::logic_error("Second engine module is presented.");
					}

					engineModule = engineModuleCandidate;
				}

				context.AddModule(*module);
			}
		}
	}
}
