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

import <algorithm>;
import <array>;
import <cstdint>;
import <functional>;

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
	class GameSystem final : public PonyEngine::Core::ITickableEngineSystem, public IGameSystem
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
		PonyEngine::Input::Handle wHandle; ///< W input handle.
		PonyEngine::Input::Handle sHandle; ///< S input handle.
		PonyEngine::Input::Handle aHandle; ///< A input handle.
		PonyEngine::Input::Handle dHandle; ///< D input handle.
		PonyEngine::Input::Handle spaceHandle; ///< Space input handle.
		PonyEngine::Input::Handle controlHandle; ///< Control input handle.
		PonyEngine::Input::Handle zHandle; ///< Z input handle.
		PonyEngine::Input::Handle xHandle; ///< X input handle.
		PonyEngine::Input::Handle cHandle; ///< C input handle.
		PonyEngine::Input::Handle vHandle; ///< V input handle.
		PonyEngine::Input::Handle bHandle; ///< B input handle.
		PonyEngine::Input::Handle nHandle; ///< N input handle.
		PonyEngine::Input::Handle enterHandle; ///< Enter input handle.
		PonyEngine::Input::Handle closeHandle; ///< Escape input handle.

		PonyEngine::Render::RenderObjectHandle boxHandle; ///< Box handle.
		PonyMath::Space::Transform3D boxTransform; ///< Box transform.

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
		wHandle(),
		sHandle(),
		aHandle(),
		dHandle(),
		spaceHandle(),
		controlHandle(),
		zHandle(),
		xHandle(),
		cHandle(),
		vHandle(),
		bHandle(),
		nHandle(),
		enterHandle(),
		closeHandle(),
		boxHandle(),
		boxTransform(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, 5.f),
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
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Rotate(PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(10.f * PonyMath::Core::DegToRad<float>, 0.f, 0.f)));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Up input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register down input.");
			constexpr auto downMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowDown, .isDown = true};
			constexpr auto downEvent = PonyEngine::Input::Event{.expectedMessage = downMessage};
			downHandle = inputSystem->RegisterAction(downEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Rotate(PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(-10.f * PonyMath::Core::DegToRad<float>, 0.f, 0.f)));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Down input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register right input.");
			constexpr auto rightMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowRight, .isDown = true};
			constexpr auto rightEvent = PonyEngine::Input::Event{.expectedMessage = rightMessage};
			rightHandle = inputSystem->RegisterAction(rightEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Rotate(PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, -10.f * PonyMath::Core::DegToRad<float>, 0.f)));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Right input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register left input.");
			constexpr auto leftMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::ArrowLeft, .isDown = true};
			constexpr auto leftEvent = PonyEngine::Input::Event{.expectedMessage = leftMessage};
			leftHandle = inputSystem->RegisterAction(leftEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Rotate(PonyMath::Core::RotationQuaternion(PonyMath::Core::Vector3<float>(0.f, 10.f * PonyMath::Core::DegToRad<float>, 0.f)));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Left input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register w input.");
			constexpr auto wMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::W, .isDown = true};
			constexpr auto wEvent = PonyEngine::Input::Event{.expectedMessage = wMessage};
			wHandle = inputSystem->RegisterAction(wEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(0.f, 0.f, 5.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "W input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register s input.");
			constexpr auto sMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::S, .isDown = true};
			constexpr auto sEvent = PonyEngine::Input::Event{.expectedMessage = sMessage};
			sHandle = inputSystem->RegisterAction(sEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(0.f, 0.f, -5.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "S input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register a input.");
			constexpr auto aMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::A, .isDown = true};
			constexpr auto aEvent = PonyEngine::Input::Event{.expectedMessage = aMessage};
			aHandle = inputSystem->RegisterAction(aEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(-5.f, 0.f, 0.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "A input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register d input.");
			constexpr auto dMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::D, .isDown = true};
			constexpr auto dEvent = PonyEngine::Input::Event{.expectedMessage = dMessage};
			dHandle = inputSystem->RegisterAction(dEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(5.f, 0.f, 0.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "A input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register space input.");
			constexpr auto spaceMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Space, .isDown = true};
			constexpr auto spaceEvent = PonyEngine::Input::Event{.expectedMessage = spaceMessage};
			spaceHandle = inputSystem->RegisterAction(spaceEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(0.f, 5.f, 0.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Space input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register control input.");
			constexpr auto controlMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::LeftCtrl, .isDown = true};
			constexpr auto controlEvent = PonyEngine::Input::Event{.expectedMessage = controlMessage};
			controlHandle = inputSystem->RegisterAction(controlEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Translate(PonyMath::Core::Vector3<float>(0.f, -5.f, 0.f));
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Control input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register z input.");
			constexpr auto zMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Z, .isDown = true};
			constexpr auto zEvent = PonyEngine::Input::Event{.expectedMessage = zMessage};
			zHandle = inputSystem->RegisterAction(zEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.X() -= 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Z input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register x input.");
			constexpr auto xMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::X, .isDown = true};
			constexpr auto xEvent = PonyEngine::Input::Event{.expectedMessage = xMessage};
			xHandle = inputSystem->RegisterAction(xEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.X() += 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "X input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register c input.");
			constexpr auto cMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::C, .isDown = true};
			constexpr auto cEvent = PonyEngine::Input::Event{.expectedMessage = cMessage};
			cHandle = inputSystem->RegisterAction(cEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.Y() -= 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "C input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register v input.");
			constexpr auto vMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::V, .isDown = true};
			constexpr auto vEvent = PonyEngine::Input::Event{.expectedMessage = vMessage};
			vHandle = inputSystem->RegisterAction(vEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.Y() += 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "V input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register b input.");
			constexpr auto bMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::B, .isDown = true};
			constexpr auto bEvent = PonyEngine::Input::Event{.expectedMessage = bMessage};
			bHandle = inputSystem->RegisterAction(bEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.Z() -= 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "B input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register n input.");
			constexpr auto nMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::N, .isDown = true};
			constexpr auto nEvent = PonyEngine::Input::Event{.expectedMessage = nMessage};
			nHandle = inputSystem->RegisterAction(nEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					auto scale = boxTransform.Scale();
					scale.Z() += 0.2;
					boxTransform.Scale(scale);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "N input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register enter input.");
			constexpr auto enterMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Enter, .isDown = true};
			constexpr auto enterEvent = PonyEngine::Input::Event{.expectedMessage = enterMessage};
			enterHandle = inputSystem->RegisterAction(enterEvent, std::bind([&]
			{
				if (const auto render = engine->SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>())
				{
					boxTransform.Position(PonyMath::Core::Vector3<float>(0.f, 0.f, 20.f));
					boxTransform.Rotation(PonyMath::Core::Quaternion<float>::Predefined::Identity);
					render->UpdateRenderObjectTrs(boxHandle, boxTransform.TrsMatrix());
				}
			}));
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Control input registered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Register close input.");
			constexpr auto escapeMessage = PonyEngine::Input::KeyboardMessage{.keyCode = PonyEngine::Input::KeyboardKeyCode::Escape, .isDown = false};
			constexpr auto escapeEvent = PonyEngine::Input::Event{.expectedMessage = escapeMessage};
			closeHandle = inputSystem->RegisterAction(escapeEvent, std::bind([&]
			{
				engine->Stop();
			}));
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
			constexpr std::array<PonyMath::Core::Vector3<float>, 8> vertices = { PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
				PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f), PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f), PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f) };
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 12> triangles = { PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2), PonyMath::Core::Vector3<std::uint32_t>(0, 2, 3), PonyMath::Core::Vector3<std::uint32_t>(4, 6, 5), PonyMath::Core::Vector3<std::uint32_t>(4, 7, 6),
				PonyMath::Core::Vector3<std::uint32_t>(0, 4, 1), PonyMath::Core::Vector3<std::uint32_t>(1, 4, 5), PonyMath::Core::Vector3<std::uint32_t>(1, 5, 2), PonyMath::Core::Vector3<std::uint32_t>(2, 5, 6),
				PonyMath::Core::Vector3<std::uint32_t>(2, 6, 3), PonyMath::Core::Vector3<std::uint32_t>(3, 6, 7), PonyMath::Core::Vector3<std::uint32_t>(3, 7, 0), PonyMath::Core::Vector3<std::uint32_t>(0, 7, 4) };
			constexpr std::array<PonyMath::Core::RGBA<float>, 8> vertexColors = { PonyMath::Core::RGBA<float>::Predefined::Red, PonyMath::Core::RGBA<float>::Predefined::Green, PonyMath::Core::RGBA<float>::Predefined::Blue, PonyMath::Core::RGBA<float>::Predefined::Yellow,
				PonyMath::Core::RGBA<float>::Predefined::Magenta, PonyMath::Core::RGBA<float>::Predefined::Cyan, PonyMath::Core::RGBA<float>::Predefined::Gray, PonyMath::Core::RGBA<float>::Predefined::White };
			auto box = PonyMath::Geometry::Mesh();
			box.Vertices(vertices);
			box.Triangles(triangles);
			box.Colors(vertexColors);
			boxHandle = renderSystem->CreateRenderObject(box, boxTransform.TrsMatrix());
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
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister w input.");
			inputSystem->UnregisterAction(wHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "W input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister s input.");
			inputSystem->UnregisterAction(sHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "S input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister a input.");
			inputSystem->UnregisterAction(aHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "A input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister d input.");
			inputSystem->UnregisterAction(dHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "D input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister space input.");
			inputSystem->UnregisterAction(spaceHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Space input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister control input.");
			inputSystem->UnregisterAction(controlHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Control input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister z input.");
			inputSystem->UnregisterAction(zHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Z input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister x input.");
			inputSystem->UnregisterAction(xHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "X input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister c input.");
			inputSystem->UnregisterAction(cHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "C input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister v input.");
			inputSystem->UnregisterAction(vHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "V input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister b input.");
			inputSystem->UnregisterAction(bHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "B input unregistered.");
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Unregister n input.");
			inputSystem->UnregisterAction(nHandle);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "N input unregistered.");
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
