/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ITickableEngineSystem;

import :IEngineSystem;

export namespace PonyEngine::Core
{
	/// @brief Tickable system.
	class ITickableEngineSystem : public IEngineSystem
	{
	public:
		ITickableEngineSystem(const ITickableEngineSystem&) = delete;
		ITickableEngineSystem(ITickableEngineSystem&&) = delete;

		/// @brief Ticks the system.
		virtual void Tick() = 0;

		ITickableEngineSystem& operator =(const ITickableEngineSystem&) = delete;
		ITickableEngineSystem& operator =(ITickableEngineSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITickableEngineSystem() noexcept = default;

		~ITickableEngineSystem() noexcept = default;
	};
}
