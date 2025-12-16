/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.XInput.Impl;

export import PonyEngine.RawInput.Ext;

#if PONY_WINDOWS
export import :Windows.GamepadProviderModule;
#endif
