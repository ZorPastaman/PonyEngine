/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:AtomicSupport;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Atomic operation support.
	struct AtomicSupport final
	{
		bool atomicInt64 = false; ///< Are atomic operations on int64 supported?
		bool groupSharedAtomicInt64 = false; ///< Are atomic operations on group shared int64 supported?
		bool atomicInt64OnDescriptorHeap = false; ///< Are atomic operations on int64 from descriptor heaps supported?
	};
}
