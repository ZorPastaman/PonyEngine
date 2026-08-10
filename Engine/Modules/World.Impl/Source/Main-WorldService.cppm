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

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.World;

import :ObjectTable;
import :ServiceContext;
import :TypeRegistry;
import :World;

export namespace PonyEngine::World
{
	/// @brief World service.
	class WorldService final : public IWorldService
	{
	public:
		/// @brief Creates a world service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit WorldService(Application::IApplication& application) noexcept;
		WorldService(const WorldService&) = delete;
		WorldService(WorldService&&) = delete;

		~WorldService() noexcept;

		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) override;
		virtual void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset) override;

		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IWorld> CreateWorld() override;

		WorldService& operator =(const WorldService&) = delete;
		WorldService& operator =(WorldService&&) = delete;

	private:
		Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.

		TypeRegistry typeRegistry; ///< Type registry.

		ServiceContext context; ///< World service context.
	};
}

namespace PonyEngine::World
{
	WorldService::WorldService(Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		context(*this->application, typeRegistry)
	{
	}

	WorldService::~WorldService() noexcept
	{
		context.EnsureZeroCounts();
	}

	void WorldService::RegisterComponent(const std::type_index componentType, const std::size_t componentSize, const std::size_t componentAlignment)
	{
		PONY_LOG(logService, Log::LogType::Info, "Registering component type. Type name: '{}'; size: '{}'; alignment: '{}'.", 
			componentType.name(), componentSize, componentAlignment);
		typeRegistry.AddComponentType(componentType, componentSize, componentAlignment);
	}

	void WorldService::RegisterComponentObjectHandleMember(const std::type_index objectType, const std::type_index componentType, const std::size_t componentOffset)
	{
		PONY_LOG(logService, Log::LogType::Info, "Registering component object handle member. Component type name: '{}'; Object type name: '{}'; Component offset: '{}'.",
			componentType.name(), objectType.name(), componentOffset);
		typeRegistry.RegisterComponentObjectHandleMember(objectType, componentType, componentOffset);
	}

	std::shared_ptr<IWorld> WorldService::CreateWorld()
	{
		return std::make_shared<World>(context);
	}
}
