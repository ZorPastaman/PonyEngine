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

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource load process.
	class IResourceLoadProcess
	{
		PONY_INTERFACE_BODY(IResourceLoadProcess)

		/// @brief Invoked on a dependency success.
		/// @param dependencyIndex Dependency index.
		virtual void OnDependencySuccess(std::size_t dependencyIndex) = 0;
		/// @brief Invoked on a dependency failure.
		/// @param dependencyIndex Dependency index.
		virtual void OnDependencyFailure(std::size_t dependencyIndex) = 0;
		/// @brief Invoked on a cancel request.
		/// @note The cancel in the system is immediate but the process is kept alive till it's safe to release.
		/// @note It's considered safe when the process sets any status to the @p IResourceLoadRequest.
		virtual void OnCancel() = 0;
	};
}
