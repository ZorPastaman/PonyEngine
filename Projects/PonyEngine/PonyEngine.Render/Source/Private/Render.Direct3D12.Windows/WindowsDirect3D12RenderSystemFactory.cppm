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

import <utility>;

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Render.Direct3D12.Windows.Factory;

import :WindowsDirect3D12RenderSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory.
	class WindowsDirect3D12RenderSystemFactory final : public IWindowsDirect3D12RenderSystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystemFactory() noexcept = default;
		WindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory(WindowsDirect3D12RenderSystemFactory&&) = delete;

		~WindowsDirect3D12RenderSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngine& engine, const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowsDirect3D12RenderSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsDirect3D12RenderSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsDirect3D12RenderSystemFactory& operator =(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory& operator =(WindowsDirect3D12RenderSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystemFactory"; ///< Class name.

	private:
		WindowsDirect3D12RenderSystemParams renderSystemParams;
	};
}

namespace PonyEngine::Render
{
	Core::SystemData WindowsDirect3D12RenderSystemFactory::Create(Core::IEngine& engine, const Core::SystemParams&)
	{
		const auto system = new WindowsDirect3D12RenderSystem(engine, renderSystemParams);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IRenderSystem>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr(system, Core::SystemDeleter(*this)),
			.tickableSystem = system,
			.publicInterfaces = std::move(interfaces)
		};
	}

	void WindowsDirect3D12RenderSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<WindowsDirect3D12RenderSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<WindowsDirect3D12RenderSystem*>(system);
	}

	WindowsDirect3D12RenderSystemParams& WindowsDirect3D12RenderSystemFactory::SystemParams() noexcept
	{
		return renderSystemParams;
	}

	const WindowsDirect3D12RenderSystemParams& WindowsDirect3D12RenderSystemFactory::SystemParams() const noexcept
	{
		return renderSystemParams;
	}

	const char* WindowsDirect3D12RenderSystemFactory::SystemName() const noexcept
	{
		return WindowsDirect3D12RenderSystem::StaticName;
	}

	const char* WindowsDirect3D12RenderSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
