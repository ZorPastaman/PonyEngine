/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:PipelineStateSubobject;

import std;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	class alignas(void*) PipelineStateSubobject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject() = default;
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(const DataType& data);
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(DataType&& data);
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(const PipelineStateSubobject& other) = default;
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(PipelineStateSubobject&& other) = default;

		~PipelineStateSubobject() noexcept = default;

		[[nodiscard("Pure function")]]
		DataType& Data() noexcept;
		[[nodiscard("Pure function")]]
		const DataType& Data() const noexcept;

		PipelineStateSubobject& operator =(const PipelineStateSubobject& other) = default;
		PipelineStateSubobject& operator =(PipelineStateSubobject&& other) = default;

		PipelineStateSubobject& operator =(const DataType& data);
		PipelineStateSubobject& operator =(DataType&& data);

	private:
		D3D12_PIPELINE_STATE_SUBOBJECT_TYPE type = Type;
		DataType data;
	};

	using PipelineStateSubobjectRootSignature = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE, ID3D12RootSignature*>;
	using PipelineStateSubobjectAmplificationShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS, D3D12_SHADER_BYTECODE>;
	using PipelineStateSubobjectMeshShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS, D3D12_SHADER_BYTECODE>;
	using PipelineStateSubobjectPixelShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS, D3D12_SHADER_BYTECODE>;
	using PipelineStateSubobjectComputeShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS, D3D12_SHADER_BYTECODE>;
	using PipelineStateSubobjectRasterizer = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER2, D3D12_RASTERIZER_DESC2>;
	using PipelineStateSubobjectBlend = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND, D3D12_BLEND_DESC>;
	using PipelineStateSubobjectRenderTargetFormats = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS, D3D12_RT_FORMAT_ARRAY>;
	using PipelineStateSubobjectDepthStencil = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL2, D3D12_DEPTH_STENCIL_DESC2>;
	using PipelineStateSubobjectDepthStencilFormat = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT, DXGI_FORMAT>;
	using PipelineStateSubobjectSampleDesc = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC, DXGI_SAMPLE_DESC>;
	using PipelineStateSubobjectSampleMask = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK, UINT>;
	using PipelineStateSubobjectFlags = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS, D3D12_PIPELINE_STATE_FLAGS>;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>::PipelineStateSubobject(const DataType& data) :
		data(data)
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>::PipelineStateSubobject(DataType&& data) :
		data(std::move(data))
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	DataType& PipelineStateSubobject<Type, DataType>::Data() noexcept
	{
		return data;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	const DataType& PipelineStateSubobject<Type, DataType>::Data() const noexcept
	{
		return data;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>& PipelineStateSubobject<Type, DataType>::operator =(const DataType& data)
	{
		type = Type;
		this->data = data;
		return *this;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>& PipelineStateSubobject<Type, DataType>::operator =(DataType&& data)
	{
		type = Type;
		this->data = std::move(data);
		return *this;
	}
}
