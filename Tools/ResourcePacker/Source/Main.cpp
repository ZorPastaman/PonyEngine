/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <cstdlib>

#include "toml++/toml.hpp"

import std;

import PonyTools.DepFile;
import PonyTools.FileSystem;
import PonyTools.Serialization;

struct ManifestCommand final
{
	std::string_view input;
	std::string_view params; ///< Path to a data params file.
	std::string_view output;
};
struct Command final
{
	std::string_view params; ///< Path to a data params file.
	std::string_view output;
	std::vector<ManifestCommand> manifestCommands;
	std::string_view depFile; ///< Path to a dep file.
	std::size_t sizeTSize = 0uz;
	bool bigEndian = false;
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
};

struct Resource final
{
	std::string id;
	std::filesystem::path dataPath;
	std::filesystem::path loadPath;
	std::size_t manifestIndex = std::numeric_limits<std::size_t>::max();
};

struct DataParams final
{
	bool deterministic = false;
};
struct ManifestParams final
{
	bool deduplicateTypes = true;
	bool deduplicateDataMetas = true;
	bool deduplicateLoadMetas = true;
};

constexpr std::string_view ParamsFlag = "-p"; ///< Parameters flag. The next argument must be a path.
constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view ManifestFlag = "-m";
constexpr std::string_view DepFileFlag = "-d"; ///< Dep file flag. The next argument must be a path.
constexpr std::string_view SizeTSizeFlag = "--size_t-size";
constexpr std::string_view BigEndianFlag = "--big-endian";
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view DataParamsSchema = "PonyEngine/Resource/Pack/Data/v0"; ///< Data params schema.
constexpr std::string_view LoadParamsSchema = "PonyEngine/Resource/Pack/Manifest/v0"; ///< Manifest params schema.
constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name.
constexpr std::string_view DeterministicPropertyName = "deterministic";

bool Verbose = false; ///< Verbose flag.

/// @brief Parses the command line.
/// @param argc Command line argument count.
/// @param argv Command line argument views.
/// @return Parsed command.
[[nodiscard("Pure function")]]
Command ParseCommandLine(int argc, const char* const argv[]);

/// @brief Prints the compiler version if requested.
/// @param command Parsed command.
void PrintVersion(const Command& command);
/// @brief Prints how to use if requested.
/// @param command Parsed command.
void PrintHowToUse(const Command& command);
/// @brief Prints the help.
/// @param command Parsed command.
void PrintHelp(const Command& command);

void Pack(const Command& command);
[[nodiscard("Pure function")]]
std::vector<Resource> GetResourcesInOrder(std::span<const ManifestCommand> manifestCommands, bool deterministic);
[[nodiscard("Pure function")]]
std::vector<Resource> GetManifestResources(std::span<const ManifestCommand> manifestCommands);

[[nodiscard("Pure function")]]
DataParams ReadDataParams(std::string_view path);
/// @brief Parses the parameters TOML file.
/// @param path Path to the file.
/// @return Parsed TOML.
[[nodiscard("Pure function")]]
toml::table ParseParams(std::string_view path);

