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

export module PonyEngine.Render.Direct3D12.Detail:IBackManager;

import <optional>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 back manager.
	class IBackManager
	{
		INTERFACE_BODY(IBackManager)

		/// @brief Gets the back format.
		/// @return Back format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept = 0;
		/// @brief Gets the back sRGB format.
		/// @return sRGB back format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT FormatSrgb() const noexcept = 0;

		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2* CurrentBackBuffer() noexcept = 0;
		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2* CurrentBackBuffer() const noexcept = 0;

		/// @brief Gets the current back rtv handle.
		/// @return Back rtv handle.
		[[nodiscard("Pure function")]]
		virtual std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CurrentRtvHandle() const noexcept = 0;
	};
}
