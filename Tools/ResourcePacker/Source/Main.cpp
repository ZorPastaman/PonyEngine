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
import PonyTools.PackManifest;
import PonyTools.Serialization;

/// @brief Parsed manifest command.
struct ManifestCommand final
{
	std::string_view input; /// Input path. Resource list.
	std::string_view params; ///< Path to a data params file.
	std::string_view output; ///< Pack manifest output path.
};
/// @brief Parsed command.
struct Command final
{
	std::string_view params; ///< Path to a data params file.
	std::string_view output; ///< Pack data output path.
	std::vector<ManifestCommand> manifestCommands; ///< Parsed manifest commands.
	std::string_view depFile; ///< Path to a dep file.
	std::size_t sizeTSize = 0uz; ///< Size of std::size_t on a target platform.
	bool bigEndian = false; ///< Is a target platform big-endian?
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
};

/// @brief Pack resource.
struct Resource final
{
	std::string id; ///< Resource ID.
	std::filesystem::path dataPath; ///< Path to a resource data.
	std::filesystem::path loadPath; ///< Path to a resource load.
	std::size_t manifestIndex = std::numeric_limits<std::size_t>::max(); ///< Pack manifest index.
};

/// @brief Pack data parameters.
struct DataParams final
{
	bool deterministic = false; ///< Should the same unique resource list produce the same pack data?
};
/// @brief Pack manifest parameters.
struct ManifestParams final
{
	bool deduplicateTypes = true; ///< Deduplicate types?
	bool deduplicateDataMetas = true; ///< Deduplicate data metas?
	bool deduplicateLoadMetas = true; ///< Deduplicate load metas?
	bool deduplicateRanges = true; ///< Deduplicate ranges?
};

constexpr std::string_view ParamsFlag = "-p"; ///< Parameters flag. The next argument must be a path.
constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view ManifestFlag = "-m"; ///< Manifest flag. The next arguments are resource list, parameters path and pack manifest output path.
constexpr std::string_view DepFileFlag = "-d"; ///< Dep file flag. The next argument must be a path.
constexpr std::string_view SizeTSizeFlag = "--size_t-size"; ///< Target platform std::size_t size flag. The next argument must be an unsigned integer.
constexpr std::string_view BigEndianFlag = "--big-endian"; ///< Target platform big endianness flag.
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view DataParamsSchema = "PonyEngine/Resource/Pack/Data/v0"; ///< Data params schema.
constexpr std::string_view ManifestParamsSchema = "PonyEngine/Resource/Pack/Manifest/v0"; ///< Manifest params schema.
constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name.
constexpr std::string_view DeterministicPropertyName = "deterministic"; ///< Deterministic property name.
constexpr std::string_view DeduplicateTypes = "deduplicateTypes"; ///< Deduplicate types property name.
constexpr std::string_view DeduplicateDataMetas = "deduplicateDataMetas"; ///< Deduplicate data metas property name.
constexpr std::string_view DeduplicateLoadMetas = "deduplicateLoadMetas"; ///< Deduplicate load metas property name.
constexpr std::string_view DeduplicateRanges = "deduplicateRanges"; ///< Deduplicate ranges.

constexpr std::string_view DataMagicWord = "PonyEngineResourceData"; ///< Resource data magic word.
constexpr std::string_view LoadMagicWord = "PonyEngineResourceLoad"; ///< Resource load magic word.
constexpr std::string_view PackManifestMagicWord = "PonyEngineResourcePackManifest"; ///< Pack manifest magic word.

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

