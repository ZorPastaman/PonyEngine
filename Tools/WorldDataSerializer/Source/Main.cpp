/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Macro/Compiler.h"

#include "toml++/toml.hpp"

import std;

import PonyEngine.Math;
import PonyEngine.World.Meta;

import PonyTools.Memory;

constexpr std::string_view NamePropertyName = "name"; ///< Name property name.
constexpr std::string_view ObjectPropertyName = "object"; ///< Object property name.
constexpr std::string_view ParentPropertyName = "parent"; ///< Parent property name.
constexpr std::string_view PositionPropertyName = "position"; ///< Position property name.
constexpr std::string_view RotationPropertyName = "rotation"; ///< Rotation property name.
constexpr std::string_view ScalePropertyName = "scale"; ///< Scale property name.
constexpr std::string_view InterfacePropertyName = "interface"; ///< Resource interface property name.
constexpr std::string_view ResourcePropertyName = "resource"; ///< Resource ID property name.

using GetComponentSizeFunction = std::size_t(*)(const toml::table&, std::size_t); ///< Get component size function.
using SerializeComponentFunction = void(*)(const toml::table&, std::span<std::byte>, const std::unordered_map<std::string_view, std::uint64_t>&, 
	const std::unordered_map<std::string_view, std::uint64_t>&, const std::unordered_map<std::string_view, std::string_view>&, std::size_t, bool); ///< Serialize component function.
using GetObjectSizeFunction = std::size_t(*)(const toml::table&, std::size_t); ///< @p GetObjectSize() function.
using SerializeObjectFunction = void(*)(const toml::table&, std::span<std::byte>, std::size_t, bool); ///< @p SerializeObject() function.

/// @brief Component entry.
struct ComponentEntry final
{
	std::string_view type; ///< Component type.
	GetComponentSizeFunction sizeFunction; ///< Get component size function.
	SerializeComponentFunction serializeFunction; ///< Serialize component function.
};
/// @brief Object entry.
struct ObjectEntry final
{
	std::string_view type; ///< Object type.
	GetObjectSizeFunction sizeFunction; ///< Get object size function.
	SerializeObjectFunction serializeFunction; ///< Serialize object function.
};

/// @brief std::string_view C wrapper.
struct alignas(std::span<const std::string_view>) StringViewSpan final
{
	[[maybe_unused]] std::byte data[sizeof(std::span<const std::string_view>)];
};

extern "C"
{
	/// @brief Gets component types.
	/// @return Component types.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL StringViewSpan GetComponentTypes() noexcept;
	/// @brief Gets a component size.
	/// @param typeIndex Component type index.
	/// @param componentTable Component table.
	/// @param sizeTSize Target platform std::size_t size.
	/// @return Component size.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL std::size_t GetComponentSize(std::size_t typeIndex, const toml::table& componentTable, std::size_t sizeTSize) noexcept;
	/// @brief Serializes a component.
	/// @param typeIndex Component type index.
	/// @param componentTable Component table.
	/// @param componentData Component output data.
	/// @param entityIDToIndex Entity ID to index map.
	/// @param objectIDToIndex Object ID to index map.
	/// @param objectIDToType Object ID to type map.
	/// @param sizeTSize Target platform std::size_t size.
	/// @param bigEndian Is the target platform big endian?
	/// @return @a True if it serialized successfully; @a false otherwise.
	PONY_DLL_EXPORT_IMPL bool SerializeComponent(std::size_t typeIndex, const toml::table& componentTable, std::span<std::byte> componentData,
		const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex, 
		const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian) noexcept;

	/// @brief Gets object types.
	/// @return Object types.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL StringViewSpan GetObjectTypes() noexcept;
	/// @brief Gets an object size.
	/// @param typeIndex Object type index.
	/// @param objectTable Object table.
	/// @param sizeTSize Target platform std::size_t size.
	/// @return Object size.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL std::size_t GetObjectSize(std::size_t typeIndex, const toml::table& objectTable, std::size_t sizeTSize) noexcept;
	/// @brief Serializes a object.
	/// @param typeIndex Object type index.
	/// @param objectTable Object table.
	/// @param objectData Object output data.
	/// @param sizeTSize Target platform std::size_t size.
	/// @param bigEndian Is the target platform big endian?
	/// @return @a True if it serialized successfully; @a false otherwise.
	PONY_DLL_EXPORT_IMPL bool SerializeObject(std::size_t typeIndex, const toml::table& objectTable, std::span<std::byte> objectData,
		std::size_t sizeTSize, bool bigEndian) noexcept;
}

