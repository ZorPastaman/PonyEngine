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

constexpr std::string_view CreateFlag = "--create";
constexpr std::string_view AddFlag = "--add";
constexpr std::string_view RemoveFlag = "--remove";
constexpr std::string_view UpgradeFlag = "--upgrade";
constexpr std::string_view VersionFlag = "--version";
constexpr std::string_view HelpFlag = "--help";
constexpr std::string_view VerboseFlag = "--verbose";

constexpr std::string_view SchemaPropertyName = "schema";
constexpr std::string_view ResourcesPropertyName = "resources";
constexpr std::string_view IdPropertyName = "id";
constexpr std::string_view TypePropertyName = "type";
constexpr std::string_view PathPropertyName = "path";

constexpr std::string_view SchemaV0 = SCHEMA_BASE "v0";

struct AddCommand final
{
	std::string_view id;
	std::string_view type;
	std::string_view path;
};
struct RemoveCommand final
{
	std::string_view id;
};

std::string_view FilePath = std::string_view();
std::vector<AddCommand> AddCommands;
std::vector<RemoveCommand> RemoveCommands;
bool Create = false;
bool Upgrade = false;
bool ShowVersion = false;
bool ShowHowToUse = false;
bool ShowHelp = false;
bool Verbose = false;

void ParseCommandLine(int argc, const char* const argv[]);

void PrintVersion();
void PrintHowToUse();
void PrintHelp();

[[nodiscard("Pure function")]]
toml::table ReadManifest();
[[nodiscard("Pure function")]]
std::filesystem::path GetInputPath();
void ValidateManifestV0(const toml::table& manifest);
void RemoveResources(toml::table& manifest);
void AddResources(toml::table& manifest);

void SaveToFile(const toml::table& manifest);
[[nodiscard("Pure function")]]
std::filesystem::path GetOutputPath();

[[nodiscard("Pure function")]]
std::optional<std::size_t> FindResource(const toml::array& resources, std::string_view id, std::string_view stage);
[[nodiscard("Pure function")]]
toml::array* GetOrCreateResourceArray(toml::table& manifest);

int main(const int argc, const char* const argv[])
{
	try
	{
		ParseCommandLine(argc, argv);

		PrintVersion();
		PrintHowToUse();
		PrintHelp();

		if (!FilePath.empty()) [[likely]]
		{
			toml::table manifest = ReadManifest();
			RemoveResources(manifest);
			AddResources(manifest);

			SaveToFile(manifest);
		}
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

		if (arg == CreateFlag)
		{
			if (Create)
			{
				std::println(std::clog, "Create flag '{}' set multiple times.", CreateFlag);
			}

			Create = true;
		}
		else if (arg == AddFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing resource description after add flag '{}'", AddFlag));
			}

			const std::string_view resource = argv[i];
			const std::size_t firstCommaIndex = resource.find(',');
			const std::size_t secondCommaIndex = resource.find(',', firstCommaIndex + 1uz);
			const std::size_t thirdCommaIndex = resource.find(',', secondCommaIndex + 1uz);
			if (firstCommaIndex == std::string_view::npos || secondCommaIndex == std::string_view::npos || thirdCommaIndex != std::string_view::npos) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Invalid object to add = '{}'", resource));
			}

			AddCommands.push_back(AddCommand
			{
				.id = resource.substr(0uz, firstCommaIndex),
				.type = resource.substr(firstCommaIndex + 1uz, secondCommaIndex - firstCommaIndex - 1uz),
				.path = resource.substr(secondCommaIndex + 1uz)
			});
		}
		else if (arg == RemoveFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing id after remove flag '{}'", RemoveFlag));
			}

			RemoveCommands.push_back(RemoveCommand{.id = argv[i]});
		}
		else if (arg == UpgradeFlag)
		{
			if (Upgrade) [[unlikely]]
			{
				std::println(std::clog, "Upgrade flag '{}' set multiple times.", UpgradeFlag);
			}

			Upgrade = true;
		}
		else if (arg == VersionFlag) [[unlikely]]
		{
			if (ShowVersion) [[unlikely]]
			{
				std::println(std::clog, "Version flag '{}' set multiple times.", VersionFlag);
			}

			ShowVersion = true;
		}
		else if (arg == HelpFlag) [[unlikely]]
		{
			if (ShowHelp) [[unlikely]]
			{
				std::println(std::clog, "Help flag '{}' set multiple times.", HelpFlag);
			}

			ShowHelp = true;
		}
		else if (arg == VerboseFlag) [[unlikely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println(std::clog, "Verbose flag '{}' set multiple times.", VersionFlag);
			}

			Verbose = true;
		}
		else
		{
			if (!FilePath.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Parsing - File path set multiple times");
			}

			FilePath = arg;
		}
	}

	if ((Create || Upgrade || !RemoveCommands.empty() || !AddCommands.empty()) && FilePath.empty()) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - File path isn't set");
	}

	if (Create)
	{
		if (!RemoveCommands.empty()) [[unlikely]]
		{
			std::println(std::clog, "Create '{}' and remove '{}' flags are set in one command.", CreateFlag, RemoveFlag);
		}
		if (Upgrade) [[unlikely]]
		{
			std::println(std::clog, "Create '{}' and upgrade '{}' flags are set in one command.", CreateFlag, UpgradeFlag);
		}
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
		std::println("Pony Engine File Resource Manifest Generator v{}.{}.{}.{}",
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
		std::println("\nGenerates a text file resource manifest.");
		std::println("\nUsage:");
		std::println("\tponyfrmg <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>             Input manifest file.");
		std::println("\nOptions:");
		std::println("\t--create            Create new file.");
		std::println("\t--add <resource>    Add resource to manifest.");
		std::println("\t                    <resource> format: '<id>,<type>,<path>'.");
		std::println("\t--remove <id>       Remove resource from manifest.");
		std::println("\t--upgrade           Upgrade manifest to the last version.");
		std::println("\t--version           Display version information and exit.");
		std::println("\t--verbose           Enable verbose output.");
		std::println("\t--help              Display this help message and exit.");
		std::println();
	}
}

