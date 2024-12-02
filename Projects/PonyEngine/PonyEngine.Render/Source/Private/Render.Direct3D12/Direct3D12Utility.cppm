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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Utility;

import <stdexcept>;

import PonyBase.StringUtility;

import :Direct3D12VertexDataType;

export namespace PonyEngine::Render
{
	/// @brief Gets an index format by the index size.
	/// @param indexSize Index size in bytes. Must be 2 or 4.
	/// @return Index format.
	[[nodiscard("Pure constructor")]]
	constexpr DXGI_FORMAT GetFormat(UINT indexSize);

	/// @brief Gets a vertex format by the parameters.
	/// @param componentSize Vertex component size.
	/// @param componentCount Vertex component count.
	/// @param dataType Vertex data type.
	/// @return Vertex format.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetFormat(UINT componentSize, UINT componentCount, Direct3D12VertexDataType dataType);
}

namespace PonyEngine::Render
{
	constexpr DXGI_FORMAT GetFormat(const UINT indexSize)
	{
		switch (indexSize)
		{
		case 2:
			return DXGI_FORMAT_R16_UINT;
		case 4:
			return DXGI_FORMAT_R32_UINT;
		default: [[unlikely]]
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported index size. Index size: '{}'. Supported index sizes are 2 and 4 only.", indexSize));
		}
	}

	constexpr DXGI_FORMAT GetFormat(const UINT componentSize, const UINT componentCount, const Direct3D12VertexDataType dataType)
	{
		switch (dataType)
		{
		case Direct3D12VertexDataType::Signed:
			switch (componentSize)
			{
			case 1:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R8_SINT;
				case 2:
					return DXGI_FORMAT_R8G8_SINT;
				case 4:
					return DXGI_FORMAT_R8G8B8A8_SINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 1-byte signed supports 1, 2 and 4 counts only.", componentCount));
				}
			case 2:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R16_SINT;
				case 2:
					return DXGI_FORMAT_R16G16_SINT;
				case 4:
					return DXGI_FORMAT_R16G16B16A16_SINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 2-byte signed supports 1, 2 and 4 counts only.", componentCount));
				}
			case 4:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R32_SINT;
				case 2:
					return DXGI_FORMAT_R32G32_SINT;
				case 3:
					return DXGI_FORMAT_R32G32B32_SINT;
				case 4:
					return DXGI_FORMAT_R32G32B32A32_SINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 4-byte signed supports 1, 2, 3 and 4 counts only.", componentCount));
				}
			default: [[unlikely]]
					   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component size. Component size: '{}'. Signed supports 1, 2 and 4 sizes only.", componentSize));
			}
		case Direct3D12VertexDataType::Unsigned:
			switch (componentSize)
			{
			case 1:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R8_UINT;
				case 2:
					return DXGI_FORMAT_R8G8_UINT;
				case 4:
					return DXGI_FORMAT_R8G8B8A8_UINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 1-byte unsigned supports 1, 2 and 4 counts only.", componentCount));
				}
			case 2:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R16_UINT;
				case 2:
					return DXGI_FORMAT_R16G16_UINT;
				case 4:
					return DXGI_FORMAT_R16G16B16A16_UINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 2-byte unsigned supports 1, 2 and 4 counts only.", componentCount));
				}
			case 4:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R32_UINT;
				case 2:
					return DXGI_FORMAT_R32G32_UINT;
				case 3:
					return DXGI_FORMAT_R32G32B32_UINT;
				case 4:
					return DXGI_FORMAT_R32G32B32A32_UINT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 4-byte unsigned supports 1, 2, 3 and 4 counts only.", componentCount));
				}
			default: [[unlikely]]
					   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component size. Component size: '{}'. Unsigned supports 1, 2 and 4 sizes only.", componentSize));
			}
		case Direct3D12VertexDataType::SignedNormalized:
			switch (componentSize)
			{
			case 1:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R8_SNORM;
				case 2:
					return DXGI_FORMAT_R8G8_SNORM;
				case 4:
					return DXGI_FORMAT_R8G8B8A8_SNORM;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 1-byte signed normalized supports 1, 2 and 4 counts only.", componentCount));
				}
			case 2:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R16_SNORM;
				case 2:
					return DXGI_FORMAT_R16G16_SNORM;
				case 4:
					return DXGI_FORMAT_R16G16B16A16_SNORM;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 2-byte signed normalized supports 1, 2 and 4 counts only.", componentCount));
				}
			default: [[unlikely]]
					   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component size. Component size: '{}'. Signed normalized supports 1 and 2 sizes only.", componentSize));
			}
		case Direct3D12VertexDataType::UnsignedNormalized:
			switch (componentSize)
			{
			case 1:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R8_UNORM;
				case 2:
					return DXGI_FORMAT_R8G8_UNORM;
				case 4:
					return DXGI_FORMAT_R8G8B8A8_UNORM;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 1-byte unsigned normalized supports 1, 2 and 4 counts only.", componentCount));
				}
			case 2:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R16_UNORM;
				case 2:
					return DXGI_FORMAT_R16G16_UNORM;
				case 4:
					return DXGI_FORMAT_R16G16B16A16_UNORM;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 2-byte unsigned normalized supports 1, 2 and 4 counts only.", componentCount));
				}
			default: [[unlikely]]
					   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component size. Component size: '{}'. Unsigned normalized supports 1 and 2 sizes only.", componentSize));
			}
		case Direct3D12VertexDataType::Float:
			switch (componentSize)
			{
			case 2:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R16_FLOAT;
				case 2:
					return DXGI_FORMAT_R16G16_FLOAT;
				case 4:
					return DXGI_FORMAT_R16G16B16A16_FLOAT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 2-byte float supports 1, 2 and 4 counts only.", componentCount));
				}
			case 4:
				switch (componentCount)
				{
				case 1:
					return DXGI_FORMAT_R32_FLOAT;
				case 2:
					return DXGI_FORMAT_R32G32_FLOAT;
				case 3:
					return DXGI_FORMAT_R32G32B32_FLOAT;
				case 4:
					return DXGI_FORMAT_R32G32B32A32_FLOAT;
				default: [[unlikely]]
						   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component count. Component count: '{}'. 4-byte float supports 1, 2, 3 and 4 counts only.", componentCount));
				}
			default: [[unlikely]]
					   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported component size. Component size: '{}'. Float supports 2 and 4 sizes only.", componentSize));
			}
		default: [[unlikely]]
				   throw std::invalid_argument(PonyBase::Utility::SafeFormat("Unsupported vertex data type. Vertex data type: '{}'. Supported vertex data types are Signed, Unsigned, Signed Normalized, Unsigned Normalized and Float.", ToString(dataType)));
		}
	}
}
