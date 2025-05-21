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

export module PonyEngine.Render.Detail:PipelineStateManager;

import <cstddef>;
import <memory>;
import <stdexcept>;
import <utility>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :PipelineState;
import :PipelineStateDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state manager.
	class PipelineStateManager final : public IPipelineStateManager
	{
	public:
		/// @brief Creates a pipeline state manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit PipelineStateManager(IRenderSystemContext& renderSystem) noexcept;
		PipelineStateManager(const PipelineStateManager&) = delete;
		PipelineStateManager(PipelineStateManager&&) = delete;

		~PipelineStateManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IPipelineState> CreatePipelineState(const PipelineStateParams& params) override;

		/// @brief Ticks the pipeline state manager.
		void Tick();
		/// @brief Cleans out dead pipeline states.
		void Clean();

		PipelineStateManager& operator =(const PipelineStateManager&) = delete;
		PipelineStateManager& operator =(PipelineStateManager&&) = delete;

	private:
		/// @brief Creates new pipeline states on GPU.
		void Create();
		/// @brief Update living pipeline states.
		void Update();
		/// @brief Clears caches.
		void Clear() noexcept;

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<PipelineState>> pipelineStates; ///< Pipeline states.
		std::vector<const PipelineState*> newPipelineStates; ///< New pipeline states.
	};
}

namespace PonyEngine::Render
{
	PipelineStateManager::PipelineStateManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IPipelineState> PipelineStateManager::CreatePipelineState(const PipelineStateParams& params)
	{
		if (!params.rootSignature) [[unlikely]]
		{
			throw std::invalid_argument("Root signature is nullptr.");
		}
		if (!params.meshShader) [[unlikely]]
		{
			throw std::invalid_argument("Mesh shader is nullptr.");
		}
		if (!params.pixelShader) [[unlikely]]
		{
			throw std::invalid_argument("Pixel shader is nullptr.");
		}

		const auto pipelineState = std::make_shared<PipelineState>(params);
		pipelineStates.push_back(pipelineState);
		newPipelineStates.push_back(pipelineState.get());

		return pipelineState;
	}

	void PipelineStateManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
	}

	void PipelineStateManager::Clean()
	{
		for (std::size_t i = pipelineStates.size(); i-- > 0; )
		{
			const std::shared_ptr<PipelineState>& pipelineState = pipelineStates[i];
			if (pipelineState.use_count() > 1L)
			{
				continue;
			}

			if (const auto position = std::ranges::find(newPipelineStates, pipelineState.get()); position != newPipelineStates.cend())
			{
				newPipelineStates.erase(position);
			}
			else
			{
				renderSystem->RenderAgent().PipelineStateAgent().Destroy(*pipelineState);
			}
			pipelineStates.erase(pipelineStates.cbegin() + i);
		}
	}

	void PipelineStateManager::Create()
	{
		for (const PipelineState* pipelineState : newPipelineStates)
		{
			renderSystem->RenderAgent().PipelineStateAgent().Create(*pipelineState);
		}
	}

	void PipelineStateManager::Update()
	{
		for (const std::shared_ptr<PipelineState>& pipelineState : pipelineStates)
		{
			if (pipelineState->DirtyFlags() != PipelineStateDirtyFlag::None)
			{
				renderSystem->RenderAgent().PipelineStateAgent().Update(*pipelineState, pipelineState->DirtyFlags());
			}
		}
	}

	void PipelineStateManager::Clear() noexcept
	{
		for (const std::shared_ptr<PipelineState>& pipelineState : pipelineStates)
		{
			pipelineState->ResetDirty();
		}

		newPipelineStates.clear();
	}
}
