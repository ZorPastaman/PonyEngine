/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:ISystemFactory;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	/// @brief System factory.
	export class ISystemFactory
	{
	public:
		/// @brief Creates a system.
		/// @param engine Engine that owns the system.
		/// @return Created system.
		[[nodiscard("Pure function")]]
		virtual ISystem* Create(IEngine& engine) = 0;
		/// @brief Destroys a previously created system.
		/// @param system System to destroy.
		virtual void Destroy(ISystem* system) noexcept = 0;

	protected:
		inline virtual ~ISystemFactory() noexcept = default;
	};
}