/// @brief Makes a pack.
/// @param command Parsed command.
void Pack(const Command& command);
/// @brief Gets manifest resources.
/// @param manifestCommands Parsed manifest commands.
/// @return Manifest resources.
[[nodiscard("Pure function")]]
std::vector<Resource> GetManifestResources(std::span<const ManifestCommand> manifestCommands);
/// @brief Adds the data.
/// @param dataInput Data input file. Must be at a point of a data beginning.
/// @param dataOutput Data output file.
/// @param dataRanges Data ranges cache.
/// @param dataInputPath Data input file path.
/// @param outputOffset Output offset.
/// @return Data range.
[[nodiscard("Pure function")]]
std::pair<std::uintmax_t, std::uintmax_t> AddData(std::ifstream& dataInput, std::ofstream& dataOutput, 
	std::unordered_map<std::filesystem::path, std::pair<std::uintmax_t, std::uintmax_t>>& dataRanges, const std::filesystem::path& dataInputPath,
	std::uintmax_t& outputOffset);

/// @brief Write a dep file.
/// @param command Parsed command.
/// @param resources Resources.
void WriteDepFile(const Command& command, std::span<const Resource> resources);

/// @brief Reads a pack data parameters.
/// @param path Pack data parameters path.
/// @return Pack data parameters.
[[nodiscard("Pure function")]]
DataParams ReadDataParams(std::string_view path);
/// @brief Reads a pack manifest parameters.
/// @param path Pack manifest parameters path.
/// @return Pack manifest parameters.
[[nodiscard("Pure function")]]
ManifestParams ReadManifestParams(std::string_view path);
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

	const std::uint8_t mainParamCount = !command.params.empty() + !command.output.empty() + !command.manifestCommands.empty() + (command.sizeTSize != 0uz);
	if (mainParamCount != 0u && mainParamCount != 4u) [[unlikely]]
	{
		throw std::invalid_argument("Invalid argument set");
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
		std::println("\t-p <path>                              Pack data parameters.");
		std::println("\t-o <path>                              Pack data output path.");
		std::println("\t-m <resource_list> <params> <output>   Pack manifest.");
		std::println("\t-d <path>                              Dep file path.");
		std::println("\t--size_t-size <number>                 Target platform std::size_t size.");
		std::println("\t--big-endian                           If set, target platform is treated as big-endian.");
		std::println("\t--version                              Display version information and exit.");
		std::println("\t--verbose                              Enable verbose output.");
		std::println("\t--help                                 Display this help message and exit.");
		std::println();
	}
}

