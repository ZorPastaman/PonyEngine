/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:MeshManager;

import <algorithm>;
import <cstddef>;
import <memory>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IMeshAgent;
import :IRenderSystemContext;
import :Mesh;
import :MeshDirtyState;

export namespace PonyEngine::Render
{
	/// @brief Mesh manager.
	class MeshManager final : public IMeshManager
	{
	public:
		/// @brief Creates a mesh manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit MeshManager(IRenderSystemContext& renderSystem) noexcept;
		MeshManager(const MeshManager&) = delete;
		MeshManager(MeshManager&&) = delete;

		~MeshManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IMesh> CreateMesh(const MeshParams& params) override;

		/// @brief Tick the mesh manager.
		void Tick();

		MeshManager& operator =(const MeshManager&) = delete;
		MeshManager& operator =(MeshManager&&) = delete;

	private:
		/// @brief Creates new meshes on GPU.
		void Create();
		/// @brief Destroys expired meshes on both CPU and GPU.
		void Destroy();
		/// @brief Updates living meshes.
		void Update();
		/// @brief Clears dirty flags and caches.
		void Clear();

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<const Mesh*> newMeshes; ///< Meshes created this frame.
	};
}

namespace PonyEngine::Render
{
	MeshManager::MeshManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IMesh> MeshManager::CreateMesh(const MeshParams& params)
	{
		const auto mesh = std::make_shared<Mesh>(params);
		meshes.push_back(mesh);
		newMeshes.push_back(mesh.get());

		return mesh;
	}

	void MeshManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Destroy.");
		Destroy();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
	}

	void MeshManager::Create()
	{
		for (const Mesh* mesh : newMeshes)
		{
			renderSystem->RenderAgent().MeshAgent().Create(*mesh);
		}
	}

	void MeshManager::Destroy()
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			const std::shared_ptr<Mesh>& mesh = meshes[i];
			if (mesh.use_count() > 1L)
			{
				continue;
			}

			if (const auto position = std::ranges::find(newMeshes, mesh.get()); position != newMeshes.cend())
			{
				newMeshes.erase(position);
			}
			else
			{
				renderSystem->RenderAgent().MeshAgent().Destroy(*mesh);
			}
			meshes.erase(meshes.cbegin() + i);
		}
	}

	void MeshManager::Update()
	{
		for (const std::shared_ptr<Mesh>& mesh : meshes)
		{
			if (const MeshDirtyState& dirtyState = mesh->DirtyState(); dirtyState.dirtyData.size() > 0 || dirtyState.dirtyFlags != MeshDirtyFlag::None)
			{
				renderSystem->RenderAgent().MeshAgent().Update(*mesh);
			}
		}
	}

	void MeshManager::Clear()
	{
		for (const std::shared_ptr<Mesh>& mesh : meshes)
		{
			mesh->ResetDirtyState();
		}

		newMeshes.clear();
	}
}
