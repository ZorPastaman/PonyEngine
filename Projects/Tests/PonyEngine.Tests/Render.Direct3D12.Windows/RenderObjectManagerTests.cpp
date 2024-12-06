/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <memory>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"
#include "Mocks/ScreenSystem.h"

import PonyMath.Core;
import PonyMath.Geometry;

import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Render
{
	TEST_CLASS(RenderObjectManagerTests)
	{
		TEST_METHOD(CreateRenderObjectTest)
		{
			auto triangle = PonyMath::Geometry::Mesh();
			triangle.Vertices(std::array<PonyMath::Core::Vector3<float>, 3>{ PonyMath::Core::Vector3<float>(-1.f, 0.f, 0.f), PonyMath::Core::Vector3<float>(1.f, 0.f, 0.f), PonyMath::Core::Vector3<float>(0.f, 1.f, 0.f) });
			triangle.Triangles(std::array<PonyMath::Core::Vector3<std::uint32_t>, 1>{ PonyMath::Core::Vector3<std::uint32_t>(0u, 1u, 2u) });

			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::WindowsClassParams{ .name = L"Pony Engine Test" };
			auto windowsClass = PonyEngine::Window::CreateWindowsClass(application, classParams);
			auto windowFactory = PonyEngine::Window::CreateWindowsWindowFactory(application, PonyEngine::Window::WindowsWindowSystemFactoryParams{}, PonyEngine::Window::WindowsWindowSystemParams{ .windowsClass = std::move(windowsClass.windowsClass) });
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::IWindowsWindowSystem), dynamic_cast<PonyEngine::Window::IWindowsWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::CreateWindowsDirect3D12RenderSystemFactory(application, PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryParams{}, PonyEngine::Render::WindowsDirect3D12RenderSystemParams{});
			auto renderSystem = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			auto& renderObjectManager = dynamic_cast<PonyEngine::Render::IRenderSystem*>(std::get<1>(renderSystem.system).get())->RenderObjectManager();

			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == renderObjectManager.CreateObject(triangle)->ModelMatrix());

			PonyMath::Core::Matrix4x4<float> expectedMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(2.f, 4.f, 7.f), PonyMath::Core::Vector3<float>(1.1f, 0.7f, -0.3f), PonyMath::Core::Vector3<float>(2.f, 1.1f, 0.7f));
			auto object = renderObjectManager.CreateObject(triangle, expectedMatrix);
			Assert::IsTrue(expectedMatrix == object->ModelMatrix());

			std::get<1>(renderSystem.system)->Tick();
			Assert::IsNotNull(object.get());

			auto weakObject = std::weak_ptr(object);
			object.reset();
			std::get<1>(renderSystem.system)->Tick();
			Assert::IsTrue(weakObject.expired());
		}
	};
}
