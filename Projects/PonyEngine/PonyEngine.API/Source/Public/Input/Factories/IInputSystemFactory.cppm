/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factories:IInputSystemFactory;

import PonyEngine.Core.Factories;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class IInputSystemFactory : public Core::ISystemFactory
	{
	protected:
		~IInputSystemFactory() noexcept = default;
	};
}
