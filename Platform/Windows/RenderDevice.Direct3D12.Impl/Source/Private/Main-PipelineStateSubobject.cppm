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
	/// @brief Pipeline state subobject.
	/// @tparam Type Subobject type.
	/// @tparam DataType Subobject data type.
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	class alignas(void*) PipelineStateSubobject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject() noexcept = default;
		/// @brief Creates a pipeline state subobject.
		/// @param data Subobject data.
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(const DataType& data) noexcept;
		/// @brief Creates a pipeline state subobject.
		/// @param data Subobject data.
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(DataType&& data) noexcept;
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(const PipelineStateSubobject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PipelineStateSubobject(PipelineStateSubobject&& other) noexcept = default;

		~PipelineStateSubobject() noexcept = default;

		/// @brief Gets the subobject data.
		/// @return Subobject data.
		[[nodiscard("Pure function")]]
		DataType& Data() noexcept;
		/// @brief Gets the subobject data.
		/// @return Subobject data.
		[[nodiscard("Pure function")]]
		const DataType& Data() const noexcept;

		PipelineStateSubobject& operator =(const PipelineStateSubobject& other) = default;
		PipelineStateSubobject& operator =(PipelineStateSubobject&& other) = default;

		/// @brief Sets the subobject data.
		/// @param data Subobject data to set.
		/// @return @a This.
		PipelineStateSubobject& operator =(const DataType& data) noexcept;
		/// @brief Sets the subobject data.
		/// @param data Subobject data to set.
		/// @return @a This.
		PipelineStateSubobject& operator =(DataType&& data) noexcept;

	private:
		D3D12_PIPELINE_STATE_SUBOBJECT_TYPE type = Type; ///< Subobject type.
		DataType data; ///< Subobject data.
	};

	using PipelineStateSubobjectRootSignature = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE, ID3D12RootSignature*>; ///< Pipeline state subobject for a root signature.
	using PipelineStateSubobjectAmplificationShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS, D3D12_SHADER_BYTECODE>; ///< Pipeline state subobject for an amplification shader.
	using PipelineStateSubobjectMeshShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS, D3D12_SHADER_BYTECODE>; ///< Pipeline state subobject for a mesh shader.
	using PipelineStateSubobjectPixelShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS, D3D12_SHADER_BYTECODE>; ///< Pipeline state subobject for a pixel shader.
	using PipelineStateSubobjectComputeShader = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS, D3D12_SHADER_BYTECODE>; ///< Pipeline state subobject for a compute shader.
	using PipelineStateSubobjectRasterizer = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER2, D3D12_RASTERIZER_DESC2>; ///< Pipeline state subobject for a rasterizer description.
	using PipelineStateSubobjectBlend = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND, D3D12_BLEND_DESC>; ///< Pipeline state subobject for a blend description.
	using PipelineStateSubobjectRenderTargetFormats = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS, D3D12_RT_FORMAT_ARRAY>; ///< Pipeline state subobject for a render target format array.
	using PipelineStateSubobjectDepthStencil = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL2, D3D12_DEPTH_STENCIL_DESC2>; ///< Pipeline state subobject for a depth stencil description.
	using PipelineStateSubobjectDepthStencilFormat = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT, DXGI_FORMAT>; ///< Pipeline state subobject for a depth stencil format.
	using PipelineStateSubobjectSampleDesc = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC, DXGI_SAMPLE_DESC>; ///< Pipeline state subobject for a sample description.
	using PipelineStateSubobjectSampleMask = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK, UINT>; ///< Pipeline state subobject for a sample mask.
	using PipelineStateSubobjectFlags = PipelineStateSubobject<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS, D3D12_PIPELINE_STATE_FLAGS>; ///< Pipeline state subobject for pipeline state flags.
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>::PipelineStateSubobject(const DataType& data) noexcept :
		data(data)
	{
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>::PipelineStateSubobject(DataType&& data) noexcept :
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
	PipelineStateSubobject<Type, DataType>& PipelineStateSubobject<Type, DataType>::operator =(const DataType& data) noexcept
	{
		type = Type;
		this->data = data;
		return *this;
	}

	template<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE Type, typename DataType>
	PipelineStateSubobject<Type, DataType>& PipelineStateSubobject<Type, DataType>::operator =(DataType&& data) noexcept
	{
		type = Type;
		this->data = std::move(data);
		return *this;
	}
}
