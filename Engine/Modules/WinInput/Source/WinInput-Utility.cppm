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

export module PonyEngine.WinInput:Utility;

import std;

export namespace PonyEngine::WinInput
{
	/// @brief Gets a device name size.
	/// @param deviceHandle Device handle.
	/// @return Device name size.
	[[nodiscard("Pure function")]]
	std::size_t GetDeviceNameSize(HANDLE deviceHandle);
	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @param deviceName Device name. Must be enough size.
	/// @return Copied byte count.
	std::size_t GetDeviceName(HANDLE deviceHandle, std::span<char> deviceName);
}

namespace PonyEngine::WinInput
{
	std::size_t GetDeviceNameSize(const HANDLE deviceHandle)
	{
		UINT size = 0u;
		GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, nullptr, &size);
		if (!size || size == std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get device name size: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return size;
	}

	std::size_t GetDeviceName(const HANDLE deviceHandle, const std::span<char> deviceName)
	{
		UINT size = static_cast<UINT>(deviceName.size());
		const std::size_t copied = GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, deviceName.data(), &size);
		if (!copied || copied == std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get device name: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return copied - 1uz; // Minus null-terminator.
	}
}
