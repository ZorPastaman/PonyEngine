/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:EngineUniquePtr;

import <memory>;

import :IEngineDestroyer;

export namespace PonyEngine::Core
{
	/// @brief Engine deleter.
	class EngineDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		EngineDeleter() noexcept = default;
		/// @brief Creates an @p EngineDeleter.
		/// @param engineDestroyer Engine destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit EngineDeleter(IEngineDestroyer& engineDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		EngineDeleter(const EngineDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		EngineDeleter(EngineDeleter&& other) noexcept = default;

		~EngineDeleter() noexcept = default;

		/// @brief Gets the engine destroyer.
		/// @return Engine destroyer.
		[[nodiscard("Pure function")]]
		IEngineDestroyer* EngineDestroyer() const noexcept;

		/// @brief Deletes the @p engine.
		/// @param engine Engine to delete.
		void operator ()(IEngine* engine) const noexcept;

		EngineDeleter& operator =(const EngineDeleter& other) noexcept = default;
		EngineDeleter& operator =(EngineDeleter&& other) noexcept = default;

	private:
		IEngineDestroyer* engineDestroyer; ///< Engine destroyer.
	};

	using EngineUniquePtr = std::unique_ptr<IEngine, EngineDeleter>; ///< Engine unique_ptr typedef.
}

namespace PonyEngine::Core
{
	EngineDeleter::EngineDeleter(IEngineDestroyer& engineDestroyer) noexcept :
		engineDestroyer{&engineDestroyer}
	{
	}

	IEngineDestroyer* EngineDeleter::EngineDestroyer() const noexcept
	{
		return engineDestroyer;
	}

	void EngineDeleter::operator ()(IEngine* const engine) const noexcept
	{
		if (engineDestroyer)
		{
			engineDestroyer->Destroy(engine);
		}
	}
}
