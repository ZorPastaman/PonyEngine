/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.World.Impl:CopyComponentDeserializer;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Resource.World.Ext;

import :WorldDefinitionLoader;

export namespace PonyEngine::Resource::World
{
	/// @brief Component deserializer that simply copies input bytes to output bytes as is.
	class CopyComponentDeserializer final : public ICopyComponentDeserializer, private IInlineComponentDeserializer
	{
	public:
		/// @brief Creates a copy component deserializer.
		/// @param application Application
		/// @param worldDefinitionLoader World definition loader.
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer(Application::IApplication& application, WorldDefinitionLoader& worldDefinitionLoader) noexcept;
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer(const CopyComponentDeserializer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CopyComponentDeserializer(CopyComponentDeserializer&& other) noexcept = default;

		~CopyComponentDeserializer() noexcept;

		virtual void Associate(std::type_index componentType, std::size_t componentSize, std::string_view serializedType) override;

		CopyComponentDeserializer& operator =(const CopyComponentDeserializer& other) noexcept = default;
		CopyComponentDeserializer& operator =(CopyComponentDeserializer&& other) noexcept = default;

	private:
		virtual void Deserialize(std::size_t entityCount, std::span<const std::byte> input, std::span<std::byte> output) override;

		Application::IApplication* application; ///< Application.
		Log::ILogService* logService; ///< Log service.

		WorldDefinitionLoader* worldDefinitionLoader; ///< World definition loader.

		std::vector<std::pair<std::type_index, std::string>> registrations; ///< Registrations.
	};
}

namespace PonyEngine::Resource::World
{
	CopyComponentDeserializer::CopyComponentDeserializer(Application::IApplication& application, WorldDefinitionLoader& worldDefinitionLoader) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		worldDefinitionLoader{&worldDefinitionLoader}
	{
	}

	CopyComponentDeserializer::~CopyComponentDeserializer() noexcept
	{
		for (std::size_t i = registrations.size(); i-- > 0uz; )
		{
			const auto& [type, serializedType] = registrations[i];
			worldDefinitionLoader->UnregisterComponentDeserializer(type, serializedType, *this);
		}
	}

	void CopyComponentDeserializer::Associate(const std::type_index componentType, const std::size_t componentSize, const std::string_view serializedType)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		worldDefinitionLoader->RegisterComponentDeserializer(componentType, componentSize, serializedType, *this);
		try
		{
			registrations.emplace_back(componentType, serializedType);
		}
		catch (...)
		{
			worldDefinitionLoader->UnregisterComponentDeserializer(componentType, serializedType, *this);
			throw;
		}

		PONY_LOG(logService, Log::LogType::Info, "Component type '{}' associated with serialized type '{}' as copy component.", componentType.name(), serializedType);
	}

	void CopyComponentDeserializer::Deserialize(const std::size_t, const std::span<const std::byte> input, const std::span<std::byte> output)
	{
		if (input.size() != output.size()) [[unlikely]]
		{
			throw std::runtime_error("Invalid component table input");
		}

		std::memcpy(output.data(), input.data(), output.size());
	}
}
