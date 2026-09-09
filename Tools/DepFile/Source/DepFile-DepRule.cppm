/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.DepFile:DepRule;

import std;

export namespace PonyTools::DepFile
{
	class DepRule final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DepRule() noexcept = default;
		[[nodiscard("Pure constructor")]]
		DepRule(const DepRule& other) = default;
		[[nodiscard("Pure constructor")]]
		DepRule(DepRule&& other) noexcept = default;

		~DepRule() noexcept = default;

		[[nodiscard("Pure function")]]
		bool HasTarget(const std::filesystem::path& path);
		[[nodiscard("Pure function")]]
		bool HasDependency(const std::filesystem::path& path);

		[[nodiscard("Pure function")]]
		std::span<const std::filesystem::path> Targets() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::filesystem::path> Dependencies() const noexcept;

		void AddTarget(const std::filesystem::path& path);
		void AddDependency(const std::filesystem::path& path);

		DepRule& operator =(const DepRule& other);
		DepRule& operator =(DepRule&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		static bool HasPath(std::span<const std::filesystem::path> checkPaths, const std::filesystem::path& path);
		void AddPath(std::vector<std::filesystem::path>& list, const std::filesystem::path& path);

		[[nodiscard("Pure function")]]
		static std::filesystem::path NormalPath(const std::filesystem::path& path);

		std::vector<std::filesystem::path> targets;
		std::vector<std::filesystem::path> dependencies;
	};
}

namespace PonyTools::DepFile
{
	bool DepRule::HasTarget(const std::filesystem::path& path)
	{
		return HasPath(targets, path);
	}

	bool DepRule::HasDependency(const std::filesystem::path& path)
	{
		return HasPath(dependencies, path);
	}

	std::span<const std::filesystem::path> DepRule::Targets() const noexcept
	{
		return targets;
	}

	std::span<const std::filesystem::path> DepRule::Dependencies() const noexcept
	{
		return dependencies;
	}

	void DepRule::AddTarget(const std::filesystem::path& path)
	{
		AddPath(targets, path);
	}

	void DepRule::AddDependency(const std::filesystem::path& path)
	{
		AddPath(dependencies, path);
	}

	DepRule& DepRule::operator =(const DepRule& other)
	{
		DepRule depSet = other;
		return *this = std::move(depSet);
	}

	bool DepRule::HasPath(const std::span<const std::filesystem::path> checkPaths, const std::filesystem::path& path)
	{
		for (const std::filesystem::path& checkPath : checkPaths)
		{
			if (std::filesystem::equivalent(checkPath, path))
			{
				return true;
			}
		}

		return false;
	}

	void DepRule::AddPath(std::vector<std::filesystem::path>& list, const std::filesystem::path& path)
	{
		if (HasTarget(path) || HasDependency(path)) [[unlikely]]
		{
			throw std::invalid_argument("Path already added");
		}

		list.push_back(NormalPath(path));
	}

	std::filesystem::path DepRule::NormalPath(const std::filesystem::path& path)
	{
		return std::filesystem::absolute(path).lexically_normal();
	}
}
