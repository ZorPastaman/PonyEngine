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

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Main:App;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :DefaultLogger;
import :ExitCodes;
import :ServiceManager;

export namespace PonyEngine::Application
{
	class App final
	{
	public:
		/// @brief Creates application.
		[[nodiscard("Pure constructor")]]
		App();
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept;

		/// @brief Runs the application.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		App& operator =(const App&) = delete;
		App& operator =(App&&) = delete;

	private:
		class AppContext final : public IApplicationContext
		{
		public:
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
			virtual void* FindService(const std::type_info& type) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindService(const std::type_info& type) const noexcept override;

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override;
			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override;
			virtual void Stop(int exitCode) noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::uint64_t FrameCount() const noexcept override;

			AppContext& operator =(const AppContext&) = delete;
			AppContext& operator =(AppContext&&) = delete;

		private:
			App* application; ///< Application.
		};

		class StartingUpModuleContext final : public IModuleContext
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit StartingUpModuleContext(App& application) noexcept;
			StartingUpModuleContext(const StartingUpModuleContext&) = delete;
			StartingUpModuleContext(StartingUpModuleContext&&) = delete;

			~StartingUpModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::size_t DataCount(const std::type_info& type) const noexcept override;
			[[nodiscard("Pure function")]]
			virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const override;
			virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) override;

			[[nodiscard("Pure function")]]
			virtual void* FindService(const std::type_info& type) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindService(const std::type_info& type) const noexcept override;
			virtual void AddService(const std::shared_ptr<IServiceFactory>& factory) override;

			StartingUpModuleContext& operator =(const StartingUpModuleContext&) = delete;
			StartingUpModuleContext& operator =(StartingUpModuleContext&&) = delete;

		private:
			App* application; ///< Application.

