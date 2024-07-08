/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:ISystemFactoriesProvider;

import PonyEngine.Core.Factories;

export namespace Launcher
{
	/// @brief System factories provider.
	class ISystemFactoriesProvider
	{
	public:
		/// @brief Add system factories to the @p engineParams.
		/// @param engineParams Engine params.
		virtual void AddSystemFactories(PonyEngine::Core::EngineParams& engineParams) const = 0;

	protected:
		~ISystemFactoriesProvider() noexcept = default;
	};
}
