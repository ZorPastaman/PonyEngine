/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Input.Implementation:InputSystemFactory;

import <string_view>;
import <utility>;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Factory;

import :InputSystem;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactory final : public IInputSystemFactory
	{
	public:
		InputSystemFactory() noexcept = default;
		InputSystemFactory(const InputSystemFactory&) = delete;
		InputSystemFactory(InputSystemFactory&&) = delete;

		~InputSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual InputSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const InputSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Input::InputSystemFactory"; ///< Class name.

	private:
		InputSystemParams inputSystemParams; ///< Input system parameters.
	};
}

namespace PonyEngine::Input
{
	Core::SystemData InputSystemFactory::Create(Core::IEngineContext& engine, const Core::EngineSystemParams&)
	{
		auto system = PonyBase::Memory::UniquePointer<InputSystem>::Create(engine);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IInputSystem>(*system);

		return Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<Core::ITickableEngineSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	InputSystemParams& InputSystemFactory::SystemParams() noexcept
	{
		return inputSystemParams;
	}

	const InputSystemParams& InputSystemFactory::SystemParams() const noexcept
	{
		return inputSystemParams;
	}

	std::string_view InputSystemFactory::SystemName() const noexcept
	{
		return InputSystem::StaticName;
	}

	std::string_view InputSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
