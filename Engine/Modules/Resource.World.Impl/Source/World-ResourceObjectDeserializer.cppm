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

export module PonyEngine.Resource.World.Impl:ResourceObjectDeserializer;

import std;

import PonyEngine.Application;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Resource.World.Ext;

import :ResourceObjectDeserializationRequest;
import :WorldDefinitionLoader;

export namespace PonyEngine::Resource::World
{
	/// @brief Resource object deserializer.
	/// @details It deserializes 'Pony.Resource' world objects.
	class ResourceObjectDeserializer final : public IResourceObjectDeserializer, public IObjectDeserializer
	{
	public:
		/// @brief Creates a resource object deserializer.
		/// @param application 
		[[nodiscard("Pure constructor")]]
		explicit ResourceObjectDeserializer(Application::IApplication& application);
		ResourceObjectDeserializer(const ResourceObjectDeserializer&) = delete;
		ResourceObjectDeserializer(ResourceObjectDeserializer&&) = delete;

		~ResourceObjectDeserializer() noexcept = default;

		virtual void Associate(std::type_index interfaceType, std::string_view serializedType) override;
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IWorldDeserializationRequest> Deserialize(std::span<const std::byte> input, PonyEngine::World::Object& output,
			std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback) override;

		ResourceObjectDeserializer& operator =(const ResourceObjectDeserializer&) = delete;
		ResourceObjectDeserializer& operator =(ResourceObjectDeserializer&&) = delete;

	private:
		/// @brief Gets a resource interface type by its serialized version.
		/// @param type Serialized type.
		/// @return Resource interface type.
		[[nodiscard("Pure function")]]
		std::type_index GetType(std::string_view type) const;

		/// @brief Validates if the buffer has enough data.
		/// @param current Current buffer pointer.
		/// @param end End buffer pointer.
		/// @param requiredSize Required size.
		static void ValidateSize(const std::byte* current, const std::byte* end, std::size_t requiredSize);
		/// @brief Reads the input as a data of type @p T and moves the pointer.
		/// @tparam T Data type.
		/// @param current Input.
		/// @return Read data.
		template<typename T>
		static T Read(const std::byte*& current) noexcept;
		/// @brief Reads the input as a string and moves the pointer.
		/// @param current Input.
		/// @param length String length.
		/// @return Read string.
		static std::string_view ReadString(const std::byte*& current, std::size_t length) noexcept;

		Application::IApplication* application; ///< Application.
		Log::ILogService* logService; ///< Log service.

		IResourceService* resourceService; ///< Resource service.

		std::unordered_map<std::uint64_t, std::type_index> types; ///< Type map.
		mutable std::shared_mutex typeMutex; ///< Type mutex.
	};
}

namespace PonyEngine::Resource::World
{
	ResourceObjectDeserializer::ResourceObjectDeserializer(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		resourceService{&this->application->GetInterface<IResourceService>()}
	{
	}

	void ResourceObjectDeserializer::Associate(const std::type_index interfaceType, const std::string_view serializedType)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");

		{
			const std::uint64_t typeHash = Hash::FNV1a64(serializedType);
			const auto lock = std::unique_lock(typeMutex);
			const auto [_, added] = types.emplace(typeHash, interfaceType);
			assert(added && "Such type is already added.");
		}

		PONY_LOG(logService, Log::LogType::Info, "Resource interface type '{}' associated with the serialized type '{}'.", interfaceType.name(), serializedType);
	}

	std::shared_ptr<IWorldDeserializationRequest> ResourceObjectDeserializer::Deserialize(const std::span<const std::byte> input, PonyEngine::World::Object& output,
		std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback)
	{
		const std::byte* current = input.data();
		const std::byte* const end = input.data() + input.size();

		ValidateSize(current, end, sizeof(std::uint8_t) * 2uz);
		const std::uint8_t interfaceLength = Read<std::uint8_t>(current);
		const std::uint8_t idLength = Read<std::uint8_t>(current);

		ValidateSize(current, end, static_cast<std::size_t>(interfaceLength) + idLength);
		const std::string_view interface = ReadString(current, interfaceLength);
		const std::string_view id = ReadString(current, idLength);

		const std::type_index resourceInterface = GetType(interface);
		const ResourceID resourceId = resourceService->MakeResourceID(id);

		auto request = std::make_shared<ResourceObjectDeserializationRequest>(output, std::move(callback));
		request->LoadRequest(resourceService->LoadResource(resourceId, resourceInterface, 
		[req = request.get(), resInterface = resourceInterface](const IResourceRequest& resourceRequest) noexcept
		{
			switch (resourceRequest.Status())
			{
			case Async::RequestStatus::Success:
				req->SetSuccess(PonyEngine::World::Object(resourceRequest.Resource(resInterface), resInterface));
				break;
			case Async::RequestStatus::Failure:
				req->SetFailure(resourceRequest.Exceptions());
				break;
			case Async::RequestStatus::Canceled:
				req->SetCanceled();
				break;
			default: [[unlikely]]
				assert(false && "Unexpected status.");
				break;
			}
		}));

		return request;
	}

	std::type_index ResourceObjectDeserializer::GetType(const std::string_view type) const
	{
		const std::uint64_t typeHash = Hash::FNV1a64(type);
		const auto lock = std::shared_lock(typeMutex);
		if (const auto position = types.find(typeHash); position != types.cend())
		{
			return position->second;
		}

		throw std::runtime_error("Resource type not found");
	}

	void ResourceObjectDeserializer::ValidateSize(const std::byte* const current, const std::byte* const end, const std::size_t requiredSize)
	{
		if (static_cast<std::size_t>(end - current) < requiredSize) [[unlikely]]
		{
			throw std::runtime_error("Invalid input");
		}
	}

	template<typename T>
	T ResourceObjectDeserializer::Read(const std::byte*& current) noexcept
	{
		if constexpr (sizeof(T) == 1)
		{
			return static_cast<T>(*current++);
		}
		else
		{
			T value;
			std::memcpy(&value, current, sizeof(T));
			current += sizeof(T);
			return value;
		}
	}

	std::string_view ResourceObjectDeserializer::ReadString(const std::byte*& current, const std::size_t length) noexcept
	{
		const auto string = std::string_view(reinterpret_cast<const char*>(current), length);
		current += length;
		return string;
	}
}
