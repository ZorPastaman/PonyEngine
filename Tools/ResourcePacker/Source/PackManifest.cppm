/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.PackManifest;

import std;

export namespace PonyTools::PackManifest
{
	class PackManifest final
	{
	public:
		struct Resource final
		{
			std::size_t typeIndex;
			std::size_t dataMetaIndex;
			std::size_t loadMetaIndex;
			std::size_t rangeIndex;
			std::string id;
		};

		[[nodiscard("Pure constructor")]]
		PackManifest(bool deduplicateTypes, bool deduplicateDataMetas, bool deduplicateLoadMetas, bool deduplicateRanges) noexcept;
		[[nodiscard("Pure constructor")]]
		PackManifest(const PackManifest& other) = default;
		[[nodiscard("Pure constructor")]]
		PackManifest(PackManifest&& other) noexcept = default;

		~PackManifest() noexcept = default;

		[[nodiscard("Pure function")]]
		std::span<const std::string> Types() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::vector<std::byte>> DataMetas() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::vector<std::byte>> LoadMetas() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::uintmax_t, std::uintmax_t>> Ranges() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const Resource> Resources() const noexcept;

		void AddResource(std::string_view type, std::span<const std::byte> dataMeta, std::span<const std::byte> loadMeta, const std::pair<std::uintmax_t, std::uintmax_t>& range,
			std::string_view id);

		PackManifest& operator =(const PackManifest& other);
		PackManifest& operator =(PackManifest&& other) noexcept = default;

	private:
		[[nodiscard("Must be used")]]
		std::size_t AddType(std::string_view type);
		[[nodiscard("Must be used")]]
		std::size_t AddDataMeta(std::span<const std::byte> dataMeta);
		[[nodiscard("Must be used")]]
		std::size_t AddLoadMeta(std::span<const std::byte> loadMeta);
		[[nodiscard("Must be used")]]
		std::size_t AddRange(const std::pair<std::uintmax_t, std::uintmax_t>& range);

		bool deduplicateTypes;
		bool deduplicateDataMetas;
		bool deduplicateLoadMetas;
		bool deduplicateRanges;

		std::vector<std::string> types;
		std::vector<std::vector<std::byte>> dataMetas;
		std::vector<std::vector<std::byte>> loadMetas;
		std::vector<std::pair<std::uintmax_t, std::uintmax_t>> ranges;

		std::vector<Resource> resources;
	};
}

namespace PonyTools::PackManifest
{
	PackManifest::PackManifest(const bool deduplicateTypes, const bool deduplicateDataMetas, const bool deduplicateLoadMetas, const bool deduplicateRanges) noexcept :
		deduplicateTypes{deduplicateTypes},
		deduplicateDataMetas{deduplicateDataMetas},
		deduplicateLoadMetas{deduplicateLoadMetas},
		deduplicateRanges{deduplicateRanges}
	{
	}

	std::span<const std::string> PackManifest::Types() const noexcept
	{
		return types;
	}

	std::span<const std::vector<std::byte>> PackManifest::DataMetas() const noexcept
	{
		return dataMetas;
	}

	std::span<const std::vector<std::byte>> PackManifest::LoadMetas() const noexcept
	{
		return loadMetas;
	}

	std::span<const std::pair<std::uintmax_t, std::uintmax_t>> PackManifest::Ranges() const noexcept
	{
		return ranges;
	}

	std::span<const PackManifest::Resource> PackManifest::Resources() const noexcept
	{
		return resources;
	}

	void PackManifest::AddResource(const std::string_view type, const std::span<const std::byte> dataMeta, const std::span<const std::byte> loadMeta, 
		const std::pair<std::uintmax_t, std::uintmax_t>& range, const std::string_view id)
	{
		resources.push_back(Resource
		{
			.typeIndex = AddType(type),
			.dataMetaIndex = AddDataMeta(dataMeta),
			.loadMetaIndex = AddLoadMeta(loadMeta),
			.rangeIndex = AddRange(range),
			.id = std::string(id)
		});
	}

	PackManifest& PackManifest::operator =(const PackManifest& other)
	{
		PackManifest manifest = other;
		return *this = std::move(manifest);
	}

	std::size_t PackManifest::AddType(const std::string_view type)
	{
		if (deduplicateTypes)
		{
			if (const auto position = std::ranges::find(types, type); position != types.cend())
			{
				return position - types.cbegin();
			}
		}

		const std::size_t index = types.size();
		types.push_back(std::string(type));
		return index;
	}

	std::size_t PackManifest::AddDataMeta(const std::span<const std::byte> dataMeta)
	{
		if (deduplicateDataMetas)
		{
			if (const auto position = std::ranges::find_if(dataMetas, [&](const std::span<const std::byte> m)
			{
				return m.size() == dataMeta.size() && std::memcmp(m.data(), dataMeta.data(), dataMeta.size()) == 0;
			}); position != dataMetas.cend())
			{
				return position - dataMetas.cbegin();
			}
		}

		const std::size_t index = dataMetas.size();
		dataMetas.push_back(std::vector<std::byte>(dataMeta.cbegin(), dataMeta.cend()));
		return index;
	}

	std::size_t PackManifest::AddLoadMeta(const std::span<const std::byte> loadMeta)
	{
		if (deduplicateLoadMetas)
		{
			if (const auto position = std::ranges::find_if(loadMetas, [&](const std::span<const std::byte> m)
			{
				return m.size() == loadMeta.size() && std::memcmp(m.data(), loadMeta.data(), loadMeta.size()) == 0;
			}); position != loadMetas.cend())
			{
				return position - loadMetas.cbegin();
			}
		}

		const std::size_t index = loadMetas.size();
		loadMetas.push_back(std::vector<std::byte>(loadMeta.cbegin(), loadMeta.cend()));
		return index;
	}

	std::size_t PackManifest::AddRange(const std::pair<std::uintmax_t, std::uintmax_t>& range)
	{
		if (deduplicateRanges)
		{
			if (const auto position = std::ranges::find(ranges, range); position != ranges.cend())
			{
				return position - ranges.cbegin();
			}
		}

		const std::size_t index = ranges.size();
		ranges.push_back(range);
		return index;
	}
}
