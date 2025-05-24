/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12:IRenderSystemContext;

import PonyDebug.Log;

import :IDescriptorHeapManager;
import :IResourceManager;

export namespace PonyEngine::Render::Direct3D12
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

		/// @brief Gets the render device.
		/// @return Render device.
		[[nodiscard("Pure function")]]
		virtual ID3D12Device10& Device() noexcept = 0;
		/// @brief Gets the render device.
		/// @return Render device.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Device10& Device() const noexcept = 0;

		/// @brief Gets the resource manager.
		/// @return Resource manager.
		[[nodiscard("Pure function")]]
		virtual IResourceManager& ResourceManager() noexcept = 0;
		/// @brief Gets the resource manager.
		/// @return Resource manager.
		[[nodiscard("Pure function")]]
		virtual const IResourceManager& ResourceManager() const noexcept = 0;

		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual IDescriptorHeapManager& DescriptorHeapManager() noexcept = 0;
		/// @brief Gets the descriptor heap manager.
		/// @return Descriptor heap manager.
		[[nodiscard("Pure function")]]
		virtual const IDescriptorHeapManager& DescriptorHeapManager() const noexcept = 0;
	};
}
