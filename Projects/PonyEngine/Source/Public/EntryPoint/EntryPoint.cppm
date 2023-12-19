/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EntryPoint;

import "PonyAPIMacro.h";

import PonyEngine.IEngine;
import PonyEngine.EngineParams;

namespace PonyEngine
{
	/// <summary>
	/// Creates a new Engine instance with default parameters
	/// and returns it as <see cref="IEngine"/>.
	/// </summary>
	/// <returns>New Engine.</returns>
	export extern "C" PONY_API IEngine* CreateEngine();

	/// <summary>
	/// Creates a new Engine instance with <paramref name="params"/>
	/// and returns it as <see cref="IEngine"/>.
	/// </summary>
	/// <param name="params">Engine parameters.</param>
	/// <returns>New Engine.</returns>
	export extern "C" PONY_API IEngine* CreateEngineWithParams(const EngineParams& params);
}
