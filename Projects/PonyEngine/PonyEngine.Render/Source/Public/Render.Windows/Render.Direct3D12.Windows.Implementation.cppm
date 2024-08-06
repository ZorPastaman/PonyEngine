/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Render.Direct3D12.Windows.Implementation;

import <memory>;

export import PonyEngine.Render.Factory;

import :WindowsDirect3D12RenderSystemFactory;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory deleter.
	struct PONY_DLL_EXPORT WindowsDirect3D12RenderSystemFactoryDeleter final
	{
		/// @brief Deletes the @p factory.
		/// @param factory Render system factory to delete.
		void operator ()(IRenderSystemFactory* factory) const noexcept;
	};

	using WindowsDirect3D12RenderUniquePtr = std::unique_ptr<IRenderSystemFactory, WindowsDirect3D12RenderSystemFactoryDeleter>; ///< Direct3D 12 render system for Windows factory unique_ptr typedef.

	/// @brief Creates a Direct3D 12 render system for Windows factory.
	/// @return Direct3D 12 render system for Windows factory
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsDirect3D12RenderUniquePtr CreateWindowsDirect3D12RenderSystemFactory();
}

namespace PonyEngine::Render
{
	void WindowsDirect3D12RenderSystemFactoryDeleter::operator ()(IRenderSystemFactory* const factory) const noexcept
	{
		assert((dynamic_cast<WindowsDirect3D12RenderSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<WindowsDirect3D12RenderSystemFactory*>(factory);
	}

	WindowsDirect3D12RenderUniquePtr CreateWindowsDirect3D12RenderSystemFactory()
	{
		return std::unique_ptr<IRenderSystemFactory, WindowsDirect3D12RenderSystemFactoryDeleter>(new WindowsDirect3D12RenderSystemFactory());
	}
}
