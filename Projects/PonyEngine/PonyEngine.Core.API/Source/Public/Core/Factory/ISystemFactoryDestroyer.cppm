/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:ISystemFactoryDestroyer;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief System factory destroyer.
	class ISystemFactoryDestroyer
	{
	public:
		ISystemFactoryDestroyer(const ISystemFactoryDestroyer&) = delete;
		ISystemFactoryDestroyer(ISystemFactoryDestroyer&&) = delete;

		/// @brief Checks the system factory compatibility.
		/// @param factory System factory.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(ISystemFactory* factory) const noexcept = 0;

		/// @brief Destroys the @p factory.
		/// @param factory System factory to destroy.
		virtual void Destroy(ISystemFactory* factory) noexcept = 0;

		ISystemFactoryDestroyer& operator =(const ISystemFactoryDestroyer&) = delete;
		ISystemFactoryDestroyer& operator =(ISystemFactoryDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemFactoryDestroyer() noexcept = default;

		~ISystemFactoryDestroyer() noexcept = default;
	};
}
