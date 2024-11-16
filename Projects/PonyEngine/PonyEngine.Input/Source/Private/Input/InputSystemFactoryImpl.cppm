/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Detail:InputSystemFactoryImpl;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyEngine.Core;
import PonyEngine.Input;

import :InputSystem;

export namespace PonyEngine::Input
{
	/// @brief Input system factory.
	class InputSystemFactoryImpl final : public InputSystemFactory
	{
	public:
		/// @brief Creates an @p InputSystemFactory.
		/// @param application Application context.
		/// @param factoryParams Input system factory parameters.
		/// @param systemParams Input system parameters.
		InputSystemFactoryImpl(Core::IApplicationContext& application, const InputSystemFactoryParams& factoryParams, const InputSystemParams& systemParams) noexcept;
		InputSystemFactoryImpl(const InputSystemFactoryImpl&) = delete;
		InputSystemFactoryImpl(InputSystemFactoryImpl&&) = delete;

		virtual ~InputSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		InputSystemFactoryImpl& operator =(const InputSystemFactoryImpl&) = delete;
		InputSystemFactoryImpl& operator =(InputSystemFactoryImpl&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Input::InputSystemFactory"; ///< Class name.

	private:
		InputSystemParams inputSystemParams; ///< Input system parameters.

		Core::IApplicationContext* application; ///< Application.
	};
}

namespace PonyEngine::Input
{
	InputSystemFactoryImpl::InputSystemFactoryImpl(Core::IApplicationContext& application, const InputSystemFactoryParams&, const InputSystemParams& systemParams) noexcept :
		inputSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData InputSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		auto system = std::make_unique<InputSystem>(engine, params, inputSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IInputSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view InputSystemFactoryImpl::SystemName() const noexcept
	{
		return InputSystem::StaticName;
	}

	std::string_view InputSystemFactoryImpl::Name() const noexcept
	{
		return StaticName;
	}
}
