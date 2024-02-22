/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IService;

namespace PonyEngine::Core
{
	/// @brief Engine service.
	export class IService
	{
	protected:
		inline virtual ~IService() noexcept = default;
	};
}
