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

import :Camera;

export namespace PonyEngine::Render
{
	/// @brief Pipeline.
	class IPipeline
	{
		INTERFACE_BODY(IPipeline)

		/// @brief Submits the camera for rendering.
		/// @param camera Camera to submit.
		virtual void Submit(const Camera& camera) = 0;
	};
}
