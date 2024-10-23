/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game.Factory:IGameSystemFactory;

import PonyEngine.Core.Factory;

import :GameSystemParams;

export namespace Game
{
	/// @brief Game system factory.
	class IGameSystemFactory : public PonyEngine::Core::ISystemFactory
	{
	public:
		IGameSystemFactory(const IGameSystemFactory&) = delete;
		IGameSystemFactory(IGameSystemFactory&&) = delete;

		/// @brief Gets a game system parameters.
		/// @return Game system parameters.
		[[nodiscard("Pure function")]]
		virtual GameSystemParams& SystemParams() noexcept = 0;
		/// @brief Gets a game system parameters.
		/// @return Game system parameters.
		[[nodiscard("Pure function")]]
		virtual const GameSystemParams& SystemParams() const noexcept = 0;

		IGameSystemFactory& operator =(const IGameSystemFactory&) = delete;
		IGameSystemFactory& operator =(IGameSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IGameSystemFactory() noexcept = default;

		~IGameSystemFactory() noexcept = default;
	};
}
