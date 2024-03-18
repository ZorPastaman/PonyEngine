/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:IPlatformEngineParamsProvider;

import PonyEngine.Core.Factories;

namespace Launcher
{
	/// @brief Platform engine params provider.
	export class IPlatformEngineParamsProvider
	{
	public:
		/// @brief Modify engine params.
		/// @param engineParams Engine params to modify.
		virtual void Modify(PonyEngine::Core::EngineParams& engineParams) const = 0;

	protected:
		inline virtual ~IPlatformEngineParamsProvider() noexcept = default;
	};
}
