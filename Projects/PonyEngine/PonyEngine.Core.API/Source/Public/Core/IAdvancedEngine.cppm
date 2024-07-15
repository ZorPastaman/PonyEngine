/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IAdvancedEngine;

import :IEngine;

export namespace PonyEngine::Core
{
	/// @brief Advanced engine. These functions must be used with caution.
	class IAdvancedEngine : public IEngine
	{
	public:
		IAdvancedEngine(const IAdvancedEngine&) = delete;
		IAdvancedEngine(IAdvancedEngine&&) = delete;

		/// @brief Ticks the engine.
		virtual void Tick() = 0;

		IAdvancedEngine& operator =(const IAdvancedEngine&) = delete;
		IAdvancedEngine& operator =(IAdvancedEngine&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IAdvancedEngine() noexcept = default;

		~IAdvancedEngine() noexcept = default;
	};
}
