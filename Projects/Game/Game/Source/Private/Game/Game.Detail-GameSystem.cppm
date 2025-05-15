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
		const auto rootSignatureShaderParams = PonyEngine::Render::ShaderParams
		{
			.shaderPath = std::format("{}{}.cso", GAME_SHADERS_DIR, "RootSig"),
			.name = "RootSig"
		};
		const auto meshShaderParams = PonyEngine::Render::ShaderParams
		{
			.shaderPath = std::format("{}{}.cso", GAME_SHADERS_DIR, "MeshShader"),
			.name = "MeshShader"
		};
		const auto pixelShaderParams = PonyEngine::Render::ShaderParams
		{
			.shaderPath = std::format("{}{}.cso", GAME_SHADERS_DIR, "PixelShader"),
			.name = "PixelShader"
		};
		const auto rootSignatureShader = renderSystem->ShaderManager().CreateShader(rootSignatureShaderParams);
		const auto meshShader = renderSystem->ShaderManager().CreateShader(meshShaderParams);
		const auto pixelShader = renderSystem->ShaderManager().CreateShader(pixelShaderParams);

		const auto rootSignatureParams = PonyEngine::Render::RootSignatureParams
		{
			.shader = rootSignatureShader,
			.slots =
			{
				std::string(PonyEngine::Render::DataTypes::Data),
				"Meshlets",
				"Positions",
				"Color",
				"Filter"
			},
			.name = "RootSig"
		};
		const auto rootSignature = renderSystem->RootSignatureManager().CreateRootSignature(rootSignatureParams);

		const auto opaquePipelineStateParams = PonyEngine::Render::PipelineStateParams
		{
			.rootSignature = rootSignature,
			.meshShader = meshShader,
			.pixelShader = pixelShader,
			.blend = PonyEngine::Render::OpaqueBlend{},
			.rasterizer = PonyEngine::Render::Rasterizer{},
			.depthStencil = PonyEngine::Render::DepthStencil{},
			.renderQueue = static_cast<std::int32_t>(PonyEngine::Render::RenderQueue::Opaque),
			.name = "Opaque"
		};
		const auto transparentPipelineStateParams = PonyEngine::Render::PipelineStateParams
		{
			.rootSignature = rootSignature,
			.meshShader = meshShader,
			.pixelShader = pixelShader,
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
			.renderQueue = static_cast<std::int32_t>(PonyEngine::Render::RenderQueue::Transparent),
			.name = "Transparent"
		};
		const auto opaquePipelineState = renderSystem->PipelineStateManager().CreatePipelineState(opaquePipelineStateParams);
		const auto transparentPipelineState = renderSystem->PipelineStateManager().CreatePipelineState(transparentPipelineStateParams);

		const auto filterTextureParams = PonyEngine::Render::TextureParams
		{
			.dimension = PonyEngine::Render::TextureDimension::Texture1D,
			.format = PonyEngine::Render::TextureFormat::R8G8B8A8_Unorm,
			.width = 3u,
			.height = 1u,
			.depth = 1u
		};
		auto filterTexture = renderSystem->TextureManager().CreateTexture(filterTextureParams);
		filterTexture->Color(PonyMath::Color::RGBA<float>::Predefined::Red, 0u);
		filterTexture->Color(PonyMath::Color::RGBA<float>::Predefined::Yellow, 1u);
		filterTexture->Color(PonyMath::Color::RGBA<float>::Predefined::Blue, 2u);

		auto greenOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "GreenOpaque"
		};
		greenOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		greenOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>> { filterTexture };
		auto whiteOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "WhiteOpaque"
		};
		whiteOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		whiteOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto yellowOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "YellowOpaque"
		};
		yellowOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		yellowOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto cyanOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "CyanOpaque"
		};
		cyanOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		cyanOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto blueOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "BlueOpaque"
		};
		blueOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		blueOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto magentaOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "MagentaOpaque"
		};
		magentaOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		magentaOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto redOpaqueMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = opaquePipelineState,
			.name = "RedOpaque"
		};
		redOpaqueMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		redOpaqueMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto redTransparentMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = transparentPipelineState,
			.name = "RedTransparent"
		};
		redTransparentMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		redTransparentMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto greenTransparentMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = transparentPipelineState,
			.name = "GreenTransparent"
		};
		greenTransparentMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		greenTransparentMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto blueTransparentMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = transparentPipelineState,
			.name = "BlueTransparent"
		};
		blueTransparentMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		blueTransparentMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };
		auto yellowTransparentMaterialParams = PonyEngine::Render::MaterialParams
		{
			.pipelineState = transparentPipelineState,
			.name = "YellowTransparent"
		};
		yellowTransparentMaterialParams.data["Color"] = std::vector{ PonyBase::Container::BufferParams(sizeof(PonyMath::Color::RGBA<float>), 1) };
		yellowTransparentMaterialParams.textures["Filter"] = std::vector<std::shared_ptr<const PonyEngine::Render::ITexture>>{ filterTexture };

		const auto greenOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(greenOpaqueMaterialParams);
		greenOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Green);
		const auto whiteOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(whiteOpaqueMaterialParams);
		whiteOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::White);
		const auto yellowOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(yellowOpaqueMaterialParams);
		yellowOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Yellow);
		const auto cyanOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(cyanOpaqueMaterialParams);
		cyanOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Cyan);
		const auto blueOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(blueOpaqueMaterialParams);
		blueOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Blue);
		const auto magentaOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(magentaOpaqueMaterialParams);
		magentaOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Magenta);
		const auto redOpaqueMaterial = renderSystem->MaterialManager().CreateMaterial(redOpaqueMaterialParams);
		redOpaqueMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Red);
		const auto redTransparentMaterial = renderSystem->MaterialManager().CreateMaterial(redTransparentMaterialParams);
		redTransparentMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Red);
		const auto greenTransparentMaterial = renderSystem->MaterialManager().CreateMaterial(greenTransparentMaterialParams);
		greenTransparentMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Green);
		const auto blueTransparentMaterial = renderSystem->MaterialManager().CreateMaterial(blueTransparentMaterialParams);
		blueTransparentMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Blue);
		const auto yellowTransparentMaterial = renderSystem->MaterialManager().CreateMaterial(yellowTransparentMaterialParams);
		yellowTransparentMaterial->Element(0u, 0u, 0u, PonyMath::Color::RGBA<float>::Predefined::Yellow);

		const auto boxMeshlets = std::array
		{
			PonyShader::Mesh::Meshlet(0u, 0u, 7u, 6u),
			PonyShader::Mesh::Meshlet(7u, 0u, 7u, 6u)
		};
		const auto pyramidMeshlets = std::array
		{
			PonyShader::Mesh::Meshlet(0u, 0u, 5u, 6u)
		};
		const auto boxVertexIndices = std::array<std::uint32_t, 14>
		{
			0u, 1u, 2u, 3u, 4u, 5u, 7u, 6u, 5u, 4u, 7u, 2u, 1u, 3u
		};
		const auto pyramidVertexIndices = std::array
		{
			0u, 1u, 2u, 3u, 4u
		};
		const auto boxTriangles = std::array
		{
			PonyShader::Mesh::Primitive(0u, 1u, 2u),
			PonyShader::Mesh::Primitive(0u, 2u, 3u),
			PonyShader::Mesh::Primitive(0u, 4u, 5u),
			PonyShader::Mesh::Primitive(0u, 5u, 1u),
			PonyShader::Mesh::Primitive(0u, 6u, 4u),
			PonyShader::Mesh::Primitive(0u, 3u, 6u)
		};
		const auto pyramidTriangles = std::array
		{
			PonyShader::Mesh::Primitive(0u, 1u, 2u),
			PonyShader::Mesh::Primitive(0u, 2u, 3u),
			PonyShader::Mesh::Primitive(0u, 3u, 4u),
			PonyShader::Mesh::Primitive(0u, 4u, 1u),
			PonyShader::Mesh::Primitive(1u, 3u, 2u),
			PonyShader::Mesh::Primitive(1u, 4u, 3u)
		};
		const auto boxPositions = std::array
		{
			PonyMath::Core::Vector3<float>(-1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, 1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f)
		};
		const auto pyramidPositions = std::array
		{
			PonyMath::Core::Vector3<float>(0.f, 1.f, 0.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, -1.f),
			PonyMath::Core::Vector3<float>(-1.f, -1.f, 1.f),
			PonyMath::Core::Vector3<float>(1.f, -1.f, 1.f),
		};

		auto boxMeshParams = PonyEngine::Render::MeshParams{};
		boxMeshParams.data["Meshlets"] = std::vector
		{
			PonyBase::Container::BufferParams{.stride = sizeof(PonyShader::Mesh::Meshlet), .count = boxMeshlets.size()},
			PonyBase::Container::BufferParams{.stride = sizeof(std::uint32_t), .count = boxVertexIndices.size()},
			PonyBase::Container::BufferParams{.stride = sizeof(PonyShader::Mesh::Primitive), .count = boxTriangles.size()}
		};
		boxMeshParams.data["Positions"] = std::vector
		{
			PonyBase::Container::BufferParams{.stride = sizeof(PonyMath::Core::Vector3<float>), .count = boxPositions.size()}
		};
		boxMeshParams.threadGroupCounts = { 2u, 1u, 1u };
		boxMeshParams.boundingBox = PonyMath::Shape::CreateBoundingBox(std::span<const PonyMath::Core::Vector3<float>>(boxPositions));
		boxMeshParams.name = "Box";
		auto pyramidMeshParams = PonyEngine::Render::MeshParams{};
		pyramidMeshParams.data["Meshlets"] = std::vector
		{
			PonyBase::Container::BufferParams{.stride = sizeof(PonyShader::Mesh::Meshlet), .count = pyramidMeshlets.size()},
			PonyBase::Container::BufferParams{.stride = sizeof(std::uint32_t), .count = pyramidVertexIndices.size()},
			PonyBase::Container::BufferParams{.stride = sizeof(PonyShader::Mesh::Primitive), .count = pyramidTriangles.size()}
		};
		pyramidMeshParams.data["Positions"] = std::vector
		{
			PonyBase::Container::BufferParams{.stride = sizeof(PonyMath::Core::Vector3<float>), .count = pyramidPositions.size()}
		};
		pyramidMeshParams.threadGroupCounts = { 1u, 1u, 1u };
		pyramidMeshParams.boundingBox = PonyMath::Shape::CreateBoundingBox(std::span<const PonyMath::Core::Vector3<float>>(pyramidPositions));
		pyramidMeshParams.name = "Pyramid";
		const auto boxMesh = renderSystem->MeshManager().CreateMesh(boxMeshParams);
		const auto pyramidMesh = renderSystem->MeshManager().CreateMesh(pyramidMeshParams);

		boxMesh->Data<PonyShader::Mesh::Meshlet>(0u, 0u, boxMeshlets);
		boxMesh->Data<std::uint32_t>(0u, 1u, boxVertexIndices);
		boxMesh->Data<PonyShader::Mesh::Primitive>(0u, 2u, boxTriangles);
		boxMesh->Data<PonyMath::Core::Vector3<float>>(1u, 0u, boxPositions);

		pyramidMesh->Data<PonyShader::Mesh::Meshlet>(0u, 0u, pyramidMeshlets);
		pyramidMesh->Data<std::uint32_t>(0u, 1u, pyramidVertexIndices);
		pyramidMesh->Data<PonyShader::Mesh::Primitive>(0u, 2u, pyramidTriangles);
		pyramidMesh->Data<PonyMath::Core::Vector3<float>>(1u, 0u, pyramidPositions);

		floor = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = greenOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>::Predefined::Zero, PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(10.f, 0.1f, 10.f)),
			.name = "Floor"
		});
		centralColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = whiteOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(0.f, 2.5f, 0.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(-1.f, 5.f, 1.f)),
			.name = "CentralColumn"
		});
		leftNearColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = yellowOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-8.f, 6.f, -8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "LeftNearColumn"
		});
		leftFarColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = cyanOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-8.f, 6.f, 8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "LeftFarColumn"
		});
		rightFarColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = blueOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(8.f, 6.f, 8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "RightFarColumn"
		});
		rightNearColumn = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = magentaOpaqueMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(8.f, 6.f, -8.f), PonyMath::Core::Quaternion<float>::Predefined::Identity, PonyMath::Core::Vector3<float>(1.f, 8.f, 1.f)),
			.name = "RightNearColumn"
		});
		pyramid = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = redOpaqueMaterial,
			.mesh = pyramidMesh,
			.modelMatrix = pyramidTransform.TrsMatrix(),
			.name = "Pyramid"
		});
		leftNearGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = redTransparentMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-5.f, 4.f, -5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 45.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "LeftNearGlass"
		});
		leftFarGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = greenTransparentMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(-5.f, 4.f, 5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 135.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "LeftFarGlass"
		});
		rightFarGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = blueTransparentMaterial,
			.mesh = boxMesh,
			.modelMatrix = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3<float>(5.f, 4.f, 5.f), PonyMath::Core::Vector3<float>::Predefined::Up, 225.f * PonyMath::Core::DegToRad<float>, PonyMath::Core::Vector3<float>(6.f, 6.f, 0.1f)),
			.name = "RightFarGlass"
		});
		rightNearGlass = renderSystem->RenderObjectManager().CreateObject(PonyEngine::Render::RenderObjectParams
		{
			.material = yellowTransparentMaterial,
			.mesh = boxMesh,
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
