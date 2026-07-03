/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "toml++/toml.hpp"

#define SCHEMA_BASE "PonyEngine/Manifest/Resource/Pack/"

import std;

constexpr std::string_view PackOutputFlag = "-po";
constexpr std::string_view ManifestOutputFlag = "-mo";
constexpr std::string_view RootPathFlag = "-r";
constexpr std::string_view SizeTFlag = "--size-t";
constexpr std::string_view BigEndianFlag = "--big-endian";
constexpr std::string_view VersionFlag = "--version";
constexpr std::string_view HelpFlag = "--help";
constexpr std::string_view VerboseFlag = "--verbose";

constexpr std::string_view SchemaPropertyName = "schema";
constexpr std::string_view PackPathPropertyName = "pack";
constexpr std::string_view ResourcesPropertyName = "resources";
constexpr std::string_view IdPropertyName = "id";
constexpr std::string_view TypePropertyName = "type";
constexpr std::string_view PathPropertyName = "path";

constexpr std::string_view SchemaV0 = SCHEMA_BASE "v0";

constexpr std::string_view ManifestExtension = ".pprm";
constexpr std::string_view MagicHeader = "PonyEnginePRM";

std::string_view Input = std::string_view();
std::string_view PackOutput = std::string_view();
std::string_view ManifestOutput = std::string_view();
std::string_view RootPath = std::string_view();
std::uintmax_t SizeTSize = 0uz;
bool BigEndian = false;
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
std::vector<char> GenerateData(const toml::table& manifest);
[[nodiscard("Pure function")]]
std::vector<char> GenerateDataV0(const toml::table& manifest);
[[nodiscard("Pure function")]]
std::string_view GetResourcePropertyValue(const toml::table& table, std::string_view propertyName, std::string_view id = std::string_view());
void PushBigSize(std::vector<char>& data, std::uintmax_t size);
void PushSmallSize(std::vector<char>& data, std::size_t size, std::string_view propertyName);

void SaveManifest(std::span<const char> manifest);

