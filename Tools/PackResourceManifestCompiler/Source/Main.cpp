/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <cassert>

#include "toml++/toml.hpp"

#define SCHEMA_BASE "PonyEngine/Manifest/Resource/Pack/"

import std;

constexpr std::string_view PackOutputFlag = "-po";
constexpr std::string_view ManifestOutputFlag = "-mo";
constexpr std::string_view DepFileFlag = "-d";
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

struct Command final
{
	std::string_view input = std::string_view();
	std::string_view packOutput = std::string_view();
	std::string_view manifestOutput = std::string_view();
	std::string_view depFile = std::string_view();
	std::string_view root = std::string_view();
	std::uintmax_t sizeTSize = 0uz;
	bool bigEndian = false;
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

void Compile(const Command& command);
[[nodiscard("Pure function")]]
std::uint32_t GetManifestVersion(const toml::table& manifest);
void CompileV0(const Command& command, const toml::table& source);
[[nodiscard("Pure function")]]
std::string_view GetRuntimePackPath(const Command& command, const toml::table& source, std::string_view propertyName);
[[nodiscard("Pure function")]]
std::string_view GetResourceID(const toml::table& table, std::string_view propertyName);
[[nodiscard("Pure function")]]
std::string_view GetResourcePropertyValue(const toml::table& table, std::string_view propertyName, std::string_view id);
[[nodiscard("Pure function")]]
std::filesystem::path GetResourcePathRoot(const Command& command);
[[nodiscard("Pure function")]]
std::uintmax_t GetMaxSize(const Command& command) noexcept;
void PushBigSize(std::ofstream& stream, std::uintmax_t size, const Command& command);
void PushSmallSize(std::ofstream& stream, std::size_t size, std::string_view propertyName);

[[nodiscard("Pure function")]]
std::filesystem::path GetPackPath(std::string_view path);
[[nodiscard("Pure function")]]
std::ofstream CreatePackStream(const std::filesystem::path& path);
[[nodiscard("Pure function")]]
std::filesystem::path GetManifestPath(std::string_view path);
[[nodiscard("Pure function")]]
std::ofstream CreateManifestStream(const std::filesystem::path& path);

[[nodiscard("Pure function")]]
std::ofstream CreateDepStream(std::string_view path);
void AddTargetsToDepStream(std::ofstream& depFile, const std::filesystem::path& packPath, const std::filesystem::path& manifestPath);
void AddDependencyToDepStream(std::ofstream& depFile, const std::filesystem::path& path);
void FinishDepStreamDependencyList(std::ofstream& depFile);
[[nodiscard("Pure function")]]
std::string ConvertPathToDepPath(const std::filesystem::path& path);

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

[[nodiscard("Pure function")]]
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

		if (arg == PackOutputFlag) [[likely]]
		{
			if (!command.packOutput.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Pack output flag '{}' set multiple times", PackOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after pack output flag '{}'", PackOutputFlag));
			}

			command.packOutput = argv[i];
		}
		else if (arg == ManifestOutputFlag) [[likely]]
		{
			if (!command.manifestOutput.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Manifest output flag '{}' set multiple times", ManifestOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after manifest output flag '{}'", ManifestOutputFlag));
			}

			command.manifestOutput = argv[i];
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
		else if (arg == RootPathFlag)
		{
			if (!command.root.empty()) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Root path flag '{}' set multiple times", ManifestOutputFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after root path flag '{}'", ManifestOutputFlag));
			}

			command.root = argv[i];
		}
		else if (arg == SizeTFlag) [[likely]]
		{
			if (command.sizeTSize != 0u) [[unlikely]]
			{
				throw std::invalid_argument(std::format("sizeof(std::size_t) flag '{}' set multiple times", SizeTFlag));
			}

			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing size after size_t flag '{}'", SizeTFlag));
			}

			const std::string_view serializedSize = argv[i];
			auto [ptr, ec] = std::from_chars(serializedSize.data(), serializedSize.data() + serializedSize.size(), command.sizeTSize);
			if (ec != std::errc() || command.sizeTSize == 0u) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Invalid size after size_t flag '{}'", SizeTFlag));
			}
			if (command.sizeTSize > sizeof(std::uintmax_t)) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Too great size after size_t flag '{}', it can't be greater than std::uintmax_t of the host platform", SizeTFlag));
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

	const bool hasOutput = !command.packOutput.empty() || !command.manifestOutput.empty();
	if (hasOutput) [[likely]]
	{
		if (command.packOutput.empty()) [[unlikely]]
		{
			throw std::invalid_argument("No pack output path");
		}
		if (command.manifestOutput.empty()) [[unlikely]]
		{
			throw std::invalid_argument("No manifest output path");
		}
	}
	
	if (hasOutput && command.input.empty()) [[unlikely]]
	{
		throw std::invalid_argument("No input path");
	}
	if (!command.input.empty() && !hasOutput) [[unlikely]]
	{
		throw std::invalid_argument("No output path");
	}

	if (!command.root.empty() && command.input.empty()) [[unlikely]]
	{
		std::println(std::clog, "Root path flag '{}' set but input isn't.", RootPathFlag);
	}

	if (hasOutput && command.sizeTSize == 0u) [[unlikely]]
	{
		throw std::invalid_argument("No std::size_t size");
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
		std::println("Pony Engine Pack Resource Manifest Compiler v{}.{}.{}.{}",
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
		std::println("\nCompiles a text pack resource manifest into a binary pack resource manifest and pack data.");
		std::println("\nUsage:");
		std::println("\tponyprmc <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>          Input manifest file.");
		std::println("\nOptions:");
		std::println("\t-po <output>     Output pack data file.");
		std::println("\t-mo <output>     Output manifest file. The extension must be '.pprm'.");
		std::println("\t-r <path>        Root path of resources in the source manifest.");
		std::println("\t                 If set, it must be absolute.");
		std::println("\t                 If not set, the input manifest directory is used as a root.");
		std::println("\t--size-t         std::size_t size of a target platform. Can't be greater than host platform std::uintmax_t.");
		std::println("\t--big-endian     Must be set if the target platform has big-endian memory; otherwise don't set it.");
		std::println("\t--version        Display version information and exit.");
		std::println("\t--verbose        Enable verbose output.");
		std::println("\t--help           Display this help message and exit.");
		std::println();
	}
}

