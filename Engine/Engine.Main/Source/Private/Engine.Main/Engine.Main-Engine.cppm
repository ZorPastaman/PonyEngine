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

export module PonyEngine.Engine.Main:Engine;

import std;

import PonyEngine.Application;
import PonyEngine.Engine.Extension;

import :SystemManager;

export namespace PonyEngine::Engine
{
	/// @brief Engine.
	class Engine final : public Application::ITickableService
	{
	public:
		/// @brief Creates an engine.
		/// @param application Application context.
		/// @param systemFactories System factories. The order of the factories may be changed.
		[[nodiscard("Pure constructor")]]
		Engine(Application::IApplicationContext& application, std::span<ISystemFactory*> systemFactories);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		virtual void Begin() override;
		virtual void End() noexcept override;
		virtual void Tick() override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:
		/// @brief Engine context.
		class EngineContext final : public IEngineContext
		{
		public:
			/// @brief Creates an engine context.
			/// @param engine Engine.
			[[nodiscard("Pure constructor")]]
			explicit EngineContext(Engine& engine) noexcept;
			EngineContext(const EngineContext&) = delete;
			EngineContext(EngineContext&&) = delete;

			~EngineContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Application::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Application::IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info& typeInfo) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindSystem(const std::type_info& typeInfo) const noexcept override;

			EngineContext& operator =(const EngineContext&) = delete;
			EngineContext& operator =(EngineContext&&) = delete;

		private:
			Engine* engine; ///< Engine.
		};

		Application::IApplicationContext* application; ///< Application.

		EngineContext engineContext; ///< Engine context.

		std::unique_ptr<SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Engine
{
	Engine::Engine(Application::IApplicationContext& application, const std::span<ISystemFactory*> systemFactories) :
		application{&application},
		engineContext(*this)
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Constructing system manager...");
		systemManager = std::make_unique<SystemManager>(engineContext, systemFactories);
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Constructing system manager done.");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Destructing system manager...");
		systemManager.reset();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Destructing system manager done.");
	}

	void Engine::Begin()
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning system manager...");
		systemManager->Begin();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning system manager done.");
	}

	void Engine::End() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending system manager...");
		systemManager->End();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending system manager done.");
	}

	void Engine::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking system manager.");
		systemManager->Tick();
	}

	Engine::EngineContext::EngineContext(Engine& engine) noexcept :
		engine{&engine}
	{
	}

	Application::IApplicationContext& Engine::EngineContext::Application() noexcept
	{
		return *engine->application;
	}

	const Application::IApplicationContext& Engine::EngineContext::Application() const noexcept
	{
		return *engine->application;
	}

	Log::ILogger& Engine::EngineContext::Logger() noexcept
	{
		return engine->application->Logger();
	}

	const Log::ILogger& Engine::EngineContext::Logger() const noexcept
	{
		return engine->application->Logger();
	}

	void* Engine::EngineContext::FindSystem(const std::type_info& typeInfo) noexcept
	{
		return engine->systemManager->FindSystem(typeInfo);
	}

	const void* Engine::EngineContext::FindSystem(const std::type_info& typeInfo) const noexcept
	{
		return engine->systemManager->FindSystem(typeInfo);
	}
}
