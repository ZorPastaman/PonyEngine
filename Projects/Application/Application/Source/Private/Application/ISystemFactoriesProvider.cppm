/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Application:ISystemFactoriesProvider;

import PonyEngine.Core.Factory;

export namespace Application
{
	/// @brief System factories provider.
	class ISystemFactoriesProvider
	{
	public:
		ISystemFactoriesProvider(const ISystemFactoriesProvider&) = delete;
		ISystemFactoriesProvider(ISystemFactoriesProvider&&) = delete;

		/// @brief Adds system factories to the @p systemFactoriesParams.
		/// @param systemFactories System factories.
		virtual void AddSystemFactories(PonyEngine::Core::SystemFactoriesContainer& systemFactories) const = 0;

		ISystemFactoriesProvider& operator =(const ISystemFactoriesProvider&) = delete;
		ISystemFactoriesProvider& operator =(ISystemFactoriesProvider&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemFactoriesProvider() noexcept = default;

		~ISystemFactoriesProvider() noexcept = default;
	};
}
