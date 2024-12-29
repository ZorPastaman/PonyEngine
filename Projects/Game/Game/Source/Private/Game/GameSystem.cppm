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
import <span>;
import <stdexcept>;

import PonyMath.Color;
import PonyMath.Core;
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
		renderSystem{nullptr},
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
		(resetHandle = inputSystem->CreateReceiver("Reset"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { cameraTransform.Position() = PonyMath::Core::Vector3<float>::Predefined::Zero; cameraTransform.Rotation() = PonyMath::Core::Quaternion<float>::Predefined::Identity; cameraTransform.Scale() = PonyMath::Core::Vector3<float>::Predefined::One; })));
		(exitHandle = inputSystem->CreateReceiver("Exit"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { Engine().Stop(); }, false)));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Inputs registered.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set render view params.");
		renderSystem->RenderView().ViewMatrix(cameraTransform.TrsMatrix().Inverse());
		renderSystem->RenderView().ProjectionMatrix(PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, renderSystem->RenderTarget().Resolution().Aspect<float>(), 0.2f, 1000.f));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render view params set.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create render objects.");
		auto mesh = PonyEngine::Render::Mesh();
		PonyBase::Container::BufferView<PonyEngine::Render::Meshlet> meshlets = mesh.CreateBuffer<PonyEngine::Render::Meshlet>("Meshlets", 2);
		meshlets[0] = PonyEngine::Render::Meshlet{.vertexOffset = 0u, .vertexCount = 7u, .primitiveOffset = 0u, .primitiveCount = 6u};
		meshlets[1] = PonyEngine::Render::Meshlet{.vertexOffset = 7u, .vertexCount = 7u, .primitiveOffset = 0u, .primitiveCount = 6u};
		PonyBase::Container::BufferView<std::uint32_t> vertexIndices = mesh.CreateBuffer<std::uint32_t>("Meshlets", 14);
		vertexIndices[0] = 0u;
		vertexIndices[1] = 1u;
		vertexIndices[2] = 2u;
		vertexIndices[3] = 3u;
		vertexIndices[4] = 7u;
		vertexIndices[5] = 4u;
		vertexIndices[6] = 5u;
		vertexIndices[7] = 6u;
		vertexIndices[8] = 7u;
		vertexIndices[9] = 3u;
		vertexIndices[10] = 2u;
		vertexIndices[11] = 1u;
		vertexIndices[12] = 5u;
		vertexIndices[13] = 4u;
		PonyBase::Container::BufferView<PonyEngine::Render::Primitive> triangles = mesh.CreateBuffer<PonyEngine::Render::Primitive>("Meshlets", 6);
		triangles[0] = PonyEngine::Render::Primitive{.indices = { 0u, 1u, 2u, 0u }};
		triangles[1] = PonyEngine::Render::Primitive{.indices = { 0u, 2u, 3u, 0u }};
		triangles[2] = PonyEngine::Render::Primitive{.indices = { 4u, 5u, 0u, 0u }};
		triangles[3] = PonyEngine::Render::Primitive{.indices = { 4u, 0u, 3u, 0u }};
		triangles[4] = PonyEngine::Render::Primitive{.indices = { 5u, 6u, 1u, 0u }};
		triangles[5] = PonyEngine::Render::Primitive{.indices = { 5u, 1u, 0u, 0u }};
		PonyBase::Container::BufferView<PonyMath::Core::Vector3<float>> positions = mesh.CreateBuffer<PonyMath::Core::Vector3<float>>("Positions", 8);
		positions[0] = PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f);
		positions[1] = PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f);
		positions[2] = PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f);
		positions[3] = PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f);
		positions[4] = PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f);
		positions[5] = PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f);
		positions[6] = PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f);
		positions[7] = PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f);
		PonyBase::Container::BufferView<PonyMath::Color::RGBA<float>> colors = mesh.CreateBuffer<PonyMath::Color::RGBA<float>>("Colors", 8);
		colors[0] = PonyMath::Color::RGBA<float>::Predefined::Red;
		colors[1] = PonyMath::Color::RGBA<float>::Predefined::Green;
		colors[2] = PonyMath::Color::RGBA<float>::Predefined::Blue;
		colors[3] = PonyMath::Color::RGBA<float>::Predefined::Yellow;
		colors[4] = PonyMath::Color::RGBA<float>::Predefined::Magenta;
		colors[5] = PonyMath::Color::RGBA<float>::Predefined::Cyan;
		colors[6] = PonyMath::Color::RGBA<float>::Predefined::Gray;
		colors[7] = PonyMath::Color::RGBA<float>::Predefined::White;
		std::span<std::uint32_t> threadGroupCounts = mesh.ThreadGroupCounts();
		threadGroupCounts[0] = 2u;
		threadGroupCounts[1] = 1u;
		threadGroupCounts[2] = 1u;
		boxHandle = renderSystem->RenderObjectManager().CreateObject(mesh, PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One * 5.f));
		bigBoxHandle = renderSystem->RenderObjectManager().CreateObject(mesh, PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 50.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(20.f, 20.f, 5.f)));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render objects created.");
	}

	void GameSystem::End()
	{
	}

	void GameSystem::Tick()
	{
		const auto mouse = cameraTransform.Rotation() * PonyMath::Core::Vector3<float>(inputSystem->State("MouseX"), inputSystem->State("MouseY"), 0.f);
		auto rotationAxis = PonyMath::Core::Cross(cameraTransform.Forward(), mouse);
		const auto rotation = rotationAxis.Magnitude();
		rotationAxis *= 1.f / rotation;
		if (rotationAxis.IsFinite())
		{
			cameraTransform.Rotate(PonyMath::Core::RotationQuaternion(rotationAxis, rotation));
		}

		cameraTransform.Rotate(PonyMath::Core::RotationQuaternion(cameraTransform.Forward(), inputSystem->State("Rotate") * (0.5f * timeSystem->VirtualDeltaTime())));

		auto moveDirection = PonyMath::Core::Vector3<float>(inputSystem->State("Right"), inputSystem->State("Up"), inputSystem->State("Forward"));
		moveDirection.Normalize();
		if (moveDirection.IsFinite())
		{
			cameraTransform.Translate(cameraTransform.Rotation() * (moveDirection * (10.f * timeSystem->VirtualDeltaTime())));
		}

		renderSystem->RenderView().ViewMatrix(cameraTransform.TrsMatrix().Inverse());
	}
}
