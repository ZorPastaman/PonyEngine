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
	/// @brief Opens an input file.
	/// @param path File path.
	/// @param openMode Open mode.
	/// @return Input file stream.
	[[nodiscard("Pure function")]]
	std::ifstream OpenInput(const std::filesystem::path& path, std::ios::openmode openMode = 0);
	/// @brief Opens an output file.
	/// @param path File path.
	/// @param openMode Open mode.
	/// @return Output file stream.
	[[nodiscard("Pure function")]]
	std::ofstream OpenOutput(std::string_view path, std::ios::openmode openMode = 0);
	/// @brief Opens an output file.
	/// @param path File path.
	/// @param openMode Open mode.
	/// @return Output file stream.
	[[nodiscard("Pure function")]]
	std::ofstream OpenOutput(const std::filesystem::path& path, std::ios::openmode openMode = 0);

	/// @brief Writes the unsigned integral value to the stream.
	/// @tparam T Value type.
	/// @param stream Target stream.
	/// @param value Value.
	/// @param byteCount How many bytes to write.
	/// @param bigEndian If @a true, the writing will treat a target platform as big-endian; otherwise, little-endian.
	/// @return Target stream.
	template<std::unsigned_integral T>
	std::ofstream& Write(std::ofstream& stream, T value, std::size_t byteCount, bool bigEndian);
}

namespace PonyTools::FileSystem
{
	std::ifstream OpenInput(const std::string_view path, const std::ios::openmode openMode)
	{
		return OpenInput(std::filesystem::path(path), openMode);
	}

	std::ifstream OpenInput(const std::filesystem::path& path, const std::ios::openmode openMode)
	{
		const auto inputPath = std::filesystem::absolute(path).lexically_normal();
		auto input = std::ifstream(inputPath, openMode);
		if (!input) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to open input file at path '{}'", inputPath.string()));
		}

		return input;
	}

	std::ofstream OpenOutput(const std::string_view path, const std::ios::openmode openMode)
	{
		return OpenOutput(std::filesystem::path(path), openMode);
	}

	std::ofstream OpenOutput(const std::filesystem::path& path, const std::ios::openmode openMode)
	{
		const auto outputPath = std::filesystem::absolute(path).lexically_normal();
		std::filesystem::create_directories(outputPath.parent_path());
		auto output = std::ofstream(outputPath, openMode);
		if (!output) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to open output file at path '{}'", outputPath.string()));
		}

		return output;
	}

	template<std::unsigned_integral T>
	std::ofstream& Write(std::ofstream& stream, const T value, const std::size_t byteCount, const bool bigEndian)
	{
		for (std::size_t i = 0uz; i < byteCount; ++i)
		{
			const std::size_t byteIndex = bigEndian ? byteCount - 1u - i : i;
			const auto byte = static_cast<std::byte>((value >> (byteIndex * 8u)) & 0xFFu);
			stream.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
		}

		return stream;
	}
}