int main(const int argc, const char* const argv[])
{
	try
	{
		const Command command = ParseCommandLine(argc, argv);

		PrintVersion(command);
		PrintHowToUse(command);
		PrintHelp(command);

		if (!command.output.empty()) [[likely]]
		{
			Pack(command);
		}
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}': '{}'.", typeid(e).name(), e.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::println(std::cerr, "Unexpected exception.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

Command ParseCommandLine(const int argc, const char* const argv[])
{
	auto command = Command{};

	if (argc <= 1) [[unlikely]]
	{
		command.showVersion = true;
		command.showHowToUse = true;

		return command;
	}

	for (int i = 1; i < argc; ++i)
	{
		const std::string_view arg = argv[i];

		if (arg == ParamsFlag)
		{
			if (!command.params.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Params flag '{}' set multiple times", ParamsFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after params flag '{}'", ParamsFlag));
			}

			command.params = argv[i];
		}
		else if (arg == OutputFlag)
		{
			if (!command.output.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Output flag '{}' set multiple times", OutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after output flag '{}'", OutputFlag));
			}

			command.output = argv[i];
		}
		else if (arg == ManifestFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path to input after manifest flag '{}'", ManifestFlag));
			}
			const std::string_view input = argv[i];
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path to params after manifest flag '{}'", ManifestFlag));
			}
			const std::string_view params = argv[i];
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path to output after manifest flag '{}'", ManifestFlag));
			}
			const std::string_view output = argv[i];

			command.manifestCommands.push_back(ManifestCommand{.input = input, .params = params, .output = output});
		}
		else if (arg == DepFileFlag)
		{
			if (!command.depFile.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Dep file flag '{}' set multiple times", DepFileFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after dep file flag '{}'", DepFileFlag));
			}

			command.depFile = argv[i];
		}
		else if (arg == SizeTSizeFlag)
		{
			if (command.sizeTSize != 0uz) [[unlikely]]
			{
				throw std::invalid_argument(std::format("std::size_t size flag '{}' set multiple times", SizeTSizeFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing size after std::size_t size flag '{}'", SizeTSizeFlag));
			}

			const std::string_view serializedSize = argv[i];
			auto [ptr, ec] = std::from_chars(serializedSize.data(), serializedSize.data() + serializedSize.size(), command.sizeTSize);
			if (ec != std::errc() || command.sizeTSize == 0uz) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Invalid size after std::size_t size flag '{}'", SizeTSizeFlag));
			}
			if (command.sizeTSize > sizeof(std::uintmax_t)) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Too great size after std::size_t size flag '{}', it can't be greater than std::uintmax_t of the host platform", SizeTSizeFlag));
			}
		}
		else if (arg == BigEndianFlag)
		{
			if (command.bigEndian) [[unlikely]]
			{
				std::println(std::clog, "Big endian flag '{}' set multiple times.", BigEndianFlag);
			}

			command.bigEndian = true;
		}
		else if (arg == VersionFlag) [[unlikely]]
		{
			if (command.showVersion) [[unlikely]]
			{
				std::println(std::clog, "Version flag '{}' set multiple times.", VersionFlag);
			}

			command.showVersion = true;
		}
		else if (arg == HelpFlag) [[unlikely]]
		{
			if (command.showHelp) [[unlikely]]
			{
				std::println(std::clog, "Help flag '{}' set multiple times.", HelpFlag);
			}

			command.showHelp = true;
		}
		else if (arg == VerboseFlag) [[unlikely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println(std::clog, "Verbose flag '{}' set multiple times.", VersionFlag);
			}

			Verbose = true;
		}
		else [[unlikely]]
		{
			throw std::invalid_argument(std::format("Unexpected argument: '{}'", arg));
		}
	}

	if (!command.output.empty())
	{
		if (command.params.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Data params file not set");
		}
		if (command.manifestCommands.empty()) [[unlikely]]
		{
			throw std::invalid_argument("No manifest command set");
		}
		if (command.sizeTSize == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("std::size_t size not set");
		}
	}
	else if (Verbose)
	{
		std::println("No data output file set - packing will be skipped.");
	}

	return command;
}

void PrintVersion(const Command& command)
{
	if (command.showVersion) [[unlikely]]
	{
		std::println("Pony Engine Resource Packer v{}.{}.{}.{}",
			PONY_ENGINE_VERSION_MAJOR, PONY_ENGINE_VERSION_MINOR, PONY_ENGINE_VERSION_PATCH, PONY_ENGINE_VERSION_TWEAK);
	}
}

void PrintHowToUse(const Command& command)
{
	if (command.showHowToUse) [[unlikely]]
	{
		std::println("Use '--help' to know how to use it.");
	}
}

