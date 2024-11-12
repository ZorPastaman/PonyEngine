/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderView;

import PonyMath.Core;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	class IRenderView
	{
	public:
		IRenderView(const IRenderView&) = delete;
		IRenderView(IRenderView&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ViewMatrix() const noexcept = 0;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ProjectionMatrix() const noexcept = 0;
		virtual void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> Resolution() const noexcept = 0;

		IRenderView& operator =(const IRenderView&) = delete;
		IRenderView& operator =(IRenderView&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderView() noexcept = default;

		~IRenderView() noexcept = default;
	};
}
