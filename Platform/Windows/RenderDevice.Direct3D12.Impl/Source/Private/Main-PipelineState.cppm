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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:PipelineState;

import std;

import PonyEngine.Platform.Windows;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class PipelineState final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(ID3D12PipelineState& pipelineState) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState) noexcept;
		PipelineState(const PipelineState&) = delete;
		PipelineState(PipelineState&&) = delete;

		~PipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12PipelineState& GetPipelineState() const noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		PipelineState& operator =(const PipelineState&) = delete;
		PipelineState& operator =(PipelineState&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12PipelineState> pipelineState;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	PipelineState::PipelineState(ID3D12PipelineState& pipelineState) noexcept :
		pipelineState(&pipelineState)
	{
	}

	PipelineState::PipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState) noexcept :
		pipelineState(std::move(pipelineState))
	{
		assert(this->pipelineState && "Invalid pipeline state.");
	}

	ID3D12PipelineState& PipelineState::GetPipelineState() const noexcept
	{
		return *pipelineState;
	}

	std::string_view PipelineState::Name() const noexcept
	{
		return name;
	}

	void PipelineState::Name(const std::string_view name)
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
