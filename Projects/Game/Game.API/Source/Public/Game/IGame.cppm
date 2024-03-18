/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:IGame;

namespace Game
{
	/// @brief Game interface.
	export class IGame
	{
	public:
		/// @brief Called before a first tick.
		virtual void Begin() = 0;
		/// @brief Called before every tick.
		virtual void PreTick() = 0;
		/// @brief Called after every tick.
		virtual void PostTick() = 0;
		/// @brief Called after a last tick.
		virtual void End() = 0;

	protected:
		inline virtual ~IGame() noexcept = default;
	};
}
