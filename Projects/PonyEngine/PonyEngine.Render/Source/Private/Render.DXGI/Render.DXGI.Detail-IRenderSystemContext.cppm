/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.DXGI.Detail:IRenderSystemContext;

import PonyEngine.Render.Detail;

export namespace PonyEngine::Render::DXGI
{
	/// @brief DXGI render system context.
	class IRenderSystemContext : public Render::IRenderSystemContext
	{
		INTERFACE_BODY(IRenderSystemContext)

		/// @brief Gets the graphics device.
		/// @return Graphics device.
		[[nodiscard("Pure function")]]
		virtual IUnknown* Device() noexcept = 0;
		/// @brief Gets the graphics device.
		/// @return Graphics device.
		[[nodiscard("Pure function")]]
		virtual const IUnknown* Device() const noexcept = 0;
	};
}
