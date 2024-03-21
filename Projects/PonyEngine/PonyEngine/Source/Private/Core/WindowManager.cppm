/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:WindowManager;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Window;
import PonyEngine.Window.Factories;

namespace PonyEngine::Core
{
	/// @brief Holder of a window.
	export class WindowManager final
	{
	public:
		/// @brief Creates a @p WindowManager.
		/// @param windowFactory Window factory. May be nullptr.
		/// @param engine Engine that owns the @p WindowManager.
		[[nodiscard("Pure constructor")]]
		WindowManager(Window::IWindowFactory* windowFactory, IEngine& engine);
		WindowManager(const WindowManager&) = delete;
		[[nodiscard("Pure constructor")]]
		inline WindowManager(WindowManager&& other) noexcept = default;

		~WindowManager() noexcept;

		/// @brief Gets a window.
		/// @return Window. May be nullptr if the window is not created.
		[[nodiscard("Pure function")]]
		inline Window::IWindow* GetWindow() const noexcept;

		/// @brief Show a window if it exists.
		void ShowWindow() const;

		/// @brief Ticks a window if it exists.
		void Tick() const;

		WindowManager& operator =(const WindowManager&) = delete;
		WindowManager& operator =(WindowManager&& other) noexcept = default;

	private:
		Window::IWindow* const m_window; /// @brief Created window.
		Window::IWindowFactory* const m_windowFactory; /// @brief Factory that created the @p m_window.

		const IEngine& m_engine; /// @brief Engine that owns the @p WindowManager.
	};

	WindowManager::WindowManager(Window::IWindowFactory* const windowFactory, IEngine& engine) :
		m_window{windowFactory != nullptr ? windowFactory->Create(engine) : nullptr},
		m_windowFactory{windowFactory},
		m_engine{engine}
	{
		PONY_LOG_IF(m_window != nullptr, m_engine.GetLogger(), Debug::Log::LogType::Info, "Window created.");
		PONY_LOG_IF(m_window == nullptr, m_engine.GetLogger(), Debug::Log::LogType::Info, "Window creation skipped.");
	}

	WindowManager::~WindowManager() noexcept
	{
		if (m_windowFactory != nullptr)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy a window.");
			m_windowFactory->Destroy(m_window);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window destroyed.");
		}
	}

	inline Window::IWindow* WindowManager::GetWindow() const noexcept
	{
		return m_window;
	}

	void WindowManager::ShowWindow() const
	{
		if (m_window != nullptr)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Show a window.");
			m_window->ShowWindow();
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window shown.");
		}
	}

	void WindowManager::Tick() const
	{
		if (m_window != nullptr)
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Tick a window.");
			m_window->Tick();
		}
	}
}
