/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factories:IInputSystemFactory;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class IInputSystemFactory : public Core::ISystemFactory
	{
	public:
		/// @brief Creates an input system.
		/// @param engine Engine that owns the system.
		/// @return Created system.
		[[nodiscard("Pure function")]]
		virtual IInputSystem* Create(Core::IEngine& engine) override = 0;

	protected:
		~IInputSystemFactory() noexcept = default;
	};
}