void Compile(const Command& command)
{
	if (command.input.empty() || command.packOutput.empty() || command.manifestOutput.empty()) [[unlikely]]
	{
		return;
	}

	if (command.verbose) [[unlikely]]
	{
		std::println("Input: '{}'; Pack output: '{}'; Manifest output: '{}'; std::size_t size: '{}'; Big endian: '{}'.", 
			command.input, command.packOutput, command.manifestOutput, command.sizeTSize, command.bigEndian);
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
		std::println("Generating Data V0.");
	}

	const std::filesystem::path packPath = GetPackPath(command.packOutput);
	const std::filesystem::path manifestPath = GetManifestPath(command.manifestOutput);
	const std::filesystem::path rootPath = GetResourcePathRoot(command);
	std::ofstream pack = CreatePackStream(packPath);
	std::ofstream manifest = CreateManifestStream(manifestPath);
	std::ofstream depFile = CreateDepStream(command.depFile);
	AddTargetsToDepStream(depFile, packPath, manifestPath);

	const std::string_view runtimePackPath = GetRuntimePackPath(command, source, PackPathPropertyName);
	PushSmallSize(manifest, runtimePackPath.size(), PackPathPropertyName);
	manifest << runtimePackPath;

	if (const toml::node_view resourcesProperty = source[ResourcesPropertyName]) [[likely]]
	{
		if (const toml::array* const resources = resourcesProperty.as_array()) [[likely]]
		{
			std::vector<std::string_view> ids;
			ids.reserve(resources->size());

			const std::uintmax_t maxPackSize = GetMaxSize(command);
			std::uintmax_t currentPackSize = 0u;

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

					const std::filesystem::path resourceFilePath = (rootPath / path).lexically_normal();
					auto resourceFile = std::ifstream(resourceFilePath, std::ios::binary);
					if (!resourceFile) [[unlikely]]
					{
						throw std::runtime_error(std::format("Failed to open resource '{}' file stream", id));
					}
					const std::uintmax_t resourceSize = std::filesystem::file_size(resourceFilePath);
					if (resourceSize > maxPackSize - currentPackSize) [[unlikely]]
					{
						throw std::runtime_error(std::format("Output pack is too big for the target platform", id));
					}
					pack << resourceFile.rdbuf();
					const std::uintmax_t resourceOffset = currentPackSize;
					currentPackSize += resourceSize;

					PushBigSize(manifest, resourceOffset, command);
					PushBigSize(manifest, resourceSize, command);
					PushSmallSize(manifest, id.size(), IdPropertyName);
					PushSmallSize(manifest, type.size(), TypePropertyName);
					manifest << id << type;

					AddDependencyToDepStream(depFile, resourceFilePath);

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

	FinishDepStreamDependencyList(depFile);
}

std::string_view GetRuntimePackPath(const Command& command, const toml::table& source, const std::string_view propertyName)
{
	const std::optional<std::string_view> runtimePackPath = source[propertyName].value<std::string_view>();
	if (!runtimePackPath) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Pack manifest doesn't have property '{}'", propertyName));
	}

	if (command.verbose) [[unlikely]]
	{
		std::println("Runtime pack path: '{}'.", *runtimePackPath);
	}

	if (!std::filesystem::path(*runtimePackPath).is_relative()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Not relative pack path '{}'", *runtimePackPath));
	}

	return *runtimePackPath;
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

std::filesystem::path GetResourcePathRoot(const Command& command)
{
	if (command.root.empty())
	{
		return std::filesystem::absolute(std::filesystem::path(command.input).lexically_normal()).parent_path();
	}

	const std::filesystem::path root = std::filesystem::path(command.root).lexically_normal();
	if (!root.is_absolute()) [[unlikely]]
	{
		throw std::invalid_argument("Root path isn't absolute");
	}
	if (!std::filesystem::is_directory(root)) [[unlikely]]
	{
		throw std::invalid_argument("Root path isn't directory");
	}

	return root;
}

std::uintmax_t GetMaxSize(const Command& command) noexcept
{
	return sizeof(std::uintmax_t) > command.sizeTSize
		? (std::uintmax_t{1u} << (command.sizeTSize * 8u)) - 1u
		: std::numeric_limits<std::uintmax_t>::max();
}

void PushBigSize(std::ofstream& stream, const std::uintmax_t size, const Command& command)
{
	for (std::uintmax_t i = 0uz; i < command.sizeTSize; ++i)
	{
		const std::byte byte = command.bigEndian
			? static_cast<std::byte>((size >> ((command.sizeTSize - 1u - i) * 8u)) & 0xFFu)
			: static_cast<std::byte>((size >> (i * 8u)) & 0xFFu);
		stream << std::bit_cast<char>(byte);
	}
}

void PushSmallSize(std::ofstream& stream, const std::size_t size, const std::string_view propertyName)
{
	if (size > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Value of property '{}' is too long: Length = '{}', Max = '{}'",
			propertyName, size, std::numeric_limits<std::uint8_t>::max()));
	}

	stream << std::bit_cast<char>(static_cast<std::uint8_t>(size));
}

