/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:GameSystemFactory;

import PonyEngine.Core;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory : public PonyEngine::Core::ISystemFactory
	{
	public:
		GameSystemFactory(const GameSystemFactory&) = delete;
		GameSystemFactory(GameSystemFactory&&) = delete;

		virtual ~GameSystemFactory() noexcept = default;

		GameSystemFactory& operator =(const GameSystemFactory&) = delete;
		GameSystemFactory& operator =(GameSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		GameSystemFactory() noexcept = default;
	};
}
