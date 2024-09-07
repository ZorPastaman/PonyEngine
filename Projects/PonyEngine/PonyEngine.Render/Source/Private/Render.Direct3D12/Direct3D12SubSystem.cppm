/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12:Direct3D12SubSystem;

import <stdexcept>;

import PonyBase.StringUtility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem();
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> d3D12Debug;
#endif
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem()
	{
#ifdef _DEBUG
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(d3D12Debug.GetAddressOf())); FAILED(result))
		{
			throw std::logic_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 debug interface with '0x{:X}' result.", result));
		}

		d3D12Debug->EnableDebugLayer();
#endif
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
#ifdef _DEBUG
		d3D12Debug.Reset();
#endif
	}
}
