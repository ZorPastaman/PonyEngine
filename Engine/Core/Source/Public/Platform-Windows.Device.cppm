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

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets a device name size.
	/// @param deviceHandle Device handle.
	/// @return Device name size.
	[[nodiscard("Pure function")]]
	std::size_t GetDeviceNameSize(HANDLE deviceHandle);

	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @return Device name.
	[[nodiscard("Pure function")]]
	std::string GetDeviceName(HANDLE deviceHandle);
	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @param deviceName Device name.
	void GetDeviceName(HANDLE deviceHandle, std::string& deviceName);
	/// @brief Gets a device name.
	/// @param deviceHandle Device handle.
	/// @param deviceName Device name. Must be enough size.
	/// @return Copied byte count.
	std::size_t GetDeviceName(HANDLE deviceHandle, std::span<char> deviceName);

}

namespace PonyEngine::Platform::Windows
{
	std::size_t GetDeviceNameSize(const HANDLE deviceHandle)
	{
		UINT size = 0u;
		GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, nullptr, &size);
		if (!size || size == std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get device name size. Error code: '0x{:X}'.", GetLastError()));
		}

		return static_cast<std::size_t>(size);
	}

	std::string GetDeviceName(const HANDLE deviceHandle)
	{
		std::string deviceName;
		GetDeviceName(deviceHandle, deviceName);
		return deviceName;
	}

	void GetDeviceName(const HANDLE deviceHandle, std::string& deviceName)
	{
		const std::size_t size = GetDeviceNameSize(deviceHandle);
		deviceName.resize(size);
		const std::size_t copied = GetDeviceName(deviceHandle, std::span<char>(deviceName.data(), deviceName.size()));
		deviceName.resize(copied); // Minus null-terminator.
	}

	std::size_t GetDeviceName(const HANDLE deviceHandle, const std::span<char> deviceName)
	{
		UINT size = static_cast<UINT>(deviceName.size());
		const std::size_t copied = GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICENAME, deviceName.data(), &size);
		if (!copied || copied == std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get device name. Error code: '0x{:X}'.", GetLastError()));
		}

		return static_cast<std::size_t>(copied - 1uz); // Minus null-terminator.
	}
}
