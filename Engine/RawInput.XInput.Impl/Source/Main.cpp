/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Input/ControllerProviderModule.h"

PONY_MODULE(PonyEngine::Input::GetControllerProviderModule, PonyEngineRawInputControllerProvider, PONY_ENGINE_RAW_INPUT_CONTROLLER_ORDER);
