module;

#include "PonyEngine/Log/Log.h"

export module Game:GameService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.RawInput;
import PonyEngine.Surface;

export namespace Game
{
	class GameService final : public PonyEngine::Application::IService, private PonyEngine::RawInput::IRawInputObserver
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplicationContext& application) noexcept;
		GameService(const GameService&) = delete;
		GameService(GameService&&) = delete;

		~GameService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		GameService& operator =(const GameService&) = delete;
		GameService& operator =(GameService&&) = delete;

	private:
		virtual void OnRawInput(PonyEngine::RawInput::DeviceHandle, const PonyEngine::RawInput::RawInputEvent& inputEvent) override;

		void ChangeStyle();
		void Move(const PonyEngine::Math::Vector2<std::int32_t>& deltaPos, const PonyEngine::Math::Vector2<std::int32_t>& deltaSize);

		PonyEngine::Math::Vector2<std::int32_t> defaultPosition;
		PonyEngine::Math::Vector2<std::int32_t> defaultSize;

		std::int32_t moveSpeed;

		PonyEngine::Application::IApplicationContext* application;
		PonyEngine::RawInput::IRawInputService* input;
		PonyEngine::Surface::ISurfaceService* surface;

		PonyEngine::RawInput::AxisID fullscreenSwitchAxis;
		PonyEngine::RawInput::AxisID moveLeftAxis;
		PonyEngine::RawInput::AxisID moveRightAxis;
		PonyEngine::RawInput::AxisID moveDownAxis;
		PonyEngine::RawInput::AxisID moveUpAxis;
		PonyEngine::RawInput::AxisID sizeLeftAxis;
		PonyEngine::RawInput::AxisID sizeRightAxis;
		PonyEngine::RawInput::AxisID sizeDownAxis;
		PonyEngine::RawInput::AxisID sizeUpAxis;
		PonyEngine::RawInput::AxisID titleAxis;
		PonyEngine::RawInput::AxisID cursorVisibilityAxis;
		PonyEngine::RawInput::AxisID cursorClippingAxis;
		PonyEngine::RawInput::AxisID reportPositionsAxis;
	};
}

namespace Game
{
	GameService::GameService(PonyEngine::Application::IApplicationContext& application) noexcept :
		defaultPosition(100, 160),
		defaultSize(320, 240),
		moveSpeed{30},
		application{&application},
		input{&this->application->GetService<PonyEngine::RawInput::IRawInputService>()},
		surface{&this->application->GetService<PonyEngine::Surface::ISurfaceService>()}
	{
		surface->MinimalSize(defaultSize);
	}

	GameService::~GameService() noexcept
	{
	}

	void GameService::Begin()
	{
		fullscreenSwitchAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainSpacePath));
		moveLeftAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::ArrowLeftPath));
		moveRightAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::ArrowRightPath));
		moveDownAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::ArrowDownPath));
		moveUpAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::ArrowUpPath));
		sizeLeftAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::Numpad4Path));
		sizeRightAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::Numpad6Path));
		sizeDownAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::Numpad2Path));
		sizeUpAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::Numpad8Path));
		titleAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainTPath));
		cursorVisibilityAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainVPath));
		cursorClippingAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainCPath));
		reportPositionsAxis = input->Hash(PonyEngine::RawInput::Axis(PonyEngine::RawInput::KeyboardLayout::MainRPath));

		input->AddObserver(*this);
	}

	void GameService::End()
	{
		input->RemoveObserver(*this);
	}

	void GameService::OnRawInput(PonyEngine::RawInput::DeviceHandle, const PonyEngine::RawInput::RawInputEvent& inputEvent)
	{
		auto deltaPos = PonyEngine::Math::Vector2<std::int32_t>::Zero();
		auto deltaSize = PonyEngine::Math::Vector2<std::int32_t>::Zero();

		for (std::size_t i = 0uz; i < inputEvent.axes.size(); ++i)
		{
			if (!inputEvent.values[i])
			{
				continue;
			}

			if (inputEvent.axes[i] == fullscreenSwitchAxis)
			{
				ChangeStyle();
			}
			else if (inputEvent.axes[i] == moveLeftAxis)
			{
				deltaPos.X() -= 1;
			}
			else if (inputEvent.axes[i] == moveRightAxis)
			{
				deltaPos.X() += 1;
			}
			else if (inputEvent.axes[i] == moveDownAxis)
			{
				deltaPos.Y() += 1;
			}
			else if (inputEvent.axes[i] == moveUpAxis)
			{
				deltaPos.Y() -= 1;
			}
			else if (inputEvent.axes[i] == sizeLeftAxis)
			{
				deltaSize.X() -= 1;
			}
			else if (inputEvent.axes[i] == sizeRightAxis)
			{
				deltaSize.X() += 1;
			}
			else if (inputEvent.axes[i] == sizeDownAxis)
			{
				deltaSize.Y() += 1;
			}
			else if (inputEvent.axes[i] == sizeUpAxis)
			{
				deltaSize.Y() -= 1;
			}
			else if (inputEvent.axes[i] == titleAxis)
			{
				surface->Title(std::format("Test. Cursor Visibility: {}; Cursor position: {}", surface->IsCursorVisible(), surface->CursorPosition()));
				PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Info, "Title changed to '{}'.", surface->Title());
			}
			else if (inputEvent.axes[i] == cursorVisibilityAxis)
			{
				surface->CursorVisibility(!surface->CursorVisibility());
			}
			else if (inputEvent.axes[i] == cursorClippingAxis)
			{
				surface->CursorClippingRect(surface->CursorClippingRect() ? std::optional<PonyEngine::Math::CornerRect<float>>(std::nullopt) : PonyEngine::Math::CornerRect<float>(PonyEngine::Math::Vector2<float>::One()));
			}
			else if (inputEvent.axes[i] == reportPositionsAxis)
			{
				PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Info, "ClientToScreen: '{}'; ScreenToClient: '{}'.", 
					surface->ClientToScreen(PonyEngine::Math::Vector2<int>::Zero()), surface->ScreenToClient(surface->CursorPosition()));
			}
		}

		if (!deltaPos.IsZero() || !deltaSize.IsZero())
		{
			deltaPos *= moveSpeed;
			deltaSize *= moveSpeed;
			Move(deltaPos, deltaSize);
		}
	}

	void GameService::ChangeStyle()
	{
		if (std::holds_alternative<PonyEngine::Surface::FullscreenRectStyle>(surface->RectStyle()))
		{
			surface->RectStyle(PonyEngine::Surface::WindowRectStyle{.resizable = true});
			surface->ClientRect(PonyEngine::Math::CornerRect<std::int32_t>(defaultPosition, defaultSize));
		}
		else
		{
			surface->RectStyle(PonyEngine::Surface::FullscreenRectStyle{});
		}
	}

	void GameService::Move(const PonyEngine::Math::Vector2<std::int32_t>& deltaPos, const PonyEngine::Math::Vector2<std::int32_t>& deltaSize)
	{
		PonyEngine::Math::CornerRect<std::int32_t> rect = surface->ClientRect();
		rect.Position(rect.Position() + deltaPos);
		rect.Size(rect.Size() + deltaSize);
		surface->ClientRect(rect);
	}
}
