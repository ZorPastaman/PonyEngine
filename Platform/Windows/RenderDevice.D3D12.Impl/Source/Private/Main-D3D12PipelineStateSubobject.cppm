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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12PipelineStateSubobject;

import std;

export namespace PonyEngine::RenderDevice::Windows
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	class alignas(void*) D3D12PipelineStateSubobject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12PipelineStateSubobject() = default;
		[[nodiscard("Pure constructor")]]
		D3D12PipelineStateSubobject(const DataType& data);
		[[nodiscard("Pure constructor")]]
		D3D12PipelineStateSubobject(DataType&& data);
		[[nodiscard("Pure constructor")]]
		D3D12PipelineStateSubobject(const D3D12PipelineStateSubobject& other) = default;
		[[nodiscard("Pure constructor")]]
		D3D12PipelineStateSubobject(D3D12PipelineStateSubobject&& other) = default;

		~D3D12PipelineStateSubobject() noexcept = default;

		[[nodiscard("Pure function")]]
		DataType& Data() noexcept;
		[[nodiscard("Pure function")]]
		const DataType& Data() const noexcept;

		D3D12PipelineStateSubobject& operator =(const D3D12PipelineStateSubobject& other) = default;
		D3D12PipelineStateSubobject& operator =(D3D12PipelineStateSubobject&& other) = default;

		D3D12PipelineStateSubobject& operator =(const DataType& data);
		D3D12PipelineStateSubobject& operator =(DataType&& data);

	private:
		D3D12_PIPELINE_STATE_SUBOBJECT_TYPE type = Type;
		DataType data;
	};

	using D3D12PipelineStateSubobjectRootSignature = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE, ID3D12RootSignature*>;
	using D3D12PipelineStateSubobjectAmplificationShader = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS, D3D12_SHADER_BYTECODE>;
	using D3D12PipelineStateSubobjectMeshShader = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS, D3D12_SHADER_BYTECODE>;
	using D3D12PipelineStateSubobjectPixelShader = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS, D3D12_SHADER_BYTECODE>;
	using D3D12PipelineStateSubobjectRasterizer = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER2, D3D12_RASTERIZER_DESC2>;
	using D3D12PipelineStateSubobjectBlend = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND, D3D12_BLEND_DESC>;
	using D3D12PipelineStateSubobjectRenderTargetFormats = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS, D3D12_RT_FORMAT_ARRAY>;
	using D3D12PipelineStateSubobjectDepthStencil = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL2, D3D12_DEPTH_STENCIL_DESC2>;
	using D3D12PipelineStateSubobjectDepthStencilFormat = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT, DXGI_FORMAT>;
	using D3D12PipelineStateSubobjectSampleDesc = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC, DXGI_SAMPLE_DESC>;
	using D3D12PipelineStateSubobjectSampleMask = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK, UINT>;
	using D3D12PipelineStateSubobjectFlags = D3D12PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS, D3D12_PIPELINE_STATE_FLAGS>;
}

namespace PonyEngine::RenderDevice::Windows
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	D3D12PipelineStateSubobject<Type, DataType>::D3D12PipelineStateSubobject(const DataType& data) :
		data(data)
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	D3D12PipelineStateSubobject<Type, DataType>::D3D12PipelineStateSubobject(DataType&& data) :
		data(std::move(data))
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	DataType& D3D12PipelineStateSubobject<Type, DataType>::Data() noexcept
	{
		return data;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	const DataType& D3D12PipelineStateSubobject<Type, DataType>::Data() const noexcept
	{
		return data;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	D3D12PipelineStateSubobject<Type, DataType>& D3D12PipelineStateSubobject<Type, DataType>::operator =(const DataType& data)
	{
		type = Type;
		this->data = data;
		return *this;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	D3D12PipelineStateSubobject<Type, DataType>& D3D12PipelineStateSubobject<Type, DataType>::operator =(DataType&& data)
	{
		type = Type;
		this->data = std::move(data);
		return *this;
	}
}
