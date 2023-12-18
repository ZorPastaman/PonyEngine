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
	export template<typename T>
	class IEngineFeatureFactory
	{
	public:
		virtual T* Create(IEngineView* engine) = 0;

	protected:
		virtual ~IEngineFeatureFactory() noexcept = default;
	};
}
