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

export module PonyEngine.Resource.Impl:Context;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	class Context final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Context() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Context(const Context& other) = default;
		[[nodiscard("Pure constructor")]]
		Context(Context&& other) noexcept = default;

		~Context() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Index(ContextKey key, std::size_t startIndex = 0uz) const noexcept;
		[[nodiscard("Pure function")]]
		bool IsValid(ContextKey key, std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		ContextKey Key(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		ContextValue& Value(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const ContextValue& Value(std::size_t index) const noexcept;

		void Update(std::span<const std::size_t> indices, std::span<const ContextValue> values) noexcept;
		void Reserve(std::size_t addCount);
		std::size_t Add(ContextKey key);

		Context& operator =(const Context& other) = default;
		Context& operator =(Context&& other) noexcept = default;

	private:
		std::vector<ContextKey> keys;
		std::vector<ContextValue> values;
	};
}

namespace PonyEngine::Resource
{
	std::size_t Context::Size() const noexcept
	{
		return keys.size();
	}

	std::size_t Context::Index(const ContextKey key, const std::size_t startIndex) const noexcept
	{
		std::size_t index = startIndex;
		for (; index < keys.size() && keys[index] < key; ++index)
		{
		}

		return index;
	}

	bool Context::IsValid(const ContextKey key, const std::size_t index) const noexcept
	{
		return index < keys.size() && keys[index] == key;
	}

	ContextKey Context::Key(const std::size_t index) const noexcept
	{
		return keys[index];
	}

	ContextValue& Context::Value(const std::size_t index) noexcept
	{
		return values[index];
	}

	const ContextValue& Context::Value(const std::size_t index) const noexcept
	{
		return values[index];
	}

	void Context::Update(const std::span<const std::size_t> indices, const std::span<const ContextValue> values) noexcept
	{
		assert(indices.size() == values.size() && "Indices and values sizes are mismatched.");

		for (std::size_t i = 0uz; i < indices.size(); ++i)
		{
			this->values[indices[i]] = values[i];
		}
	}

	void Context::Reserve(const std::size_t addCount)
	{
		const std::size_t reserve = Size() + addCount;
		keys.reserve(reserve);
		values.reserve(reserve);
	}

	std::size_t Context::Add(const ContextKey key)
	{
		const std::size_t index = Index(key);
		keys.insert(keys.cbegin() + index, key);
		try
		{
			values.insert(values.cbegin() + index, ContextValue{});
		}
		catch (...)
		{
			keys.erase(keys.cbegin() + index);
			throw;
		}

		return index;
	}
}
