/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "toml++/toml.hpp"

import std;

import PonyTools.DepFile;

/// @brief Parsed load command.
struct LoadCommand final
{
	std::string_view params; ///< Load params file.
	std::string_view output; ///< Load output file.
};
/// @brief Parsed command.
struct Command final
{
	std::string_view input; ///< Path to an input file.
	std::string_view params; ///< Path to a data params file.
	std::string_view output; ///< Path to an output file.
	std::vector<LoadCommand> loadCommands; ///< Load commands.
	std::string_view depFile; ///< Path to a dep file.
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
};

/// @brief Data parameters.
struct DataParams final
{
	bool removeFinalNewLine = true; ///< Remove final new line?
};
/// @brief Load parameters.
struct LoadParams final
{
	bool directResourceAccess = false; ///< Enable direct resource access?
};

constexpr std::string_view ParamsFlag = "-p"; ///< Parameters flag. The next argument must be a path.
constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view LoadFlag = "-l"; ///< Load flag. The next arguments must be two paths.
constexpr std::string_view DepFileFlag = "-d"; ///< Dep file flag. The next argument must be a path.
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view DataParamsSchema = "PonyEngine/Resource/Text/Data/v0"; ///< Data params schema.
constexpr std::string_view LoadParamsSchema = "PonyEngine/Resource/Text/Load/v0"; ///< Load params schema.
constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name.
constexpr std::string_view RemoveFinalNewLinePropertyName = "removeFinalNewLine"; ///< Remove final new line property name.
constexpr std::string_view DirectResourceAccessPropertyName = "directResourceAccess"; ///< Direct resource access property name.

constexpr std::string_view DataMagicWord = "PonyEngineResourceData"; ///< Resource data magic word.
constexpr std::string_view LoadMagicWord = "PonyEngineResourceLoad"; ///< Resource load magic word.
constexpr std::string_view TextResourceType = "PonyText"; ///< Text resource type.

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

/// @brief Write a dep file.
/// @param command Parsed command.
void WriteDepFile(const Command& command);

/// @brief Compiles a resource.
/// @param command Parsed command.
void Compile(const Command& command);
/// @brief Compiles a resource data.
/// @param inputPath Path to an input asset.
/// @param outputPath Path to an output data.
/// @param params Data parameters.
void CompileData(std::string_view inputPath, std::string_view outputPath, const DataParams& params);
/// @brief Compiles a resource load.
/// @param outputPath Path to an output load.
/// @param params Load parameters.
void CompileLoad(std::string_view outputPath, const LoadParams& params);

/// @brief Opens an input file.
/// @param path File path.
/// @param openMode Open mode.
/// @return Input file stream.
[[nodiscard("Pure function")]]
std::ifstream OpenInput(std::string_view path, std::ios::openmode openMode = 0);
/// @brief Opens an output file.
/// @param path File path.
/// @param openMode Open mode.
/// @return Output file stream.
[[nodiscard("Pure function")]]
std::ofstream OpenOutput(std::string_view path, std::ios::openmode openMode = 0);

/// @brief Reads data parameters.
/// @param path Data parameter file path.
/// @return Data parameters.
[[nodiscard("Pure function")]]
DataParams ReadDataParams(std::string_view path);
/// @brief Reads load parameters.
/// @param path Load parameter file path.
/// @return Load parameters.
[[nodiscard("Pure function")]]
LoadParams ReadLoadParams(std::string_view path);
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

		if (!command.input.empty()) [[likely]]
		{
			WriteDepFile(command);
			Compile(command);
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
		else if (arg == LoadFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path to params after load flag '{}'", LoadFlag));
			}
			const std::string_view loadParams = argv[i];
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path to output after load flag '{}'", LoadFlag));
			}
			const std::string_view loadOutput = argv[i];

			command.loadCommands.push_back(LoadCommand{.params = loadParams, .output = loadOutput});
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
		else
		{
			if (!command.input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Input path set multiple times");
			}

			command.input = arg;
		}
	}

	if (!command.input.empty()) [[likely]]
	{
		if (command.params.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Data params file not set");
		}
		if (command.output.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Data output file not set");
		}
		if (command.loadCommands.empty()) [[unlikely]]
		{
			throw std::invalid_argument("No load command set");
		}
	}
	else if (Verbose) [[unlikely]]
	{
		std::println("No input file set - compilation will be skipped.");
	}

	return command;
}

