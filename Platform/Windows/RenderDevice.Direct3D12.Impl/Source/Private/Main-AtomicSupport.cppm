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
	struct AtomicSupport final
	{
		bool atomicInt64 = false;
		bool groupSharedAtomicInt64 = false;
		bool atomicInt64OnDescriptorHeap = false;
	};
}
