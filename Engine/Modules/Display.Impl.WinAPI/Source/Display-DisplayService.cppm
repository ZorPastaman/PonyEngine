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

export module PonyEngine.Display.Impl.WinAPI:DisplayService;

import std;

import PonyEngine.Application;
import PonyEngine.Display;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Text.WinAPI;
import PonyEngine.Utility;

import :DisplayContainer;
import :DisplayState;

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

		[[nodiscard("Pure function")]]
		static std::size_t IndexOfSource(std::span<const DISPLAYCONFIG_PATH_INFO> paths, const DisplayID& displayID) noexcept;
		[[nodiscard("Pure function")]]
		static void GetDisplayName(std::wstring_view sourceName, std::string& name);

		/// @brief Checks if the display handle is invalid.
		/// @param handle Handle to check.
		/// @return @a True if it's invalid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsInvalid(DisplayHandle handle) const noexcept;
		/// @brief Create a new display handle.
		/// @return Display handle.
		[[nodiscard("Weird call")]]
		DisplayHandle CreateDisplayHandle();
		/// @brief Makes a new display handle.
		/// @return Display handle.
		[[nodiscard("Weird call")]]
		DisplayHandle MakeDisplayHandle();
		/// @brief Resurrects a display handle.
		/// @return Display handle.
		[[nodiscard("Weird call")]]
		DisplayHandle ResurrectDisplayHandle() noexcept;
		/// @brief Kills the display handle.
		/// @param handle Display handle to kill.
		void KillDisplayHandle(DisplayHandle handle) noexcept;

		Application::IApplication* application;
		Log::ILogService* logService;

		DisplayContainer displayContainer;

		std::vector<DisplayHandleVersion> displayHandleVersions; ///< Display handle versions.
		std::vector<DisplayHandleID> deadDisplayHandleIds; ///< Display handle IDs.
	};
}

namespace PonyEngine::Display
{
	DisplayService::DisplayService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
		UpdateDisplays();
	}

	DisplayService::~DisplayService() noexcept
	{
	}

	std::size_t DisplayService::DisplayCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return displayContainer.Size();
	}

	DisplayHandle DisplayService::Display(const std::size_t index) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const DisplayHandleID id = displayContainer.Handle(index);
		return DisplayHandle{.id = id, .version = displayHandleVersions[id]};
	}

	bool DisplayService::IsValid(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return !IsInvalid(displayHandle);
	}

	bool DisplayService::IsConnected(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(displayHandle) && "Invalid display handle.");
		return displayContainer.State(displayContainer.IndexOf(displayHandle.id)).isConnected;
	}

	struct DisplayInfo DisplayService::DisplayInfo(const DisplayHandle displayHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(displayHandle) && "Invalid display handle.");

		const std::size_t index = displayContainer.IndexOf(displayHandle.id);
		const DisplayState& state = displayContainer.State(index);

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

	void DisplayService::UpdateDisplays() noexcept
	{
		try
		{
			const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(1024uz);
			const auto [displayPaths, displayModes] = GetDisplayPaths(*buffer);
			UpdateDisplayConnections(displayPaths);
			UpdateDisplayInfos(displayPaths, displayModes);
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
				std::size_t index = displayContainer.IndexOf(displayId);
				if (index >= displayContainer.Size())
				{
					const DisplayHandle handle = CreateDisplayHandle();
					index = displayContainer.Add(handle.id, displayId, DisplayState{.isConnected = true});
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

	bool DisplayService::IsInvalid(const DisplayHandle handle) const noexcept
	{
		return Math::IsEven(handle.version) || handle.id >= displayHandleVersions.size() || displayHandleVersions[handle.id] != handle.version;
	}

	DisplayHandle DisplayService::CreateDisplayHandle()
	{
		return deadDisplayHandleIds.empty() ? MakeDisplayHandle() : ResurrectDisplayHandle();
	}

	DisplayHandle DisplayService::MakeDisplayHandle()
	{
		if (displayHandleVersions.size() >= std::numeric_limits<DisplayHandleID>::max()) [[unlikely]]
		{
			throw std::overflow_error("No more display handles available");
		}

		const DisplayHandleID handleId = static_cast<DisplayHandleID>(displayHandleVersions.size());

		constexpr DisplayHandleVersion handleVersion = 1u;
		displayHandleVersions.push_back(handleVersion);

		return DisplayHandle{.id = handleId, .version = handleVersion};
	}

	DisplayHandle DisplayService::ResurrectDisplayHandle() noexcept
	{
		const DisplayHandleID handleId = deadDisplayHandleIds.back();
		deadDisplayHandleIds.pop_back();

		const DisplayHandleVersion handleVersion = ++displayHandleVersions[handleId];

		return DisplayHandle{.id = handleId, .version = handleVersion};
	}

	void DisplayService::KillDisplayHandle(const DisplayHandle handle) noexcept
	{
		try
		{
			++displayHandleVersions[handle.id];
			deadDisplayHandleIds.push_back(handle.id);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On killing display handle. HandleID: '0x{:X}'.", handle.id);
			// Just forget about this handle.
		}
	}
}
