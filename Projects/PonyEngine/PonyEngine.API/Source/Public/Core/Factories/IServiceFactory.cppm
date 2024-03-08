/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:IServiceFactory;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	export class IServiceFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual IService* Create(IEngine& engine) = 0;
		virtual void Destroy(IService* service) = 0;

	protected:
		inline virtual ~IServiceFactory() noexcept = default;
	};
}
