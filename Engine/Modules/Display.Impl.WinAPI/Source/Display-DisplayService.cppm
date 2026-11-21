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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef CreateWindow

export module PonyEngine.Display.Impl.WinAPI:DisplayService;

import std;

import PonyEngine.Application;
import PonyEngine.Display;
import PonyEngine.FileSystem.WinAPI;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Text.WinAPI;
import PonyEngine.Utility;

import :DisplayContainer;
import :DisplayState;
import :Window;

export namespace PonyEngine::Display
{
	class DisplayService final : public IDisplayService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DisplayService(Application::IApplication& application);
		DisplayService(const DisplayService&) = delete;
		DisplayService(DisplayService&&) = delete;

		~DisplayService() noexcept;

		[[nodiscard("Pure function")]] 
		virtual std::size_t DisplayCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual DisplayHandle Display(std::size_t index) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(DisplayHandle displayHandle) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DisplayHandle displayHandle) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual struct DisplayInfo DisplayInfo(DisplayHandle displayHandle) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual struct WindowSupport WindowSupport() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IWindow> CreateWindow(const WindowParams& params) override;

		virtual void AddObserver(IDisplayObserver& observer) override;
		virtual void RemoveObserver(IDisplayObserver& observer) override;

		DisplayService& operator =(const DisplayService&) = delete;
		DisplayService& operator =(DisplayService&&) = delete;

	private:
		void UpdateDisplays() noexcept;
		[[nodiscard("Pure function")]]
		static std::pair<std::span<const DISPLAYCONFIG_PATH_INFO>, std::span<const DISPLAYCONFIG_MODE_INFO>> GetDisplayPaths(Application::IBuffer& buffer);
		void UpdateDisplayConnections(std::span<const DISPLAYCONFIG_PATH_INFO> displayPaths) noexcept;
		void UpdateDisplayInfos(std::span<const DISPLAYCONFIG_PATH_INFO> displayPaths, std::span<const DISPLAYCONFIG_MODE_INFO> displayModes) noexcept;
		void FillDisplayState(const DISPLAYCONFIG_PATH_INFO& displayPath, std::span<const DISPLAYCONFIG_MODE_INFO> displayModes, DisplayState& displayState) const noexcept;
		static void FillDisplayStateWithGeneralInfo(const DISPLAYCONFIG_PATH_INFO& displayPath, std::span<const DISPLAYCONFIG_MODE_INFO> displayModes, 
			DisplayState& displayState) noexcept;
		void FillDisplayStateWithSourceName(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept;
		void FillDisplayStateWithTargetName(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept;
		void FillDisplayStateWithColorInfo(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept;
		void FillDisplayStateWithSDRWhiteLevel(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept;
		void ObserveDisplays() const noexcept;

		[[nodiscard("Pure function")]]
		static std::size_t IndexOfSource(std::span<const DISPLAYCONFIG_PATH_INFO> paths, const DisplayID& displayID) noexcept;
		[[nodiscard("Pure function")]]
		static void GetDisplayName(std::wstring_view sourceName, std::string& name);

		[[nodiscard("Must be returned to system")]]
		static LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObserveDisplayChange(WPARAM wParam, LPARAM lParam) noexcept;

		Application::IApplication* application;
		Log::ILogService* logService;

		DisplayContainer displayContainer;

		HMODULE moduleHandle; ///< Module instance handle.
		ATOM messageClass; /// Message class handle.
		ATOM windowClass; ///< Window class handle.
		HWND messageWindow; ///< Message window.

		std::vector<IDisplayObserver*> observers;

#ifndef NDEBUG
		std::atomic_size_t windowCount;
#endif
	};
}

namespace PonyEngine::Display
{
	DisplayService::DisplayService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		moduleHandle{FileSystem::GetModule()}
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const auto messageClassDesc = WNDCLASSEXA
		{
			.cbSize = sizeof(WNDCLASSEXA),
			.style = 0u,
			.lpfnWndProc = &MessageProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = moduleHandle,
			.hIcon = nullptr,
			.hCursor = nullptr,
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = "PonyEngineDisplayMessage",
			.hIconSm = nullptr
		};
		messageClass = RegisterClassExA(&messageClassDesc);
		if (!messageClass) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to register message class: ErrorCode = '0x{:X}'", GetLastError()));
		}
		const auto messageClassScopeGuard = Utility::ScopeGuard([&]() noexcept
		{
			if (!UnregisterClassA(reinterpret_cast<LPCSTR>(messageClass), moduleHandle)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to unregister message class on constructor failure. Error code: '0x{:X}'.", GetLastError());
			}
		}, scopeGuardFlag);
		messageWindow = CreateWindowExA(0, reinterpret_cast<LPCSTR>(messageClass), "PonyEngineDisplayMessage", 0, 0, 0, 0, 0, nullptr, nullptr, moduleHandle, this);
		if (!messageWindow) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create message window: Error code = '0x{:X}'", GetLastError()));
		}
		const auto messageWindowScopeGuard = Utility::ScopeGuard([&]() noexcept
		{
			if (!DestroyWindow(messageWindow)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to destroy message window on constructor failure. Error code: '0x{:X}'.", GetLastError());
			}
		}, scopeGuardFlag);

		const auto windowClassDesc = Window::MakeWindowClassDesc(moduleHandle);
		windowClass = RegisterClassExA(&windowClassDesc);
		if (!windowClass) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to register window class: ErrorCode = '0x{:X}'", GetLastError()));
		}

		UpdateDisplays();

		scopeGuardFlag.Release();
	}

	DisplayService::~DisplayService() noexcept
	{
#ifndef NDEBUG
		assert(windowCount.load(std::memory_order::relaxed) == 0uz && "Some windows weren't destroyed.");
#endif
		assert(observers.empty() && "Some display observers weren't removed.");

		if (!UnregisterClassA(reinterpret_cast<LPCSTR>(windowClass), moduleHandle)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to unregister window class. Error code: '0x{:X}'.", GetLastError());
		}

		if (!DestroyWindow(messageWindow)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to destroy message window. Error code: '0x{:X}'.", GetLastError());
		}
		if (!UnregisterClassA(reinterpret_cast<LPCSTR>(messageClass), moduleHandle)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to unregister message class. Error code: '0x{:X}'.", GetLastError());
		}
	}

	std::size_t DisplayService::DisplayCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return displayContainer.Size();
	}

	DisplayHandle DisplayService::Display(const std::size_t index) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(index < displayContainer.Size() && "Out of range.");
		return DisplayHandle{.id = static_cast<DisplayHandleID>(index), .version = 1u};
	}

	bool DisplayService::IsValid(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return displayHandle.id < displayContainer.Size() && displayHandle.version == 1u;
	}

	bool DisplayService::IsConnected(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(displayHandle.id < displayContainer.Size() && displayHandle.version == 1u && "Invalid display handle.");
		return displayContainer.State(displayHandle.id).isConnected;
	}

	struct DisplayInfo DisplayService::DisplayInfo(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(displayHandle.id < displayContainer.Size() && displayHandle.version == 1u && "Invalid display handle.");

		const DisplayState& state = displayContainer.State(displayHandle.id);
		return Display::DisplayInfo
		{
			.sourceName = state.sourceName,
			.targetName = state.targetName,
			.friendlyTargetName = state.friendlyTargetName,
			.resolution = state.resolution,
			.refreshRate = state.refreshRate,
			.sdrWhiteLevel = state.sdrWhiteLevel,
			.colorMode = state.colorMode,
			.bitsPerColorChannel = state.bitsPerColorChannel,
		};
	}

	struct WindowSupport DisplayService::WindowSupport() const noexcept
	{
		constexpr auto commonFeatures = CommonWindowFeature::ModeSwitchable | CommonWindowFeature::Title | CommonWindowFeature::Icon | CommonWindowFeature::Hidable;
		constexpr auto fullscreenFeatures = FullscreenWindowFeature::MultiWindowPerDisplay | FullscreenWindowFeature::MultiDisplayWindow | FullscreenWindowFeature::Changeable;
		constexpr auto windowedFeatures = WindowedWindowFeature::Resizable | WindowedWindowFeature::ResizeLimits;

		return Display::WindowSupport
		{
			.commonFeatures = commonFeatures,
			.fullscreen = FullscreenWindowSupport
			{
				.features = fullscreenFeatures
			},
			.windowed = WindowedWindowSupport
			{
				.minSize = Window::MinWindowSize,
				.maxSize = Window::MaxWindowSize,
				.features = windowedFeatures
			}
		};
	}

	std::shared_ptr<IWindow> DisplayService::CreateWindow(const WindowParams& params)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

