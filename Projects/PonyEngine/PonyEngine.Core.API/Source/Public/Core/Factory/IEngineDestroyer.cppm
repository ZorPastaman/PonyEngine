/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:IEngineDestroyer;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief Engine destroyer.
	class IEngineDestroyer
	{
	public:
		IEngineDestroyer(const IEngineDestroyer&) = delete;
		IEngineDestroyer(IEngineDestroyer&&) = delete;

		/// @brief Destroys the @p engine.
		/// @param engine Engine to destroy.
		virtual void Destroy(IEngine* engine) noexcept = 0;

		IEngineDestroyer& operator =(const IEngineDestroyer&) = delete;
		IEngineDestroyer& operator =(IEngineDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngineDestroyer() noexcept = default;

		~IEngineDestroyer() noexcept = default;
	};
}
