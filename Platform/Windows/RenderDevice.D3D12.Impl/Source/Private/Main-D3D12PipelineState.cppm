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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12PipelineState;

import std;

import PonyEngine.Platform.Windows;

import :D3D12ObjectUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12PipelineState final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12PipelineState(ID3D12PipelineState& pipelineState) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit D3D12PipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState) noexcept;
		D3D12PipelineState(const D3D12PipelineState&) = delete;
		D3D12PipelineState(D3D12PipelineState&&) = delete;

		~D3D12PipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() const noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		D3D12PipelineState& operator =(const D3D12PipelineState&) = delete;
		D3D12PipelineState& operator =(D3D12PipelineState&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12PipelineState> pipelineState;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12PipelineState::D3D12PipelineState(ID3D12PipelineState& pipelineState) noexcept :
		pipelineState(&pipelineState)
	{
	}

	D3D12PipelineState::D3D12PipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState) noexcept :
		pipelineState(std::move(pipelineState))
	{
		assert(this->pipelineState && "Invalid pipeline state.");
	}

	ID3D12PipelineState& D3D12PipelineState::PipelineState() const noexcept
	{
		return *pipelineState;
	}

	std::string_view D3D12PipelineState::Name() const noexcept
	{
		return name;
	}

	void D3D12PipelineState::Name(const std::string_view name)
	{
		SetObjectName(*pipelineState, name);

		try
		{
			this->name = name;
		}
		catch (...)
		{
			SetObjectName(*pipelineState, this->name);
			throw;
		}
	}
}
