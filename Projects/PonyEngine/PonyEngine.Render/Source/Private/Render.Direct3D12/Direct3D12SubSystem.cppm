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

export module PonyEngine.Render.Direct3D12:Direct3D12SubSystem;

import <cstdint>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Geometry;
import PonyBase.Math;
import PonyBase.Screen;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

import :Direct3D12GraphicsPipeline;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem(IRenderer& renderer, D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Math::RGBA<FLOAT>& ClearColor() noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Math::RGBA<FLOAT>& ClearColor() const noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Math::Matrix4x4<FLOAT>& CameraTrsMatrix() noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Math::Matrix4x4<FLOAT>& CameraTrsMatrix() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		void Initialize(const PonyBase::Screen::Resolution<UINT>& resolution, FLOAT fov, FLOAT nearPlane, FLOAT farPlane, std::span<ID3D12Resource2*> buffers, DXGI_FORMAT rtvFormat) const;

		void PopulateCommands(UINT bufferIndex) const;
		void Execute() const;
		void WaitForEndOfFrame() const;

		RenderObjectHandle CreateRenderObject(const PonyBase::Geometry::Mesh& mesh, const PonyBase::Math::Matrix4x4<FLOAT>& trs) const;
		void DestroyRenderObject(RenderObjectHandle renderObjectHandle) const noexcept;

		void UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyBase::Math::Matrix4x4<FLOAT>& trs) const noexcept;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		IRenderer* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		std::unique_ptr<Direct3D12GraphicsPipeline> graphicsPipeline;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRenderer& renderer, const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout) :
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

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 graphics pipeline.'");
		graphicsPipeline.reset(new Direct3D12GraphicsPipeline(*this->renderer, device.Get(), commandQueuePriority, fenceTimeout));
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

	PonyBase::Math::RGBA<FLOAT>& Direct3D12SubSystem::ClearColor() noexcept
	{
		return graphicsPipeline->ClearColor();
	}

	const PonyBase::Math::RGBA<FLOAT>& Direct3D12SubSystem::ClearColor() const noexcept
	{
		return graphicsPipeline->ClearColor();
	}

	PonyBase::Math::Matrix4x4<FLOAT>& Direct3D12SubSystem::CameraTrsMatrix() noexcept
	{
		return graphicsPipeline->CameraTrsMatrix();
	}

	const PonyBase::Math::Matrix4x4<FLOAT>& Direct3D12SubSystem::CameraTrsMatrix() const noexcept
	{
		return graphicsPipeline->CameraTrsMatrix();
	}

	ID3D12CommandQueue* Direct3D12SubSystem::GetCommandQueue() const
	{
		return graphicsPipeline->GetCommandQueue();
	}

	void Direct3D12SubSystem::Initialize(const PonyBase::Screen::Resolution<UINT>& resolution, const FLOAT fov, const FLOAT nearPlane, const FLOAT farPlane, const std::span<ID3D12Resource2*> buffers, const DXGI_FORMAT rtvFormat) const
	{
		graphicsPipeline->Initialize(resolution, fov, nearPlane, farPlane, buffers, rtvFormat);
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

	RenderObjectHandle Direct3D12SubSystem::CreateRenderObject(const PonyBase::Geometry::Mesh& mesh, const PonyBase::Math::Matrix4x4<FLOAT>& trs) const
	{
		return graphicsPipeline->CreateRenderObject(mesh, trs);
	}

	void Direct3D12SubSystem::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) const noexcept
	{
		graphicsPipeline->DestroyRenderObject(renderObjectHandle);
	}

	void Direct3D12SubSystem::UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyBase::Math::Matrix4x4<FLOAT>& trs) const noexcept
	{
		graphicsPipeline->UpdateRenderObjectTrs(handle, trs);
	}
}
