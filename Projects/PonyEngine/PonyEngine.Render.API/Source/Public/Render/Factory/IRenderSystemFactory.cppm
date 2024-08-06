/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Factory:IRenderSystemFactory;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Render
{
	/// @brief Render system factory.
	class IRenderSystemFactory : public Core::ISystemFactory
	{
	public:
		IRenderSystemFactory(const IRenderSystemFactory&) = delete;
		IRenderSystemFactory(IRenderSystemFactory&&) = delete;

		IRenderSystemFactory& operator =(const IRenderSystemFactory&) = delete;
		IRenderSystemFactory& operator =(IRenderSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystemFactory() noexcept = default;

		~IRenderSystemFactory() noexcept = default;
	};
}
