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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Main.Windows:MessageLoopService;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;

export namespace PonyEngine::Application::Windows
{
	/// @brief Message loop service.
	class MessageLoopService final : public ITickableService, private IMessageLoopService
	{
	public:
		/// @brief Creates a message loop service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit MessageLoopService(IApplicationContext& application) noexcept;
		MessageLoopService(const MessageLoopService&) = delete;
		MessageLoopService(MessageLoopService&&) = delete;

		~MessageLoopService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) override;
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept override;

		/// @brief Gets the public message loop service.
		/// @return Public message loop service.
		[[nodiscard("Pure function")]]
		IMessageLoopService& PublicMessageLoopService() noexcept;
		/// @brief Gets the public message loop service.
		/// @return Public message loop service.
		[[nodiscard("Pure function")]]
		const IMessageLoopService& PublicMessageLoopService() const noexcept;

		MessageLoopService& operator =(const MessageLoopService&) = delete;
		MessageLoopService& operator =(MessageLoopService&&) = delete;

	private:
		/// @brief Calls message observers of the specified message type.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		void ObserveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		IApplicationContext* application; ///< Application context.

		std::unordered_map<UINT, std::vector<IMessageObserver*>> messageObservers; ///< Message observers.
	};
}

namespace PonyEngine::Application::Windows
{
	MessageLoopService::MessageLoopService(IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	void MessageLoopService::Begin()
	{
	}

	void MessageLoopService::End()
	{
	}

	void MessageLoopService::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Peeking messages.");
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			PONY_LOG(application->Logger(), Log::LogType::Verbose, "Received '{}' message for '{}'.", 
				message.message, message.hwnd ? std::format("0x{:X}", reinterpret_cast<std::uintptr_t>(message.hwnd)).c_str() : "nullptr");

			if (!message.hwnd) [[unlikely]]
			{
				ObserveMessage(message.message, message.wParam, message.lParam);
			}

			if (message.message == WM_QUIT) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", static_cast<int>(message.wParam));
				application->Stop(static_cast<int>(message.wParam));
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	void MessageLoopService::AddMessageObserver(IMessageObserver& observer, const UINT messageType)
	{
		std::vector<IMessageObserver*>& observers = messageObservers[messageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The observer has already been added.");
		observers.push_back(&observer);
	}

	void MessageLoopService::AddMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (std::size_t i = 0uz; i < messageTypes.size(); ++i)
		{
			try
			{
				AddMessageObserver(observer, messageTypes[i]);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveMessageObserver(observer, messageTypes[i]);
				}

				throw;
			}
		}
	}

	void MessageLoopService::RemoveMessageObserver(IMessageObserver& observer, const UINT messageType) noexcept
	{
		if (const auto position = messageObservers.find(messageType); position != messageObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of '{}' message type but it hadn't been added.", messageType);
	}

	void MessageLoopService::RemoveMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes) noexcept
	{
		for (const UINT messageType : messageTypes)
		{
			RemoveMessageObserver(observer, messageType);
		}
	}

	void MessageLoopService::RemoveMessageObserver(IMessageObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (std::vector<IMessageObserver*>& observers : std::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove message observer but it hadn't been added.");
	}

	IMessageLoopService& MessageLoopService::PublicMessageLoopService() noexcept
	{
		return *this;
	}

	const IMessageLoopService& MessageLoopService::PublicMessageLoopService() const noexcept
	{
		return *this;
	}

	void MessageLoopService::ObserveMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}
	}
}
