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

export module PonyEngine.Render.Direct3D12.Detail:IDepthStencilPrivate;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 depth stencil.
	class IDepthStencilPrivate
	{
		INTERFACE_BODY(IDepthStencilPrivate)

		/// @brief Gets the dsv format.
		/// @return Dsv format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT DsvFormat() const noexcept = 0;

		/// @brief Gets the depth stencil buffer.
		/// @return Depth stencil buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& DepthStencilTexture() noexcept = 0;
		/// @brief Gets the depth stencil buffer.
		/// @return Depth stencil buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& DepthStencilTexture() const noexcept = 0;
		/// @brief Gets the depth stencil view handle.
		/// @return Depth stencil view handle.
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE DsvHandle() const noexcept = 0;
	};
}
