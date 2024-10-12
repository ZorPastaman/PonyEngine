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

export module Game.Implementation:GameSystem;

import <cstdint>;
import <functional>;

import PonyMath.Core;
import PonyMath.Geometry;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Render;
import PonyEngine.Window;

export namespace Game
{
	/// @brief Game system.
	class GameSystem final : public PonyEngine::Core::ISystem, public PonyEngine::Core::ITickableSystem
	{
	public:
		/// @brief Creates a game system.
		/// @param engine Engine.
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Core::IEngine& engine);
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		~GameSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

		static constexpr auto StaticName = "Game::GameSystem"; ///< Class name.

	private:
		PonyEngine::Input::Handle upHandle; ///< Up arrow input handle.
		PonyEngine::Input::Handle downHandle; ///< Down arrow input handle.
		PonyEngine::Input::Handle rightHandle; ///< Right arrow input handle.
		PonyEngine::Input::Handle leftHandle; ///< Left arrow input handle.
		PonyEngine::Input::Handle closeHandle; ///< Escape input handle.

		PonyEngine::Render::RenderObjectHandle boxHandle; ///< Box handle.
		PonyMath::Core::Vector3<float> boxPosition; ///< Box position.
		PonyMath::Core::Vector3<float> boxRotation; ///< Box rotation.
		PonyMath::Core::Vector3<float> boxScale; ///< Box scale.

