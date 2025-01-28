/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <cstdint>
#include <memory>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"
#include "Mocks/ScreenSystem.h"

import PonyBase.Container;

import PonyMath.Core;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows.Impl;
import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Render
{
	TEST_CLASS(RenderObjectTests)
	{
		TEST_METHOD(ModelMatrixTest)
		{
			const auto meshlets = PonyBase::Container::Buffer::Create<PonyEngine::Render::Meshlet>(std::array<PonyEngine::Render::Meshlet, 1>
			{
				PonyEngine::Render::Meshlet(0u, 0u, 3u, 1u)
			});
			const auto vertexIndices = PonyBase::Container::Buffer::Create<std::uint32_t>(std::array<std::uint32_t, 3>
			{
				0u, 1u, 2u
			});
			const auto triangles = PonyBase::Container::Buffer::Create<PonyEngine::Render::Primitive>(std::array<PonyEngine::Render::Primitive, 1>
			{
				PonyEngine::Render::Primitive(0u, 1u, 2u)
			});
			const auto positions = PonyBase::Container::Buffer::Create<PonyMath::Core::Vector3<float>>(std::array<PonyMath::Core::Vector3<float>, 8>
			{
				PonyMath::Core::Vector3<float>(-1.f, -1.f, 0.f),
				PonyMath::Core::Vector3<float>(1.f, -1.f, 0.f),
				PonyMath::Core::Vector3<float>(0.f, 1.f, 0.f)
			});
			auto meshParams = PonyEngine::Render::MeshParams();
			meshParams.bufferTables["Meshlets"] = std::vector<PonyBase::Container::Buffer>{ meshlets, vertexIndices, triangles };
			meshParams.bufferTables["Positions"] = std::vector<PonyBase::Container::Buffer>{ positions };
			meshParams.threadGroupCounts = { 1u, 1u, 1u };
			auto triangle = std::make_shared<PonyEngine::Render::Mesh>(meshParams);

			auto logger = Mocks::Logger();
			auto screenSystem = Mocks::ScreenSystem();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Screen::IScreenSystem), static_cast<PonyEngine::Screen::IScreenSystem*>(&screenSystem));
			const auto classParams = PonyEngine::Window::Windows::ClassParams{.name = L"Pony Engine Test"};
			auto windowsClass = PonyEngine::Window::Windows::CreateClass(application, classParams);
			auto windowFactory = PonyEngine::Window::Windows::CreateWindowFactory(application, PonyEngine::Window::Windows::WindowSystemFactoryParams{}, PonyEngine::Window::Windows::WindowSystemParams{.windowsClass = std::move(windowsClass.windowsClass)});
			auto window = windowFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams());
			static_cast<Mocks::SystemManager*>(&engine.SystemManager())->types.emplace(typeid(PonyEngine::Window::Windows::IWindowSystem), dynamic_cast<PonyEngine::Window::Windows::IWindowSystem*>(std::get<1>(window.system).get()));
			auto renderFactory = PonyEngine::Render::Direct3D12::Windows::CreateRenderSystemFactory(application, PonyEngine::Render::Direct3D12::Windows::RenderSystemFactoryParams{}, PonyEngine::Render::Direct3D12::Windows::RenderSystemParams{});
			auto renderSystem = renderFactory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			const auto renderObjectParams = PonyEngine::Render::RenderObjectParams{.mesh = triangle};
			auto renderObject = dynamic_cast<PonyEngine::Render::IRenderSystem*>(std::get<1>(renderSystem.system).get())->RenderObjectManager().CreateObject(renderObjectParams);

			PonyMath::Core::Matrix4x4<float> expectedMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(2.f, 4.f, 7.f), PonyMath::Core::Vector3<float>(1.1f, 0.7f, -0.3f), PonyMath::Core::Vector3<float>(2.f, 1.1f, 0.7f));
			renderObject->ModelMatrix(expectedMatrix);
			Assert::IsTrue(expectedMatrix == renderObject->ModelMatrix());
		}
	};
}
