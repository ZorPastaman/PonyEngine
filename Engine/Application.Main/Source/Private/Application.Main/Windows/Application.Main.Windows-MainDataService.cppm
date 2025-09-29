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

export module PonyEngine.Application.Main.Windows:MainDataService;

import PonyEngine.Application.Windows;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows main data service.
	class MainDataService final : public IService, private IMainDataService
	{
	public:
		/// @brief Creates a Windows main data service.
		/// @param instance Instance.
		/// @param prevInstance Previous instance.
		/// @param commandLine Command line.
		/// @param showCommand Show command.
		/// @param appIcon Application icon.
		[[nodiscard("Pure constructor")]]
		MainDataService(HINSTANCE instance, HINSTANCE prevInstance, const char* commandLine, int showCommand, HICON appIcon) noexcept;
		MainDataService(const MainDataService&) = delete;
		MainDataService(MainDataService&&) = delete;

		~MainDataService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const char* CommandLine() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HICON AppIcon() const noexcept override;

		/// @brief Gets the public main data service.
		/// @return Public main data service.
		[[nodiscard("Pure function")]]
		IMainDataService& PublicMainDataService() noexcept;
		/// @brief Gets the public main data service.
		/// @return Public main data service.
		[[nodiscard("Pure function")]]
		const IMainDataService& PublicMainDataService() const noexcept;

		MainDataService& operator =(const MainDataService&) = delete;
		MainDataService& operator =(MainDataService&&) = delete;

	private:
		HINSTANCE instance; ///< Instance.
		HINSTANCE prevInstance; ///< Previous instance.
		const char* commandLine; ///< Command line.
		int showCommand; ///< Show command.

		HICON appIcon; ///< Application icon.
	};
}

namespace PonyEngine::Application::Windows
{
	MainDataService::MainDataService(const HINSTANCE instance, const HINSTANCE prevInstance, const char* const commandLine, const int showCommand, const HICON appIcon) noexcept :
		instance{instance},
		prevInstance{prevInstance},
		commandLine{commandLine},
		showCommand{showCommand},
		appIcon(appIcon)
	{
	}

	void MainDataService::Begin()
	{
	}

	void MainDataService::End()
	{
	}

	HINSTANCE MainDataService::Instance() const noexcept
	{
		return instance;
	}

	HINSTANCE MainDataService::PrevInstance() const noexcept
	{
		return prevInstance;
	}

	const char* MainDataService::CommandLine() const noexcept
	{
		return commandLine;
	}

	int MainDataService::ShowCommand() const noexcept
	{
		return showCommand;
	}

	HICON MainDataService::AppIcon() const noexcept
	{
		return appIcon;
	}

	IMainDataService& MainDataService::PublicMainDataService() noexcept
	{
		return *this;
	}

	const IMainDataService& MainDataService::PublicMainDataService() const noexcept
	{
		return *this;
	}
}
