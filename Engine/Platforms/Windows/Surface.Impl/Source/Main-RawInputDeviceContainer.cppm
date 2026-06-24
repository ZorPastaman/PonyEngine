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

export module PonyEngine.Surface.Impl.Windows:RawInputDeviceContainer;

import std;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Raw input device container.
	class RawInputDeviceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		RawInputDeviceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		RawInputDeviceContainer(const RawInputDeviceContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		RawInputDeviceContainer(RawInputDeviceContainer&& other) noexcept = default;

		~RawInputDeviceContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the @p handle.
		/// @param handle Device handle.
		/// @return Handle index or @p Size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(HANDLE handle) const noexcept;

		/// @brief Gets a device handle.
		/// @param index Device index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		HANDLE Handle(std::size_t index) const noexcept;
		/// @brief Gets a device type.
		/// @param index Device index.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		DWORD DeviceType(std::size_t index) const noexcept;

		/// @brief Adds a device.
		/// @param handle Device handle.
		/// @param deviceType Device type.
		void Add(HANDLE handle, DWORD deviceType);
		/// @brief Removes a device.
		/// @param index Device index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the data.
		void Clear() noexcept;

		RawInputDeviceContainer& operator =(const RawInputDeviceContainer& other) = delete;
		RawInputDeviceContainer& operator =(RawInputDeviceContainer&& other) noexcept = default;

	private:
		std::vector<HANDLE> deviceHandles; ///< Device handles.
		std::vector<DWORD> deviceTypes; ///< Device types.
	};
}

namespace PonyEngine::Surface::Windows
{
	std::size_t RawInputDeviceContainer::Size() const noexcept
	{
		return deviceHandles.size();
	}

	std::size_t RawInputDeviceContainer::IndexOf(const HANDLE handle) const noexcept
	{
		return std::ranges::find(deviceHandles, handle) - deviceHandles.cbegin();
	}

	HANDLE RawInputDeviceContainer::Handle(const std::size_t index) const noexcept
	{
		return deviceHandles[index];
	}

	DWORD RawInputDeviceContainer::DeviceType(const std::size_t index) const noexcept
	{
		return deviceTypes[index];
	}

	void RawInputDeviceContainer::Add(const HANDLE handle, const DWORD deviceType)
	{
		deviceHandles.push_back(handle);
		try
		{
			deviceTypes.push_back(deviceType);
		}
		catch (...)
		{
			deviceHandles.pop_back();
			throw;
		}
	}

	void RawInputDeviceContainer::Remove(const std::size_t index) noexcept
	{
		deviceTypes.erase(deviceTypes.cbegin() + index);
		deviceHandles.erase(deviceHandles.cbegin() + index);
	}

	void RawInputDeviceContainer::Clear() noexcept
	{
		deviceHandles.clear();
		deviceTypes.clear();
	}
}
