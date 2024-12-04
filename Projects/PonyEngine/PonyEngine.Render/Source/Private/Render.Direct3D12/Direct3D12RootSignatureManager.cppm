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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RootSignatureManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import :Direct3D12Shader;
import :IDirect3D12RootSignatureManagerPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 root signature manager.
	class Direct3D12RootSignatureManager final : public IDirect3D12RootSignatureManagerPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12RootSignatureManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RootSignatureManager(IDirect3D12SystemContext& d3d12System) noexcept;
		Direct3D12RootSignatureManager(const Direct3D12RootSignatureManager&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignatureManager(Direct3D12RootSignatureManager&& other) noexcept = default;

		~Direct3D12RootSignatureManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Direct3D12RootSignature> CreateRootSignature(const Direct3D12Shader& rootSignatureShader, UINT mvpIndex) override;

		/// @brief Cleans out of dead root signatures.
		void Clean() noexcept;

		Direct3D12RootSignatureManager& operator =(const Direct3D12RootSignatureManager&) = delete;
		Direct3D12RootSignatureManager& operator =(Direct3D12RootSignatureManager&& other) noexcept = default;

	private:
		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Direct3D12RootSignature>> rootSignatures; ///< Root signatures.
	};
}

namespace PonyEngine::Render
{
	Direct3D12RootSignatureManager::Direct3D12RootSignatureManager(IDirect3D12SystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Direct3D12RootSignature> Direct3D12RootSignatureManager::CreateRootSignature(const Direct3D12Shader& rootSignatureShader, const UINT mvpIndex)
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create root signature.");
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		if (const HRESULT result = d3d12System->Device().CreateRootSignature(0, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Root signature created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rootSignature.Get()));

		const auto d3d12RootSignature = std::make_shared<Direct3D12RootSignature>(*rootSignature.Get(), mvpIndex);
		rootSignatures.push_back(d3d12RootSignature);

		return d3d12RootSignature;
	}

	void Direct3D12RootSignatureManager::Clean() noexcept
	{
		for (std::size_t i = rootSignatures.size(); i-- > 0; )
		{
			if (rootSignatures[i].use_count() <= 1L)
			{
				rootSignatures.erase(rootSignatures.cbegin() + i);
			}
		}
	}
}
