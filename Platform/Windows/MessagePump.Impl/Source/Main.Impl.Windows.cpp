/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/MessagePump/Windows/PumpServiceModule.h"

import PonyEngine.MessagePump.Impl.Windows;

namespace PonyEngine::MessagePump::Windows
{
	Application::IModule* GetPumpServiceModule()
	{
		static PumpServiceModule pumpModule;
		return &pumpModule;
	}
}
