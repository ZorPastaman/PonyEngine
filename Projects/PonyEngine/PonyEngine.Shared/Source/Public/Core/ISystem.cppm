/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

import PonyEngine.Utility;

namespace PonyEngine::Core
{
	/// @brief Engine system.
	export class ISystem : public Utility::INamed
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		/// @brief Ticks the system.
		virtual void Tick() = 0;

	protected:
		inline virtual ~ISystem() noexcept = default;
	};
}
