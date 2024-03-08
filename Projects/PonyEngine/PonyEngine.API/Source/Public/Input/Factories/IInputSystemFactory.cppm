/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factories:IInputSystemFactory;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Input;

namespace PonyEngine::Input
{
	export class IInputSystemFactory : public Core::ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual IInputSystem* Create(Core::IEngine& engine) = 0;

	protected:
		inline virtual ~IInputSystemFactory() noexcept = default;
	};
}
