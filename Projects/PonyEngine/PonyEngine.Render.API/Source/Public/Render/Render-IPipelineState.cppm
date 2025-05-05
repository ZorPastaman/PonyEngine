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

export module PonyEngine.Render:IPipelineState;

import <cstdint>;

import :IRootSignature;
import :IShader;
import :ThreadGroupCounts;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state.
	class IPipelineState
	{
		INTERFACE_BODY(IPipelineState)

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		virtual const IRootSignature& RootSignature() const noexcept = 0;

		/// @brief Gets the amplification shader.
		/// @return Amplification shader.
		[[nodiscard("Pure function")]]
		virtual const IShader* AmplificationShader() const noexcept = 0;
		/// @brief Gets the mesh shader.
		/// @return Mesh shader.
		[[nodiscard("Pure function")]]
		virtual const IShader& MeshShader() const noexcept = 0;
		/// @brief Gets the pixel shader.
		/// @return Pixel shader.
		[[nodiscard("Pure function")]]
		virtual const IShader& PixelShader() const noexcept = 0;

		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		virtual const ThreadGroupCounts& ThreadGroupCount() const noexcept = 0;
		/// @brief Gets the render queue.
		/// @return Render queue.
		[[nodiscard("Pure function")]]
		virtual std::int32_t RenderQueue() const noexcept = 0;
		/// @brief Is the state transparent?
		/// @return @a True if it's transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTransparent() const noexcept = 0;
		/// @brief Is camera culling enabled?
		/// @return @a True if it's enabled; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool CameraCulling() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
