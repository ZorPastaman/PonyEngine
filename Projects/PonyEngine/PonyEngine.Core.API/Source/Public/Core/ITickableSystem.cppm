/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ITickableSystem;

export namespace PonyEngine::Core
{
	/// @brief Tickable system.
	class ITickableSystem
	{
	public:
		ITickableSystem(const ITickableSystem&) = delete;
		ITickableSystem(ITickableSystem&&) = delete;

		/// @brief Ticks the system.
		virtual void Tick() = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		ITickableSystem& operator =(const ITickableSystem&) = delete;
		ITickableSystem& operator =(ITickableSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITickableSystem() noexcept = default;

		~ITickableSystem() noexcept = default;
	};
}
