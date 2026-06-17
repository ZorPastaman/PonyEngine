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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.Impl:ResourceContainer;

import std;

import PonyEngine.Log;

import :ResourceEntry;
import :VariantEntry;

export namespace PonyEngine::Resource
{
	class ResourceContainer final
	{
	public:
		static constexpr auto ContextSort = [](const std::pair<ContextKey, ContextValue>& lhs, const std::pair<ContextKey, ContextValue>& rhs) 
		{
			return lhs.first < rhs.first;
		};

		[[nodiscard("Pure constructor")]]
		ResourceContainer() noexcept = default;
		ResourceContainer(const ResourceContainer&) = delete;
		ResourceContainer(ResourceContainer&&) = delete;

		~ResourceContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		bool HasResource(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		bool HasResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept;
		[[nodiscard("Pure function")]]
		const ResourceEntry* GetResource(ResourceID resourceId) const;
		[[nodiscard("Pure function")]]
		std::pair<const ResourceEntry*, std::size_t> GetResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const;

		[[nodiscard("Pure function")]]
		bool Empty() const noexcept;

		void AddResource(const ResourceParams& params, IResourceProvider& provider, ResourceHandle handle);
		void RemoveResource(ResourceHandle handle);
		void Clear() noexcept;

		[[nodiscard("Pure function")]]
		const std::unordered_map<ResourceHandle, ResourceID>& Handles() const noexcept;

		ResourceContainer& operator =(const ResourceContainer&) = delete;
		ResourceContainer& operator =(ResourceContainer&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		static bool AreMatched(std::span<const std::pair<ContextKey, ContextValue>> requiredContext, std::span<const std::pair<ContextKey, ContextValue>> context) noexcept;
		[[nodiscard("Pure function")]]
		static std::pair<std::size_t, bool> TryFind(std::span<const std::pair<ContextKey, ContextValue>> context, std::size_t startIndex, 
			ContextKey key, ContextValue value) noexcept;

		[[nodiscard("Pure function")]]
		static VariantEntry MakeVariant(const ResourceParams& params, IResourceProvider& provider, ResourceHandle handle);
		[[nodiscard("Pure function")]]
		static std::size_t InsertIndex(std::span<const VariantEntry> variants, const VariantEntry& newEntry) noexcept;

		std::unordered_map<ResourceID, ResourceEntry> resources;
		std::unordered_map<ResourceHandle, ResourceID> handleToIdMap;
	};
}

namespace PonyEngine::Resource
{
	bool ResourceContainer::HasResource(const ResourceID resourceId) const noexcept
	{
		return resources.contains(resourceId);
	}

