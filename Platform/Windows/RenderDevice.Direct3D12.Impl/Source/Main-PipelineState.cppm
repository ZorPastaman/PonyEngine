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
	/// @brief Pipeline state wrapper.
	class PipelineState final
	{
	public:
		/// @brief Creates a pipeline state wrapper.
		/// @param pipelineState Pipeline state.
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(ID3D12PipelineState& pipelineState) noexcept;
		/// @brief Creates a pipeline state wrapper.
		/// @param pipelineState Pipeline state.
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState) noexcept;
		PipelineState(const PipelineState&) = delete;
		PipelineState(PipelineState&&) = delete;

		~PipelineState() noexcept = default;

		/// @brief Gets a pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& GetPipelineState() const noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		PipelineState& operator =(const PipelineState&) = delete;
		PipelineState& operator =(PipelineState&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.

		std::string name; ///< Name.
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