[[nodiscard("Pure function")]]
std::size_t GetNameSize(const toml::table& componentTable, std::size_t sizeTSize);
[[nodiscard("Pure function")]]
std::size_t GetDescriptionSize(const toml::table& componentTable, std::size_t sizeTSize);

[[nodiscard("Pure function")]]
std::size_t GetParentSize(const toml::table& componentTable, std::size_t sizeTSize);
[[nodiscard("Pure function")]]
std::size_t GetTransform2DSize(const toml::table& componentTable, std::size_t sizeTSize);
[[nodiscard("Pure function")]]
std::size_t GetTransform3DSize(const toml::table& componentTable, std::size_t sizeTSize);

void SerializeName(const toml::table& componentTable, std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian);
void SerializeDescription(const toml::table& componentTable, std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian);

void SerializeParent(const toml::table& componentTable, std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian);
void SerializeTransform2D(const toml::table& componentTable, std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian);
void SerializeTransform3D(const toml::table& componentTable, std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, std::size_t sizeTSize, bool bigEndian);

constexpr std::array ComponentEntries
{
	ComponentEntry{.type = "Pony.Name", .sizeFunction = &GetNameSize, .serializeFunction = &SerializeName},
	ComponentEntry{.type = "Pony.Description", .sizeFunction = &GetDescriptionSize, .serializeFunction = &SerializeDescription},
	ComponentEntry{.type = "Pony.Parent", .sizeFunction = &GetParentSize, .serializeFunction = &SerializeParent},
	ComponentEntry{.type = "Pony.Transform2D", .sizeFunction = &GetTransform2DSize, .serializeFunction = &SerializeTransform2D},
	ComponentEntry{.type = "Pony.Transform3D", .sizeFunction = &GetTransform3DSize, .serializeFunction = &SerializeTransform3D}
};
[[nodiscard("Pure function")]]
constexpr std::array<std::string_view, ComponentEntries.size()> GetComponentEntryTypes()
{
	std::array<std::string_view, ComponentEntries.size()> types;
	for (std::size_t i = 0uz; i < types.size(); ++i)
	{
		types[i] = ComponentEntries[i].type;
	}

	return types;
}
constexpr std::array<std::string_view, ComponentEntries.size()> ComponentTypes = GetComponentEntryTypes();

[[nodiscard("Pure function")]]
std::size_t GetResourceSize(const toml::table& componentTable, std::size_t sizeTSize);

void SerializeResource(const toml::table& componentTable, std::span<std::byte> componentData, std::size_t sizeTSize, bool bigEndian);

constexpr std::array ObjectEntries
{
	ObjectEntry{.type = "Pony.Resource", .sizeFunction = &GetResourceSize, .serializeFunction = &SerializeResource}
};
[[nodiscard("Pure function")]]
constexpr std::array<std::string_view, ObjectEntries.size()> GetObjectEntryTypes()
{
	std::array<std::string_view, ObjectEntries.size()> types;
	for (std::size_t i = 0uz; i < types.size(); ++i)
	{
		types[i] = ObjectEntries[i].type;
	}

	return types;
}
constexpr std::array<std::string_view, ObjectEntries.size()> ObjectTypes = GetObjectEntryTypes();

StringViewSpan GetComponentTypes() noexcept
{
	constexpr std::span<const std::string_view> types = ComponentTypes;
	StringViewSpan span;
	std::memcpy(&span, &types, sizeof(StringViewSpan));
	return span;
}

std::size_t GetComponentSize(const std::size_t typeIndex, const toml::table& componentTable, const std::size_t sizeTSize) noexcept
{
	try
	{
		return ComponentEntries[typeIndex].sizeFunction(componentTable, sizeTSize);
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}' on getting component size. Message: '{}'.", typeid(e).name(), e.what());
	}
	catch (...)
	{
		std::println(std::cerr, "Unknown exception on serializing data.");
	}

	return std::numeric_limits<std::size_t>::max();
}

