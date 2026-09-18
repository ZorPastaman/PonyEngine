/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/RawInput/XInput/XInputProviderModule.h"

PONY_ENGINE_MODULE(PonyEngine::RawInput::XInput::CreateXInputProviderModule, PonyEngineRawInputXInputProvider, PONY_ENGINE_RAW_INPUT_XINPUT_ORDER);
