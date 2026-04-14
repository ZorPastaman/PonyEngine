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

export module PonyEngine.Log.Impl:SubLoggerContainer;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger container.
	class SubLoggerContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SubLoggerContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		SubLoggerContainer(const SubLoggerContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		SubLoggerContainer(SubLoggerContainer&& other) noexcept = default;

		~SubLoggerContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Gets the index of the @p handle.
		/// @param handle Handle.
		/// @return Index of the handle if found; size otherwise.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(SubLoggerHandle handle) const noexcept;
		/// @brief Gets the index of the @p subLogger.
		/// @param subLogger Sub-logger.
		/// @return Index of the sub-logger if found; size otherwise.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const ISubLogger& subLogger) const noexcept;

		/// @brief Gets the handle at the @p index.
		/// @param index Index.
		/// @return Handle.
		[[nodiscard("Pure function")]]
		SubLoggerHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets the sub-logger at the @p index.
		/// @param index Index.
		/// @return Sub-logger.
		[[nodiscard("Pure function")]]
		ISubLogger& SubLogger(std::size_t index) const noexcept;

		/// @brief Adds a sub-logger.
		/// @param handle Handle.
		/// @param subLogger Sub-logger.
		void Add(SubLoggerHandle handle, const std::shared_ptr<ISubLogger>& subLogger);
		/// @brief Removes a sub-logger at the @p index.
		/// @param index Index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the container.
		void Clear() noexcept;

		SubLoggerContainer& operator =(const SubLoggerContainer& other) = delete;
		SubLoggerContainer& operator =(SubLoggerContainer&& other) noexcept = default;

	private:
		std::vector<SubLoggerHandle> subLoggerHandles; ///< Sub-logger handles.
		std::vector<std::shared_ptr<ISubLogger>> subLoggers; ///< Sub-loggers.
	};
}

namespace PonyEngine::Log
{
	std::size_t SubLoggerContainer::Size() const noexcept
	{
		return subLoggerHandles.size();
	}

	std::size_t SubLoggerContainer::IndexOf(const SubLoggerHandle handle) const noexcept
	{
		return std::ranges::find(subLoggerHandles, handle) - subLoggerHandles.cbegin();
	}

	std::size_t SubLoggerContainer::IndexOf(const ISubLogger& subLogger) const noexcept
	{
		return std::ranges::find_if(subLoggers, [&](const std::shared_ptr<ISubLogger>& s) { return s.get() == &subLogger; }) - subLoggers.cbegin();
	}

	SubLoggerHandle SubLoggerContainer::Handle(const std::size_t index) const noexcept
	{
		return subLoggerHandles[index];
	}

	ISubLogger& SubLoggerContainer::SubLogger(const std::size_t index) const noexcept
	{
		return *subLoggers[index];
	}

	void SubLoggerContainer::Add(const SubLoggerHandle handle, const std::shared_ptr<ISubLogger>& subLogger)
	{
		assert(subLogger && "The sub-logger is nullptr.");

		subLoggerHandles.push_back(handle);
		try
		{
			subLoggers.push_back(subLogger);
		}
		catch (...)
		{
			subLoggerHandles.pop_back();
			throw;
		}
	}

	void SubLoggerContainer::Remove(const std::size_t index) noexcept
	{
		subLoggers.erase(subLoggers.cbegin() + index);
		subLoggerHandles.erase(subLoggerHandles.cbegin() + index);
	}

	void SubLoggerContainer::Clear() noexcept
	{
		subLoggerHandles.clear();
		subLoggers.clear();
	}
}
