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

export module PonyEngine.Input.Factories.Implementation:InputSystemFactory;

import PonyEngine.Core;
import PonyEngine.Input.Factories;
import PonyEngine.Input.Implementation;

namespace PonyEngine::Input
{
	export class InputSystemFactory final : public IInputSystemFactory
	{
	public:
		inline InputSystemFactory() noexcept = default;
		InputSystemFactory(const InputSystemFactory&) = delete;
		InputSystemFactory(InputSystemFactory&&) = delete;

		inline virtual ~InputSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual IInputSystem* Create(Core::IEngine& engine) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;
	};

	IInputSystem* InputSystemFactory::Create(Core::IEngine& engine)
	{
		return new InputSystem(engine);
	}

	void InputSystemFactory::Destroy(Core::ISystem* system) noexcept
	{
		assert((dynamic_cast<InputSystem*>(system) != nullptr));
		delete static_cast<InputSystem*>(system);
	}
}