void PrintVersion(const Command& command)
{
	if (command.showVersion) [[unlikely]]
	{
		std::println("Pony Engine Text Compiler v{}.{}.{}.{}",
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
		std::println("\nCompiles a text asset into a Pony Engine resource.");
		std::println("\nUsage:");
		std::println("\tPonyTextCompiler <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>                          Input asset file path, can be any file.");
		std::println("\nOptions:");
		std::println("\t-p <path>                        Text resource data params file path.");
		std::println("\t-o <path>                        Resource data output file path.");
		std::println("\t-l <params_path> <output_path>   Resource load params and load output file paths.");
		std::println("\t-d <path>                        Dep file path.");
		std::println("\t--version                        Display version information and exit.");
		std::println("\t--verbose                        Enable verbose output.");
		std::println("\t--help                           Display this help message and exit.");
		std::println();
	}
}

void WriteDepFile(const Command& command)
{
	if (command.depFile.empty()) [[unlikely]]
	{
		std::println(std::clog, "No dep file set - no dep file will be generated");
		return;
	}

	auto depData = PonyTools::DepFile::DepData();
	PonyTools::DepFile::DepRule& depRule = depData.AddRule();

	depRule.AddTarget(std::filesystem::path(command.output));
	depRule.AddDependency(std::filesystem::path(command.input));
	depRule.AddDependency(std::filesystem::path(command.params));

	for (const LoadCommand& loadCommand : command.loadCommands)
	{
		depRule.AddTarget(std::filesystem::path(loadCommand.output));
		depRule.AddDependency(std::filesystem::path(loadCommand.params));
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Writing to dep file at '{}'.", command.depFile);
	}
	std::ofstream depFile = OpenOutput(command.depFile, std::ios::trunc);
	depData.Write(depFile);
}

void Compile(const Command& command)
{
	CompileData(command.input, command.output, ReadDataParams(command.params));

	for (const LoadCommand& loadCommand : command.loadCommands)
	{
		CompileLoad(loadCommand.output, ReadLoadParams(loadCommand.params));
	}
}

void CompileData(const std::string_view inputPath, const std::string_view outputPath, const DataParams& params)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Opening data input file at '{}'.", inputPath);
	}
	std::ifstream input = OpenInput(inputPath);

	if (Verbose) [[unlikely]]
	{
		std::println("Opening data output file at '{}'.", outputPath);
	}
	std::ofstream output = OpenOutput(outputPath, std::ios::binary | std::ios::trunc);

	auto data = std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());

	if (params.removeFinalNewLine && data.back() == '\n')
	{
		data.pop_back();
	}

	output.write(DataMagicWord.data(), DataMagicWord.size());

	constexpr std::uint8_t typeSize = TextResourceType.size();
	output.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
	output.write(TextResourceType.data(), typeSize);

	constexpr std::size_t dataMetaSize = 0uz;
	output.write(reinterpret_cast<const char*>(&dataMetaSize), sizeof(dataMetaSize));

	output.write(data.data(), data.size());
}

void CompileLoad(const std::string_view outputPath, const LoadParams& params)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Opening load output file at '{}'.", outputPath);
	}
	std::ofstream output = OpenOutput(outputPath, std::ios::binary | std::ios::trunc);

	output.write(LoadMagicWord.data(), LoadMagicWord.size());

	constexpr std::size_t loadMetaSize = 1uz;
	output.write(reinterpret_cast<const char*>(&loadMetaSize), sizeof(loadMetaSize));
	
	const std::uint8_t directResourceAccess = params.directResourceAccess;
	output.write(reinterpret_cast<const char*>(&directResourceAccess), sizeof(directResourceAccess));
}

std::ifstream OpenInput(const std::string_view path, const std::ios::openmode openMode)
{
	const auto inputPath = std::filesystem::absolute(std::filesystem::path(path)).lexically_normal();
	auto input = std::ifstream(inputPath, openMode);
	if (!input) [[unlikely]]
	{
		throw std::runtime_error(std::format("Failed to open input file at path '{}'", inputPath.string()));
	}

	return input;
}

std::ofstream OpenOutput(const std::string_view path, const std::ios::openmode openMode)
{
	const auto outputPath = std::filesystem::absolute(std::filesystem::path(path)).lexically_normal();
	auto output = std::ofstream(outputPath, openMode);
	if (!output) [[unlikely]]
	{
		throw std::runtime_error(std::format("Failed to open output file at path '{}'", outputPath.string()));
	}

	return output;
}

DataParams ReadDataParams(const std::string_view path)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Reading data parameters from '{}'.", path);
	}

	const toml::table table = ParseParams(path);
	if (table[SchemaPropertyName].value<std::string_view>() != DataParamsSchema) [[unlikely]]
	{
		throw std::runtime_error(std::format("Data params file at '{}' doesn't have a valid schema", path));
	}

	auto params = DataParams{};

	if (const toml::node_view removeFinalNewLineProperty = table[RemoveFinalNewLinePropertyName])
	{
		if (const std::optional<bool> removeFinalNewLine = removeFinalNewLineProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting data parameter: removeFinalNewLine = '{}'.", *removeFinalNewLine);
			}

			params.removeFinalNewLine = *removeFinalNewLine;
		}
		else [[unlikely]]
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", RemoveFinalNewLinePropertyName, path));
		}
	}

	return params;
}

LoadParams ReadLoadParams(const std::string_view path)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Reading load parameters from '{}'.", path);
	}

	const toml::table table = ParseParams(path);
	if (table[SchemaPropertyName].value<std::string_view>() != LoadParamsSchema) [[unlikely]]
	{
		throw std::runtime_error(std::format("Load params file at '{}' doesn't have a valid schema", path));
	}

	auto params = LoadParams{};

	if (const toml::node_view directResourceAccessProperty = table[DirectResourceAccessPropertyName])
	{
		if (const std::optional<bool> directResourceAccess = directResourceAccessProperty.value<bool>()) [[likely]]
		{
			if (Verbose) [[unlikely]]
			{
				std::println("Setting load parameter: directResourceAccess = '{}'.", *directResourceAccess);
			}

			params.directResourceAccess = *directResourceAccess;
		}
		else
		{
			throw std::runtime_error(std::format("Invalid type of property '{}' in '{}', must be bool", RemoveFinalNewLinePropertyName, path));
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
