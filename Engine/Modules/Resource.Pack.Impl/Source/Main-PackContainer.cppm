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
	class PackContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackContainer() noexcept = default;
		PackContainer(const PackContainer&) = delete;
		PackContainer(PackContainer&&) = delete;

		~PackContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(PackHandle handle) const noexcept;

		[[nodiscard("Pure function")]]
		PackHandle Handle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		ResourceCollection Collection(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		class Pack& Pack(std::size_t index) const noexcept;

		void Add(PackHandle handle, ResourceCollection collection, std::shared_ptr<class Pack> pack);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		PackContainer& operator =(const PackContainer&) = delete;
		PackContainer& operator =(PackContainer&&) = delete;

	private:
		std::vector<PackHandle> handles;
		std::vector<ResourceCollection> collections;
		std::vector<std::shared_ptr<class Pack>> packs;
	};
}
