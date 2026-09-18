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

export module PonyEngine.Resource.Text.Impl:TextLoader;

import std;

import PonyEngine.Resource.Ext;

import :CompletedResourceLoadRequest;
import :OngoingResourceLoadRequest;
import :TextResource;

export namespace PonyEngine::Resource::Text
{
	/// @brief Text loader.
	class TextLoader final : public IResourceLoader
	{
	public:
		[[nodiscard("Pure constructor")]]
		TextLoader();
		TextLoader(const TextLoader&) = delete;
		TextLoader(TextLoader&&) = delete;

		~TextLoader() noexcept;

		virtual void PrepareResource(ILoadableResource& context) override;

		[[nodiscard("Weird call")]] 
		virtual std::shared_ptr<IResourceLoadRequest> Load(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) override;

		TextLoader& operator =(const TextLoader&) = delete;
		TextLoader& operator =(TextLoader&&) = delete;

	private:
		/// @brief Gets a data access type. Throws if no supported access type is available.
		/// @param availableAccessTypes Available access types.
		/// @param directResourceUsage Should the resource use the provided resource source directly?
		/// @return Data access type.
		[[nodiscard("Pure function")]]
		static std::type_index GetDataAccessType(std::span<const std::type_index> availableAccessTypes, bool directResourceUsage);

		/// @brief Creates a text resource.
		/// @param textData Text data.
		/// @param textView Text view.
		/// @return Text resource.
		[[nodiscard("Pure function")]]
		std::shared_ptr<TextResource> CreateTextResource(std::shared_ptr<const void> textData, std::string_view textView);

		/// @brief Makes a default load request - loads a text to its own buffer.
		/// @param context Load context.
		/// @param callback Callback.
		/// @return Default load request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceLoadRequest> MakeDefaultLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
		/// @brief Makes a direct load request - references a text directly in the provided data.
		/// @param context Load context.
		/// @param callback Callback.
		/// @return Direct load request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceLoadRequest> MakeDirectLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);

		/// @brief Adds the ongoing load request.
		/// @param request Request to add.
		void AddOngoingRequest(const std::shared_ptr<OngoingResourceLoadRequest>& request);
		/// @brief Removes the ongoing load request.
		/// @param request Request to remove.
		/// @return Removed load request.
		std::shared_ptr<OngoingResourceLoadRequest> RemoveOngoingRequest(OngoingResourceLoadRequest* request) noexcept;

		/// @brief Increment the ongoing request count.
		void IncrementOngoingRequestCount() noexcept;
		/// @brief Decrement the ongoing request count.
		void DecrementOngoingRequestCount() noexcept;
		/// @brief Wait till the ongoing request count reaches 0.
		void WaitForOngoingRequestCountToFinish() const noexcept;

		static inline const std::type_index DefaultAccessType = typeid(ILoadableDataAccess); ///< Default data access type.
		static inline const std::type_index DirectAccessType = typeid(IMemoryDataAccess); ///< Direct data access type.

		std::unordered_map<OngoingResourceLoadRequest*, std::shared_ptr<OngoingResourceLoadRequest>> loadRequests; ///< Load requests.
		std::mutex loadRequestsMutex; ///< Load requests mutex.

		std::atomic_size_t ongoingRequestCount; ///< Ongoing request count.

#ifndef NDEBUG
		std::atomic_size_t textResourceCount; ///< Text resource count.
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free");
	};
}

namespace PonyEngine::Resource::Text
{
	TextLoader::TextLoader() :
#ifndef NDEBUG
		textResourceCount(0uz),
#endif
		ongoingRequestCount(0uz)
	{
	}

	TextLoader::~TextLoader() noexcept
	{
		WaitForOngoingRequestCountToFinish();

#ifndef NDEBUG
		assert(textResourceCount.load(std::memory_order::relaxed) == 0uz && "Some text resources are still alive.");
#endif
	}

	void TextLoader::PrepareResource(ILoadableResource& context)
	{
		if (!context.DataMeta().empty()) [[unlikely]]
		{
			throw std::logic_error("Invalid resource data meta");
		}

		const std::span<const std::byte> loadMeta = context.LoadMeta();
		if (loadMeta.size() != 1uz) [[unlikely]]
		{
			throw std::logic_error("Invalid resource load meta");
		}
		const bool directResourceAccess = static_cast<std::uint8_t>(loadMeta[0]);

		context.SetDataAccessType(GetDataAccessType(context.DataAccessTypes(), directResourceAccess));
		context.AddInterfaceTypes<std::string_view>();
	}

	std::shared_ptr<IResourceLoadRequest> TextLoader::Load(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		if (const std::type_index accessType = context.ResourceDataAccessType(); accessType == DefaultAccessType)
		{
			return MakeDefaultLoadRequest(context, std::move(callback));
		}
		else if (accessType == DirectAccessType)
		{
			return MakeDirectLoadRequest(context, std::move(callback));
		}

		throw std::logic_error("Invalid access type");
	}

