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

		/// @brief Checks if the destroyer is compatible with the @p system.
		/// @param system Target system.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(IEngineSystem* system) const noexcept = 0;

		/// @brief Destroys the @p system.
		/// @param system System to destroy.
		virtual void Destroy(IEngineSystem* system) noexcept = 0;

		ISystemDestroyer& operator =(const ISystemDestroyer&) = delete;
		ISystemDestroyer& operator =(ISystemDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemDestroyer() noexcept = default;

		~ISystemDestroyer() noexcept = default;
	};
}
