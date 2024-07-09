/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game.Factory:IGameSystemFactory;

import PonyEngine.Core.Factories;

export namespace Game
{
	/// @brief Game system factory.
	class IGameSystemFactory : public PonyEngine::Core::ISystemFactory
	{
	protected:
		~IGameSystemFactory() noexcept = default;
	};
}