	std::type_index TextLoader::GetDataAccessType(const std::span<const std::type_index> availableAccessTypes, const bool directResourceUsage)
	{
		if (directResourceUsage)
		{
			if (std::ranges::contains(availableAccessTypes, DirectAccessType)) [[likely]]
			{
				return DirectAccessType;
			}
		}
		else
		{
			if (std::ranges::contains(availableAccessTypes, DefaultAccessType)) [[likely]]
			{
				return DefaultAccessType;
			}
		}

		throw std::logic_error("No valid access type found");
	}

	std::shared_ptr<TextResource> TextLoader::CreateTextResource(std::shared_ptr<const void> textData, const std::string_view textView)
	{
#ifndef NDEBUG
		const auto resource = new TextResource(std::move(textData), textView);
		textResourceCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<TextResource>(resource, [this](const TextResource* const text) noexcept
			{
				delete text;
				textResourceCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete resource;
			textResourceCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<TextResource>(std::move(textData), textView);
#endif
	}

	std::shared_ptr<IResourceLoadRequest> TextLoader::MakeDefaultLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		const auto dataAccess = static_cast<ILoadableDataAccess*>(context.ResourceDataAccess().get());
		const std::size_t size = dataAccess->Size();
		auto data = std::make_shared<char[]>(size);
		const auto buffer = std::span(reinterpret_cast<std::byte*>(data.get()), size);
		const auto text = std::string_view(data.get(), size);

		auto resource = CreateTextResource(std::move(data), text);
		auto request = std::make_shared<OngoingResourceLoadRequest>(std::move(resource), std::move(callback));
		AddOngoingRequest(request);
		IncrementOngoingRequestCount();

		try
		{
			request->Request(dataAccess->Load(LoadParams{.buffer = buffer}, [this, req = request.get()](const ILoadableDataAccessRequest& accessRequest) noexcept
			{
				std::shared_ptr<OngoingResourceLoadRequest> loadRequest = RemoveOngoingRequest(req);
				switch (accessRequest.Status())
				{
				case Async::RequestStatus::Success:
					loadRequest->SetSuccess();
					break;
				case Async::RequestStatus::Failure:
					loadRequest->SetException(accessRequest.Exception());
					break;
				case Async::RequestStatus::Canceled:
					loadRequest->SetCanceled();
					break;
				default: [[unlikely]]
					assert(false && "Unexpected status");
					break;
				}

				loadRequest.reset();
				DecrementOngoingRequestCount();
			}));
		}
		catch (...)
		{
			RemoveOngoingRequest(request.get());
			DecrementOngoingRequestCount();
			throw;
		}

		return request;
	}

	std::shared_ptr<IResourceLoadRequest> TextLoader::MakeDirectLoadRequest(const ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback)
	{
		std::shared_ptr<IMemoryDataAccess> dataAccess = std::static_pointer_cast<IMemoryDataAccess>(context.ResourceDataAccess());
		const std::span<const std::byte> data = dataAccess->Buffer();
		const auto text = std::string_view(reinterpret_cast<const char*>(data.data()), data.size());

		auto resource = CreateTextResource(std::move(dataAccess), text);
		auto request = std::make_shared<CompletedResourceLoadRequest>(std::move(resource));

		if (callback)
		{
			callback(*request);
		}

		return request;
	}

	void TextLoader::AddOngoingRequest(const std::shared_ptr<OngoingResourceLoadRequest>& request)
	{
		const auto lock = std::lock_guard(loadRequestsMutex);
		assert(!loadRequests.contains(request.get()) && "Double request addition.");

		loadRequests[request.get()] = request;
	}

	std::shared_ptr<OngoingResourceLoadRequest> TextLoader::RemoveOngoingRequest(OngoingResourceLoadRequest* const request) noexcept
	{
		const auto lock = std::lock_guard(loadRequestsMutex);
		const auto position = loadRequests.find(request);
		assert(position != loadRequests.cend() && "Request wasn't added.");

		std::shared_ptr<OngoingResourceLoadRequest> req = std::move(position->second);
		loadRequests.erase(position);

		return req;
	}

	void TextLoader::IncrementOngoingRequestCount() noexcept
	{
		ongoingRequestCount.fetch_add(1uz, std::memory_order::release);
	}

	void TextLoader::DecrementOngoingRequestCount() noexcept
	{
		ongoingRequestCount.fetch_sub(1uz, std::memory_order::release);
		ongoingRequestCount.notify_one();
	}

	void TextLoader::WaitForOngoingRequestCountToFinish() const noexcept
	{
		for (std::size_t requestCount = ongoingRequestCount.load(std::memory_order::acquire);
			requestCount > 0uz;
			requestCount = ongoingRequestCount.load(std::memory_order::acquire))
		{
			ongoingRequestCount.wait(requestCount, std::memory_order::acquire);
		}
	}
}
