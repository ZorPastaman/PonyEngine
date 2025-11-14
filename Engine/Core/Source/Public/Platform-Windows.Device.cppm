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

export module PonyEngine.Platform:Windows.Device;

import std;

import PonyEngine.Text;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @return Device name.
	[[nodiscard("Pure function")]]
	std::string GetDeviceName(HANDLE deviceHandle);
	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @param deviceName Device name.
	/// @note In case of an exception, the @p deviceName may be corrupted.
	void GetDeviceName(HANDLE deviceHandle, std::string& deviceName);
}

namespace PonyEngine::Platform::Windows
{
	std::string GetDeviceName(const HANDLE deviceHandle)
	{
		std::string deviceName;
		GetDeviceName(deviceHandle, deviceName);
		return deviceName;
	}

	void GetDeviceName(const HANDLE deviceHandle, std::string& deviceName)
	{
		UINT size = 0u;
		GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, nullptr, &size);
		if (!size) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get device name size. Error code: '0x{:X}'.", GetLastError()));
		}
		deviceName.resize(size);

		const UINT length = GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, deviceName.data(), &size);
		if (!length) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get device name. Error code: '0x{:X}'.", GetLastError()));
		}
		deviceName.resize(length - 1u); // Minus null-terminator
	}
}
