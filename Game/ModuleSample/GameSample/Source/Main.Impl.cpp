#include "Game/GameModule.h"

import Game;

namespace Game
{
	PonyEngine::Application::IModule* GetGameModule()
	{
		// The module lifetime must be the same as the library lifetime. So, it's much easier to define it as a global variable.
		static GameModule gameModule;
		return &gameModule;
	}
}