[[nodiscard("Pure function")]]
std::filesystem::path GetInputPath();
[[nodiscard("Pure function")]]
std::filesystem::path GetPackOutputPath();
[[nodiscard("Pure function")]]
std::filesystem::path GetManifestOutputPath();
[[nodiscard("Pure function")]]
std::filesystem::path GetResourcePath(std::string_view path);

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

		if (arg == PackOutputFlag) [[likely]]
		{
			if (!PackOutput.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Pack output flag '{}' set multiple times", PackOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing path after pack output flag '{}'", PackOutputFlag));
			}

			PackOutput = argv[i];
		}
		else if (arg == ManifestOutputFlag) [[likely]]
		{
			if (!ManifestOutput.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Manifest output flag '{}' set multiple times", ManifestOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing path after manifest output flag '{}'", ManifestOutputFlag));
			}

			ManifestOutput = argv[i];
		}
		else if (arg == RootPathFlag)
		{
			if (!RootPath.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Root path flag '{}' set multiple times", ManifestOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing path after root path flag '{}'", ManifestOutputFlag));
			}

			RootPath = argv[i];
		}
		else if (arg == SizeTFlag) [[likely]]
		{
			if (SizeTSize != 0u) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - size_t flag '{}' set multiple times", SizeTFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Missing size after size_t flag '{}'", SizeTFlag));
			}

			const std::string_view serializedSize = argv[i];
			auto [ptr, ec] = std::from_chars(serializedSize.data(), serializedSize.data() + serializedSize.size(), SizeTSize);
			if (ec != std::errc() || SizeTSize == 0u) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Invalid size after size_t flag '{}'", SizeTFlag));
			}
			if (SizeTSize > sizeof(std::uintmax_t)) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Parsing - Too great size after size_t flag '{}', it can't be greater than std::uintmax_t of the host platform", SizeTFlag));
			}
		}
		else if (arg == BigEndianFlag)
		{
			if (BigEndian) [[unlikely]]
			{
				std::println(std::clog, "Big endian flag '{}' set multiple times.", BigEndianFlag);
			}

			BigEndian = true;
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
		else [[likely]]
		{
			if (!Input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Parsing - Input path set multiple times");
			}

			Input = arg;
		}
	}

	const bool hasOutput = !PackOutput.empty() || !ManifestOutput.empty();
	if (hasOutput) [[likely]]
	{
		if (PackOutput.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Parsing - No pack output path");
		}
		if (ManifestOutput.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Parsing - No manifest output path");
		}
	}
	
	if (hasOutput && Input.empty()) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - No input path");
	}
	if (!Input.empty() && !hasOutput) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - No output path");
	}

	if (!RootPath.empty() && Input.empty()) [[unlikely]]
	{
		std::println(std::clog, "Root path flag '{}' set but input isn't.", RootPathFlag);
	}

	if (hasOutput && SizeTSize == 0u) [[unlikely]]
	{
		throw std::invalid_argument("Parsing - No size_t size");
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
		std::println("Pony Engine Pack Resource Manifest Compiler v{}.{}.{}.{}",
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
		std::println("\nCompiles a text pack resource manifest into a binary pack resource manifest and pack data.");
		std::println("\nUsage:");
		std::println("\tponyprmc <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>          Input manifest file.");
		std::println("\nOptions:");
		std::println("\t-po <output>     Output pack data file.");
		std::println("\t-mo <output>     Output manifest file. The extension must be '.pprm'.");
		std::println("\t-r <path>        Root path of resources in the source manifest.");
		std::println("\t                 If not set, the working directory is used as a root path.");
		std::println("\t--size-t         std::size_t size of a target platform.");
		std::println("\t--big-endian     Must be set if the target platform has big-endian memory; otherwise don't set it.");
		std::println("\t--version        Display version information and exit.");
		std::println("\t--verbose        Enable verbose output.");
		std::println("\t--help           Display this help message and exit.");
		std::println();
	}
}

void Compile()
{
	if (Input.empty() || PackOutput.empty() || ManifestOutput.empty()) [[unlikely]]
	{
		return;
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Input: '{}'; Pack output: '{}'; Manifest output: '{}'; SizeT: '{}'; Big endian: '{}'.", Input, PackOutput, ManifestOutput, SizeTSize, BigEndian);
	}

	const toml::table manifest = toml::parse_file(GetInputPath().c_str());
	const std::vector<char> data = GenerateData(manifest);
	SaveManifest(data);
}

[[nodiscard("Pure function")]]
std::vector<char> GenerateData(const toml::table& manifest)
{
	const std::optional<std::string_view> schema = manifest[SchemaPropertyName].value<std::string_view>();
	if (!schema) [[unlikely]]
	{
		throw std::invalid_argument("Compiling - No schema property found or it's invalid");
	}

	if (schema == SchemaV0) [[likely]]
	{
		return GenerateDataV0(manifest);
	}

	throw std::invalid_argument(std::format("Compiling - Unsupported schema '{}'", *schema));
}

