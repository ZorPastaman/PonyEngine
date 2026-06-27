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

struct Command final
{
	std::string_view input;
	std::string_view output;
};

constexpr std::string_view OutputFlag = "-o";

constexpr std::string_view SchemaPropertyName = "schema";
constexpr std::string_view ResourcesPropertyName = "resources";
constexpr std::string_view IdPropertyName = "id";
constexpr std::string_view TypePropertyName = "type";
constexpr std::string_view PathPropertyName = "path";

constexpr std::string_view SchemaV0 = SCHEMA_BASE "v0";

static constexpr std::string_view ManifestExtension = ".pfrm";
static constexpr std::string_view MagicHeader = "PonyEngineFRM";

[[nodiscard("Pure function")]]
Command ParseCommandLine(int argc, const char* const argv[]);

void ExecuteCommand(const Command& command);
[[nodiscard("Pure function")]]
std::vector<char> GenerateData(const toml::parse_result& manifest);
[[nodiscard("Pure function")]]
std::vector<char> GenerateDataV0(const toml::parse_result& manifest);
[[nodiscard("Pure function")]]
std::string_view GetResourcePropertyValue(const toml::table& table, std::string_view propertyName, std::string_view id = std::string_view());
void PushSize(std::vector<char>& data, std::size_t size, std::string_view propertyName);

void SaveToFile(std::span<const char> data, std::string_view path);

int main(const int argc, const char* const argv[])
{
	try
	{
		const Command command = ParseCommandLine(argc, argv);
		try
		{
			ExecuteCommand(command);
		}
		catch (const std::exception& e)
		{
			std::println(std::cerr, "Executing. Exception of type '{}': '{}'.", typeid(e).name(), e.what());
			return 2;
		}
		catch (...)
		{
			std::println(std::cerr, "Executing. Unexpected exception.");
			return 2;
		}
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Parsing. Exception of type '{}': '{}'.", typeid(e).name(), e.what());
		return 1;
	}
	catch (...)
	{
		std::println(std::cerr, "Parsing. Unexpected exception.");
		return 1;
	}

#ifndef NDEBUG
	std::println("Finished successfully.");
#endif

	return 0;
}

Command ParseCommandLine(const int argc, const char* const argv[])
{
	Command command;

	for (int i = 1; i < argc; ++i)
	{
		const std::string_view arg = argv[i];

		if (arg == OutputFlag)
		{
			if (!command.output.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Output flag set multiple times");
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::runtime_error("Missing path after output flag");
			}

			command.output = argv[i];
		}
		else
		{
			if (!command.input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Input path set multiple times");
			}

			command.input = arg;
		}
	}
	
	if (command.input.empty()) [[unlikely]]
	{
		throw std::invalid_argument("No input path");
	}
	if (command.output.empty()) [[unlikely]]
	{
		throw std::invalid_argument("No output path");
	}

	return command;
}

void ExecuteCommand(const Command& command)
{
#ifndef NDEBUG
	std::println("Executing command. Input: '{}'; Output: '{}'.", command.input, command.output);
#endif

	const toml::parse_result manifest = toml::parse_file(command.input);
	const std::vector<char> data = GenerateData(manifest);
	SaveToFile(data, command.output);
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
#ifndef NDEBUG
		std::println("Generating Data V0.");
#endif

		return GenerateDataV0(manifest);
	}

	throw std::invalid_argument("Unsupported schema");
}

std::vector<char> GenerateDataV0(const toml::parse_result& manifest)
{
	std::vector<char> data;

	if (std::vector<std::string_view> ids; const toml::array* const resources = manifest[ResourcesPropertyName].as_array()) [[likely]]
	{
		for (const toml::node& node : *resources) 
		{
			if (const toml::table* const table = node.as_table()) [[likely]]
			{
				const std::string_view id = GetResourcePropertyValue(*table, IdPropertyName);
				const std::string_view type = GetResourcePropertyValue(*table, TypePropertyName, id);
				const std::string_view path = GetResourcePropertyValue(*table, PathPropertyName, id);
				if (std::ranges::find(ids, id) != ids.cend()) [[unlikely]]
				{
					throw std::invalid_argument(std::format("Resource id '{}' used multiple times", id));
				}

#ifndef NDEBUG
				std::println("Adding resource element. ID: '{}'; Type: '{}'; Path: '{}'.", id, type, path);
#endif

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
				throw std::invalid_argument("Invalid resource element");
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
			throw std::invalid_argument("Resource element doesn't have property 'id'");
		}

		throw std::invalid_argument(std::format("Resource element with id '{}' doesn't have property '{}'", id, propertyName));
	}

	return *property;
}

void PushSize(std::vector<char>& data, const std::size_t size, const std::string_view propertyName)
{
	if (size > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Value of property '{}' is too long: Length = '{}', Max = '{}'", 
			propertyName, size, std::numeric_limits<std::uint8_t>::max()));
	}

	data.push_back(std::bit_cast<char>(static_cast<std::uint8_t>(size)));
}

void SaveToFile(const std::span<const char> data, const std::string_view path)
{
	auto filePath = std::string();
	filePath.reserve(path.size() + ManifestExtension.size());
	filePath.append_range(path);
	filePath.append_range(ManifestExtension);

	auto file = std::ofstream(filePath, std::ios::trunc | std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("Failed to open output file");
	}

	file << MagicHeader << std::string_view(data);
}
