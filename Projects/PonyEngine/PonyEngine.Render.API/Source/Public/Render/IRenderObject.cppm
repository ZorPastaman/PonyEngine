/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderObject;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	class IRenderObject
	{
	public:
		IRenderObject(const IRenderObject&) = delete;
		IRenderObject(IRenderObject&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ModelMatrix() const noexcept = 0;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;

		IRenderObject& operator =(const IRenderObject&) = delete;
		IRenderObject& operator =(IRenderObject&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderObject() noexcept = default;

		~IRenderObject() noexcept = default;
	};
}
