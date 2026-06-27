/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "toml++/toml.hpp"

#define SCHEMA_BASE "PonyEngine/Manifest/Resource/File/"

import std;

constexpr std::string_view OutputFlag = "-o";
constexpr std::string_view VersionFlag = "--version";
constexpr std::string_view HelpFlag = "--help";
constexpr std::string_view VerboseFlag = "--verbose";

constexpr std::string_view SchemaPropertyName = "schema";
constexpr std::string_view ResourcesPropertyName = "resources";
constexpr std::string_view IdPropertyName = "id";
constexpr std::string_view TypePropertyName = "type";
constexpr std::string_view PathPropertyName = "path";

constexpr std::string_view SchemaV0 = SCHEMA_BASE "v0";

constexpr std::string_view ManifestExtension = ".pfrm";
constexpr std::string_view MagicHeader = "PonyEngineFRM";

std::string_view Input = std::string_view();
std::string_view Output = std::string_view();
bool ShowVersion = false;
bool ShowHowToUse = false;
bool ShowHelp = false;
bool Verbose = false;

void ParseCommandLine(int argc, const char* const argv[]);

void PrintVersion();
void PrintHowToUse();
void PrintHelp();

void Compile();
[[nodiscard("Pure function")]]
std::vector<char> GenerateData(const toml::parse_result& manifest);
[[nodiscard("Pure function")]]
std::vector<char> GenerateDataV0(const toml::parse_result& manifest);
[[nodiscard("Pure function")]]
std::string_view GetResourcePropertyValue(const toml::table& table, std::string_view propertyName, std::string_view id = std::string_view());
void PushSize(std::vector<char>& data, std::size_t size, std::string_view propertyName);

void SaveToFile(std::span<const char> data);

int main(const int argc, const char* const argv[])
{
	try
	{
		ParseCommandLine(argc, argv);
		PrintVersion();
		PrintHowToUse();
		PrintHelp();
		Compile();
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

void ParseCommandLine(const int argc, const char* const argv[])
{
	if (argc <= 1) [[unlikely]]
	{
		ShowVersion = true;
		ShowHowToUse = true;

		return;
	}

	for (int i = 1; i < argc; ++i)
	{
		const std::string_view arg = argv[i];

		if (arg == OutputFlag) [[likely]]
		{
			if (!Output.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Output flag '{}' set multiple times", OutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::runtime_error(std::format("Parsing - Missing path after output flag '{}'", OutputFlag));
			}

			Output = argv[i];
		}
		else if (arg == VersionFlag) [[unlikely]]
		{
			if (ShowVersion) [[unlikely]]
			{
				std::println(std::clog, "Version flag '{}' set multiple times", VersionFlag);
			}

			ShowVersion = true;
		}
		else if (arg == HelpFlag) [[unlikely]]
		{
			if (ShowHelp) [[unlikely]]
			{
				std::println(std::clog, "Help flag '{}' set multiple times", HelpFlag);
			}

			ShowHelp = true;
		}
		else if (arg == VerboseFlag) [[unlikely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println(std::clog, "Verbose flag '{}' set multiple times", VersionFlag);
			}

			Verbose = true;
		}
		else [[likely]]
		{
			if (!Input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Parsing - Input path set multiple times");
			}

			Input = arg;
		}
	}
	
	if (!Output.empty() && Input.empty()) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - No input path");
	}
	if (!Input.empty() && Output.empty()) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - No output path");
	}

	if (ShowHelp) [[unlikely]]
	{
		ShowVersion = true;
	}
}

void PrintVersion()
{
	if (ShowVersion) [[unlikely]]
	{
		std::println("Pony Engine File Resource Manifest Compiler v{}.{}.{}.{}",
			PONY_ENGINE_VERSION_MAJOR, PONY_ENGINE_VERSION_MINOR, PONY_ENGINE_VERSION_PATCH, PONY_ENGINE_VERSION_TWEAK);
	}
}

void PrintHowToUse()
{
	if (ShowHowToUse) [[unlikely]]
	{
		std::println("Use '--help' to know how to use it.");
	}
}

