/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:ISystemFactoriesProvider;

import PonyEngine.Core.Factory;

export namespace Launcher
{
	/// @brief System factories provider.
	class ISystemFactoriesProvider
	{
	public:
		ISystemFactoriesProvider(const ISystemFactoriesProvider&) = delete;
		ISystemFactoriesProvider(ISystemFactoriesProvider&&) = delete;

		/// @brief Adds system factories to the @p engineParams.
		/// @param engineParams Engine params.
		virtual void AddSystemFactories(PonyEngine::Core::EngineParams& engineParams) const = 0;

		ISystemFactoriesProvider& operator =(const ISystemFactoriesProvider&) = delete;
		ISystemFactoriesProvider& operator =(ISystemFactoriesProvider&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemFactoriesProvider() noexcept = default;

		~ISystemFactoriesProvider() noexcept = default;
	};
}
