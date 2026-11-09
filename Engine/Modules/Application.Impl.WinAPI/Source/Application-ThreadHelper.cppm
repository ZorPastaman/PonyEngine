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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <avrt.h>

export module PonyEngine.Application.Impl.WinAPI:ThreadHelper;

import std;

import PonyEngine.Hash;

import :ThreadRole;
import :ThreadRoleList;

namespace PonyEngine::Application
{
	/// @brief Gets thread role hashes.
	/// @return Thread role hashes. Synced with thread roles by index.
	[[nodiscard("Pure function")]]
	static constexpr std::array<std::uint32_t, ThreadRoles.size()> GetThreadRoleNameHashes() noexcept
	{
		std::array<std::uint32_t, ThreadRoles.size()> hashes;
		for (std::size_t i = 0uz; i < ThreadRoles.size(); ++i)
		{
			hashes[i] = Hash::FNV1a32(ThreadRoles[i].first);
		}

		return hashes;
	}

	/// @brief Checks if the hashes are unique.
	/// @param elements Hash elements.
	/// @return @a True if they're unique; @a false otherwise.
	[[nodiscard("Pure function")]]
	static constexpr bool AreHashesUnique(const std::span<const std::uint32_t> elements) noexcept
	{
		for (std::size_t i = 1uz; i < elements.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (elements[i] == elements[j])
				{
					return false;
				}
			}
		}

		return true;
	}

	/// @brief Calculates how many unique mmcss task names are in thread roles.
	/// @return Unique mmcss task name count.
	[[nodiscard("Pure function")]]
	static constexpr std::size_t CalculateUniqueMMCSSTaskNameCount() noexcept
	{
		std::size_t nameCount = 0uz;
		for (std::size_t i = 0uz; i < ThreadRoles.size(); ++i)
		{
			if (!ThreadRoles[i].second.mmcssTask.empty())
			{
				bool found = false;
				for (std::size_t j = 0uz; j < i && !found; ++j)
				{
					found = ThreadRoles[i].second.mmcssTask == ThreadRoles[j].second.mmcssTask;
				}

				nameCount += !found;
			}
		}

		return nameCount;
	}

	/// @brief Gets task index to unique task index map.
	/// @return Task index map.
	[[nodiscard("Pure function")]]
	static constexpr std::array<std::size_t, ThreadRoles.size()> GetTaskIndexMap() noexcept
	{
		std::array<std::size_t, ThreadRoles.size()> indexMap;

		for (std::size_t i = 0uz, uniqueIndex = 0uz; i < ThreadRoles.size(); ++i)
		{
			if (ThreadRoles[i].second.mmcssTask.empty())
			{
				indexMap[i] = std::numeric_limits<std::size_t>::max();
			}
			else
			{
				std::optional<std::size_t> foundIndex = std::nullopt;
				for (std::size_t j = 0uz; j < i; ++j)
				{
					if (ThreadRoles[i].second.mmcssTask == ThreadRoles[j].second.mmcssTask)
					{
						foundIndex = j;
						break;
					}
				}

				if (foundIndex)
				{
					indexMap[i] = *foundIndex;
				}
				else
				{
					indexMap[i] = uniqueIndex++;
				}
			}
		}

		return indexMap;
	}

	static constexpr std::size_t UniqueMMCSSTaskNameCount = CalculateUniqueMMCSSTaskNameCount(); ///< Unique mmcss task name count.

	static constexpr std::array<std::uint32_t, ThreadRoles.size()> ThreadRoleNameHashes = GetThreadRoleNameHashes(); ///< Thread role name hashes.
	static_assert(AreHashesUnique(ThreadRoleNameHashes), "Same thread role is added twice or hash collision occured");

	static constexpr std::array<std::size_t, ThreadRoles.size()> MMCSSTaskIndexMap = GetTaskIndexMap(); ///< MMCSS task index map.
	static std::array<std::atomic<DWORD>, UniqueMMCSSTaskNameCount> MMCSSTaskIndices; ///< MMCSS task indices.
}

