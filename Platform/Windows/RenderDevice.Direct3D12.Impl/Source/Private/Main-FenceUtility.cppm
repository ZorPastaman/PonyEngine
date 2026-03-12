/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:FenceUtility;

import std;

import PonyEngine.RenderDevice;

import :Fence;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	Fence& ToNativeFence(IFence& fence);
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	const Fence& ToNativeFence(const IFence& fence);
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	Fence* ToNativeFence(IFence* fence);
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	const Fence* ToNativeFence(const IFence* fence);
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	Fence& ToNativeFenceNotNullptr(IFence* fence);
	/// @brief Casts the engine fence to a native fence.
	/// @param fence Engine fence.
	/// @return Native fence.
	[[nodiscard("Pure function")]]
	const Fence& ToNativeFenceNotNullptr(const IFence* fence);
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Fence& ToNativeFence(IFence& fence)
	{
#ifndef NDEBUG
		if (typeid(fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return static_cast<Fence&>(fence);
	}

	const Fence& ToNativeFence(const IFence& fence)
	{
#ifndef NDEBUG
		if (typeid(fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return static_cast<const Fence&>(fence);
	}

	Fence* ToNativeFence(IFence*const  fence)
	{
#ifndef NDEBUG
		if (fence && typeid(*fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return static_cast<Fence*>(fence);
	}

	const Fence* ToNativeFence(const IFence* fence)
	{
#ifndef NDEBUG
		if (fence && typeid(*fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return static_cast<const Fence*>(fence);
	}

	Fence& ToNativeFenceNotNullptr(IFence* fence)
	{
#ifndef NDEBUG
		if (!fence || typeid(*fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return *static_cast<Fence*>(fence);
	}

	const Fence& ToNativeFenceNotNullptr(const IFence* fence)
	{
#ifndef NDEBUG
		if (!fence || typeid(*fence) != typeid(Fence)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid fence");
		}
#endif

		return *static_cast<const Fence*>(fence);
	}
}
