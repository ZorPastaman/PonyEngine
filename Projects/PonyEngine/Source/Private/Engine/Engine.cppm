/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine;

import <cstddef>;

import PonyEngine.IEngine;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine main class.
	/// </summary>
	export class Engine final : public IEngine
	{
	public:
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		virtual ~Engine() = default;

		virtual size_t GetFrameCount() const override;

		virtual void Tick() override;

	private:
		size_t m_frameCount;
	};

	Engine::Engine() :
		m_frameCount(0)
	{
	}

	size_t Engine::GetFrameCount() const
	{
		return m_frameCount;
	}

	void Engine::Tick()
	{
		++m_frameCount;
	}
}
