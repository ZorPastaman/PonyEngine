#include "PonyEngine/Application/Module.h"
#include "Game/GameModule.h"

// Registers the game module.
// It's actual implementation is in Main.Game.Impl.cpp. It allows to define the game module in a private C++20 module file.
PONY_MODULE(Game::GetGameModule, Game, tg)
