/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;

import PonyEngine.Core;
import PonyEngine.Core.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(SystemInfoTests)
	{
		class IInterface
		{
		};

		class IAnotherInterface
		{
		};

		class EmptySystem final : public PonyEngine::Core::ISystem, public IInterface, public IAnotherInterface
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Begin() override
			{
			}
			virtual void End() override
			{
			}

			virtual void Tick() override
			{
			}
		};

		class EmptySystemFactory final : public PonyEngine::Core::ISystemFactory, public PonyEngine::Core::ISystemDestroyer
		{
		public:
			PonyEngine::Core::ISystem* createdSystem = nullptr;
			bool deleted = false;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::SystemInfo Create(PonyEngine::Core::IEngine&) override
			{
				const auto emptySystem = new EmptySystem();
				createdSystem = emptySystem;

				return PonyEngine::Core::SystemInfo::Create<EmptySystem>(*emptySystem, *this, true);
			}
			virtual void Destroy(PonyEngine::Core::ISystem* const system) noexcept override
			{
				Assert::IsNotNull(dynamic_cast<EmptySystem*>(system));
				delete static_cast<EmptySystem*>(system);
				deleted = true;
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetSystemName() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(ContructorTest)
		{
			auto system = new EmptySystem();
			auto factory = EmptySystemFactory();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddObjectInterface<IInterface>(*system);
			auto interface = *interfaces.GetObjectInterfaces();

			auto systemInfo = PonyEngine::Core::SystemInfo(*system, factory, interfaces, true);
			auto systemInterface = *systemInfo.GetInterfaces();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(systemInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&systemInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			Assert::IsTrue(interface.first.get() == systemInterface.first.get());
			Assert::IsTrue(systemInfo.GetIsTickable());

			auto movedInfo = std::move(systemInfo);
			systemInterface = *movedInfo.GetInterfaces();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(movedInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&movedInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			Assert::IsTrue(interface.first.get() == systemInterface.first.get());
			Assert::IsTrue(movedInfo.GetIsTickable());
		}

		TEST_METHOD(CreateTest)
		{
			auto system = new EmptySystem();
			auto factory = EmptySystemFactory();
			auto systemInfo = PonyEngine::Core::SystemInfo::Create<EmptySystem, IInterface, IAnotherInterface>(*system, factory, false);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(systemInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&systemInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			auto interfaces = systemInfo.GetInterfaces();
			auto interface = *interfaces;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++interfaces;
			interface = *interfaces;
			Assert::IsTrue(typeid(IAnotherInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IAnotherInterface*>(system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++interfaces;
			Assert::IsTrue(interfaces.IsEnd());
			Assert::IsFalse(systemInfo.GetIsTickable());

			system = new EmptySystem();
			systemInfo = PonyEngine::Core::SystemInfo::CreateDeduced<IInterface, IAnotherInterface>(*system, factory, true);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(systemInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&systemInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			interfaces = systemInfo.GetInterfaces();
			interface = *interfaces;
			Assert::IsTrue(typeid(IInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IInterface*>(system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++interfaces;
			interface = *interfaces;
			Assert::IsTrue(typeid(IAnotherInterface) == interface.first);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<IAnotherInterface*>(system)), reinterpret_cast<std::uintptr_t>(interface.second));
			++interfaces;
			Assert::IsTrue(interfaces.IsEnd());
			Assert::IsTrue(systemInfo.GetIsTickable());
		}

		TEST_METHOD(AssignmentTest)
		{
			auto system = new EmptySystem();
			auto factory = EmptySystemFactory();
			auto interfaces = PonyEngine::Core::ObjectInterfaces();
			interfaces.AddObjectInterface<IInterface>(*system);
			auto interface = *interfaces.GetObjectInterfaces();

			auto systemInfo = PonyEngine::Core::SystemInfo(*system, factory, interfaces, true);
			auto systemInterface = *systemInfo.GetInterfaces();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(systemInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&systemInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			Assert::IsTrue(interface.first.get() == systemInterface.first.get());
			Assert::IsTrue(systemInfo.GetIsTickable());

			auto otherSystem = new EmptySystem();
			auto otherFactory = EmptySystemFactory();
			auto otherInterfaces = PonyEngine::Core::ObjectInterfaces();
			auto movedInfo = PonyEngine::Core::SystemInfo(*otherSystem, otherFactory, otherInterfaces, false);
			movedInfo = std::move(systemInfo);
			systemInterface = *movedInfo.GetInterfaces();
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystem*>(system)), reinterpret_cast<std::uintptr_t>(movedInfo.GetSystem().get()));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Core::ISystemDestroyer*>(&factory)), reinterpret_cast<std::uintptr_t>(&movedInfo.GetSystem().get_deleter().GetSystemDestroyer()));
			Assert::IsTrue(interface.first.get() == systemInterface.first.get());
			Assert::IsTrue(movedInfo.GetIsTickable());
		}
	};
}
