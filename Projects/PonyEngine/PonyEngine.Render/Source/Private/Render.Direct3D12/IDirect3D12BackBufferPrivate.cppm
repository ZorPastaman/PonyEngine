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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12BackBufferPrivate;

import PonyMath.Utility;

export namespace PonyEngine::Render
{
	class IDirect3D12BackBufferPrivate
	{
		INTERFACE_BODY(IDirect3D12BackBufferPrivate)

		/// @brief Gets the back buffer format.
		/// @return Back buffer format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept = 0;

		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept = 0;
		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept = 0;

		/// @brief Gets the current back buffer handle.
		/// @return Back buffer handle.
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferHandle() const noexcept = 0;
	};
}
