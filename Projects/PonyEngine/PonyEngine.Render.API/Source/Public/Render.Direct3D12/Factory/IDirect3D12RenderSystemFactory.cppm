/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Factory:IDirect3D12RenderSystemFactory;

import PonyEngine.Render.Factory;

import :Direct3D12RenderParams;

export namespace PonyEngine::Render
{
	class IDirect3D12RenderSystemFactory : public IRenderSystemFactory
	{
	public:
		IDirect3D12RenderSystemFactory(const IDirect3D12RenderSystemFactory&) = delete;
		IDirect3D12RenderSystemFactory(IDirect3D12RenderSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual Direct3D12RenderParams& RenderSystemParams() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const Direct3D12RenderParams& RenderSystemParams() const noexcept override = 0;

		IDirect3D12RenderSystemFactory& operator =(const IDirect3D12RenderSystemFactory&) = delete;
		IDirect3D12RenderSystemFactory& operator =(IDirect3D12RenderSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IDirect3D12RenderSystemFactory() noexcept = default;

		~IDirect3D12RenderSystemFactory() noexcept = default;
	};
}
