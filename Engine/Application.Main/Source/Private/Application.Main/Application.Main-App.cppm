/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application.Main:App;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :AppDataManager;
import :Console;
import :ExitCodes;
import :FlowManager;
import :LoggerManager;
import :MessageLoopManager;
import :ModuleManager;
import :PathManager;
import :ServiceManager;

namespace PonyEngine::Application
{

}

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
		[[nodiscard("Pure constructor")]]
		App(HINSTANCE instance, HINSTANCE prevInstance, PSTR commandLine, int showCommand);
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept = default;

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
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept override;

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

		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) override;
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept override;

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

		std::unique_ptr<LoggerManager> loggerManager; ///< Logger manager.
		std::unique_ptr<FlowManager> flowManager; ///< Flow manager.
		std::unique_ptr<AppDataManager> appDataManager; ///< Application data manager.
		std::unique_ptr<PathManager> pathManager; ///< Path manager.
		std::unique_ptr<MessageLoopManager> messageLoopManager; ///< Message loop manager.
		std::unique_ptr<ServiceManager> serviceManager; ///< Service manager.
		std::unique_ptr<ModuleManager> moduleManager; ///< Module manager.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	App::App(const HINSTANCE instance, const HINSTANCE prevInstance, const PSTR commandLine, const int showCommand) :
		loggerManager(std::make_unique<LoggerManager>(*static_cast<IApplicationContext*>(this))),
		flowManager(std::make_unique<FlowManager>(*static_cast<IApplicationContext*>(this))),
		appDataManager(std::make_unique<AppDataManager>(*static_cast<IApplicationContext*>(this), instance, prevInstance, commandLine, showCommand)),
		pathManager(std::make_unique<PathManager>(*static_cast<IApplicationContext*>(this))),
		messageLoopManager(std::make_unique<MessageLoopManager>(*static_cast<IApplicationContext*>(this))),
		serviceManager(std::make_unique<ServiceManager>(*static_cast<IApplicationContext*>(this))),
		moduleManager(std::make_unique<ModuleManager>(*static_cast<IApplicationContext*>(this), *loggerManager, *serviceManager))
	{
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

	void App::LogToConsole(const Log::LogType logType, const std::string_view message) const noexcept
	{
		Application::LogToConsole(logType, message);
	}

	void* App::FindService(const std::type_info& type) noexcept
	{
		return serviceManager->FindService(type);
	}

	const void* App::FindService(const std::type_info& type) const noexcept
	{
		return serviceManager->FindService(type);
	}

	bool App::IsRunning() const noexcept
	{
		return flowManager->IsRunning();
	}

	int App::ExitCode() const noexcept
	{
		return flowManager->ExitCode();
	}

	void App::Stop(const int exitCode) noexcept
	{
		flowManager->Stop(exitCode);
	}

	std::uint64_t App::FrameCount() const noexcept
	{
		return flowManager->FrameCount();
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

	void App::AddMessageObserver(IMessageObserver& observer, const UINT messageType)
	{
		messageLoopManager->AddMessageObserver(observer, messageType);
	}

	void App::AddMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		messageLoopManager->AddMessageObserver(observer, messageTypes);
	}

	void App::RemoveMessageObserver(IMessageObserver& observer, const UINT messageType) noexcept
	{
		messageLoopManager->RemoveMessageObserver(observer, messageType);
	}

	void App::RemoveMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes) noexcept
	{
		messageLoopManager->RemoveMessageObserver(observer, messageTypes);
	}

	void App::RemoveMessageObserver(IMessageObserver& observer) noexcept
	{
		messageLoopManager->RemoveMessageObserver(observer);
	}

	int App::Run()
	{
		if (!flowManager->IsRunning()) [[unlikely]]
		{
			throw std::logic_error("Application has already run.");
		}

		Begin();

		try
		{
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Starting application main loop.");
			while (flowManager->IsRunning())
			{
				PONY_LOG(loggerManager->Logger(), Log::LogType::Verbose, "Starting application frame: '{}'.", flowManager->FrameCount());
				messageLoopManager->Tick();
				serviceManager->Tick();
				PONY_LOG(loggerManager->Logger(), Log::LogType::Verbose, "Finishing application frame: '{}'.", flowManager->FrameCount());

				if (flowManager->IsRunning()) [[likely]]
				{
					flowManager->Next();
				}
			}
			PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Finishing application main loop. Exit code: '{}'.", flowManager->ExitCode());
		}
		catch (...)
		{
			End();
			throw;
		}

		End();

		return flowManager->ExitCode();
	}

	void App::Begin()
	{
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning application...");
		serviceManager->Begin();
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Beginning application done.");
	}

	void App::End() noexcept
	{
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending application...");
		serviceManager->End();
		PONY_LOG(loggerManager->Logger(), Log::LogType::Info, "Ending application done.");
	}
}
#endif
