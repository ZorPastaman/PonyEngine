/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderSystem;

import PonyMath.Core;
import PonyMath.Geometry;

import PonyEngine.Core;

import :CameraParams;
import :RenderObjectHandle;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem : public Core::ISystem
	{
	public:
		IRenderSystem(const IRenderSystem&) = delete;
		IRenderSystem(IRenderSystem&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::RGBA<float> ClearColor() const noexcept = 0;
		virtual void ClearColor(const PonyMath::Core::RGBA<float>& color) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual CameraParams CameraParameters() const noexcept = 0; // TODO: Here and in other api interfaces, don't return values, return references.
		virtual void CameraParameters(const CameraParams& cameraParams) noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> CameraTrsMatrix() const noexcept = 0;
		virtual void CameraTrsMatrix(const PonyMath::Core::Matrix4x4<float>& trs) noexcept = 0;

		virtual RenderObjectHandle CreateRenderObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& trs) = 0;
		virtual void DestroyRenderObject(RenderObjectHandle renderObjectHandle) = 0;
		virtual void UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyMath::Core::Matrix4x4<float>& trs) const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		IRenderSystem& operator =(const IRenderSystem&) = delete;
		IRenderSystem& operator =(IRenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystem() noexcept = default;

		~IRenderSystem() noexcept = default;
	};
}
