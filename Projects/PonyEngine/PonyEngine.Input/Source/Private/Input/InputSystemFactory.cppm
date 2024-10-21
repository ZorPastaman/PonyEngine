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

import <utility>;

import PonyEngine.Core.Factory;
import PonyEngine.Input.Factory;

import :InputSystem;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactory final : public IInputSystemFactory, public Core::ISystemDestroyer
	{
	public:
		InputSystemFactory() noexcept = default;
		InputSystemFactory(const InputSystemFactory&) = delete;
		InputSystemFactory(InputSystemFactory&&) = delete;

		~InputSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngine& engine, const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual InputSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const InputSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Input::InputSystemFactory"; ///< Class name.

	private:
		InputSystemParams inputSystemParams; ///< Input system parameters.
	};
}

namespace PonyEngine::Input
{
	Core::SystemData InputSystemFactory::Create(Core::IEngine& engine, const Core::SystemParams&)
	{
		const auto system = new InputSystem(engine);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IInputSystem>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr(system, Core::SystemDeleter(*this)),
			.tickableSystem = system,
			.publicInterfaces = std::move(interfaces)
		};
	}

	void InputSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<InputSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<InputSystem*>(system);
	}

	InputSystemParams& InputSystemFactory::SystemParams() noexcept
	{
		return inputSystemParams;
	}

	const InputSystemParams& InputSystemFactory::SystemParams() const noexcept
	{
		return inputSystemParams;
	}

	const char* InputSystemFactory::SystemName() const noexcept
	{
		return InputSystem::StaticName;
	}

	const char* InputSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
