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

		[[nodiscard("Pure function")]]
		virtual InputSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const InputSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(Core::IEngineSystem* system) const noexcept override;
		virtual void Destroy(Core::IEngineSystem* system) noexcept override;

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
			.system = Core::SystemUniquePtr<Core::IEngineSystem>(*system, *this),
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

	bool InputSystemFactory::IsCompatible(Core::IEngineSystem* const system) const noexcept
	{
		return dynamic_cast<InputSystem*>(system);
	}

	void InputSystemFactory::Destroy(Core::IEngineSystem* const system) noexcept
	{
		assert((dynamic_cast<InputSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<InputSystem*>(system);
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
