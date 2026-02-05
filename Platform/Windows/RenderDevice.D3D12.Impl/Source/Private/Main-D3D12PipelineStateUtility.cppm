/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12PipelineStateUtility;

import std;

import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :D3D12Utility;

export namespace PonyEngine::RenderDevice::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_RASTERIZER_DESC2 ToRasterizerDesc(const RasterizerParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_FILL_MODE ToFillMode(FillMode fillMode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_CULL_MODE ToCullMode(CullMode cullMode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_LINE_RASTERIZATION_MODE ToLineRasterizationMode(LineRasterizationMode lineRasterizationMode) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_BLEND_DESC ToBlendDesc(const GraphicsPipelineStateParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BLEND ToBlend(BlendFactor blend) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BLEND_OP ToBlendOp(BlendOperation operation) noexcept;
	[[nodiscard("Pure function")]]
	constexpr UINT8 ToWriteMask(ColorComponentMask colorComponents) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_LOGIC_OP ToLogicOp(LogicOperation operation) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_DEPTH_STENCIL_DESC2 ToDepthStencilDesc(const DepthStencilParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_STENCIL_OP ToStencilOp(StencilOperation operation) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
{
	constexpr D3D12_RASTERIZER_DESC2 ToRasterizerDesc(const RasterizerParams& params) noexcept
	{
		return D3D12_RASTERIZER_DESC2
		{
			.FillMode = ToFillMode(params.fillMode),
			.CullMode = ToCullMode(params.cullMode),
			.FrontCounterClockwise = params.counterClockwiseFrontFace,
			.DepthBias = static_cast<FLOAT>(params.depthBias),
			.DepthBiasClamp = static_cast<FLOAT>(params.depthBiasClamp),
			.SlopeScaledDepthBias = static_cast<FLOAT>(params.slopeScaledDepthBias),
			.DepthClipEnable = params.depthClipping,
			.LineRasterizationMode = ToLineRasterizationMode(params.lineRasterizationMode),
			.ForcedSampleCount = 0u,
			.ConservativeRaster = params.conservativeRasterization ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
		};
	}

	constexpr D3D12_FILL_MODE ToFillMode(const FillMode fillMode) noexcept
	{
		switch (fillMode)
		{
		case FillMode::Solid:
			return D3D12_FILL_MODE_SOLID;
		case FillMode::Wireframe:
			return D3D12_FILL_MODE_WIREFRAME;
		default: [[unlikely]]
			assert(false && "Invalid fill mode.");
			return D3D12_FILL_MODE_SOLID;
		}
	}

	constexpr D3D12_CULL_MODE ToCullMode(const CullMode cullMode) noexcept
	{
		switch (cullMode)
		{
		case CullMode::None:
			return D3D12_CULL_MODE_NONE;
		case CullMode::Front:
			return D3D12_CULL_MODE_FRONT;
		case CullMode::Back:
			return D3D12_CULL_MODE_BACK;
		default: [[unlikely]]
			assert(false && "Invalid cull mode.");
			return D3D12_CULL_MODE_NONE;
		}
	}

	constexpr D3D12_LINE_RASTERIZATION_MODE ToLineRasterizationMode(const LineRasterizationMode lineRasterizationMode) noexcept
	{
		switch (lineRasterizationMode)
		{
		case LineRasterizationMode::Aliased:
			return D3D12_LINE_RASTERIZATION_MODE_ALIASED;
		case LineRasterizationMode::AlphaAntialiased:
			return D3D12_LINE_RASTERIZATION_MODE_ALPHA_ANTIALIASED;
		case LineRasterizationMode::QuadrilateralWide:
			return D3D12_LINE_RASTERIZATION_MODE_QUADRILATERAL_WIDE;
		case LineRasterizationMode::QuadrilateralNarrow:
			return D3D12_LINE_RASTERIZATION_MODE_QUADRILATERAL_NARROW;
		default: [[unlikely]]
			assert(false && "Invalid line rasterization mode.");
			return D3D12_LINE_RASTERIZATION_MODE_ALIASED;
		}
	}

	constexpr D3D12_BLEND_DESC ToBlendDesc(const GraphicsPipelineStateParams& params) noexcept
	{
		auto blend = D3D12_BLEND_DESC
		{
			.AlphaToCoverageEnable = params.sample.alphaToCoverage,
			.IndependentBlendEnable = !std::holds_alternative<LogicBlendGroupParams>(params.blend.blendGroup)
		};

		std::visit(Type::Overload
		{
			[&](const BlendGroupParams& p) noexcept
			{
				for (std::size_t i = 0uz; i < std::min(std::size(blend.RenderTarget), p.renderTargetBlend.size()); ++i)
				{
					const RenderTargetBlendParams& rtBlend = p.renderTargetBlend[i];
					if (rtBlend.blend)
					{
						const ColorBlendParams& blendParams = *rtBlend.blend;
						blend.RenderTarget[i] = D3D12_RENDER_TARGET_BLEND_DESC
						{
							.BlendEnable = true,
							.LogicOpEnable = false,
							.SrcBlend = ToBlend(blendParams.sourceColorBlendFactor),
							.DestBlend = ToBlend(blendParams.destinationColorBlendFactor),
							.BlendOp = ToBlendOp(blendParams.colorBlendOperation),
							.SrcBlendAlpha = ToBlend(blendParams.sourceAlphaBlendFactor),
							.DestBlendAlpha = ToBlend(blendParams.destinationAlphaBlendFactor),
							.BlendOpAlpha = ToBlendOp(blendParams.alphaBlendOperation),
							.LogicOp = D3D12_LOGIC_OP_NOOP,
							.RenderTargetWriteMask = ToWriteMask(rtBlend.colorComponentWriteMask)
						};
					}
					else
					{
						blend.RenderTarget[i] = D3D12_RENDER_TARGET_BLEND_DESC
						{
							.BlendEnable = false,
							.LogicOpEnable = false,
							.SrcBlend = D3D12_BLEND_ZERO,
							.DestBlend = D3D12_BLEND_ZERO,
							.BlendOp = D3D12_BLEND_OP_ADD,
							.SrcBlendAlpha = D3D12_BLEND_ZERO,
							.DestBlendAlpha = D3D12_BLEND_ZERO,
							.BlendOpAlpha = D3D12_BLEND_OP_ADD,
							.LogicOp = D3D12_LOGIC_OP_NOOP,
							.RenderTargetWriteMask = ToWriteMask(rtBlend.colorComponentWriteMask)
						};
					}
				}
			},
			[&](const LogicBlendGroupParams& p) noexcept
			{
				const D3D12_LOGIC_OP logicOp = ToLogicOp(p.logicOperation);
				for (std::size_t i = 0uz; i < std::min(std::size(blend.RenderTarget), p.renderTargetBlend.size()); ++i)
				{
					const LogicRenderTargetBlendParams& rtBlend = p.renderTargetBlend[i];
					blend.RenderTarget[i] = D3D12_RENDER_TARGET_BLEND_DESC
					{
						.BlendEnable = false,
						.LogicOpEnable = true,
						.SrcBlend = D3D12_BLEND_ZERO,
						.DestBlend = D3D12_BLEND_ZERO,
						.BlendOp = D3D12_BLEND_OP_ADD,
						.SrcBlendAlpha = D3D12_BLEND_ZERO,
						.DestBlendAlpha = D3D12_BLEND_ZERO,
						.BlendOpAlpha = D3D12_BLEND_OP_ADD,
						.LogicOp = logicOp,
						.RenderTargetWriteMask = ToWriteMask(rtBlend.colorComponentWriteMask)
					};
				}
			}
		}, params.blend.blendGroup);

		return blend;
	}

	constexpr D3D12_BLEND ToBlend(const BlendFactor blend) noexcept
	{
		switch (blend)
		{
		case BlendFactor::Zero:
			return D3D12_BLEND_ZERO;
		case BlendFactor::One:
			return D3D12_BLEND_ONE;
		case BlendFactor::SourceColor:
			return D3D12_BLEND_SRC_COLOR;
		case BlendFactor::OneMinusSourceColor:
			return D3D12_BLEND_INV_SRC_COLOR;
		case BlendFactor::DestinationColor:
			return D3D12_BLEND_DEST_COLOR;
		case BlendFactor::OneMinusDestinationColor:
			return D3D12_BLEND_INV_DEST_COLOR;
		case BlendFactor::SourceAlpha:
			return D3D12_BLEND_SRC_ALPHA;
		case BlendFactor::OneMinusSourceAlpha:
			return D3D12_BLEND_INV_SRC_ALPHA;
		case BlendFactor::DestinationAlpha:
			return D3D12_BLEND_DEST_ALPHA;
		case BlendFactor::OneMinusDestinationAlpha:
			return D3D12_BLEND_INV_DEST_ALPHA;
		case BlendFactor::ConstantColor:
		case BlendFactor::ConstantAlpha:
			return D3D12_BLEND_BLEND_FACTOR;
		case BlendFactor::OneMinusConstantColor:
		case BlendFactor::OneMinusConstantAlpha:
			return D3D12_BLEND_INV_BLEND_FACTOR;
		case BlendFactor::SourceAlphaSaturate:
			return D3D12_BLEND_SRC_ALPHA_SAT;
		case BlendFactor::Source1Color:
			return D3D12_BLEND_SRC1_COLOR;
		case BlendFactor::OneMinusSource1Color:
			return D3D12_BLEND_INV_SRC1_COLOR;
		case BlendFactor::Source1Alpha:
			return D3D12_BLEND_SRC1_ALPHA;
		case BlendFactor::OneMinusSource1Alpha:
			return D3D12_BLEND_INV_SRC1_ALPHA;
		default: [[unlikely]]
			assert(false && "Invalid blend factor.");
			return D3D12_BLEND_ZERO;
		}
	}

	constexpr D3D12_BLEND_OP ToBlendOp(const BlendOperation operation) noexcept
	{
		switch (operation)
		{
		case BlendOperation::Add:
			return D3D12_BLEND_OP_ADD;
		case BlendOperation::Subtract:
			return D3D12_BLEND_OP_SUBTRACT;
		case BlendOperation::ReverseSubtract:
			return D3D12_BLEND_OP_REV_SUBTRACT;
		case BlendOperation::Min:
			return D3D12_BLEND_OP_MIN;
		case BlendOperation::Max:
			return D3D12_BLEND_OP_MAX;
		default: [[unlikely]]
			assert(false && "Invalid blend operation.");
			return D3D12_BLEND_OP_ADD;
		}
	}

	constexpr UINT8 ToWriteMask(const ColorComponentMask colorComponents) noexcept
	{
		UINT8 writeMask = 0u;
		if (Any(ColorComponentMask::Red, colorComponents))
		{
			writeMask |= D3D12_COLOR_WRITE_ENABLE_RED;
		}
		if (Any(ColorComponentMask::Green, colorComponents))
		{
			writeMask |= D3D12_COLOR_WRITE_ENABLE_GREEN;
		}
		if (Any(ColorComponentMask::Blue, colorComponents))
		{
			writeMask |= D3D12_COLOR_WRITE_ENABLE_BLUE;
		}
		if (Any(ColorComponentMask::Alpha, colorComponents))
		{
			writeMask |= D3D12_COLOR_WRITE_ENABLE_ALPHA;
		}

		return writeMask;
	}

	constexpr D3D12_LOGIC_OP ToLogicOp(const LogicOperation operation) noexcept
	{
		switch (operation)
		{
		case LogicOperation::Noop:
			return D3D12_LOGIC_OP_NOOP;
		case LogicOperation::Clear:
			return D3D12_LOGIC_OP_CLEAR;
		case LogicOperation::Set:
			return D3D12_LOGIC_OP_SET;
		case LogicOperation::Copy:
			return D3D12_LOGIC_OP_COPY;
		case LogicOperation::CopyInverted:
			return D3D12_LOGIC_OP_COPY_INVERTED;
		case LogicOperation::Equivalent:
			return D3D12_LOGIC_OP_EQUIV;
		case LogicOperation::Invert:
			return D3D12_LOGIC_OP_INVERT;
		case LogicOperation::And:
			return D3D12_LOGIC_OP_AND;
		case LogicOperation::AndReverse:
			return D3D12_LOGIC_OP_AND_REVERSE;
		case LogicOperation::AndInverted:
			return D3D12_LOGIC_OP_AND_INVERTED;
		case LogicOperation::Nand:
			return D3D12_LOGIC_OP_NAND;
		case LogicOperation::Or:
			return D3D12_LOGIC_OP_OR;
		case LogicOperation::OrReverse:
			return D3D12_LOGIC_OP_OR_REVERSE;
		case LogicOperation::OrInverted:
			return D3D12_LOGIC_OP_OR_INVERTED;
		case LogicOperation::Xor:
			return D3D12_LOGIC_OP_XOR;
		case LogicOperation::Nor:
			return D3D12_LOGIC_OP_NOR;
		default: [[unlikely]]
			assert(false && "Invalid logic operation.");
			return D3D12_LOGIC_OP_NOOP;
		}
	}

	constexpr D3D12_DEPTH_STENCIL_DESC2 ToDepthStencilDesc(const DepthStencilParams& params) noexcept
	{
		auto depthStencil = D3D12_DEPTH_STENCIL_DESC2{};

		if (params.depth)
		{
			const DepthParams& depth = *params.depth;
			depthStencil.DepthEnable = true;
			depthStencil.DepthWriteMask = depth.depthWrite ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
			depthStencil.DepthFunc = ToComparisonFunc(depth.comparisonFunc);
			depthStencil.DepthBoundsTestEnable = depth.depthBoundsTest;
		}
		else
		{
			depthStencil.DepthEnable = false;
			depthStencil.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
			depthStencil.DepthFunc = D3D12_COMPARISON_FUNC_NONE;
			depthStencil.DepthBoundsTestEnable = false;
		}

		if (params.stencil)
		{
			const StencilParams& stencil = *params.stencil;
			depthStencil.StencilEnable = true;
			const StencilOperationParams& front = stencil.frontFace;
			depthStencil.FrontFace = D3D12_DEPTH_STENCILOP_DESC1
			{
				.StencilFailOp = ToStencilOp(front.failOperation),
				.StencilDepthFailOp = ToStencilOp(front.depthFailOperation),
				.StencilPassOp = ToStencilOp(front.passOperation),
				.StencilFunc = ToComparisonFunc(front.stencilFunc),
				.StencilReadMask = front.readMask,
				.StencilWriteMask = front.writeMask
			};
			const StencilOperationParams& back = stencil.backFace;
			depthStencil.BackFace = D3D12_DEPTH_STENCILOP_DESC1
			{
				.StencilFailOp = ToStencilOp(back.failOperation),
				.StencilDepthFailOp = ToStencilOp(back.depthFailOperation),
				.StencilPassOp = ToStencilOp(back.passOperation),
				.StencilFunc = ToComparisonFunc(back.stencilFunc),
				.StencilReadMask = back.readMask,
				.StencilWriteMask = back.writeMask
			};
		}
		else
		{
			depthStencil.StencilEnable = false;
			depthStencil.BackFace = depthStencil.FrontFace = D3D12_DEPTH_STENCILOP_DESC1
			{
				.StencilFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilPassOp = D3D12_STENCIL_OP_KEEP,
				.StencilFunc = D3D12_COMPARISON_FUNC_NONE,
				.StencilReadMask = 0u,
				.StencilWriteMask = 0u
			};
		}

		return depthStencil;
	}

	constexpr D3D12_STENCIL_OP ToStencilOp(const StencilOperation operation) noexcept
	{
		switch (operation)
		{
		case StencilOperation::Keep:
			return D3D12_STENCIL_OP_KEEP;
		case StencilOperation::Zero:
			return D3D12_STENCIL_OP_ZERO;
		case StencilOperation::Replace:
			return D3D12_STENCIL_OP_REPLACE;
		case StencilOperation::Invert:
			return D3D12_STENCIL_OP_INVERT;
		case StencilOperation::IncrementAndClamp:
			return D3D12_STENCIL_OP_INCR_SAT;
		case StencilOperation::DecrementAndClamp:
			return D3D12_STENCIL_OP_DECR_SAT;
		case StencilOperation::IncrementAndWrap:
			return D3D12_STENCIL_OP_INCR;
		case StencilOperation::DecrementAndWrap:
			return D3D12_STENCIL_OP_DECR;
		default: [[unlikely]]
			assert(false && "Invalid stencil operation.");
			return D3D12_STENCIL_OP_KEEP;
		}
	}
}
