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

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 vertex format.
	class Direct3D12VertexFormat final
	{
	public:
		/// @brief Creates a @p Direct3D12VertexFormat.
		/// @param format Vertex format.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Direct3D12VertexFormat(DXGI_FORMAT format);
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12VertexFormat(const Direct3D12VertexFormat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Direct3D12VertexFormat(Direct3D12VertexFormat&& other) noexcept = default;

		constexpr ~Direct3D12VertexFormat() noexcept = default;

		/// @brief Gets the vertex format.
		/// @return Vertex format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT VertexFormat() const noexcept;
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

		constexpr Direct3D12VertexFormat& operator =(const Direct3D12VertexFormat& other) noexcept = default;
		constexpr Direct3D12VertexFormat& operator =(Direct3D12VertexFormat&& other) noexcept = default;

		/// @brief Checks if the two formats are the same.
		/// @param other Format to compare to.
		/// @return @a True if they're equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Direct3D12VertexFormat& other) const noexcept;

	private:
		DXGI_FORMAT vertexFormat; ///< Vertex format.
		UINT componentSize; ///< Vertex component size.
		UINT componentCount; ///< Vertex component count.
	};
}

namespace PonyEngine::Render
{
	constexpr Direct3D12VertexFormat::Direct3D12VertexFormat(const DXGI_FORMAT format) :
		vertexFormat{format}
	{
		GetVertexFormatInfo(vertexFormat, componentSize, componentCount);
	}

	constexpr DXGI_FORMAT Direct3D12VertexFormat::VertexFormat() const noexcept
	{
		return vertexFormat;
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
		return componentSize * componentCount;
	}

	constexpr bool Direct3D12VertexFormat::operator ==(const Direct3D12VertexFormat& other) const noexcept
	{
		return vertexFormat == other.vertexFormat;
	}
}
