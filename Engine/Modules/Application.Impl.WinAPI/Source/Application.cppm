/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl.Windows;

export import PonyEngine.Application.WinAPI;
export import PonyEngine.Application.Impl;

export import :CommandLine;

#ifdef PONY_ENGINE_APPLICATION_MODE_CONSOLE
export import :ConsoleProcess;
#endif

#ifdef PONY_ENGINE_APPLICATION_MODE_GUI
export import :GUIProcess;
#endif
