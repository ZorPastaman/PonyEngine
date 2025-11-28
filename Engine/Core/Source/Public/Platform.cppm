/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Platform;

#if PONY_WINDOWS
export import :Windows.Cursor;
export import :Windows.Device;
export import :Windows.File;
export import :Windows.GUID;
export import :Windows.Text;
#endif