export namespace PonyEngine::Application
{
	/// @brief Gets a list of thread roles.
	/// @return Thread roles.
	[[nodiscard("Pure function")]]
	std::vector<std::string_view> GetThreadRoles();

	[[nodiscard("Pure function")]]
	std::size_t GetThreadRoleIndex(std::string_view role);

	void SetThreadPriority(HANDLE thread, std::size_t roleIndex);

	[[nodiscard("Must be used")]]
	HANDLE SetThreadMMCSS(HANDLE thread, std::size_t roleIndex);
	void SetThreadMMCSSPriority(HANDLE mmcssHandle, std::size_t roleIndex);
	void RevertThreadMMCSS(HANDLE mmcssHandle);

	[[nodiscard("Pure function")]]
	std::string GetThreadRoleLog(std::size_t roleIndex);
}

namespace PonyEngine::Application
{
	std::vector<std::string_view> GetThreadRoles()
	{
		constexpr auto roleView = std::views::keys(ThreadRoles);
		return std::vector<std::string_view>(roleView.cbegin(), roleView.cend());
	}

	std::size_t GetThreadRoleIndex(const std::string_view role)
	{
		const std::uint32_t roleHash = Hash::FNV1a32(role);
		const std::size_t index = std::ranges::find(ThreadRoleNameHashes, roleHash) - ThreadRoleNameHashes.cbegin();
		if (index >= ThreadRoleNameHashes.size() || ThreadRoles[index].first != role) [[unlikely]]
		{
			throw std::invalid_argument("Invalid thread role");
		}

		return index;
	}

	void SetThreadPriority(const HANDLE thread, const std::size_t roleIndex)
	{
		const int threadPriority = ThreadRoles[roleIndex].second.threadPriority;
		if (!::SetThreadPriority(thread, threadPriority)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set thread priority: Priority = '0x{:X}'; Error code = '0x{:X}'", threadPriority, GetLastError()));
		}
	}

	HANDLE SetThreadMMCSS(const HANDLE thread, const std::size_t roleIndex)
	{
		const std::string_view mmcssTask = ThreadRoles[roleIndex].second.mmcssTask;
		if (mmcssTask.empty())
		{
			return nullptr;
		}

		std::atomic<DWORD>& taskIndex = MMCSSTaskIndices[MMCSSTaskIndexMap[roleIndex]];
		DWORD index = taskIndex.load(std::memory_order::relaxed);
		const HANDLE mmcssHandle = AvSetMmThreadCharacteristicsA(mmcssTask.data(), &index);
		if (!mmcssHandle) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set mmcss thread task: Task = '{}'; Error code = '0x{:X}'", mmcssTask, GetLastError()));
		}
		taskIndex.store(index, std::memory_order::relaxed);

		return mmcssHandle;
	}

	void SetThreadMMCSSPriority(const HANDLE mmcssHandle, const std::size_t roleIndex)
	{
		assert(mmcssHandle && "MMCSS handle is nullptr.");

		const AVRT_PRIORITY mmcssPriority = ThreadRoles[roleIndex].second.mmcssPriority;
		if (!AvSetMmThreadPriority(mmcssHandle, mmcssPriority)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set mmcss thread priority: TaskHandle = '0x{:X}'; Priority = '{}'; Error code = '0x{:X}'",
				reinterpret_cast<std::uintptr_t>(mmcssHandle), std::to_underlying(mmcssPriority), GetLastError()));
		}
	}

	void RevertThreadMMCSS(const HANDLE mmcssHandle)
	{
		assert(mmcssHandle && "MMCSS handle is nullptr.");

		if (!AvRevertMmThreadCharacteristics(mmcssHandle)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to revert mmcss task: Error code = '0x{:X}'", GetLastError()));
		}
	}

	std::string GetThreadRoleLog(const std::size_t roleIndex)
	{
		const ThreadRole& role = ThreadRoles[roleIndex].second;
		return std::format("Priority: '{}'; MMCSS task: '{}'; MMCSS task priority: '{}'", role.threadPriority, role.mmcssTask, std::to_underlying(role.mmcssPriority));
	}
}
