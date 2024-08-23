/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ITickableEngine;

export namespace PonyEngine::Core
{
	/// @brief Tickable engine.
	class ITickableEngine
	{
	public:
		ITickableEngine(const ITickableEngine&) = delete;
		ITickableEngine(ITickableEngine&&) = delete;

		/// @brief Ticks the engine.
		virtual void Tick() = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		ITickableEngine& operator =(const ITickableEngine&) = delete;
		ITickableEngine& operator =(ITickableEngine&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITickableEngine() noexcept = default;

		~ITickableEngine() noexcept = default;
	};
}
