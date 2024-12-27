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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12PipelineStateUtility;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state stream.
	/// @tparam Type Sub-object type.
	/// @tparam DataType Sub-object data type.
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	class alignas(void*) PipelineStateStream final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PipelineStateStream() noexcept = default;
		/// @brief Creates a @p PipelineStateStream with the @p data.
		/// @param data Sub-object data.
		[[nodiscard("Pure constructor")]]
		PipelineStateStream(const DataType& data) noexcept;
		[[nodiscard("Pure constructor")]]
		PipelineStateStream(const PipelineStateStream& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PipelineStateStream(PipelineStateStream&& other) noexcept = default;

		~PipelineStateStream() noexcept = default;

		/// @brief Gets the sub-object data.
		/// @return Sub-object data.
		[[nodiscard("Pure function")]]
		DataType& Data() noexcept;
		/// @brief Gets the sub-object data.
		/// @return Sub-object data.
		[[nodiscard("Pure function")]]
		const DataType& Data() const noexcept;

		PipelineStateStream& operator =(const PipelineStateStream& other) noexcept = default;
		PipelineStateStream& operator =(PipelineStateStream&& other) noexcept = default;

	private:
		D3D12_PIPELINE_STATE_SUBOBJECT_TYPE streamType = Type; ///< Sub-object type.
		DataType data; ///< Sub-object data.
	};

	using PipelineStateStreamRootSignature = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE, ID3D12RootSignature*>; ///< Pipeline state stream with a root signature data.
	using PipelineStateStreamVertexShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a vertex shader data.
	using PipelineStateStreamPixelShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a pixel shader data.
	using PipelineStateStreamDomainShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a domain shader data.
	using PipelineStateStreamHullShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_HS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a hull shader data.
	using PipelineStateStreamGeometryShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_GS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a geometry shader data.
	using PipelineStateStreamComputeShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a compute shader data.
	using PipelineStateStreamStreamOutput = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_STREAM_OUTPUT, D3D12_STREAM_OUTPUT_DESC>; ///< Pipeline state stream with a stream output data.
	using PipelineStateStreamBlend = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND, D3D12_BLEND_DESC>; ///< Pipeline state stream with a blend data.
	using PipelineStateStreamSampleMask = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK, UINT>; ///< Pipeline state stream with a sample mask data.
	using PipelineStateStreamRasterizer = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER, D3D12_RASTERIZER_DESC>; ///< Pipeline state stream with a rasterizer data.
	using PipelineStateStreamDepthStencil = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL, D3D12_DEPTH_STENCIL_DESC>; ///< Pipeline state stream with a depth stencil description data.
	using PipelineStateStreamInputLayout = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_INPUT_LAYOUT, D3D12_INPUT_LAYOUT_DESC>; ///< Pipeline state stream with a layout description data.
	using PipelineStateStreamStripCutValue = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_IB_STRIP_CUT_VALUE, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE>; ///< Pipeline state stream with a strip cut value data.
	using PipelineStateStreamPrimitiveTopology = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY, D3D12_PRIMITIVE_TOPOLOGY_TYPE>; ///< Pipeline state stream with a primitive topology data.
	using PipelineStateStreamRenderTargetFormats = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS, D3D12_RT_FORMAT_ARRAY>; ///< Pipeline state stream with a render target formats data.
	using PipelineStateStreamDepthStencilFormat = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT, DXGI_FORMAT>; ///< Pipeline state stream with a depth stencil format data.
	using PipelineStateStreamSampleDescription = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC, DXGI_SAMPLE_DESC>; ///< Pipeline state stream with a sample description data.
	using PipelineStateStreamNodeMask = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_NODE_MASK, D3D12_NODE_MASK>; ///< Pipeline state stream with a node mask data.
	using PipelineStateStreamCachedPipelineStateObject = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CACHED_PSO, D3D12_CACHED_PIPELINE_STATE>; ///< Pipeline state stream with a cached pipeline state data.
	using PipelineStateStreamTypeFlags = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS, D3D12_PIPELINE_STATE_FLAGS>; ///< Pipeline state stream with a pipeline state flags data.
	using PipelineStateStreamDepthStencil1 = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL1, D3D12_DEPTH_STENCIL_DESC1>; ///< Pipeline state stream with a depth stencil description 1 data.
	using PipelineStateStreamViewInstancing = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VIEW_INSTANCING, D3D12_VIEW_INSTANCING_DESC>; ///< Pipeline state stream with an instancing description data.
	using PipelineStateStreamAmplificationShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with an amplification shader data.
	using PipelineStateStreamMeshShader = PipelineStateStream<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS, D3D12_SHADER_BYTECODE>; ///< Pipeline state stream with a mesh shader data.
}

namespace PonyEngine::Render
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateStream<Type, DataType>::PipelineStateStream(const DataType& data) noexcept :
		data(data)
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	DataType& PipelineStateStream<Type, DataType>::Data() noexcept
	{
		return data;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	const DataType& PipelineStateStream<Type, DataType>::Data() const noexcept
	{
		return data;
	}
}
