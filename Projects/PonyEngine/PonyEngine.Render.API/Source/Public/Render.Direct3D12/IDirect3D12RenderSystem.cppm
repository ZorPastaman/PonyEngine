/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderSystem;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	class IDirect3D12RenderSystem : public IRenderSystem
	{
	public:
		IDirect3D12RenderSystem(const IDirect3D12RenderSystem&) = delete;
		IDirect3D12RenderSystem(IDirect3D12RenderSystem&&) = delete;

		IDirect3D12RenderSystem& operator =(const IDirect3D12RenderSystem&) = delete;
		IDirect3D12RenderSystem& operator =(IDirect3D12RenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IDirect3D12RenderSystem() noexcept = default;

		~IDirect3D12RenderSystem() noexcept = default;
	};
}
