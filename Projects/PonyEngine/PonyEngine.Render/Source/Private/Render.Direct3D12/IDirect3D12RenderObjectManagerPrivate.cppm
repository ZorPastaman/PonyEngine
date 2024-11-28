/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderObjectManagerPrivate;

import <cstddef>;

import PonyEngine.Render.Direct3D12;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render object manager.
	class IDirect3D12RenderObjectManagerPrivate : public IDirect3D12RenderObjectManager
	{
		INTERFACE_BODY(IDirect3D12RenderObjectManagerPrivate)

		/// @brief Gets the render object count.
		/// @return Render object count.
		[[nodiscard("Pure function")]]
		virtual std::size_t RenderObjectCount() const noexcept = 0;
		/// @brief Gets a render object by the @p index.
		/// @param index Render object index.
		/// @return Render object.
		[[nodiscard("Pure function")]]
		virtual Direct3D12RenderObject& RenderObject(std::size_t index) noexcept = 0;
		/// @brief Gets a render object by the @p index.
		/// @param index Render object index.
		/// @return Render object.
		[[nodiscard("Pure function")]]
		virtual const Direct3D12RenderObject& RenderObject(std::size_t index) const noexcept = 0;
	};
}
