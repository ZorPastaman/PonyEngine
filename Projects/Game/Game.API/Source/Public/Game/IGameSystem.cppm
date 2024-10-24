/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:IGameSystem;

import PonyEngine.Core;

export namespace Game
{
	/// @brief Game system.
	class IGameSystem : public PonyEngine::Core::ISystem
	{
	public:
		IGameSystem(const IGameSystem&) = delete;
		IGameSystem(IGameSystem&&) = delete;

		IGameSystem& operator =(const IGameSystem&) = delete;
		IGameSystem& operator =(IGameSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IGameSystem() noexcept = default;

		~IGameSystem() noexcept = default;
	};
}
