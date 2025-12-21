/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl:Windows.App;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :ExitCodes;
import :FlowManager;
import :ModuleManager;
import :ServiceManager;

import :Windows.AppDataManager;
import :Windows.LoggerManager;
import :Windows.PathManager;

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

		/// @brief Runs the application.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		App& operator =(const App&) = delete;
		App& operator =(App&) = delete;

	private:
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

		FlowManager flowManager; ///< Flow manager.
		LoggerManager loggerManager; ///< Logger manager.
		AppDataManager appDataManager; ///< Application data manager.
		PathManager pathManager; ///< Path manager.
		ServiceManager serviceManager; ///< Service manager.
		ModuleManager moduleManager; ///< Module manager.
	};
}

namespace PonyEngine::Application::Windows
{
	App::App(const HINSTANCE instance, const HINSTANCE prevInstance, const PSTR commandLine, const int showCommand, const std::shared_ptr<Log::ILogger>& defaultLogger) :
		flowManager(*this),
		loggerManager(*this, defaultLogger),
		appDataManager(*this, instance, prevInstance, commandLine, showCommand),
		pathManager(*this),
		serviceManager(*this),
		moduleManager(*this, loggerManager, serviceManager)
	{
	}

	App::~App() noexcept
	{
		flowManager.ShutDown();
	}

	int App::Run()
	{
		const auto begin = [&] { serviceManager.Begin(); };
		const auto end = [&] noexcept { serviceManager.End(); };
		const auto tick = [&] { serviceManager.Tick(); };

		return flowManager.Run(begin, end, tick);
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
		return pathManager.ExecutableFile();
	}

	const std::filesystem::path& App::ExecutableDirectory() const noexcept
	{
		return pathManager.ExecutableDirectory();
	}

	const std::filesystem::path& App::RootDirectory() const noexcept
	{
		return pathManager.RootDirectory();
	}

	const std::filesystem::path& App::LocalDataDirectory() const noexcept
	{
		return pathManager.LocalDataDirectory();
	}

	const std::filesystem::path& App::UserDataDirectory() const noexcept
	{
		return pathManager.UserDataDirectory();
	}

	const std::filesystem::path& App::TempDataDirectory() const noexcept
	{
		return pathManager.TempDataDirectory();
	}

	std::string_view App::CommandLine() const noexcept
	{
		return appDataManager.CommandLine();
	}

	Log::ILogger& App::Logger() noexcept
	{
		return loggerManager.Logger();
	}

	const Log::ILogger& App::Logger() const noexcept
	{
		return loggerManager.Logger();
	}

	void* App::FindService(const std::type_index type) noexcept
	{
		return serviceManager.FindService(type);
	}

	const void* App::FindService(const std::type_index type) const noexcept
	{
		return serviceManager.FindService(type);
	}

	enum FlowState App::FlowState() const noexcept
	{
		return flowManager.FlowState();
	}

	int App::ExitCode() const noexcept
	{
		return flowManager.ExitCode();
	}

	void App::Stop(const int exitCode) noexcept
	{
		flowManager.Stop(exitCode);
	}

	std::uint64_t App::FrameCount() const noexcept
	{
		return flowManager.FrameCount();
	}

	HINSTANCE App::Instance() const noexcept
	{
		return appDataManager.Instance();
	}

	HINSTANCE App::PrevInstance() const noexcept
	{
		return appDataManager.PrevInstance();
	}

	int App::ShowCommand() const noexcept
	{
		return appDataManager.ShowCommand();
	}

	HICON App::AppIcon() const noexcept
	{
		return appDataManager.AppIcon();
	}

	HCURSOR App::AppCursor() const noexcept
	{
		return appDataManager.AppCursor();
	}
}
