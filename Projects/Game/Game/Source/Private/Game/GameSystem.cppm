/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

#include "PonyDebug/Log/Log.h"

export module Game.Detail:GameSystem;

import <algorithm>;
import <array>;
import <cstdint>;
import <functional>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
import PonyMath.Space;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Render;

import Game;

export namespace Game
{
	/// @brief Game system.
	class GameSystem final : public PonyEngine::Core::TickableSystem, public IGameSystem
	{
	public:
		/// @brief Creates a game system.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param gameParams Game system parameters.
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& systemParams, const GameSystemParams& gameParams);
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		virtual ~GameSystem() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

	private:
		std::shared_ptr<PonyEngine::Input::InputHandle> forwardHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> rightHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> upHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> rotateRightHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> rotateUpHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> xHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> yHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> zHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> resetHandle;
		std::shared_ptr<PonyEngine::Input::InputHandle> exitHandle;

		std::shared_ptr<PonyEngine::Render::IRenderObject> boxHandle; ///< Box handle.
		std::shared_ptr<PonyEngine::Render::IRenderObject> background;
		PonyMath::Space::Transform3D boxTransform; ///< Box transform.
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& systemParams, const GameSystemParams&) :
		TickableSystem(engine, systemParams),
		boxTransform(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, 5.f)
	{
	}

	void GameSystem::Begin()
	{
		if (const auto inputSystem = Engine().SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Register inputs.");

			forwardHandle = inputSystem->Bind("Forward", std::function<void(float)>([&](const float input) { boxTransform.Translate(PonyMath::Core::Vector3<float>(0.f, 0.f, 5.f) * input); }));

			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Inputs registered.");
		}
		else
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Warning, "No input system found.");
		}

		if (const auto renderSystem = Engine().SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set render view params.");
			renderSystem->RenderView().ViewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity.Inverse());
			renderSystem->RenderView().ProjectionMatrix(PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, renderSystem->RenderTarget().Resolution().Aspect<float>(), 0.2f, 1000.f));
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render view params set.");

			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create triangle.");
			constexpr std::array<PonyMath::Core::Vector3<float>, 8> vertices = { PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
				PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f) };
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 12> triangles = { PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2), PonyMath::Core::Vector3<std::uint32_t>(0, 2, 3), PonyMath::Core::Vector3<std::uint32_t>(4, 6, 5), PonyMath::Core::Vector3<std::uint32_t>(4, 7, 6),
				PonyMath::Core::Vector3<std::uint32_t>(0, 4, 1), PonyMath::Core::Vector3<std::uint32_t>(1, 4, 5), PonyMath::Core::Vector3<std::uint32_t>(1, 5, 2), PonyMath::Core::Vector3<std::uint32_t>(2, 5, 6),
				PonyMath::Core::Vector3<std::uint32_t>(2, 6, 3), PonyMath::Core::Vector3<std::uint32_t>(3, 6, 7), PonyMath::Core::Vector3<std::uint32_t>(3, 7, 0), PonyMath::Core::Vector3<std::uint32_t>(0, 7, 4) };
			constexpr std::array<PonyMath::Color::RGBA<float>, 8> vertexColors = { PonyMath::Color::RGBA<float>::Predefined::Red, PonyMath::Color::RGBA<float>::Predefined::Green, PonyMath::Color::RGBA<float>::Predefined::Blue, PonyMath::Color::RGBA<float>::Predefined::Yellow,
				PonyMath::Color::RGBA<float>::Predefined::Magenta, PonyMath::Color::RGBA<float>::Predefined::Cyan, PonyMath::Color::RGBA<float>::Predefined::Gray, PonyMath::Color::RGBA<float>::Predefined::White };
			auto box = PonyMath::Geometry::Mesh();
			box.Vertices(vertices);
			box.Triangles(triangles);
			box.Colors(vertexColors);

			auto backgroundTransform = boxTransform;
			backgroundTransform.Position(PonyMath::Core::Vector3<float>(0.f, 0.f, 50.f));
			backgroundTransform.Scale(PonyMath::Core::Vector3<float>(20.f, 20.f, 1.f));
			background = renderSystem->RenderObjectManager().CreateObject(box, backgroundTransform.TrsMatrix());

			boxHandle = renderSystem->RenderObjectManager().CreateObject(box, boxTransform.TrsMatrix());
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Triangle created.");
		}
	}

	void GameSystem::End()
	{
		if (PonyEngine::Input::IInputSystem* const inputSystem = Engine().SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Unregister inputs.");

			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Inputs unregistered.");
		}
	}

	void GameSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Game tick.");
		boxHandle->ModelMatrix(boxTransform.TrsMatrix());
	}
}
