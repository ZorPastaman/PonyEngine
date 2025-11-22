/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/MessagePump/PumpServiceModule.h"

import PonyEngine.MessagePump.Impl;

namespace PonyEngine::MessagePump
{
	Application::IModule* GetPumpServiceModule()
	{
#if PONY_WINDOWS
		static Windows::PumpServiceModule pumpModule;
#else
#error "Unsupported platform!"
#endif
		return &pumpModule;
	}
}
