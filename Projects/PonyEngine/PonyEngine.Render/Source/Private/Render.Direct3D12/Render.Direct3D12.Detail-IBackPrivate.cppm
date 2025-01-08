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

export module PonyEngine.Render.Direct3D12.Detail:IBackPrivate;

import PonyMath.Utility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 back.
	class IBackPrivate
	{
		INTERFACE_BODY(IBackPrivate)

		/// @brief Gets the back view format.
		/// @return Back view format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept = 0;
		/// @brief Gets the back view srgb format.
		/// @return Srgb back view format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT FormatSrgb() const noexcept = 0;

		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept = 0;
		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept = 0;

		/// @brief Gets the current back view handle.
		/// @return Back view handle.
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackViewHandle() const noexcept = 0;
	};
}
