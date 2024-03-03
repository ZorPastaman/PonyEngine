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
		/// @brief Begins a service.
		/// @details The service takes its dependencies in this function.
		virtual void Begin() = 0;
		/// @brief Ends a service.
		/// @details The function is called before a destruction.
		virtual void End() = 0;

	protected:
		inline virtual ~IService() noexcept = default;
	};
}
