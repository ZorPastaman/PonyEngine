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

export module Game.Implementation;

import PonyEngine.Core;

import Game;

import :Game;

namespace Game
{
	/// @brief Creates a game.
	/// @param engine Engine that owns the game.
	/// @return Created game.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) IGame* CreateGame(PonyEngine::Core::IEngine& engine);
	/// @brief Destroys a previously created game.
	/// @param game Game to destroy.
	export __declspec(dllexport) void DestroyGame(IGame* game) noexcept;

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
