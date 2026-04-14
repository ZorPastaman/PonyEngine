/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseContainer;

import std;

import PonyEngine.RawInput;

import :MouseAxis;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse container.
	/// @tparam NativeHandleType Native mouse handle type.
	template<typename NativeHandleType>
	class MouseContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		MouseContainer() noexcept = default;
		MouseContainer(const MouseContainer&) = delete;
		MouseContainer(MouseContainer&&) = delete;

		~MouseContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds a mouse index by the @p nativeHandle.
		/// @param nativeHandle Native handle.
		/// @return Mouse index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const NativeHandleType& nativeHandle) const noexcept;
		/// @brief Finds a mouse index by the @p deviceHandle.
		/// @param deviceHandle Device handle.
		/// @return Mouse index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(struct DeviceHandle deviceHandle) const noexcept;
		/// @brief Finds a mouse index by the @p deviceName.
		/// @param deviceName Device name.
		/// @return Mouse index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::string_view deviceName) const noexcept;

		/// @brief Gets a native handle.
		/// @param index Mouse index.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		NativeHandleType& NativeHandle(std::size_t index) noexcept;
		/// @brief Gets a native handle.
		/// @param index Mouse index.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		const NativeHandleType& NativeHandle(std::size_t index) const noexcept;
		/// @brief Gets a device handle.
		/// @param index Mouse index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		struct DeviceHandle& DeviceHandle(std::size_t index) noexcept;
		/// @brief Gets a device handle.
		/// @param index Mouse index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		const struct DeviceHandle& DeviceHandle(std::size_t index) const noexcept;

		/// @brief Gets the mouse name.
		/// @return Mouse name.
		[[nodiscard("Pure function")]]
		std::string_view Name(std::size_t index) const noexcept;

		/// @brief Gets the connection status.
		/// @param index Mouse index.
		/// @return Connection status.
		[[nodiscard("Pure function")]]
		bool IsConnected(std::size_t index) const noexcept;
		/// @brief Sets the connection status.
		/// @param index Mouse index.
		/// @param isConnected Connection status.
		void Connect(std::size_t index, bool isConnected) noexcept;

		/// @brief Checks if the button pressed.
		/// @param index Mouse index.
		/// @param button Button ID.
		/// @return @a True if it's pressed; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsPressed(std::size_t index, MouseButton button) const noexcept;
		/// @brief Gets all the button states.
		/// @param index Mouse index.
		/// @return Button states.
		/// @remark They are placed in the order they are declared in the enum.
		[[nodiscard("Pure function")]]
		std::span<const bool, MouseButtonCount> ButtonStates(std::size_t index) const noexcept;
		/// @brief Sets a button state.
		/// @param index Mouse index.
		/// @param button Button ID.
		/// @param value Button state.
		void Press(std::size_t index, MouseButton button, bool value) noexcept;
		/// @brief Resets all the buttons to the false state.
		void ResetButtons(std::size_t index) noexcept;

		/// @brief Adds a mouse.
		/// @param nativeHandle Native handle.
		/// @param deviceHandle Device handle.
		/// @param name Device name.
		/// @param isConnected Is the mouse connected?
		void Add(const NativeHandleType& nativeHandle, struct DeviceHandle deviceHandle, std::string_view name, bool isConnected);
		/// @brief Removed a mouse.
		/// @param index Mouse index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		MouseContainer& operator =(const MouseContainer&) = delete;
		MouseContainer& operator =(MouseContainer&&) = delete;

	private:
		std::vector<NativeHandleType> nativeHandles; ///< Native mouse handles.
		std::vector<struct DeviceHandle> deviceHandles; ///< Device handles.
		std::vector<std::string> mouseNames;
		std::vector<bool> connections;
		std::vector<std::array<bool, MouseButtonCount>> buttonStates;
	};
}

namespace PonyEngine::RawInput::Mouse
{
	template<typename NativeHandleType>
	std::size_t MouseContainer<NativeHandleType>::Size() const noexcept
	{
		return nativeHandles.size();
	}

	template<typename NativeHandleType>
	std::size_t MouseContainer<NativeHandleType>::IndexOf(const NativeHandleType& nativeHandle) const noexcept
	{
		return std::ranges::find(nativeHandles, nativeHandle) - nativeHandles.cbegin();
	}

	template<typename NativeHandleType>
	std::size_t MouseContainer<NativeHandleType>::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin();
	}

	template<typename NativeHandleType>
	std::size_t MouseContainer<NativeHandleType>::IndexOf(const std::string_view deviceName) const noexcept
	{
		return std::ranges::find(mouseNames, deviceName) - mouseNames.cbegin();
	}

	template<typename NativeHandleTypeType>
	NativeHandleTypeType& MouseContainer<NativeHandleTypeType>::NativeHandle(const std::size_t index) noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleTypeType>
	const NativeHandleTypeType& MouseContainer<NativeHandleTypeType>::NativeHandle(const std::size_t index) const noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleType>
	struct DeviceHandle& MouseContainer<NativeHandleType>::DeviceHandle(const std::size_t index) noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType>
	const struct DeviceHandle& MouseContainer<NativeHandleType>::DeviceHandle(const std::size_t index) const noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType>
	std::string_view MouseContainer<NativeHandleType>::Name(const std::size_t index) const noexcept
	{
		return mouseNames[index];
	}

	template<typename NativeHandleType>
	bool MouseContainer<NativeHandleType>::IsConnected(const std::size_t index) const noexcept
	{
		return connections[index];
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Connect(const std::size_t index, const bool isConnected) noexcept
	{
		connections[index] = isConnected;
	}

	template<typename NativeHandleType>
	bool MouseContainer<NativeHandleType>::IsPressed(const std::size_t index, const MouseButton button) const noexcept
	{
		return buttonStates[index][static_cast<std::size_t>(button)];
	}

	template<typename NativeHandleType>
	std::span<const bool, MouseButtonCount> MouseContainer<NativeHandleType>::ButtonStates(const std::size_t index) const noexcept
	{
		return buttonStates[index];
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Press(const std::size_t index, const MouseButton button, const bool value) noexcept
	{
		buttonStates[index][static_cast<std::size_t>(button)] = value;
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::ResetButtons(const std::size_t index) noexcept
	{
		std::ranges::fill(buttonStates[index], false);
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Add(const NativeHandleType& nativeHandle, const struct DeviceHandle deviceHandle,
		const std::string_view name, const bool isConnected)
	{
		nativeHandles.push_back(nativeHandle);
		try
		{
			deviceHandles.push_back(deviceHandle);
			try
			{
				mouseNames.emplace_back(name);
				try
				{
					connections.push_back(isConnected);
					try
					{
						auto buttons = std::array<bool, MouseButtonCount>();
						std::ranges::fill(buttons, false);
						buttonStates.push_back(buttons);
					}
					catch (...)
					{
						connections.pop_back();
						throw;
					}
				}
				catch (...)
				{
					mouseNames.pop_back();
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

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Remove(const std::size_t index) noexcept
	{
		buttonStates.erase(buttonStates.cbegin() + index);
		connections.erase(connections.cbegin() + index);
		mouseNames.erase(mouseNames.cbegin() + index);
		deviceHandles.erase(deviceHandles.cbegin() + index);
		nativeHandles.erase(nativeHandles.cbegin() + index);
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Clear() noexcept
	{
		nativeHandles.clear();
		deviceHandles.clear();
		mouseNames.clear();
		connections.clear();
		buttonStates.clear();
	}
}
