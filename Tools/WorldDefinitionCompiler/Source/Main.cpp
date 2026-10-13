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

import PonyEngine.FileSystem;

import PonyTools.DepFile;
import PonyTools.FileSystem;
import PonyTools.World;

 /// @brief Parsed command.
struct Command final
{
	std::string_view input; ///< Path to an input file.
	std::string_view output; ///< Path to an output file.
	std::vector<std::string_view> serializers; ///< Paths to serializers.
	std::string_view depFile; ///< Path to a dep file.
	std::size_t sizeTSize = 0uz; ///< Size of std::size_t on a target platform.
	bool bigEndian = false; ///< Is a target platform big-endian?
	bool showVersion = false; ///< Show compiler version?
	bool showHowToUse = false; ///< Show how to use?
	bool showHelp = false; ///< Show help?
};

constexpr std::string_view OutputFlag = "-o"; ///< Output flag. The next argument must be a path.
constexpr std::string_view SerializerFlag = "-s"; ///< Serializer flag. The next argument must be a path.
constexpr std::string_view DepFileFlag = "-d"; ///< Dep file flag. The next argument must be a path.
constexpr std::string_view SizeTSizeFlag = "--size_t-size"; ///< Target platform std::size_t size flag. The next argument must be an unsigned integer.
constexpr std::string_view BigEndianFlag = "--big-endian"; ///< Target platform big endianness flag.
constexpr std::string_view VersionFlag = "--version"; ///< Version flag.
constexpr std::string_view HelpFlag = "--help"; ///< Help flag.
constexpr std::string_view VerboseFlag = "--verbose"; ///< Verbose flag.

constexpr std::string_view WorldDefinitionSchema = "PonyEngine/Resource/WorldDefinition/v0"; ///< World definition schema.
constexpr std::string_view SchemaPropertyName = "schema"; ///< Schema property name.
constexpr std::string_view EntityPropertyName = "entity"; ///< Entity property name.
constexpr std::string_view ComponentPropertyName = "component"; ///< Component property name.
constexpr std::string_view ObjectPropertyName = "object"; ///< Object property name.
constexpr std::string_view IDPropertyName = "id"; ///< ID property name.
constexpr std::string_view TypePropertyName = "type"; ///< Type property name.

constexpr std::string_view DataMagicWord = "PonyEngineResourceData"; ///< Resource data magic word.
constexpr std::string_view WorldDefinitionResourceType = "Pony.WorldDefinition"; ///< World definition resource type.

constexpr std::string_view GetComponentTypesFunctionName = "GetComponentTypes";
constexpr std::string_view GetComponentSizeFunctionName = "GetComponentSize";
constexpr std::string_view SerializeComponentFunctionName = "SerializeComponent";
constexpr std::string_view GetObjectTypesFunctionName = "GetObjectTypes";
constexpr std::string_view GetObjectSizeFunctionName = "GetObjectSize";
constexpr std::string_view SerializeObjectFunctionName = "SerializeObject";

using GetComponentTypesFunction = std::span<const std::string_view>(*)();
using GetComponentSizeFunction = std::size_t(*)(std::size_t, const toml::table&);
using SerializeComponentFunction = void(*)(std::size_t, const toml::table&, std::span<std::byte>,
	const std::unordered_map<std::string_view, std::uint64_t>&, const std::unordered_map<std::string_view, std::uint64_t>&, std::size_t, bool);
using GetObjectTypesFunction = std::span<const std::string_view>(*)();
using GetObjectSizeFunction = std::size_t(*)(std::size_t, const toml::table&);
using SerializeObjectFunction = void(*)(std::size_t, const toml::table&, std::span<std::byte>, const std::unordered_map<std::string_view, std::uint64_t>&, std::size_t, bool);

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
/// @brief Reads the world TOML file.
/// @param command Command.
/// @return World definition
[[nodiscard("Pure function")]]
PonyTools::World::WorldDefinition ReadWorld(const Command& command);
/// @brief Parses the world TOML file.
/// @param path Path to the file.
/// @return Parsed TOML.
[[nodiscard("Pure function")]]
toml::table ParseWorld(std::string_view path);

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
			WriteDepFile(command);
			Compile(command);
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

		if (arg == OutputFlag)
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
		else if (arg == SerializerFlag)
		{
			if (++i >= argc) [[unlikely]]
			{
				throw std::invalid_argument(std::format("Missing path after serializer flag '{}'", OutputFlag));
			}

			command.serializers.push_back(argv[i]);
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
		else
		{
			if (!command.input.empty()) [[unlikely]]
			{
				throw std::invalid_argument("Input path set multiple times");
			}

			command.input = arg;
		}
	}

	const std::uint8_t mainParamCount = !command.input.empty() + !command.output.empty();
	if (mainParamCount != 0u && mainParamCount != 2u) [[unlikely]]
	{
		throw std::invalid_argument("Invalid argument set");
	}

	return command;
}

