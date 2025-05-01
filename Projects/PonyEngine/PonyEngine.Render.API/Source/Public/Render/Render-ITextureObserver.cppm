/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:ITextureObserver;

export namespace PonyEngine::Render
{
	/// @brief Texture observer.
	class ITextureObserver
	{
		INTERFACE_BODY(ITextureObserver)

		/// @brief Invoked when a texture is changed.
		virtual void OnTextureChanged() noexcept = 0;
	};
}
