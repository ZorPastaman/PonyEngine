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

import :Keyboard;

export namespace PonyEngine::Input
{
	/// @brief Keyboard container.
	/// @tparam NativeHandleType Native keyboard handle type.
	template<typename NativeHandleType>
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
		/// @brief Finds a keyboard index.
		/// @param keyboard Keyboard.
		/// @return Keyboard index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const class Keyboard& keyboard) const noexcept;
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
		/// @brief Gets a keyboard.
		/// @param index Keyboard index.
		/// @return Keyboard.
		[[nodiscard("Pure function")]]
		class Keyboard& Keyboard(std::size_t index) noexcept;
		/// @brief Gets a keyboard.
		/// @param index Keyboard index.
		/// @return Keyboard.
		[[nodiscard("Pure function")]]
		const class Keyboard& Keyboard(std::size_t index) const noexcept;

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
		std::vector<class Keyboard> keyboards; ///< Keyboards.
	};
}

namespace PonyEngine::Input
{
	template<typename NativeHandleType>
	std::size_t KeyboardContainer<NativeHandleType>::Size() const noexcept
	{
		return nativeHandles.size();
	}

	template<typename NativeHandleType>
	std::size_t KeyboardContainer<NativeHandleType>::IndexOf(const NativeHandleType& nativeHandle) const noexcept
	{
		return std::ranges::find(nativeHandles, nativeHandle) - nativeHandles.cbegin();
	}

	template<typename NativeHandleType>
	std::size_t KeyboardContainer<NativeHandleType>::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin();
	}

	template<typename NativeHandleType>
	std::size_t KeyboardContainer<NativeHandleType>::IndexOf(const class Keyboard& keyboard) const noexcept
	{
		return std::ranges::find_if(keyboards, [&](const std::shared_ptr<class Keyboard>& k) { return k.get() == &keyboard; }) - keyboards.cbegin();
	}

	template<typename NativeHandleType>
	std::size_t KeyboardContainer<NativeHandleType>::IndexOf(const std::string_view deviceName) const noexcept
	{
		return std::ranges::find_if(keyboards, [&](const class Keyboard& keyboard) { return keyboard.Name() == deviceName; }) - keyboards.cbegin();
	}

	template<typename NativeHandleTypeType>
	NativeHandleTypeType& KeyboardContainer<NativeHandleTypeType>::NativeHandle(const std::size_t index) noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleTypeType>
	const NativeHandleTypeType& KeyboardContainer<NativeHandleTypeType>::NativeHandle(const std::size_t index) const noexcept
	{
		return nativeHandles[index];
	}

	template<typename NativeHandleType>
	struct DeviceHandle& KeyboardContainer<NativeHandleType>::DeviceHandle(const std::size_t index) noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType>
	const struct DeviceHandle& KeyboardContainer<NativeHandleType>::DeviceHandle(const std::size_t index) const noexcept
	{
		return deviceHandles[index];
	}

	template<typename NativeHandleType>
	class Keyboard& KeyboardContainer<NativeHandleType>::Keyboard(const std::size_t index) noexcept
	{
		return keyboards[index];
	}

	template<typename NativeHandleType>
	const class Keyboard& KeyboardContainer<NativeHandleType>::Keyboard(const std::size_t index) const noexcept
	{
		return keyboards[index];
	}

	template<typename NativeHandleType>
	void KeyboardContainer<NativeHandleType>::Add(const NativeHandleType& nativeHandle, const struct DeviceHandle deviceHandle, 
		const std::string_view name, const bool isConnected)
	{
		nativeHandles.push_back(nativeHandle);
		try
		{
			deviceHandles.push_back(deviceHandle);
			try
			{
				keyboards.emplace_back(name, isConnected);
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
	void KeyboardContainer<NativeHandleType>::Remove(const std::size_t index) noexcept
	{
		keyboards.erase(keyboards.cbegin() + index);
		deviceHandles.erase(deviceHandles.cbegin() + index);
		nativeHandles.erase(nativeHandles.cbegin() + index);
	}

	template<typename NativeHandleType>
	void KeyboardContainer<NativeHandleType>::Clear() noexcept
	{
		nativeHandles.clear();
		deviceHandles.clear();
		keyboards.clear();
	}
}
