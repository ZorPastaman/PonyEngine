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

export module PonyEngine.Resource.Impl:ResourceProviderContainer;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Resource provider container.
	class ResourceProviderContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceProviderContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ResourceProviderContainer(const ResourceProviderContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		ResourceProviderContainer(ResourceProviderContainer&& other) noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the @p handle.
		/// @param handle Provider handle.
		/// @return Provider index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ResourceProviderHandle handle) const noexcept;
		/// @brief Finds an index of the @p provider.
		/// @param provider Provider.
		/// @return Provider index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IResourceProvider& provider) const noexcept;

		/// @brief Gets a provider handle.
		/// @param index Provider index.
		/// @return Provider handle.
		[[nodiscard("Pure function")]]
		ResourceProviderHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets a provider.
		/// @param index Provider index.
		/// @return Provider.
		[[nodiscard("Pure function")]]
		IResourceProvider& Provider(std::size_t index) const noexcept;

		/// @brief Adds the provider.
		/// @param handle Provider handle.
		/// @param provider Provider.
		void Add(ResourceProviderHandle handle, const std::shared_ptr<IResourceProvider>& provider);
		/// @brief Removes a provider.
		/// @param index Provider index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the data.
		void Clear() noexcept;

		ResourceProviderContainer& operator =(const ResourceProviderContainer&) = delete;
		ResourceProviderContainer& operator =(ResourceProviderContainer&& other) noexcept = default;

	private:
		std::vector<ResourceProviderHandle> handles; ///< Resource provider handles.
		std::vector<std::shared_ptr<IResourceProvider>> providers; ///< Resource providers.
	};
}

namespace PonyEngine::Resource
{
	std::size_t ResourceProviderContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t ResourceProviderContainer::IndexOf(const ResourceProviderHandle handle) const noexcept
	{
		return std::ranges::find(handles, handle) - handles.cbegin();
	}

	std::size_t ResourceProviderContainer::IndexOf(const IResourceProvider& provider) const noexcept
	{
		return std::ranges::find_if(providers, [&](const std::shared_ptr<IResourceProvider>& p) { return p.get() == &provider; }) - providers.cbegin();
	}

	ResourceProviderHandle ResourceProviderContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	IResourceProvider& ResourceProviderContainer::Provider(const std::size_t index) const noexcept
	{
		return *providers[index];
	}

	void ResourceProviderContainer::Add(const ResourceProviderHandle handle, const std::shared_ptr<IResourceProvider>& provider)
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

	void ResourceProviderContainer::Remove(const std::size_t index) noexcept
	{
		providers.erase(providers.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void ResourceProviderContainer::Clear() noexcept
	{
		providers.clear();
		handles.clear();
	}
}
