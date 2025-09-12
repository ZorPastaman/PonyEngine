#include "Game/GameModule.h"

import Game;

namespace Game
{
	// The module lifetime must be the same as the library lifetime. So, it's much easier to define it as a global variable.
	GameModule GameModule;

	PonyEngine::Application::IModule* GetGameModule()
	{
		return &GameModule;
	}
}
