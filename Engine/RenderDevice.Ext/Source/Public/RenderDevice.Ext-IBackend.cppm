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

export module PonyEngine.RenderDevice.Ext:IBackend;

import PonyEngine.RenderDevice;

export namespace PonyEngine::Render
{
	class IBackend
	{
		INTERFACE_BODY(IBackend)

		[[nodiscard("Pure function")]]
		virtual IRenderAPI& RenderApi() const noexcept = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
	};
}
