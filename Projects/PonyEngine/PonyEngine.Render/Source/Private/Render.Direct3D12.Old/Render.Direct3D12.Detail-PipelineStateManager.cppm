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

export module PonyEngine.Render.Direct3D12.Detail:PipelineStateManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;
import <unordered_map>;
import <variant>;
import <vector>;

import PonyDebug.Log;

import :FrameParams;
import :IGraphicsPipeline;
import :IPipelineStateManager;
import :IMeshManager;
import :ISubSystemContext;
import :PipelineState;
import :PipelineStateUtility;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 pipeline state manager.
	class PipelineStateManager final : public IPipelineStateManager
	{
	public:
		/// @brief Creates a @p PipelineStateManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit PipelineStateManager(ISubSystemContext& d3d12System) noexcept;
		PipelineStateManager(const PipelineStateManager&) = delete;
		PipelineStateManager(PipelineStateManager&&) = delete;

		~PipelineStateManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<PipelineState> CreatePipelineState(const std::shared_ptr<const Render::PipelineState>& pipelineState) override;

		/// @brief Ticks the pipeline state manager.
		void Tick();

		/// @brief Cleans out of dead pipelineState.
		void Clean() noexcept;

		PipelineStateManager& operator =(const PipelineStateManager&) = delete;
		PipelineStateManager& operator =(PipelineStateManager&&) = delete;

	private:
		/// @brief Pipeline state observer.
		class PipelineStateObserver final : public IPipelineStateObserver
		{
		public:
			/// @brief Creates a zero pipeline state observer.
			[[nodiscard("Pure constructor")]]
			PipelineStateObserver() noexcept;
			PipelineStateObserver(const PipelineStateObserver&) = delete;
			PipelineStateObserver(PipelineStateObserver&&) = delete;

			~PipelineStateObserver() noexcept = default;

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

			/// @brief Is the core changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool CoreChanged() const noexcept;
			/// @brief Is the amplification shader changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool AmplificationShaderChanged() const noexcept;
			/// @brief Is the mesh shader changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool MeshShaderChanged() const noexcept;
			/// @brief Is the pixel shader changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool PixelShaderChanged() const noexcept;
			/// @brief Are the data slots changed?
			/// @return @a True if they're changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool DataSlotsChanged() const noexcept;
			/// @brief Is the additional data changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool AdditionalDataChanged() const noexcept;
			/// @brief Is the name changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			/// @brief Resets all the flags.
			void Reset() noexcept;

			PipelineStateObserver& operator =(const PipelineStateObserver&) = delete;
			PipelineStateObserver& operator =(PipelineStateObserver&&) = delete;

		private:
			bool coreChanged; ///< Is the core changed?
			bool amplificationShaderChanged; ///< Is the amplification shader changed?
			bool meshShaderChanged; ///< Is the mesh shader changed?
			bool pixelShaderChanged; ///< Is the pixel shader changed?
			bool dataSlotsChanged; ///< Are the data slots changed?
			bool additionalDataChanged; ///< Is the additional data changed?
			bool nameChanged; ///< Is the name changed?
		};

		/// @brief Pipeline state stream.
		struct PipelineStateStream final
		{
			PipelineStateStreamRootSignature rootSignature; ///< Root signature.
			PipelineStateStreamAmplificationShader amplificationShader; ///< Amplification shader.
			PipelineStateStreamMeshShader meshShader; ///< Mesh shader.
			PipelineStateStreamPixelShader pixelShader; ///< Pixel shader.
			PipelineStateStreamBlend blend; ///< Blend.
			PipelineStateStreamSampleMask sampleMask; ///< Sample mask.
			PipelineStateStreamRasterizer rasterizer; ///< Rasterizer.
			PipelineStateStreamDepthStencil1 depthStencil; ///< Depth stencil.
			PipelineStateStreamRenderTargetFormats renderTargetFormats; ///< Render target formats.
			PipelineStateStreamDepthStencilFormat depthStencilFormat; ///< Depth stencil format.
			PipelineStateStreamSampleDescription sampleDescription; ///< Sample description.
		};

		/// @brief Pipeline shader data.
		struct ShaderData final
		{
			std::shared_ptr<const Shader> amplificationShader; ///< Amplification shader.
			std::shared_ptr<const Shader> meshShader; ///< Mesh shader.
			std::shared_ptr<const Shader> pixelShader; ///< Pixel shader.
		};

		/// @brief Creates a Direct3D12 blend.
		/// @param blend Blend.
		/// @return Direct3D12 blend.
		[[nodiscard("Pure function")]]
		static D3D12_BLEND_DESC CreateBlendDesc(const Blend& blend) noexcept;
		/// @brief Creates a Direct3D12 opaque blend.
		/// @param blend Blend.
		/// @return Direct3D12 opaque blend.
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateOpaqueBlendDesc(const OpaqueBlend& blend) noexcept;
		/// @brief Creates a Direct3D12 transparent blend.
		/// @param blend Blend.
		/// @return Direct3D12 transparent blend.
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateTransparentBlendDesc(const TransparentBlend& blend) noexcept;
		/// @brief Creates a Direct3D12 logic blend.
		/// @param blend Blend.
		/// @return Direct3D12 logic blend.
		[[nodiscard("Pure function")]]
		static D3D12_RENDER_TARGET_BLEND_DESC CreateLogicBlendDesc(const LogicBlend& blend) noexcept;
		/// @brief Converts the @p blendFactor to a Direct3D12 blend factor.
		/// @param blendFactor Blend factor.
		/// @return Direct3D12 blend factor.
		[[nodiscard("Pure function")]]
		static D3D12_BLEND GetBlendFactor(BlendFactor blendFactor) noexcept;
		/// @brief Converts the @p blendOperation to a Direct3D12 blend operation.
		/// @param blendOperation Blend operation.
		/// @return Direct3D12 blend operation.
		[[nodiscard("Pure function")]]
		static D3D12_BLEND_OP GetBlendOperation(BlendOperation blendOperation) noexcept;
		/// @brief Converts the @p logicOperation to a Direct3D12 logic operation.
		/// @param logicOperation Logic operation.
		/// @return Direct3D12 logic operation.
		[[nodiscard("Pure function")]]
		static D3D12_LOGIC_OP GetLogicOperation(LogicOperation logicOperation) noexcept;

		/// @brief Creates a Direct3D12 rasterizer.
		/// @param rasterizer Rasterizer.
		/// @return Direct3D12 rasterizer.
		[[nodiscard("Pure function")]]
		static D3D12_RASTERIZER_DESC CreateRasterizerDesc(const Rasterizer& rasterizer) noexcept;
		/// @brief Converts the @p fillMode to a Direct3D12 fill mode.
		/// @param fillMode Fill mode.
		/// @return Direct3D12 fill mode.
		[[nodiscard("Pure function")]]
		static D3D12_FILL_MODE GetFillMode(FillMode fillMode) noexcept;
		/// @brief Converts the @p cullMode to a Direct3D12 cull mode.
		/// @param cullMode Cull mode.
		/// @return Direct3D12 cull mode.
		[[nodiscard("Pure function")]]
		static D3D12_CULL_MODE GetCullMode(CullMode cullMode) noexcept;

		/// @brief Creates a Direct3D12 depth stencil.
		/// @param depthStencil Depth stencil.
		/// @return Direct3D12 depth stencil.
		[[nodiscard("Pure function")]]
		static D3D12_DEPTH_STENCIL_DESC1 CreateDepthStencilDesc(const DepthStencil& depthStencil) noexcept;
		/// @brief Converts the @p comparison to a Direct3D12 comparison.
		/// @param comparison Comparison.
		/// @return Direct3D12 comparison.
		[[nodiscard("Pure function")]]
		static D3D12_COMPARISON_FUNC GetComparison(ComparisonFunction comparison) noexcept;
		/// @brief Converts the @p operation to a Direct3D12 depth stencil operation.
		/// @param operation Depth stencil operation.
		/// @return Direct3D12 depth stencil operation.
		[[nodiscard("Pure function")]]
		static D3D12_DEPTH_STENCILOP_DESC GetDepthStencilOpDesc(const DepthStencilOperation& operation) noexcept;
		/// @brief Converts the @p stencilOperation to a Direct3D12 stencil operation.
		/// @param stencilOperation Stencil operation.
		/// @return Direct3D12 stencil operation.
		[[nodiscard("Pure function")]]
		static D3D12_STENCIL_OP GetStencilOp(StencilOperation stencilOperation) noexcept;

		/// @brief Updates the shaders.
		/// @param source Pipeline state source.
		/// @param shaderData Shader data to update.
		/// @param observer Pipeline state observer.
		void UpdateShaders(const Render::PipelineState& source, ShaderData& shaderData, const PipelineStateObserver& observer) const;
		/// @brief Update the pipeline state.
		/// @param pipelineState Pipeline state to update.
		/// @param source Pipeline state source.
		/// @param shaderData Shader data.
		/// @param observer Pipeline state observer.
		void UpdatePipelineState(PipelineState& pipelineState, const Render::PipelineState& source, const ShaderData& shaderData, const PipelineStateObserver& observer) const;
        /// @brief Updates the pipeline state data slots.
		/// @param pipelineState Pipeline state to update.
		/// @param source Pipeline state source.
		/// @param observer Pipeline state observer.
		static void UpdateDataSlots(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer);
		/// @brief Updates the pipeline state additional data.
		/// @param pipelineState Pipeline state to update.
		/// @param source Pipeline state source.
		/// @param observer Pipeline state observer.
		static void UpdateAdditionalData(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer);
		/// @brief Updates the pipeline state name.
		/// @param pipelineState Pipeline state to update.
		/// @param source Pipeline state source.
		/// @param observer Pipeline state observer.
		static void UpdateName(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer);

		/// @brief Adds a pipeline state.
		/// @param pipelineState Pipeline state.
		/// @param source Pipeline state source.
		void Add(const std::shared_ptr<PipelineState>& pipelineState, const std::shared_ptr<const Render::PipelineState>& source);
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<PipelineState>> pipelineStates; ///< Pipeline states.
		std::vector<std::shared_ptr<const Render::PipelineState>> sources; ///< Pipeline state sources.
		std::vector<ShaderData> shaders; ///< Shader data.
		std::vector<std::unique_ptr<PipelineStateObserver>> pipelineStateObservers; ///< Pipeline state observers.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Map of a blend factor to a Direct3D12 blend factor.
	const std::unordered_map<BlendFactor, D3D12_BLEND> BlendFactors
	{
		{ BlendFactor::Zero, D3D12_BLEND_ZERO },
		{ BlendFactor::One, D3D12_BLEND_ONE },
		{ BlendFactor::ColorSource, D3D12_BLEND_SRC_COLOR},
		{ BlendFactor::ColorSourceInverse, D3D12_BLEND_INV_SRC_COLOR },
		{ BlendFactor::AlphaSource, D3D12_BLEND_SRC_ALPHA },
		{ BlendFactor::AlphaSourceInverse, D3D12_BLEND_INV_SRC_ALPHA },
		{ BlendFactor::AlphaSourceSaturate, D3D12_BLEND_SRC_ALPHA_SAT },
		{ BlendFactor::ColorDestination, D3D12_BLEND_DEST_COLOR },
		{ BlendFactor::ColorDestinationInverse, D3D12_BLEND_INV_DEST_COLOR },
		{ BlendFactor::AlphaDestination, D3D12_BLEND_DEST_ALPHA },
		{ BlendFactor::AlphaDestinationInverse, D3D12_BLEND_INV_DEST_ALPHA }
	};
	/// @brief Map of a blend operation to a Direct3D12 blend operation.
	const std::unordered_map<BlendOperation, D3D12_BLEND_OP> BlendOperations
	{
		{ BlendOperation::Add, D3D12_BLEND_OP_ADD },
		{ BlendOperation::Subtract, D3D12_BLEND_OP_SUBTRACT },
		{ BlendOperation::SubtractReverse, D3D12_BLEND_OP_REV_SUBTRACT },
		{ BlendOperation::Min, D3D12_BLEND_OP_MIN },
		{ BlendOperation::Max, D3D12_BLEND_OP_MAX }
	};
	/// @brief Map of a logic operation to a Direct3D12 logic operation.
	const std::unordered_map<LogicOperation, D3D12_LOGIC_OP> LogicOperations
	{
		{ LogicOperation::Noop, D3D12_LOGIC_OP_NOOP },
		{ LogicOperation::Clear, D3D12_LOGIC_OP_CLEAR },
		{ LogicOperation::Set, D3D12_LOGIC_OP_SET },
		{ LogicOperation::Copy, D3D12_LOGIC_OP_COPY },
		{ LogicOperation::CopyInverted, D3D12_LOGIC_OP_COPY_INVERTED },
		{ LogicOperation::Invert, D3D12_LOGIC_OP_INVERT },
		{ LogicOperation::And, D3D12_LOGIC_OP_AND },
		{ LogicOperation::AndReverse, D3D12_LOGIC_OP_AND_REVERSE },
		{ LogicOperation::AndInverted, D3D12_LOGIC_OP_AND_INVERTED },
		{ LogicOperation::Nand, D3D12_LOGIC_OP_NAND },
		{ LogicOperation::Or, D3D12_LOGIC_OP_OR },
		{ LogicOperation::OrReverse, D3D12_LOGIC_OP_OR_REVERSE },
		{ LogicOperation::OrInverted, D3D12_LOGIC_OP_INVERT },
		{ LogicOperation::Nor, D3D12_LOGIC_OP_NOR },
		{ LogicOperation::Xor, D3D12_LOGIC_OP_NOR },
		{ LogicOperation::Equal, D3D12_LOGIC_OP_EQUIV }
	};
	/// @brief Map of a fill mode to a Direct3D12 fill mode.
	const std::unordered_map<FillMode, D3D12_FILL_MODE> FillModes
	{
		{ FillMode::Solid, D3D12_FILL_MODE_SOLID },
		{ FillMode::Wireframe, D3D12_FILL_MODE_WIREFRAME }
	};
	/// @brief Map of a cull mode to a Direct3D12 cull mode.
	const std::unordered_map<CullMode, D3D12_CULL_MODE> CullModes
	{
		{ CullMode::None, D3D12_CULL_MODE_NONE },
		{ CullMode::Front, D3D12_CULL_MODE_FRONT },
		{ CullMode::Back, D3D12_CULL_MODE_BACK }
	};
	/// @brief Map of a comparison function to a Direct3D12 comparison function.
	const std::unordered_map<ComparisonFunction, D3D12_COMPARISON_FUNC> ComparisonFunctions
	{
		{ ComparisonFunction::Never, D3D12_COMPARISON_FUNC_NEVER },
		{ ComparisonFunction::Always, D3D12_COMPARISON_FUNC_ALWAYS },
		{ ComparisonFunction::Equal, D3D12_COMPARISON_FUNC_EQUAL },
		{ ComparisonFunction::NotEqual, D3D12_COMPARISON_FUNC_NOT_EQUAL },
		{ ComparisonFunction::Less, D3D12_COMPARISON_FUNC_LESS },
		{ ComparisonFunction::LessOrEqual, D3D12_COMPARISON_FUNC_LESS_EQUAL },
		{ ComparisonFunction::Greater, D3D12_COMPARISON_FUNC_GREATER },
		{ ComparisonFunction::GreaterOrEqual, D3D12_COMPARISON_FUNC_GREATER_EQUAL }
	};
	/// @brief Map of a depth stencil operation to a Direct3D12 depth stencil operation.
	const std::unordered_map<StencilOperation, D3D12_STENCIL_OP> StencilOperations
	{
		{ StencilOperation::Keep, D3D12_STENCIL_OP_KEEP },
		{ StencilOperation::Zero, D3D12_STENCIL_OP_ZERO },
		{ StencilOperation::Replace, D3D12_STENCIL_OP_REPLACE },
		{ StencilOperation::Invert, D3D12_STENCIL_OP_INVERT },
		{ StencilOperation::Increment, D3D12_STENCIL_OP_INCR },
		{ StencilOperation::Decrement, D3D12_STENCIL_OP_DECR },
		{ StencilOperation::IncrementSaturated, D3D12_STENCIL_OP_INCR_SAT },
		{ StencilOperation::DecrementSaturated, D3D12_STENCIL_OP_DECR_SAT }
	};

	PipelineStateManager::PipelineStateObserver::PipelineStateObserver() noexcept :
		coreChanged{true},
		amplificationShaderChanged{true},
		meshShaderChanged{true},
		pixelShaderChanged{true},
		dataSlotsChanged{true},
		additionalDataChanged{true},
		nameChanged{true}
	{
	}

	void PipelineStateManager::PipelineStateObserver::OnRootSignatureShaderChanged() noexcept
	{
		coreChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnAmplificationShaderChanged() noexcept
	{
		amplificationShaderChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnMeshShaderChanged() noexcept
	{
		meshShaderChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnPixelShaderChanged() noexcept
	{
		pixelShaderChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnBlendChanged() noexcept
	{
		coreChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnRasterizerChanged() noexcept
	{
		coreChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnDepthStencilChanged() noexcept
	{
		coreChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnDataSlotsChanged() noexcept
	{
		dataSlotsChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnThreadGroupCountsChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnRenderQueueChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnCameraCullingChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void PipelineStateManager::PipelineStateObserver::OnNameChanged() noexcept
	{
		nameChanged = true;
	}

	bool PipelineStateManager::PipelineStateObserver::CoreChanged() const noexcept
	{
		return coreChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::AmplificationShaderChanged() const noexcept
	{
		return amplificationShaderChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::MeshShaderChanged() const noexcept
	{
		return meshShaderChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::PixelShaderChanged() const noexcept
	{
		return pixelShaderChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::DataSlotsChanged() const noexcept
	{
		return dataSlotsChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::AdditionalDataChanged() const noexcept
	{
		return additionalDataChanged;
	}

	bool PipelineStateManager::PipelineStateObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void PipelineStateManager::PipelineStateObserver::Reset() noexcept
	{
		coreChanged = false;
		amplificationShaderChanged = false;
		meshShaderChanged = false;
		pixelShaderChanged = false;
		dataSlotsChanged = false;
		additionalDataChanged = false;
		nameChanged = false;
	}

	PipelineStateManager::PipelineStateManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<PipelineState> PipelineStateManager::CreatePipelineState(const std::shared_ptr<const Render::PipelineState>& pipelineState)
	{
		if (!pipelineState)
		{
			throw std::invalid_argument("Pipeline state is nullptr.");
		}

		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i] == pipelineState)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Pipeline state reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineStates[i].get()));

				return pipelineStates[i];
			}
		}

		const auto renderPipelineState = std::make_shared<PipelineState>();
		Add(renderPipelineState, pipelineState);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Pipeline state created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineState.get()));

		return renderPipelineState;
	}

	void PipelineStateManager::Tick()
	{
		for (std::size_t i = 0; i < pipelineStates.size(); ++i)
		{
			PipelineState& pipelineState = *pipelineStates[i];
			const Render::PipelineState& source = *sources[i];
			ShaderData& shaderData = shaders[i];
			PipelineStateObserver& observer = *pipelineStateObservers[i];

			UpdateShaders(source, shaderData, observer);
			UpdatePipelineState(pipelineState, source, shaderData, observer);
			UpdateDataSlots(pipelineState, source, observer);
			UpdateAdditionalData(pipelineState, source, observer);
			UpdateName(pipelineState, source, observer);

			observer.Reset();
		}
	}

	void PipelineStateManager::Clean() noexcept
	{
		for (std::size_t i = pipelineStates.size(); i-- > 0; )
		{
			if (pipelineStates[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy pipeline state at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineStates[i].get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Pipeline state destroyed.");
			}
		}
	}

	D3D12_BLEND_DESC PipelineStateManager::CreateBlendDesc(const Blend& blend) noexcept
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

	D3D12_RENDER_TARGET_BLEND_DESC PipelineStateManager::CreateOpaqueBlendDesc(const OpaqueBlend&) noexcept
	{
		return D3D12_RENDER_TARGET_BLEND_DESC
		{
			.BlendEnable = false,
			.LogicOpEnable = false
		};
	}

	D3D12_RENDER_TARGET_BLEND_DESC PipelineStateManager::CreateTransparentBlendDesc(const TransparentBlend& blend) noexcept
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

	D3D12_RENDER_TARGET_BLEND_DESC PipelineStateManager::CreateLogicBlendDesc(const LogicBlend& blend) noexcept
	{
		return D3D12_RENDER_TARGET_BLEND_DESC
		{
			.BlendEnable = false,
			.LogicOpEnable = true,
			.LogicOp = GetLogicOperation(blend.operation)
		};
	}

	D3D12_BLEND PipelineStateManager::GetBlendFactor(const BlendFactor blendFactor) noexcept
	{
		if (const auto position = BlendFactors.find(blendFactor); position != BlendFactors.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Unsupported blend factor.");
		return D3D12_BLEND_ZERO;
	}

	D3D12_BLEND_OP PipelineStateManager::GetBlendOperation(const BlendOperation blendOperation) noexcept
	{
		if (const auto position = BlendOperations.find(blendOperation); position != BlendOperations.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Unsupported blend operation");
		return D3D12_BLEND_OP_ADD;
	}

	D3D12_LOGIC_OP PipelineStateManager::GetLogicOperation(const LogicOperation logicOperation) noexcept
	{
		if (const auto position = LogicOperations.find(logicOperation); position != LogicOperations.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Unsupported logic operation.");
		return D3D12_LOGIC_OP_NOOP;
	}

	D3D12_RASTERIZER_DESC PipelineStateManager::CreateRasterizerDesc(const Rasterizer& rasterizer) noexcept
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

	D3D12_FILL_MODE PipelineStateManager::GetFillMode(const FillMode fillMode) noexcept
	{
		if (const auto position = FillModes.find(fillMode); position != FillModes.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Unsupported fill mode.");
		return D3D12_FILL_MODE_SOLID;
	}

	D3D12_CULL_MODE PipelineStateManager::GetCullMode(const CullMode cullMode) noexcept
	{
		if (const auto position = CullModes.find(cullMode); position != CullModes.cend()) [[likely]]
		{
			return position->second;
		};

		assert(false && "Unsupported cull mode");
		return D3D12_CULL_MODE_NONE;
	}

	D3D12_DEPTH_STENCIL_DESC1 PipelineStateManager::CreateDepthStencilDesc(const DepthStencil& depthStencil) noexcept
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

	D3D12_COMPARISON_FUNC PipelineStateManager::GetComparison(const ComparisonFunction comparison) noexcept
	{
		if (const auto position = ComparisonFunctions.find(comparison); position != ComparisonFunctions.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Unsupported comparison function.");
		return D3D12_COMPARISON_FUNC_NEVER;
	}

	D3D12_DEPTH_STENCILOP_DESC PipelineStateManager::GetDepthStencilOpDesc(const DepthStencilOperation& operation) noexcept
	{
		return D3D12_DEPTH_STENCILOP_DESC
		{
			.StencilFailOp = GetStencilOp(operation.failOperation),
			.StencilDepthFailOp = GetStencilOp(operation.depthFailOperation),
			.StencilPassOp = GetStencilOp(operation.passOperation),
			.StencilFunc = GetComparison(operation.stencilComparison)
		};
	}

	D3D12_STENCIL_OP PipelineStateManager::GetStencilOp(const StencilOperation stencilOperation) noexcept
	{
		if (const auto position = StencilOperations.find(stencilOperation); position != StencilOperations.cend())
		{
			return position->second;
		}

		assert(false && "Unsupported stencil operation.");
		return D3D12_STENCIL_OP_KEEP;
	}

	void PipelineStateManager::UpdateShaders(const Render::PipelineState& source, ShaderData& shaderData, const PipelineStateObserver& observer) const
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

	void PipelineStateManager::UpdatePipelineState(PipelineState& pipelineState, const Render::PipelineState& source, const ShaderData& shaderData, const PipelineStateObserver& observer) const
	{
		if (!observer.CoreChanged() && !observer.AmplificationShaderChanged() && !observer.MeshShaderChanged() && !observer.PixelShaderChanged()) [[likely]]
		{
			return;
		}

		const std::shared_ptr<Shader> rootSignatureShader = d3d12System->ShaderManager().CreateShader(source.RootSignatureShader());
		const std::shared_ptr<RootSignature> rootSignature = d3d12System->RootSignatureManager().CreateRootSignature(rootSignatureShader); // TODO: It creates a bug. The same root signature will be updated with data slots from different pipeline states.
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
		Microsoft::WRL::ComPtr<ID3D12PipelineState> state;
		if (const HRESULT result = d3d12System->Device().CreatePipelineState(&pssDesc, IID_PPV_ARGS(state.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const bool isTransparent = pss.blend.Data().RenderTarget[0].BlendEnable || pss.blend.Data().RenderTarget[0].LogicOpEnable;
		pipelineState = PipelineState(rootSignature, *state.Get(), isTransparent);
	}

	void PipelineStateManager::UpdateDataSlots(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer)
	{
		if (observer.DataSlotsChanged() || observer.CoreChanged()) [[unlikely]]
		{
			pipelineState.RootSignature()->DataSlots() = source.DataSlots();
		}
	}

	void PipelineStateManager::UpdateAdditionalData(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer)
	{
		if (observer.AdditionalDataChanged()) [[unlikely]]
		{
			pipelineState.ThreadGroupCounts() = source.ThreadGroupCounts();
			pipelineState.RenderQueue() = source.RenderQueue();
			pipelineState.CameraCulling() = source.CameraCulling();
		}
	}

	void PipelineStateManager::UpdateName(PipelineState& pipelineState, const Render::PipelineState& source, const PipelineStateObserver& observer)
	{
		if (observer.NameChanged()) [[unlikely]]
		{
			pipelineState.Name(source.Name());
		}
	}

	void PipelineStateManager::Add(const std::shared_ptr<PipelineState>& pipelineState, const std::shared_ptr<const Render::PipelineState>& source)
	{
		const std::size_t currentSize = pipelineStates.size();

		try
		{
			pipelineStates.push_back(pipelineState);
			sources.push_back(source);
			shaders.push_back(ShaderData{});
			pipelineStateObservers.push_back(std::make_unique<PipelineStateObserver>());
			source->AddObserver(*pipelineStateObservers.back());
		}
		catch (...)
		{
			pipelineStates.resize(currentSize);
			sources.resize(currentSize);
			shaders.resize(currentSize);
			pipelineStateObservers.resize(currentSize);

			throw;
		}
	}

	void PipelineStateManager::Remove(const std::size_t index) noexcept
	{
		sources[index]->RemoveObserver(*pipelineStateObservers[index]);

		pipelineStates.erase(pipelineStates.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		shaders.erase(shaders.cbegin() + index);
		pipelineStateObservers.erase(pipelineStateObservers.cbegin() + index);
	}
}
