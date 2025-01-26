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

import PonyBase.Container;

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
		std::shared_ptr<PonyEngine::Render::ICamera> camera;
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
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render view params set.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create render objects.");
		const auto meshlets = PonyBase::Container::Buffer::Create<PonyEngine::Render::Meshlet>(std::array<PonyEngine::Render::Meshlet, 2>
		{
			PonyEngine::Render::Meshlet(0u, 0u, 7u, 6u),
			PonyEngine::Render::Meshlet(7u, 0u, 7u, 6u)
		});
		const auto vertexIndices = PonyBase::Container::Buffer::Create<std::uint32_t>(std::array<std::uint32_t, 14>
		{
			0u, 1u, 2u, 3u, 7u, 4u, 5u, 6u, 7u, 3u, 2u, 1u, 5u, 4u
		});
		const auto triangles = PonyBase::Container::Buffer::Create<PonyEngine::Render::PackedPrimitive>(std::array<PonyEngine::Render::PackedPrimitive, 6>
		{
			PonyEngine::Render::PackedPrimitive(0u, 1u, 2u),
			PonyEngine::Render::PackedPrimitive(0u, 2u, 3u),
			PonyEngine::Render::PackedPrimitive(4u, 5u, 0u),
			PonyEngine::Render::PackedPrimitive(4u, 0u, 3u),
			PonyEngine::Render::PackedPrimitive(5u, 6u, 1u),
			PonyEngine::Render::PackedPrimitive(5u, 1u, 0u)
		});
		const auto positions = PonyBase::Container::Buffer::Create<PonyMath::Core::Vector3<float>>(std::array<PonyMath::Core::Vector3<float>, 8>
		{
			PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f)
		});
		const auto colors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array<PonyMath::Color::RGBA<float>, 8>
		{
			PonyMath::Color::RGBA<float>::Predefined::Red,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Gray,
			PonyMath::Color::RGBA<float>::Predefined::White
		});
		auto meshParams = PonyEngine::Render::MeshParams();
		meshParams.bufferTables["Meshlets"] = std::vector<PonyBase::Container::Buffer>{ meshlets, vertexIndices, triangles };
		meshParams.bufferTables["Positions"] = std::vector<PonyBase::Container::Buffer>{ positions };
		meshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ colors };
		meshParams.threadGroupCounts = { 2u, 1u, 1u };
		meshParams.name = "Box";
		const auto mesh = std::make_shared<PonyEngine::Render::Mesh>(meshParams);
		boxHandle = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams{.mesh = mesh, .modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One * 5.f)});
		bigBoxHandle = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams{.mesh = mesh, .modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 0.f, 50.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(20.f, 20.f, 5.f))});
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render objects created.");

		camera = renderSystem->CameraManager().CreateCamera(PonyEngine::Render::CameraParams{});
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

		camera->ViewMatrix(cameraTransform.TrsMatrix().Inverse());
	}
}
