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
	/// @brief Input provider container.
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

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the @p handle.
		/// @param handle Provider handle.
		/// @return Provider index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(InputProviderHandle handle) const noexcept;
		/// @brief Finds an index of the @p provider.
		/// @param provider Provider.
		/// @return Provider index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IInputProvider& provider) const noexcept;

		/// @brief Gets a provider handle.
		/// @param index Provider index.
		/// @return Provider handle.
		[[nodiscard("Pure function")]]
		InputProviderHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets a provider.
		/// @param index Provider index.
		/// @return Provider.
		[[nodiscard("Pure function")]]
		IInputProvider& Provider(std::size_t index) const noexcept;

		/// @brief Adds the provider.
		/// @param handle Provider handle.
		/// @param provider Provider.
		void Add(InputProviderHandle handle, const std::shared_ptr<IInputProvider>& provider);
		/// @brief Removes a provider.
		/// @param index Provider index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the data.
		void Clear() noexcept;

		InputProviderContainer& operator =(const InputProviderContainer& other) = delete;
		InputProviderContainer& operator =(InputProviderContainer&& other) noexcept = default;

	private:
		std::vector<InputProviderHandle> handles; ///< Input provider handles.
		std::vector<std::shared_ptr<IInputProvider>> providers; ///< Input providers.
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
