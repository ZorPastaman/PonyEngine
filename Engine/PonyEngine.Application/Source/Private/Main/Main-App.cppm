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

#include "PonyEngine/Core/Module.h"
#include "PonyEngine/Log/Log.h"

export module PonyEngine.Main:App;

import std;

import PonyEngine.Application;
import PonyEngine.Core;
import PonyEngine.Log;

import :DefaultLogger;
import :PlatformPaths;

export namespace PonyEngine::Main
{
	/// @brief Application.
	class App
	{
	public:
		/// @brief Creates application.
		[[nodiscard("Pure constructor")]]
		explicit App(const PlatformPaths& platformPaths);
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept;

		/// @brief Ticks the application.
		/// @param exitCode Exit code. Set if the function returns @a true.
		/// @return @a True if the application should exit; @a false otherwise.
		[[nodiscard("Return value must be checked: true means no further ticks should be called")]]
		bool Tick(int& exitCode);

		App& operator =(const App&) = delete;
		App& operator =(App&&) = delete;

	private:
		/// @brief Application context.
		class AppContext final : public Application::IApplicationContext
		{
		public:
			/// @brief Creates an application context.
			/// @param application Application.
			[[nodiscard("Pure constructor")]]
			explicit AppContext(App& application) noexcept;
			AppContext(const AppContext&) = delete;
			AppContext(AppContext&&) = delete;

			~AppContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Engine::IEngine* Engine() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Engine::IEngine* Engine() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual const Application::ApplicationPaths& Paths() const noexcept override;

			AppContext& operator =(const AppContext&) = delete;
			AppContext& operator =(AppContext&&) = delete;

		private:
			App* application; ///< Application.
		};

		/// @brief Module context.
		class ModuleContext final : public Core::IModuleContext
		{
		public:
			/// @brief Creates a module context.
			/// @param appContext Application context.
			[[nodiscard("Pure constructor")]]
			explicit ModuleContext(Application::IApplicationContext& appContext) noexcept;
			ModuleContext(const ModuleContext&) = delete;
			ModuleContext(ModuleContext&&) = delete;

			~ModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Application::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Application::IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::size_t DataCount(const std::type_info& type) const noexcept override;
			[[nodiscard("Pure function")]]
			virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const override;
			virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) override;

			/// @brief Clears data.
			void ClearData() noexcept;

			ModuleContext& operator =(const ModuleContext&) = delete;
			ModuleContext& operator =(ModuleContext&&) = delete;

		private:
			Application::IApplicationContext* appContext; ///< Application context.
			std::unordered_map<std::type_index, std::vector<std::shared_ptr<void>>> dataMap; ///< Data map.
		};

		/// @brief Start up modules.
		/// @param start Start pointer.
		/// @param end End pointer.
		void StartupModules(std::uintptr_t start, std::uintptr_t end);
		/// @brief Shuts down modules.
		/// @param start Start pointer.
		/// @param end End pointer.
		void ShutdownModules(std::uintptr_t start, std::uintptr_t end) const noexcept;

		/// @brief Finalizes the application.
		void Finalize() noexcept;

		/// @brief Checks if logger modules are correct.
		/// @param loggerPhase Is this a logger phase now?
		void CheckForLoggerModule(bool loggerPhase) const;
		/// @brief Tries to create a logger if there's at least one registered.
		void TryCreateLogger();

		/// @brief Checks if engine modules are correct.
		/// @param enginePhase Is this an engine phase now?
		void CheckForEngineModule(bool enginePhase) const;
		/// @brief Creates an engine.
		void CreateEngine();

		Application::ApplicationPaths paths; ///< Application paths.

		std::shared_ptr<DefaultLogger> defaultLogger; ///< Default logger.
		std::shared_ptr<Core::ILogger> logger; ///< Current logger.
		Log::ILogger* publicLogger; ///< Public logger from the current logger.

		std::shared_ptr<Core::IEngine> engine; ///< Engine.
		Engine::IEngine* publicEngine; ///< Public engine from the engine.

		AppContext appContext; ///< Application context.
		ModuleContext moduleContext; ///< Module context.

		std::uintptr_t lastStartedModule; ///< Last started module.
	};
}

