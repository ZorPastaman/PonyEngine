/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:MaterialManager;

import <cstddef>;
import <memory>;
import <stdexcept>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :Material;

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

		/// @brief Cleans out dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.
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

		const auto material = std::make_shared<Material>(params);
		materials.push_back(material);

		return material;
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
}
