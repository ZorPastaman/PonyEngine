/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Display.Impl.WinAPI:DisplayService;

import std;

import PonyEngine.Application;
import PonyEngine.Display;

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
	};
}

namespace PonyEngine::Display
{
	DisplayService::DisplayService(Application::IApplication& application)
	{
		UINT32 pathCount = 0;
		UINT32 modeCount = 0;
		if (const LONG result = GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount); result != ERROR_SUCCESS) [[unlikely]]
		{
			throw std::runtime_error("Failed to get display count");
		}

		std::vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
		std::vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);
		if (const LONG result = QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount,paths.data(), &modeCount, modes.data(), nullptr); result != ERROR_SUCCESS) [[unlikely]]
		{
			throw std::runtime_error("Failed to get display infos");
		}

		for (const DISPLAYCONFIG_PATH_INFO& path : std::span(paths).subspan(0uz, pathCount))
		{
			const UINT32 modeIndex = path.targetInfo.modeInfoIdx;
			if (modeIndex == DISPLAYCONFIG_PATH_MODE_IDX_INVALID)
			{
				continue;
			}

			const DISPLAYCONFIG_MODE_INFO& mode = modes[modeIndex];
			if (mode.infoType != DISPLAYCONFIG_MODE_INFO_TYPE_TARGET)
			{
				continue;
			}

			const DISPLAYCONFIG_VIDEO_SIGNAL_INFO& signal = mode.targetMode.targetVideoSignalInfo;

			const std::uint32_t width = signal.activeSize.cx;
			const std::uint32_t height = signal.activeSize.cy;

			const std::uint32_t refreshNumerator = signal.vSyncFreq.Numerator;
			const std::uint32_t refreshDenominator = signal.vSyncFreq.Denominator;

			DISPLAYCONFIG_TARGET_DEVICE_NAME targetName{};
			targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
			targetName.header.size = sizeof(targetName);
			targetName.header.adapterId = path.targetInfo.adapterId;
			targetName.header.id = path.targetInfo.id;
			if (const LONG result = DisplayConfigGetDeviceInfo(&targetName.header); result != ERROR_SUCCESS) [[unlikely]]
			{
				throw std::runtime_error("Failed to get display info");
			}

			std::wstring_view name = targetName.monitorDevicePath;
			std::wstring_view friendlyName = targetName.monitorFriendlyDeviceName;
		}
	}

	DisplayService::~DisplayService() noexcept
	{
	}

	std::size_t DisplayService::DisplayCount() const noexcept
	{
		return 0uz;
	}

	DisplayHandle DisplayService::Display(const std::size_t index) const noexcept
	{
		return DisplayHandle{};
	}

	bool DisplayService::IsValid(const DisplayHandle displayHandle) const noexcept
	{
		return false;
	}

	bool DisplayService::IsConnected(const DisplayHandle displayHandle) const noexcept
	{
		return false;
	}

	struct DisplayInfo DisplayService::DisplayInfo(DisplayHandle displayHandle) const noexcept
	{
		return Display::DisplayInfo{};
	}
}
