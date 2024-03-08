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
	export class ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual ISystem* Create(IEngine& engine) = 0;
		virtual void Destroy(ISystem* system) = 0;

	protected:
		inline virtual ~ISystemFactory() noexcept = default;
	};
}
