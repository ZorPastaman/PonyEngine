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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12VertexFormat;

import <stdexcept>;

import PonyBase.StringUtility;

import :Direct3D12Utility;
import :Direct3D12VertexDataType;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 vertex format.
	class Direct3D12VertexFormat final
	{
	public:
		/// @brief Creates a @p Direct3D12VertexFormat.
		/// @param componentSize Vertex component size in bytes.
		/// @param componentCount Vertex component count.
		/// @param dataType Vertex data type.
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12VertexFormat(UINT componentSize, UINT componentCount, Direct3D12VertexDataType dataType);
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12VertexFormat(const Direct3D12VertexFormat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12VertexFormat(Direct3D12VertexFormat&& other) noexcept = default;

		constexpr ~Direct3D12VertexFormat() noexcept = default;

		/// @brief Gets the vertex component size.
		/// @return Vertex component size.
		[[nodiscard("Pure function")]]
		constexpr UINT ComponentSize() const noexcept;
		/// @brief Gets the vertex component count.
		/// @return Vertex component count.
		[[nodiscard("Pure function")]]
		constexpr UINT ComponentCount() const noexcept;
		/// @brief Gets the vertex size.
		/// @return Vertex size in bytes.
		[[nodiscard("Pure function")]]
		constexpr UINT VertexSize() const noexcept;
		/// @brief Gets the vertex format.
		/// @return Vertex format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT VertexFormat() const noexcept;

		constexpr Direct3D12VertexFormat& operator =(const Direct3D12VertexFormat& other) noexcept = default;
		constexpr Direct3D12VertexFormat& operator =(Direct3D12VertexFormat&& other) noexcept = default;

	private:
		UINT componentSize; ///< Vertex component size.
		UINT componentCount; ///< Vertex component count.
		Direct3D12VertexDataType dataType; ///< Vertex data type.
		DXGI_FORMAT vertexFormat; ///< Vertex format.
	};
}

namespace PonyEngine::Render
{
	constexpr Direct3D12VertexFormat::Direct3D12VertexFormat(const UINT componentSize, const UINT componentCount, const Direct3D12VertexDataType dataType) :
		componentSize{componentSize},
		componentCount{componentCount},
		dataType{dataType},
		vertexFormat{GetFormat(this->componentSize, this->componentCount, this->dataType)}
	{
	}

	constexpr UINT Direct3D12VertexFormat::ComponentSize() const noexcept
	{
		return componentSize;
	}

	constexpr UINT Direct3D12VertexFormat::ComponentCount() const noexcept
	{
		return componentCount;
	}

	constexpr UINT Direct3D12VertexFormat::VertexSize() const noexcept
	{
		return ComponentSize() * ComponentCount();
	}

	constexpr DXGI_FORMAT Direct3D12VertexFormat::VertexFormat() const noexcept
	{
		return vertexFormat;
	}
}
