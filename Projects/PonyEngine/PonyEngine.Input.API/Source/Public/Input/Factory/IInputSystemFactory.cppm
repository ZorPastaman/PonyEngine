/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Factory:IInputSystemFactory;

import PonyEngine.Core.Factory;

import :InputSystemParams;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class IInputSystemFactory : public Core::ISystemFactory
	{
	public:
		IInputSystemFactory(const IInputSystemFactory&) = delete;
		IInputSystemFactory(IInputSystemFactory&&) = delete;

		/// @brief Gets system parameters.
		/// @return System parameters.
		[[nodiscard("Pure function")]]
		virtual InputSystemParams& SystemParams() noexcept = 0;
		/// @brief Gets system parameters.
		/// @return System parameters.
		[[nodiscard("Pure function")]]
		virtual const InputSystemParams& SystemParams() const noexcept = 0;

		IInputSystemFactory& operator =(const IInputSystemFactory&) = delete;
		IInputSystemFactory& operator =(IInputSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IInputSystemFactory() noexcept = default;

		~IInputSystemFactory() noexcept = default;
	};
}
