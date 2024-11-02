/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:ISystemFactory;

import <string_view>;

import PonyEngine.Core;

import :SystemData;
import :EngineSystemParams;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief System factory.
	class ISystemFactory
	{
	public:
		ISystemFactory(const ISystemFactory&) = delete;
		ISystemFactory(ISystemFactory&&) = delete;

		/// @brief Creates a system.
		///	@param engine Engine context.
		/// @param params Engine system parameters.
		/// @return Created system.
		[[nodiscard("Pure function")]]
		virtual SystemData Create(IEngineContext& engine, const EngineSystemParams& params) = 0;

		/// @brief Gets the system parameters.
		/// @return System parameters.
		[[nodiscard("Pure function")]]
		virtual SystemParams& SystemParams() noexcept = 0;
		/// @brief Gets the system parameters.
		/// @return System parameters.
		[[nodiscard("Pure function")]]
		virtual const Core::SystemParams& SystemParams() const noexcept = 0;

		/// @brief Gets the system static name.
		/// @return System static name.
		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept = 0;

		/// @brief Gets the system factory name.
		/// @return System factory name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		ISystemFactory& operator =(const ISystemFactory&) = delete;
		ISystemFactory& operator =(ISystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure function")]]
		ISystemFactory() noexcept = default;

		~ISystemFactory() noexcept = default;
	};
}
