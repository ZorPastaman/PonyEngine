/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:LoaderContainer;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Loader container.
	class LoaderContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoaderContainer() noexcept = default;
		LoaderContainer(const LoaderContainer&) = delete;
		LoaderContainer(LoaderContainer&&) = delete;

		~LoaderContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Tries to find an index of the @p loader.
		/// @param loader Loader.
		/// @return Loader index or size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(IResourceLoader& loader) const noexcept;
		/// @brief Tries to find an index of the @p type.
		/// @param type Resource type.
		/// @return Type index or size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ResourceType type) const noexcept;

		/// @brief Gets a loader at the index.
		/// @param index Loader index.
		/// @return Loader.
		[[nodiscard("Pure function")]]
		IResourceLoader& Loader(std::size_t index) const noexcept;
		/// @brief Gets types at the index.
		/// @param index Type index.
		/// @return Types.
		[[nodiscard("Pure function")]]
		std::span<const ResourceType> Types(std::size_t index) const noexcept;

		/// @brief Adds the loader.
		/// @param loader Loader.
		/// @param types Resource types.
		void Add(IResourceLoader& loader, std::span<const ResourceType> types);
		/// @brief Removes a loader.
		/// @param index Loader index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the container.
		void Clear() noexcept;

		LoaderContainer& operator =(const LoaderContainer&) = delete;
		LoaderContainer& operator =(LoaderContainer&&) = delete;

	private:
		std::vector<IResourceLoader*> loaders; ///< Loaders.
		std::vector<std::vector<ResourceType>> types; ///< Resource types.
	};
}

namespace PonyEngine::Resource
{
	std::size_t LoaderContainer::Size() const noexcept
	{
		return loaders.size();
	}

	std::size_t LoaderContainer::IndexOf(IResourceLoader& loader) const noexcept
	{
		return std::ranges::find(loaders, &loader) - loaders.cbegin();
	}

	std::size_t LoaderContainer::IndexOf(const ResourceType type) const noexcept
	{
		std::size_t index = 0uz;
		for (const std::span<const ResourceType> loaderTypes : types)
		{
			if (std::ranges::find(loaderTypes, type) != loaderTypes.cend())
			{
				break;
			}

			++index;
		}

		return index;
	}

	IResourceLoader& LoaderContainer::Loader(const std::size_t index) const noexcept
	{
		return *loaders[index];
	}

	std::span<const ResourceType> LoaderContainer::Types(const std::size_t index) const noexcept
	{
		return types[index];
	}

	void LoaderContainer::Add(IResourceLoader& loader, const std::span<const ResourceType> types)
	{
		loaders.push_back(&loader);
		try
		{
			this->types.push_back(std::vector<ResourceType>(types.cbegin(), types.cend()));
		}
		catch (...)
		{
			loaders.pop_back();
			throw;
		}
	}

	void LoaderContainer::Remove(const std::size_t index) noexcept
	{
		types.erase(types.cbegin() + index);
		loaders.erase(loaders.cbegin() + index);
	}

	void LoaderContainer::Clear() noexcept
	{
		types.clear();
		loaders.clear();
	}
}
