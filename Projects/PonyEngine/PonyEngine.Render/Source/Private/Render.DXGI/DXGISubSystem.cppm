/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

#include "PonyEngine/Render/DXGI/Framework.h"

export module PonyEngine.Render.DXGI:DXGISubSystem;

import <cstdint>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

export namespace PonyEngine::Render
{
	/// @brief DXGI sub-system.
	class DXGISubSystem final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGISubSystem(IRenderer& renderer);
		DXGISubSystem(const DXGISubSystem&) = delete;
		DXGISubSystem(DXGISubSystem&&) = delete;

		~DXGISubSystem() noexcept;

		DXGISubSystem& operator =(const DXGISubSystem&) = delete;
		DXGISubSystem& operator =(DXGISubSystem&&) = delete;

	private:
		IRenderer* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
#endif
	};
}

namespace PonyEngine::Render
{
	DXGISubSystem::DXGISubSystem(IRenderer& renderer) :
		renderer{&renderer}
	{
#ifdef _DEBUG
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Create DXGI debug interface.");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get DXGI debug interface with '0x{:X}' result.", result));
		}
		PONY_LOG(renderer.Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Debug, "Enable DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif
	}

	DXGISubSystem::~DXGISubSystem() noexcept
	{
#ifdef _DEBUG
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Report DXGI live objects.");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result))
		{
			PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Error, "Failed to report live objects with '0x{:X}' result.", result);
		}
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI live objects reported.");

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI debug interface.");
		debug.Reset();
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface destroyed.");
#endif
	}
}
