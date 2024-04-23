/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "Core/Linking.h"

export module Game.Implementation;

import PonyEngine.Core;

import Game;

import :Game;

export namespace Game
{
	/// @brief Creates a game.
	/// @param engine Engine that owns the game.
	/// @return Created game.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT IGame* CreateGame(PonyEngine::Core::IEngine& engine);
	/// @brief Destroys a previously created game.
	/// @param game Game to destroy.
	PONY_DLL_EXPORT void DestroyGame(IGame* game) noexcept;
}

namespace Game
{
	IGame* CreateGame(PonyEngine::Core::IEngine& engine)
	{
		return new Game(engine);
	}

	void DestroyGame(IGame* const game) noexcept
	{
		assert((dynamic_cast<Game*>(game) != nullptr));
		delete static_cast<Game*>(game);
	}
}
