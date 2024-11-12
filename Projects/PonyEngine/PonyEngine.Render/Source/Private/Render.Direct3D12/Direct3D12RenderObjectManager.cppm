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

export module PonyEngine.Render.Direct3D12.Implementation:Direct3D12RenderObjectManager;

import <cstddef>;
import <stdexcept>;
import <unordered_map>;
import <utility>;

import PonyMath.Core;

import PonyDebug.Log;

import PonyEngine.Render;
import PonyEngine.Render.Core;

import :Direct3D12Mesh;
import :Direct3D12MeshManager;
import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObjectManager final : public IRenderObjectManager
	{
	public:
		using RenderObjectIterator = std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash>::const_iterator;

		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObjectManager(IRenderer& renderer, Direct3D12MeshManager& meshManager, ID3D12Device10* device) noexcept;
		Direct3D12RenderObjectManager(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager(Direct3D12RenderObjectManager&&) = delete;

		~Direct3D12RenderObjectManager() noexcept = default;

		virtual RenderObjectHandle CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) override;
		virtual void DestroyObject(RenderObjectHandle handle) noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRenderObject* FindRenderObject(RenderObjectHandle handle) noexcept override;

		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectBegin() const noexcept;
		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectEnd() const noexcept;

		Direct3D12RenderObjectManager& operator =(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager& operator =(Direct3D12RenderObjectManager&&) = delete;

	private:
		IRenderer* renderer;

		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		Direct3D12MeshManager* meshManager;

		std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash> renderObjects;
		std::size_t nextRenderObjectId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObjectManager::Direct3D12RenderObjectManager(IRenderer& renderer, Direct3D12MeshManager& meshManager, ID3D12Device10* const device) noexcept :
		renderer{&renderer},
		device(device),
		meshManager{&meshManager},
		nextRenderObjectId{1}
	{
	}

	RenderObjectHandle Direct3D12RenderObjectManager::CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix)
	{
		const auto handle = RenderObjectHandle{.id = nextRenderObjectId++};
		if (const auto result = renderObjects.try_emplace(handle, meshManager->CreateDirect3D12Mesh(mesh), static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(modelMatrix)); !result.second) [[unlikely]]
		{
			throw std::runtime_error("Failed to create a render object.");
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render object created with '{}' id.", handle.id);

		return handle;
	}

	void Direct3D12RenderObjectManager::DestroyObject(const RenderObjectHandle handle) noexcept
	{
		if (const auto position = renderObjects.find(handle); position != renderObjects.cend()) [[likely]]
		{
			renderObjects.erase(position);
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render object with '{}' id destroyed.", handle.id);
		}
		else [[unlikely]]
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Warning, "Tried to destroy a non-existing render object. ID: '{}'.", handle.id);
		}
	}

	IRenderObject* Direct3D12RenderObjectManager::FindRenderObject(const RenderObjectHandle handle) noexcept
	{
		if (const auto position = renderObjects.find(handle); position != renderObjects.cend()) [[likely]]
		{
			return &position->second;
		}

		return nullptr;
	}

	Direct3D12RenderObjectManager::RenderObjectIterator Direct3D12RenderObjectManager::RenderObjectBegin() const noexcept
	{
		return renderObjects.cbegin();
	}

	Direct3D12RenderObjectManager::RenderObjectIterator Direct3D12RenderObjectManager::RenderObjectEnd() const noexcept
	{
		return renderObjects.cend();
	}
}