void Pack(const Command& command)
{
	const DataParams dataParams = ReadDataParams(command.params);

	std::vector<Resource> resources = GetManifestResources(command.manifestCommands);
	if (dataParams.deterministic)
	{
		std::ranges::sort(resources, std::less<std::filesystem::path>{}, &Resource::dataPath);
	}

	std::vector<PonyTools::PackManifest::PackManifest> manifests;
	manifests.reserve(command.manifestCommands.size());
	std::vector<std::ofstream> manifestOutputs;
	manifestOutputs.reserve(command.manifestCommands.size());
	for (const ManifestCommand& manifestCommand : command.manifestCommands)
	{
		const ManifestParams manifestParams = ReadManifestParams(manifestCommand.params);
		manifests.push_back(PonyTools::PackManifest::PackManifest(manifestParams.deduplicateTypes, manifestParams.deduplicateDataMetas,
			manifestParams.deduplicateLoadMetas, manifestParams.deduplicateRanges));
		manifestOutputs.push_back(PonyTools::FileSystem::OpenOutput(manifestCommand.output, std::ios::binary | std::ios::trunc));
	}

	std::ofstream dataOutput = PonyTools::FileSystem::OpenOutput(command.output, std::ios::binary | std::ios::trunc);
	std::unordered_map<std::filesystem::path, std::pair<std::uintmax_t, std::uintmax_t>> dataRanges;

	std::string dataMagicWord;
	dataMagicWord.resize(DataMagicWord.size());
	std::string loadMagicWord;
	loadMagicWord.resize(LoadMagicWord.size());
	std::string typeCache;
	std::vector<std::byte> dataMetaCache;
	std::vector<std::byte> loadMetaCache;
	std::uintmax_t outputOffset = 0u;
	for (const Resource& resource : resources)
	{
		std::ifstream dataInput = PonyTools::FileSystem::OpenInput(resource.dataPath, std::ios::binary);

		dataInput.read(dataMagicWord.data(), dataMagicWord.size());
		if (dataInput.gcount() != dataMagicWord.size() || dataMagicWord != DataMagicWord) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid data magic word at '{}'", resource.dataPath.string()));
		}

		std::uint8_t typeSize;
		dataInput.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize));
		if (dataInput.gcount() != sizeof(typeSize)) [[unlikely]]
		{
			throw std::runtime_error(std::format("No type size at '{}'", resource.dataPath.string()));
		}

		typeCache.resize(typeSize);
		dataInput.read(typeCache.data(), typeCache.size());
		if (dataInput.gcount() != typeCache.size()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type at '{}'", resource.dataPath.string()));
		}

		std::size_t dataMetaSize;
		dataInput.read(reinterpret_cast<char*>(&dataMetaSize), sizeof(dataMetaSize));
		if (dataInput.gcount() != sizeof(dataMetaSize)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid data meta size at '{}'", resource.dataPath.string()));
		}

		dataMetaCache.resize(dataMetaSize);
		dataInput.read(reinterpret_cast<char*>(dataMetaCache.data()), dataMetaCache.size());
		if (dataInput.gcount() != dataMetaCache.size()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid data meta at '{}'", resource.dataPath.string()));
		}

		const std::pair<std::uintmax_t, std::uintmax_t> range = AddData(dataInput, dataOutput, dataRanges, resource.dataPath, outputOffset);

		std::ifstream loadInput = PonyTools::FileSystem::OpenInput(resource.loadPath, std::ios::binary);

		loadInput.read(loadMagicWord.data(), loadMagicWord.size());
		if (loadInput.gcount() != loadMagicWord.size() || loadMagicWord != LoadMagicWord) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid load magic word at '{}'", resource.loadPath.string()));
		}

		std::size_t loadMetaSize;
		loadInput.read(reinterpret_cast<char*>(&loadMetaSize), sizeof(loadMetaSize));
		if (loadInput.gcount() != sizeof(loadMetaSize)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid load meta size at '{}'", resource.loadPath.string()));
		}

		loadMetaCache.resize(loadMetaSize);
		loadInput.read(reinterpret_cast<char*>(loadMetaCache.data()), loadMetaCache.size());
		if (loadInput.gcount() != loadMetaCache.size()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid load meta at '{}'", resource.loadPath.string()));
		}

		PonyTools::PackManifest::PackManifest& manifest = manifests[resource.manifestIndex];
		manifest.AddResource(typeCache, dataMetaCache, loadMetaCache, range, resource.id);
	}

	std::uintmax_t sizeTMaxValue = command.sizeTSize == sizeof(std::uintmax_t)
		? std::numeric_limits<std::uintmax_t>::max()
		: (std::uintmax_t{1u} << (command.sizeTSize * 8u)) - 1u;

	for (std::size_t i = 0uz; i < manifests.size(); ++i)
	{
		const PonyTools::PackManifest::PackManifest& manifest = manifests[i];
		const std::span<const std::string> types = manifest.Types();
		const std::span<const std::vector<std::byte>> dataMetas = manifest.DataMetas();
		const std::span<const std::vector<std::byte>> loadMetas = manifest.LoadMetas();
		const std::span<const std::pair<std::uintmax_t, std::uintmax_t>> ranges = manifest.Ranges();
		const std::span<const PonyTools::PackManifest::PackManifest::Resource> manifestResources = manifest.Resources();

		if (types.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error("Too many types");
		}
		if (dataMetas.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error("Too many data metas");
		}
		if (loadMetas.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error("Too many load metas");
		}
		if (ranges.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error("Too many ranges");
		}
		if (manifestResources.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error("Too many resources");
		}

		std::ofstream& manifestOutput = manifestOutputs[i];

		manifestOutput.write(PackManifestMagicWord.data(), PackManifestMagicWord.size());

		PonyTools::FileSystem::Write(manifestOutput, types.size(), command.sizeTSize, command.bigEndian);
		PonyTools::FileSystem::Write(manifestOutput, dataMetas.size(), command.sizeTSize, command.bigEndian);
		PonyTools::FileSystem::Write(manifestOutput, loadMetas.size(), command.sizeTSize, command.bigEndian);
		PonyTools::FileSystem::Write(manifestOutput, ranges.size(), command.sizeTSize, command.bigEndian);

		for (const std::string_view type : types)
		{
			const std::uint8_t typeSize = static_cast<std::uint8_t>(type.size());
			manifestOutput.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
		}
		for (const std::span<const std::byte> dataMeta : dataMetas)
		{
			if (dataMeta.size() > sizeTMaxValue) [[unlikely]]
			{
				throw std::runtime_error("Too big data meta");
			}
			PonyTools::FileSystem::Write(manifestOutput, dataMeta.size(), command.sizeTSize, command.bigEndian);
		}
		for (const std::span<const std::byte> loadMeta : loadMetas)
		{
			if (loadMeta.size() > sizeTMaxValue) [[unlikely]]
			{
				throw std::runtime_error("Too big load meta");
			}
			PonyTools::FileSystem::Write(manifestOutput, loadMeta.size(), command.sizeTSize, command.bigEndian);
		}
		for (const std::pair<std::uintmax_t, std::uintmax_t>& range : ranges)
		{
			if (range.first > sizeTMaxValue || range.second > sizeTMaxValue) [[unlikely]]
			{
				throw std::runtime_error("Too big range");
			}
			PonyTools::FileSystem::Write(manifestOutput, range.first, command.sizeTSize, command.bigEndian);
			PonyTools::FileSystem::Write(manifestOutput, range.second, command.sizeTSize, command.bigEndian);
		}

		for (const std::string_view type : types)
		{
			manifestOutput.write(type.data(), type.size());
		}
		for (const std::span<const std::byte> dataMeta : dataMetas)
		{
			manifestOutput.write(reinterpret_cast<const char*>(dataMeta.data()), dataMeta.size());
		}
		for (const std::span<const std::byte> loadMeta : loadMetas)
		{
			manifestOutput.write(reinterpret_cast<const char*>(loadMeta.data()), loadMeta.size());
		}

		for (const PonyTools::PackManifest::PackManifest::Resource& manifestResource : manifestResources)
		{
			PonyTools::FileSystem::Write(manifestOutput, manifestResource.typeIndex, command.sizeTSize, command.bigEndian);
			PonyTools::FileSystem::Write(manifestOutput, manifestResource.dataMetaIndex, command.sizeTSize, command.bigEndian);
			PonyTools::FileSystem::Write(manifestOutput, manifestResource.loadMetaIndex, command.sizeTSize, command.bigEndian);
			PonyTools::FileSystem::Write(manifestOutput, manifestResource.rangeIndex, command.sizeTSize, command.bigEndian);
			
			const std::uint8_t idSize = static_cast<std::uint8_t>(manifestResource.id.size());
			manifestOutput.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
			manifestOutput.write(manifestResource.id.data(), idSize);
		}
	}

	WriteDepFile(command, resources);
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

