/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module Game.Detail:GameSystem;

import <array>;
import <cstdint>;
import <format>;
import <functional>;
import <memory>;
import <span>;
import <stdexcept>;

import PonyBase.Container;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Space;

import PonyShader.Core;
import PonyShader.Mesh;
import PonyShader.Space;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Render;
import PonyEngine.Time;

import Game;

export namespace Game
{
	/// @brief Game system.
	class GameSystem final : public PonyEngine::Core::TickableSystem, public IGameSystem
	{
	public:
		/// @brief Creates a game system.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param gameParams Game system parameters.
		[[nodiscard("Pure constructor")]]
		explicit GameSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& systemParams, const GameSystemParams& gameParams);
		GameSystem(const GameSystem&) = delete;
		GameSystem(GameSystem&&) = delete;

		virtual ~GameSystem() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		GameSystem& operator =(const GameSystem&) = delete;
		GameSystem& operator =(GameSystem&&) = delete;

	private:
		PonyEngine::Input::IInputSystem* inputSystem;
		PonyEngine::Render::IRenderSystem* renderSystem;
		PonyEngine::Time::ITimeSystem* timeSystem;

		std::shared_ptr<PonyEngine::Input::IInputReceiver> resetHandle;
		std::shared_ptr<PonyEngine::Input::IInputReceiver> exitHandle;

		std::shared_ptr<PonyEngine::Render::IRenderObject> floor;
		std::shared_ptr<PonyEngine::Render::IRenderObject> centralColumn;
		std::shared_ptr<PonyEngine::Render::IRenderObject> leftNearColumn;
		std::shared_ptr<PonyEngine::Render::IRenderObject> leftFarColumn;
		std::shared_ptr<PonyEngine::Render::IRenderObject> rightFarColumn;
		std::shared_ptr<PonyEngine::Render::IRenderObject> rightNearColumn;
		std::shared_ptr<PonyEngine::Render::IRenderObject> pyramid;
		std::shared_ptr<PonyEngine::Render::IRenderObject> leftNearGlass;
		std::shared_ptr<PonyEngine::Render::IRenderObject> leftFarGlass;
		std::shared_ptr<PonyEngine::Render::IRenderObject> rightFarGlass;
		std::shared_ptr<PonyEngine::Render::IRenderObject> rightNearGlass;

		PonyMath::Space::Transform3D<float> pyramidTransform;

		PonyMath::Space::Transform3D<float> cameraTransform;
		std::shared_ptr<PonyEngine::Render::ICamera> camera;
	};
}

