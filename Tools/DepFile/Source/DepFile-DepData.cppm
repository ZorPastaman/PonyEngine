/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.DepFile:DepData;

import std;

import :DepRule;

export namespace PonyTools::DepFile
{
	class DepData final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DepData() noexcept = default;
		[[nodiscard("Pure constructor")]]
		DepData(const DepData& other) = default;
		[[nodiscard("Pure constructor")]]
		DepData(DepData&& other) noexcept = default;

		~DepData() noexcept = default;

		[[nodiscard("Pure function")]]
		std::span<DepRule> Rules() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const DepRule> Rules() const noexcept;

		DepRule& AddRule();

		void Write(std::ostream& stream) const;

		DepData& operator =(const DepData& other);
		DepData& operator =(DepData&& other) noexcept = default;

	private:
		static void WritePaths(std::ostream& stream, std::span<const std::filesystem::path> paths);

		static std::string ConvertPathToDepPath(const std::filesystem::path& path);

		std::vector<DepRule> rules;
	};
}

namespace PonyTools::DepFile
{
	std::span<DepRule> DepData::Rules() noexcept
	{
		return rules;
	}

	std::span<const DepRule> DepData::Rules() const noexcept
	{
		return rules;
	}

	DepRule& DepData::AddRule()
	{
		rules.push_back(DepRule());
		return rules.back();
	}

	void DepData::Write(std::ostream& stream) const
	{
		if (!stream) [[unlikely]]
		{
			throw std::invalid_argument("Invalid stream");
		}

		for (const DepRule& rule : rules)
		{
			WritePaths(stream, rule.Targets());
			stream << ": ";
			WritePaths(stream, rule.Dependencies());
			stream << '\n';
		}
	}

	DepData& DepData::operator =(const DepData& other)
	{
		DepData data = other;
		return *this = std::move(data);
	}

	void DepData::WritePaths(std::ostream& stream, const std::span<const std::filesystem::path> paths)
	{
		if (paths.empty())
		{
			return;
		}

		stream << ConvertPathToDepPath(paths[0]);

		for (std::size_t i = 1uz; i < paths.size(); ++i)
		{
			stream << ' ' << ConvertPathToDepPath(paths[i]);
		}
	}

	std::string DepData::ConvertPathToDepPath(const std::filesystem::path& path)
	{
		return '"' + path.generic_string() + '"';
	}
}
