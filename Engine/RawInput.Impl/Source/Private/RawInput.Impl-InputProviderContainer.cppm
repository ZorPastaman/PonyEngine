/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.RawInput.Impl:InputProviderContainer;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::Input
{
	class InputProviderContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputProviderContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		InputProviderContainer(const InputProviderContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		InputProviderContainer(InputProviderContainer&& other) noexcept = default;

		~InputProviderContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(InputProviderHandle handle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IInputProvider& provider) const noexcept;

		[[nodiscard("Pure function")]]
		InputProviderHandle Handle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		IInputProvider& Provider(std::size_t index) const noexcept;

		void Add(InputProviderHandle handle, const std::shared_ptr<IInputProvider>& provider);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		InputProviderContainer& operator =(const InputProviderContainer& other) = default;
		InputProviderContainer& operator =(InputProviderContainer&& other) noexcept = default;

	private:
		std::vector<InputProviderHandle> handles;
		std::vector<std::shared_ptr<IInputProvider>> providers;
	};
}

namespace PonyEngine::Input
{
	std::size_t InputProviderContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t InputProviderContainer::IndexOf(const InputProviderHandle handle) const noexcept
	{
		return std::ranges::find(handles, handle) - handles.cbegin();
	}

	std::size_t InputProviderContainer::IndexOf(const IInputProvider& provider) const noexcept
	{
		return std::ranges::find_if(providers, [&](const std::shared_ptr<IInputProvider>& p) { return p.get() == &provider; }) - providers.cbegin();
	}

	InputProviderHandle InputProviderContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	IInputProvider& InputProviderContainer::Provider(const std::size_t index) const noexcept
	{
		return *providers[index];
	}

	void InputProviderContainer::Add(const InputProviderHandle handle, const std::shared_ptr<IInputProvider>& provider)
	{
		assert(provider && "The provider is nullptr.");

		handles.push_back(handle);
		try
		{
			providers.push_back(provider);
		}
		catch (...)
		{
			handles.pop_back();
			throw;
		}
	}

	void InputProviderContainer::Remove(const std::size_t index) noexcept
	{
		providers.erase(providers.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void InputProviderContainer::Clear() noexcept
	{
		handles.clear();
		providers.clear();
	}
}
