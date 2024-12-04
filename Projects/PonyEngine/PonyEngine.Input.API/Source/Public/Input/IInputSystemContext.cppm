/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Input:IInputSystemContext;

import PonyEngine.Core;

export namespace PonyEngine::Input
{
	class IInputSystemContext
	{
		INTERFACE_BODY(IInputSystemContext)

		[[nodiscard("Pure function")]]
		virtual Core::ISystemManager& SystemManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const Core::ISystemManager& SystemManager() const noexcept = 0;
	};
}
