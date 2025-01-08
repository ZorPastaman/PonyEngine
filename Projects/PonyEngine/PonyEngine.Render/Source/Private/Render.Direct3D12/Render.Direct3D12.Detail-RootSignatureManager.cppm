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

export module PonyEngine.Render.Direct3D12.Detail:RootSignatureManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.Utility;

import PonyDebug.Log;

import :IRootSignatureManagerPrivate;
import :ISubSystemContext;
import :Shader;
import :RootSignature;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 root signature manager.
	class RootSignatureManager final : public IRootSignatureManagerPrivate
	{
	public:
		/// @brief Creates a @p RootSignatureManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit RootSignatureManager(ISubSystemContext& d3d12System) noexcept;
		RootSignatureManager(const RootSignatureManager&) = delete;
		[[nodiscard("Pure constructor")]]
		RootSignatureManager(RootSignatureManager&& other) noexcept = default;

		~RootSignatureManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<RootSignature> CreateRootSignature(const Shader& rootSignatureShader, const std::unordered_map<std::string, UINT>& meshDataSlots, UINT mvpIndex) override;

		/// @brief Cleans out of dead root signatures.
		void Clean() noexcept;

		RootSignatureManager& operator =(const RootSignatureManager&) = delete;
		RootSignatureManager& operator =(RootSignatureManager&& other) noexcept = default;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<RootSignature>> rootSignatures; ///< Root signatures.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RootSignatureManager::RootSignatureManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<RootSignature> RootSignatureManager::CreateRootSignature(const Shader& rootSignatureShader, const std::unordered_map<std::string, UINT>& meshDataSlots, const UINT mvpIndex)
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create root signature.");
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		if (const HRESULT result = d3d12System->Device().CreateRootSignature(0, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Root signature created.");

		const auto d3d12RootSignature = std::make_shared<RootSignature>(*rootSignature.Get(), meshDataSlots, mvpIndex);
		rootSignatures.push_back(d3d12RootSignature);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Root signature created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(d3d12RootSignature.get()));

		return d3d12RootSignature;
	}

	void RootSignatureManager::Clean() noexcept
	{
		for (std::size_t i = rootSignatures.size(); i-- > 0; )
		{
			if (rootSignatures[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy root signature at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rootSignatures[i].get()));
				rootSignatures.erase(rootSignatures.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Root signature destroyed.");
			}
		}
	}
}
