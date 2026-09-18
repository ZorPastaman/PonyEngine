/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:PackContainer;

import std;

import PonyEngine.Resource.Pack;

import :Pack;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack container.
	class PackContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackContainer() noexcept = default;
		PackContainer(const PackContainer&) = delete;
		PackContainer(PackContainer&&) = delete;

		~PackContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Tries to find an index of the @p handle.
		/// @param handle Pack handle.
		/// @return Pack handle index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(PackID handle) const noexcept;

		/// @brief Gets a pack handle.
		/// @param index Pack index.
		/// @return Pack handle.
		[[nodiscard("Pure function")]]
		PackID Handle(std::size_t index) const noexcept;
		/// @brief Gets a pack resource collection.
		/// @param index Pack index.
		/// @return Pack resource collection.
		[[nodiscard("Pure function")]]
		ResourceCollection Collection(std::size_t index) const noexcept;
		/// @brief Gets a pack.
		/// @param index Pack index.
		/// @return Pack.
		[[nodiscard("Pure function")]]
		class Pack& Pack(std::size_t index) const noexcept;

		/// @brief Adds the pack.
		/// @param handle Pack handle.
		/// @param collection Pack resource collection.
		/// @param pack Pack.
		void Add(PackID handle, ResourceCollection collection, std::shared_ptr<class Pack> pack);
		/// @brief Removes a pack.
		/// @param index Pack index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the container.
		void Clear() noexcept;

		PackContainer& operator =(const PackContainer&) = delete;
		PackContainer& operator =(PackContainer&&) = delete;

	private:
		std::vector<PackID> handles;
		std::vector<ResourceCollection> collections;
		std::vector<std::shared_ptr<class Pack>> packs;
	};
}

namespace PonyEngine::Resource::Pack
{
	std::size_t PackContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t PackContainer::IndexOf(const PackID handle) const noexcept
	{
		auto position = std::ranges::lower_bound(handles, handle);
		if (position != handles.cend() && *position != handle)
		{
			position = handles.cend();
		}

		return position - handles.cbegin();
	}

	PackID PackContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	ResourceCollection PackContainer::Collection(const std::size_t index) const noexcept
	{
		return collections[index];
	}

	class Pack& PackContainer::Pack(const std::size_t index) const noexcept
	{
		return *packs[index];
	}

	void PackContainer::Add(const PackID handle, const ResourceCollection collection, std::shared_ptr<class Pack> pack)
	{
		const std::size_t initialSize = Size();
		const std::size_t index = std::ranges::lower_bound(handles, handle) - handles.cbegin();

		try
		{
			handles.insert(handles.cbegin() + index, handle);
			collections.insert(collections.cbegin() + index, collection);
			packs.insert(packs.cbegin() + index, std::move(pack));
		}
		catch (...)
		{
			if (packs.size() != initialSize)
			{
				packs.erase(packs.cbegin() + index);
			}
			if (collections.size() != initialSize)
			{
				collections.erase(collections.cbegin() + index);
			}
			if (handles.size() != initialSize)
			{
				handles.erase(handles.cbegin() + index);
			}

			throw;
		}
	}

	void PackContainer::Remove(const std::size_t index) noexcept
	{
		packs.erase(packs.cbegin() + index);
		collections.erase(collections.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void PackContainer::Clear() noexcept
	{
		handles.clear();
		collections.clear();
		packs.clear();
	}
}
