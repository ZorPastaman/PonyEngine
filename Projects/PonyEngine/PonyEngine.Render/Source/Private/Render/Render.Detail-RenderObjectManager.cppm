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

export module PonyEngine.Render.Detail:RenderObjectManager;

import <cstddef>;
import <memory>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Render object manager.
	class RenderObjectManager final : public IRenderObjectManager
	{
	public:
		/// @brief Creates a render object manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit RenderObjectManager(IRenderSystemContext& renderSystem) noexcept;
		RenderObjectManager(const RenderObjectManager&) = delete;
		RenderObjectManager(RenderObjectManager&&) = delete;

		~RenderObjectManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRenderObject> CreateObject(const RenderObjectParams& params) override;

		/// @brief Ticks the render object manager.
		void Tick();
		/// @brief Cleans out dead render objects.
		void Clean() noexcept;

		RenderObjectManager& operator =(const RenderObjectManager&) = delete;
		RenderObjectManager& operator =(RenderObjectManager&&) = delete;

	private:
		/// @brief Submits render objects to a pipeline.
		void Submit();

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<RenderObject>> renderObjects; ///< Render objects.
	};
}

namespace PonyEngine::Render
{
	RenderObjectManager::RenderObjectManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IRenderObject> RenderObjectManager::CreateObject(const RenderObjectParams& params)
	{
		if (params.material == nullptr)
		{
			throw std::runtime_error{ "Material is nullptr." };
		}

		auto renderObject = std::make_shared<RenderObject>(params);
		renderObjects.push_back(renderObject);

		return renderObject;
	}

	void RenderObjectManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Submit.");
		Submit();
	}

	void RenderObjectManager::Clean() noexcept
	{
		for (std::size_t i = renderObjects.size(); i-- > 0; )
		{
			if (renderObjects[i].use_count() <= 1L)
			{
				renderObjects.erase(renderObjects.cbegin() + i);
			}
		}
	}

	void RenderObjectManager::Submit()
	{
		for (const std::shared_ptr<RenderObject>& renderObject : renderObjects)
		{
			renderSystem->Pipeline().Submit(*renderObject);
		}
	}
}