			std::unordered_map<std::type_index, std::vector<std::shared_ptr<void>>> dataMap; ///< Data map.
		};

		class ShuttingDownModuleContext final : public IModuleContext
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit ShuttingDownModuleContext(App& application) noexcept;
			ShuttingDownModuleContext(const ShuttingDownModuleContext&) = delete;
			ShuttingDownModuleContext(ShuttingDownModuleContext&&) = delete;

			~ShuttingDownModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::size_t DataCount(const std::type_info& type) const noexcept override;
			[[nodiscard("Pure function")]]
			virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const override;
			virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) override;

			[[nodiscard("Pure function")]]
			virtual void* FindService(const std::type_info& type) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindService(const std::type_info& type) const noexcept override;
			virtual void AddService(const std::shared_ptr<IServiceFactory>& factory) override;

			ShuttingDownModuleContext& operator =(const ShuttingDownModuleContext&) = delete;
			ShuttingDownModuleContext& operator =(ShuttingDownModuleContext&&) = delete;

		private:
			App* application; ///< Application.
		};

		/// @brief Initializes the application.
		/// @param lastModule Last module pointer.
		void Initialize(std::uintptr_t& lastModule);
		/// @brief Finalizes the application.
		/// @param lastModule Last module pointer.
		void Finalize(std::uintptr_t lastModule) noexcept;

		/// @brief Stops the application.
		/// @param exitCode Exit code. It's ignored if the application is already stopped.
		void Stop(int exitCode) noexcept;

		/// @brief On logger added hook.
		/// @param loggerService Logger service.
		/// @param loggerInterface Logger interface.
		void OnLoggerAdded(const IService* loggerService, void* loggerInterface);
		/// @brief On logger removed hook.
		/// @param service Logger service.
		void OnLoggerRemoved(const IService* service) noexcept;

		std::uint64_t frameCount; ///< Frame count.

		int exitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.

		AppContext appContext; ///< Application context.

		std::shared_ptr<DefaultLogger> defaultLogger; ///< Default logger.
		Log::ILogger* logger; ///< Current logger.

		std::unique_ptr<ServiceManager> serviceManager;
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) IModule** FirstModule = nullptr;
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) IModule** LastModule = nullptr;

	App::App() :
		frameCount{0ull},
		exitCode{ExitCodes::InitialExitCode},
		isRunning{true},
		appContext(*this)
	{
		PONY_CONSOLE(Log::LogType::Info, "Constructing default logger...");
		defaultLogger = std::make_shared<DefaultLogger>(appContext);
		logger = defaultLogger.get();
		PONY_CONSOLE(Log::LogType::Info, "Constructing default logger done.");

		PONY_LOG(*logger, Log::LogType::Info, "Constructing service manager...");
		serviceManager = std::make_unique<ServiceManager>(appContext);
		serviceManager->AddInterfaceAddedHook(typeid(Log::ILogger), std::bind(&App::OnLoggerAdded, this, std::placeholders::_1, std::placeholders::_2));
		PONY_LOG(*logger, Log::LogType::Info, "Constructing service manager done.");

		std::uintptr_t lastModule = reinterpret_cast<std::uintptr_t>(&FirstModule);
		try
		{
			Initialize(lastModule);
		}
		catch (...)
		{
			PONY_LOG(*logger, Log::LogType::Info, "Clearing service manager...");
			serviceManager->Clear();
			PONY_LOG(*logger, Log::LogType::Info, "Clearing service manager done.");
			Finalize(lastModule);
			throw;
		}
	}

	App::~App() noexcept
	{
		PONY_LOG(*logger, Log::LogType::Info, "Clearing service manager...");
		serviceManager->Clear();
		PONY_LOG(*logger, Log::LogType::Info, "Clearing service manager done.");
		Finalize(reinterpret_cast<std::uintptr_t>(&LastModule) - sizeof(IModule**));

		PONY_LOG(*logger, Log::LogType::Info, "Releasing service manager...");
		serviceManager.reset();
		PONY_LOG(*logger, Log::LogType::Info, "Releasing service manager done.");

		PONY_CONSOLE(Log::LogType::Info, "Releasing default logger...");
		defaultLogger.reset();
		PONY_CONSOLE(Log::LogType::Info, "Releasing default logger done.");
	}

	int App::Run()
	{
		if (!isRunning) [[unlikely]]
		{
			throw std::logic_error("Application has already run.");
		}

		PONY_LOG(*logger, Log::LogType::Info, "Starting application main loop.");
		while (isRunning)
		{
			PONY_LOG(*logger, Log::LogType::Verbose, "Ticking service manager.");
			serviceManager->Tick();

			++frameCount;
		}
		PONY_LOG(*logger, Log::LogType::Info, "Finishing application main loop. Exit code: '{}'.", exitCode);

		return exitCode;
	}

	App::AppContext::AppContext(App& application) noexcept :
		application{&application}
	{
	}

	Log::ILogger& App::AppContext::Logger() noexcept
	{
		return *application->logger;
	}

	const Log::ILogger& App::AppContext::Logger() const noexcept
	{
		return *application->logger;
	}

	void* App::AppContext::FindService(const std::type_info& type) noexcept
	{
		return application->serviceManager->FindService(type);
	}

	const void* App::AppContext::FindService(const std::type_info& type) const noexcept
	{
		return application->serviceManager->FindService(type);
	}

	bool App::AppContext::IsRunning() const noexcept
	{
		return application->isRunning;
	}

	int App::AppContext::ExitCode() const noexcept
	{
		return application->exitCode;
	}

	void App::AppContext::Stop(const int exitCode) noexcept
	{
		application->Stop(exitCode);
	}

	std::uint64_t App::AppContext::FrameCount() const noexcept
	{
		return application->frameCount;
	}

	App::StartingUpModuleContext::StartingUpModuleContext(App& application) noexcept :
		application{&application}
	{
	}

	IApplicationContext& App::StartingUpModuleContext::Application() noexcept
	{
		return application->appContext;
	}

	const IApplicationContext& App::StartingUpModuleContext::Application() const noexcept
	{
		return application->appContext;
	}

	Log::ILogger& App::StartingUpModuleContext::Logger() noexcept
	{
		return *application->logger;
	}

	const Log::ILogger& App::StartingUpModuleContext::Logger() const noexcept
	{
		return *application->logger;
	}

	std::size_t App::StartingUpModuleContext::DataCount(const std::type_info& type) const noexcept
	{
		if (const auto position = dataMap.find(type); position != dataMap.end())
		{
			return position->second.size();
		}

		return 0uz;
	}

	const std::shared_ptr<void>& App::StartingUpModuleContext::GetData(const std::type_info& type, const std::size_t index) const
	{
		if (const auto position = dataMap.find(type); position != dataMap.end()) [[likely]]
		{
			if (index < position->second.size()) [[likely]]
			{
				return position->second[index];
			}
		}

		throw std::invalid_argument("Incorrect data request.");
	}

	void App::StartingUpModuleContext::AddData(const std::type_info& type, const std::shared_ptr<void>& data)
	{
		dataMap[type].push_back(data);
	}

	void* App::StartingUpModuleContext::FindService(const std::type_info& type) noexcept
	{
		return application->serviceManager->FindService(type);
	}

	const void* App::StartingUpModuleContext::FindService(const std::type_info& type) const noexcept
	{
		return application->serviceManager->FindService(type);
	}

	void App::StartingUpModuleContext::AddService(const std::shared_ptr<IServiceFactory>& factory)
	{
		assert(factory && "The service factory is nullptr!");
		application->serviceManager->AddService(*factory);
	}

	App::ShuttingDownModuleContext::ShuttingDownModuleContext(App& application) noexcept :
		application{&application}
	{
	}

	IApplicationContext& App::ShuttingDownModuleContext::Application() noexcept
	{
		return application->appContext;
	}

	const IApplicationContext& App::ShuttingDownModuleContext::Application() const noexcept
	{
		return application->appContext;
	}

	Log::ILogger& App::ShuttingDownModuleContext::Logger() noexcept
	{
		return *application->logger;
	}

	const Log::ILogger& App::ShuttingDownModuleContext::Logger() const noexcept
	{
		return *application->logger;
	}

	std::size_t App::ShuttingDownModuleContext::DataCount(const std::type_info& type) const noexcept
	{
		return 0uz;
	}

	const std::shared_ptr<void>& App::ShuttingDownModuleContext::GetData(const std::type_info& type, const std::size_t index) const
	{
		throw std::logic_error("Invalid operation");
	}

	void App::ShuttingDownModuleContext::AddData(const std::type_info& type, const std::shared_ptr<void>& data)
	{
		throw std::logic_error("Invalid operation");
	}

	void* App::ShuttingDownModuleContext::FindService(const std::type_info& type) noexcept
	{
		return application->serviceManager->FindService(type);
	}

	const void* App::ShuttingDownModuleContext::FindService(const std::type_info& type) const noexcept
	{
		return application->serviceManager->FindService(type);
	}

	void App::ShuttingDownModuleContext::AddService(const std::shared_ptr<IServiceFactory>& factory)
	{
		throw std::logic_error("Invalid operation");
	}

	void App::Initialize(std::uintptr_t& lastModule)
	{
		PONY_LOG(*logger, Log::LogType::Info, "Starting up modules...")
		auto moduleContext = StartingUpModuleContext(*this);

		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(IModule**); current < reinterpret_cast<std::uintptr_t>(&LastModule); current += sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
				PONY_LOG(*logger, Log::LogType::Info, "Starting up '{}' module...", typeid(*&*module).name());
				try
				{
					module->StartUp(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(*logger, e, "On starting up '{}' module.", typeid(*&*module).name());
					throw;
				}
				catch (...)
				{
					PONY_LOG(*logger, Log::LogType::Exception, "Unknown exception on starting up '{}' module.", typeid(*&*module).name());
					throw;
				}
				PONY_LOG(*logger, Log::LogType::Info, "Starting up '{}' module done.", typeid(*&*module).name());
				lastModule = current;
			}
		}

		PONY_LOG(*logger, Log::LogType::Info, "Starting up modules done.")
	}

	void App::Finalize(const std::uintptr_t lastModule) noexcept
	{
		PONY_LOG(*logger, Log::LogType::Info, "Shutting down modules...")
		const auto moduleContext = ShuttingDownModuleContext(*this);

		for (std::uintptr_t current = lastModule; current > reinterpret_cast<std::uintptr_t>(&FirstModule); current -= sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
				PONY_LOG(*logger, Log::LogType::Info, "Shutting down '{}' module...", typeid(*&*module).name());
				try
				{
					module->ShutDown(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(*logger, e, "On shutting down '{}' module.", typeid(*&*module).name());
				}
				catch (...)
				{
					PONY_LOG(*logger, Log::LogType::Exception, "Unknown exception on shutting down '{}' module.", typeid(*&*module).name());
				}
				PONY_LOG(*logger, Log::LogType::Info, "Shutting down '{}' module done.", typeid(*&*module).name());
			}
		}
		PONY_LOG(*logger, Log::LogType::Info, "Shutting down modules done.")
	}

	void App::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			this->exitCode = exitCode;
			isRunning = false;
			PONY_LOG(*logger, Log::LogType::Info, "Application is stopped. Exit code: '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(*logger, Log::LogType::Verbose, "Application is stopped when it's not running. Ignoring.");
		}
	}

	void App::OnLoggerAdded(const IService* const loggerService, void* const loggerInterface)
	{
		serviceManager->AddServiceRemovedHook(loggerService, std::bind(&App::OnLoggerRemoved, this, std::placeholders::_1));
		logger = static_cast<Log::ILogger*>(loggerInterface);
	}

	void App::OnLoggerRemoved(const IService* service) noexcept
	{
		logger = defaultLogger.get();
	}
}
