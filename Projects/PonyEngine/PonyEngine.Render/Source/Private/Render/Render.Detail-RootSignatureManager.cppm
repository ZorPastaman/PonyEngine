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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:RootSignatureManager;

import <algorithm>;
import <memory>;
import <stdexcept>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :RootSignature;
import :RootSignatureDirtyFlag;
import :Shader;

export namespace PonyEngine::Render
{
	/// @brief Root signature manager.
	class RootSignatureManager final : public IRootSignatureManager
	{
	public:
		/// @brief Creates a root signature manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit RootSignatureManager(IRenderSystemContext& renderSystem) noexcept;
		RootSignatureManager(const RootSignatureManager&) = delete;
		RootSignatureManager(RootSignatureManager&&) = delete;

		~RootSignatureManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRootSignature> CreateRootSignature(const RootSignatureParams& params) override;

		/// @brief Ticks the root signature manager.
		void Tick();
		/// @brief Cleans out dead root signatures.
		void Clean();

		RootSignatureManager& operator =(const RootSignatureManager&) = delete;
		RootSignatureManager& operator =(RootSignatureManager&&) = delete;

	private:
		/// @brief Creates new root signatures on GPU.
		void Create();
		/// @brief Updates living root signatures.
		void Update();
		/// @brief Clears caches.
		void Clear() noexcept;

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<RootSignature>> rootSignatures; ///< Root signatures.
		std::vector<const RootSignature*> newRootSignatures; ///< Root signatures created this frame.
	};
}

namespace PonyEngine::Render
{
	RootSignatureManager::RootSignatureManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IRootSignature> RootSignatureManager::CreateRootSignature(const RootSignatureParams& params)
	{
		if (!params.shader) [[unlikely]]
		{
			throw std::invalid_argument("Shader is nullptr.");
		}
		assert(dynamic_cast<const Shader*>(params.shader.get()) && "The shader is not a valid type.");

		const auto rootSignature = std::make_shared<RootSignature>(params);
		rootSignatures.push_back(rootSignature);
		newRootSignatures.push_back(rootSignature.get());

		return rootSignature;
	}

	void RootSignatureManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
	}

	void RootSignatureManager::Clean()
	{
		for (std::size_t i = rootSignatures.size(); i-- > 0; )
		{
			const std::shared_ptr<RootSignature>& rootSignature = rootSignatures[i];
			if (rootSignature.use_count() > 1L)
			{
				continue;
			}

			if (const auto position = std::ranges::find(newRootSignatures, rootSignature.get()); position != newRootSignatures.cend())
			{
				newRootSignatures.erase(position);
			}
			else
			{
				renderSystem->RenderAgent().RootSignatureAgent().Destroy(*rootSignature);
			}
			rootSignatures.erase(rootSignatures.cbegin() + i);
		}
	}

	void RootSignatureManager::Create()
	{
		for (const RootSignature* rootSignature : newRootSignatures)
		{
			renderSystem->RenderAgent().RootSignatureAgent().Create(*rootSignature);
		}
	}

	void RootSignatureManager::Update()
	{
		for (const std::shared_ptr<RootSignature>& rootSignature : rootSignatures)
		{
			if (rootSignature->DirtyFlags() != RootSignatureDirtyFlag::None)
			{
				renderSystem->RenderAgent().RootSignatureAgent().Update(*rootSignature, rootSignature->DirtyFlags());
			}
		}
	}

	void RootSignatureManager::Clear() noexcept
	{
		for (const std::shared_ptr<RootSignature>& rootSignature : rootSignatures)
		{
			rootSignature->ResetDirty();
		}

		newRootSignatures.clear();
	}
}
