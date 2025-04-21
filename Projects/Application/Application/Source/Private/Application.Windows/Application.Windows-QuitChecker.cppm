/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module Application.Windows:QuitChecker;

import PonyDebug.Log;

import PonyEngine.Core;

export namespace Application::Windows
{
	/// @brief Checker for WM_QUIT
	class QuitChecker final
	{
	public:
		/// @brief Creates a @p QuitChecker.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit QuitChecker(PonyEngine::Core::IApplicationContext& application) noexcept;
		QuitChecker(const QuitChecker&) = delete;
		QuitChecker(QuitChecker&&) = delete;

		~QuitChecker() noexcept = default;

		/// @brief Checks for WM_QUIT.
		/// @param quitCode Quit code.
		/// @return @a False if WM_QUIT is received; @a true otherwise.
		bool Check(int& quitCode) const noexcept;

		QuitChecker& operator =(const QuitChecker&) = delete;
		QuitChecker& operator =(QuitChecker&&) = delete;

	private:
		PonyEngine::Core::IApplicationContext* application; ///< Application
	};
}

namespace Application::Windows
{
	QuitChecker::QuitChecker(PonyEngine::Core::IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	bool QuitChecker::Check(int& quitCode) const noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Verbose, "Peek application messages.");

		MSG message;
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);

			if (message.message == WM_QUIT)
			{
				quitCode = static_cast<int>(message.wParam);
				PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Received exit code '{}' from Windows.", quitCode);

				return false;
			}
		}

		return true;
	}
}
