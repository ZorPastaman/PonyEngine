/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "InputSystem.h"

namespace Mocks
{
	PonyDebug::Log::ILogger& InputSystem::Logger() noexcept
	{
		return engine->Logger();
	}

	const PonyDebug::Log::ILogger& InputSystem::Logger() const noexcept
	{
		return engine->Logger();
	}

	PonyEngine::Core::ISystemManager& InputSystem::SystemManager() noexcept
	{
		return engine->SystemManager();
	}

	const PonyEngine::Core::ISystemManager& InputSystem::SystemManager() const noexcept
	{
		return engine->SystemManager();
	}

	void InputSystem::AddInputEvent(const PonyEngine::Input::InputEvent& inputEntry)
	{
		++version;
		lastEvent = inputEntry;
	}
}