void PrintVersion(const Command& command)
{
	if (command.showVersion) [[unlikely]]
	{
		std::println("Pony Engine World Definition Compiler v{}.{}.{}.{}",
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
		std::println("\nCompiles a world definition asset into a Pony Engine resource.");
		std::println("\nUsage:");
		std::println("\tPonyWorldDefinitionCompiler <input> [options]");
		std::println("\nArguments:");
		std::println("\t<input>                          Input asset file path, must be toml.");
		std::println("\nOptions:");
		std::println("\t-o <path>                        Resource data output file path.");
		std::println("\t-s <path>                        Serializer library file path.");
		std::println("\t-d <path>                        Dep file path.");
		std::println("\t--size_t-size <number>           Target platform std::size_t size.");
		std::println("\t--big-endian                     If set, target platform is treated as big-endian.");
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

	if (Verbose) [[unlikely]]
	{
		std::println("Writing to dep file at '{}'.", command.depFile);
	}
	std::ofstream depFile = PonyTools::FileSystem::OpenOutput(command.depFile, std::ios::trunc);
	depData.Write(depFile);
}

void Compile(const Command& command)
{
	const PonyTools::World::WorldDefinition world = ReadWorld(command);

	if (Verbose) [[unlikely]]
	{
		std::println("Opening data output file at '{}'.", command.output);
	}
	std::ofstream output = PonyTools::FileSystem::OpenOutput(command.output, std::ios::binary | std::ios::trunc);

	output.write(DataMagicWord.data(), DataMagicWord.size());

	constexpr std::uint8_t typeSize = WorldDefinitionResourceType.size();
	output.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
	output.write(WorldDefinitionResourceType.data(), typeSize);

	constexpr std::size_t dataMetaSize = 0uz;
	output.write(reinterpret_cast<const char*>(&dataMetaSize), sizeof(dataMetaSize));

	const std::uintmax_t sizeTMaxValue = command.sizeTSize == sizeof(std::uintmax_t)
		? std::numeric_limits<std::uintmax_t>::max()
		: (std::uintmax_t{1u} << (command.sizeTSize * 8u)) - 1u;

	const std::size_t entityCount = world.EntityCount();
	if (entityCount > sizeTMaxValue) [[unlikely]]
	{
		throw std::runtime_error("Too many entities");
	}
	const std::size_t componentTableCount = world.ComponentTableCount();
	if (componentTableCount > sizeTMaxValue) [[unlikely]]
	{
		throw std::runtime_error("Too many component tables");
	}
	const std::size_t objectCount = world.ObjectCount();
	if (objectCount > sizeTMaxValue) [[unlikely]]
	{
		throw std::runtime_error("Too many objects");
	}

	PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(entityCount), command.sizeTSize, command.bigEndian);
	PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(componentTableCount), command.sizeTSize, command.bigEndian);
	PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(objectCount), command.sizeTSize, command.bigEndian);

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		const std::string_view type = world.ComponentType(i);
		if (type.size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Component type '{}' is too long", type));
		}

		const std::uint8_t length = type.size();
		output.write(reinterpret_cast<const char*>(&length), sizeof(length));
	}

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		const std::span<const std::uint64_t> entityIndices = world.ComponentEntities(i);
		PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(entityIndices.size()), command.sizeTSize, command.bigEndian);
	}

	for (std::size_t i = 0uz; i < objectCount; ++i)
	{
		const std::string_view type = world.ObjectType(i);
		if (type.size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Object type '{}' is too long", type));
		}

		const std::uint8_t length = type.size();
		output.write(reinterpret_cast<const char*>(&length), sizeof(length));
	}

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		const std::span<const std::byte> componentData = world.ComponentData(i);
		if (componentData.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error(std::format("Too large data on component table of type '{}'", world.ComponentType(i)));
		}

		PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(componentData.size()), command.sizeTSize, command.bigEndian);
	}

	for (std::size_t i = 0uz; i < objectCount; ++i)
	{
		const std::span<const std::byte> objectData = world.ObjectData(i);
		if (objectData.size() > sizeTMaxValue) [[unlikely]]
		{
			throw std::runtime_error(std::format("Too large data on object with id '{}'", world.ObjectID(i)));
		}

		PonyTools::FileSystem::Write(output, static_cast<std::uintmax_t>(objectData.size()), command.sizeTSize, command.bigEndian);
	}

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		const std::string_view type = world.ComponentType(i);
		output.write(type.data(), type.size());
	}

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		for (const std::uint64_t entityIndex : world.ComponentEntities(i))
		{
			PonyTools::FileSystem::Write(output, entityIndex, sizeof(std::uint64_t), command.bigEndian);
		}
	}

	for (std::size_t i = 0uz; i < objectCount; ++i)
	{
		const std::string_view type = world.ObjectType(i);
		output.write(type.data(), type.size());
	}

	for (std::size_t i = 0uz; i < componentTableCount; ++i)
	{
		const std::span<const std::byte> componentData = world.ComponentData(i);
		output.write(reinterpret_cast<const char*>(componentData.data()), componentData.size());
	}

	for (std::size_t i = 0uz; i < objectCount; ++i)
	{
		const std::span<const std::byte> objectData = world.ObjectData(i);
		output.write(reinterpret_cast<const char*>(objectData.data()), objectData.size());
	}
}

