/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#ifdef DLL_OUT
	#define PONY_API __declspec(dllexport)
#else
	#define PONY_API __declspec(dllimport)
#endif // DLL_OUT