namespace Game
{
	GameSystem::GameSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& systemParams, const GameSystemParams&) :
		TickableSystem(engine, systemParams),
		inputSystem{nullptr},
		renderSystem{nullptr},
		timeSystem{nullptr},
		pyramidTransform(PonyMath::Core::Vector3<float>(0.f, 9.f, 0.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One),
		cameraTransform(PonyMath::Core::Vector3<float>(0.f, 5.f, -25.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>::Predefined::One)
	{
	}

	void GameSystem::Begin()
	{
		inputSystem = Engine().SystemManager().FindSystem<PonyEngine::Input::IInputSystem>();
		if (!inputSystem)
		{
			throw std::logic_error("Failed to get input system.");
		}
		renderSystem = Engine().SystemManager().FindSystem<PonyEngine::Render::IRenderSystem>();
		if (!renderSystem)
		{
			throw std::logic_error("Failed to get render system");
		}
		timeSystem = Engine().SystemManager().FindSystem<PonyEngine::Time::ITimeSystem>();
		if (!timeSystem)
		{
			throw std::logic_error("Failed to find time system");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Register inputs.");
		(resetHandle = inputSystem->CreateReceiver("Reset"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { cameraTransform.Position() = PonyMath::Core::Vector3<float>::Predefined::Zero; cameraTransform.Rotation() = PonyMath::Core::Quaternion<float>::Predefined::Identity; cameraTransform.Scale() = PonyMath::Core::Vector3<float>::Predefined::One; })));
		(exitHandle = inputSystem->CreateReceiver("Exit"))->Action(PonyEngine::Input::FloatToBoolAction(PonyEngine::Input::BoolToEventAction([&] { Engine().Stop(); }, false)));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Inputs registered.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set render view params.");
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render view params set.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create render objects.");
		const auto opaquePipelineStateParams = PonyEngine::Render::PipelineStateParams
		{
			.rootSignatureShader = std::format("{}{}", GAME_SHADERS_DIR, "RootSig"),
			.meshShader = std::format("{}{}", GAME_SHADERS_DIR, "MeshShader"),
			.pixelShader = std::format("{}{}", GAME_SHADERS_DIR, "PixelShader"),
			.blend = PonyEngine::Render::OpaqueBlend{},
			.rasterizer = PonyEngine::Render::Rasterizer{},
			.depthStencil = PonyEngine::Render::DepthStencil{},
			.dataSlots =
			{
				{ std::string(PonyEngine::Render::DataTypes::Data), 0u },
				{ "Meshlets", 1u },
				{ "Positions", 2u },
				{ "Colors", 3u }
			},
			.renderQueue = static_cast<std::int32_t>(PonyEngine::Render::RenderQueue::Opaque),
			.name = "Opaque"
		};
		const auto transparentPipelineStateParams = PonyEngine::Render::PipelineStateParams
		{
			.rootSignatureShader = std::format("{}{}", GAME_SHADERS_DIR, "RootSig"),
			.meshShader = std::format("{}{}", GAME_SHADERS_DIR, "MeshShader"),
			.pixelShader = std::format("{}{}", GAME_SHADERS_DIR, "PixelShader"),
			.blend = PonyEngine::Render::TransparentBlend
			{
				.sourceBlend = PonyEngine::Render::BlendFactor::AlphaSource,
				.destinationBlend = PonyEngine::Render::BlendFactor::AlphaSourceInverse,
				.blendOperation = PonyEngine::Render::BlendOperation::Add,
				.sourceBlendAlpha = PonyEngine::Render::BlendFactor::One,
				.destinationBlendAlpha = PonyEngine::Render::BlendFactor::AlphaSourceInverse,
				.blendOperationAlpha = PonyEngine::Render::BlendOperation::Add
			},
			.rasterizer = PonyEngine::Render::Rasterizer{},
			.depthStencil = PonyEngine::Render::DepthStencil
			{
				.depthWrite = false
			},
			.dataSlots =
			{
				{ std::string(PonyEngine::Render::DataTypes::Data), 0u },
				{ "Meshlets", 1u },
				{ "Positions", 2u },
				{ "Colors", 3u }
			},
			.renderQueue = static_cast<std::int32_t>(PonyEngine::Render::RenderQueue::Transparent),
			.name = "Transparent"
		};
		const auto opaquePipelineState = std::make_shared<PonyEngine::Render::PipelineState>(opaquePipelineStateParams);
		const auto transparentPipelineState = std::make_shared<PonyEngine::Render::PipelineState>(transparentPipelineStateParams);

		const auto boxMeshlets = PonyBase::Container::Buffer::Create<PonyShader::Mesh::Meshlet>(std::array
		{
			PonyShader::Mesh::Meshlet(0u, 0u, 7u, 6u),
			PonyShader::Mesh::Meshlet(7u, 0u, 7u, 6u)
		});
		const auto pyramidMeshlets = PonyBase::Container::Buffer::Create<PonyShader::Mesh::Meshlet>(std::array
		{
			PonyShader::Mesh::Meshlet(0u, 0u, 5u, 6u)
		});
		const auto boxVertexIndices = PonyBase::Container::Buffer::Create<std::uint32_t>(std::array
		{
			0u, 1u, 2u, 3u, 4u, 5u, 7u, 6u, 5u, 4u, 7u, 2u, 1u, 3u
		});
		const auto pyramidVertexIndices = PonyBase::Container::Buffer::Create<std::uint32_t>(std::array
		{
			0u, 1u, 2u, 3u, 4u
		});
		const auto boxTriangles = PonyBase::Container::Buffer::Create<PonyShader::Mesh::Primitive>(std::array
		{
			PonyShader::Mesh::Primitive(0u, 1u, 2u),
			PonyShader::Mesh::Primitive(0u, 2u, 3u),
			PonyShader::Mesh::Primitive(0u, 4u, 5u),
			PonyShader::Mesh::Primitive(0u, 5u, 1u),
			PonyShader::Mesh::Primitive(0u, 6u, 4u),
			PonyShader::Mesh::Primitive(0u, 3u, 6u)
		});
		const auto pyramidTriangles = PonyBase::Container::Buffer::Create<PonyShader::Mesh::Primitive>(std::array
		{
			PonyShader::Mesh::Primitive(0u, 1u, 2u),
			PonyShader::Mesh::Primitive(0u, 2u, 3u),
			PonyShader::Mesh::Primitive(0u, 3u, 4u),
			PonyShader::Mesh::Primitive(0u, 4u, 1u),
			PonyShader::Mesh::Primitive(1u, 3u, 2u),
			PonyShader::Mesh::Primitive(1u, 4u, 3u)
		});
		const auto boxPositions = PonyBase::Container::Buffer::Create<PonyMath::Core::Vector3<float>>(std::array
		{
			PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f)
		});
		const auto pyramidPositions = PonyBase::Container::Buffer::Create<PonyMath::Core::Vector3<float>>(std::array
		{
			PonyMath::Core::Vector3<float>(0.f, 1.f, 0.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f),
		});
		const auto floorColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array // TODO: Change to a data number
		{
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green,
			PonyMath::Color::RGBA<float>::Predefined::Green
		});
		const auto centralColumnColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White,
			PonyMath::Color::RGBA<float>::Predefined::White
		});
		const auto leftNearColumnColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow,
			PonyMath::Color::RGBA<float>::Predefined::Yellow
		});
		const auto leftFarColumnColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan,
			PonyMath::Color::RGBA<float>::Predefined::Cyan
		});
		const auto rightFarColumnColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue,
			PonyMath::Color::RGBA<float>::Predefined::Blue
		});
		const auto rightNearColumnColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta,
			PonyMath::Color::RGBA<float>::Predefined::Magenta
		});
		const auto pyramidColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>::Predefined::Red,
			PonyMath::Color::RGBA<float>::Predefined::Red,
			PonyMath::Color::RGBA<float>::Predefined::Red,
			PonyMath::Color::RGBA<float>::Predefined::Red,
			PonyMath::Color::RGBA<float>::Predefined::Red,
		});
		const auto leftNearGlassColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f),
			PonyMath::Color::RGBA<float>(1.f, 0.f, 0.f, 0.2f)
			
		});
		const auto leftFarGlassColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f),
			PonyMath::Color::RGBA<float>(0.f, 1.f, 0.f, 0.1f)
		});
		const auto rightFarGlassColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f),
			PonyMath::Color::RGBA<float>(0.f, 0.f, 1.f, 0.3f)
		});
		const auto rightNearGlassColors = PonyBase::Container::Buffer::Create<PonyMath::Color::RGBA<float>>(std::array
		{
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f),
			PonyMath::Color::RGBA<float>(1.f, 1.f, 0.f, 0.15f)
		});
		auto floorMeshParams = PonyEngine::Render::MeshParams{};
		floorMeshParams.bufferTables["Meshlets"] = std::vector<PonyBase::Container::Buffer>{ boxMeshlets, boxVertexIndices, boxTriangles };
		floorMeshParams.bufferTables["Positions"] = std::vector<PonyBase::Container::Buffer>{ boxPositions };
		floorMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ floorColors };
		floorMeshParams.threadGroupCounts = { 2u, 1u, 1u };
		floorMeshParams.boundingBox = PonyMath::Shape::CreateBoundingBox(boxPositions.Span<PonyMath::Core::Vector3<float>>());
		floorMeshParams.name = "Floor";
		auto centralColumnMeshParams = floorMeshParams;
		centralColumnMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ centralColumnColors };
		centralColumnMeshParams.name = "CentralColumn";
		auto leftNearColumnMeshParams = floorMeshParams;
		leftNearColumnMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ leftNearColumnColors };
		leftNearColumnMeshParams.name = "LeftNearColumn";
		auto leftFarColumnMeshParams = floorMeshParams;
		leftFarColumnMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ leftFarColumnColors };
		leftFarColumnMeshParams.name = "LeftFarColumn";
		auto rightFarColumnMeshParams = floorMeshParams;
		rightFarColumnMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ rightFarColumnColors };
		rightFarColumnMeshParams.name = "RightFarColumn";
		auto rightNearColumnMeshParams = floorMeshParams;
		rightNearColumnMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ rightNearColumnColors };
		rightNearColumnMeshParams.name = "RightNearColumn";
		auto pyramidMeshParams = PonyEngine::Render::MeshParams{};
		pyramidMeshParams.bufferTables["Meshlets"] = std::vector<PonyBase::Container::Buffer>{ pyramidMeshlets, pyramidVertexIndices, pyramidTriangles };
		pyramidMeshParams.bufferTables["Positions"] = std::vector<PonyBase::Container::Buffer>{ pyramidPositions };
		pyramidMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ pyramidColors };
		pyramidMeshParams.threadGroupCounts = { 1u, 1u, 1u };
		pyramidMeshParams.boundingBox = PonyMath::Shape::CreateBoundingBox(pyramidPositions.Span<PonyMath::Core::Vector3<float>>());
		pyramidMeshParams.name = "Pyramid";
		auto leftNearGlassMeshParams = floorMeshParams;
		leftNearGlassMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ leftNearGlassColors };
		leftNearGlassMeshParams.name = "LeftNearGlass";
		auto leftFarGlassMeshParams = floorMeshParams;
		leftFarGlassMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ leftFarGlassColors };
		leftFarGlassMeshParams.name = "LeftFarGlass";
		auto rightFarGlassMeshParams = floorMeshParams;
		rightFarGlassMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ rightFarGlassColors };
		rightFarGlassMeshParams.name = "RightFarGlass";
		auto rightNearGlassMeshParams = floorMeshParams;
		rightNearGlassMeshParams.bufferTables["Colors"] = std::vector<PonyBase::Container::Buffer>{ rightNearGlassColors };
		rightNearGlassMeshParams.name = "RightNearGlass";
		const auto floorMesh = std::make_shared<PonyEngine::Render::Mesh>(floorMeshParams);
		const auto centralColumnMesh = std::make_shared<PonyEngine::Render::Mesh>(centralColumnMeshParams);
		const auto leftNearColumnMesh = std::make_shared<PonyEngine::Render::Mesh>(leftNearColumnMeshParams);
		const auto leftFarColumnMesh = std::make_shared<PonyEngine::Render::Mesh>(leftFarColumnMeshParams);
		const auto rightFarColumnMesh = std::make_shared<PonyEngine::Render::Mesh>(rightFarColumnMeshParams);
		const auto rightNearColumnMesh = std::make_shared<PonyEngine::Render::Mesh>(rightNearColumnMeshParams);
		const auto pyramidMesh = std::make_shared<PonyEngine::Render::Mesh>(pyramidMeshParams);
		const auto leftNearGlassMesh = std::make_shared<PonyEngine::Render::Mesh>(leftNearGlassMeshParams);
		const auto leftFarGlassMesh = std::make_shared<PonyEngine::Render::Mesh>(leftFarGlassMeshParams);
		const auto rightFarGlassMesh = std::make_shared<PonyEngine::Render::Mesh>(rightFarGlassMeshParams);
		const auto rightNearGlassMesh = std::make_shared<PonyEngine::Render::Mesh>(rightNearGlassMeshParams);

		floor = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = floorMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>::Predefined::Zero, PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(10.f, 0.1f, 10.f)),
			.name = "Floor"
		});
		centralColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = centralColumnMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 2.5f, 0.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(-1.f, 5.f, 1.f)),
			.name = "CentralColumn"
		});
		leftNearColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = leftNearColumnMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-8.f, 6.f, -8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "LeftNearColumn"
		});
		leftFarColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = leftFarColumnMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-8.f, 6.f, 8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "LeftFarColumn"
		});
		rightFarColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = rightFarColumnMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(8.f, 6.f, 8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "RightFarColumn"
		});
		rightNearColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = rightNearColumnMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(8.f, 6.f, -8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "RightNearColumn"
		});
		pyramid = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = opaquePipelineState,
			.mesh = pyramidMesh,
			.modelMatrix = pyramidTransform.TrsMatrix(),
			.name = "Pyramid"
		});
		leftNearGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = transparentPipelineState,
			.mesh = leftNearGlassMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-5.f, 4.f, -5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 45.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "LeftNearGlass"
		});
		leftFarGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = transparentPipelineState,
			.mesh = leftFarGlassMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-5.f, 4.f, 5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 135.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "LeftFarGlass"
		});
		rightFarGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = transparentPipelineState,
			.mesh = rightFarGlassMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(5.f, 4.f, 5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 225.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "RightFarGlass"
		});
		rightNearGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.pipelineState = transparentPipelineState,
			.mesh = rightNearGlassMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(5.f, 4.f, -5.f), PonyMath::Core::Vector3<float>::Predefined::Up, -45.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "RightNearGlass"
		});
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Render objects created.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Create camera.");

		camera = renderSystem->CameraManager().CreateCamera(PonyEngine::Render::CameraParams
		{
			.viewMatrix = cameraTransform.TrsMatrix()
		});
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Camera created.");
	}

	void GameSystem::End()
	{
	}

	void GameSystem::Tick()
	{
		pyramidTransform.Rotate(PonyMath::Core::RotationQuaternion(pyramidTransform.Up(), 1.f * timeSystem->VirtualDeltaTime()));
		pyramid->ModelMatrix(pyramidTransform.TrsMatrix());

		const auto rotation = PonyMath::Core::RotationQuaternion(cameraTransform.Forward(), inputSystem->State("Rotate") * (0.5f * timeSystem->VirtualDeltaTime())) *
			PonyMath::Core::RotationQuaternion(cameraTransform.Right(), inputSystem->State("MouseY")) * PonyMath::Core::RotationQuaternion(cameraTransform.Up(), inputSystem->State("MouseX"));
		cameraTransform.Rotate(rotation);

		auto moveDirection = PonyMath::Core::Vector3<float>(inputSystem->State("Right"), inputSystem->State("Up"), inputSystem->State("Forward"));
		cameraTransform.Translate(cameraTransform.Rotation() * (moveDirection.Normalized(PonyMath::Core::Vector3<float>::Predefined::Zero) * (10.f * timeSystem->VirtualDeltaTime())));

		camera->ViewMatrix(cameraTransform.TrsMatrix().Inverse());
	}
}
