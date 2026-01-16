/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/RawInput/Windows/KeyboardProviderModule.h"

PONY_MODULE(PonyEngine::RawInput::Windows::GetKeyboardProviderModule, PonyEngineRawInputKeyboardProvider, PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER);