#ifndef NDEBUG
		const auto window = new Window(*application, displayContainer, windowClass, moduleHandle, params);
		windowCount.fetch_add(1uz, std::memory_order::relaxed);
		return std::shared_ptr<Window>(window, [this](const Window* const windowToDelete) noexcept
		{
			delete windowToDelete;
			windowCount.fetch_sub(1uz, std::memory_order::relaxed);
		});
#else
		return std::make_shared<Window>(*application, displayContainer, windowClass, moduleHandle, params);
#endif
	}

	void DisplayService::AddObserver(IDisplayObserver& observer)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		observers.push_back(&observer);
	}

	void DisplayService::RemoveObserver(IDisplayObserver& observer)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const auto position = std::ranges::find(observers, &observer);
		assert(position != observers.cend() && "Observer not found.");
		observers.erase(position);
	}

	void DisplayService::UpdateDisplays() noexcept
	{
		try
		{
			const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(1024uz);
			const auto [displayPaths, displayModes] = GetDisplayPaths(*buffer);
			UpdateDisplayConnections(displayPaths);
			UpdateDisplayInfos(displayPaths, displayModes);
			ObserveDisplays();
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On update displays.");
		}
	}

	std::pair<std::span<const DISPLAYCONFIG_PATH_INFO>, std::span<const DISPLAYCONFIG_MODE_INFO>> DisplayService::GetDisplayPaths(Application::IBuffer& buffer)
	{
		std::span<DISPLAYCONFIG_MODE_INFO> displayModes;
		std::span<DISPLAYCONFIG_PATH_INFO> displayPaths;

		LONG result;
		do
		{
			constexpr UINT32 flags = QDC_ONLY_ACTIVE_PATHS | QDC_VIRTUAL_MODE_AWARE | QDC_VIRTUAL_REFRESH_RATE_AWARE;
			UINT32 pathCount = 0u;
			UINT32 modeCount = 0u;

			result = GetDisplayConfigBufferSizes(flags, &pathCount, &modeCount);
			if (result != ERROR_SUCCESS) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to get display count: Result = '0x{:X}'", result));
			}

			const std::size_t bufferSize = Memory::CalculateBufferSize<DISPLAYCONFIG_MODE_INFO>(modeCount) +
				Memory::CalculateBufferSize<DISPLAYCONFIG_MODE_INFO, DISPLAYCONFIG_MODE_INFO>(pathCount);
			buffer.EnsureSize(bufferSize);
			auto arena = Memory::Arena(buffer.Span());
			displayModes = arena.AllocateArray<DISPLAYCONFIG_MODE_INFO>(modeCount);
			displayPaths = arena.AllocateArray<DISPLAYCONFIG_PATH_INFO>(pathCount);

			result = QueryDisplayConfig(flags, &pathCount, displayPaths.data(), &modeCount, displayModes.data(), nullptr);

			displayModes = displayModes.subspan(0uz, modeCount);
			displayPaths = displayPaths.subspan(0uz, pathCount);
		} while (result == ERROR_INSUFFICIENT_BUFFER);
		if (result != ERROR_SUCCESS) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get display infos: Result = '0x{:X}'", result));
		}

		return std::pair(displayPaths, displayModes);
	}

	void DisplayService::UpdateDisplayConnections(const std::span<const DISPLAYCONFIG_PATH_INFO> displayPaths) noexcept
	{
		for (std::size_t i = 0uz; i < displayContainer.Size(); ++i)
		{
			const DisplayID& id = displayContainer.DisplayID(i);
			const std::size_t index = IndexOfSource(displayPaths, id);
			const bool isConnected = index < displayPaths.size();
			displayContainer.State(i).isConnected = isConnected;
		}
	}

	void DisplayService::UpdateDisplayInfos(const std::span<const DISPLAYCONFIG_PATH_INFO> displayPaths, const std::span<const DISPLAYCONFIG_MODE_INFO> displayModes) noexcept
	{
		for (std::size_t i = 0uz; i < displayPaths.size(); ++i)
		{
			const DISPLAYCONFIG_PATH_INFO& displayPath = displayPaths[i];
			const auto displayId = DisplayID{.adapterId = displayPath.sourceInfo.adapterId, .id = displayPath.sourceInfo.id};

			if (IndexOfSource(displayPaths, displayId) != i)
			{
				continue;
			}

			try
			{
				const std::size_t index = displayContainer.IndexOf(displayId);
				if (index >= displayContainer.Size())
				{
					if (index >= std::numeric_limits<DisplayHandleID>::max()) [[unlikely]]
					{
						throw std::overflow_error("No more display handles available");
					}

					displayContainer.Add(displayId, DisplayState{.isConnected = true});
				}

				FillDisplayState(displayPath, displayModes, displayContainer.State(index));
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On updating display info.");
			}
		}
	}

	void DisplayService::FillDisplayState(const DISPLAYCONFIG_PATH_INFO& displayPath, const std::span<const DISPLAYCONFIG_MODE_INFO> displayModes,
		DisplayState& displayState) const noexcept
	{
		FillDisplayStateWithGeneralInfo(displayPath, displayModes, displayState);
		FillDisplayStateWithSourceName(displayPath, displayState);
		FillDisplayStateWithTargetName(displayPath, displayState);
		FillDisplayStateWithColorInfo(displayPath, displayState);
		FillDisplayStateWithSDRWhiteLevel(displayPath, displayState);
	}

	void DisplayService::FillDisplayStateWithGeneralInfo(const DISPLAYCONFIG_PATH_INFO& displayPath, const std::span<const DISPLAYCONFIG_MODE_INFO> displayModes, 
		DisplayState& displayState) noexcept
	{
		const bool virtualMode = displayPath.flags & DISPLAYCONFIG_PATH_SUPPORT_VIRTUAL_MODE;
		const UINT32 sourceModeIndex = virtualMode ? displayPath.sourceInfo.sourceModeInfoIdx : displayPath.sourceInfo.modeInfoIdx;
		const UINT32 targetModeIndex = virtualMode ? displayPath.targetInfo.targetModeInfoIdx : displayPath.targetInfo.modeInfoIdx;
		const DISPLAYCONFIG_SOURCE_MODE& sourceMode = displayModes[sourceModeIndex].sourceMode;
		const DISPLAYCONFIG_TARGET_MODE& targetMode = displayModes[targetModeIndex].targetMode;

		displayState.resolution = Math::Vector2<std::uint32_t>(sourceMode.width, sourceMode.height);
		displayState.refreshRate = Math::Rational<std::uint32_t>(targetMode.targetVideoSignalInfo.vSyncFreq.Numerator, targetMode.targetVideoSignalInfo.vSyncFreq.Denominator);
		displayState.position = Math::Vector2<LONG>(sourceMode.position.x, sourceMode.position.y);
	}

	void DisplayService::FillDisplayStateWithSourceName(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept
	{
		auto sourceName = DISPLAYCONFIG_SOURCE_DEVICE_NAME{};
		sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
		sourceName.header.size = sizeof(sourceName);
		sourceName.header.adapterId = displayPath.sourceInfo.adapterId;
		sourceName.header.id = displayPath.sourceInfo.id;
		if (const LONG result = DisplayConfigGetDeviceInfo(&sourceName.header); result != ERROR_SUCCESS) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get display source name. Result: '0x{:X}'.", result);
			return;
		}

		try
		{
			GetDisplayName(sourceName.viewGdiDeviceName, displayState.sourceName);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On filling display state with source name.");
		}
	}

	void DisplayService::FillDisplayStateWithTargetName(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept
	{
		auto targetName = DISPLAYCONFIG_TARGET_DEVICE_NAME{};
		targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
		targetName.header.size = sizeof(targetName);
		targetName.header.adapterId = displayPath.targetInfo.adapterId;
		targetName.header.id = displayPath.targetInfo.id;
		if (const LONG result = DisplayConfigGetDeviceInfo(&targetName.header); result != ERROR_SUCCESS) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get display target name. Result: '0x{:X}'.", result);
			return;
		}

		try
		{
			GetDisplayName(targetName.monitorDevicePath, displayState.targetName);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On filling display state with target name.");
		}
		try
		{
			GetDisplayName(targetName.monitorFriendlyDeviceName, displayState.friendlyTargetName);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On filling display state with friendly target name.");
		}
	}

	void DisplayService::FillDisplayStateWithColorInfo(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept
	{
		auto colorInfo = DISPLAYCONFIG_GET_ADVANCED_COLOR_INFO_2{};
		colorInfo.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO_2;
		colorInfo.header.size = sizeof(colorInfo);
		colorInfo.header.adapterId = displayPath.targetInfo.adapterId;
		colorInfo.header.id = displayPath.targetInfo.id;
		if (const LONG result = DisplayConfigGetDeviceInfo(&colorInfo.header); result != ERROR_SUCCESS) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get display color info. Result: '0x{:X}'.", result);
			return;
		}

		switch (colorInfo.activeColorMode)
		{
		case DISPLAYCONFIG_ADVANCED_COLOR_MODE_SDR:
			displayState.colorMode = ColorMode::SDR;
			break;
		case DISPLAYCONFIG_ADVANCED_COLOR_MODE_WCG:
			displayState.colorMode = ColorMode::WCG;
			break;
		case DISPLAYCONFIG_ADVANCED_COLOR_MODE_HDR:
			displayState.colorMode = ColorMode::HDR;
			break;
		}

		displayState.bitsPerColorChannel = static_cast<std::uint8_t>(colorInfo.bitsPerColorChannel);
	}

	void DisplayService::FillDisplayStateWithSDRWhiteLevel(const DISPLAYCONFIG_PATH_INFO& displayPath, DisplayState& displayState) const noexcept
	{
		auto whiteInfo = DISPLAYCONFIG_SDR_WHITE_LEVEL{};
		whiteInfo.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
		whiteInfo.header.size = sizeof(whiteInfo);
		whiteInfo.header.adapterId = displayPath.targetInfo.adapterId;
		whiteInfo.header.id = displayPath.targetInfo.id;
		if (const LONG result = DisplayConfigGetDeviceInfo(&whiteInfo.header); result != ERROR_SUCCESS) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get display SDR white level. Result: '0x{:X}'.", result);
			return;
		}

		displayState.sdrWhiteLevel = static_cast<float>(whiteInfo.SDRWhiteLevel) / 1000.f * 80.f;
	}

	void DisplayService::ObserveDisplays() const noexcept
	{
		for (IDisplayObserver* const observer : observers)
		{
			try
			{
				observer->OnDisplayChanged();
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' on display change.", typeid(*observer).name());
			}
		}
	}

	std::size_t DisplayService::IndexOfSource(const std::span<const DISPLAYCONFIG_PATH_INFO> paths, const DisplayID& displayID) noexcept
	{
		for (std::size_t i = 0uz; i < paths.size(); ++i)
		{
			const DISPLAYCONFIG_PATH_INFO& path = paths[i];
			if (const auto id = DisplayID{.adapterId = path.sourceInfo.adapterId, .id = path.sourceInfo.id}; id == displayID)
			{
				return i;
			}
		}

		return paths.size();
	}

	void DisplayService::GetDisplayName(const std::wstring_view sourceName, std::string& name)
	{
		std::size_t nameSize = Text::GetStringSize(sourceName);
		name.resize(nameSize);
		nameSize = Text::ConvertToString(sourceName, name);
		name.resize(nameSize);
	}

	LRESULT DisplayService::MessageProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (msg == WM_CREATE) [[unlikely]]
		{
			const auto displayService = static_cast<DisplayService*>(reinterpret_cast<CREATESTRUCTA*>(lParam)->lpCreateParams);
			SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(displayService));
			return 0;
		}

		if (const auto displayService = reinterpret_cast<DisplayService*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA))) [[likely]]
		{
			switch (msg)
			{
			case WM_DISPLAYCHANGE:
				return displayService->ObserveDisplayChange(wParam, lParam);
			default:
				break;
			}
		}

		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}

	LRESULT DisplayService::ObserveDisplayChange(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		UpdateDisplays();
		return 0;
	}
}
