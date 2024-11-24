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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderObjectManager;

import <cstddef>;
import <memory>;
import <span>;
import <stdexcept>;
import <utility>;
import <vector>;

import PonyMath.Core;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;
import PonyEngine.Render.Detail;

import :Direct3D12Material;
import :Direct3D12MaterialManager;
import :Direct3D12Mesh;
import :Direct3D12MeshManager;
import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObjectManager final : public IDirect3D12RenderObjectManager
	{
	public:

		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObjectManager(IRenderSystemContext& renderer, Direct3D12RootSignatureManager* rootSignatureManager, Direct3D12MaterialManager& materialManager, Direct3D12MeshManager& meshManager, ID3D12Device10* device) noexcept;
		Direct3D12RenderObjectManager(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager(Direct3D12RenderObjectManager&&) = delete;

		~Direct3D12RenderObjectManager() noexcept = default;

		virtual std::shared_ptr<IRenderObject> CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) override;
		virtual std::shared_ptr<IDirect3D12RenderObject> CreateObjectD3D12(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix) override;

		std::span<const std::weak_ptr<Direct3D12RenderObject>> RenderObjects() noexcept;

		Direct3D12RenderObjectManager& operator =(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager& operator =(Direct3D12RenderObjectManager&&) = delete;

	private:
		IRenderSystemContext* renderer;

		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		Direct3D12RootSignatureManager* rootSignatureManager;
		Direct3D12MaterialManager* materialManager;
		Direct3D12MeshManager* meshManager;

		std::vector<std::weak_ptr<Direct3D12RenderObject>> renderObjects;

		std::shared_ptr<Direct3D12Material> defaultMaterial;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObjectManager::Direct3D12RenderObjectManager(IRenderSystemContext& renderer, Direct3D12RootSignatureManager* rootSignatureManager, Direct3D12MaterialManager& materialManager, Direct3D12MeshManager& meshManager, ID3D12Device10* const device) noexcept :
		renderer{&renderer},
		device(device),
		rootSignatureManager{rootSignatureManager},
		materialManager{&materialManager},
		meshManager{&meshManager}
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 root signature shader.");
		const auto rootSignatureHandle = rootSignatureManager->CreateRootSignature(Direct3D12Shader("RootSignature"), 0u);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 root signature shader loaded.");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 vertex shader.");
		const auto vertexShader = Direct3D12Shader("VertexShader");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 vertex shader loaded.");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 pixel shader.");
		const auto pixelShader = Direct3D12Shader("PixelShader");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 pixel shader loaded.");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 material.");
		defaultMaterial = materialManager.CreateMaterial(rootSignatureHandle, vertexShader, pixelShader);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material created.");
	}

	std::shared_ptr<IRenderObject> Direct3D12RenderObjectManager::CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix)
	{
		return std::static_pointer_cast<IRenderObject>(CreateObjectD3D12(mesh, static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(modelMatrix)));
	}

	std::shared_ptr<IDirect3D12RenderObject> Direct3D12RenderObjectManager::CreateObjectD3D12(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix)
	{
		auto renderObject = std::make_shared<Direct3D12RenderObject>(defaultMaterial, meshManager->CreateDirect3D12Mesh(mesh), static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(modelMatrix));
		renderObjects.push_back(renderObject);

		return renderObject;
	}

	std::span<const std::weak_ptr<Direct3D12RenderObject>> Direct3D12RenderObjectManager::RenderObjects() noexcept
	{
		for (std::size_t i = renderObjects.size(); i-- > 0; )
		{
			if (renderObjects[i].expired())
			{
				renderObjects.erase(renderObjects.begin() + i);
			}
		}

		return renderObjects;
	}
}
