/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderObjectManager;

import PonyMath.Geometry;

import :IRenderObject;
import :RenderObjectHandle;

export namespace PonyEngine::Render
{
	class IRenderObjectManager
	{
	public:
		IRenderObjectManager(const IRenderObjectManager&) = delete;
		IRenderObjectManager(IRenderObjectManager&&) = delete;

		virtual RenderObjectHandle CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity) = 0;
		virtual void DestroyObject(RenderObjectHandle handle) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IRenderObject* FindRenderObject(RenderObjectHandle handle) noexcept = 0;

		IRenderObjectManager& operator =(const IRenderObjectManager&) = delete;
		IRenderObjectManager& operator =(IRenderObjectManager&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderObjectManager() noexcept = default;

		~IRenderObjectManager() noexcept = default;
	};
}
