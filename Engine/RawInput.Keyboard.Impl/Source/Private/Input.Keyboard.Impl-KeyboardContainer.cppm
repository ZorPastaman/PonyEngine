/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Keyboard.Impl:KeyboardContainer;

import std;

import PonyEngine.RawInput.Ext;

import :Keyboard;

export namespace PonyEngine::Input
{
	template<typename NativeHandleType>
	class KeyboardContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		KeyboardContainer() noexcept = default;
		KeyboardContainer(const KeyboardContainer&) = delete;
		KeyboardContainer(KeyboardContainer&&) = delete;

		~KeyboardContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const NativeHandleType& nativeHandle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(struct DeviceHandle deviceHandle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const class Keyboard& keyboard) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::string_view deviceName) const noexcept;

		[[nodiscard("Pure function")]]
		NativeHandleType& NativeHandle(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const NativeHandleType& NativeHandle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		struct DeviceHandle& DeviceHandle(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const struct DeviceHandle& DeviceHandle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		class Keyboard& Keyboard(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const class Keyboard& Keyboard(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<class Keyboard>& KeyboardShared(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const class Keyboard>& KeyboardShared(std::size_t index) const noexcept;

		void Add(const NativeHandleType& nativeHandle, struct DeviceHandle deviceHandle, const std::shared_ptr<class Keyboard>& keyboard);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		KeyboardContainer& operator =(const KeyboardContainer&) = delete;
		KeyboardContainer& operator =(KeyboardContainer&&) = delete;

	private:
		std::vector<NativeHandleType> nativeHandles;
		std::vector<struct DeviceHandle> deviceHandles;
		std::vector<std::shared_ptr<class Keyboard>> keyboards;
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
		return std::ranges::find_if(keyboards, [&](const std::shared_ptr<class Keyboard>& keyboard) { return keyboard->Name() == deviceName; }) - keyboards.cbegin();
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
		return *keyboards[index];
	}

	template<typename NativeHandleType>
	const class Keyboard& KeyboardContainer<NativeHandleType>::Keyboard(const std::size_t index) const noexcept
	{
		return *keyboards[index];
	}

	template<typename NativeHandleType>
	const std::shared_ptr<class Keyboard>& KeyboardContainer<NativeHandleType>::KeyboardShared(const std::size_t index) noexcept
	{
		return keyboards[index];
	}

	template<typename NativeHandleType>
	const std::shared_ptr<const class Keyboard>& KeyboardContainer<NativeHandleType>::KeyboardShared(const std::size_t index) const noexcept
	{
		return keyboards[index];
	}

	template<typename NativeHandleType>
	void KeyboardContainer<NativeHandleType>::Add(const NativeHandleType& nativeHandle, const struct DeviceHandle deviceHandle, const std::shared_ptr<class Keyboard>& keyboard)
	{
		try
		{
			nativeHandles.push_back(nativeHandle);
			deviceHandles.push_back(deviceHandle);
			keyboards.push_back(keyboard);
		}
		catch (...)
		{
			const std::size_t size = keyboards.size();
			deviceHandles.resize(size);
			nativeHandles.resize(size);

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
