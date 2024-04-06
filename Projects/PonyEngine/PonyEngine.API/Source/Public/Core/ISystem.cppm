/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

import PonyEngine.Utility;

namespace PonyEngine::Core
{
	/// @brief Engine system.
	export class ISystem : public Utility::INamed
	{
	public:
		/// @brief Begins a system.
		/// @details The system takes its dependencies in this function.
		virtual void Begin() = 0;
		/// @brief Ends a system.
		/// @details The function is called before a destruction.
		virtual void End() = 0;

		/// @brief Is the system tickable. The engine will call @p Tick() only if it returns @a true.
		/// @return @a True if the system is tickable; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept = 0;
		/// @brief Ticks the system.
		virtual void Tick() = 0;

	protected:
		inline virtual ~ISystem() noexcept = default;
	};
}
