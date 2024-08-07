/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System.
	class ISystem
	{
	public:
		ISystem(const ISystem&) = delete;
		ISystem(ISystem&&) = delete;

		/// @brief Gets public system interfaces.
		/// @return Public system interfaces.
		[[nodiscard("Pure function")]]
		virtual ObjectInterfaces PublicInterfaces() noexcept = 0;
		/// @brief Gets if the system is tickable.
		/// @return @a True if it's tickable; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept = 0;

		/// @brief Begins the system.
		/// @details The system takes its dependencies in this function.
		virtual void Begin() = 0;
		/// @brief Ends the system.
		/// @details The function is called before a destruction.
		virtual void End() = 0;

		/// @brief Ticks the system.
		virtual void Tick() = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		ISystem& operator =(const ISystem&) = delete;
		ISystem& operator =(ISystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystem() noexcept = default;

		~ISystem() noexcept = default;
	};
}
