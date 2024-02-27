/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IService;

import PonyEngine.Utility;

namespace PonyEngine::Core
{
	/// @brief Engine service.
	export class IService : public Utility::INamed
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

	protected:
		inline virtual ~IService() noexcept = default;
	};
}
