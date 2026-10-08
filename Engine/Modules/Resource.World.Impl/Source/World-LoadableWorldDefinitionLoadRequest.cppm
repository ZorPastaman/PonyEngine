/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Impl:LoadableWorldDefinitionLoadRequest;

import std;

import PonyEngine.Resource.Ext;

import :WorldDefinitionLoadRequest;

export namespace PonyEngine::Resource::World
{
	/// @brief World definition load request with a loadable data request.
	class LoadableWorldDefinitionLoadRequest final : public WorldDefinitionLoadRequest
	{
	public:
		/// @brief Creates a loadable world definition load request.
		/// @param data World data buffer.
		/// @param dataSize World data size.
		/// @param worldDefinition World definition target.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		LoadableWorldDefinitionLoadRequest(std::shared_ptr<std::byte[]> data, std::size_t dataSize, std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition,
			std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
		LoadableWorldDefinitionLoadRequest(const LoadableWorldDefinitionLoadRequest&) = delete;
		LoadableWorldDefinitionLoadRequest(LoadableWorldDefinitionLoadRequest&&) = delete;

		virtual ~LoadableWorldDefinitionLoadRequest() noexcept override = default;

		virtual void Cancel() override;

		/// @brief Gets the request.
		/// @return Request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<ILoadableDataAccessRequest>& Request() const noexcept;
		/// @brief Sets the request.
		/// @param request Request.
		void Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept;

		LoadableWorldDefinitionLoadRequest& operator =(const LoadableWorldDefinitionLoadRequest&) = delete;
		LoadableWorldDefinitionLoadRequest& operator =(LoadableWorldDefinitionLoadRequest&&) = delete;

	private:
		std::shared_ptr<std::byte[]> data; ///< World data buffer.
		std::shared_ptr<ILoadableDataAccessRequest> request; ///< Loadable data request.
	};
}

namespace PonyEngine::Resource::World
{
	LoadableWorldDefinitionLoadRequest::LoadableWorldDefinitionLoadRequest(std::shared_ptr<std::byte[]> data, const std::size_t dataSize, 
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) :
		WorldDefinitionLoadRequest(std::move(worldDefinition), std::span(data.get(), dataSize), std::move(callback)),
		data(std::move(data))
	{
	}

	void LoadableWorldDefinitionLoadRequest::Cancel()
	{
		WorldDefinitionLoadRequest::Cancel();
		request->Cancel();
	}

	const std::shared_ptr<ILoadableDataAccessRequest>& LoadableWorldDefinitionLoadRequest::Request() const noexcept
	{
		return request;
	}

	void LoadableWorldDefinitionLoadRequest::Request(std::shared_ptr<ILoadableDataAccessRequest> request) noexcept
	{
		this->request = std::move(request);
	}
}
