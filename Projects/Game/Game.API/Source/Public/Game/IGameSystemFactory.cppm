/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:IGameSystemFactory;

import PonyEngine.Core;

export namespace Game
{
	/// @brief Game system factory.
	class IGameSystemFactory : public PonyEngine::Core::ISystemFactory
	{
	public:
		IGameSystemFactory(const IGameSystemFactory&) = delete;
		IGameSystemFactory(IGameSystemFactory&&) = delete;

		IGameSystemFactory& operator =(const IGameSystemFactory&) = delete;
		IGameSystemFactory& operator =(IGameSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IGameSystemFactory() noexcept = default;

		~IGameSystemFactory() noexcept = default;
	};
}
