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

export module PonyEngine.Render.Detail:IRenderSystemContext;

import PonyDebug.Log;

import :IPipeline;
import :IRenderAgent;

export namespace PonyEngine::Render
{
	/// @brief Render system context.
	class IRenderSystemContext
	{
		INTERFACE_BODY(IRenderSystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the pipeline.
		/// @return Pipeline.
		[[nodiscard("Pure function")]]
		virtual IPipeline& Pipeline() noexcept = 0;
		/// @brief Gets the pipeline.
		/// @return Pipeline.
		[[nodiscard("Pure function")]]
		virtual const IPipeline& Pipeline() const noexcept = 0;

		/// @brief Gets the render agent.
		/// @return Render agent.
		[[nodiscard("Pure function")]]
		virtual IRenderAgent& RenderAgent() noexcept = 0;
		/// @brief Gets the render agent.
		/// @return Render agent.
		[[nodiscard("Pure function")]]
		virtual const IRenderAgent& RenderAgent() const noexcept = 0;
	};
}
