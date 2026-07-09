/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "toml++/toml.hpp"

/// @brief File resource manifest schema base.
#define SCHEMA_BASE "PonyEngine/Manifest/Resource/File/"

import std;

constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name. Must be a string.
constexpr std::string_view ResourcesPropertyName = "resources"; ///< Resources property name. Must be an array.
constexpr std::string_view IdPropertyName = "id"; ///< Resource ID property name. Must be a string.
constexpr std::string_view TypePropertyName = "type"; ///< Resource type property name. Must be a string.
constexpr std::string_view PathPropertyName = "path"; ///< Resource path property name. Must be a string.

constexpr std::string_view SchemaV0 = SCHEMA_BASE "v0"; ///< Schema v0. It's the actual schema.

constexpr std::string_view ManifestExtension = ".pfrm"; ///< Binary manifest extension.
constexpr std::string_view MagicHeader = "PonyEngineFRM"; ///< Magic header of a binary manifest.

/// @brief Parsed command.
struct Command final
{
	std::string_view input = std::string_view(); ///< Path to an input text manifest.
	std::string_view output = std::string_view(); ///< Path to an output binary manifest.
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
	bool verbose = false; ///< Verbose?
};

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

/// @brief Compiles a manifest if requested.
/// @param command Parsed command.
void Compile(const Command& command);
/// @brief Gets a manifest version index.
/// @param manifest Parsed manifest.
/// @return Manifest version index.
[[nodiscard("Pure function")]]
std::uint32_t GetManifestVersion(const toml::table& manifest);
/// @brief Compiles a manifest of version 0.
/// @param command Parsed command.
/// @param source Parsed manifest.
void CompileV0(const Command& command, const toml::table& source);
/// @brief Gets a resource ID.
/// @param table Resource table.
/// @param propertyName Resource ID property name.
/// @return Resource ID.
[[nodiscard("Pure function")]]
std::string_view GetResourceID(const toml::table& table, std::string_view propertyName);
/// @brief Gets a resource property value.
/// @param table Resource table.
/// @param propertyName Resource property name.
/// @param id Resource ID.
/// @return Resource property value.
[[nodiscard("Pure function")]]
std::string_view GetResourcePropertyValue(const toml::table& table, std::string_view propertyName, std::string_view id);
/// @brief Pushes the small size to the stream.
/// @param stream Target stream.
/// @param size Size.
/// @param propertyName Property name.
void PushSize(std::ofstream& stream, std::size_t size, std::string_view propertyName);

/// @brief Gets a binary resource manifest path.
/// @param path Parsed resource manifest path.
/// @return Binary resource manifest path.
[[nodiscard("Pure function")]]
std::filesystem::path GetManifestPath(std::string_view path);
/// @brief Gets a binary resource manifest output stream.
/// @param path Binary resource manifest path.
/// @return Binary resource manifest output stream.
[[nodiscard("Pure function")]]
std::ofstream CreateManifestStream(const std::filesystem::path& path);

int main(const int argc, const char* const argv[])
{
	try
	{
		const Command command = ParseCommandLine(argc, argv);
		PrintVersion(command);
		PrintHowToUse(command);
		PrintHelp(command);
		Compile(command);
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}': '{}'.", typeid(e).name(), e.what());
		return 1;
	}
	catch (...)
	{
		std::println(std::cerr, "Unexpected exception.");
		return 1;
	}

	return 0;
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

		if (arg == OutputFlag) [[likely]]
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
			if (command.verbose) [[unlikely]]
			{
				std::println(std::clog, "Verbose flag '{}' set multiple times.", VersionFlag);
			}

			command.verbose = true;
		}
		else [[likely]]
		{
			if (!command.input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Input path set multiple times");
			}

			command.input = arg;
		}
	}
	
	if (!command.output.empty() && command.input.empty()) [[unlikely]]
	{
		throw std::invalid_argument("No input path");
	}
	if (!command.input.empty() && command.output.empty()) [[unlikely]]
	{
		throw std::invalid_argument("No output path");
	}

	if (command.showHelp) [[unlikely]]
	{
		command.showVersion = true;
	}

	return command;
}

