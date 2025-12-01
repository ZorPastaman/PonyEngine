/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Input/KeyboardProviderModule.h"

PONY_MODULE(PonyEngine::Input::GetKeyboardProviderModule, PonyEngineKeyboardProvider, PONY_ENGINE_INPUT_KEYBOARD_ORDER);
