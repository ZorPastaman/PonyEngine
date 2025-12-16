/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl;

export import PonyEngine.Application.Ext;

export import :Console;
export import :DefaultLogger;
export import :ExitCodes;

#if PONY_WINDOWS
export import :Windows.App;
export import :Windows.Console;
export import :Windows.DefaultLogger;
export import :Windows.Process;
#endif
