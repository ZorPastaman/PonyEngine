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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RootSignatureManager;

import <cstddef>;
import <memory>;
import <unordered_map>;

import PonyEngine.Render.Detail;

import :Direct3D12RootSignature;
import :Direct3D12Shader;
import :IDirect3D12RootSignatureManagerPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12RootSignatureManager final : public IDirect3D12RootSignatureManagerPrivate
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RootSignatureManager(IDirect3D12SystemContext& render) noexcept;
		Direct3D12RootSignatureManager(const Direct3D12RootSignatureManager&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignatureManager(Direct3D12RootSignatureManager&& other) noexcept = default;

		~Direct3D12RootSignatureManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Direct3D12RootSignature> CreateRootSignature(const Direct3D12Shader& rootSignatureShader, UINT mvpIndex) override;

		Direct3D12RootSignatureManager& operator =(const Direct3D12RootSignatureManager&) = delete;
		Direct3D12RootSignatureManager& operator =(Direct3D12RootSignatureManager&& other) noexcept = default;

	private:
		IDirect3D12SystemContext* render;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RootSignatureManager::Direct3D12RootSignatureManager(IDirect3D12SystemContext& render) noexcept :
		render{&render}
	{
	}

	std::shared_ptr<Direct3D12RootSignature> Direct3D12RootSignatureManager::CreateRootSignature(const Direct3D12Shader& rootSignatureShader, const UINT mvpIndex)
	{
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		if (const HRESULT result = render->Device().CreateRootSignature(0, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_shared<Direct3D12RootSignature>(*rootSignature.Get(), mvpIndex);
	}
}
