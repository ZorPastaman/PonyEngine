/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderSystem;

import PonyBase.Geometry;
import PonyBase.Math;

import :RenderObjectHandle;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
	public:
		IRenderSystem(const IRenderSystem&) = delete;
		IRenderSystem(IRenderSystem&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyBase::Math::RGBA<float> ClearColor() const noexcept = 0;
		virtual void ClearColor(const PonyBase::Math::RGBA<float>& color) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual PonyBase::Math::Matrix4x4<float> CameraTrsMatrix() const noexcept = 0;
		virtual void CameraTrsMatrix(const PonyBase::Math::Matrix4x4<float>& trs) noexcept = 0;

		virtual RenderObjectHandle CreateRenderObject(const PonyBase::Geometry::Mesh& mesh, const PonyBase::Math::Matrix4x4<float>& trs) = 0;
		virtual void DestroyRenderObject(RenderObjectHandle renderObjectHandle) = 0;

		virtual void UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyBase::Math::Matrix4x4<float>& trs) const noexcept = 0;

		IRenderSystem& operator =(const IRenderSystem&) = delete;
		IRenderSystem& operator =(IRenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystem() noexcept = default;

		~IRenderSystem() noexcept = default;
	};
}
