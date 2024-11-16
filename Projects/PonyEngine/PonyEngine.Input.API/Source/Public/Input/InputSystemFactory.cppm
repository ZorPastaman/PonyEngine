/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactory : public Core::ISystemFactory
	{
	public:
		InputSystemFactory(const InputSystemFactory&) = delete;
		InputSystemFactory(InputSystemFactory&&) = delete;

		virtual ~InputSystemFactory() noexcept = default;

		InputSystemFactory& operator =(const InputSystemFactory&) = delete;
		InputSystemFactory& operator =(InputSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		InputSystemFactory() noexcept = default;
	};
}
