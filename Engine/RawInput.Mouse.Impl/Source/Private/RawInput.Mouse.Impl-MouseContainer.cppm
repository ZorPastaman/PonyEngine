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

import :Mouse;

export namespace PonyEngine::Input
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
		/// @brief Gets a mouse.
		/// @param index Mouse index.
		/// @return Mouse.
		[[nodiscard("Pure function")]]
		class Mouse& Mouse(std::size_t index) noexcept;
		/// @brief Gets a mouse.
		/// @param index Mouse index.
		/// @return Mouse.
		[[nodiscard("Pure function")]]
		const class Mouse& Mouse(std::size_t index) const noexcept;

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
		std::vector<class Mouse> mouses; ///< Mouses.
	};
}

namespace PonyEngine::Input
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
		return std::ranges::find_if(mouses, [&](const class Mouse& mouse) { return mouse.Name() == deviceName; }) - mouses.cbegin();
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
	class Mouse& MouseContainer<NativeHandleType>::Mouse(const std::size_t index) noexcept
	{
		return mouses[index];
	}

	template<typename NativeHandleType>
	const class Mouse& MouseContainer<NativeHandleType>::Mouse(const std::size_t index) const noexcept
	{
		return mouses[index];
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
				mouses.emplace_back(name, isConnected);
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
		mouses.erase(mouses.cbegin() + index);
		deviceHandles.erase(deviceHandles.cbegin() + index);
		nativeHandles.erase(nativeHandles.cbegin() + index);
	}

	template<typename NativeHandleType>
	void MouseContainer<NativeHandleType>::Clear() noexcept
	{
		nativeHandles.clear();
		deviceHandles.clear();
		mouses.clear();
	}
}