		PonyEngine::Core::IEngine* const engine; ///< Engine.
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngine& engine) :
		upHandle(),
		downHandle(),
		rightHandle(),
		leftHandle(),
		closeHandle(),
		boxHandle(),
		boxPosition(0.f, 0.f, 20.f),
		boxRotation(PonyMath::Core::Vector3<float>::Predefined::Zero),
		boxScale(PonyMath::Core::Vector3<float>::Predefined::One * 5.f),
		engine{&engine}
	{
	}

	void GameSystem::Begin()
	{
		if (const auto inputSystem = engine->SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Register inputs.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register up input.");
			constexpr auto upMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowUp, .isDown = true};
			constexpr auto upEvent = PonyEngine::Input::Event{.expectedMessage = upMessage};
			upHandle = inputSystem->RegisterAction(upEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindowSystem* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindowSystem>())
				{
					window->SecondaryTitle(L"Up");
				}
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxRotation.X() += 10.f * PonyMath::Core::DegToRad<float>;
					const PonyMath::Core::Matrix4x4<float> trs = PonyMath::Core::TrsMatrix(boxPosition, boxRotation, boxScale);
					render->UpdateRenderObjectTrs(boxHandle, trs);
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Up input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register down input.");
			constexpr auto downMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowDown, .isDown = true};
			constexpr auto downEvent = PonyEngine::Input::Event{.expectedMessage = downMessage};
			downHandle = inputSystem->RegisterAction(downEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindowSystem* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindowSystem>())
				{
					window->SecondaryTitle(L"Down");
				}
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxRotation.X() -= 10.f * PonyMath::Core::DegToRad<float>;
					const PonyMath::Core::Matrix4x4<float> trs = PonyMath::Core::TrsMatrix(boxPosition, boxRotation, boxScale);
					render->UpdateRenderObjectTrs(boxHandle, trs);
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Down input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register right input.");
			constexpr auto rightMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowRight, .isDown = true};
			constexpr auto rightEvent = PonyEngine::Input::Event{.expectedMessage = rightMessage};
			rightHandle = inputSystem->RegisterAction(rightEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindowSystem* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindowSystem>())
				{
					window->SecondaryTitle(L"Right");
				}
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxRotation.Y() -= 10.f * PonyMath::Core::DegToRad<float>;
					const PonyMath::Core::Matrix4x4<float> trs = PonyMath::Core::TrsMatrix(boxPosition, boxRotation, boxScale);
					render->UpdateRenderObjectTrs(boxHandle, trs);
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Right input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register left input.");
			constexpr auto leftMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowLeft, .isDown = true};
			constexpr auto leftEvent = PonyEngine::Input::Event{.expectedMessage = leftMessage};
			leftHandle = inputSystem->RegisterAction(leftEvent, std::bind([&]
			{
				if (PonyEngine::Window::IWindowSystem* const window = engine->SystemManager().FindSystem<PonyEngine::Window::IWindowSystem>())
				{
					window->SecondaryTitle(L"Left");
				}
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxRotation.Y() += 10.f * PonyMath::Core::DegToRad<float>;
					const PonyMath::Core::Matrix4x4<float> trs = PonyMath::Core::TrsMatrix(boxPosition, boxRotation, boxScale);
					render->UpdateRenderObjectTrs(boxHandle, trs);
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Left input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register close input.");
			constexpr auto escapeMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Escape, .isDown = false};
			constexpr auto escapeEvent = PonyEngine::Input::Event{.expectedMessage = escapeMessage};
			closeHandle = inputSystem->RegisterAction(escapeEvent, std::bind([&]{engine->Stop();}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Close input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Inputs registered.");
		}
		else
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Warning, "No input system found.");
		}

		if (const auto renderSystem = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Create triangle.");
			constexpr PonyMath::Core::Vector3<float> vertices[] = { PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
				PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f) };
			constexpr PonyMath::Core::Vector3<std::uint32_t> vertexTriangles[] = { PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2), PonyMath::Core::Vector3<std::uint32_t>(0, 2, 3), PonyMath::Core::Vector3<std::uint32_t>(4, 6, 5), PonyMath::Core::Vector3<std::uint32_t>(4, 7, 6),
				PonyMath::Core::Vector3<std::uint32_t>(0, 4, 1), PonyMath::Core::Vector3<std::uint32_t>(1, 4, 5), PonyMath::Core::Vector3<std::uint32_t>(1, 5, 2), PonyMath::Core::Vector3<std::uint32_t>(2, 5, 6),
				PonyMath::Core::Vector3<std::uint32_t>(2, 6, 3), PonyMath::Core::Vector3<std::uint32_t>(3, 6, 7), PonyMath::Core::Vector3<std::uint32_t>(3, 7, 0), PonyMath::Core::Vector3<std::uint32_t>(0, 7, 4) };
			constexpr PonyMath::Core::RGBA<float> vertexColors[] = { PonyMath::Core::RGBA<float>::Predefined::Red, PonyMath::Core::RGBA<float>::Predefined::Green, PonyMath::Core::RGBA<float>::Predefined::Blue, PonyMath::Core::RGBA<float>::Predefined::Yellow,
				PonyMath::Core::RGBA<float>::Predefined::Magenta, PonyMath::Core::RGBA<float>::Predefined::Cyan, PonyMath::Core::RGBA<float>::Predefined::Gray, PonyMath::Core::RGBA<float>::Predefined::White };
			auto box = PonyMath::Geometry::Mesh();
			box.Vertices(vertices);
			box.Triangles(vertexTriangles);
			box.Colors(vertexColors);
			const PonyMath::Core::Matrix4x4<float> trs = PonyMath::Core::TrsMatrix(boxPosition, boxRotation, boxScale);
			boxHandle = renderSystem->CreateRenderObject(box, trs);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Triangle created.");
		}
	}

	void GameSystem::End()
	{
		if (PonyEngine::Input::IInputSystem* const inputSystem = engine->SystemManager().FindSystem<PonyEngine::Input::IInputSystem>())
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Unregister inputs.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister up input.");
			inputSystem->UnregisterAction(upHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Up input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister down input.");
			inputSystem->UnregisterAction(downHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Down input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister right input.");
			inputSystem->UnregisterAction(rightHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Right input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister left input.");
			inputSystem->UnregisterAction(leftHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Left input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister close input.");
			inputSystem->UnregisterAction(closeHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Close input unregistered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Inputs unregistered.");
		}

		if (const auto renderSystem = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Destroy triangle.");
			renderSystem->DestroyRenderObject(boxHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Triangle destroyed.");
		}
	}

	void GameSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Game tick.");
	}

	const char* GameSystem::Name() const noexcept
	{
		return StaticName;
	}
}