bool SerializeComponent(const std::size_t typeIndex, const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex, 
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, const std::size_t sizeTSize, const bool bigEndian) noexcept
{
	try
	{
		ComponentEntries[typeIndex].serializeFunction(componentTable, componentData, entityIDToIndex, objectIDToIndex, objectIDToType, sizeTSize, bigEndian);
		return true;
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}' on serializing component. Message: '{}'.", typeid(e).name(), e.what());
	}
	catch (...)
	{
		std::println(std::cerr, "Unknown exception on serializing component.");
	}

	return false;
}

StringViewSpan GetObjectTypes() noexcept
{
	constexpr std::span<const std::string_view> types = ObjectTypes;
	StringViewSpan span;
	std::memcpy(&span, &types, sizeof(StringViewSpan));
	return span;
}

std::size_t GetObjectSize(const std::size_t typeIndex, const toml::table& objectTable, const std::size_t sizeTSize) noexcept
{
	try
	{
		return ObjectEntries[typeIndex].sizeFunction(objectTable, sizeTSize);
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}' on getting object size. Message: '{}'.", typeid(e).name(), e.what());
	}
	catch (...)
	{
		std::println(std::cerr, "Unknown exception on serializing data.");
	}

	return std::numeric_limits<std::size_t>::max();
}

bool SerializeObject(const std::size_t typeIndex, const toml::table& objectTable, const std::span<std::byte> objectData,
	const std::size_t sizeTSize, const bool bigEndian) noexcept
{
	try
	{
		ObjectEntries[typeIndex].serializeFunction(objectTable, objectData, sizeTSize, bigEndian);
		return true;
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}' on serializing object. Message: '{}'.", typeid(e).name(), e.what());
	}
	catch (...)
	{
		std::println(std::cerr, "Unknown exception on serializing object.");
	}

	return false;
}

std::size_t GetNameSize(const toml::table& componentTable, const std::size_t)
{
	const std::optional<std::string_view> name = componentTable[NamePropertyName].value<std::string_view>();
	if (!name || name->size() > PonyEngine::World::Meta::Name::MaxLength) [[unlikely]]
	{
		throw std::runtime_error("Invalid name component");
	}

	return sizeof(std::uint8_t) + name->size();
}

std::size_t GetDescriptionSize(const toml::table&, const std::size_t)
{
	return sizeof(std::uint64_t);
}

std::size_t GetParentSize(const toml::table&, const std::size_t)
{
	return sizeof(std::uint64_t);
}

std::size_t GetTransform2DSize(const toml::table&, const std::size_t)
{
	return sizeof(double) * 2uz + sizeof(float) * 3uz;
}

std::size_t GetTransform3DSize(const toml::table&, const std::size_t)
{
	return sizeof(double) * 3uz + sizeof(float) * 6uz;
}

