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

/// @brief Parsed command.
struct Command final
{
	std::string_view input; ///< Path to an input file.
	std::string_view params; ///< Path to a params file.
	std::string_view output; ///< Path to an output file.
	std::string_view depFile; ///< Path to a dep file.
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
	bool verbose = false; ///< Verbose?
};

/// @brief Variant.
struct Variant final
{
	std::string id; ///< Variant ID.
	bool directResourceAccess = false; ///< Enable direct resource access.
};
/// @brief Resource parameters.
struct Params final
{
	std::vector<Variant> variants; ///< Variants.
};

constexpr std::string_view ParamsFlag = "-p"; ///< Parameters flag. The next argument must be a path.
constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view DepFileFlag = "-d"; ///< Dep file flag. The next argument must be a path.
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view ParamsSchema = "PonyEngine/Resource/Text/v0"; ///< Params schema.
constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name.
constexpr std::string_view VariantArrayPropertyName = "variant"; ///< Variant array property name.
constexpr std::string_view VariantIdPropertyName = "id"; ///< Variant ID property name.
constexpr std::string_view DirectResourceAccessPropertyName = "directResourceAccess"; ///< Direct resource access property name.

constexpr std::string_view MagicWord = "PonyEngineResourceContainer"; ///< Resource magic word.
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

/// @brief Compiles a resource.
/// @param command Parsed command.
void Compile(const Command& command);
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
/// @brief Reads parameters.
/// @param path Parameter file path.
/// @return Parameters.
[[nodiscard("Pure function")]]
Params ReadParams(std::string_view path);
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
		Verbose = command.verbose;
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
			if (command.verbose) [[unlikely]]
			{
				std::println(std::clog, "Verbose flag '{}' set multiple times.", VersionFlag);
			}

			command.verbose = true;
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
		std::println("\t<input>          Input asset file, can be any file.");
		std::println("\nOptions:");
		std::println("\t-p <path>        Text resource params file.");
		std::println("\t-o <path>        Resource output file.");
		std::println("\t-d <path>        Dep file path.");
		std::println("\t--version        Display version information and exit.");
		std::println("\t--verbose        Enable verbose output.");
		std::println("\t--help           Display this help message and exit.");
		std::println();
	}
}

