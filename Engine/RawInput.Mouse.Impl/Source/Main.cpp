/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Input/MouseProviderModule.h"

PONY_MODULE(PonyEngine::Input::GetMouseProviderModule, PonyEngineRawInputMouseProvider, PONY_ENGINE_RAW_INPUT_MOUSE_ORDER);
