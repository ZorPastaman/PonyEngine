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

export module PonyEngine.Resource.Ext:IResourceLoadProcess;

export namespace PonyEngine::Resource
{
	/// @brief Resource load process.
	class IResourceLoadProcess
	{
		PONY_INTERFACE_BODY(IResourceLoadProcess)

		/// @brief Cancels the load.
		/// @note The cancel in the system is immediate but the process is kept alive till it's safe to release.
		/// @note It's considered safe when the process sets any status to the @p IResourceLoadRequest.
		virtual void Cancel() = 0;
	};
}
