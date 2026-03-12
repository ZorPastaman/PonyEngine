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
	/// @brief Secondary graphics command list.
	class ISecondaryGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ISecondaryGraphicsCommandList)

		/// @brief Sets the depth bias.
		/// @param bias Depth bias.
		virtual void SetDepthBias(const DepthBias& bias) = 0;
		/// @brief Sets the depth range.
		/// @param range Depth range.
		virtual void SetDepthBounds(const DepthRange& range) = 0;
		/// @brief Sets the stencil reference.
		/// @param reference Stencil reference.
		virtual void SetStencilReference(const StencilReference& reference) = 0;
		/// @brief Sets the blend factor.
		/// @param factor Blend factor.
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) = 0;

		/// @brief Unbinds all the containers.
		void BindContainers();
		/// @brief Binds the shader data container and unbinds a sampler container.
		/// @param shaderDataContainer Shader data container to bind. Must be shader visible.
		void BindContainers(const IShaderDataContainer& shaderDataContainer);
		/// @brief Binds the sampler container and unbinds a shader data container.
		/// @param samplerContainer Sampler container to bind. Must be shader visible.
		void BindContainers(const ISamplerContainer& samplerContainer);
		/// @brief Binds the containers.
		/// @param shaderDataContainer Shader data container to bind. Must be shader visible.
		/// @param samplerContainer Sampler container to bind. Must be shader visible.
		/// @remark All the containers must be the same as set in a main graphics command list.
		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) = 0;
		/// @brief Binds the graphics pipeline state.
		/// @param pipelineState 
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) = 0;
		/// @brief Binds the compute pipeline state.
		/// @param pipelineState Compute pipeline state to bind.
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
		/// @brief Binds a view from a currently bound shader data container to a currently bound graphics pipeline state.
		/// @param shaderDataBinding Shader data binding.
		void BindGraphics(const ShaderDataBinding& shaderDataBinding);
		/// @brief Binds a sampler a currently bound sampler container to a currently bound graphics pipeline state.
		/// @param samplerBinding Sampler binding.
		void BindGraphics(const SamplerBinding& samplerBinding);
		/// @brief Binds views from a currently bound shader data container to a currently bound graphics pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings);
		/// @brief Binds samplers a currently bound sampler container to a currently bound graphics pipeline state.
		/// @param samplerBindings Sampler bindings.
		void BindGraphics(std::span<const SamplerBinding> samplerBindings);
		/// @brief Binds views from a currently bound shader data container and samplers from a currently bound sampler container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		/// @param samplerBindings Sampler bindings.
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;
		/// @brief Binds a view from a currently bound shader data container to a currently bound compute pipeline state.
		/// @param shaderDataBinding Shader data binding.
		void BindCompute(const ShaderDataBinding& shaderDataBinding);
		/// @brief Binds a sampler a currently bound sampler container to a currently bound compute pipeline state.
		/// @param samplerBinding Sampler binding.
		void BindCompute(const SamplerBinding& samplerBinding);
		/// @brief Binds views from a currently bound shader data container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings);
		/// @brief Binds samplers a currently bound sampler container to a currently bound compute pipeline state.
		/// @param samplerBindings Sampler bindings.
		void BindCompute(std::span<const SamplerBinding> samplerBindings);
		/// @brief Binds views from a currently bound shader data container and samplers from a currently bound sampler container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		/// @param samplerBindings Sampler bindings.
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;

		/// @brief Dispatches a graphics command.
		/// @param threadGroupCount X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(std::uint32_t threadGroupCount);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X and Y thread group counts.
		/// @remark Z thread group count is set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		/// @brief Dispatches a compute command.
		/// @param threadGroupCount X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(std::uint32_t threadGroupCount);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X and Y thread group counts.
		/// @remark Z thread group count is set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void ISecondaryGraphicsCommandList::BindContainers()
	{
		BindContainers(nullptr, nullptr);
	}

	void ISecondaryGraphicsCommandList::BindContainers(const IShaderDataContainer& shaderDataContainer)
	{
		BindContainers(&shaderDataContainer, nullptr);
	}

	void ISecondaryGraphicsCommandList::BindContainers(const ISamplerContainer& samplerContainer)
	{
		BindContainers(nullptr, &samplerContainer);
	}

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
