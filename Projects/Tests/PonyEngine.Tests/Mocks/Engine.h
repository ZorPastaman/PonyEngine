/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <optional>
#include <string_view>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "Application.h"

import PonyEngine.Core;

namespace Core
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
		virtual size_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCodeToSet) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		std::size_t frameCount = 0;
		std::optional<int> exitCode = {};

		Application* application = nullptr;

	private:
		mutable Core::SystemManager systemManager;
	};
}
