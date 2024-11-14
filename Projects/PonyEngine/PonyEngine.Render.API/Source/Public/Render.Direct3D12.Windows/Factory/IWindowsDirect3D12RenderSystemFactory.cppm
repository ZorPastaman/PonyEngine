/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Factory:IWindowsDirect3D12RenderSystemFactory;

import PonyEngine.Render.Direct3D12.Factory;

export namespace PonyEngine::Render
{
	class IWindowsDirect3D12RenderSystemFactory : public IDirect3D12RenderSystemFactory
	{
	public:
		IWindowsDirect3D12RenderSystemFactory(const IWindowsDirect3D12RenderSystemFactory&) = delete;
		IWindowsDirect3D12RenderSystemFactory(IWindowsDirect3D12RenderSystemFactory&&) = delete;

		IWindowsDirect3D12RenderSystemFactory& operator =(const IWindowsDirect3D12RenderSystemFactory&) = delete;
		IWindowsDirect3D12RenderSystemFactory& operator =(IWindowsDirect3D12RenderSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsDirect3D12RenderSystemFactory() noexcept = default;

		~IWindowsDirect3D12RenderSystemFactory() noexcept = default;
	};
}
