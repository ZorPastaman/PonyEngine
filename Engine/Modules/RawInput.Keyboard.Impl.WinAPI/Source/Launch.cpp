/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/RawInput/Keyboard/WinAPI/KeyboardProviderModule.h"

PONY_ENGINE_MODULE(PonyEngine::RawInput::Keyboard::CreateKeyboardProviderModule, PonyEngineRawInputKeyboardProvider, PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER);
