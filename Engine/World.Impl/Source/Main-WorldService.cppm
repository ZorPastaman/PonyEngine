/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.World.Impl:WorldService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.World;

import :TypeRegistry;
import :World;

export namespace PonyEngine::World
{
	class WorldService final : public Application::IService, private IWorldService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WorldService(Application::IApplicationContext& application) noexcept;
		WorldService(const WorldService&) = delete;
		WorldService(WorldService&&) = delete;

		~WorldService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		WorldService& operator =(const WorldService&) = delete;
		WorldService& operator =(WorldService&&) = delete;

	private:
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) override;
		virtual void RegisterTag(std::type_index tagType) override;

		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IWorld> CreateWorld() override;

		Application::IApplicationContext* application;

		TypeRegistry typeRegistry;
	};
}

namespace PonyEngine::World
{
	WorldService::WorldService(Application::IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	void WorldService::Begin()
	{
	}

	void WorldService::End()
	{
	}

	void WorldService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IWorldService>(*this);
	}

	void WorldService::RegisterComponent(const std::type_index componentType, const std::size_t componentSize, const std::size_t componentAlignment)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering component type. Type name: '{}'; size: '{}'; alignment: '{}'.", 
			componentType.name(), componentSize, componentAlignment);
		typeRegistry.AddComponentType(componentType, componentSize, componentAlignment);
	}

	void WorldService::RegisterTag(const std::type_index tagType)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering tag type. Type name: '{}'.", tagType.name());
		typeRegistry.AddTagType(tagType);
	}

	std::shared_ptr<IWorld> WorldService::CreateWorld()
	{
		return std::make_shared<World>(*application, typeRegistry);
	}
}