void SerializeName(const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>&, const std::unordered_map<std::string_view, std::uint64_t>&,
	const std::unordered_map<std::string_view, std::string_view>&, const std::size_t, const bool bigEndian)
{
	const std::optional<std::string_view> name = componentTable[NamePropertyName].value<std::string_view>();
	if (!name || name->size() > PonyEngine::World::Meta::Name::MaxLength) [[unlikely]]
	{
		throw std::runtime_error("Invalid name component");
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(static_cast<std::uint8_t>(name->size()));
	writer.Write(*name);
}

void SerializeDescription(const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex,
	const std::unordered_map<std::string_view, std::string_view>& objectIDToType, const std::size_t sizeTSize, const bool bigEndian)
{
	const std::optional<std::string_view> object = componentTable[ObjectPropertyName].value<std::string_view>();
	if (!object) [[unlikely]]
	{
		throw std::runtime_error("Invalid description component");
	}
	const auto position = objectIDToIndex.find(*object);
	if (position == objectIDToIndex.cend()) [[unlikely]]
	{
		throw std::runtime_error("Object not found");
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(position->second);
}

void SerializeParent(const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>&,
	const std::unordered_map<std::string_view, std::string_view>&, const std::size_t, const bool bigEndian)
{
	const std::optional<std::string_view> parentId = componentTable[ParentPropertyName].value<std::string_view>();
	if (!parentId) [[unlikely]]
	{
		throw std::runtime_error("Invalid parent component");
	}

	const auto position = entityIDToIndex.find(*parentId);
	if (position == entityIDToIndex.cend()) [[unlikely]]
	{
		throw std::runtime_error(std::format("Failed to find an entity with ID '{}'", *parentId));
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(position->second);
}

void SerializeTransform2D(const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>&, const std::unordered_map<std::string_view, std::uint64_t>&,
	const std::unordered_map<std::string_view, std::string_view>&, const std::size_t, const bool bigEndian)
{
	const toml::table* const position = componentTable[PositionPropertyName].as_table();
	if (!position) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}
	const std::optional<double> positionX = (*position)["x"].value<double>();
	const std::optional<double> positionY = (*position)["y"].value<double>();
	if (!positionX || !positionY) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	const std::optional<float> rotation = componentTable[RotationPropertyName].value<float>();
	if (!rotation) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	const toml::table* const scale = componentTable[ScalePropertyName].as_table();
	if (!scale) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}
	const std::optional<float> scaleX = (*scale)["x"].value<float>();
	const std::optional<float> scaleY = (*scale)["y"].value<float>();
	if (!scaleX || !scaleY) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(*positionX);
	writer.Write(*positionY);
	writer.Write(*rotation * PonyEngine::Math::DegToRad<float>);
	writer.Write(*scaleX);
	writer.Write(*scaleY);
}

void SerializeTransform3D(const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>&, const std::unordered_map<std::string_view, std::uint64_t>&,
	const std::unordered_map<std::string_view, std::string_view>&, const std::size_t, const bool bigEndian)
{
	const toml::table* const position = componentTable[PositionPropertyName].as_table();
	if (!position) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}
	const std::optional<double> positionX = (*position)["x"].value<double>();
	const std::optional<double> positionY = (*position)["y"].value<double>();
	const std::optional<double> positionZ = (*position)["z"].value<double>();
	if (!positionX || !positionY || !positionZ) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	const toml::table* rotation = componentTable[RotationPropertyName].as_table();
	if (!rotation) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}
	const std::optional<float> rotationX = (*rotation)["x"].value<float>();
	const std::optional<float> rotationY = (*rotation)["y"].value<float>();
	const std::optional<float> rotationZ = (*rotation)["z"].value<float>();
	if (!rotationX || !rotationY || !rotationZ) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	const toml::table* const scale = componentTable[ScalePropertyName].as_table();
	if (!scale) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}
	const std::optional<float> scaleX = (*scale)["x"].value<float>();
	const std::optional<float> scaleY = (*scale)["y"].value<float>();
	const std::optional<float> scaleZ = (*scale)["z"].value<float>();
	if (!scaleX || !scaleY || !scaleZ) [[unlikely]]
	{
		throw std::runtime_error("Invalid transform component");
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(*positionX);
	writer.Write(*positionY);
	writer.Write(*positionZ);
	writer.Write(*rotationX * PonyEngine::Math::DegToRad<float>);
	writer.Write(*rotationY * PonyEngine::Math::DegToRad<float>);
	writer.Write(*rotationZ * PonyEngine::Math::DegToRad<float>);
	writer.Write(*scaleX);
	writer.Write(*scaleY);
	writer.Write(*scaleZ);
}

std::size_t GetResourceSize(const toml::table& componentTable, const std::size_t)
{
	const std::optional<std::string_view> interface = componentTable[InterfacePropertyName].value<std::string_view>();
	if (!interface || interface->size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::runtime_error("Invalid resource object");
	}
	const std::optional<std::string_view> resource = componentTable[ResourcePropertyName].value<std::string_view>();
	if (!resource || resource->size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::runtime_error("Invalid resource object");
	}

	return sizeof(std::uint8_t) * 2uz + interface->size() + resource->size();
}

void SerializeResource(const toml::table& componentTable, const std::span<std::byte> componentData, const std::size_t sizeTSize, const bool bigEndian)
{
	const std::optional<std::string_view> interface = componentTable[InterfacePropertyName].value<std::string_view>();
	if (!interface || interface->size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::runtime_error("Invalid resource object");
	}
	const std::optional<std::string_view> resource = componentTable[ResourcePropertyName].value<std::string_view>();
	if (!resource || resource->size() > std::numeric_limits<std::uint8_t>::max()) [[unlikely]]
	{
		throw std::runtime_error("Invalid resource object");
	}

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(static_cast<std::uint8_t>(interface->size()));
	writer.Write(static_cast<std::uint8_t>(resource->size()));
	writer.Write(*interface);
	writer.Write(*resource);
}
