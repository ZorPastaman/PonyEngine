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
import PonyEngine.World.Hierarchy;

import PonyTools.Memory;

constexpr std::string_view ParentPropertyName = "parent";
constexpr std::string_view PositionPropertyName = "position";
constexpr std::string_view RotationPropertyName = "rotation";
constexpr std::string_view ScalePropertyName = "scale";

constexpr std::array<std::string_view, 3> ComponentTypes
{
	"Pony.Parent",
	"Pony.Transform2D",
	"Pony.Transform3D"
};

struct StringViewSpan final
{
	std::byte data[sizeof(std::span<const std::string_view>)];
};

extern "C"
{
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL StringViewSpan GetComponentTypes() noexcept;
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT_IMPL std::size_t GetComponentSize(std::size_t typeIndex, const toml::table& componentTable, std::size_t sizeTSize) noexcept;
	PONY_DLL_EXPORT_IMPL void SerializeComponent(std::size_t typeIndex, const toml::table& componentTable, std::span<std::byte> componentData,
		const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex, 
		std::size_t sizeTSize, bool bigEndian) noexcept;
}

void SerializeParent(const toml::table& componentTable, std::span<std::byte> componentData, const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, 
	bool bigEndian);
void SerializeTransform2D(const toml::table& componentTable, std::span<std::byte> componentData, bool bigEndian);
void SerializeTransform3D(const toml::table& componentTable, std::span<std::byte> componentData, bool bigEndian);

StringViewSpan GetComponentTypes() noexcept
{
	constexpr std::span<const std::string_view> types = ComponentTypes;
	StringViewSpan span;
	std::memcpy(&span, &types, sizeof(StringViewSpan));
	return span;
}

std::size_t GetComponentSize(const std::size_t typeIndex, const toml::table& componentTable, const std::size_t sizeTSize) noexcept
{
	switch (typeIndex)
	{
	case 0:
		return sizeof(PonyEngine::World::Hierarchy::Parent);
	case 1:
		return sizeof(PonyEngine::World::Hierarchy::LocalTransform2D);
	case 2:
		return sizeof(PonyEngine::World::Hierarchy::LocalTransform3D);
	default: [[unlikely]]
		std::println(std::cerr, "Type index is out of range.");
		return 0uz;
	}
}

void SerializeComponent(const std::size_t typeIndex, const toml::table& componentTable, const std::span<std::byte> componentData,
	const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex, const std::unordered_map<std::string_view, std::uint64_t>& objectIDToIndex, 
	const std::size_t sizeTSize, const bool bigEndian) noexcept
{
	try
	{
		switch (typeIndex)
		{
		case 0:
			SerializeParent(componentTable, componentData, entityIDToIndex, bigEndian);
			break;
		case 1:
			SerializeTransform2D(componentTable, componentData, bigEndian);
			break;
		case 2:
			SerializeTransform3D(componentTable, componentData, bigEndian);
			break;
		default: [[unlikely]]
			std::println(std::cerr, "Type index is out of range.");
			break;
		}
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "Exception of type '{}' on serializing data. Message: '{}'.", typeid(e).name(), e.what());
	}
	catch (...)
	{
		std::println(std::cerr, "Unknown exception on serializing data.");
	}
}

void SerializeParent(const toml::table& componentTable, const std::span<std::byte> componentData, const std::unordered_map<std::string_view, std::uint64_t>& entityIDToIndex,
	const bool bigEndian)
{
	if (componentData.size() != sizeof(PonyEngine::World::Hierarchy::Parent)) [[unlikely]]
	{
		throw std::invalid_argument("Invalid component data size");
	}

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

void SerializeTransform2D(const toml::table& componentTable, const std::span<std::byte> componentData, const bool bigEndian)
{
	if (componentData.size() != sizeof(PonyEngine::World::Hierarchy::LocalTransform2D)) [[unlikely]]
	{
		throw std::invalid_argument("Invalid component data size");
	}

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

	const auto transform = PonyEngine::World::Hierarchy::LocalTransform2D(PonyEngine::Math::Vector2<double>(*positionX, *positionY),
		*rotation, PonyEngine::Math::Vector2<float>(*scaleX, *scaleY));

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(transform.Position().X());
	writer.Write(transform.Position().Y());
	writer.Write(transform.Rotation());
	writer.Write(transform.Scale().X());
	writer.Write(transform.Scale().Y());
}

void SerializeTransform3D(const toml::table& componentTable, const std::span<std::byte> componentData, const bool bigEndian)
{
	if (componentData.size() != sizeof(PonyEngine::World::Hierarchy::LocalTransform3D)) [[unlikely]]
	{
		throw std::invalid_argument("Invalid component data size");
	}

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

	const auto transform = PonyEngine::World::Hierarchy::LocalTransform3D(PonyEngine::Math::Vector3<double>(*positionX, *positionY, *positionZ),
		PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(*rotationX, *rotationY, *rotationZ) * PonyEngine::Math::DegToRad<float>),
		PonyEngine::Math::Vector3<float>(*scaleX, *scaleY, *scaleZ));

	auto writer = PonyTools::Memory::ByteWriter(componentData, bigEndian);
	writer.Write(transform.Position().X());
	writer.Write(transform.Position().Y());
	writer.Write(transform.Position().Z());
	writer.Write(transform.Rotation().X());
	writer.Write(transform.Rotation().Y());
	writer.Write(transform.Rotation().Z());
	writer.Write(transform.Rotation().W());
	writer.Write(transform.Scale().X());
	writer.Write(transform.Scale().Y());
	writer.Write(transform.Scale().Z());
}
