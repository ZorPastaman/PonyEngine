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

export module PonyEngine.Surface.Main:WindowClass;

import PonyEngine.Application.Extension;
import PonyEngine.File;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Text;

import :MessageHandler;

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Window class.
	class WindowClass final
	{
	public:
		/// @brief Creates a Windows class.
		/// @param application Application context.
		/// @param mainIcon Main application icon.
		/// @param smallIcon Small application icon.
		/// @param cursor Cursor.
		/// @param backgroundColor Background color.
		[[nodiscard("Pure constructor")]]
		WindowClass(Application::IApplicationContext& application, HICON mainIcon, HICON smallIcon, HCURSOR cursor, const Math::ColorRGB<std::uint8_t>& backgroundColor);
		WindowClass(const WindowClass&) = delete;
		WindowClass(WindowClass&&) = delete;

		~WindowClass() noexcept;

		/// @brief Gets the module handle.
		/// @return Module handle.
		[[nodiscard("Pure function")]]
		HMODULE ModuleHandle() const noexcept;
		/// @brief Gets the class handle.
		/// @return Class handle.
		[[nodiscard("Pure function")]]
		ATOM ClassHandle() noexcept;

		WindowClass& operator =(const WindowClass&) = delete;
		WindowClass& operator =(WindowClass&&) = delete;

	private:
		Application::IApplicationContext* application; ///< Application.

		HMODULE moduleHandle; ///< Module instance handle.
		ATOM classHandle; /// Registered class handle.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	WindowClass::WindowClass(Application::IApplicationContext& application, const HICON mainIcon, const HICON smallIcon, const HCURSOR cursor, const Math::ColorRGB<std::uint8_t>& backgroundColor) :
		application{&application},
		moduleHandle(File::Windows::GetModule())
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating background brush... Color: '{}'.", backgroundColor);
		const HBRUSH backgroundBrush = CreateSolidBrush(RGB(backgroundColor.R(), backgroundColor.G(), backgroundColor.B()));
		if (!backgroundBrush) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to create background brush. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating background brush done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(backgroundBrush));

		const auto wc = WNDCLASSEXA
		{
			.cbSize = sizeof(WNDCLASSEXA),
			.style = CS_OWNDC,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = moduleHandle,
			.hIcon = mainIcon,
			.hCursor = cursor,
			.hbrBackground = backgroundBrush,
			.lpszMenuName = nullptr,
			.lpszClassName = "Pony Engine Class",
			.hIconSm = smallIcon
		};
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Registering window class... Class name: '{}'; Module: '0x{:X}'; Main icon: '0x{:X}'; Small icon: '0x{:X}'; Cursor: '0x{:X}'; Background brush: '0x{:X}'.",
			wc.lpszClassName, reinterpret_cast<std::uintptr_t>(wc.hInstance), reinterpret_cast<std::uintptr_t>(wc.hIcon), reinterpret_cast<std::uintptr_t>(wc.hIconSm),
			reinterpret_cast<std::uintptr_t>(wc.hCursor), reinterpret_cast<std::uintptr_t>(wc.hbrBackground));
		classHandle = RegisterClassExA(&wc);
		if (!classHandle) [[unlikely]]
		{
			if (!DeleteObject(backgroundBrush)) [[unlikely]]
			{
				PONY_LOG(this->application->Logger(), Log::LogType::Error, "Failed to delete background brush. Handle: '0x{:X}', Error code: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(backgroundBrush), GetLastError());
			}

			throw std::runtime_error(Text::FormatSafe("Failed to register class. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Registering window class done. Handle: '0x{:X}'.", classHandle);
	}

	WindowClass::~WindowClass() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering window class... Handle: '0x{:X}'.", classHandle);
		if (!UnregisterClassA(reinterpret_cast<LPCSTR>(classHandle), moduleHandle)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to unregister class. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering window class done.");
	}

	HMODULE WindowClass::ModuleHandle() const noexcept
	{
		return moduleHandle;
	}

	ATOM WindowClass::ClassHandle() noexcept
	{
		return classHandle;
	}
}
#endif
