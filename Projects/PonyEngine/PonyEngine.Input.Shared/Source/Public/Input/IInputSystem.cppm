/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:IInputSystem;

import PonyEngine.Core;

namespace PonyEngine::Input
{
	export class IInputSystem : public Core::ISystem
	{
	protected:
		virtual ~IInputSystem() noexcept = default;
	};
}
