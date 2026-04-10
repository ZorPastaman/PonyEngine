/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/MessagePump/Windows/MessagePumpServiceModule.h"

import PonyEngine.MessagePump.Impl.Windows;

namespace PonyEngine::MessagePump::Windows
{
	Application::IModule* GetMessagePumpServiceModule()
	{
		static MessagePumpServiceModule pumpModule;
		return &pumpModule;
	}
}
