/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ITimeManager;

import <cstddef>;

export namespace PonyEngine::Core
{
	/// @brief Engine time manager.
	class ITimeManager
	{
	public:
		/// @brief Gets current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

	protected:
		~ITimeManager() noexcept = default;
	};
}
