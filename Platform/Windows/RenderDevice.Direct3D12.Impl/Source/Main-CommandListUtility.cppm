/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandListUtility;

import std;

import PonyEngine.RenderDevice;

import :BundleCommandList;
import :ComputeCommandList;
import :CopyCommandList;
import :GraphicsCommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	GraphicsCommandList& ToNativeCommandList(IGraphicsCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const GraphicsCommandList& ToNativeCommandList(const IGraphicsCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	GraphicsCommandList* ToNativeCommandList(IGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const GraphicsCommandList* ToNativeCommandList(const IGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	GraphicsCommandList* ToNativeCommandListNotNullptr(IGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const GraphicsCommandList* ToNativeCommandListNotNullptr(const IGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	ComputeCommandList& ToNativeCommandList(IComputeCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const ComputeCommandList& ToNativeCommandList(const IComputeCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	ComputeCommandList* ToNativeCommandList(IComputeCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const ComputeCommandList* ToNativeCommandList(const IComputeCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	ComputeCommandList* ToNativeCommandListNotNullptr(IComputeCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const ComputeCommandList* ToNativeCommandListNotNullptr(const IComputeCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	CopyCommandList& ToNativeCommandList(ICopyCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const CopyCommandList& ToNativeCommandList(const ICopyCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	CopyCommandList* ToNativeCommandList(ICopyCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const CopyCommandList* ToNativeCommandList(const ICopyCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	CopyCommandList* ToNativeCommandListNotNullptr(ICopyCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const CopyCommandList* ToNativeCommandListNotNullptr(const ICopyCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	BundleCommandList& ToNativeCommandList(ISecondaryGraphicsCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const BundleCommandList& ToNativeCommandList(const ISecondaryGraphicsCommandList& commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	BundleCommandList* ToNativeCommandList(ISecondaryGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const BundleCommandList* ToNativeCommandList(const ISecondaryGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	BundleCommandList* ToNativeCommandListNotNullptr(ISecondaryGraphicsCommandList* commandList);
	/// @brief Casts the engine command list to a native command list.
	/// @param commandList Engine command list.
	/// @return Native command list.
	[[nodiscard("Pure function")]]
	const BundleCommandList* ToNativeCommandListNotNullptr(const ISecondaryGraphicsCommandList* commandList);
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsCommandList& ToNativeCommandList(IGraphicsCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<GraphicsCommandList&>(commandList);
	}

	const GraphicsCommandList& ToNativeCommandList(const IGraphicsCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const GraphicsCommandList&>(commandList);
	}

	GraphicsCommandList* ToNativeCommandList(IGraphicsCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<GraphicsCommandList*>(commandList);
	}

	const GraphicsCommandList* ToNativeCommandList(const IGraphicsCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const GraphicsCommandList*>(commandList);
	}

	GraphicsCommandList* ToNativeCommandListNotNullptr(IGraphicsCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<GraphicsCommandList*>(commandList);
	}

	const GraphicsCommandList* ToNativeCommandListNotNullptr(const IGraphicsCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(GraphicsCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const GraphicsCommandList*>(commandList);
	}

	ComputeCommandList& ToNativeCommandList(IComputeCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<ComputeCommandList&>(commandList);
	}

	const ComputeCommandList& ToNativeCommandList(const IComputeCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const ComputeCommandList&>(commandList);
	}

	ComputeCommandList* ToNativeCommandList(IComputeCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<ComputeCommandList*>(commandList);
	}

	const ComputeCommandList* ToNativeCommandList(const IComputeCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const ComputeCommandList*>(commandList);
	}

	ComputeCommandList* ToNativeCommandListNotNullptr(IComputeCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<ComputeCommandList*>(commandList);
	}

	const ComputeCommandList* ToNativeCommandListNotNullptr(const IComputeCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(ComputeCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const ComputeCommandList*>(commandList);
	}

	CopyCommandList& ToNativeCommandList(ICopyCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<CopyCommandList&>(commandList);
	}

	const CopyCommandList& ToNativeCommandList(const ICopyCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const CopyCommandList&>(commandList);
	}

	CopyCommandList* ToNativeCommandList(ICopyCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<CopyCommandList*>(commandList);
	}

	const CopyCommandList* ToNativeCommandList(const ICopyCommandList* commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const CopyCommandList*>(commandList);
	}

	CopyCommandList* ToNativeCommandListNotNullptr(ICopyCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<CopyCommandList*>(commandList);
	}

	const CopyCommandList* ToNativeCommandListNotNullptr(const ICopyCommandList* commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(CopyCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const CopyCommandList*>(commandList);
	}

	BundleCommandList& ToNativeCommandList(ISecondaryGraphicsCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<BundleCommandList&>(commandList);
	}

	const BundleCommandList& ToNativeCommandList(const ISecondaryGraphicsCommandList& commandList)
	{
#ifndef NDEBUG
		if (typeid(commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const BundleCommandList&>(commandList);
	}

	BundleCommandList* ToNativeCommandList(ISecondaryGraphicsCommandList* const commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<BundleCommandList*>(commandList);
	}

	const BundleCommandList* ToNativeCommandList(const ISecondaryGraphicsCommandList* const commandList)
	{
#ifndef NDEBUG
		if (commandList && typeid(*commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const BundleCommandList*>(commandList);
	}

	BundleCommandList* ToNativeCommandListNotNullptr(ISecondaryGraphicsCommandList* const commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<BundleCommandList*>(commandList);
	}

	const BundleCommandList* ToNativeCommandListNotNullptr(const ISecondaryGraphicsCommandList* const commandList)
	{
#ifndef NDEBUG
		if (!commandList || typeid(*commandList) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid command list");
		}
#endif

		return static_cast<const BundleCommandList*>(commandList);
	}
}
