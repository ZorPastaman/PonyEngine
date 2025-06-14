/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Core/Module.h"
#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application:App;

import std;

import PonyEngine.Core;
import PonyEngine.Log;

import :AppLogger;
import :PlatformPaths;

export namespace PonyEngine::Application
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

		/// @brief Begins the application.
		void Begin();
		/// @brief Ends the application.
		void End();
		/// @brief Ticks the application.
		void Tick();

		App& operator =(const App&) = delete;
		App& operator =(App&&) = delete;

	private:
		/// @brief Application context.
		class AppContext final : public Core::IApplicationContext
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
			virtual const Core::ApplicationPaths& Paths() const noexcept override;

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
			explicit ModuleContext(Core::IApplicationContext& appContext) noexcept;
			ModuleContext(const ModuleContext&) = delete;
			ModuleContext(ModuleContext&&) = delete;

			~ModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Core::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Core::IApplicationContext& Application() const noexcept override;

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
			Core::IApplicationContext* appContext; ///< Application context.
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

		/// @brief Checks if logger modules are correct.
		/// @param loggerPhase Is this a logger phase now?
		void CheckForLoggerModule(bool loggerPhase) const;
		/// @brief Tries to create a logger if there's at least one registered.
		void TryCreateLogger();

		Core::ApplicationPaths paths; ///< Application paths.
		AppLogger logger; ///< Application logger.
		AppContext appContext; ///< Application context.
		ModuleContext moduleContext; ///< Module context.

		std::uintptr_t lastStartedModule; ///< Last started module.
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) Core::IModule** FirstModule = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_LOG_CHECKPOINT) Core::IModule** LogCheckpoint = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) Core::IModule** LastModule = nullptr;

	App::App(const PlatformPaths& platformPaths) :
		paths
		{
			.gameData = platformPaths.gameData,
			.executable = platformPaths.executable,
			.localData = platformPaths.localData,
			.userData = platformPaths.userData
		},
		appContext(*this),
		moduleContext(appContext),
		lastStartedModule(reinterpret_cast<std::uintptr_t>(&FirstModule))
	{
		std::filesystem::create_directories(paths.localData);
		std::filesystem::create_directories(paths.userData);
	}

	App::~App() noexcept
	{
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Shuts down modules.");
		ShutdownModules(reinterpret_cast<std::uintptr_t>(&FirstModule), lastStartedModule);
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Modules shut down.");
	}

	void App::Begin()
	{
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Starts up modules.");
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Starts up log modules.");
		StartupModules(reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(Core::IModule**), reinterpret_cast<std::uintptr_t>(&LogCheckpoint));
		CheckForLoggerModule(true);
		TryCreateLogger();
		moduleContext.ClearData();
		PONY_LOG(logger.Logger(), Log::LogType::Info, "Modules started up.");
	}

	void App::End()
	{
	}

	void App::Tick()
	{
	}

	App::AppContext::AppContext(App& application) noexcept :
		application{&application}
	{
	}

	Log::ILogger& App::AppContext::Logger() noexcept
	{
		return application->logger.Logger();
	}

	const Log::ILogger& App::AppContext::Logger() const noexcept
	{
		return application->logger.Logger();
	}

	const Core::ApplicationPaths& App::AppContext::Paths() const noexcept
	{
		return application->paths;
	}

	App::ModuleContext::ModuleContext(Core::IApplicationContext& appContext) noexcept :
		appContext{&appContext}
	{
	}

	Core::IApplicationContext& App::ModuleContext::Application() noexcept
	{
		return *appContext;
	}

	const Core::IApplicationContext& App::ModuleContext::Application() const noexcept
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

		throw std::invalid_argument("Such a data doesn't exist in context.");
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
				PONY_LOG(logger.Logger(), Log::LogType::Info, "Starts up '{}' module.", module->Name());
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
				PONY_LOG(logger.Logger(), Log::LogType::Info, "Shuts down '{}' module.", module->Name());
				try
				{
					module->ShutDown(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(logger.Logger(), e, "On '{}' module shutdown.", typeid(*module).name());
				}
				catch (...)
				{
					PONY_LOG(logger.Logger(), Log::LogType::Exception, "Unknown exception on '{}' module shutdown.", typeid(*module).name());
				}
			}
		}
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
			PONY_LOG(logger.Logger(), Log::LogType::Info, "Creates logger with '{}'.", typeid(*loggerFactory).name());
			logger.SetLogger(loggerFactory->Create(moduleContext));
			PONY_LOG(logger.Logger(), Log::LogType::Info, "Logger created.");
		}
	}
}
