/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Application:IEngineSetupAgent;

import PonyEngine.Core;

export namespace Application
{
	/// @brief Engine set-up agent.
	class IEngineSetupAgent
	{
	public:
		IEngineSetupAgent(const IEngineSetupAgent&) = delete;
		IEngineSetupAgent(IEngineSetupAgent&&) = delete;

		/// @brief Sets up the @p engine.
		/// @param engine Engine to set up.
		virtual void Setup(PonyEngine::Core::IEngine& engine) const = 0;

		IEngineSetupAgent& operator =(const IEngineSetupAgent&) = delete;
		IEngineSetupAgent& operator =(IEngineSetupAgent&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngineSetupAgent() noexcept = default;

		~IEngineSetupAgent() noexcept = default;
	};
}
