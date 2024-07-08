/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:IGameSystem;

export namespace Game
{
	/// @brief Game system.
	class IGameSystem
	{
	protected:
		~IGameSystem() noexcept = default;
	};
}
