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

import <string_view>;
import <utility>;

import PonyBase.Memory;

import PonyDebug.Log;

import PonyEngine.Core.Factory;
import PonyEngine.Render.Direct3D12.Windows.Factory;

import :WindowsDirect3D12RenderSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory.
	class WindowsDirect3D12RenderSystemFactory final : public IWindowsDirect3D12RenderSystemFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystemFactory() noexcept = default;
		WindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory(WindowsDirect3D12RenderSystemFactory&&) = delete;

		~WindowsDirect3D12RenderSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual WindowsDirect3D12RenderSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsDirect3D12RenderSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsDirect3D12RenderSystemFactory& operator =(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory& operator =(WindowsDirect3D12RenderSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystemFactory"; ///< Class name.

	private:
		WindowsDirect3D12RenderSystemParams renderSystemParams;
	};
}

namespace PonyEngine::Render
{
	Core::SystemData WindowsDirect3D12RenderSystemFactory::Create(Core::IEngineContext& engine, const Core::EngineSystemParams&)
	{
		auto system = PonyBase::Memory::UniquePointer<WindowsDirect3D12RenderSystem>::Create(engine, renderSystemParams);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IRenderSystem, IDirect3D12RenderSystem, IWindowsDirect3D12RenderSystem>(*system);

		return Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<Core::ITickableEngineSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	WindowsDirect3D12RenderSystemParams& WindowsDirect3D12RenderSystemFactory::SystemParams() noexcept
	{
		return renderSystemParams;
	}

	const WindowsDirect3D12RenderSystemParams& WindowsDirect3D12RenderSystemFactory::SystemParams() const noexcept
	{
		return renderSystemParams;
	}

	std::string_view WindowsDirect3D12RenderSystemFactory::SystemName() const noexcept
	{
		return WindowsDirect3D12RenderSystem::StaticName;
	}

	std::string_view WindowsDirect3D12RenderSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
