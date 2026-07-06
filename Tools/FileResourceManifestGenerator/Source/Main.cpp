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
struct Command final
{
	std::string_view filePath = std::string_view();
	std::vector<AddCommand> addCommands;
	std::vector<RemoveCommand> removeCommands;
	bool create = false;
	bool upgrade = false;
	bool showVersion = false;
	bool showHowToUse = false;
	bool showHelp = false;
	bool verbose = false;
};

[[nodiscard("Pure function")]]
Command ParseCommandLine(int argc, const char* const argv[]);

void PrintVersion(const Command& command);
void PrintHowToUse(const Command& command);
void PrintHelp(const Command& command);

void Execute(const Command& command);
[[nodiscard("Pure function")]]
toml::table CreateOrReadManifest(const Command& command);
[[nodiscard("Pure function")]]
toml::table CreateManifest(const Command& command);
[[nodiscard("Pure function")]]
toml::table ReadManifest(const Command& command);
void ValidateManifestV0(const toml::table& manifest);
void RemoveResources(const Command& command, toml::table& manifest);
void AddResources(const Command& command, toml::table& manifest);

void SaveToFile(const Command& command, const toml::table& manifest);

[[nodiscard("Pure function")]]
std::optional<std::size_t> FindResource(const toml::array& resources, std::string_view id);
[[nodiscard("Pure function")]]
toml::array* GetOrCreateResourceArray(toml::table& manifest);

int main(const int argc, const char* const argv[])
{
	try
	{
		const Command command = ParseCommandLine(argc, argv);
		PrintVersion(command);
		PrintHowToUse(command);
		PrintHelp(command);
		Execute(command);
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

		if (arg == CreateFlag)
		{
			if (command.create)
			{
				std::println(std::clog, "Create flag '{}' set multiple times.", CreateFlag);
			}

			command.create = true;
		}
		else if (arg == AddFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing resource description after add flag '{}'", AddFlag));
			}

			const std::string_view resource = argv[i];
			const std::size_t firstCommaIndex = resource.find(',');
			const std::size_t secondCommaIndex = resource.find(',', firstCommaIndex + 1uz);
			const std::size_t thirdCommaIndex = resource.find(',', secondCommaIndex + 1uz);
			if (firstCommaIndex == std::string_view::npos || secondCommaIndex == std::string_view::npos || thirdCommaIndex != std::string_view::npos) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Invalid object to add = '{}'", resource));
			}

			command.addCommands.push_back(AddCommand
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
				throw std::invalid_argument(std::format("Missing id after remove flag '{}'", RemoveFlag));
			}

			command.removeCommands.push_back(RemoveCommand{.id = argv[i]});
		}
		else if (arg == UpgradeFlag)
		{
			if (command.upgrade) [[unlikely]]
			{
				std::println(std::clog, "Upgrade flag '{}' set multiple times.", UpgradeFlag);
			}

			command.upgrade = true;
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
		else
		{
			if (!command.filePath.empty()) [[unlikely]]
			{
				throw std::invalid_argument("File path set multiple times");
			}

			command.filePath = arg;
		}
	}

	const bool modify = command.create || command.upgrade || !command.addCommands.empty() || !command.removeCommands.empty();
	if (modify && command.filePath.empty()) [[unlikely]]
	{
		throw std::invalid_argument("File path isn't set");
	}

	if (command.create)
	{
		if (!command.removeCommands.empty()) [[unlikely]]
		{
			std::println(std::clog, "Create '{}' and remove '{}' flags are set in one command.", CreateFlag, RemoveFlag);
		}
		if (command.upgrade) [[unlikely]]
		{
			std::println(std::clog, "Create '{}' and upgrade '{}' flags are set in one command.", CreateFlag, UpgradeFlag);
		}
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
		std::println("Pony Engine File Resource Manifest Generator v{}.{}.{}.{}",
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

void Execute(const Command& command)
{
	if (command.filePath.empty()) [[unlikely]]
	{
		return;
	}

	toml::table manifest = CreateOrReadManifest(command);
	RemoveResources(command, manifest);
	AddResources(command, manifest);

	SaveToFile(command, manifest);
}

toml::table CreateOrReadManifest(const Command& command)
{
	if (command.verbose) [[unlikely]]
	{
		std::println("File: '{}'.", command.filePath);
	}

	if (command.create)
	{
		return CreateManifest(command);
	}

	return ReadManifest(command);
}

toml::table CreateManifest(const Command& command)
{
	if (command.verbose) [[unlikely]]
	{
		std::println("Creating new manifest.");
	}

	auto manifest = toml::table();
	manifest.insert(SchemaPropertyName, SchemaV0);

	return manifest;
}

toml::table ReadManifest(const Command& command)
{
	if (command.verbose) [[unlikely]]
	{
		std::println("Reading manifest.");
	}

	const toml::table manifest = toml::parse_file(command.filePath);

	const std::optional<std::string_view> schema = manifest[SchemaPropertyName].value<std::string_view>();
	if (!schema) [[unlikely]]
	{
		throw std::invalid_argument("No schema property found or it's invalid");
	}

	if (schema == SchemaV0)
	{
		if (command.verbose) [[unlikely]]
		{
			std::println("Manifest has schema V0. It's the newest schema.");
		}

		ValidateManifestV0(manifest);
		return manifest;
	}

	if (!command.upgrade) [[unlikely]]
	{
		throw std::invalid_argument("Manifest has old version and upgrade flag isn't set");
	}

	// In the future, it may have upgraders here

	throw std::invalid_argument("Invalid schema");
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
						throw std::invalid_argument(std::format("Resource element doesn't have property '{}'", IdPropertyName));
					}

					if (FindResource(*resources, *resourceId) != i) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource element duplicate found: id = '{}'", *resourceId));
					}

					if (!(*table)[TypePropertyName].value<std::string_view>()) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource '{}' doesn't have property '{}'", *resourceId, TypePropertyName));
					}
					if (!(*table)[PathPropertyName].value<std::string_view>()) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource '{}' doesn't have property '{}'", *resourceId, PathPropertyName));
					}
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