[[nodiscard("Pure function")]]
std::vector<char> GenerateDataV0(const toml::table& manifest)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Generating Data V0.");
	}

	std::vector<char> data;

	const std::optional<std::string_view> packPath = manifest[PackPathPropertyName].value<std::string_view>();
	if (!packPath) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Compiling - Pack manifest doesn't have property '{}'", PackPathPropertyName));
	}
	if (Verbose) [[unlikely]]
	{
		std::println("Runtime pack path: '{}'.", *packPath);
	}
	PushSmallSize(data, packPath->size(), PackPathPropertyName);
	data.append_range(*packPath);

	auto pack = std::ofstream(GetPackOutputPath(), std::ios::trunc | std::ios::binary);
	if (!pack) [[unlikely]]
	{
		throw std::runtime_error("Compiling - Failed to create pack output file stream");
	}

	if (const toml::node_view resourcesProperty = manifest[ResourcesPropertyName]) [[likely]]
	{
		if (const toml::array* const resources = resourcesProperty.as_array()) [[likely]]
		{
			std::vector<std::string_view> ids;
			ids.reserve(resources->size());

			const std::uintmax_t maxPackSize = sizeof(std::uintmax_t) > SizeTSize 
				? (std::uintmax_t{1u} << (SizeTSize * 8u)) - 1u
				: std::numeric_limits<std::uintmax_t>::max();
			std::uintmax_t currentPackSize = 0u;

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

					const std::filesystem::path resourceFilePath = GetResourcePath(path);
					auto resourceFile = std::ifstream(resourceFilePath, std::ios::binary);
					if (!resourceFile) [[unlikely]]
					{
						throw std::runtime_error(std::format("Compiling - Failed to open resource '{}' file stream", id));
					}
					const std::uintmax_t resourceSize = std::filesystem::file_size(resourceFilePath);
					if (resourceSize > maxPackSize - currentPackSize)
					{
						throw std::runtime_error(std::format("Compiling - Output pack is too big for the target platform", id));
					}
					pack << resourceFile.rdbuf();
					const std::uintmax_t resourceOffset = currentPackSize;
					currentPackSize += resourceSize;

					PushBigSize(data, resourceOffset);
					PushBigSize(data, resourceSize);
					PushSmallSize(data, id.size(), IdPropertyName);
					PushSmallSize(data, type.size(), TypePropertyName);
					data.append_range(id);
					data.append_range(type);

					ids.push_back(id);
				}
				else [[unlikely]]
				{
					throw std::invalid_argument("Compiling - Invalid resource element");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Compiling - Invalid resources array");
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

void PushBigSize(std::vector<char>& data, const std::uintmax_t size)
{
	for (std::size_t i = 0uz; i < SizeTSize; ++i)
	{
		const std::byte byte = BigEndian
			? static_cast<std::byte>((size >> ((SizeTSize - 1u - i) * 8u)) & 0xFFu)
			: static_cast<std::byte>((size >> (i * 8u)) & 0xFFu);
		data.push_back(std::bit_cast<char>(byte));
	}
}

void PushSmallSize(std::vector<char>& data, const std::size_t size, const std::string_view propertyName)
{
	if (size > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Compiling - Value of property '{}' is too long: Length = '{}', Max = '{}'",
			propertyName, size, std::numeric_limits<std::uint8_t>::max()));
	}

	data.push_back(std::bit_cast<char>(static_cast<std::uint8_t>(size)));
}

void SaveManifest(const std::span<const char> manifest)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Saving to file.");
	}

	auto file = std::ofstream(GetManifestOutputPath(), std::ios::trunc | std::ios::binary);
	if (!file) [[unlikely]]
	{
		throw std::runtime_error("Saving - Failed to create manifest output file stream");
	}

	file << MagicHeader << std::string_view(manifest);
}

std::filesystem::path GetInputPath()
{
	return std::filesystem::path(Input).lexically_normal();
}

std::filesystem::path GetPackOutputPath()
{
	const auto path = std::filesystem::absolute(std::filesystem::path(PackOutput).lexically_normal());
	std::filesystem::create_directories(path.parent_path());

	return path;
}

std::filesystem::path GetManifestOutputPath()
{
	const auto path = std::filesystem::absolute(std::filesystem::path(ManifestOutput).lexically_normal());
	if (path.extension() != ManifestExtension) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Saving - Invalid file format. Must be '{}'", ManifestExtension));
	}
	std::filesystem::create_directories(path.parent_path());

	return path;
}

std::filesystem::path GetResourcePath(const std::string_view path)
{
	return (std::filesystem::path(RootPath) / path).lexically_normal();
}
