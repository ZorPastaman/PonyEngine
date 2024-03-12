/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factories.Implementation:InputSystemFactory;

import PonyEngine.Core;
import PonyEngine.Input.Factories;
import PonyEngine.Input.Implementation;

namespace PonyEngine::Input
{
	export class InputSystemFactory final : public IInputSystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual IInputSystem* Create(Core::IEngine& engine) override;
		virtual void Destroy(Core::ISystem* system) override;
	};

	IInputSystem* InputSystemFactory::Create(Core::IEngine& engine)
	{
		return new InputSystem(engine);
	}

	void InputSystemFactory::Destroy(Core::ISystem* system)
	{
		delete static_cast<InputSystem*>(system);
	}
}
