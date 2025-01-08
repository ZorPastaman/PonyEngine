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

export module PonyEngine.Render.Direct3D12.Detail:RenderObjectManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <vector>;

import PonyMath.Core;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :IGraphicsPipeline;
import :IRenderObjectManagerPrivate;
import :ISubSystemContext;
import :Material;
import :RenderObject;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render object manager.
	class Direct3D12RenderObjectManager final : public IRenderObjectManagerPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12RenderObjectManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObjectManager(ISubSystemContext& d3d12System) noexcept;
		Direct3D12RenderObjectManager(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager(Direct3D12RenderObjectManager&&) = delete;

		~Direct3D12RenderObjectManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Render::IRenderObject> CreateObject(const std::shared_ptr<const Render::Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) override;
		/// @brief Creates a render object.
		/// @param mesh Render object mesh.
		/// @param modelMatrix Render object translation-rotation-scaling matrix.
		/// @return Render object handle.
		[[nodiscard("Redundant call")]]
		std::shared_ptr<IRenderObject> CreateObjectD3D12(const std::shared_ptr<const Render::Mesh>& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix = PonyMath::Core::Matrix4x4<FLOAT>::Predefined::Identity);

		void AddRenderTasks();

		/// @brief Cleans out of dead render objects.
		void Clean() noexcept;

		Direct3D12RenderObjectManager& operator =(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager& operator =(Direct3D12RenderObjectManager&&) = delete;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<RenderObject>> renderObjects; ///< Render objects.

		// TODO: There should not be a default material. The user must create their own materials.
		std::shared_ptr<Material> defaultMaterial; ///< Default material.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Direct3D12RenderObjectManager::Direct3D12RenderObjectManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
		// TODO: Add ShaderManager. But seems that there's no need of exactly ShaderManager for d3d12. I just need a ShaderResource in a ResourceSystem.
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create default material.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Load root signature shader.");
		const std::unordered_map<std::string, UINT> dataSlots =
		{
			{ "Meshlets", 1u },
			{ "Positions", 2u },
			{ "Colors", 3u }
		};
		const auto rootSignature = this->d3d12System->RootSignatureManagerPrivate().CreateRootSignature(Shader("RootSig"), dataSlots, 0u);
		rootSignature->Name("DefaultRootSignature");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Root signature shader loaded.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Load mesh shader.");
		const auto meshShader = Shader("MeshShader");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh shader loaded.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Load pixel shader.");
		const auto pixelShader = Shader("PixelShader");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Pixel shader loaded.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create material.");
		defaultMaterial = this->d3d12System->MaterialManagerPrivate().CreateMaterial(rootSignature, meshShader, pixelShader);
		defaultMaterial->Name("DefaultMaterial");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material created.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Default material created.");
	}

	std::shared_ptr<Render::IRenderObject> Direct3D12RenderObjectManager::CreateObject(const std::shared_ptr<const Render::Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix)
	{
		return std::static_pointer_cast<IRenderObject>(CreateObjectD3D12(mesh, static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(modelMatrix)));
	}

	std::shared_ptr<IRenderObject> Direct3D12RenderObjectManager::CreateObjectD3D12(const std::shared_ptr<const Render::Mesh>& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix)
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create render mesh.");
		const std::shared_ptr<Mesh> renderMesh = d3d12System->MeshManagerPrivate().CreateDirect3D12Mesh(mesh);
		renderMesh->Name("Mesh");
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render mesh created");
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create render object.");
		auto renderObject = std::make_shared<RenderObject>(defaultMaterial, renderMesh, static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(modelMatrix));
		renderObjects.push_back(renderObject);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render object created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderObject.get()));

		return renderObject;
	}

	void Direct3D12RenderObjectManager::AddRenderTasks()
	{
		IGraphicsPipeline& graphicsPipeline = d3d12System->GraphicsPipeline();
		for (const std::shared_ptr<RenderObject>& renderObject : renderObjects)
		{
			graphicsPipeline.AddRenderTask(renderObject);
		}
	}

	void Direct3D12RenderObjectManager::Clean() noexcept
	{
		for (std::size_t i = renderObjects.size(); i-- > 0; )
		{
			if (renderObjects[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy render object at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderObjects[i].get()));
				renderObjects.erase(renderObjects.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render object destroyed.");
			}
		}
	}
}
