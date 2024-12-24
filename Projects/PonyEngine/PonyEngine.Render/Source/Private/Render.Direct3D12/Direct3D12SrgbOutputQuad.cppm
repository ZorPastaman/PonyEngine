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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12SrgbOutputQuad;

import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Core;

import :Direct3D12Utility;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12SrgbOutputQuad final
	{
	public:
		static constexpr UINT VertexSlot = 0u;
		static constexpr UINT UvSlot = 1u;
		static constexpr UINT RenderTargetSlot = 0u;
		static constexpr UINT IndexCount = 6u;

		[[nodiscard("Pure constructor")]]
		explicit Direct3D12SrgbOutputQuad(IDirect3D12SystemContext& d3d12System);
		Direct3D12SrgbOutputQuad(const Direct3D12SrgbOutputQuad&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12SrgbOutputQuad(Direct3D12SrgbOutputQuad&& other) noexcept = default;

		~Direct3D12SrgbOutputQuad() noexcept;

		[[nodiscard("Pure function")]]
		ID3D12RootSignature& RootSignature() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature& RootSignature() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& PipelineState() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& VertexBuffer() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& VertexBuffer() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12Resource2& UvBuffer() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& UvBuffer() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12Resource2& IndexBuffer() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& IndexBuffer() const noexcept;

		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexBufferView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& UvBufferView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_INDEX_BUFFER_VIEW& IndexBufferView() const noexcept;

		void Name(std::string_view name);

		Direct3D12SrgbOutputQuad& operator =(const Direct3D12SrgbOutputQuad&) = delete;
		Direct3D12SrgbOutputQuad& operator =(Direct3D12SrgbOutputQuad&& other) noexcept = default;

	private:
		IDirect3D12SystemContext* d3d12System;

		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource2> uvBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource2> indexBuffer;

		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		D3D12_VERTEX_BUFFER_VIEW uvBufferView;
		D3D12_INDEX_BUFFER_VIEW indexBufferView;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SrgbOutputQuad::Direct3D12SrgbOutputQuad(IDirect3D12SystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output root signature.");
		const auto rootSignatureShader = Direct3D12Shader("SrgbOutputRootSignature");
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateRootSignature(0u, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire srgb output root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output root signature created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output pipeline state.");
		const auto vertexShader = Direct3D12Shader("SrgbOutputVertexShader");
		const auto pixelShader = Direct3D12Shader("SrgbOutputPixelShader");
		constexpr auto blendState = D3D12_BLEND_DESC
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
		};
		constexpr auto rasterizerState = D3D12_RASTERIZER_DESC
		{
			.FillMode = D3D12_FILL_MODE_SOLID,
			.CullMode = D3D12_CULL_MODE_NONE,
			.FrontCounterClockwise = true,
			.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
			.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
			.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			.DepthClipEnable = false,
			.MultisampleEnable = false,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0u,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
		};
		const auto inputLayout = std::array<D3D12_INPUT_ELEMENT_DESC, 2>
		{
			D3D12_INPUT_ELEMENT_DESC
			{
				.SemanticName = "POSITION",
				.SemanticIndex = 0u,
				.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				.InputSlot = VertexSlot,
				.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0u
			},
				D3D12_INPUT_ELEMENT_DESC
			{
				.SemanticName = "TEXCOORD",
				.SemanticIndex = 0u,
				.Format = DXGI_FORMAT_R32G32_FLOAT,
				.InputSlot = UvSlot,
				.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0u
			},
		};
		const auto gfxPsd = D3D12_GRAPHICS_PIPELINE_STATE_DESC
		{
			.pRootSignature = rootSignature.Get(),
			.VS = D3D12_SHADER_BYTECODE{.pShaderBytecode = vertexShader.Data(), .BytecodeLength = vertexShader.Size()},
			.PS = D3D12_SHADER_BYTECODE{.pShaderBytecode = pixelShader.Data(), .BytecodeLength = pixelShader.Size()},
			.BlendState = blendState,
			.SampleMask = UINT_MAX,
			.RasterizerState = rasterizerState,
			.InputLayout = D3D12_INPUT_LAYOUT_DESC{ .pInputElementDescs = inputLayout.data(), .NumElements = static_cast<UINT>(inputLayout.size()) },
			.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
			.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
			.NumRenderTargets = 1,
			.RTVFormats = { this->d3d12System->BackPrivate().FormatSrgb() },
			.SampleDesc = DXGI_SAMPLE_DESC{ .Count = 1u, .Quality = 0u },
			.NodeMask = 0u,
			.Flags = D3D12_PIPELINE_STATE_FLAG_NONE
		};
		if (const HRESULT result = device.CreateGraphicsPipelineState(&gfxPsd, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire srgb output pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output pipeline state created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output mesh.");
		constexpr auto quadVertices = std::array<PonyMath::Core::Vector3<FLOAT>, 4>
		{
			PonyMath::Core::Vector3<FLOAT>(-1.f, -1.f, 0.f),
			PonyMath::Core::Vector3<FLOAT>(1.f, -1.f, 0.f),
			PonyMath::Core::Vector3<FLOAT>(1.f, 1.f, 0.f),
			PonyMath::Core::Vector3<FLOAT>(-1.f, 1.f, 0.f)
		};
		constexpr auto quadUvs = std::array<PonyMath::Core::Vector2<FLOAT>, 4>
		{
			PonyMath::Core::Vector2<FLOAT>(0.f, 1.f),
			PonyMath::Core::Vector2<FLOAT>(1.f, 1.f),
			PonyMath::Core::Vector2<FLOAT>(1.f, 0.f),
			PonyMath::Core::Vector2<FLOAT>(0.f, 0.f)
		};
		constexpr auto quadTriangles = std::array<PonyMath::Core::Vector3<UINT32>, 2>
		{
			PonyMath::Core::Vector3<UINT32>(0u, 1u, 2u),
			PonyMath::Core::Vector3<UINT32>(0u, 2u, 3u)
		};
		constexpr auto uploadHeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_UPLOAD,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		constexpr auto gpuHeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		constexpr std::size_t vertexBufferSize = sizeof(quadVertices);
		constexpr auto vertexBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(vertexBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadVertexBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadVertexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create upload vertex buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* vertexData;
		if (const HRESULT result = uploadVertexBuffer->Map(0, nullptr, &vertexData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertex buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(vertexData, quadVertices.data(), vertexBufferSize);
		uploadVertexBuffer->Unmap(0, nullptr);
		if (const HRESULT result = device.CreateCommittedResource3(&gpuHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(vertexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu vertex buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		IDirect3D12CopyPipeline& copyPipeline = this->d3d12System->CopyPipeline();
		copyPipeline.AddBufferCopyTask(*uploadVertexBuffer.Get(), *vertexBuffer.Get());
		constexpr std::size_t uvBufferSize = sizeof(quadUvs);
		constexpr auto uvBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(uvBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadUvBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &uvBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadUvBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create upload uv buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* uvData;
		if (const HRESULT result = uploadUvBuffer->Map(0, nullptr, &uvData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map uv buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(uvData, quadUvs.data(), uvBufferSize);
		uploadUvBuffer->Unmap(0, nullptr);
		if (const HRESULT result = device.CreateCommittedResource3(&gpuHeapProperties, D3D12_HEAP_FLAG_NONE, &uvBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uvBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu uv buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		copyPipeline.AddBufferCopyTask(*uploadUvBuffer.Get(), *uvBuffer.Get());
		constexpr std::size_t indexBufferSize = sizeof(quadTriangles);
		constexpr auto indexBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(indexBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadIndexBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &indexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadIndexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create upload index buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* indexData;
		if (const HRESULT result = uploadIndexBuffer->Map(0, nullptr, &indexData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map index buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(indexData, quadTriangles.data(), indexBufferSize);
		uploadIndexBuffer->Unmap(0, nullptr);
		if (const HRESULT result = device.CreateCommittedResource3(&gpuHeapProperties, D3D12_HEAP_FLAG_NONE, &indexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(indexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu index buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		copyPipeline.AddBufferCopyTask(*uploadIndexBuffer.Get(), *indexBuffer.Get());
		vertexBufferView = D3D12_VERTEX_BUFFER_VIEW{.BufferLocation = vertexBuffer->GetGPUVirtualAddress(), .SizeInBytes = vertexBufferSize, .StrideInBytes = sizeof(PonyMath::Core::Vector3<FLOAT>)};
		uvBufferView = D3D12_VERTEX_BUFFER_VIEW{.BufferLocation = uvBuffer->GetGPUVirtualAddress(), .SizeInBytes = uvBufferSize, .StrideInBytes = sizeof(PonyMath::Core::Vector2<FLOAT>)};
		indexBufferView = D3D12_INDEX_BUFFER_VIEW{.BufferLocation = indexBuffer->GetGPUVirtualAddress(), .SizeInBytes = indexBufferSize, .Format = DXGI_FORMAT_R32_UINT};
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output mesh created.");
	}

	Direct3D12SrgbOutputQuad::~Direct3D12SrgbOutputQuad() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release srgb output mesh.");
		indexBuffer.Reset();
		uvBuffer.Reset();
		vertexBuffer.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output mesh released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release srgb output pipeline state.");
		pipelineState.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output pipeline state released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release srgb output root signature.");
		pipelineState.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output root signature released.");
	}

	ID3D12RootSignature& Direct3D12SrgbOutputQuad::RootSignature() noexcept
	{
		return *rootSignature.Get();
	}

	const ID3D12RootSignature& Direct3D12SrgbOutputQuad::RootSignature() const noexcept
	{
		return *rootSignature.Get();
	}

	ID3D12PipelineState& Direct3D12SrgbOutputQuad::PipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& Direct3D12SrgbOutputQuad::PipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	ID3D12Resource2& Direct3D12SrgbOutputQuad::VertexBuffer() noexcept
	{
		return *vertexBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12SrgbOutputQuad::VertexBuffer() const noexcept
	{
		return *vertexBuffer.Get();
	}

	ID3D12Resource2& Direct3D12SrgbOutputQuad::UvBuffer() noexcept
	{
		return *uvBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12SrgbOutputQuad::UvBuffer() const noexcept
	{
		return *uvBuffer.Get();
	}

	ID3D12Resource2& Direct3D12SrgbOutputQuad::IndexBuffer() noexcept
	{
		return *indexBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12SrgbOutputQuad::IndexBuffer() const noexcept
	{
		return *indexBuffer.Get();
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12SrgbOutputQuad::VertexBufferView() const noexcept
	{
		return vertexBufferView;
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12SrgbOutputQuad::UvBufferView() const noexcept
	{
		return uvBufferView;
	}

	const D3D12_INDEX_BUFFER_VIEW& Direct3D12SrgbOutputQuad::IndexBufferView() const noexcept
	{
		return indexBufferView;
	}

	void Direct3D12SrgbOutputQuad::Name(const std::string_view name)
	{
		constexpr std::string_view rootSignatureName = " - RootSignature";
		constexpr std::string_view pipelineStateName = " - PipelineState";
		constexpr std::string_view vertexBufferName = " - VertexBuffer";
		constexpr std::string_view uvBufferName = " - UvBuffer";
		constexpr std::string_view indexBufferName = " - IndexBuffer";

		auto componentName = std::string();
		componentName.reserve(name.size() + rootSignatureName.size());

		componentName.append(name).append(rootSignatureName);
		SetName(*rootSignature.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(pipelineStateName);
		SetName(*pipelineState.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(vertexBufferName);
		SetName(*vertexBuffer.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(uvBufferName);
		SetName(*uvBuffer.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(indexBufferName);
		SetName(*indexBuffer.Get(), componentName);
	}
}
