/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows:IWindowsDirect3D12RenderSystem;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	class IWindowsDirect3D12RenderSystem : public IDirect3D12RenderSystem
	{
	public:
		IWindowsDirect3D12RenderSystem(const IWindowsDirect3D12RenderSystem&) = delete;
		IWindowsDirect3D12RenderSystem(IWindowsDirect3D12RenderSystem&&) = delete;

		IWindowsDirect3D12RenderSystem& operator =(const IWindowsDirect3D12RenderSystem&) = delete;
		IWindowsDirect3D12RenderSystem& operator =(IWindowsDirect3D12RenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsDirect3D12RenderSystem() noexcept = default;

		~IWindowsDirect3D12RenderSystem() noexcept = default;
	};
}
