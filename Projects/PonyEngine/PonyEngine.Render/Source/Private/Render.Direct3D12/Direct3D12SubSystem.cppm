/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12SubSystem;

import <cstdint>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Geometry;
import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Detail;

import :Direct3D12GraphicsPipeline;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem(IRendererContext& renderer, D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		[[nodiscard("Pure function")]]
		IRenderTarget* RenderTarget() const noexcept;
		[[nodiscard("Pure function")]]
		IRenderView* RenderView() const noexcept;
		[[nodiscard("Pure function")]]
		IRenderObjectManager* RenderObjectManager() const noexcept;

		void Initialize(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, const PonyMath::Utility::Resolution<UINT>& resolution, std::span<ID3D12Resource2*> buffers, DXGI_FORMAT rtvFormat) const;

		void PopulateCommands(UINT bufferIndex) const;
		void Execute() const;
		void WaitForEndOfFrame() const;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		IRendererContext* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		std::unique_ptr<Direct3D12GraphicsPipeline> graphicsPipeline;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRendererContext& renderer, const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout) :
		renderer{&renderer}
	{
#ifdef _DEBUG
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Debug, "Enable Direct3D 12 debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 device. Feature level: '0x{:X}.'", static_cast<unsigned int>(featureLevel));
		if (const HRESULT result = D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(device.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 graphics pipeline.");
		graphicsPipeline = std::make_unique<Direct3D12GraphicsPipeline>(*this->renderer, device.Get(), commandQueuePriority, fenceTimeout);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline created.'");
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 graphics pipeline.'");
		graphicsPipeline.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline destroyed.'");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 device.");
		device.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device released.");

#ifdef _DEBUG
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 debug interface.");
		debug.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface released.");
#endif
	}

	ID3D12CommandQueue* Direct3D12SubSystem::GetCommandQueue() const
	{
		return graphicsPipeline->GetCommandQueue();
	}

	IRenderTarget* Direct3D12SubSystem::RenderTarget() const noexcept
	{
		return graphicsPipeline->RenderTarget();
	}

	IRenderView* Direct3D12SubSystem::RenderView() const noexcept
	{
		return graphicsPipeline->RenderView();
	}

	IRenderObjectManager* Direct3D12SubSystem::RenderObjectManager() const noexcept
	{
		return graphicsPipeline->RenderObjectManager();
	}

	void Direct3D12SubSystem::Initialize(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, const PonyMath::Utility::Resolution<UINT>& resolution, const std::span<ID3D12Resource2*> buffers, const DXGI_FORMAT rtvFormat) const
	{
		graphicsPipeline->Initialize(viewMatrix, projectionMatrix, resolution, buffers, rtvFormat);
	}

	void Direct3D12SubSystem::PopulateCommands(const UINT bufferIndex) const
	{
		graphicsPipeline->PopulateCommands(bufferIndex);
	}

	void Direct3D12SubSystem::Execute() const
	{
		graphicsPipeline->Execute();
	}

	void Direct3D12SubSystem::WaitForEndOfFrame() const
	{
		graphicsPipeline->WaitForEndOfFrame();
	}
}
