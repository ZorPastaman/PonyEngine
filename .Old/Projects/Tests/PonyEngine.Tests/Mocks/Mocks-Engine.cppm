/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:Engine;

import <cstdint>;
import <optional>;
import <typeindex>;
import <unordered_map>;

import PonyEngine.Core;

import :Application;

export namespace Mocks
{
	class SystemManager final : public PonyEngine::Core::ISystemManager
	{
	public:
		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override;

		std::unordered_map<std::type_index, void*> types;
	};

	class Engine final : public PonyEngine::Core::Engine, public PonyEngine::Core::IEngineContext
	{
	public:
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::ISystemManager& SystemManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyEngine::Core::ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCodeToSet) noexcept override;

		virtual void Tick() override;

		std::int64_t frameCount = 0;
		std::optional<int> exitCode = {};

		Application* application = nullptr;

	private:
		mutable Mocks::SystemManager systemManager;
	};
}

namespace Mocks
{
	void* SystemManager::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		if (const auto position = types.find(typeInfo); position != types.cend())
		{
			return position->second;
		}

		return nullptr;
	}

	std::uint64_t Engine::FrameCount() const noexcept
	{
		return frameCount;
	}

	PonyDebug::Log::ILogger& Engine::Logger() noexcept
	{
		return application->Logger();
	}

	const PonyDebug::Log::ILogger& Engine::Logger() const noexcept
	{
		return application->Logger();
	}

	PonyEngine::Core::ISystemManager& Engine::SystemManager() noexcept
	{
		return systemManager;
	}

	const PonyEngine::Core::ISystemManager& Engine::SystemManager() const noexcept
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

	void Engine::Stop(const int exitCodeToSet) noexcept
	{
		exitCode = exitCodeToSet;
	}

	void Engine::Tick()
	{
		++frameCount;
	}
}
