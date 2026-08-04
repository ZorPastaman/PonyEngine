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

#include "PonyEngine/Platform/Windows/Framework.h"

#include <avrt.h>

export module PonyEngine.Application.Impl.Windows:ThreadControl;

import std;

import PonyEngine.Application;

import :ThreadRole;

export namespace PonyEngine::Application
{
	/// @brief Thread control.
	class ThreadControl final : public IThreadControl
	{
	public:
		/// @brief Creates a thread control.
		/// @param thread Thread. Must be valid.
		[[nodiscard("Pure constructor")]]
		explicit ThreadControl(std::thread& thread) noexcept;
		/// @brief Creates a thread control.
		/// @param thread Thread. Must be valid.
		[[nodiscard("Pure constructor")]]
		explicit ThreadControl(HANDLE thread) noexcept;
		ThreadControl(const ThreadControl&) = delete;
		ThreadControl(ThreadControl&&) = delete;

		~ThreadControl() noexcept;

		/// @brief Gets the thread role.
		/// @return Thread role.
		[[nodiscard("Pure function")]]
		virtual std::string_view Role() const noexcept override;
		/// @brief Sets the thread role.
		/// @param role Thread role.
		virtual void Role(std::string_view role) override;

		ThreadControl& operator =(const ThreadControl&) = delete;
		ThreadControl& operator =(ThreadControl&&) = delete;

	private:
		HANDLE thread; ///< Thread.
		std::string_view role; ///< Thread role.
		HANDLE mmcssHandle; ///< MMCSS handle.
	};

	/// @brief Gets a list of thread roles.
	/// @return Thread roles.
	[[nodiscard("Pure function")]]
	std::vector<std::string_view> GetThreadRoles();
}

namespace PonyEngine::Application
{
	ThreadControl::ThreadControl(std::thread& thread) noexcept :
		ThreadControl(thread.native_handle())
	{
	}

	ThreadControl::ThreadControl(const HANDLE thread) noexcept :
		thread{thread},
		mmcssHandle{nullptr}
	{
	}

	ThreadControl::~ThreadControl() noexcept
	{
		if (mmcssHandle)
		{
			AvRevertMmThreadCharacteristics(mmcssHandle);
		}
	}

	std::string_view ThreadControl::Role() const noexcept
	{
		return role;
	}

	void ThreadControl::Role(const std::string_view role)
	{
		try
		{
			if (mmcssHandle)
			{
				if (!AvRevertMmThreadCharacteristics(mmcssHandle)) [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to revert mmcss task: Error code = '0x{:X}'", GetLastError()));
				}
				mmcssHandle = nullptr;
			}

			if (role.empty())
			{
				if (!SetThreadPriority(thread, THREAD_PRIORITY_NORMAL)) [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to set normal priority: Error code = '0x{:X}'", GetLastError()));
				}

				this->role = "";
			}
			else
			{
				const auto roleDesc = ThreadRoles.find(role);
				if (roleDesc == ThreadRoles.cend()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid role");
				}

				if (!SetThreadPriority(thread, roleDesc->second.threadPriority)) [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to set '{}' priority: Error code = '0x{:X}'", roleDesc->first, GetLastError()));
				}

				if (!roleDesc->second.mmcssTask.empty())
				{
					DWORD index = 0;
					mmcssHandle = AvSetMmThreadCharacteristicsA(roleDesc->second.mmcssTask.data(), &index);
					if (!mmcssHandle) [[unlikely]]
					{
						throw std::runtime_error(std::format("Failed to set mmcss thread task: Task = '{}', Error code = '0x{:X}'", roleDesc->second.mmcssTask, GetLastError()));
					}
					if (!AvSetMmThreadPriority(mmcssHandle, roleDesc->second.mmcssPriority)) [[unlikely]]
					{
						throw std::runtime_error(std::format("Failed to set mmcss thread priority: Task = '{}', Error code = '0x{:X}'", roleDesc->second.mmcssTask, GetLastError()));
					}
				}

				this->role = roleDesc->first;
			}
		}
		catch (...)
		{
			Role("");
			throw;
		}
	}

	std::vector<std::string_view> GetThreadRoles()
	{
		constexpr auto roleView = std::views::keys(ThreadRoles);
		return std::vector<std::string_view>(roleView.cbegin(), roleView.cend());
	}
}