	bool ResourceContainer::HasResource(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept
	{
		if (const auto position = resources.find(resourceId); position != resources.cend())
		{
			const ResourceEntry& entry = position->second;
			const std::span variants = entry.variants;
			for (std::size_t i = 0uz; i < variants.size(); ++i)
			{
				if (AreMatched(variants[i].requiredContext, context))
				{
					return true;
				}
			}
		}

		return false;
	}

	const ResourceEntry* ResourceContainer::GetResource(const ResourceID resourceId) const
	{
		if (const auto position = resources.find(resourceId); position != resources.cend()) [[likely]]
		{
			return &position->second;
		}

		throw std::invalid_argument("Not found by resource id");
	}

	std::pair<const ResourceEntry*, std::size_t> ResourceContainer::GetResource(const ResourceID resourceId,
		const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		if (const auto position = resources.find(resourceId); position != resources.cend()) [[likely]]
		{
			const ResourceEntry& entry = position->second;
			const std::span variants = entry.variants;
			for (std::size_t i = 0uz; i < variants.size(); ++i)
			{
				if (AreMatched(variants[i].requiredContext, context))
				{
					return std::pair(&entry, i);
				}
			}

			throw std::invalid_argument("Not found by context");
		}

		throw std::invalid_argument("Not found by resource id");
	}

	bool ResourceContainer::Empty() const noexcept
	{
		return handleToIdMap.empty();
	}

	void ResourceContainer::AddResource(const ResourceParams& params, IResourceProvider& provider, const ResourceHandle handle)
	{
		assert(!handleToIdMap.contains(handle) && "The handle has already been added.");

		handleToIdMap.emplace(handle, params.resourceId);
		try
		{
			if (const auto position = resources.find(params.resourceId); position != resources.cend())
			{
				if (position->second.type != params.type) [[unlikely]]
				{
					throw std::invalid_argument("Invalid type");
				}

				std::vector<VariantEntry>& variants = resources[params.resourceId].variants;
				VariantEntry variant = MakeVariant(params, provider, handle);
				const std::size_t index = InsertIndex(variants, variant);
				variants.insert(variants.cbegin() + index, std::move(variant));
			}
			else
			{
				ResourceEntry& entry = resources[params.resourceId];
				entry.id = params.resourceId;
				entry.type = params.type;
				try
				{
					entry.variants.push_back(MakeVariant(params, provider, handle));
				}
				catch (...)
				{
					resources.erase(params.resourceId);
					throw;
				}
			}
		}
		catch (...)
		{
			handleToIdMap.erase(handle);
			throw;
		}
	}

	void ResourceContainer::RemoveResource(const ResourceHandle handle)
	{
		if (const auto position = handleToIdMap.find(handle); position != handleToIdMap.cend())
		{
			ResourceEntry& entry = resources[position->second];
			for (std::size_t i = 0uz; i < entry.variants.size(); ++i)
			{
				if (entry.variants[i].handle == handle)
				{
					entry.variants.erase(entry.variants.cbegin() + i);
					break;
				}
			}
			if (entry.variants.empty())
			{
				resources.erase(position->second);
			}

			handleToIdMap.erase(position);
		}
		else
		{
			throw std::invalid_argument("Resource handle not found");
		}
	}

	void ResourceContainer::Clear() noexcept
	{
		resources.clear();
		handleToIdMap.clear();
	}

	const std::unordered_map<ResourceHandle, ResourceID>& ResourceContainer::Handles() const noexcept
	{
		return handleToIdMap;
	}

	bool ResourceContainer::AreMatched(const std::span<const std::pair<ContextKey, ContextValue>> requiredContext,
		const std::span<const std::pair<ContextKey, ContextValue>> context) noexcept
	{
		for (std::size_t requiredIndex = 0uz, contextIndex = 0uz; requiredIndex < requiredContext.size(); ++requiredIndex)
		{
			const auto [key, value] = requiredContext[requiredIndex];
			const auto [nextIndex, found] = TryFind(context, contextIndex, key, value);
			if (!found)
			{
				return false;
			}
			contextIndex = nextIndex;
		}

		return true;
	}

	std::pair<std::size_t, bool> ResourceContainer::TryFind(const std::span<const std::pair<ContextKey, ContextValue>> context, const std::size_t startIndex, 
		const ContextKey key, const ContextValue value) noexcept
	{
		std::size_t index = startIndex;
		bool found = false;
		for (; index < context.size() && !found && context[index].first <= key; ++index)
		{
			const auto [contextKey, contextValue] = context[index];
			found = contextKey == key && contextValue == value;
		}

		return std::pair(index, found);
	}

	VariantEntry ResourceContainer::MakeVariant(const ResourceParams& params, IResourceProvider& provider, const ResourceHandle handle)
	{
		auto variant = VariantEntry
		{
			.requiredContext = std::vector(std::from_range, params.requiredContext),
			.priority = params.priority,
			.provider = &provider,
			.index = params.index,
			.handle = handle
		};
		std::ranges::sort(variant.requiredContext, ContextSort);
		
		for (std::size_t i = 1uz; i < variant.requiredContext.size(); ++i)
		{
			if (variant.requiredContext[i - 1uz].first == variant.requiredContext[i].first) [[unlikely]]
			{
				throw std::invalid_argument("Context key duplicate found");
			}
		}

		return variant;
	}

	std::size_t ResourceContainer::InsertIndex(const std::span<const VariantEntry> variants, const VariantEntry& newEntry) noexcept
	{
		std::size_t index = 0uz;
		for (; index < variants.size() && newEntry.priority <= variants[index].priority; ++index)
		{
		}

		return index;
	}
}
