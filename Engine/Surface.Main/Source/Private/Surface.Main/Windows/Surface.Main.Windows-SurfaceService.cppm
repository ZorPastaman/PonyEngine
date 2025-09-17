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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Surface.Main.Windows:SurfaceService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Surface.Main;
import PonyEngine.Surface.Windows;
import PonyEngine.Utility;

import :MessageHandler;
import :WindowClass;

export namespace PonyEngine::Surface::Windows
{
	class SurfaceService final : public Application::ITickableService, private ISurfaceService, private IMessageHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, std::string_view title, const WindowRect& rect, SurfaceStyle style);
		SurfaceService(const SurfaceService&) = delete;
		SurfaceService(SurfaceService&&) = delete;

		~SurfaceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		ISurfaceService& PublicSurfaceService() noexcept;
		[[nodiscard("Pure function")]]
		const ISurfaceService& PublicSurfaceService() const noexcept;

		SurfaceService& operator =(const SurfaceService&) = delete;
		SurfaceService& operator =(SurfaceService&&) = delete;

	private:
		static constexpr auto MinimalWindowSize = Math::Vector2<int>(640, 480);

		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const override;
		virtual void Title(std::string_view title) override;

		[[nodiscard("Pure function")]]
		virtual WindowRect Rect(const RectRequest& request) const override;
		virtual void Rect(const WindowRect& rect) override;

		[[nodiscard("Pure function")]]
		virtual SurfaceStyle Style() const override;
		virtual void Style(SurfaceStyle style) override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const override;

		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept override;

		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) override;
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept override;

		virtual void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) override;
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) noexcept override;

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		[[nodiscard("Pure function")]]
		static WindowRect CalculateRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, const RectRequest& request);
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> CalculateRect(const WindowRect& rect, DWORD style, DWORD styleEx);
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> GetResolution();

		[[nodiscard("Pure function")]]
		std::pair<DWORD, DWORD> GetStyle() const;
		void SetStyle(DWORD style, DWORD styleEx);

		void RegisterRawInputType(USHORT usagePage, USHORT usage);
		void UnregisterRawInputType(USHORT usagePage, USHORT usage);
		void RegisterRawInputType(USHORT usagePage, USHORT usage, DWORD flags);

		void ObserveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
		void ObserveRawInput(LPARAM lParam) noexcept;

		[[nodiscard("Pure function")]]
		static DWORD GetHidType(const RAWINPUT& input);

		[[nodiscard("Pure function")]]
		static constexpr DWORD Pack(USHORT first, USHORT second) noexcept;
		[[nodiscard("Pure function")]]
		static constexpr std::pair<USHORT, USHORT> Unpack(DWORD value) noexcept;

		Application::IApplicationContext* application;

		std::shared_ptr<WindowClass> windowClass;

		HWND windowHandle;

		std::unordered_map<UINT, std::vector<IMessageObserver*>> messageObservers;
		std::unordered_map<DWORD, std::vector<IRawInputObserver*>> rawInputObservers;

		mutable std::string titleCache;
		std::vector<BYTE> rawInputCache;
	};
}

