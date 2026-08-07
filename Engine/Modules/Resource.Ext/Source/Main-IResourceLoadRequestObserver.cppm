/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Resource.Ext:IResourceLoadRequestObserver;

export namespace PonyEngine::Resource
{
	/// @brief Resource load request observer.
	class IResourceLoadRequestObserver
	{
		PONY_INTERFACE_BODY(IResourceLoadRequestObserver)

		/// @brief Invoked on a load error. Usually due to a dependency error.
		virtual void OnError() = 0;
		/// @brief Invoked on a cancel requested.
		virtual void OnCancel() = 0;
	};
}