std::filesystem::path GetPackPath(const std::string_view path)
{
	const std::filesystem::path packPath = std::filesystem::absolute(std::filesystem::path(path).lexically_normal());
	std::filesystem::create_directories(packPath.parent_path());

	return packPath;
}

std::ofstream CreatePackStream(const std::filesystem::path& path)
{
	auto packStream = std::ofstream(path, std::ios::trunc | std::ios::binary);
	if (!packStream) [[unlikely]]
	{
		throw std::runtime_error("Failed to open pack output file for writing");
	}

	return packStream;
}

std::filesystem::path GetManifestPath(const std::string_view path)
{
	const std::filesystem::path manifestPath = std::filesystem::absolute(std::filesystem::path(path).lexically_normal());
	if (manifestPath.extension() != ManifestExtension) [[unlikely]]
	{
		throw std::invalid_argument(std::format("Invalid manifest output file extension, must be '{}'", ManifestExtension));
	}
	std::filesystem::create_directories(manifestPath.parent_path());

	return manifestPath;
}

std::ofstream CreateManifestStream(const std::filesystem::path& path)
{
	auto manifestStream = std::ofstream(path, std::ios::trunc | std::ios::binary);
	if (!manifestStream) [[unlikely]]
	{
		throw std::runtime_error("Failed to open manifest output file for writing");
	}

	manifestStream << MagicHeader;

	return manifestStream;
}

std::ofstream CreateDepStream(const std::string_view path)
{
	if (path.empty())
	{
		return std::ofstream();
	}

	const std::filesystem::path depPath = std::filesystem::absolute(std::filesystem::path(path).lexically_normal());
	std::filesystem::create_directories(depPath.parent_path());

	auto depStream = std::ofstream(depPath, std::ios::trunc);
	if (!depStream)
	{
		throw std::runtime_error("Failed to open dep file for writing");
	}

	return depStream;
}

void AddTargetsToDepStream(std::ofstream& depFile, const std::filesystem::path& packPath, const std::filesystem::path& manifestPath)
{
	assert(packPath.is_absolute() && "Pack path isn't absolute");
	assert(manifestPath.is_absolute() && "Manifest path isn't absolute");

	if (depFile)
	{
		depFile << ConvertPathToDepPath(packPath) << ' ' << ConvertPathToDepPath(manifestPath) << ':';
	}
}

void AddDependencyToDepStream(std::ofstream& depFile, const std::filesystem::path& path)
{
	assert(path.is_absolute() && "Dependency path isn't absolute");

	if (depFile)
	{
		depFile << ' ' << ConvertPathToDepPath(path);
	}
}

void FinishDepStreamDependencyList(std::ofstream& depFile)
{
	if (depFile)
	{
		depFile << '\n';
	}
}

std::string ConvertPathToDepPath(const std::filesystem::path& path)
{
	const std::string targetPath = path.generic_string();
	std::string depPath;
	depPath.reserve(targetPath.size() + 2uz);

	depPath += '"';
	for (const char c : targetPath)
	{
		switch (c)
		{
		case ' ':
			depPath += "\\ ";
			break;
		case '\\':
			depPath += "\\\\";
			break;
		case '#':
			depPath += "\\#";
			break;
		case '$':
			depPath += "$$";
			break;
		case ':':
			depPath += "\\:";
			break;
		default: [[likely]]
			depPath += c;
			break;
		}
	}
	depPath += '"';

	return depPath;
}
