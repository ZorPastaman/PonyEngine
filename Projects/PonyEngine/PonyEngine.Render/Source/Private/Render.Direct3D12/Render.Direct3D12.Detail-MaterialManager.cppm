/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:MaterialManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyDebug.Log;

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

			virtual void OnRootSignatureChanged() noexcept override;
			virtual void OnAmplificationShaderChanged() noexcept override;
			virtual void OnMeshShaderChanged() noexcept override;
			virtual void OnPixelShaderChanged() noexcept override;
			virtual void OnDataSlotsChanged() noexcept override;
			virtual void OnThreadGroupCountsChanged() noexcept override;
			virtual void OnNameChanged() noexcept override;

			[[nodiscard("Pure function")]]
			bool RootSignatureChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool AmplificationShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool MeshShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool PixelShaderChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool DataSlotsChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool ThreadGroupCountsChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			void Reset() noexcept;

			MaterialObserver& operator =(const MaterialObserver&) = delete;
			MaterialObserver& operator =(MaterialObserver&&) = delete;

		private:
			bool rootSignatureChanged;
			bool amplificationShaderChanged;
			bool meshShaderChanged;
			bool pixelShaderChanged;
			bool dataSlotsChanged;
			bool threadGroupCountsChanged;
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

		void UpdateShaders(const Render::Material& source, ShaderData& shaderData, const MaterialObserver& observer) const;
		void UpdateMaterial(Material& material, const Render::Material& source, const ShaderData& shaderData, const MaterialObserver& observer) const;
		static void UpdateDataSlots(Material& material, const Render::Material& source, const MaterialObserver& observer);
		static void UpdateThreadGroupCounts(Material& material, const Render::Material& source, const MaterialObserver& observer);
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
		rootSignatureChanged{true},
		amplificationShaderChanged{true},
		meshShaderChanged{true},
		pixelShaderChanged{true},
		dataSlotsChanged{true},
		threadGroupCountsChanged{true},
		nameChanged{true}
	{
	}

	void MaterialManager::MaterialObserver::OnRootSignatureChanged() noexcept
	{
		rootSignatureChanged = true;
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

	void MaterialManager::MaterialObserver::OnDataSlotsChanged() noexcept
	{
		dataSlotsChanged = true;
	}

	void MaterialManager::MaterialObserver::OnThreadGroupCountsChanged() noexcept
	{
		threadGroupCountsChanged = true;
	}

	void MaterialManager::MaterialObserver::OnNameChanged() noexcept
	{
		nameChanged = true;
	}

	bool MaterialManager::MaterialObserver::RootSignatureChanged() const noexcept
	{
		return rootSignatureChanged;
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

	bool MaterialManager::MaterialObserver::ThreadGroupCountsChanged() const noexcept
	{
		return threadGroupCountsChanged;
	}

	bool MaterialManager::MaterialObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void MaterialManager::MaterialObserver::Reset() noexcept
	{
		rootSignatureChanged = false;
		amplificationShaderChanged = false;
		meshShaderChanged = false;
		pixelShaderChanged = false;
		dataSlotsChanged = false;
		threadGroupCountsChanged = false;
		nameChanged = false;
	}

	MaterialManager::MaterialManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::shared_ptr<const Render::Material>& material)
	{
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
			UpdateThreadGroupCounts(material, source, observer);
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
		if (!observer.RootSignatureChanged() && !observer.AmplificationShaderChanged() && !observer.MeshShaderChanged() && !observer.PixelShaderChanged()) [[likely]]
		{
			return;
		}

		const std::shared_ptr<Shader> rootSignatureShader = d3d12System->ShaderManager().CreateShader(source.RootSignatureShader());
		const std::shared_ptr<RootSignature> rootSignature = d3d12System->RootSignatureManager().CreateRootSignature(rootSignatureShader);
		rootSignature->Name(source.RootSignatureShader());

		auto pss = PipelineStateStream
		{
			.rootSignature = &rootSignature->RootSig(),
			.amplificationShader = shaderData.amplificationShader ? shaderData.amplificationShader->ByteCode() : D3D12_SHADER_BYTECODE{},
			.meshShader = shaderData.meshShader->ByteCode(),
			.pixelShader = shaderData.pixelShader->ByteCode(),
			.blend = D3D12_BLEND_DESC
			{
				.AlphaToCoverageEnable = false,
				.IndependentBlendEnable = false,
				.RenderTarget =
			{
					D3D12_RENDER_TARGET_BLEND_DESC
					{
						.BlendEnable = false,
						.LogicOpEnable = false,
						.SrcBlend = D3D12_BLEND_ONE,
						.DestBlend = D3D12_BLEND_ZERO,
						.BlendOp = D3D12_BLEND_OP_ADD,
						.SrcBlendAlpha = D3D12_BLEND_ONE,
						.DestBlendAlpha = D3D12_BLEND_ZERO,
						.BlendOpAlpha = D3D12_BLEND_OP_ADD,
						.LogicOp = D3D12_LOGIC_OP_NOOP,
						.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
					}
				}
			},
			.sampleMask = UINT_MAX,
			.rasterizer = D3D12_RASTERIZER_DESC
			{
				.FillMode = D3D12_FILL_MODE_SOLID,
				.CullMode = D3D12_CULL_MODE_BACK,
				.FrontCounterClockwise = true,
				.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
				.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
				.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
				.DepthClipEnable = true,
				.MultisampleEnable = true,
				.AntialiasedLineEnable = false,
				.ForcedSampleCount = 0u,
				.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
			},
			.depthStencil = D3D12_DEPTH_STENCIL_DESC1
			{
				.DepthEnable = true,
				.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
				.DepthFunc = D3D12_COMPARISON_FUNC_LESS,
				.StencilEnable = true,
				.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
				.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
				.FrontFace = D3D12_DEPTH_STENCILOP_DESC
				{
					.StencilFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilPassOp = D3D12_STENCIL_OP_KEEP,
					.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS
				},
				.BackFace = D3D12_DEPTH_STENCILOP_DESC
				{
					.StencilFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilPassOp = D3D12_STENCIL_OP_KEEP,
					.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS
				},
				.DepthBoundsTestEnable = true
			},
			.renderTargetFormats = D3D12_RT_FORMAT_ARRAY
			{
				.RTFormats = { d3d12System->FrameManager().RtvFormat() },
				.NumRenderTargets = 1u
			},
			.depthStencilFormat = d3d12System->FrameManager().DsvFormat(),
			.sampleDescription = d3d12System->FrameManager().SampleDesc()
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

		material = Material(rootSignature, *pipelineState.Get(), false);
	}

	void MaterialManager::UpdateDataSlots(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (observer.DataSlotsChanged() || observer.RootSignatureChanged()) [[unlikely]]
		{
			material.RootSignature()->DataSlots(source.DataSlots());
		}
	}

	void MaterialManager::UpdateThreadGroupCounts(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (observer.ThreadGroupCountsChanged()) [[unlikely]]
		{
			std::ranges::copy(source.ThreadGroupCounts(), material.ThreadGroupCounts().begin());
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
