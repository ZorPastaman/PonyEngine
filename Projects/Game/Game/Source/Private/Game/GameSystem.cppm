/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module Game.Detail:GameSystem;

import <array>;
import <cstdint>;
import <functional>;
import <memory>;
import <stdexcept>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
import PonyMath.Space;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Render;
import PonyEngine.Time;

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
		PonyEngine::Input::IInputSystem* inputSystem;
		PonyEngine::Render::IRenderSystem* renderSystem;
		PonyEngine::Time::ITimeSystem* timeSystem;

		std::shared_ptr<PonyEngine::Input::InputReceiver> resetHandle;
		std::shared_ptr<PonyEngine::Input::InputReceiver> exitHandle;
		std::shared_ptr<PonyEngine::Input::InputReceiver> mouseXHandle;
		std::shared_ptr<PonyEngine::Input::InputReceiver> mouseYHandle;

		std::shared_ptr<PonyEngine::Render::IRenderObject> boxHandle;
		std::shared_ptr<PonyEngine::Render::IRenderObject> bigBoxHandle;

		PonyMath::Space::Transform3D cameraTransform;
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& systemParams, const GameSystemParams&) :
		TickableSystem(engine, systemParams),
		inputSystem{nullptr},
		timeSystem{nullptr},
		cameraTransform(PonyMath::Core::Vector3<float>::Predefined::Zero, PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One)
	{
	}

	void GameSystem::Begin()
	{
		inputSystem = Engine().SystemManager().FindSystem<PonyEngine::Input::IInputSystem>();
		if (!inputSystem)
		{
			throw std::logic_error("Failed to get input system.");
		}
		renderSystem = Engine().SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>();
		if (!renderSystem)
		{
			throw std::logic_error("Failed to get render system");
		}
		timeSystem = Engine().SystemManager().FindSystem<PonyEngine::Time::ITimeSystem>();
		if (!timeSystem)
		{
			throw std::logic_error("Failed to find time system");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Register inputs.");
		(resetHandle = inputSystem->CreateReceiver("Reset"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { cameraTransform.Position(PonyMath::Core::Vector3<float>::Predefined::Zero); cameraTransform.Rotation(PonyMath::Core::Quaternion<float>::Predefined::Identity); cameraTransform.Scale(PonyMath::Core::Vector3<float>::Predefined::One); })));
		(exitHandle = inputSystem->CreateReceiver("Exit"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { Engine().Stop(); }, false)));
		(mouseXHandle = inputSystem->CreateReceiver("MouseX"))->Action([&](const float input) { cameraTransform.Rotate(PonyMath::Core::RotationQuaternion(cameraTransform.Up(), input)); });
		(mouseYHandle = inputSystem->CreateReceiver("MouseY"))->Action([&](const float input) { cameraTransform.Rotate(PonyMath::Core::RotationQuaternion(cameraTransform.Right(), input)); });
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Inputs registered.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set render view params.");
		renderSystem->RenderView().ViewMatrix(cameraTransform.TrsMatrix().Inverse());
		renderSystem->RenderView().ProjectionMatrix(PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, renderSystem->RenderTarget().Resolution().Aspect<float>(), 0.2f, 1000.f));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render view params set.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create render objects.");
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
		boxHandle = renderSystem->RenderObjectManager().CreateObject(box, PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One * 5.f));
		bigBoxHandle = renderSystem->RenderObjectManager().CreateObject(box, PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 50.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(20.f, 20.f, 5.f)));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render objects created.");
	}

	void GameSystem::End()
	{
	}

	void GameSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Game tick.");

		auto moveDirection = PonyMath::Core::Vector3<float>(inputSystem->State("Right"), inputSystem->State("Up"), inputSystem->State("Forward"));
		moveDirection.Normalize();
		if (moveDirection.IsFinite())
		{
			cameraTransform.Translate(cameraTransform.Rotation() * (moveDirection * (10.f * timeSystem->VirtualDeltaTime())));
		}

		renderSystem->RenderView().ViewMatrix(cameraTransform.TrsMatrix().Inverse());
	}
}