namespace PonyEngine::Main
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) Core::IModule** FirstModule = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_LOG_CHECKPOINT) Core::IModule** LogCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_ENGINE_EARLY_CHECKPOINT) Core::IModule** EngineEarlyCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_ENGINE_CHECKPOINT) Core::IModule** EngineCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) Core::IModule** LastModule = nullptr;

	App::App(const PlatformPaths& platformPaths) :
		paths
		{
			.gameData = platformPaths.gameData,
			.executable = platformPaths.executable,
			.localData = platformPaths.localData,
			.userData = platformPaths.userData
		},
		defaultLogger(std::make_shared<DefaultLogger>()),
		logger(defaultLogger),
		publicLogger{&logger->PublicLogger()},
		publicEngine{nullptr},
		appContext(*this),
		moduleContext(appContext),
		lastStartedModule(reinterpret_cast<std::uintptr_t>(&FirstModule))
	{
		PONY_LOG(*publicLogger, Log::LogType::Info, "Creating data directories.");
		std::filesystem::create_directories(paths.localData);
		std::filesystem::create_directories(paths.userData);

		try
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up modules...");
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up log modules.");
			StartupModules(reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(Core::IModule**), reinterpret_cast<std::uintptr_t>(&LogCheckpoint));
			CheckForLoggerModule(true);
			CheckForEngineModule(false);
			TryCreateLogger();
			moduleContext.ClearData();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up early engine modules.");
			StartupModules(reinterpret_cast<std::uintptr_t>(&LogCheckpoint) + sizeof(Core::IModule**), reinterpret_cast<std::uintptr_t>(&EngineEarlyCheckpoint));
			CheckForLoggerModule(false);
			CheckForEngineModule(false);
			moduleContext.ClearData();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up engine modules.");
			StartupModules(reinterpret_cast<std::uintptr_t>(&EngineEarlyCheckpoint) + sizeof(Core::IModule**), reinterpret_cast<std::uintptr_t>(&EngineCheckpoint));
			CheckForLoggerModule(false);
			CheckForEngineModule(true);
			CreateEngine();
			moduleContext.ClearData();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up late engine modules.");
			StartupModules(reinterpret_cast<std::uintptr_t>(&EngineCheckpoint) + sizeof(Core::IModule**), reinterpret_cast<std::uintptr_t>(&LastModule));
			CheckForLoggerModule(false);
			CheckForEngineModule(false);
			moduleContext.ClearData();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up modules done.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(*publicLogger, e, "On starting up modules.");
			Finalize();

			throw;
		}
		catch (...)
		{
			PONY_LOG(*publicLogger, Log::LogType::Exception, "Unknown exception on starting up modules.");
			Finalize();

			throw;
		}
	}

	App::~App() noexcept
	{
		Finalize();
	}

	bool App::Tick(int& exitCode)
	{
		PONY_LOG(*publicLogger, Log::LogType::Verbose, "Ticking engine.");
		engine->Tick();

		const bool isRunning = engine->IsRunning();
		if (!isRunning)
		{
			exitCode = engine->ExitCode();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Engine stopped. Exit code: {}.", exitCode);
		}

		return !isRunning;
	}

	App::AppContext::AppContext(App& application) noexcept :
		application{&application}
	{
	}

	Log::ILogger& App::AppContext::Logger() noexcept
	{
		return *application->publicLogger;
	}

	const Log::ILogger& App::AppContext::Logger() const noexcept
	{
		return *application->publicLogger;
	}

	Engine::IEngine* App::AppContext::Engine() noexcept
	{
		return application->publicEngine;
	}

	const Engine::IEngine* App::AppContext::Engine() const noexcept
	{
		return application->publicEngine;
	}

	const Application::ApplicationPaths& App::AppContext::Paths() const noexcept
	{
		return application->paths;
	}

	App::ModuleContext::ModuleContext(Application::IApplicationContext& appContext) noexcept :
		appContext{&appContext}
	{
	}

	Application::IApplicationContext& App::ModuleContext::Application() noexcept
	{
		return *appContext;
	}

	const Application::IApplicationContext& App::ModuleContext::Application() const noexcept
	{
		return *appContext;
	}

	std::size_t App::ModuleContext::DataCount(const std::type_info& type) const noexcept
	{
		if (const auto position = dataMap.find(type); position != dataMap.cend())
		{
			return position->second.size();
		}

		return 0;
	}

	const std::shared_ptr<void>& App::ModuleContext::GetData(const std::type_info& type, const std::size_t index) const
	{
		if (const auto position = dataMap.find(type); position != dataMap.cend())
		{
			if (index < position->second.size())
			{
				return position->second[index];
			}
		}

		throw std::invalid_argument("Data not found.");
	}

	void App::ModuleContext::AddData(const std::type_info& type, const std::shared_ptr<void>& data)
	{
		dataMap[type].push_back(data);
	}

	void App::ModuleContext::ClearData() noexcept
	{
		dataMap.clear();
	}

	void App::StartupModules(const std::uintptr_t start, const std::uintptr_t end)
	{
		for (std::uintptr_t current = start; current < end; current += sizeof(Core::IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<Core::IModule***>(current))
			{
				Core::IModule* const module = *modulePtr;
				PONY_LOG(*publicLogger, Log::LogType::Info, "Starting up '{}' module.", module->Name());
				module->StartUp(moduleContext);
				lastStartedModule = current;
			}
		}
	}

	void App::ShutdownModules(const std::uintptr_t start, const std::uintptr_t end) const noexcept
	{
		for (std::uintptr_t current = end; current > start; current -= sizeof(Core::IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<Core::IModule***>(current))
			{
				Core::IModule* const module = *modulePtr;
				PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down '{}' module.", module->Name());
				try
				{
					module->ShutDown(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(*publicLogger, e, "On shutting down '{}' module.", typeid(*module).name());
				}
				catch (...)
				{
					PONY_LOG(*publicLogger, Log::LogType::Exception, "Unknown exception on shutting down '{}' module.", typeid(*module).name());
				}
			}
		}
	}

	void App::Finalize() noexcept
	{
		PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down modules...");
		if (lastStartedModule > reinterpret_cast<std::uintptr_t>(&EngineCheckpoint))
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down late engine modules...");
			ShutdownModules(reinterpret_cast<std::uintptr_t>(&EngineCheckpoint), lastStartedModule);
			lastStartedModule = reinterpret_cast<std::uintptr_t>(&EngineCheckpoint) - sizeof(Core::IModule**);
		}

		if (engine)
		{
			if (engine->IsRunning())
			{
				PONY_LOG(*publicLogger, Log::LogType::Info, "Stopping engine...", engine->IsRunning());
				engine->Stop();
				PONY_LOG(*publicLogger, Log::LogType::Info, "Stopping engine done. Exit code", engine->ExitCode());
			}

			PONY_LOG(*publicLogger, Log::LogType::Info, "Destructing engine...");
			engine.reset();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Destructing engine done.");
		}

		if (lastStartedModule > reinterpret_cast<std::uintptr_t>(&EngineEarlyCheckpoint))
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down engine modules...");
			ShutdownModules(reinterpret_cast<std::uintptr_t>(&EngineEarlyCheckpoint), lastStartedModule);
			lastStartedModule = reinterpret_cast<std::uintptr_t>(&EngineEarlyCheckpoint) - sizeof(Core::IModule**);
		}

		if (lastStartedModule > reinterpret_cast<std::uintptr_t>(&LogCheckpoint))
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down early engine modules...");
			ShutdownModules(reinterpret_cast<std::uintptr_t>(&LogCheckpoint), lastStartedModule);
			lastStartedModule = reinterpret_cast<std::uintptr_t>(&LogCheckpoint) - sizeof(Core::IModule**);
		}

		if (logger != defaultLogger)
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Destructing logger...");
			logger = defaultLogger;
			publicLogger = &logger->PublicLogger();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Destructing logger done.");
		}

		if (lastStartedModule > reinterpret_cast<std::uintptr_t>(&FirstModule))
		{
			PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down log modules...");
			ShutdownModules(reinterpret_cast<std::uintptr_t>(&FirstModule), lastStartedModule);
			lastStartedModule = reinterpret_cast<std::uintptr_t>(&FirstModule);
		}
		PONY_LOG(*publicLogger, Log::LogType::Info, "Shutting down modules done.");
	}

	void App::CheckForLoggerModule(const bool loggerPhase) const
	{
		if (moduleContext.DataCount(typeid(Core::ILoggerFactory)) > static_cast<std::size_t>(loggerPhase)) [[unlikely]]
		{
			if (loggerPhase)
			{
				throw std::logic_error("More than 1 logger modules added.");
			}
			else
			{
				throw std::logic_error("No logger modules allowed out of log module phase.");
			}
		}
	}

	void App::TryCreateLogger()
	{
		if (moduleContext.DataCount(typeid(Core::ILoggerFactory)) > 0Z)
		{
			const std::shared_ptr<void>& loggerFactoryData = moduleContext.GetData(typeid(Core::ILoggerFactory), 0Z);
			const std::shared_ptr<Core::ILoggerFactory> loggerFactory = std::static_pointer_cast<Core::ILoggerFactory>(loggerFactoryData);
			PONY_LOG(*publicLogger, Log::LogType::Info, "Creating application logger... Factory: '{}'", typeid(*loggerFactory).name());
			logger = loggerFactory->Create(moduleContext);
			assert(logger && "The created logger is nullptr!");
			publicLogger = &logger->PublicLogger();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Creating application logger done. Logger: '{}'.", typeid(*logger).name());
		}
	}

	void App::CheckForEngineModule(const bool enginePhase) const
	{
		if (moduleContext.DataCount(typeid(Core::IEngineFactory)) > static_cast<std::size_t>(enginePhase)) [[unlikely]]
		{
			if (enginePhase)
			{
				throw std::logic_error("More than 1 engine modules added.");
			}
			else
			{
				throw std::logic_error("No engine modules allowed out of engine module phase.");
			}
		}
	}

	void App::CreateEngine()
	{
		if (moduleContext.DataCount(typeid(Core::IEngineFactory)) > 0Z)
		{
			const std::shared_ptr<void>& engineFactoryData = moduleContext.GetData(typeid(Core::IEngineFactory), 0Z);
			const std::shared_ptr<Core::IEngineFactory> engineFactory = std::static_pointer_cast<Core::IEngineFactory>(engineFactoryData);
			PONY_LOG(*publicLogger, Log::LogType::Info, "Creating application engine... Factory: '{}'", typeid(*engineFactory).name());
			engine = engineFactory->Create(moduleContext);
			assert(engine && "The created engine is nullptr!");
			publicEngine = &engine->PublicEngine();
			PONY_LOG(*publicLogger, Log::LogType::Info, "Creating application engine done. Engine: '{}'.", typeid(*engine).name());
		}
		else
		{
			throw std::logic_error("No engine factory found.");
		}
	}
}
