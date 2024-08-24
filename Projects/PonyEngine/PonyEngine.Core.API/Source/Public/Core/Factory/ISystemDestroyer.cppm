/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:ISystemDestroyer;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief System destroyer.
	class ISystemDestroyer
	{
	public:
		ISystemDestroyer(const ISystemDestroyer&) = delete;
		ISystemDestroyer(ISystemDestroyer&&) = delete;

		/// @brief Destroys the @p system.
		/// @param system System to destroy.
		virtual void Destroy(ISystem* system) noexcept = 0;

		ISystemDestroyer& operator =(const ISystemDestroyer&) = delete;
		ISystemDestroyer& operator =(ISystemDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemDestroyer() noexcept = default;

		~ISystemDestroyer() noexcept = default;
	};
}
