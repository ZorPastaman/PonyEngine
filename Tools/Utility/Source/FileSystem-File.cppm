/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.FileSystem:File;

import std;

export namespace PonyTools::FileSystem
{
	/// @brief Opens an input file.
	/// @param path File path.
	/// @param openMode Open mode.
	/// @return Input file stream.
	[[nodiscard("Pure function")]]
	std::ifstream OpenInput(std::string_view path, std::ios::openmode openMode = 0);
	/// @brief Opens an output file.
	/// @param path File path.
	/// @param openMode Open mode.
	/// @return Output file stream.
	[[nodiscard("Pure function")]]
	std::ofstream OpenOutput(std::string_view path, std::ios::openmode openMode = 0);
}

namespace PonyTools::FileSystem
{
	std::ifstream OpenInput(const std::string_view path, const std::ios::openmode openMode)
	{
		const auto inputPath = std::filesystem::absolute(std::filesystem::path(path)).lexically_normal();
		auto input = std::ifstream(inputPath, openMode);
		if (!input) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to open input file at path '{}'", inputPath.string()));
		}

		return input;
	}

	std::ofstream OpenOutput(const std::string_view path, const std::ios::openmode openMode)
	{
		const auto outputPath = std::filesystem::absolute(std::filesystem::path(path)).lexically_normal();
		std::filesystem::create_directories(outputPath.parent_path());
		auto output = std::ofstream(outputPath, openMode);
		if (!output) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to open output file at path '{}'", outputPath.string()));
		}

		return output;
	}
}
