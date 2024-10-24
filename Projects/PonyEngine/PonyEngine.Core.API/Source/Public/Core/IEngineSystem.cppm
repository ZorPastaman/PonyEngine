/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IEngineSystem;

import :ISystem;

export namespace PonyEngine::Core
{
	/// @brief Engine system.
	class IEngineSystem : public ISystem
	{
	public:
		IEngineSystem(const IEngineSystem&) = delete;
		IEngineSystem(IEngineSystem&&) = delete;

		/// @brief Begins the system.
		/// @details The system takes its dependencies in this function.
		virtual void Begin() = 0;
		/// @brief Ends the system.
		/// @details The function is called before a destruction.
		virtual void End() = 0;

		IEngineSystem& operator =(const IEngineSystem&) = delete;
		IEngineSystem& operator =(IEngineSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngineSystem() noexcept = default;

		~IEngineSystem() noexcept = default;
	};
}
