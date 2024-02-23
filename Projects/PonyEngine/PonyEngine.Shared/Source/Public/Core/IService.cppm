/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IService;

import :INamed;

namespace PonyEngine::Core
{
	/// @brief Engine service.
	export class IService : public INamed
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

	protected:
		inline virtual ~IService() noexcept = default;
	};
}
