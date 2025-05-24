/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Windows:RenderSystemFactoryData;

import <memory>;

import PonyEngine.Render;

export namespace PonyEngine::Render::Windows
{
	/// @brief Render system for Windows factory data.
	struct RenderSystemFactoryData final
	{
		std::shared_ptr<RenderSystemFactory> systemFactory; ///< Render system factory.
	};
}
