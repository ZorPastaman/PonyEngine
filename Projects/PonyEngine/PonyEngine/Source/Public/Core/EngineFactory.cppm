/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:EngineFactory;

import PonyEngine.Core;

import :Engine;

namespace PonyEngine::Core
{
	/// @brief Creates a new @p Engine instance with default parameters.
	/// @return Created @p Engine. It has to be destroyed with the function @p DestroyEngine().
	export [[nodiscard("Pure function")]] __declspec(dllexport) IEngine* CreateEngine();

	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine. It has to be destroyed with the function @p DestroyEngine().
	export [[nodiscard("Pure function")]] __declspec(dllexport) IEngine* CreateEngine(const EngineParams& params);

	/// @brief Destroy the @p engine instance.
	export __declspec(dllexport) void DestroyEngine(IEngine* engine);

	IEngine* CreateEngine()
	{
		EngineParams params;
		return CreateEngine(params);
	}

	IEngine* CreateEngine(const EngineParams& params)
	{
		return new Engine(params);
	}

	void DestroyEngine(IEngine* const engine)
	{
		delete static_cast<Engine*>(engine);
	}
}
