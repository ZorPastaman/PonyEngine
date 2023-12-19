/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Factories.IEngineFeatureFactory;

import PonyEngine.IEngineView;

namespace PonyEngine::Factories
{
	/// <summary>
	/// Interface for factory that creates an engine features.
	/// </summary>
	/// <typeparam name="T">Feature type.</typeparam>
	export template<typename T>
	class IEngineFeatureFactory
	{
	public:
		/// <summary>
		/// Creates a feature.
		/// </summary>
		/// <param name="engine">Engine that is an owner of the feature.</param>
		/// <returns>Pointer to a feature.</returns>
		virtual T* Create(IEngineView* engine) = 0;

	protected:
		virtual ~IEngineFeatureFactory() noexcept = default;
	};
}
