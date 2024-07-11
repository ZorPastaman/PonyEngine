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
	/// @brief Time manager.
	class ITimeManager
	{
	public:
		ITimeManager(const ITimeManager&) = delete;
		ITimeManager(ITimeManager&&) = delete;

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

		ITimeManager& operator =(const ITimeManager&) = delete;
		ITimeManager& operator =(ITimeManager&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITimeManager() noexcept = default;

		~ITimeManager() noexcept = default;
	};
}