std::pair<std::uintmax_t, std::uintmax_t> AddData(std::ifstream& dataInput, std::ofstream& dataOutput,
	std::unordered_map<std::filesystem::path, std::pair<std::uintmax_t, std::uintmax_t>>& dataRanges, const std::filesystem::path& dataInputPath, std::uintmax_t& outputOffset)
{
	if (const auto position = dataRanges.find(dataInputPath); position != dataRanges.cend())
	{
		return position->second;
	}

	const auto data = std::string(std::istreambuf_iterator<char>(dataInput), std::istreambuf_iterator<char>());
	if (std::numeric_limits<std::uintmax_t>::max() - outputOffset < data.size()) [[unlikely]]
	{
		throw std::runtime_error("Data file is too large");
	}

	dataOutput.write(data.data(), data.size());

	const auto range = std::pair<std::uintmax_t, std::uintmax_t>(outputOffset, data.size());
	outputOffset += data.size();
	return range;
}

void WriteDepFile(const Command& command, const std::span<const Resource> resources)
{
	if (command.depFile.empty()) [[unlikely]]
	{
		std::println(std::clog, "No dep file set - no dep file will be generated");
		return;
	}

	auto depData = PonyTools::DepFile::DepData();
	PonyTools::DepFile::DepRule& depRule = depData.AddRule();

	depRule.AddTarget(std::filesystem::path(command.output));
	depRule.AddDependency(std::filesystem::path(command.params));

	for (const ManifestCommand& manifestCommand : command.manifestCommands)
	{
		depRule.AddTarget(std::filesystem::path(manifestCommand.output));

		auto input = std::filesystem::path(manifestCommand.input);
		if (!depRule.HasDependency(input))
		{
			depRule.AddDependency(std::move(input));
		}
		auto params = std::filesystem::path(manifestCommand.params);
		if (!depRule.HasDependency(params))
		{
			depRule.AddDependency(std::move(params));
		}
	}

	for (const Resource& resource : resources)
	{
		if (!depRule.HasDependency(resource.dataPath))
		{
			depRule.AddDependency(resource.dataPath);
		}
		if (!depRule.HasDependency(resource.loadPath))
		{
			depRule.AddDependency(resource.loadPath);
		}
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Writing to dep file at '{}'.", command.depFile);
	}
	std::ofstream depFile = PonyTools::FileSystem::OpenOutput(command.depFile, std::ios::trunc);
	depData.Write(depFile);
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

ManifestParams ReadManifestParams(std::string_view path)
{
	const toml::table table = ParseParams(path);
	if (table[SchemaPropertyName].value<std::string_view>() != ManifestParamsSchema) [[unlikely]]
	{
		throw std::runtime_error(std::format("Manifest params file at '{}' doesn't have a valid schema", path));
	}

	auto params = ManifestParams{};

	if (const toml::node_view deduplicateTypesProperty = table[DeduplicateTypes])
	{
		if (const std::optional<bool> deduplicateTypes = deduplicateTypesProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting data parameter: deduplicate types = '{}'.", *deduplicateTypes);
			}

			params.deduplicateTypes = *deduplicateTypes;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", DeduplicateTypes, path));
		}
	}
	if (const toml::node_view deduplicateDataMetasProperty = table[DeduplicateDataMetas])
	{
		if (const std::optional<bool> deduplicateDataMetas = deduplicateDataMetasProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting data parameter: deduplicate data metas = '{}'.", *deduplicateDataMetas);
			}

			params.deduplicateDataMetas = *deduplicateDataMetas;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", DeduplicateDataMetas, path));
		}
	}
	if (const toml::node_view deduplicateLoadMetasProperty = table[DeduplicateLoadMetas])
	{
		if (const std::optional<bool> deduplicateLoadMetas = deduplicateLoadMetasProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting load parameter: deduplicate load metas = '{}'.", *deduplicateLoadMetas);
			}

			params.deduplicateLoadMetas = *deduplicateLoadMetas;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", DeduplicateLoadMetas, path));
		}
	}
	if (const toml::node_view deduplicateRangesProperty = table[DeduplicateRanges])
	{
		if (const std::optional<bool> deduplicateRanges = deduplicateRangesProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting data parameter: deduplicate ranges = '{}'.", *deduplicateRanges);
			}

			params.deduplicateRanges = *deduplicateRanges;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", DeduplicateRanges, path));
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