void Compile(const Command& command)
{
	const Params params = ReadParams(command.params);

	if (command.input.empty()) [[unlikely]]
	{
		if (Verbose) [[unlikely]]
		{
			std::println("Returning because command doesn't have input.");
		}

		return;
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Opening input file at '{}'.", command.input);
	}
	std::ifstream input = OpenInput(command.input);

	if (command.output.empty()) [[unlikely]]
	{
		if (Verbose) [[unlikely]]
		{
			std::println("Returning because command doesn't have output.");
		}

		return;
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Opening output file at '{}'.", command.output);
	}
	std::ofstream output = OpenOutput(command.output, std::ios::binary | std::ios::trunc);

	if (!command.depFile.empty()) [[likely]]
	{
		auto depData = PonyTools::DepFile::DepData();
		PonyTools::DepFile::DepRule& depRule = depData.AddRule();
		depRule.AddTarget(std::filesystem::path(command.output));
		depRule.AddDependency(std::filesystem::path(command.input));
		if (!command.params.empty())
		{
			depRule.AddDependency(std::filesystem::path(command.params));
		}

		if (Verbose) [[unlikely]]
		{
			std::println("Writing to dep file at '{}'.", command.depFile);
		}
		std::ofstream depFile = OpenOutput(command.depFile, std::ios::trunc);
		depData.Write(depFile);
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Writing to output. Magic word: '{}'.", MagicWord);
	}
	output.write(MagicWord.data(), MagicWord.size());

	const std::size_t variantCount = params.variants.size();
	if (Verbose) [[unlikely]]
	{
		std::println("Writing to output. VariantCount: '{}'.", variantCount);
	}
	output.write(reinterpret_cast<const char*>(&variantCount), sizeof(variantCount));

	for (const Variant& variant : params.variants)
	{
		const auto variantIdSize = static_cast<std::uint8_t>(variant.id.size());
		constexpr auto typeSize = static_cast<std::uint8_t>(TextResourceType.size());
		constexpr std::size_t dataMetaSize = 0uz;
		constexpr std::size_t loadMetaSize = 1uz;
		const auto directResourceAccess = static_cast<std::uint8_t>(variant.directResourceAccess);

		if (Verbose) [[unlikely]]
		{
			std::println("Writing to output. VariantIDSize: '{}'; VariantID: '{}'; TypeSize: '{}'; Type: '{}'; DataMetaSize: '{}'; LoadMetaSize: '{}'; DirectResourceAccess: '{}'.", 
				variantIdSize, variant.id, typeSize, TextResourceType, dataMetaSize, loadMetaSize, directResourceAccess);
		}

		output.write(reinterpret_cast<const char*>(&variantIdSize), sizeof(variantIdSize));
		output.write(variant.id.data(), variantIdSize);
		output.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
		output.write(TextResourceType.data(), typeSize);
		output.write(reinterpret_cast<const char*>(&dataMetaSize), sizeof(dataMetaSize));
		output.write(reinterpret_cast<const char*>(&loadMetaSize), sizeof(loadMetaSize));
		output.write(reinterpret_cast<const char*>(&directResourceAccess), sizeof(directResourceAccess));
	}

	auto inputData = std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
	const std::size_t inputWriteCount = inputData.size() - (inputData.size() > 0uz && inputData.back() == '\n');
	if (Verbose) [[unlikely]]
	{
		std::println("Writing to output. Input: '{}'.", std::string_view(inputData).substr(0, inputWriteCount));
	}
	output.write(inputData.data(), inputWriteCount);
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

Params ReadParams(const std::string_view path)
{
	if (Verbose) [[unlikely]]
	{
		std::println("Reading parameters from '{}'.", path);
	}

	auto params = Params{};

	if (path.empty())
	{
		if (Verbose) [[unlikely]]
		{
			std::println("Parameters path is empty. Returning default parameters.");
		}

		params.variants.push_back(Variant{});
		return params;
	}

	const toml::table table = ParseParams(path);
	if (table[SchemaPropertyName].value<std::string_view>() != ParamsSchema) [[unlikely]]
	{
		throw std::runtime_error("Params file doesn't have a valid schema");
	}

	if (const toml::node_view variantsProperty = table[VariantArrayPropertyName]) [[likely]]
	{
		if (const toml::array* const variants = variantsProperty.as_array()) [[likely]]
		{
			for (const toml::node& variantProperty : *variants)
			{
				if (const toml::table* const variant = variantProperty.as_table()) [[likely]]
				{
					const std::optional<std::string_view> id = (*variant)[VariantIdPropertyName].value<std::string_view>();
					if (!id) [[unlikely]]
					{
						throw std::runtime_error(std::format("No '{}' property as string found in variant", VariantIdPropertyName));
					}
					if (Verbose) [[unlikely]]
					{
						std::println("Adding variant. ID: '{}'.", *id);
					}
					if (id->size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
					{
						throw std::runtime_error(std::format("Variant ID '{}' is too long, must be less or equal '{}'", *id, std::numeric_limits<std::uint8_t>::max()));
					}
					const std::optional<bool> directResourceAccess = (*variant)[DirectResourceAccessPropertyName].value<bool>();

					for (const Variant& entry : params.variants)
					{
						if (entry.id == id) [[unlikely]]
						{
							throw std::runtime_error(std::format("Resource with ID '{}' found twice at least", *id));
						}
					}

					auto var = Variant
					{
						.id = std::string(*id),
						.directResourceAccess = directResourceAccess.value_or(false)
					};
					if (Verbose) [[unlikely]]
					{
						std::println("Pushing variant. ID: '{}'; DirectResourceAccess: '{}'.", var.id, var.directResourceAccess);
					}
					params.variants.push_back(std::move(var));
				}
				else [[unlikely]]
				{
					throw std::runtime_error("Invalid resource element in params file");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Invalid resources array in params file");
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
