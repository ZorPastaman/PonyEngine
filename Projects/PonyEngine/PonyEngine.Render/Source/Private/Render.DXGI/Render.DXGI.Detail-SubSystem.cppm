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

#include "PonyBase/Core/DXGI/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.DXGI.Detail:SubSystem;

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Utility;

import PonyDebug.Log;

import :SwapChain;
import :IRenderSystemContext;
import :ISubSystemContext;

export namespace PonyEngine::Render::DXGI
{
	/// @brief DXGI system.
	class SubSystem final : private ISubSystemContext
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit SubSystem(IRenderSystemContext& renderSystem);
		SubSystem(const SubSystem&) = delete;
		[[nodiscard("Pure constructor")]]
		SubSystem(SubSystem&& other) noexcept = default;

		~SubSystem() noexcept;

		/// @brief Gets the swap chain.
		/// @return Swap chain.
		[[nodiscard("Pure function")]]
		ISwapChain* SwapChain() noexcept;
		/// @brief Gets the swap chain.
		/// @return Swap chain.
		[[nodiscard("Pure function")]]
		const ISwapChain* SwapChain() const noexcept;
		/// @brief Creates a swap chain.
		/// @note The context must be ready to provide a device to call this function.
		/// @note The function may be called only once.
		/// @param swapChainParams Swap chain parameters.
		/// @return Created swap chain.
		ISwapChain& CreateSwapChain(const SwapChainParams& swapChainParams);

		/// @brief Presents a new frame.
		/// @note It may be called only after creation of a swap chain.
		void Present();

		SubSystem& operator =(const SubSystem&) = delete;
		SubSystem& operator =(SubSystem&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDXGIFactory7& Factory() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDXGIFactory7& Factory() const noexcept override;

		IRenderSystemContext* renderSystem; ///< Render system context.

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug; ///< DXGI debug.
#endif
		Microsoft::WRL::ComPtr<IDXGIFactory7> factory; ///< DXGI factory.

		std::unique_ptr<class SwapChain> swapChain; ///< Swap chain.
	};
}

namespace PonyEngine::Render::DXGI
{
	SubSystem::SubSystem(IRenderSystemContext& renderSystem) :
		renderSystem{&renderSystem}
	{
#ifdef _DEBUG
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI debug interface.");
		if (const HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface acquired.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Enable DXGI leak tracking.");
		debug->EnableLeakTrackingForThread();
#endif

		UINT factoryFlags = 0;
#ifdef _DEBUG
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Acquire DXGI factory. Factory flags: '0x{:X}'.", factoryFlags);
		if (const HRESULT result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(factory.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire DXGI factory with '0x{:X} result.'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI factory acquired.");
	}

	SubSystem::~SubSystem() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy swap chain.");
		swapChain.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Release DXGI factory.");
		factory.Reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI factory released.");

#ifdef _DEBUG
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Report DXGI live objects.");
		if (const HRESULT result = debug->ReportLiveObjects(DXGI_DEBUG_ALL, static_cast<DXGI_DEBUG_RLO_FLAGS>(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)); FAILED(result)) [[unlikely]]
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Error, "Failed to report live objects with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI live objects reported.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Release DXGI debug interface.");
		debug.Reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI debug interface released.");
#endif
	}

	ISwapChain* SubSystem::SwapChain() noexcept
	{
		return swapChain.get();
	}

	const ISwapChain* SubSystem::SwapChain() const noexcept
	{
		return swapChain.get();
	}

	ISwapChain& SubSystem::CreateSwapChain(const SwapChainParams& swapChainParams)
	{
		assert(!swapChain && "The swap chain has already been created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create swap chain.");
		swapChain = std::make_unique<class SwapChain>(*static_cast<ISubSystemContext*>(this), swapChainParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Set windowed mode.");
		if (const HRESULT result = factory->MakeWindowAssociation(swapChainParams.hWnd, DXGI_MWA_NO_ALT_ENTER); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to make window association with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		swapChain->SetFullscreenState(false);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Windowed mode set.");

		return *swapChain;
	}

	void SubSystem::Present()
	{
		swapChain->Present();
	}

	PonyDebug::Log::ILogger& SubSystem::Logger() noexcept
	{
		return renderSystem->Logger();
	}

	const PonyDebug::Log::ILogger& SubSystem::Logger() const noexcept
	{
		return renderSystem->Logger();
	}

	IDXGIFactory7& SubSystem::Factory() noexcept
	{
		return *factory.Get();
	}

	const IDXGIFactory7& SubSystem::Factory() const noexcept
	{
		return *factory.Get();
	}
}
