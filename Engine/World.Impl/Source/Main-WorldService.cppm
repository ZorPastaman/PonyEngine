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

import :ObjectRegistry;
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

		[[nodiscard("Weird call")]] 
		virtual std::shared_ptr<IWorld> CreateWorld() override;
		virtual void CollectDeadWorlds() override;

		virtual void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset) override;
		[[nodiscard("Weird call")]] 
		virtual std::pair<HandleID, HandleVersion> RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object) override;
		virtual void UnregisterObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsObjectValid(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::shared_ptr<void>& GetObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const override;
		virtual void CollectGarbage() override;

		Application::IApplicationContext* application;

		TypeRegistry typeRegistry;
		ObjectRegistry objectRegistry;

		std::vector<std::weak_ptr<const World>> worlds;
	};
}

namespace PonyEngine::World
{
	WorldService::WorldService(Application::IApplicationContext& application) noexcept :
		application{&application},
		objectRegistry{*this->application}
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

	std::shared_ptr<IWorld> WorldService::CreateWorld()
	{
		const auto world = std::make_shared<World>(typeRegistry);
		worlds.push_back(world);
		return world;
	}

	void WorldService::CollectDeadWorlds()
	{
		for (std::size_t i = worlds.size(); i-- > 0uz; )
		{
			if (worlds[i].expired())
			{
				worlds.erase(worlds.cbegin() + i);
			}
		}
	}

	void WorldService::RegisterComponentObjectHandleMember(const std::type_index objectType, const std::type_index componentType, const std::size_t componentOffset)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering component object handle member. Component type name: '{}'; Object type name: '{}'; Component offset: '{}'.",
			componentType.name(), objectType.name(), componentOffset);
		objectRegistry.RegisterComponentObjectHandleMember(objectType, componentType, componentOffset);
	}

	std::pair<HandleID, HandleVersion> WorldService::RegisterObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
#ifndef NDEBUG
		if (!object) [[unlikely]]
		{
			throw std::invalid_argument("Object is nullptr");
		}
#endif

		return objectRegistry.RegisterObject(objectType, object);
	}

	void WorldService::UnregisterObject(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion)
	{
		objectRegistry.UnregisterObject(objectType, handleId, handleVersion);
	}

	bool WorldService::IsObjectValid(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion) const noexcept
	{
		return objectRegistry.IsObjectValid(objectType, handleId, handleVersion);
	}

	const std::shared_ptr<void>& WorldService::GetObject(const std::type_index objectType, const HandleID handleId, const HandleVersion handleVersion) const
	{
		return objectRegistry.GetObject(objectType, handleId, handleVersion);
	}

	void WorldService::CollectGarbage()
	{
		CollectDeadWorlds();
		objectRegistry.CollectGarbage(worlds);
	}
}
