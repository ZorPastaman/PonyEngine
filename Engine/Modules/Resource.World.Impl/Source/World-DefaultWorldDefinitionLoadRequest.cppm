/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Impl:DefaultWorldDefinitionLoadRequest;

import std;

import PonyEngine.Resource.Ext;

import :WorldDefinitionLoadRequest;

export namespace PonyEngine::Resource::World
{
	class DefaultWorldDefinitionLoadRequest final : public WorldDefinitionLoadRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		DefaultWorldDefinitionLoadRequest(std::shared_ptr<std::byte[]> data, std::size_t dataSize, std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition,
			std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
		DefaultWorldDefinitionLoadRequest(const DefaultWorldDefinitionLoadRequest&) = delete;
		DefaultWorldDefinitionLoadRequest(DefaultWorldDefinitionLoadRequest&&) = delete;

		virtual ~DefaultWorldDefinitionLoadRequest() noexcept override = default;

		virtual void Cancel() override;

		/// @brief Gets the request.
		/// @return Request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<ILoadableDataAccessRequest>& Request() const noexcept;
		/// @brief Sets the request.
		/// @param request Request.
		void Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept;

		DefaultWorldDefinitionLoadRequest& operator =(const DefaultWorldDefinitionLoadRequest&) = delete;
		DefaultWorldDefinitionLoadRequest& operator =(DefaultWorldDefinitionLoadRequest&&) = delete;

	private:
		std::shared_ptr<std::byte[]> data;
		std::shared_ptr<ILoadableDataAccessRequest> request;
	};
}

namespace PonyEngine::Resource::World
{
	DefaultWorldDefinitionLoadRequest::DefaultWorldDefinitionLoadRequest(std::shared_ptr<std::byte[]> data, const std::size_t dataSize, 
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) :
		WorldDefinitionLoadRequest(std::move(worldDefinition), std::span(data.get(), dataSize), std::move(callback)),
		data(std::move(data))
	{
	}

	void DefaultWorldDefinitionLoadRequest::Cancel()
	{
		WorldDefinitionLoadRequest::Cancel();
		request->Cancel();
	}

	const std::shared_ptr<ILoadableDataAccessRequest>& DefaultWorldDefinitionLoadRequest::Request() const noexcept
	{
		return request;
	}

	void DefaultWorldDefinitionLoadRequest::Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept
	{
		this->request = std::move(request);
	}
}
