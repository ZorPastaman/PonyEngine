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
#include "PonyEngine/Platform/Windows/Framework.h"

export module Application.Windows:WindowsQuitChecker;

import PonyEngine.Core;
import PonyEngine.Log;

export namespace Application
{
	/// @brief Checker for WM_QUIT
	class WindowsQuitChecker final
	{
	public:
		/// @brief Creates a @p WindowsQuitChecker.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WindowsQuitChecker(PonyEngine::Core::IApplication& application);
		WindowsQuitChecker(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker(WindowsQuitChecker&&) = delete;

		~WindowsQuitChecker() noexcept = default;

		/// @brief Checks for WM_QUIT.
		/// @param quitCode Quit code.
		/// @return @a False if WM_QUIT is received; @a true otherwise.
		bool Check(int& quitCode) const noexcept;

		WindowsQuitChecker& operator =(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker& operator =(WindowsQuitChecker&&) = delete;

	private:
		PonyEngine::Core::IApplication* application; ///< Application
	};
}

namespace Application
{
	WindowsQuitChecker::WindowsQuitChecker(PonyEngine::Core::IApplication& application) :
		application{&application}
	{
	}

	bool WindowsQuitChecker::Check(int& quitCode) const noexcept
	{
		PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Verbose, "Peek messages.");

		MSG message;
		while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);

			if (message.message == WM_QUIT)
			{
				quitCode = static_cast<int>(message.wParam);
				PONY_LOG_GENERAL(&application->Logger(), PonyEngine::Log::LogType::Info, "Received exit code '{}' from Windows.", quitCode);

				return false;
			}
		}

		return true;
	}
}