void PrintHelp(const Command& command)
{
	if (command.showHelp) [[unlikely]]
	{
		std::println("\nPacks individual resources to a pack file.");
		std::println("\nUsage:");
		std::println("\tPonyResourcePacker [options]");
		std::println("\nOptions:");
		// TODO: Add options
		std::println("\t-d <path>                        Dep file path.");
		std::println("\t--version                        Display version information and exit.");
		std::println("\t--verbose                        Enable verbose output.");
		std::println("\t--help                           Display this help message and exit.");
		std::println();
	}
}

void Pack(const Command& command)
{
	const DataParams dataParams = ReadDataParams(command.params);
	const std::vector<Resource> resources = GetResourcesInOrder(command.manifestCommands, dataParams.deterministic);

	std::unordered_map<std::filesystem::path, std::pair<std::size_t, std::size_t>> dataRanges;
}

std::vector<Resource> GetResourcesInOrder(const std::span<const ManifestCommand> manifestCommands, const bool deterministic)
{
	std::vector<Resource> resources = GetManifestResources(manifestCommands);
	
	if (deterministic)
	{
		std::ranges::sort(resources, std::less<std::filesystem::path>{}, &Resource::dataPath);
	}

	return resources;
}

std::vector<Resource> GetManifestResources(const std::span<const ManifestCommand> manifestCommands)
{
	std::vector<Resource> resources;

	for (std::size_t i = 0uz; i < manifestCommands.size(); ++i)
	{
		const std::size_t thisManifestResourceStartIndex = resources.size();

		const ManifestCommand& manifestCommand = manifestCommands[i];
		const std::string_view inputPath = manifestCommand.input;
		std::ifstream input = PonyTools::FileSystem::OpenInput(inputPath);

		std::string line;
		while (std::getline(input, line))
		{
			std::vector<std::string> parsedLine = PonyTools::Serialization::ParseLine(line);
			if (parsedLine.size() != 3uz) [[unlikely]]
			{
				throw std::runtime_error("Invalid count of arguments in line in resource list, must be 3");
			}

			const std::string_view id = parsedLine[0];
			if (id.size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
			{
				throw std::runtime_error(std::format("ID '{}' at '{}' is too long, must be less or equal '{}'", id, inputPath, std::numeric_limits<std::uint8_t>::max()));
			}
			for (std::size_t index = thisManifestResourceStartIndex; index < resources.size(); ++index)
			{
				if (resources[index].id == id) [[unlikely]]
				{
					throw std::runtime_error(std::format("ID '{}' at '{}' is used at least twice", id, inputPath));
				}
			}

			resources.push_back(Resource
			{
				.id = std::move(parsedLine[0]),
				.dataPath = PonyTools::FileSystem::NormalizePath(parsedLine[1]),
				.loadPath = PonyTools::FileSystem::NormalizePath(parsedLine[2]),
				.manifestIndex = i
			});
		}
	}

	return resources;
}

DataParams ReadDataParams(const std::string_view path)
{
	const toml::table table = ParseParams(path);
	if (table[SchemaPropertyName].value<std::string_view>() != DataParamsSchema) [[unlikely]]
	{
		throw std::runtime_error(std::format("Data params file at '{}' doesn't have a valid schema", path));
	}

	auto params = DataParams{};

	if (const toml::node_view deterministicProperty = table[DeterministicPropertyName])
	{
		if (const std::optional<bool> deterministic = deterministicProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting data parameter: deterministic = '{}'.", *deterministic);
			}

			params.deterministic = *deterministic;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", DeterministicPropertyName, path));
		}
	}

	return params;
}

toml::table ParseParams(const std::string_view path)
{
	try
	{
		return toml::parse_file(path);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(std::format("Failed to parse params at path '{}': '{}': '{}'", std::filesystem::absolute(std::filesystem::path(path)).string(),
			typeid(e).name(), e.what()));
	}
	catch (...)
	{
		throw std::runtime_error(std::format("Failed to parse params at path '{}': Unknown exception", std::filesystem::absolute(std::filesystem::path(path)).string()));
	}
}
