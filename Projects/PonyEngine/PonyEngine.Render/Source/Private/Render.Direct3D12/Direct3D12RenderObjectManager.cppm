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

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObjectManager;

import <cstddef>;
import <unordered_map>;

import PonyEngine.Render;

import :Direct3D12Mesh;
import :Direct3D12MeshHelper;
import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObjectManager final
	{
	public:
		using RenderObjectIterator = std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash>::const_iterator;

		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObjectManager(ID3D12Device10* device) noexcept;
		Direct3D12RenderObjectManager(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager(Direct3D12RenderObjectManager&&) = delete;

		~Direct3D12RenderObjectManager() noexcept = default;

		[[nodiscard("Pure function")]]
		RenderObjectHandle CreateRenderObject(const PonyBase::Geometry::Mesh& mesh);
		void DestroyRenderObject(RenderObjectHandle renderObjectHandle) noexcept;

		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectBegin() const noexcept;
		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectEnd() const noexcept;

		Direct3D12RenderObjectManager& operator =(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager& operator =(Direct3D12RenderObjectManager&&) = delete;

	private:
		Microsoft::WRL::ComPtr<ID3D12Device10> device;

		std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash> renderObjects;
		std::size_t nextRenderObjectId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObjectManager::Direct3D12RenderObjectManager(ID3D12Device10* const device) noexcept :
		device(device),
		nextRenderObjectId{1}
	{
	}

	RenderObjectHandle Direct3D12RenderObjectManager::CreateRenderObject(const PonyBase::Geometry::Mesh& mesh)
	{
		const size_t id = nextRenderObjectId++;
		const auto renderMesh = CreateDirect3D12Mesh(device.Get(), mesh);
		renderObjects.emplace(id, renderMesh);

		return RenderObjectHandle{.id = id};
	}

	void Direct3D12RenderObjectManager::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) noexcept
	{
		if (const auto position = renderObjects.find(renderObjectHandle); position != renderObjects.cend()) [[likely]]
		{
			renderObjects.erase(position);
		}
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
