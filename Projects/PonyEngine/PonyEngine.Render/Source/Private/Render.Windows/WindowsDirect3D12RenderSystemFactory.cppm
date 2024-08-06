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

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystemFactory;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Render.Factory;

import :WindowsDirect3D12RenderSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory.
	class WindowsDirect3D12RenderSystemFactory final : public IRenderSystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystemFactory() noexcept = default;
		WindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory(WindowsDirect3D12RenderSystemFactory&&) = delete;

		~WindowsDirect3D12RenderSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemUniquePtr Create(Core::IEngine& engine) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		WindowsDirect3D12RenderSystemFactory& operator =(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory& operator =(WindowsDirect3D12RenderSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystemFactory"; ///< Class name.
	};
}

namespace PonyEngine::Render
{
	Core::SystemUniquePtr WindowsDirect3D12RenderSystemFactory::Create(Core::IEngine& engine)
	{
		return Core::SystemUniquePtr(new WindowsDirect3D12RenderSystem(engine), Core::SystemDeleter(*this));
	}

	void WindowsDirect3D12RenderSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<WindowsDirect3D12RenderSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<WindowsDirect3D12RenderSystem*>(system);
	}

	const char* WindowsDirect3D12RenderSystemFactory::GetSystemName() const noexcept
	{
		return WindowsDirect3D12RenderSystem::StaticName;
	}

	const char* WindowsDirect3D12RenderSystemFactory::GetName() const noexcept
	{
		return StaticName;
	}
}
