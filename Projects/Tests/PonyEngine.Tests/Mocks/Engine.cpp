/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Engine.h"

namespace Core
{
	void* SystemManager::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		if (const auto position = types.find(typeInfo); position != types.cend())
		{
			return position->second;
		}

		return nullptr;
	}

	size_t Engine::FrameCount() const noexcept
	{
		return frameCount;
	}

	PonyDebug::Log::ILogger& Engine::Logger() const noexcept
	{
		return application->Logger();
	}

	PonyEngine::Core::ISystemManager& Engine::SystemManager() const noexcept
	{
		return systemManager;
	}

	bool Engine::IsRunning() const noexcept
	{
		return !exitCode;
	}

	int Engine::ExitCode() const noexcept
	{
		return exitCode.value();
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		this->exitCode = exitCode;
	}

	void Engine::Tick()
	{
		++frameCount;
	}

	std::string_view Engine::Name() const noexcept
	{
		return "TestEngine";
	}
}
