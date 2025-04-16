/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "cassert"

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:MaterialManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;
import <variant>;
import <vector>;

import PonyDebug.Log;

import :FrameParams;
import :IGraphicsPipeline;
import :IMaterialManager;
import :IMeshManager;
import :ISubSystemContext;
import :Material;
import :PipelineStateUtility;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class MaterialManager final : public IMaterialManager
	{
	public:
		/// @brief Creates a @p MaterialManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit MaterialManager(ISubSystemContext& d3d12System) noexcept;
		MaterialManager(const MaterialManager&) = delete;
		MaterialManager(MaterialManager&&) = delete;

		~MaterialManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<const Render::Material>& material) override;

		void Tick();

		/// @brief Cleans out of dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		class MaterialObserver final : public IMaterialObserver
		{
		public:
			[[nodiscard("Pure constructor")]]
			MaterialObserver() noexcept;
			MaterialObserver(const MaterialObserver&) = delete;
			MaterialObserver(MaterialObserver&&) = delete;

			~MaterialObserver() noexcept = default;

			virtual void OnRootSignatureShaderChanged() noexcept override;
			virtual void OnAmplificationShaderChanged() noexcept override;
			virtual void OnMeshShaderChanged() noexcept override;
			virtual void OnPixelShaderChanged() noexcept override;
			virtual void OnBlendChanged() noexcept override;
			virtual void OnRasterizerChanged() noexcept override;
			virtual void OnDepthStencilChanged() noexcept override;
			virtual void OnDataSlotsChanged() noexcept override;
			virtual void OnThreadGroupCountsChanged() noexcept override;
			virtual void OnRenderQueueChanged() noexcept override;
			virtual void OnCameraCullingChanged() noexcept override;
			virtual void OnNameChanged() noexcept override;

			[[nodiscard("Pure function")]]
			bool MaterialChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool AmplificationShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool MeshShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool PixelShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool DataSlotsChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool AdditionalDataChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			void Reset() noexcept;

			MaterialObserver& operator =(const MaterialObserver&) = delete;
			MaterialObserver& operator =(MaterialObserver&&) = delete;

		private:
			bool materialChanged;
			bool amplificationShaderChanged;
			bool meshShaderChanged;
			bool pixelShaderChanged;
			bool dataSlotsChanged;
			bool additionalDataChanged;
			bool nameChanged;
		};

		struct PipelineStateStream final
		{
			PipelineStateStreamRootSignature rootSignature;
			PipelineStateStreamAmplificationShader amplificationShader;
			PipelineStateStreamMeshShader meshShader;
			PipelineStateStreamPixelShader pixelShader;
			PipelineStateStreamBlend blend;
			PipelineStateStreamSampleMask sampleMask;
			PipelineStateStreamRasterizer rasterizer;
			PipelineStateStreamDepthStencil1 depthStencil;
			PipelineStateStreamRenderTargetFormats renderTargetFormats;
			PipelineStateStreamDepthStencilFormat depthStencilFormat;
			PipelineStateStreamSampleDescription sampleDescription;
		};

		struct ShaderData final
		{
			std::shared_ptr<const Shader> amplificationShader;
			std::shared_ptr<const Shader> meshShader;
			std::shared_ptr<const Shader> pixelShader;
		};

		[[nodiscard("Pure function")]]
		static D3D12_BLEND_DESC CreateBlendDesc(const Blend& blend) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateOpaqueBlendDesc(const OpaqueBlend& blend) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateTransparentBlendDesc(const TransparentBlend& blend) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateLogicBlendDesc(const LogicBlend& blend) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_BLEND GetBlendFactor(BlendFactor blendFactor) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_BLEND_OP GetBlendOperation(BlendOperation blendOperation) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_LOGIC_OP GetLogicOperation(LogicOperation logicOperation) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_RASTERIZER_DESC CreateRasterizerDesc(const Rasterizer& rasterizer) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_FILL_MODE GetFillMode(FillMode fillMode) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_CULL_MODE GetCullMode(CullMode cullMode) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_DEPTH_STENCIL_DESC1 CreateDepthStencilDesc(const DepthStencil& depthStencil) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_COMPARISON_FUNC GetComparison(ComparisonFunction comparison) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_DEPTH_STENCILOP_DESC GetDepthStencilOpDesc(const DepthStencilOperation& operation) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_STENCIL_OP GetStencilOp(StencilOperation stencilOperation) noexcept;

		void UpdateShaders(const Render::Material& source, ShaderData& shaderData, const MaterialObserver& observer) const;
		void UpdateMaterial(Material& material, const Render::Material& source, const ShaderData& shaderData, const MaterialObserver& observer) const;
		static void UpdateDataSlots(Material& material, const Render::Material& source, const MaterialObserver& observer);
		static void UpdateAdditionalData(Material& material, const Render::Material& source, const MaterialObserver& observer);
		static void UpdateName(Material& material, const Render::Material& source, const MaterialObserver& observer);

		void Add(const std::shared_ptr<Material>& material, const std::shared_ptr<const Render::Material>& source);
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.
		std::vector<std::shared_ptr<const Render::Material>> sources;
		std::vector<ShaderData> shaders;
		std::vector<std::unique_ptr<MaterialObserver>> materialObservers;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MaterialManager::MaterialObserver::MaterialObserver() noexcept :
		materialChanged{true},
		amplificationShaderChanged{true},
		meshShaderChanged{true},
		pixelShaderChanged{true},
		dataSlotsChanged{true},
		additionalDataChanged{true},
		nameChanged{true}
	{
	}

	void MaterialManager::MaterialObserver::OnRootSignatureShaderChanged() noexcept
	{
		materialChanged = true;
	}

	void MaterialManager::MaterialObserver::OnAmplificationShaderChanged() noexcept
	{
		amplificationShaderChanged = true;
	}

	void MaterialManager::MaterialObserver::OnMeshShaderChanged() noexcept
	{
		meshShaderChanged = true;
	}

	void MaterialManager::MaterialObserver::OnPixelShaderChanged() noexcept
	{
		pixelShaderChanged = true;
	}

	void MaterialManager::MaterialObserver::OnBlendChanged() noexcept
	{
		materialChanged = true;
	}

	void MaterialManager::MaterialObserver::OnRasterizerChanged() noexcept
	{
		materialChanged = true;
	}

	void MaterialManager::MaterialObserver::OnDepthStencilChanged() noexcept
	{
		materialChanged = true;
	}

	void MaterialManager::MaterialObserver::OnDataSlotsChanged() noexcept
	{
		dataSlotsChanged = true;
	}

	void MaterialManager::MaterialObserver::OnThreadGroupCountsChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void MaterialManager::MaterialObserver::OnRenderQueueChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void MaterialManager::MaterialObserver::OnCameraCullingChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void MaterialManager::MaterialObserver::OnNameChanged() noexcept
	{
		nameChanged = true;
	}

	bool MaterialManager::MaterialObserver::MaterialChanged() const noexcept
	{
		return materialChanged;
	}

	bool MaterialManager::MaterialObserver::AmplificationShaderChanged() const noexcept
	{
		return amplificationShaderChanged;
	}

	bool MaterialManager::MaterialObserver::MeshShaderChanged() const noexcept
	{
		return meshShaderChanged;
	}

	bool MaterialManager::MaterialObserver::PixelShaderChanged() const noexcept
	{
		return pixelShaderChanged;
	}

	bool MaterialManager::MaterialObserver::DataSlotsChanged() const noexcept
	{
		return dataSlotsChanged;
	}

	bool MaterialManager::MaterialObserver::AdditionalDataChanged() const noexcept
	{
		return additionalDataChanged;
	}

	bool MaterialManager::MaterialObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void MaterialManager::MaterialObserver::Reset() noexcept
	{
		materialChanged = false;
		amplificationShaderChanged = false;
		meshShaderChanged = false;
		pixelShaderChanged = false;
		dataSlotsChanged = false;
		additionalDataChanged = false;
		nameChanged = false;
	}

	MaterialManager::MaterialManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::shared_ptr<const Render::Material>& material)
	{
		if (!material)
		{
			throw std::invalid_argument("Material is nullptr.");
		}

		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i] == material)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materials[i].get()));

				return materials[i];
			}
		}

		const auto renderMaterial = std::make_shared<Material>();
		Add(renderMaterial, material);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(material.get()));

		return renderMaterial;
	}

	void MaterialManager::Tick()
	{
		for (std::size_t i = 0; i < materials.size(); ++i)
		{
			Material& material = *materials[i];
			const Render::Material& source = *sources[i];
			ShaderData& shaderData = shaders[i];
			MaterialObserver& observer = *materialObservers[i];

			UpdateShaders(source, shaderData, observer);
			UpdateMaterial(material, source, shaderData, observer);
			UpdateDataSlots(material, source, observer);
			UpdateAdditionalData(material, source, observer);
			UpdateName(material, source, observer);

			observer.Reset();
		}
	}

	void MaterialManager::Clean() noexcept
	{
		for (std::size_t i = materials.size(); i-- > 0; )
		{
			if (materials[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy material at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materials[i].get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material destroyed.");
			}
		}
	}

	D3D12_BLEND_DESC MaterialManager::CreateBlendDesc(const Blend& blend) noexcept
	{
		D3D12_BLEND_DESC blendDesc;

		switch (blend.renderTargetBlend.index())
		{
		case 0:
			blendDesc.RenderTarget[0] = CreateOpaqueBlendDesc(std::get<0>(blend.renderTargetBlend));
			break;
		case 1:
			blendDesc.RenderTarget[0] = CreateTransparentBlendDesc(std::get<1>(blend.renderTargetBlend));
			break;
		case 2:
			blendDesc.RenderTarget[0] = CreateLogicBlendDesc(std::get<2>(blend.renderTargetBlend));
			break;
		default: [[unlikely]]
			assert(false && "Unsupported render target blend type.");
			break;
		}

		blendDesc.AlphaToCoverageEnable = blend.alphaToCoverage;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		return blendDesc;
	}

	D3D12_RENDER_TARGET_BLEND_DESC MaterialManager::CreateOpaqueBlendDesc(const OpaqueBlend&) noexcept
	{
		return D3D12_RENDER_TARGET_BLEND_DESC
		{
			.BlendEnable = false,
			.LogicOpEnable = false
		};
	}

	D3D12_RENDER_TARGET_BLEND_DESC MaterialManager::CreateTransparentBlendDesc(const TransparentBlend& blend) noexcept
	{
		return D3D12_RENDER_TARGET_BLEND_DESC
		{
			.BlendEnable = true,
			.LogicOpEnable = false,
			.SrcBlend = GetBlendFactor(blend.sourceBlend),
			.DestBlend = GetBlendFactor(blend.destinationBlend),
			.BlendOp = GetBlendOperation(blend.blendOperation),
			.SrcBlendAlpha = GetBlendFactor(blend.sourceBlendAlpha),
			.DestBlendAlpha = GetBlendFactor(blend.destinationBlendAlpha),
			.BlendOpAlpha = GetBlendOperation(blend.blendOperationAlpha)
		};
	}

	D3D12_RENDER_TARGET_BLEND_DESC MaterialManager::CreateLogicBlendDesc(const LogicBlend& blend) noexcept
	{
		return D3D12_RENDER_TARGET_BLEND_DESC
		{
			.BlendEnable = false,
			.LogicOpEnable = true,
			.LogicOp = GetLogicOperation(blend.operation)
		};
	}

	D3D12_BLEND MaterialManager::GetBlendFactor(const BlendFactor blendFactor) noexcept
	{
		switch (blendFactor)
		{
		case BlendFactor::Zero:
			return D3D12_BLEND_ZERO;
		case BlendFactor::One:
			return D3D12_BLEND_ONE;
		case BlendFactor::ColorSource:
			return D3D12_BLEND_SRC_COLOR;
		case BlendFactor::ColorSourceInverse:
			return D3D12_BLEND_INV_SRC_COLOR;
		case BlendFactor::AlphaSource:
			return D3D12_BLEND_SRC_ALPHA;
		case BlendFactor::AlphaSourceInverse:
			return D3D12_BLEND_INV_SRC_ALPHA;
		case BlendFactor::AlphaSourceSaturate:
			return D3D12_BLEND_SRC_ALPHA_SAT;
		case BlendFactor::ColorDestination:
			return D3D12_BLEND_DEST_COLOR;
		case BlendFactor::ColorDestinationInverse:
			return D3D12_BLEND_INV_DEST_COLOR;
		case BlendFactor::AlphaDestination:
			return D3D12_BLEND_DEST_ALPHA;
		case BlendFactor::AlphaDestinationInverse:
			return D3D12_BLEND_INV_DEST_ALPHA;
		default: [[unlikely]]
			assert(false && "Unsupported blend factor.");
			return D3D12_BLEND_ZERO;
		}
	}

	D3D12_BLEND_OP MaterialManager::GetBlendOperation(const BlendOperation blendOperation) noexcept
	{
		switch (blendOperation)
		{
		case BlendOperation::Add:
			return D3D12_BLEND_OP_ADD;
		case BlendOperation::Subtract:
			return D3D12_BLEND_OP_SUBTRACT;
		case BlendOperation::SubtractReverse:
			return D3D12_BLEND_OP_REV_SUBTRACT;
		case BlendOperation::Min:
			return D3D12_BLEND_OP_MIN;
		case BlendOperation::Max:
			return D3D12_BLEND_OP_MAX;
		default: [[unlikely]]
			assert(false && "Unsupported blend operation");
			return D3D12_BLEND_OP_ADD;
		}
	}

	D3D12_LOGIC_OP MaterialManager::GetLogicOperation(const LogicOperation logicOperation) noexcept
	{
		switch (logicOperation)
		{
		case LogicOperation::Noop:
			return D3D12_LOGIC_OP_NOOP;
		case LogicOperation::Clear:
			return D3D12_LOGIC_OP_CLEAR;
		case LogicOperation::Set:
			return D3D12_LOGIC_OP_SET;
		case LogicOperation::Copy:
			return D3D12_LOGIC_OP_COPY;
		case LogicOperation::CopyInverted:
			return D3D12_LOGIC_OP_COPY_INVERTED;
		case LogicOperation::Invert:
			return D3D12_LOGIC_OP_INVERT;
		case LogicOperation::And:
			return D3D12_LOGIC_OP_AND;
		case LogicOperation::AndReverse:
			return D3D12_LOGIC_OP_AND_REVERSE;
		case LogicOperation::AndInverted:
			return D3D12_LOGIC_OP_AND_INVERTED;
		case LogicOperation::Nand:
			return D3D12_LOGIC_OP_NAND;
		case LogicOperation::Or:
			return D3D12_LOGIC_OP_OR;
		case LogicOperation::OrReverse:
			return D3D12_LOGIC_OP_OR_REVERSE;
		case LogicOperation::OrInverted:
			return D3D12_LOGIC_OP_INVERT;
		case LogicOperation::Nor:
			return D3D12_LOGIC_OP_NOR;
		case LogicOperation::Xor:
			return D3D12_LOGIC_OP_NOR;
		case LogicOperation::Equal:
			return D3D12_LOGIC_OP_EQUIV;
		default: [[unlikely]]
			assert(false && "Unsupported logic operation.");
			return D3D12_LOGIC_OP_NOOP;
		}
	}

	D3D12_RASTERIZER_DESC MaterialManager::CreateRasterizerDesc(const Rasterizer& rasterizer) noexcept
	{
		return D3D12_RASTERIZER_DESC
		{
			.FillMode = GetFillMode(rasterizer.fillMode),
			.CullMode = GetCullMode(rasterizer.cullMode),
			.FrontCounterClockwise = false,
			.DepthBias = static_cast<INT>(rasterizer.depthBias),
			.DepthBiasClamp = static_cast<FLOAT>(rasterizer.depthBiasClamp),
			.SlopeScaledDepthBias = static_cast<FLOAT>(rasterizer.slopeScaledDepthBias),
			.DepthClipEnable = rasterizer.depthClip,
			.MultisampleEnable = true,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0u,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
		};
	}

	D3D12_FILL_MODE MaterialManager::GetFillMode(const FillMode fillMode) noexcept
	{
		switch (fillMode)
		{
		case FillMode::Solid:
			return D3D12_FILL_MODE_SOLID;
		case FillMode::Wireframe:
			return D3D12_FILL_MODE_WIREFRAME;
		default: [[unlikely]]
			assert(false && "Unsupported fill mode.");
			return D3D12_FILL_MODE_SOLID;
		}
	}

	D3D12_CULL_MODE MaterialManager::GetCullMode(const CullMode cullMode) noexcept
	{
		switch (cullMode)
		{
		case CullMode::None:
			return D3D12_CULL_MODE_NONE;
		case CullMode::Front:
			return D3D12_CULL_MODE_FRONT;
		case CullMode::Back:
			return D3D12_CULL_MODE_BACK;
		default: [[unlikely]]
			assert(false && "Unsupported cull mode");
			return D3D12_CULL_MODE_NONE;
		}
	}

	D3D12_DEPTH_STENCIL_DESC1 MaterialManager::CreateDepthStencilDesc(const DepthStencil& depthStencil) noexcept
	{
		return D3D12_DEPTH_STENCIL_DESC1
		{
			.DepthEnable = depthStencil.depth,
			.DepthWriteMask = depthStencil.depthWrite ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO,
			.DepthFunc = GetComparison(depthStencil.depthFunc),
			.StencilEnable = depthStencil.stencil,
			.StencilReadMask = static_cast<UINT8>(depthStencil.stencilReadMask),
			.StencilWriteMask = static_cast<UINT8>(depthStencil.stencilWriteMask),
			.FrontFace = GetDepthStencilOpDesc(depthStencil.frontFace),
			.BackFace = GetDepthStencilOpDesc(depthStencil.backFace),
			.DepthBoundsTestEnable = false
		};
	}

	D3D12_COMPARISON_FUNC MaterialManager::GetComparison(const ComparisonFunction comparison) noexcept
	{
		switch (comparison)
		{
		case ComparisonFunction::Never:
			return D3D12_COMPARISON_FUNC_NEVER;
		case ComparisonFunction::Always:
			return D3D12_COMPARISON_FUNC_ALWAYS;
		case ComparisonFunction::Equal:
			return D3D12_COMPARISON_FUNC_EQUAL;
		case ComparisonFunction::NotEqual:
			return D3D12_COMPARISON_FUNC_NOT_EQUAL;
		case ComparisonFunction::Less:
			return D3D12_COMPARISON_FUNC_LESS;
		case ComparisonFunction::LessOrEqual:
			return D3D12_COMPARISON_FUNC_LESS_EQUAL;
		case ComparisonFunction::Greater:
			return D3D12_COMPARISON_FUNC_GREATER;
		case ComparisonFunction::GreaterOrEqual:
			return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
		default: [[unlikely]]
			assert(false && "Unsupported comparison function.");
			return D3D12_COMPARISON_FUNC_NEVER;
		}
	}

	D3D12_DEPTH_STENCILOP_DESC MaterialManager::GetDepthStencilOpDesc(const DepthStencilOperation& operation) noexcept
	{
		return D3D12_DEPTH_STENCILOP_DESC
		{
			.StencilFailOp = GetStencilOp(operation.failOperation),
			.StencilDepthFailOp = GetStencilOp(operation.depthFailOperation),
			.StencilPassOp = GetStencilOp(operation.passOperation),
			.StencilFunc = GetComparison(operation.stencilComparison)
		};
	}

	D3D12_STENCIL_OP MaterialManager::GetStencilOp(const StencilOperation stencilOperation) noexcept
	{
		switch (stencilOperation)
		{
		case StencilOperation::Keep:
			return D3D12_STENCIL_OP_KEEP;
		case StencilOperation::Zero:
			return D3D12_STENCIL_OP_ZERO;
		case StencilOperation::Replace:
			return D3D12_STENCIL_OP_REPLACE;
		case StencilOperation::Invert:
			return D3D12_STENCIL_OP_INVERT;
		case StencilOperation::Increment:
			return D3D12_STENCIL_OP_INCR;
		case StencilOperation::Decrement:
			return D3D12_STENCIL_OP_DECR;
		case StencilOperation::IncrementSaturated:
			return D3D12_STENCIL_OP_INCR_SAT;
		case StencilOperation::DecrementSaturated:
			return D3D12_STENCIL_OP_DECR_SAT;
		default: [[unlikely]]
			assert(false && "Unsupported stencil operation.");
			return D3D12_STENCIL_OP_KEEP;
		}
	}

	void MaterialManager::UpdateShaders(const Render::Material& source, ShaderData& shaderData, const MaterialObserver& observer) const
	{
		if (observer.AmplificationShaderChanged()) [[unlikely]]
		{
			shaderData.amplificationShader = source.AmplificationShader().empty() ? nullptr : d3d12System->ShaderManager().CreateShader(source.AmplificationShader());
		}

		if (observer.MeshShaderChanged()) [[unlikely]]
		{
			shaderData.meshShader = d3d12System->ShaderManager().CreateShader(source.MeshShader());
		}

		if (observer.PixelShaderChanged()) [[unlikely]]
		{
			shaderData.pixelShader = d3d12System->ShaderManager().CreateShader(source.PixelShader());
		}
	}

	void MaterialManager::UpdateMaterial(Material& material, const Render::Material& source, const ShaderData& shaderData, const MaterialObserver& observer) const
	{
		if (!observer.MaterialChanged() && !observer.AmplificationShaderChanged() && !observer.MeshShaderChanged() && !observer.PixelShaderChanged()) [[likely]]
		{
			return;
		}

		const std::shared_ptr<Shader> rootSignatureShader = d3d12System->ShaderManager().CreateShader(source.RootSignatureShader());
		const std::shared_ptr<RootSignature> rootSignature = d3d12System->RootSignatureManager().CreateRootSignature(rootSignatureShader);
		rootSignature->Name(source.RootSignatureShader());
		const FrameParams& frameParams = d3d12System->GraphicsPipeline().MainFrameParams();

		auto pss = PipelineStateStream
		{
			.rootSignature = &rootSignature->RootSig(),
			.amplificationShader = shaderData.amplificationShader ? shaderData.amplificationShader->ByteCode() : D3D12_SHADER_BYTECODE{},
			.meshShader = shaderData.meshShader->ByteCode(),
			.pixelShader = shaderData.pixelShader->ByteCode(),
			.blend = CreateBlendDesc(source.Blend()),
			.sampleMask = UINT_MAX,
			.rasterizer = CreateRasterizerDesc(source.Rasterizer()),
			.depthStencil = CreateDepthStencilDesc(source.DepthStencil()),
			.renderTargetFormats = D3D12_RT_FORMAT_ARRAY
			{
				.RTFormats = { frameParams.rtvFormat },
				.NumRenderTargets = 1u
			},
			.depthStencilFormat = frameParams.dsvFormat,
			.sampleDescription = frameParams.sampleDesc
		};
		const auto pssDesc = D3D12_PIPELINE_STATE_STREAM_DESC
		{
			.SizeInBytes = sizeof(pss),
			.pPipelineStateSubobjectStream = &pss
		};
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
		if (const HRESULT result = d3d12System->Device().CreatePipelineState(&pssDesc, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const bool isTransparent = pss.blend.Data().RenderTarget[0].BlendEnable || pss.blend.Data().RenderTarget[0].LogicOpEnable;
		material = Material(rootSignature, *pipelineState.Get(), isTransparent);
	}

	void MaterialManager::UpdateDataSlots(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (observer.DataSlotsChanged() || observer.MaterialChanged()) [[unlikely]]
		{
			material.RootSignature()->DataSlots() = source.DataSlots();
		}
	}

	void MaterialManager::UpdateAdditionalData(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (observer.AdditionalDataChanged()) [[unlikely]]
		{
			material.ThreadGroupCounts() = source.ThreadGroupCounts();
			material.RenderQueue() = source.RenderQueue();
			material.CameraCulling() = source.CameraCulling();
		}
	}

	void MaterialManager::UpdateName(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (observer.NameChanged()) [[unlikely]]
		{
			material.Name(source.Name());
		}
	}

	void MaterialManager::Add(const std::shared_ptr<Material>& material, const std::shared_ptr<const Render::Material>& source)
	{
		const std::size_t currentSize = materials.size();

		try
		{
			materials.push_back(material);
			sources.push_back(source);
			shaders.push_back(ShaderData{});
			materialObservers.push_back(std::make_unique<MaterialObserver>());
			source->AddObserver(*materialObservers.back());
		}
		catch (...)
		{
			materials.resize(currentSize);
			sources.resize(currentSize);
			shaders.resize(currentSize);
			materialObservers.resize(currentSize);
		}
	}

	void MaterialManager::Remove(const std::size_t index) noexcept
	{
		sources[index]->RemoveObserver(*materialObservers[index]);

		materials.erase(materials.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		shaders.erase(shaders.cbegin() + index);
		materialObservers.erase(materialObservers.cbegin() + index);
	}
}
