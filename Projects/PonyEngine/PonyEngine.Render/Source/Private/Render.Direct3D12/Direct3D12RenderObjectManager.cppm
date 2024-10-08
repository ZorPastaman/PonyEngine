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

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObjectManager;

import <cstddef>;
import <unordered_map>;

import PonyDebug.Log;

import PonyEngine.Render;

import PonyEngine.Render.Core;

import :Direct3D12Mesh;
import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObjectManager final
	{
	public:
		using RenderObjectIterator = std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash>::const_iterator;

		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObjectManager(IRenderer& renderer, ID3D12Device10* device) noexcept;
		Direct3D12RenderObjectManager(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager(Direct3D12RenderObjectManager&&) = delete;

		~Direct3D12RenderObjectManager() noexcept = default;

		[[nodiscard("Pure function")]]
		RenderObjectHandle CreateRenderObject(const Direct3D12Mesh& mesh);
		void DestroyRenderObject(RenderObjectHandle renderObjectHandle) noexcept;

		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectBegin() const noexcept;
		[[nodiscard("Pure function")]]
		RenderObjectIterator RenderObjectEnd() const noexcept;

		Direct3D12RenderObjectManager& operator =(const Direct3D12RenderObjectManager&) = delete;
		Direct3D12RenderObjectManager& operator =(Direct3D12RenderObjectManager&&) = delete;

	private:
		IRenderer* renderer;

		Microsoft::WRL::ComPtr<ID3D12Device10> device;

		std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash> renderObjects;
		std::size_t nextRenderObjectId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObjectManager::Direct3D12RenderObjectManager(IRenderer& renderer, ID3D12Device10* const device) noexcept :
		renderer{&renderer},
		device(device),
		nextRenderObjectId{1}
	{
	}

	RenderObjectHandle Direct3D12RenderObjectManager::CreateRenderObject(const Direct3D12Mesh& mesh)
	{
		const size_t id = nextRenderObjectId++;
		renderObjects.emplace(id, mesh);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Debug, "Render object created with '{}' id.", id);

		return RenderObjectHandle{.id = id};
	}

	void Direct3D12RenderObjectManager::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) noexcept
	{
		if (const auto position = renderObjects.find(renderObjectHandle); position != renderObjects.cend()) [[likely]]
		{
			renderObjects.erase(position);
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Debug, "Render object with '{}' id destroyed.", renderObjectHandle.id);
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
