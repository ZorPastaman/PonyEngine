/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:LoadRequestManager;

import std;

import PonyEngine.File;

import :LoadRequest;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Load request manager.
	class LoadRequestManager final
	{
	public:
		[[nodiscard("Pure function")]]
		LoadRequestManager() noexcept = default;
		LoadRequestManager(const LoadRequestManager&) = delete;
		LoadRequestManager(LoadRequestManager&&) = delete;

		~LoadRequestManager() noexcept = default;

		/// @brief Creates a load request.
		/// @param file Pack file.
		/// @param offset Resource offset.
		/// @param loadParams Load parameters.
		/// @param callback Load callback.
		/// @return Load request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<LoadRequest> CreateRequest(const File::IFile& file, std::size_t offset,
			const LoadParams& loadParams, const std::function<void(const ILoadRequest&)>& callback) const;
		
		LoadRequestManager& operator =(const LoadRequestManager&) = delete;
		LoadRequestManager& operator =(LoadRequestManager&&) = delete;

	private:
		std::pmr::synchronized_pool_resource requestPool; ///< Request pool.
		std::pmr::polymorphic_allocator<LoadRequest> requestAllocator; ///< Request allocator.
	};
}

namespace PonyEngine::Resource::Pack
{
	std::shared_ptr<LoadRequest> LoadRequestManager::CreateRequest(const File::IFile& file, const std::size_t offset,
		const LoadParams& loadParams, const std::function<void(const ILoadRequest&)>& callback) const
	{
		auto loadRequest = std::allocate_shared<LoadRequest>(requestAllocator, loadParams, callback);
		const auto readParams = File::ReadParams
		{
			.buffer = loadParams.buffer,
			.offset = loadParams.offset + offset
		};
		loadRequest->FileRequest(file.Read(readParams, loadRequest->FileCallback()));

		return loadRequest;
	}
}
