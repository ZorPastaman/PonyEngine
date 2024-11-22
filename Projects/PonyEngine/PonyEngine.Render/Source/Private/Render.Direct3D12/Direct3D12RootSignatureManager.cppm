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
import <unordered_map>;

import PonyEngine.Render.Detail;

import :Direct3D12RootSignature;
import :Direct3D12RootSignatureHandle;
import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	class Direct3D12RootSignatureManager final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignatureManager(IRenderContext& render, ID3D12Device10& device) noexcept;
		Direct3D12RootSignatureManager(const Direct3D12RootSignatureManager&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignatureManager(Direct3D12RootSignatureManager&& other) noexcept = default;

		~Direct3D12RootSignatureManager() noexcept = default;

		Direct3D12RootSignatureHandle CreateRootSignature(const Direct3D12Shader& rootSignatureShader, UINT mvpIndex);
		void DestroyRootSignature(Direct3D12RootSignatureHandle handle) noexcept;

		[[nodiscard("Pure function")]]
		Direct3D12RootSignature* FindRootSignature(Direct3D12RootSignatureHandle handle) const noexcept;

		Direct3D12RootSignatureManager& operator =(const Direct3D12RootSignatureManager&) = delete;
		Direct3D12RootSignatureManager& operator =(Direct3D12RootSignatureManager&& other) noexcept = default;

	private:
		IRenderContext* render;

		Microsoft::WRL::ComPtr<ID3D12Device10> device;

		mutable std::unordered_map<Direct3D12RootSignatureHandle, Direct3D12RootSignature, Direct3D12RootSignatureHandleHash> rootSignatures; // TODO: It should not be mutable. So, maybe it should create RenderObjects in heap and use unique_ptr here.
		std::size_t nextId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RootSignatureManager::Direct3D12RootSignatureManager(IRenderContext& render, ID3D12Device10& device) noexcept :
		render{&render},
		device(&device),
		nextId{1}
	{
	}

	Direct3D12RootSignatureHandle Direct3D12RootSignatureManager::CreateRootSignature(const Direct3D12Shader& rootSignatureShader, const UINT mvpIndex)
	{
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		if (const HRESULT result = device->CreateRootSignature(0, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto handle = Direct3D12RootSignatureHandle{.id = nextId++};
		rootSignatures.try_emplace(handle, *rootSignature.Get(), mvpIndex);

		return handle;
	}

	void Direct3D12RootSignatureManager::DestroyRootSignature(const Direct3D12RootSignatureHandle handle) noexcept
	{
		if (const auto position = rootSignatures.find(handle); position != rootSignatures.cend())
		{
			rootSignatures.erase(position);
		}
	}

	Direct3D12RootSignature* Direct3D12RootSignatureManager::FindRootSignature(Direct3D12RootSignatureHandle handle) const noexcept
	{
		if (const auto position = rootSignatures.find(handle); position != rootSignatures.cend())
		{
			return &position->second;
		}

		return nullptr;
	}
}