void PrintHelp()
{
	if (ShowHelp) [[unlikely]]
	{
		std::println("\nCompiles a file resource manifest to a binary format used by PonyEngine.Resource.File.Impl module.");
		std::println("\nUsage:");
		std::println("\tponyfrmc <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>          Input manifest file. See the engine documentation for the file format.");
		std::println("\nOptions:");
		std::println("\t-o <output>      Output file path without extension. The extension .pfrm will be added automatically.");
		std::println("\t                 See the engine documentation for the file format.");
		std::println("\t--version        Display version information and exit.");
		std::println("\t--verbose        Enable verbose output.");
		std::println("\t--help           Display this help message and exit.");
		std::println();
	}
}

void Compile()
{
	if (Input.empty() || Output.empty()) [[unlikely]]
	{
		return;
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Input: '{}'; Output: '{}'.", Input, Output);
	}

	const toml::parse_result manifest = toml::parse_file(Input);
	const std::vector<char> data = GenerateData(manifest);
	SaveToFile(data);
}

std::vector<char> GenerateData(const toml::parse_result& manifest)
{
	const std::optional<std::string_view> schema = manifest[SchemaPropertyName].value<std::string_view>();
	if (!schema) [[unlikely]]
	{
		throw std::invalid_argument("No schema property found or it's invalid");
	}

	if (schema == SchemaV0) [[likely]]
	{
		return GenerateDataV0(manifest);
	}

	throw std::invalid_argument(std::format("Compiling - Unsupported schema '{}'", *schema));
}

std::vector<char> GenerateDataV0(const toml::parse_result& manifest)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Generating Data V0.");
	}

	std::vector<char> data;

	if (const toml::array* const resources = manifest[ResourcesPropertyName].as_array()) [[likely]]
	{
		std::vector<std::string_view> ids;
		ids.reserve(resources->size());

		for (const toml::node& node : *resources) 
		{
			if (const toml::table* const table = node.as_table()) [[likely]]
			{
				const std::string_view id = GetResourcePropertyValue(*table, IdPropertyName);
				const std::string_view type = GetResourcePropertyValue(*table, TypePropertyName, id);
				const std::string_view path = GetResourcePropertyValue(*table, PathPropertyName, id);
				if (std::ranges::find(ids, id) != ids.cend()) [[unlikely]]
				{
					throw std::invalid_argument(std::format("Compiling - Resource id '{}' used multiple times", id));
				}

				if (Verbose) [[unlikely]]
				{
					std::println("Adding resource element. ID: '{}'; Type: '{}'; Path: '{}'.", id, type, path);
				}

				PushSize(data, id.size(), IdPropertyName);
				PushSize(data, type.size(), TypePropertyName);
				PushSize(data, path.size(), PathPropertyName);
				data.append_range(id);
				data.append_range(type);
				data.append_range(path);

				ids.push_back(id);
			}
			else [[unlikely]]
			{
				throw std::invalid_argument("Compiling - Invalid resource element");
			}
		}
	}

	return data;
}

std::string_view GetResourcePropertyValue(const toml::table& table, const std::string_view propertyName, const std::string_view id)
{
	const std::optional<std::string_view> property = table[propertyName].value<std::string_view>();
	if (!property) [[unlikely]]
	{
		if (propertyName == IdPropertyName)
		{
			throw std::invalid_argument("Compiling - Resource element doesn't have property 'id'");
		}

		throw std::invalid_argument(std::format("Compiling - Resource element with id '{}' doesn't have property '{}'", id, propertyName));
	}

	return *property;
}

void PushSize(std::vector<char>& data, const std::size_t size, const std::string_view propertyName)
{
	if (size > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Compiling - Value of property '{}' is too long: Length = '{}', Max = '{}'", 
			propertyName, size, std::numeric_limits<std::uint8_t>::max()));
	}

	data.push_back(std::bit_cast<char>(static_cast<std::uint8_t>(size)));
}

void SaveToFile(const std::span<const char> data)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Saving to file.");
	}

	auto filePath = std::string();
	filePath.reserve(Output.size() + ManifestExtension.size());
	filePath.append_range(Output).append_range(ManifestExtension);

	auto file = std::ofstream(filePath, std::ios::trunc | std::ios::binary);
	file << MagicHeader << std::string_view(data);
}
