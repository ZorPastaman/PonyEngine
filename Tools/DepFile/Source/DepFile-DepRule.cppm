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
	/// @brief Dep file rule.
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

		/// @brief Checks if it has a target at the @p path.
		/// @param path Path to check.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasTarget(const std::filesystem::path& path);
		/// @brief Checks if it has a dependency at the @p path.
		/// @param path Path to check.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasDependency(const std::filesystem::path& path);

		/// @brief Gets the targets.
		/// @return Targets.
		[[nodiscard("Pure function")]]
		std::span<const std::filesystem::path> Targets() const noexcept;
		/// @brief Gets the dependencies.
		/// @return Dependencies.
		[[nodiscard("Pure function")]]
		std::span<const std::filesystem::path> Dependencies() const noexcept;

		/// @brief Adds the @p path as a target.
		/// @param path Path to add.
		void AddTarget(const std::filesystem::path& path);
		/// @brief Adds the @p path as a dependency.
		/// @param path Path to add.
		void AddDependency(const std::filesystem::path& path);

		DepRule& operator =(const DepRule& other);
		DepRule& operator =(DepRule&& other) noexcept = default;

	private:
		/// @brief Checks if the @p checkPaths contains the @p path.
		/// @param checkPaths Check paths.
		/// @param path Path to check.
		/// @return @a True if they contain; @a false otherwise.
		[[nodiscard("Pure function")]]
		static bool HasPath(std::span<const std::filesystem::path> checkPaths, const std::filesystem::path& path);
		/// @brief Adds the @p path to the @p list.
		/// @param list Path list.
		/// @param path Path to add.
		void AddPath(std::vector<std::filesystem::path>& list, const std::filesystem::path& path);

		std::vector<std::filesystem::path> targets; ///< Targets. Always have lexically normal absolute paths.
		std::vector<std::filesystem::path> dependencies; /// Dependencies. Always have lexically normal absolute paths.
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

		list.push_back(std::filesystem::absolute(path).lexically_normal());
	}
}
