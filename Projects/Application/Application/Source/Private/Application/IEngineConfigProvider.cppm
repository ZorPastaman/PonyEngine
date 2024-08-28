/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Application:IEngineConfigProvider;

import PonyEngine.Core.Factory;

export namespace Application
{
	/// @brief System provider.
	class IEngineConfigProvider
	{
	public:
		IEngineConfigProvider(const IEngineConfigProvider&) = delete;
		IEngineConfigProvider(IEngineConfigProvider&&) = delete;

		/// @brief Adds system factories to the @p systemFactoriesParams.
		/// @param systemFactories System factories.
		virtual void AddSystemFactories(PonyEngine::Core::SystemFactoriesContainer& systemFactories) const = 0;

		/// @brief Sets up the @p systemManager.
		/// @param systemManager Engine system manager to set up.
		virtual void SetupSystems(PonyEngine::Core::ISystemManager& systemManager) const = 0;

		IEngineConfigProvider& operator =(const IEngineConfigProvider&) = delete;
		IEngineConfigProvider& operator =(IEngineConfigProvider&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngineConfigProvider() noexcept = default;

		~IEngineConfigProvider() noexcept = default;
	};
}
