/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:ISecondaryGraphicsCommandList;

import std;

import PonyEngine.Math;

import :DepthBias;
import :DepthRange;
import :ICommandList;
import :IComputePipelineState;
import :IGraphicsPipelineState;
import :ISamplerContainer;
import :IShaderDataContainer;
import :SamplerBinding;
import :ShaderDataBinding;
import :StencilReference;

export namespace PonyEngine::RenderDevice
{
	class ISecondaryGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ISecondaryGraphicsCommandList)

		virtual void SetDepthBias(const DepthBias& bias) = 0;
		virtual void SetDepthBounds(const DepthRange& range) = 0;
		virtual void SetStencilReference(const StencilReference& reference) = 0;
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) = 0;

		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) = 0;
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) = 0;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
		void BindGraphics(const ShaderDataBinding& shaderDataBinding);
		void BindGraphics(const SamplerBinding& samplerBinding);
		void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings);
		void BindGraphics(std::span<const SamplerBinding> samplerBindings);
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;
		void BindCompute(const ShaderDataBinding& shaderDataBinding);
		void BindCompute(const SamplerBinding& samplerBinding);
		void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings);
		void BindCompute(std::span<const SamplerBinding> samplerBindings);
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;

		void DispatchGraphics(std::uint32_t threadGroupCount);
		void DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		void DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		void DispatchCompute(std::uint32_t threadGroupCount);
		void DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		void DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void ISecondaryGraphicsCommandList::BindGraphics(const ShaderDataBinding& shaderDataBinding)
	{
		BindGraphics(std::span(&shaderDataBinding, 1uz));
	}

	void ISecondaryGraphicsCommandList::BindGraphics(const SamplerBinding& samplerBinding)
	{
		BindGraphics(std::span(&samplerBinding, 1uz));
	}

	void ISecondaryGraphicsCommandList::BindGraphics(const std::span<const ShaderDataBinding> shaderDataBindings)
	{
		BindGraphics(shaderDataBindings, std::span<const SamplerBinding>());
	}

	void ISecondaryGraphicsCommandList::BindGraphics(const std::span<const SamplerBinding> samplerBindings)
	{
		BindGraphics(std::span<const ShaderDataBinding>(), samplerBindings);
	}

	void ISecondaryGraphicsCommandList::BindCompute(const ShaderDataBinding& shaderDataBinding)
	{
		BindCompute(std::span(&shaderDataBinding, 1uz));
	}

	void ISecondaryGraphicsCommandList::BindCompute(const SamplerBinding& samplerBinding)
	{
		BindCompute(std::span(&samplerBinding, 1uz));
	}

	void ISecondaryGraphicsCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings)
	{
		BindCompute(shaderDataBindings, std::span<const SamplerBinding>());
	}

	void ISecondaryGraphicsCommandList::BindCompute(const std::span<const SamplerBinding> samplerBindings)
	{
		BindCompute(std::span<const ShaderDataBinding>(), samplerBindings);
	}

	void ISecondaryGraphicsCommandList::DispatchGraphics(const std::uint32_t threadGroupCount)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCount, 1u, 1u));
	}

	void ISecondaryGraphicsCommandList::DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), 1u, 1u));
	}

	void ISecondaryGraphicsCommandList::DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), threadGroupCounts.Y(), 1u));
	}

	void ISecondaryGraphicsCommandList::DispatchCompute(const std::uint32_t threadGroupCount)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCount, 1u, 1u));
	}

	void ISecondaryGraphicsCommandList::DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), 1u, 1u));
	}

	void ISecondaryGraphicsCommandList::DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), threadGroupCounts.Y(), 1u));
	}
}