toml::table ReadManifest()
{
	if (Verbose) [[unlikely]]
	{
		std::println("File: '{}'.", FilePath);
	}

	if (Create)
	{
		if (Verbose) [[unlikely]]
		{
			std::println("Creating new manifest.");
		}

		auto manifest = toml::table();
		manifest.insert(SchemaPropertyName, SchemaV0);
		return manifest;
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Reading manifest.");
	}

	toml::table manifest = toml::parse_file(GetInputPath().c_str());

	const std::optional<std::string_view> schema = manifest[SchemaPropertyName].value<std::string_view>();
	if (!schema) [[unlikely]]
	{
		throw std::invalid_argument("Reading - No schema property found or it's invalid");
	}

	if (schema == SchemaV0)
	{
		ValidateManifestV0(manifest);
		return manifest;
	}

	if (!Upgrade) [[unlikely]]
	{
		throw std::invalid_argument("Reading - Manifest is old version and upgrade flag isn't set");
	}

	// In the future, it may have upgraders here

	throw std::invalid_argument("Reading - Invalid schema");
}

std::filesystem::path GetInputPath()
{
	return std::filesystem::path(FilePath).lexically_normal();
}

void ValidateManifestV0(const toml::table& manifest)
{
	if (const toml::node_view resourcesProperty = manifest[ResourcesPropertyName]) [[likely]]
	{
		if (const toml::array* const resources = resourcesProperty.as_array()) [[likely]]
		{
			for (std::size_t i = 0; i < resources->size(); ++i)
			{
				if (const toml::table* const table = (*resources)[i].as_table()) [[likely]]
				{
					const std::optional<std::string_view> resourceId = (*table)[IdPropertyName].value<std::string_view>();
					if (!resourceId) [[unlikely]]
					{
						throw std::invalid_argument("Reading - Resource element doesn't have property 'id'");
					}

					if (FindResource(*resources, *resourceId, "Reading") != i) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Reading - Resource element duplicate found: id = '{}'", *resourceId));
					}
				}
				else [[unlikely]]
				{
					throw std::invalid_argument("Reading - Invalid resource element");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Reading - Invalid resources array");
		}
	}
}

void RemoveResources(toml::table& manifest)
{
	if (toml::array* const resources = manifest[ResourcesPropertyName].as_array()) [[likely]]
	{
		for (const RemoveCommand& removeCommand : RemoveCommands)
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Removing resource. ID: '{}'.", removeCommand.id);
			}

			if (const std::optional<std::size_t> resourceIndex = FindResource(*resources, removeCommand.id, "Removing")) [[likely]]
			{
				resources->erase(resources->cbegin() + *resourceIndex);
			}
			else if (Verbose) [[unlikely]]
			{
				std::println("Resource not found");
			}
		}
	}
}

void AddResources(toml::table& manifest)
{
	toml::array* const resources = GetOrCreateResourceArray(manifest);

	for (const AddCommand& addCommand : AddCommands)
	{
		if (Verbose) [[unlikely]]
		{
			std::println("Adding resource. ID: '{}'; Type: '{}'; Path: '{}'.", addCommand.id, addCommand.type, addCommand.path);
		}

		if (FindResource(*resources, addCommand.id, "Adding")) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Adding - Resource element duplicate found: id = '{}'", addCommand.id));
		}

		resources->push_back(toml::table
		{
			{ IdPropertyName, addCommand.id },
			{ TypePropertyName, addCommand.type },
			{ PathPropertyName, addCommand.path }
		});
	}
}

void SaveToFile(const toml::table& manifest)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Saving to file.");
	}

	auto file = std::ofstream(GetOutputPath(), std::ios::trunc | std::ios::binary);
	if (!file) [[unlikely]]
	{
		throw std::runtime_error("Saving - Failed to create output file stream");
	}

	file << manifest << '\n';
}

std::filesystem::path GetOutputPath()
{
	const std::filesystem::path path = std::filesystem::path(FilePath).lexically_normal();
	std::filesystem::create_directories(path.parent_path());

	return path;
}

std::optional<std::size_t> FindResource(const toml::array& resources, const std::string_view id, const std::string_view stage)
{
	for (std::size_t i = 0; i < resources.size(); ++i)
	{
		if (const toml::table* const table = resources[i].as_table()) [[likely]]
		{
			const std::optional<std::string_view> resourceId = (*table)[IdPropertyName].value<std::string_view>();
			if (!resourceId) [[unlikely]]
			{
				throw std::invalid_argument(std::format("{} - Resource element doesn't have property 'id'", stage));
			}

			if (resourceId == id)
			{
				return i;
			}
		}
		else [[unlikely]]
		{
			throw std::invalid_argument(std::format("{} - Invalid resource element", stage));
		}
	}

	return std::nullopt;
}

toml::array* GetOrCreateResourceArray(toml::table& manifest)
{
	if (toml::array* const resources = manifest[ResourcesPropertyName].as_array())
	{
		return resources;
	}

	return manifest.insert(ResourcesPropertyName, toml::array()).first->second.as_array();
}
