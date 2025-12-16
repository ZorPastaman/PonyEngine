/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/MessagePump/PumpServiceModule.h"

PONY_MODULE(PonyEngine::MessagePump::GetPumpServiceModule, PonyEngineMessagePumpService, PONY_ENGINE_MESSAGE_PUMP_ORDER);
