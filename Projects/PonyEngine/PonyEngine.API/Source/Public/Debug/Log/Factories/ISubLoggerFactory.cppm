/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Factories:ISubLoggerFactory;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	export class ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) = 0;
		virtual void Destroy(ISubLogger* sublogger) = 0;

	protected:
		inline virtual ~ISubLoggerFactory() noexcept = default;
	};
}
