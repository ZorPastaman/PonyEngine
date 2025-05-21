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

export module PonyEngine.Render.Detail:IPipeline;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Pipeline.
	class IPipeline
	{
		INTERFACE_BODY(IPipeline)

		/// @brief Submits the render object for rendering.
		/// @param renderObject Render object to submit.
		virtual void Submit(const IRenderObject& renderObject) = 0;
		/// @brief Submits the camera for rendering.
		/// @param camera Camera to submit.
		virtual void Submit(const ICamera& camera) = 0;
	};
}