void RemoveResources(const Command& command, toml::table& manifest)
{
	if (toml::array* const resources = manifest[ResourcesPropertyName].as_array()) [[likely]]
	{
		for (const RemoveCommand& removeCommand : command.removeCommands)
		{
			if (command.verbose) [[unlikely]]
			{
				std::println("Removing resource. ID: '{}'.", removeCommand.id);
			}

			if (const std::optional<std::size_t> resourceIndex = FindResource(*resources, removeCommand.id)) [[likely]]
			{
				resources->erase(resources->cbegin() + *resourceIndex);
			}
			else if (command.verbose) [[unlikely]]
			{
				std::println("Resource not found");
			}
		}
	}
}

void AddResources(const Command& command, toml::table& manifest)
{
	toml::array* const resources = GetOrCreateResourceArray(manifest);

	for (const AddCommand& addCommand : command.addCommands)
	{
		if (command.verbose) [[unlikely]]
		{
			std::println("Adding resource. ID: '{}'; Type: '{}'; Path: '{}'.", addCommand.id, addCommand.type, addCommand.path);
		}

		if (FindResource(*resources, addCommand.id)) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Tried to add resource element duplicate: id = '{}'", addCommand.id));
		}

		if (!std::filesystem::path(addCommand.path).is_relative()) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Not relative path: id = '{}', path = '{}'", addCommand.id, addCommand.path));
		}

		resources->push_back(toml::table
		{
			{ IdPropertyName, addCommand.id },
			{ TypePropertyName, addCommand.type },
			{ PathPropertyName, addCommand.path }
		});
	}
}

void SaveToFile(const Command& command, const toml::table& manifest)
{
	if (command.verbose) [[unlikely]]
	{
		std::println("Saving to file.");
	}

	const std::filesystem::path path = std::filesystem::absolute(std::filesystem::path(command.filePath).lexically_normal());
	std::filesystem::create_directories(path.parent_path());

	auto file = std::ofstream(path, std::ios::trunc);
	if (!file) [[unlikely]]
	{
		throw std::runtime_error("Failed to create output file stream");
	}

	file << manifest << '\n';
}

std::optional<std::size_t> FindResource(const toml::array& resources, const std::string_view id)
{
	for (std::size_t i = 0; i < resources.size(); ++i)
	{
		if (const toml::table* const table = resources[i].as_table()) [[likely]]
		{
			const std::optional<std::string_view> resourceId = (*table)[IdPropertyName].value<std::string_view>();
			if (!resourceId) [[unlikely]]
			{
				throw std::invalid_argument("Resource element doesn't have property 'id'");
			}

			if (resourceId == id)
			{
				return i;
			}
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource element");
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
