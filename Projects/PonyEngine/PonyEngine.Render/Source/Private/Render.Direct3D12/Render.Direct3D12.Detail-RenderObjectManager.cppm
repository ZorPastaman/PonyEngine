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
import :ISubSystemContext;
import :Material;
import :RenderObject;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Render object manager.
	class RenderObjectManager final : public IRenderObjectManager
	{
	public:
		/// @brief Creates a @p RenderObjectManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit RenderObjectManager(ISubSystemContext& d3d12System) noexcept;
		RenderObjectManager(const RenderObjectManager&) = delete;
		RenderObjectManager(RenderObjectManager&&) = delete;

		~RenderObjectManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRenderObject> CreateObject(const RenderObjectParams& params) override;

		void Tick();

		/// @brief Cleans out of dead render objects.
		void Clean() noexcept;

		RenderObjectManager& operator =(const RenderObjectManager&) = delete;
		RenderObjectManager& operator =(RenderObjectManager&&) = delete;
		

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<RenderObject>> renderObjects; ///< Render objects.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RenderObjectManager::RenderObjectManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Render::IRenderObject> RenderObjectManager::CreateObject(const RenderObjectParams& params)
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create render material.");
		const std::shared_ptr<Material> renderMaterial = d3d12System->MaterialManager().CreateMaterial(params.material);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render material created");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create render mesh.");
		const std::shared_ptr<Mesh> renderMesh = params.mesh ? d3d12System->MeshManager().CreateMesh(params.mesh) : nullptr;
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render mesh created");

		const auto renderObject = std::make_shared<RenderObject>(renderMaterial, renderMesh, params.modelMatrix);
		renderObject->Name(params.name);
		renderObjects.push_back(renderObject);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render object created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderObject.get()));

		return renderObject;
	}

	void RenderObjectManager::Tick()
	{
		for (const std::shared_ptr<RenderObject>& renderObject : renderObjects)
		{
			d3d12System->GraphicsPipeline().AddRenderObject(*renderObject);
		}
	}

	void RenderObjectManager::Clean() noexcept
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
