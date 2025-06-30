#include "PonyEngine/Core/Module.h"
#include "Game/GameModule.h"

// Registers the game module.
// It's actual implementation is in Main.Game.Impl.cpp. It allows to define the game module in a private c++20 module file.
PONY_MODULE_ENGINE(Game::GetGameModule, Game)
