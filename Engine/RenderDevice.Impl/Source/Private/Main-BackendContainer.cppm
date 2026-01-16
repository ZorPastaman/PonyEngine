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

export module PonyEngine.RenderDevice.Impl:BackendContainer;

import std;

import PonyEngine.RenderDevice.Ext;

export namespace PonyEngine::RenderDevice
{
	class BackendContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		BackendContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		BackendContainer(const BackendContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		BackendContainer(BackendContainer&& other) noexcept = default;

		~BackendContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		BackendHandle Handle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		IBackend& Backend(std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(BackendHandle handle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IBackend& backend) const noexcept;

		void Add(BackendHandle handle, const std::shared_ptr<IBackend>& backend);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		BackendContainer& operator =(const BackendContainer&) = delete;
		BackendContainer& operator =(BackendContainer&& other) noexcept = default;

	private:
		std::vector<BackendHandle> handles;
		std::vector<std::shared_ptr<IBackend>> backends;
	};
}

namespace PonyEngine::RenderDevice
{
	std::size_t BackendContainer::Size() const noexcept
	{
		return handles.size();
	}

	BackendHandle BackendContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	IBackend& BackendContainer::Backend(const std::size_t index) const noexcept
	{
		return *backends[index];
	}

	std::size_t BackendContainer::IndexOf(const BackendHandle handle) const noexcept
	{
		return std::ranges::find(handles, handle) - handles.cbegin();
	}

	std::size_t BackendContainer::IndexOf(const IBackend& backend) const noexcept
	{
		return std::ranges::find_if(backends, [&](const std::shared_ptr<IBackend>& b) { return b.get() == &backend; }) - backends.cbegin();
	}

	void BackendContainer::Add(const BackendHandle handle, const std::shared_ptr<IBackend>& backend)
	{
		assert(backend && "Backend is nullptr.");

		handles.push_back(handle);
		try
		{
			backends.push_back(backend);
		}
		catch (...)
		{
			handles.pop_back();
			throw;
		}
	}

	void BackendContainer::Remove(const std::size_t index) noexcept
	{
		backends.erase(backends.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void BackendContainer::Clear() noexcept
	{
		handles.clear();
		backends.clear();
	}
}
