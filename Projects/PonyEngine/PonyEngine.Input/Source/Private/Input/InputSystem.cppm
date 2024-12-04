/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <ranges>

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Input.Detail:InputSystem;

import <algorithm>;
import <functional>;
import <memory>;
import <span>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class InputSystem final : public Core::TickableSystem, public IInputSystem, private IInputSystemContext
	{
	public:
		/// @brief Creates an input system
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param inputParams Input system parameters.
		[[nodiscard("Pure constructor")]]
		InputSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const InputSystemParams& inputParams) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		virtual ~InputSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(bool)>& action) override;
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(float)>& action) override;

		[[nodiscard("Pure function")]]
		virtual Core::ISystemManager& SystemManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Core::ISystemManager& SystemManager() const noexcept override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

	private:
		struct InputMappingEntryInfo final
		{
			std::string id;
			float multiplier;
		};

		struct BoolBinding final
		{
			std::shared_ptr<InputHandle> handle;
			std::function<void(bool)> function;
		};
		struct FloatBinding final
		{
			std::shared_ptr<InputHandle> handle;
			std::function<void(float)> function;
		};

		std::vector<std::unique_ptr<InputDevice>> devices;
		std::unordered_map<InputCode, std::vector<InputMappingEntryInfo>> inputMapping;

		std::unordered_map<std::string, std::vector<BoolBinding>> boolBindings;
		std::unordered_map<std::string, std::vector<FloatBinding>> floatBindings;
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const InputSystemParams& inputParams) noexcept :
		TickableSystem(engine, systemParams)
	{
		for (IInputDeviceFactory* const deviceFactory : inputParams.inputDeviceFactories)
		{
			devices.push_back(deviceFactory->CreateDevice(*static_cast<IInputSystemContext*>(this)));
		}

		for (const auto& [id, inputBindingEntries] : inputParams.inputBindings)
		{
			for (const InputBindingEntry& bindingEntry : inputBindingEntries)
			{
				inputMapping[bindingEntry.inputCode].push_back(InputMappingEntryInfo{.id = std::string(id), .multiplier = bindingEntry.multiplier});
			}
		}
	}

	InputSystem::~InputSystem() noexcept
	{
		for (auto it = devices.rbegin(); it != devices.rend(); ++it)
		{
			it->reset();
		}
	}

	void InputSystem::Begin()
	{
		for (const std::unique_ptr<InputDevice>& device : devices)
		{
			device->Begin();
		}
	}

	void InputSystem::End()
	{
		for (auto it = devices.crbegin(); it != devices.crend(); ++it)
		{
			try
			{
				(*it)->End();
			}
			catch (const std::exception& e)
			{
				
			}
		}
	}

	void InputSystem::Tick()
	{
		for (std::vector<BoolBinding>& binding : std::ranges::views::values(boolBindings))
		{
			for (std::size_t i = binding.size(); i-- > 0; )
			{
				if (binding[i].handle.use_count() <= 1)
				{
					binding.erase(binding.cbegin() + i);
				}
			}
		}
		for (std::vector<FloatBinding>& binding : std::ranges::views::values(floatBindings))
		{
			for (std::size_t i = binding.size(); i-- > 0; )
			{
				if (binding[i].handle.use_count() <= 1)
				{
					binding.erase(binding.cbegin() + i);
				}
			}
		}

		for (const std::unique_ptr<InputDevice>& device : devices)
		{
			device->Tick();
		}

		for (const std::unique_ptr<InputDevice>& device : devices)
		{
			for (const InputEntry& inputEntry : device->GetInputs())
			{
				if (const auto& mappingPosition = inputMapping.find(inputEntry.inputCode); mappingPosition != inputMapping.cend())
				{
					for (const InputMappingEntryInfo& inputMappingEntryInfo : mappingPosition->second)
					{
						if (const auto& boolBinding = boolBindings.find(inputMappingEntryInfo.id); boolBinding != boolBindings.cend())
						{
							const bool value = inputEntry.value;
							for (const BoolBinding& binding : boolBinding->second)
							{
								binding.function(value);
							}
						}

						if (const auto& floatBinding = floatBindings.find(inputMappingEntryInfo.id); floatBinding != floatBindings.cend())
						{
							for (const FloatBinding& binding : floatBinding->second)
							{
								binding.function(inputEntry.value * inputMappingEntryInfo.multiplier);
							}
						}
					}
				}
			}
		}
	}

	std::shared_ptr<InputHandle> InputSystem::Bind(const std::string_view id, const std::function<void(bool)>& action)
	{
		const auto handle = std::make_shared<InputHandle>();
		boolBindings[std::string(id)].push_back(BoolBinding{.handle = handle, .function = action});

		return handle;
	}

	std::shared_ptr<InputHandle> InputSystem::Bind(const std::string_view id, const std::function<void(float)>& action)
	{
		const auto handle = std::make_shared<InputHandle>();
		floatBindings[std::string(id)].push_back(FloatBinding{.handle = handle, .function = action});

		return handle;
	}

	Core::ISystemManager& InputSystem::SystemManager() noexcept
	{
		return Engine().SystemManager();
	}

	const Core::ISystemManager& InputSystem::SystemManager() const noexcept
	{
		return Engine().SystemManager();
	}
}
