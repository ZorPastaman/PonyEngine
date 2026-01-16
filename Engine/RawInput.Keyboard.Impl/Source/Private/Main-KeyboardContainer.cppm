/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl:KeyboardContainer;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::RawInput
{
	/// @brief Keyboard container.
	/// @tparam NativeHandleType Native keyboard handle type.
	/// @tparam NativeKeyType Native keyboard key type.
	template<typename NativeHandleType, typename NativeKeyType>
	class KeyboardContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		KeyboardContainer() noexcept = default;
		KeyboardContainer(const KeyboardContainer&) = delete;
		KeyboardContainer(KeyboardContainer&&) = delete;

		~KeyboardContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds a keyboard index by the @p nativeHandle.
		/// @param nativeHandle Native handle.
		/// @return Keyboard index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const NativeHandleType& nativeHandle) const noexcept;
		/// @brief Finds a keyboard index by the @p deviceHandle.
		/// @param deviceHandle Device handle.
		/// @return Keyboard index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(struct DeviceHandle deviceHandle) const noexcept;
		/// @brief Finds a keyboard index by the @p deviceName.
		/// @param deviceName Device name.
		/// @return Keyboard index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::string_view deviceName) const noexcept;

		/// @brief Gets a native handle.
		/// @param index Keyboard index.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		NativeHandleType& NativeHandle(std::size_t index) noexcept;
		/// @brief Gets a native handle.
		/// @param index Keyboard index.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		const NativeHandleType& NativeHandle(std::size_t index) const noexcept;
		/// @brief Gets a device handle.
		/// @param index Keyboard index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		struct DeviceHandle& DeviceHandle(std::size_t index) noexcept;
		/// @brief Gets a device handle.
		/// @param index Keyboard index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		const struct DeviceHandle& DeviceHandle(std::size_t index) const noexcept;

		/// @brief Gets a device name.
		/// @param index Keyboard index.
		/// @return Device name.
		[[nodiscard("Pure function")]]
		std::string_view DeviceName(std::size_t index) const noexcept;

		/// @brief Gets a device connection status.
		/// @param index Keyboard index.
		/// @return @a True if it's connected; @p false otherwise.
		[[nodiscard("Pure function")]]
		bool IsConnected(std::size_t index) const noexcept;
		/// @brief Sets a device connection status.
		/// @param index Keyboard index.
		/// @param isConnected Connection status.
		void Connect(std::size_t index, bool isConnected) noexcept;

		/// @brief Checks if the key is pressed.
		/// @param index Keyboard index.
		/// @param key Key axis.
		/// @return @a True if it's pressed; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsPressed(std::size_t index, NativeKeyType key) const noexcept;
		/// @brief Gets pressed keys.
		/// @param index Keyboard index.
		/// @return Pressed keys.
		[[nodiscard("Pure function")]]
		std::span<const NativeKeyType> PressedKeys(std::size_t index) const noexcept;
		/// @brief Sets if the key is pressed.
		/// @param index Keyboard index.
		/// @param key Key axis.
		/// @param value Is it pressed?
		void Press(std::size_t index, NativeKeyType key, bool value);
		/// @brief Resets all the keys to unpressed.
		/// @param index Keyboard index.
		void ResetKeys(std::size_t index) noexcept;

		/// @brief Adds a keyboard.
		/// @param nativeHandle Native handle.
		/// @param deviceHandle Device handle.
		/// @param name Keyboard name.
		/// @param isConnected Is the device connected?
		void Add(const NativeHandleType& nativeHandle, struct DeviceHandle deviceHandle, std::string_view name, bool isConnected);
		/// @brief Removed a keyboard.
		/// @param index Keyboard index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		KeyboardContainer& operator =(const KeyboardContainer&) = delete;
		KeyboardContainer& operator =(KeyboardContainer&&) = delete;

	private:
		std::vector<NativeHandleType> nativeHandles; ///< Native keyboard handles.
		std::vector<struct DeviceHandle> deviceHandles; ///< Device handles.
		std::vector<std::string> deviceNames; ///< Device names.
		std::vector<bool> connections; ///< Keyboard connection statuses.
		std::vector<std::vector<NativeKeyType>> pressedKeys; ///< Keyboard pressed keys.
	};
}

namespace PonyEngine::RawInput
{
	template<typename NativeHandleType, typename NativeKeyType>
	std::size_t KeyboardContainer<NativeHandleType, NativeKeyType>::Size() const noexcept
	{
		return nativeHandles.size();
	}