void PrintVersion(const Command& command)
{
	if (command.showVersion) [[unlikely]]
	{
		std::println("Pony Engine File Resource Manifest Compiler v{}.{}.{}.{}",
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
		std::println("\nCompiles a text file resource manifest into a binary file resource manifest.");
		std::println("\nUsage:");
		std::println("\tponyfrmc <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>          Input manifest file.");
		std::println("\nOptions:");
		std::println("\t-o <output>      Output manifest file. The extension must be '.pfrm'.");
		std::println("\t--version        Display version information and exit.");
		std::println("\t--verbose        Enable verbose output.");
		std::println("\t--help           Display this help message and exit.");
		std::println();
	}
}

void Compile(const Command& command)
{
	if (command.input.empty() || command.output.empty()) [[unlikely]]
	{
		return;
	}

	if (command.verbose) [[unlikely]]
	{
		std::println("Input: '{}'; Output: '{}'.", command.input, command.output);
	}

	switch (const toml::table manifest = toml::parse_file(command.input); GetManifestVersion(manifest))
	{
	case 0:
		CompileV0(command, manifest);
		break;
	default: [[unlikely]]
		throw std::invalid_argument("Invalid schema");
	}
}

std::uint32_t GetManifestVersion(const toml::table& manifest)
{
	const std::optional<std::string_view> schema = manifest[SchemaPropertyName].value<std::string_view>();
	if (!schema) [[unlikely]]
	{
		throw std::invalid_argument("No schema property found or it's invalid");
	}

	if (schema == SchemaV0)
	{
		return 0;
	}

	throw std::invalid_argument("Invalid schema");
}

void CompileV0(const Command& command, const toml::table& source)
{
	if (command.verbose) [[unlikely]]
	{
		std::println("Compiling manifest V0.");
	}

	const std::filesystem::path manifestPath = GetManifestPath(command.output);
	std::ofstream manifest = CreateManifestStream(manifestPath);

	if (const toml::node_view resourcesProperty = source[ResourcesPropertyName]) [[likely]]
	{
		if (const toml::array* const resources = resourcesProperty.as_array()) [[likely]]
		{
			std::vector<std::string_view> ids;
			ids.reserve(resources->size());

			for (const toml::node& node : *resources)
			{
				if (const toml::table* const table = node.as_table()) [[likely]]
				{
					const std::string_view id = GetResourceID(*table, IdPropertyName);
					const std::string_view type = GetResourcePropertyValue(*table, TypePropertyName, id);
					const std::string_view path = GetResourcePropertyValue(*table, PathPropertyName, id);
					if (std::ranges::find(ids, id) != ids.cend()) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource id '{}' used multiple times", id));
					}

					if (command.verbose) [[unlikely]]
					{
						std::println("Adding resource element. ID: '{}'; Type: '{}'; Path: '{}'.", id, type, path);
					}

					if (!std::filesystem::path(path).is_relative()) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource id '{}' has not relative path '{}'", id, path));
					}

					PushSize(manifest, id.size(), IdPropertyName);
					PushSize(manifest, type.size(), TypePropertyName);
					PushSize(manifest, path.size(), PathPropertyName);
					manifest << id << type << path;

					ids.push_back(id);
				}
				else [[unlikely]]
				{
					throw std::invalid_argument("Invalid resource element");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Invalid resources array");
		}
	}
}

std::string_view GetResourceID(const toml::table& table, const std::string_view propertyName)
{
	const std::optional<std::string_view> property = table[propertyName].value<std::string_view>();
	if (!property) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Resource element doesn't have property ID property '{}'", propertyName));
	}

	return *property;
}

std::string_view GetResourcePropertyValue(const toml::table& table, const std::string_view propertyName, const std::string_view id)
{
	const std::optional<std::string_view> property = table[propertyName].value<std::string_view>();
	if (!property) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Resource element with id '{}' doesn't have property '{}'", id, propertyName));
	}

	return *property;
}

void PushSize(std::ofstream& stream, const std::size_t size, const std::string_view propertyName)
{
	if (size > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Value of property '{}' is too long: Length = '{}', Max = '{}'",
			propertyName, size, std::numeric_limits<std::uint8_t>::max()));
	}

	stream << std::bit_cast<char>(static_cast<std::uint8_t>(size));
}

std::filesystem::path GetManifestPath(const std::string_view path)
{
	const std::filesystem::path manifestPath = std::filesystem::absolute(std::filesystem::path(path).lexically_normal());
	if (manifestPath.extension() != ManifestExtension) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Invalid output file extension, must be '{}'", ManifestExtension));
	}
	std::filesystem::create_directories(manifestPath.parent_path());

	return manifestPath;
}

std::ofstream CreateManifestStream(const std::filesystem::path& path)
{
	auto manifestStream = std::ofstream(path, std::ios::trunc | std::ios::binary);
	if (!manifestStream) [[unlikely]]
	{
		throw std::runtime_error("Failed to open output file for writing");
	}

	manifestStream << MagicHeader;

	return manifestStream;
}