PonyTools::World::WorldDefinition ReadWorld(const Command& command)
{
	std::vector<PonyEngine::FileSystem::DynamicLibrary> serializerLibraries;
	for (const std::string_view serializerPath : command.serializers)
	{
		serializerLibraries.push_back(PonyEngine::FileSystem::DynamicLibrary(serializerPath));
	}

	std::unordered_map<std::string_view, std::tuple<GetComponentSizeFunction, SerializeComponentFunction, std::size_t>> componentSerializers;
	std::unordered_map<std::string_view, std::tuple<GetObjectSizeFunction, SerializeObjectFunction, std::size_t>> objectSerializers;
	for (const PonyEngine::FileSystem::DynamicLibrary& library : serializerLibraries)
	{
		const auto getComponentTypes = static_cast<GetComponentTypesFunction>(library.GetAddress(GetComponentTypesFunctionName));
		const std::span<const std::string_view> componentTypes = getComponentTypes();
		if (!componentTypes.empty())
		{
			const auto getComponentSize = static_cast<GetComponentSizeFunction>(library.GetAddress(GetComponentSizeFunctionName));
			const auto serializeComponent = static_cast<SerializeComponentFunction>(library.GetAddress(SerializeComponentFunctionName));

			for (std::size_t i = 0uz; i < componentTypes.size(); ++i)
			{
				componentSerializers[componentTypes[i]] = std::make_tuple(getComponentSize, serializeComponent, i);
			}
		}

		const auto getObjectTypes = static_cast<GetObjectTypesFunction>(library.GetAddress(GetObjectTypesFunctionName));
		const std::span<const std::string_view> objectTypes = getObjectTypes();
		if (!objectTypes.empty())
		{
			const auto getObjectSize = static_cast<GetObjectSizeFunction>(library.GetAddress(GetObjectSizeFunctionName));
			const auto serializeObject = static_cast<SerializeObjectFunction>(library.GetAddress(SerializeObjectFunctionName));

			for (std::size_t i = 0uz; i < objectTypes.size(); ++i)
			{
				objectSerializers[objectTypes[i]] = std::make_tuple(getObjectSize, serializeObject, i);
			}
		}
	}

	if (Verbose) [[unlikely]]
	{
		std::println("Reading world file at '{}'.", command.input);
	}

	PonyTools::World::WorldDefinition world;
	const toml::table table = ParseWorld(command.input);
	if (table[SchemaPropertyName].value<std::string_view>() != WorldDefinitionSchema) [[unlikely]]
	{
		throw std::runtime_error(std::format("World file at '{}' doesn't have a valid schema", command.input));
	}

	std::vector<std::pair<std::size_t, const toml::table*>> componentSources;
	std::unordered_map<std::string_view, std::uint64_t> entityIdToIndex;
	std::unordered_map<std::string_view, std::uint64_t> objectIdToIndex;

	std::vector<std::byte> data;

	if (const toml::node_view entitiesProperty = table[EntityPropertyName])
	{
		if (const toml::array* const entities = entitiesProperty.as_array()) [[likely]]
		{
			for (const toml::node& entityProperty : *entities)
			{
				if (const toml::table* const entityTable = entityProperty.as_table()) [[likely]]
				{
					const toml::table& entity = *entityTable;

					const std::optional<std::string_view> entityId = entity[IDPropertyName].value<std::string_view>();
					if (!entityId) [[unlikely]]
					{
						throw std::runtime_error("Entity doesn't have ID");
					}

					const std::uint64_t entityIndex = world.AddEntity(*entityId);
					entityIdToIndex[*entityId] = entityIndex;

					if (const toml::node_view componentsProperty = table[ComponentPropertyName])
					{
						if (const toml::array* components = componentsProperty.as_array()) [[likely]]
						{
							for (const toml::node& componentProperty : *components)
							{
								if (const toml::table* const componentTable = componentProperty.as_table()) [[likely]]
								{
									const toml::table& component = *componentTable;

									const std::optional<std::string_view> componentId = component[IDPropertyName].value<std::string_view>();
									if (!componentId) [[unlikely]]
									{
										throw std::runtime_error(std::format("Entity '{}' has component without ID", *entityId));
									}

									const std::optional<std::string_view> componentType = component[TypePropertyName].value<std::string_view>();
									if (!componentType) [[unlikely]]
									{
										throw std::runtime_error(std::format("Component '{}' on entity '{}' doesn't have type", *componentId, *entityId));
									}

									const std::size_t tableIndex = world.AddComponent(entityIndex, *componentType);
									componentSources.emplace_back(tableIndex, componentTable);
								}
								else [[unlikely]]
								{
									throw std::runtime_error(std::format("Entity '{}' has invalid component", *entityId));
								}
							}
						}
						else [[unlikely]]
						{
							throw std::runtime_error(std::format("Entity '{}' has invalid component array", *entityId));
						}
					}
				}
				else [[unlikely]]
				{
					throw std::runtime_error("Invalid entity");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Invalid entity array");
		}
	}
	if (const toml::node_view objectsProperty = table[ObjectPropertyName])
	{
		if (const toml::array* const objects = objectsProperty.as_array()) [[likely]]
		{
			for (const toml::node& objectProperty : *objects)
			{
				if (const toml::table* objectTable = objectProperty.as_table()) [[likely]]
				{
					const toml::table& object = *objectTable;

					const std::optional<std::string_view> objectId = object[IDPropertyName].value<std::string_view>();
					if (!objectId) [[unlikely]]
					{
						throw std::runtime_error("Object doesn't have ID");
					}

					const std::optional<std::string_view> objectType = object[TypePropertyName].value<std::string_view>();
					if (!objectType) [[unlikely]]
					{
						throw std::runtime_error(std::format("Object '{}' doesn't have type", *objectId));
					}

					const auto position = objectSerializers.find(*objectType);
					if (position == objectSerializers.cend()) [[unlikely]]
					{
						throw std::runtime_error(std::format("Object serializer not found for object of type '{}'", *objectType));
					}
					const GetObjectSizeFunction getObjectSize = std::get<GetObjectSizeFunction>(position->second);
					const SerializeObjectFunction serializeObject = std::get<SerializeObjectFunction>(position->second);
					const std::size_t typeIndex = std::get<std::size_t>(position->second);

					const std::size_t objectSize = getObjectSize(typeIndex, object);
					data.resize(objectSize);
					serializeObject(typeIndex, object, data, entityIdToIndex, command.sizeTSize, command.bigEndian);

					const std::uint64_t objectIndex = world.AddObject(*objectId, *objectType, data);
					objectIdToIndex[*objectId] = objectIndex;
				}
				else [[unlikely]]
				{
					throw std::runtime_error("Invalid object");
				}
			}
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Invalid object array");
		}
	}

	for (const auto [componentTableIndex, componentTable] : componentSources)
	{
		std::vector<std::byte>& componentData = world.ComponentData(componentTableIndex);
		const std::string_view componentType = *(*componentTable)[TypePropertyName].value<std::string_view>();

		const auto position = componentSerializers.find(componentType);
		if (position == componentSerializers.cend()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Component serializer not found for component of type ''", componentType));
		}
		const GetComponentSizeFunction getComponentSize = std::get<GetComponentSizeFunction>(position->second);
		const SerializeComponentFunction serializeComponent = std::get<SerializeComponentFunction>(position->second);
		const std::size_t typeIndex = std::get<std::size_t>(position->second);

		const std::size_t componentSize = getComponentSize(typeIndex, *componentTable);
		data.resize(componentSize);
		serializeComponent(typeIndex, *componentTable, data, entityIdToIndex, objectIdToIndex, command.sizeTSize, command.bigEndian);

		componentData.append_range(data);
	}

	return world;
}

toml::table ParseWorld(const std::string_view path)
{
	try
	{
		return toml::parse_file(path);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(std::format("Failed to parse world at path '{}': '{}': '{}'", std::filesystem::absolute(std::filesystem::path(path)).string(),
			typeid(e).name(), e.what()));
	}
	catch (...)
	{
		throw std::runtime_error(std::format("Failed to parse world at path '{}': Unknown exception", std::filesystem::absolute(std::filesystem::path(path)).string()));
	}
}