namespace PonyEngine::Surface::Windows
{
	SurfaceService::SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, 
		const std::string_view title, const WindowRect& rect, const SurfaceStyle style) :
		application{&application},
		windowClass(windowClass)
	{
		assert(this->windowClass && "The window class is nullptr!");

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Calculating window rect.");
		const DWORD usualStyle = ConvertToWindowsStyle(style);
		const DWORD exStyle = ConvertToWindowsStyleEx(style) | WS_EX_APPWINDOW;
		const auto [position, size] = CalculateRect(rect, usualStyle, exStyle);

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window... Window class: '0x{:X}'; Title: '{}'; Position: '{}'; Size: '{}'; Style: {}.", 
			windowClass->ClassHandle(), title, position, size, style);
		windowHandle = CreateWindowExA(
			exStyle,
			reinterpret_cast<LPCSTR>(this->windowClass->ClassHandle()),
			title.data(),
			usualStyle,
			position.X(),
			position.Y(),
			size.X(),
			size.Y(),
			nullptr,
			nullptr,
			windowClass->ModuleHandle(),
			static_cast<IMessageHandler*>(this)
		);
		if (!windowHandle) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window done. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Show window.");
		ShowWindow(windowHandle, SW_NORMAL);
	}

	SurfaceService::~SurfaceService() noexcept
	{
		if (IsWindow(windowHandle))
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying window... Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
			if (!DestroyWindow(windowHandle)) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Error on destroying window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying window done.");
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Skip destroying window 'cause it's already been destroyed.");
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing window class.");
		windowClass.reset();
	}

	void SurfaceService::Begin()
	{
	}

	void SurfaceService::End()
	{
	}

	void SurfaceService::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Peeking messages.");
		MSG message;
		while (PeekMessageA(&message, windowHandle, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	ISurfaceService& SurfaceService::PublicSurfaceService() noexcept
	{
		return *this;
	}

	const ISurfaceService& SurfaceService::PublicSurfaceService() const noexcept
	{
		return *this;
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenResolution() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(GetResolution());
	}

	std::string_view SurfaceService::Title() const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return std::string_view();
		}

		SetLastError(DWORD{0});
		const int length = GetWindowTextLengthA(windowHandle);
		if (!length) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get window title length. Error code: '0x{:X}'.", errorCode));
			}

			return std::string_view();
		}

		titleCache.clear();
		titleCache.reserve(length + 1);
		const int copied = GetWindowTextA(windowHandle, titleCache.data(), length + 1);
		if (!copied) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get window title. Error code: '0x{:X}'.", GetLastError()));
		}
		titleCache.resize(copied);

		return titleCache;
	}

	void SurfaceService::Title(const std::string_view title)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		if (!SetWindowTextA(windowHandle, title.data())) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set window title. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	WindowRect SurfaceService::Rect(const RectRequest& request) const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			WindowRect windowRect;
			if (request.relativePosition)
			{
				windowRect.position = Math::Vector2<float>::Zero();
			}
			else
			{
				windowRect.position = Math::Vector2<std::int32_t>::Zero();
			}
			if (request.relativeSize)
			{
				windowRect.size = AbsoluteToRelative(static_cast<Math::Vector2<std::int32_t>>(MinimalWindowSize), ScreenResolution());
			}
			else
			{
				windowRect.size = static_cast<Math::Vector2<std::int32_t>>(MinimalWindowSize);
			}
			windowRect.positionMode = request.positionMode;

			return windowRect;
		}

		RECT rect;
		if (!GetClientRect(windowHandle, &rect)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get window rect. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto position = Math::Vector2<int>(static_cast<int>(rect.left), static_cast<int>(rect.top));
		const auto size = Math::Vector2<int>(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));

		return CalculateRect(position, size, request);
	}

	void SurfaceService::Rect(const WindowRect& rect)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		const auto [style, styleEx] = GetStyle();
		const auto [position, size] = CalculateRect(rect, style, styleEx);
		if (!SetWindowPos(windowHandle, nullptr, position.X(), position.Y(), size.X(), size.Y(), SWP_NOZORDER)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set window rect. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	SurfaceStyle SurfaceService::Style() const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return SurfaceStyle::None;
		}

		const auto [style, styleEx] = GetStyle();
		return ConvertToSurfaceStyle(style) | ConvertExToSurfaceStyle(styleEx);
	}

	void SurfaceService::Style(const SurfaceStyle style)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		SetStyle(ConvertToWindowsStyle(style), ConvertToWindowsStyleEx(style) | WS_EX_APPWINDOW);
	}

	Math::Vector2<std::int32_t> SurfaceService::ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return Math::Vector2<std::int32_t>::Zero();
		}

		auto screenPoint = POINT{.x = static_cast<LONG>(clientPoint.X()), .y = static_cast<LONG>(clientPoint.Y())};
		if (!::ClientToScreen(windowHandle, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(screenPoint.x), static_cast<std::int32_t>(screenPoint.y));
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return Math::Vector2<std::int32_t>::Zero();
		}

		auto clientPoint = POINT{.x = static_cast<LONG>(screenPoint.X()), .y = static_cast<LONG>(screenPoint.Y())};
		if (!::ScreenToClient(windowHandle, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(clientPoint.x), static_cast<std::int32_t>(clientPoint.y));
	}

	Math::Vector2<std::int32_t> SurfaceService::MinimalSize() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(MinimalWindowSize);
	}

	HWND SurfaceService::Handle() noexcept
	{
		return windowHandle;
	}

	void SurfaceService::AddMessageObserver(IMessageObserver& observer, const UINT messageType)
	{
		std::vector<IMessageObserver*>& observers = messageObservers[messageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The observer has already been added.");
		observers.push_back(&observer);
	}

	void SurfaceService::AddMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (std::size_t i = 0uz; i < messageTypes.size(); ++i)
		{
			try
			{
				AddMessageObserver(observer, messageTypes[i]);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveMessageObserver(observer, messageTypes[i]);
				}

				throw;
			}
		}
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer, const UINT messageType) noexcept
	{
		if (const auto position = messageObservers.find(messageType); position != messageObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of '{}' message type but it hadn't been added.", messageType);
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes) noexcept
	{
		for (const UINT messageType : messageTypes)
		{
			RemoveMessageObserver(observer, messageType);
		}
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (std::vector<IMessageObserver*>& observers : std::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove message observer but it hadn't been added.");
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		const DWORD usageType = Pack(usagePage, usage);
		const auto typePosition = rawInputObservers.find(usageType);
		std::vector<IRawInputObserver*>& observers = typePosition != rawInputObservers.cend() ? typePosition->second : rawInputObservers[usageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The raw input observer has already been added.");
		observers.push_back(&observer);

		if (observers.size() == 1uz)
		{
			try
			{
				RegisterRawInputType(usagePage, usage);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On registering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
				observers.pop_back();

				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on registering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
				observers.pop_back();

				throw;
			}
		}
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages)
	{
		for (std::size_t i = 0uz; i < rawInputUsages.size(); ++i)
		{
			try
			{
				AddRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
				}

				throw;
			}
		}
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage) noexcept
	{
		const DWORD usageType = Pack(usagePage, usage);
		if (const auto position = rawInputObservers.find(usageType); position != rawInputObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				if (position->second.empty())
				{
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(application->Logger(), e, "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG_E(application->Logger(), Log::LogType::Exception, "Unknown exception on unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}

				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of raw input type but it hadn't been added. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept
	{
		for (const auto [usagePage, usage] : rawInputUsages)
		{
			RemoveRawInputObserver(observer, usagePage, usage);
		}
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (auto& [type, observers] : rawInputObservers)
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;

				if (observers.empty())
				{
					const auto [usagePage, usage] = Unpack(type);
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(application->Logger(), e, "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG_E(application->Logger(), Log::LogType::Exception, "Unknown exception on unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer but it hadn't been added.");
	}

	LRESULT SurfaceService::HandleMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Received '{}' command.", uMsg);

		ObserveMessage(uMsg, wParam, lParam);

		switch (uMsg)
		{
		case WM_INPUT:
			ObserveRawInput(lParam);
			break;
		default:
			break;
		}

		return DefWindowProcA(windowHandle, uMsg, wParam, lParam);
	}

	WindowRect SurfaceService::CalculateRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, const RectRequest& request)
	{
		const auto resolution = static_cast<Math::Vector2<std::int32_t>>(GetResolution());
		const Math::Vector2<std::int32_t> delta = CalculateDelta(position, size, resolution, request.positionMode);

		WindowRect answer;
		if (request.relativePosition)
		{
			answer.position = AbsoluteToRelative(delta, resolution);
		}
		else
		{
			answer.position = delta;
		}
		if (request.relativeSize)
		{
			answer.size = AbsoluteToRelative(size, resolution);
		}
		else
		{
			answer.size = size;
		}
		answer.positionMode = request.positionMode;

		return answer;
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::CalculateRect(const WindowRect& rect, const DWORD style, const DWORD styleEx)
	{
		const auto resolution = static_cast<Math::Vector2<std::int32_t>>(GetResolution());
		const Math::Vector2<std::int32_t> delta = rect.position.index() ? std::get<1>(rect.position) : RelativeToAbsolute(std::get<0>(rect.position), resolution);
		const Math::Vector2<std::int32_t> size = rect.size.index() ? std::get<1>(rect.size) : RelativeToAbsolute(std::get<0>(rect.size), resolution);
		const Math::Vector2<std::int32_t> position = CalculatePosition(delta, size, resolution, rect.positionMode);

		auto windowRect = RECT
		{
			.left = static_cast<LONG>(position.X()),
			.top = static_cast<LONG>(position.Y()),
			.right = static_cast<LONG>(position.X() + size.X()),
			.bottom = static_cast<LONG>(position.Y() + size.Y())
		};
		if (!AdjustWindowRectEx(&windowRect, style, false, styleEx)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::pair(
			Math::Vector2<int>(static_cast<int>(windowRect.left), static_cast<int>(windowRect.top)), 
			Math::Vector2<int>(static_cast<int>(windowRect.right - windowRect.left), static_cast<int>(windowRect.bottom - windowRect.top))
		);
	}

	Math::Vector2<int> SurfaceService::GetResolution()
	{
		Math::Vector2<int> resolution;
		resolution.X() = GetSystemMetrics(SM_CXSCREEN);
		resolution.Y() = GetSystemMetrics(SM_CYSCREEN);
		if (!resolution.X() || !resolution.Y()) [[unlikely]]
		{
			throw std::runtime_error("Failed to get screen resolution.");
		}

		return resolution;
	}

	std::pair<DWORD, DWORD> SurfaceService::GetStyle() const
	{
		SetLastError(DWORD{0});

		const auto style = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_STYLE));
		if (!style) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get window style. Error code: '0x{:X}'.", error));
			}
		}

		const auto styleEx = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_EXSTYLE));
		if (!styleEx) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get extended window style. Error code: '0x{:X}'.", error));
			}
		}

		return std::pair(style, styleEx);
	}

	void SurfaceService::SetStyle(const DWORD style, const DWORD styleEx)
	{
		SetLastError(DWORD{0});

		if (!SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(style))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to set window style. Error code: '0x{:X}'.", error));
			}
		}

		if (!SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(styleEx))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to set extended window style. Error code: '0x{:X}'.", error));
			}
		}
	}

	void SurfaceService::RegisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		RegisterRawInputType(usagePage, usage, DWORD{0});
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Raw input type registered. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::UnregisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		RegisterRawInputType(usagePage, usage, RIDEV_REMOVE);
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Raw input type unregistered. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::RegisterRawInputType(const USHORT usagePage, const USHORT usage, const DWORD flags)
	{
		const auto rid = RAWINPUTDEVICE
		{
			.usUsagePage = usagePage,
			.usUsage = usage,
			.dwFlags = flags,
			.hwndTarget = windowHandle
		};

		if (!RegisterRawInputDevices(&rid, 1u, sizeof(rid))) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to register raw input device. Usage page: '0x{:X}'; Usage: '0x{:X}'; Flags: '0x{:X}'; Window handle: '0x{:X}'. Error code: '0x{:X}'.", rid.usUsagePage, rid.usUsage, rid.dwFlags, reinterpret_cast<std::uintptr_t>(rid.hwndTarget), GetLastError()));
		}
	}

	void SurfaceService::ObserveMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}
	}

	void SurfaceService::ObserveRawInput(const LPARAM lParam) noexcept
	{
		const auto hRawInput = reinterpret_cast<HRAWINPUT>(lParam);

		UINT size = 0u;
		if (GetRawInputData(hRawInput, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER))) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());
			return;
		}
		if (size < 1u) [[unlikely]]
		{
			return;
		}

		try
		{
			rawInputCache.resize(size);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On resizing raw input cache.");
			return;
		}
		if (GetRawInputData(hRawInput, RID_INPUT, rawInputCache.data(), &size, sizeof(RAWINPUTHEADER)) != rawInputCache.size()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());
			return;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(rawInputCache.data());

		DWORD usageType;
		switch (input->header.dwType)
		{
		case RIM_TYPEMOUSE:
			usageType = Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
			break;
		case RIM_TYPEKEYBOARD:
			usageType = Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
			break;
		case RIM_TYPEHID:
			try
			{
				usageType = GetHidType(*input);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On getting hid type.");
				return;
			}
			break;
		default: [[unlikely]]
			PONY_LOG(application->Logger(), Log::LogType::Error, "Unexpected raw input type.");
			return;
		}

		if (const auto observerPosition = rawInputObservers.find(usageType); observerPosition != rawInputObservers.cend())
		{
			for (IRawInputObserver* const observer : observerPosition->second)
			{
				try
				{
					observer->Observe(*input);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' raw input observer.", typeid(*observer).name());
				}
				catch (...)
				{
					PONY_LOG(application->Logger(), Log::LogType::Error, "Unknown exception on calling '{}' raw input observer.", typeid(*observer).name());
				}
			}
		}
	}

	DWORD SurfaceService::GetHidType(const RAWINPUT& input)
	{
		auto info = RID_DEVICE_INFO{.cbSize = sizeof(RID_DEVICE_INFO)};
		UINT size = sizeof(info);
		if (!GetRawInputDeviceInfoA(input.header.hDevice, RIDI_DEVICEINFO, &info, &size)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get hid device info. Error code: '0x{:X}'.", GetLastError()));
		}

		if (info.dwType != RIM_TYPEHID) [[unlikely]]
		{
			throw std::runtime_error("Wrong hid device!");
		}

		return Pack(info.hid.usUsagePage, info.hid.usUsage);
	}

	constexpr DWORD SurfaceService::Pack(const USHORT first, const USHORT second) noexcept
	{
		return static_cast<DWORD>(first) << 16 | second;
	}

	constexpr std::pair<USHORT, USHORT> SurfaceService::Unpack(const DWORD value) noexcept
	{
		return std::pair(static_cast<USHORT>(value >> 16), static_cast<USHORT>(value));
	}
}
