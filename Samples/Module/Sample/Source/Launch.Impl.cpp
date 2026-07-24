#include "Game/GameModule.h"

import Game;

namespace Game
{
	std::shared_ptr<PonyEngine::Application::IModule> GetGameModule()
	{
		return std::make_shared<GameModule>();
	}
}
