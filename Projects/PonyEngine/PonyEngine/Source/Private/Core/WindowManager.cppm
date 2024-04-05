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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:WindowManager;

import <format>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
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
		/// @param engineParams Engine parameters.
		/// @param engine Engine that owns the @p WindowManager.
		[[nodiscard("Pure constructor")]]
		WindowManager(const EngineParams& engineParams, IEngine& engine);
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
		Window::IWindow* m_window; /// @brief Created window.
		Window::IWindowFactory* m_windowFactory; /// @brief Factory that created the @p m_window.

		const IEngine& m_engine; /// @brief Engine that owns the @p WindowManager.
	};

	WindowManager::WindowManager(const EngineParams& engineParams, IEngine& engine) :
		m_engine{engine}
	{
		m_windowFactory = engineParams.GetWindowFactory();
		
		if (m_windowFactory != nullptr)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Create a window '{}'.", m_windowFactory->GetWindowName()).c_str());
			m_window = m_windowFactory->Create(engine);
			assert((m_window != nullptr));
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Window '{}' created.", m_window->GetName()).c_str());
		}
		else
		{
			m_window = nullptr;
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Window creation skipped.");
		}
	}

	WindowManager::~WindowManager() noexcept
	{
		if (m_windowFactory != nullptr)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Destroy a window '{}'.", m_window->GetName()).c_str());
			m_windowFactory->Destroy(m_window);
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Window destroyed '{}'.", m_windowFactory->GetWindowName()).c_str());
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
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Show a window.");
			m_window->ShowWindow();
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Window shown.");
		}
	}

	void WindowManager::Tick() const
	{
		if (m_window != nullptr)
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, "Tick a window.");
			m_window->Tick();
		}
	}
}
