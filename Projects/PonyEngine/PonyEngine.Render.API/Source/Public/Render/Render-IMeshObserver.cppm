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
	/// @brief Mesh observer.
	class IMeshObserver
	{
		INTERFACE_BODY(IMeshObserver)

		/// @brief Invoked when a mesh structure is changed.
		virtual void OnMeshChanged() noexcept = 0;
		/// @brief Invoked when a mesh buffer is changed.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		virtual void OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept = 0;

		/// @brief Invoked when thread group counts are changed.
		virtual void OnThreadGroupCountsChanged() noexcept = 0;
		/// @brief Invoked when a bounding box is changed.
		virtual void OnBoundingBoxChanged() noexcept = 0;

		/// @brief Invoked when a name is changed.
		virtual void OnNameChanged() noexcept = 0;
	};
}
