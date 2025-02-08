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

export module PonyEngine.Render:IMeshObserver;

import <cstdint>;

export namespace PonyEngine::Render
{
	class IMeshObserver
	{
		INTERFACE_BODY(IMeshObserver)

		virtual void OnMeshChanged() noexcept = 0;
		virtual void OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept = 0;
		virtual void OnThreadGroupCountsChanged() noexcept = 0;
		virtual void OnBoundingBoxChanged() noexcept = 0;
		virtual void OnNameChanged() noexcept = 0;
	};
}
