/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "EntryPoint/PonyAPIMacro.h"

export module PonyEngine.EntryPoint;

import PonyEngine.IEngine;

namespace PonyEngine
{
	/// <summary>
	/// Creates a new Engine instance
	/// and returns it as <see cref="IEngine"/>.
	/// </summary>
	/// <returns>New Engine.</returns>
	export extern "C" PONY_API IEngine* CreateEngine();
}
