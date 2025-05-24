/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Core:IPipelineAgent;

import <cstdint>;
import <functional>;
import <span>;

import PonyMath.Color;
import PonyMath.Shape;

import PonyEngine.Render;

import :ConstantData;

export namespace PonyEngine::Render
{
	/// @brief Pipeline agent interface.
	class IPipelineAgent
	{
		INTERFACE_BODY(IPipelineAgent)

		virtual void BeginTick() = 0;
		virtual void EndTick() = 0;

		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;

		virtual void BeginTarget(const IAttachment* renderTarget, const IAttachment* depthStencil) = 0;
		virtual void EndTarget(const IAttachment* renderTarget, const IAttachment* depthStencil) = 0;

		virtual void SetResources(std::span<const ConstantData> data, std::span<std::reference_wrapper<const IBuffer>> buffers, 
			std::span<std::reference_wrapper<const ITexture>> textures, std::span<std::reference_wrapper<const IAttachment>> attachments) = 0;

		virtual void ClearColor(const IAttachment& attachment, const PonyMath::Color::RGBA<float>& color) = 0;
		virtual void ClearColor(const IAttachment& attachment, const PonyMath::Color::RGBA<float>& color, const PonyMath::Shape::Rect<float>& rect) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, float depth) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, std::uint8_t stencil) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, float depth, std::uint8_t stencil) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, float depth, const PonyMath::Shape::Rect<float>& rect) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, std::uint8_t stencil, const PonyMath::Shape::Rect<float>& rect) = 0;
		virtual void ClearDepthStencil(const IAttachment& attachment, float depth, std::uint8_t stencil, const PonyMath::Shape::Rect<float>& rect) = 0;

		virtual void SetViewport(const PonyMath::Shape::Rect<float>& rect) = 0;

		virtual void SetPipelineState(const IPipelineState& pipelineState) = 0;
		virtual void BindData(const void* data, std::uint32_t subElementIndex, std::uint32_t slotIndex) = 0;
		virtual void BindBuffer(const IBuffer& buffer, std::uint32_t dataTypeIndex, std::uint32_t slotIndex) = 0;
		virtual void BindTexture(const ITexture& texture, std::uint32_t slotIndex) = 0;
		virtual void Dispatch(std::uint32_t x, std::uint32_t y, std::uint32_t z) = 0;

		virtual void Resolve(const IAttachment& source, const IAttachment& destination) = 0;

		virtual void Output(const IAttachment& source) = 0;

		virtual void Upload() = 0;

		virtual void Clear() noexcept = 0;
	};
}