	template<typename NativeHandleType, typename NativeKeyType>
	std::size_t KeyboardContainer<NativeHandleType, NativeKeyType>::IndexOf(const NativeHandleType& nativeHandle) const noexcept
	{
		return std::ranges::find(nativeHandles, nativeHandle) - nativeHandles.cbegin();
	}

	template<typename NativeHandleType, typename NativeKeyType>
	std::size_t KeyboardContainer<NativeHandleType, NativeKeyType>::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin();
	}

	template<typename NativeHandleType, typename NativeKeyType>
	std::size_t KeyboardContainer<NativeHandleType, NativeKeyType>::IndexOf(const std::string_view deviceName) const noexcept
	{
		return std::ranges::find(deviceNames, deviceName) - deviceNames.cbegin();
	}

	template<typename NativeHandleTypeType, typename NativeKeyType>
	NativeHandleTypeType& KeyboardContainer<NativeHandleTypeType, NativeKeyType>::NativeHandle(const std::size_t index) noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleTypeType, typename NativeKeyType>
	const NativeHandleTypeType& KeyboardContainer<NativeHandleTypeType, NativeKeyType>::NativeHandle(const std::size_t index) const noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	struct DeviceHandle& KeyboardContainer<NativeHandleType, NativeKeyType>::DeviceHandle(const std::size_t index) noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	const struct DeviceHandle& KeyboardContainer<NativeHandleType, NativeKeyType>::DeviceHandle(const std::size_t index) const noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	std::string_view KeyboardContainer<NativeHandleType, NativeKeyType>::DeviceName(const std::size_t index) const noexcept
	{
		return deviceNames[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	bool KeyboardContainer<NativeHandleType, NativeKeyType>::IsConnected(const std::size_t index) const noexcept
	{
		return connections[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::Connect(const std::size_t index, const bool isConnected) noexcept
	{
		connections[index] = isConnected;
	}

	template<typename NativeHandleType, typename NativeKeyType>
	bool KeyboardContainer<NativeHandleType, NativeKeyType>::IsPressed(const std::size_t index, const NativeKeyType key) const noexcept
	{
		const std::span<const NativeKeyType> pressed = PressedKeys(index);
		return std::ranges::find(pressed, key) != pressed.cend();
	}

	template<typename NativeHandleType, typename NativeKeyType>
	std::span<const NativeKeyType> KeyboardContainer<NativeHandleType, NativeKeyType>::PressedKeys(const std::size_t index) const noexcept
	{
		return pressedKeys[index];
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::Press(const std::size_t index, const NativeKeyType key, const bool value)
	{
		std::vector<NativeKeyType>& pressed = pressedKeys[index];
		const auto position = std::ranges::find(pressed, key);

		if (value)
		{
			if (position == pressed.cend()) [[likely]]
			{
				pressed.push_back(key);
			}
		}
		else
		{
			if (position != pressed.cend()) [[likely]]
			{
				pressed.erase(position);
			}
		}
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::ResetKeys(const std::size_t index) noexcept
	{
		pressedKeys[index].clear();
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::Add(const NativeHandleType& nativeHandle, const struct DeviceHandle deviceHandle, 
		const std::string_view name, const bool isConnected)
	{
		nativeHandles.push_back(nativeHandle);
		try
		{
			deviceHandles.push_back(deviceHandle);
			try
			{
				deviceNames.emplace_back(name);
				try
				{
					connections.push_back(isConnected);
					try
					{
						pressedKeys.push_back(std::vector<NativeKeyType>());
					}
					catch (...)
					{
						connections.pop_back();
						throw;
					}
				}
				catch (...)
				{
					deviceNames.pop_back();
					throw;
				}
			}
			catch (...)
			{
				deviceHandles.pop_back();
				throw;
			}
		}
		catch (...)
		{
			nativeHandles.pop_back();
			throw;
		}
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::Remove(const std::size_t index) noexcept
	{
		pressedKeys.erase(pressedKeys.cbegin() + index);
		connections.erase(connections.cbegin() + index);
		deviceNames.erase(deviceNames.cbegin() + index);
		deviceHandles.erase(deviceHandles.cbegin() + index);
		nativeHandles.erase(nativeHandles.cbegin() + index);
	}

	template<typename NativeHandleType, typename NativeKeyType>
	void KeyboardContainer<NativeHandleType, NativeKeyType>::Clear() noexcept
	{
		nativeHandles.clear();
		deviceHandles.clear();
		deviceNames.clear();
		connections.clear();
		pressedKeys.clear();
	}
}
