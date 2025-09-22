/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Surface.Extension.Windows:SurfaceParams;

import PonyEngine.Surface.Extension;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Surface parameters.
	struct SurfaceParams final : Surface::SurfaceParams
	{
		HICON icon = nullptr; ///< Main application icon.
		HICON smallIcon = nullptr; ///< Small application icon.
		HCURSOR cursor = nullptr; ///< Cursor icon.
	};
}
