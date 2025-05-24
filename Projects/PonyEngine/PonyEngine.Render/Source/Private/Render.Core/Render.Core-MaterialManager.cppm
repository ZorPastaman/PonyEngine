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

export module PonyEngine.Render.Core:MaterialManager;

import <cstddef>;
import <memory>;
import <stdexcept>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :Material;
import :PipelineState;

export namespace PonyEngine::Render
{
	/// @brief Material manager.
	class MaterialManager final : public IMaterialManager
	{
	public:
		/// @brief Creates a material manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit MaterialManager(IRenderSystemContext& renderSystem) noexcept;
		MaterialManager(const MaterialManager&) = delete;
		MaterialManager(MaterialManager&&) = delete;

		~MaterialManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IMaterial> CreateMaterial(const MaterialParams& params) override;

		/// @brief Ticks the mesh manager.
		void Tick();
		/// @brief Cleans out dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		/// @brief Creates new materials on GPU.
		void Create();
		/// @brief Updates living materials.
		void Update();
		/// @brief Clears dirty flags and caches.
		void Clear() noexcept;

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.
		std::vector<const Material*> newMaterials; ///< New materials.
	};
}

namespace PonyEngine::Render
{
	MaterialManager::MaterialManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IMaterial> MaterialManager::CreateMaterial(const MaterialParams& params)
	{
		if (!params.pipelineState) [[unlikely]]
		{
			throw std::invalid_argument("Pipeline state is nullptr.");
		}
		assert(dynamic_cast<const PipelineState*>(params.pipelineState.get()) && "The pipeline state is not a valid type.");
		if (std::ranges::find_if(params.data, [](const auto& p) { return p.first.starts_with(DataTypes::Prefix); }) != params.data.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid data type name.");
		}
		if (std::ranges::find_if(params.textures, [](const auto& p) { return p.first.starts_with(DataTypes::Prefix); }) != params.textures.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture type name.");
		}

		const auto material = std::make_shared<Material>(params);
		materials.push_back(material);

		return material;
	}

	void MaterialManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
	}

	void MaterialManager::Clean() noexcept
	{
		for (std::size_t i = materials.size(); i-- > 0; )
		{
			if (materials[i].use_count() <= 1L)
			{
				materials.erase(materials.cbegin() + i);
			}
		}
	}

	void MaterialManager::Create()
	{
		for (const Material* material : newMaterials)
		{
			renderSystem->RenderAgent().BufferAgent().Create(material->Buffer());
		}
	}

	void MaterialManager::Update()
	{
		for (const std::shared_ptr<Material>& material : materials)
		{
			if (material->DirtyFlags() != BufferDirtyFlag::None)
			{
				renderSystem->RenderAgent().BufferAgent().Update(material->Buffer(), material->DirtyFlags());
			}
		}
	}

	void MaterialManager::Clear() noexcept
	{
		for (const std::shared_ptr<Material>& material : materials)
		{
			material->ResetDirty();
		}

		newMaterials.clear();
	}
}
