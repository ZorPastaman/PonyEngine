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

export module PonyEngine.Render:IMaterialObserver;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Material observer.
	class IMaterialObserver
	{
		INTERFACE_BODY(IMaterialObserver)

		/// @brief Invoked when a pipeline state is changed.
		virtual void OnPipelineStateChanged() noexcept = 0;
		/// @brief Invoked when a data structure is changed.
		virtual void OnDataChanged() noexcept = 0;
		/// @brief Invoked when a data buffer is changed.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		virtual void OnDataChanged(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) noexcept = 0;
		/// @brief Invoked when a name is changed.
		virtual void OnNameChanged() noexcept = 0;
	};
}