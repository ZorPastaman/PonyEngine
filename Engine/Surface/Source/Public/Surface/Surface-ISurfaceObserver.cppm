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

export module PonyEngine.Surface:ISurfaceObserver;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Surface observer.
	class ISurfaceObserver
	{
		INTERFACE_BODY(ISurfaceObserver)

		/// @brief Invoked when the surface activity is changed.
		/// @param isActive Is the surface active?
		virtual void OnActiveChanged(bool isActive) {}
		/// @brief Invoked when the surface focus is changed.
		/// @param isInFocus Is the surface in focus?
		virtual void OnFocusChanged(bool isInFocus) {}

		/// @brief Invoked when the surface is moved.
		/// @param position New surface position.
		virtual void OnMoved(const Math::Vector2<std::int32_t>& position) {}
		/// @brief Invoked when the surface is resized.
		/// @param size New surface size.
		virtual void OnResized(const Math::Vector2<std::int32_t>& size) {}

		/// @brief Invoked when the surface resolution is changed.
		/// @param resolution New surface resolution.
		virtual void OnResolutionChanged(const Math::Vector2<std::int32_t>& resolution) {}
	};
}
