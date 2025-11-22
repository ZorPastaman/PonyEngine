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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application.Impl:App;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :AppDataManager;
import :ExitCodes;
import :LoggerManager;
import :ModuleManager;
import :PathManager;
import :ServiceManager;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Windows application.
	class App final : private IApplicationContext
	{
	public:
		/// @brief Creates a Windows application.
		/// @param instance Instance.
		/// @param prevInstance Previous instance.
		/// @param commandLine Command line.
		/// @param showCommand Show command.
		/// @param defaultLogger Default logger.
		[[nodiscard("Pure constructor")]]
		App(HINSTANCE instance, HINSTANCE prevInstance, PSTR commandLine, int showCommand, const std::shared_ptr<Log::ILogger>& defaultLogger);
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectVersion() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyTitle() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectTitle() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableFile() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableDirectory() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& RootDirectory() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& LocalDataDirectory() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& UserDataDirectory() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& TempDataDirectory() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view CommandLine() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual void* FindService(std::type_index type) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const void* FindService(std::type_index type) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual enum FlowState FlowState() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HICON AppIcon() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual HCURSOR AppCursor() const noexcept override;

		/// @brief Runs the application.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		App& operator =(const App&) = delete;
		App& operator =(App&) = delete;

	private:
		/// @brief Begins the application.
		void Begin();
		/// @brief Ends the application.
		void End() noexcept;

		/// @brief Starts a run.
		void StartRun();
		/// @brief Checks if the application is running.
		/// @return @a True if it's running; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsRunning() const noexcept;
		/// @brief Increments the frame count.
		void NextFrame() noexcept;

		std::uint64_t frameCount; ///< Frame count.
		int exitCode; ///< Exit code. It's defined only if @p flowState is stopped.
		enum FlowState flowState; ///< @a True if the engine is running; @a false otherwise.

		std::unique_ptr<LoggerManager> loggerManager; ///< Logger manager.
		std::unique_ptr<AppDataManager> appDataManager; ///< Application data manager.
		std::unique_ptr<PathManager> pathManager; ///< Path manager.
		std::unique_ptr<ServiceManager> serviceManager; ///< Service manager.
		std::unique_ptr<ModuleManager> moduleManager; ///< Module manager.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	App::App(const HINSTANCE instance, const HINSTANCE prevInstance, const PSTR commandLine, const int showCommand, const std::shared_ptr<Log::ILogger>& defaultLogger) :
		frameCount{0ull},
		exitCode{ExitCodes::InitialExitCode},
		flowState{FlowState::StartingUp},
		loggerManager(std::make_unique<LoggerManager>(*static_cast<IApplicationContext*>(this), defaultLogger)),
		appDataManager(std::make_unique<AppDataManager>(*static_cast<IApplicationContext*>(this), instance, prevInstance, commandLine, showCommand)),
		pathManager(std::make_unique<PathManager>(*static_cast<IApplicationContext*>(this))),
		serviceManager(std::make_unique<ServiceManager>(*static_cast<IApplicationContext*>(this))),
		moduleManager(std::make_unique<ModuleManager>(*static_cast<IApplicationContext*>(this), loggerManager->PublicLoggerModuleContext(), serviceManager->PublicServiceModuleContext()))
	{
	}

	App::~App() noexcept
	{
		flowState = FlowState::ShuttingDown;
	}

	std::string_view App::CompanyName() const noexcept
	{
		return Application::CompanyName();
	}

	std::string_view App::ProjectName() const noexcept
	{
		return Application::ProjectName();
	}

	std::string_view App::ProjectVersion() const noexcept
	{
		return Application::ProjectVersion();
	}

	std::string_view App::CompanyTitle() const noexcept
	{
		return Application::CompanyTitle();
	}

	std::string_view App::ProjectTitle() const noexcept
	{
		return Application::ProjectTitle();
	}

	const std::filesystem::path& App::ExecutableFile() const noexcept
	{
		return pathManager->ExecutableFile();
	}

	const std::filesystem::path& App::ExecutableDirectory() const noexcept
	{
		return pathManager->ExecutableDirectory();
	}

	const std::filesystem::path& App::RootDirectory() const noexcept
	{
		return pathManager->RootDirectory();
	}

	const std::filesystem::path& App::LocalDataDirectory() const noexcept
	{
		return pathManager->LocalDataDirectory();
	}

	const std::filesystem::path& App::UserDataDirectory() const noexcept
	{
		return pathManager->UserDataDirectory();
	}

	const std::filesystem::path& App::TempDataDirectory() const noexcept
	{
		return pathManager->TempDataDirectory();
	}

	std::string_view App::CommandLine() const noexcept
	{
		return appDataManager->CommandLine();
	}

	Log::ILogger& App::Logger() noexcept
	{
		return loggerManager->Logger();
	}

	const Log::ILogger& App::Logger() const noexcept
	{
		return loggerManager->Logger();
	}

	void* App::FindService(const std::type_index type) noexcept
	{
		return serviceManager->FindService(type);
	}

	const void* App::FindService(const std::type_index type) const noexcept
	{
		return serviceManager->FindService(type);
	}

	enum FlowState App::FlowState() const noexcept
	{
		return flowState;
	}

	int App::ExitCode() const noexcept
	{
		return exitCode;
	}

	void App::Stop(const int exitCode) noexcept
	{
		if (flowState == FlowState::Running)
		{
			this->exitCode = exitCode;
			flowState = FlowState::Stopped;
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Application stopped. Exit code: '{}'.", this->exitCode);
		}
		else
		{
			if (flowState == FlowState::Stopped) [[likely]]
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Debug, "Tried to stop already stopped Application. Ignoring.");
			}
			else [[unlikely]]
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Debug, "Tried to stop Application in inappropriate state. Ignoring. Current flow state: '{}'.", flowState);
			}
		}
	}

	std::uint64_t App::FrameCount() const noexcept
	{
		return frameCount;
	}

	HINSTANCE App::Instance() const noexcept
	{
		return appDataManager->Instance();
	}

	HINSTANCE App::PrevInstance() const noexcept
	{
		return appDataManager->PrevInstance();
	}

	int App::ShowCommand() const noexcept
	{
		return appDataManager->ShowCommand();
	}

	HICON App::AppIcon() const noexcept
	{
		return appDataManager->AppIcon();
	}

	HCURSOR App::AppCursor() const noexcept
	{
		return appDataManager->AppCursor();
	}

	int App::Run()
	{
		assert(flowState == FlowState::StartingUp && "The flow state is incorrect for running.");

		Begin();

		try
		{
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Starting application main loop.");
			for (StartRun(); IsRunning(); NextFrame())
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Verbose, "Starting application frame: '{}'.", frameCount);
				serviceManager->Tick();
				PONY_LOG(loggerManager->Logger(), Log::LogType::Verbose, "Finishing application frame: '{}'.", frameCount);
			}
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Finishing application main loop. Exit code: '{}'.", exitCode);
		}
		catch (...)
		{
			End();
			throw;
		}

		End();

		return exitCode;
	}

	void App::Begin()
	{
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning application...");
		flowState = FlowState::Beginning;
		serviceManager->Begin();
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning application done.");
	}

	void App::End() noexcept
	{
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending application...");
		flowState = FlowState::Ending;
		serviceManager->End();
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending application done.");
	}

	void App::StartRun()
	{
		flowState = FlowState::Running;
	}

	bool App::IsRunning() const noexcept
	{
		return flowState == FlowState::Running;
	}

	void App::NextFrame() noexcept
	{
		frameCount += IsRunning();
	}
}
#endif
