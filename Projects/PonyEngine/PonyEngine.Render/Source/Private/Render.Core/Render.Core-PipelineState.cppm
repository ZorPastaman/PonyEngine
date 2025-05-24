/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:PipelineState;

import <cstdint>;
import <memory>;
import <string>;
import <string_view>;
import <utility>;

import PonyEngine.Render;

import :RootSignature;
import :PipelineStateDirtyFlag;
import :Shader;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state.
	class PipelineState final : public IPipelineState
	{
	public:
		/// @brief Creates a pipeline state.
		/// @param params Pipeline state parameters.
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(const PipelineStateParams& params) noexcept;
		PipelineState(const PipelineState&) = delete;
		PipelineState(PipelineState&&) = delete;

		~PipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IRootSignature>& RootSignature() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IShader>& AmplificationShader() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IShader>& MeshShader() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IShader>& PixelShader() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const struct Blend& Blend() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const struct Rasterizer& Rasterizer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const struct DepthStencil& DepthStencil() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const struct ThreadGroupCounts& ThreadGroupCounts() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::int32_t RenderQueue() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool CameraCulling() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the dirty flags.
		/// @return Dirty flags.
		[[nodiscard("Pure function")]]
		PipelineStateDirtyFlag DirtyFlags() const noexcept;
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

		PipelineState& operator =(const PipelineState&) = delete;
		PipelineState& operator =(PipelineState&&) = delete;

	private:
		std::shared_ptr<const IRootSignature> rootSignature; ///< Root signature.

		std::shared_ptr<const IShader> amplificationShader; ///< Amplification shader.
		std::shared_ptr<const IShader> meshShader; ///< Mesh shader.
		std::shared_ptr<const IShader> pixelShader; ///< Pixel shader.

		struct Blend blend; ///< Blend.
		struct Rasterizer rasterizer; ///< Rasterizer.
		struct DepthStencil depthStencil; ///< Depth stencil

		struct ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::int32_t renderQueue; ///< Render queue.
		bool cameraCulling; ///< Is camera culling enabled?

		std::string name; ///< Pipeline state name.

		PipelineStateDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render
{
	PipelineState::PipelineState(const PipelineStateParams& params) noexcept :
		rootSignature(params.rootSignature),
		amplificationShader(params.amplificationShader),
		meshShader(params.meshShader),
		pixelShader(params.pixelShader),
		blend(params.blend),
		rasterizer(params.rasterizer),
		depthStencil(params.depthStencil),
		threadGroupCounts(params.threadGroupCounts),
		renderQueue{params.renderQueue},
		cameraCulling(params.cameraCulling),
		name(params.name),
		dirtyFlags{PipelineStateDirtyFlag::All}
	{
	}

	const std::shared_ptr<const IRootSignature>& PipelineState::RootSignature() const noexcept
	{
		return rootSignature;
	}

	const std::shared_ptr<const IShader>& PipelineState::AmplificationShader() const noexcept
	{
		return amplificationShader;
	}

	const std::shared_ptr<const IShader>& PipelineState::MeshShader() const noexcept
	{
		return meshShader;
	}

	const std::shared_ptr<const IShader>& PipelineState::PixelShader() const noexcept
	{
		return pixelShader;
	}

	const struct Blend& PipelineState::Blend() const noexcept
	{
		return blend;
	}

	const struct Rasterizer& PipelineState::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	const struct DepthStencil& PipelineState::DepthStencil() const noexcept
	{
		return depthStencil;
	}

	const struct ThreadGroupCounts& PipelineState::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	std::int32_t PipelineState::RenderQueue() const noexcept
	{
		return renderQueue;
	}

	bool PipelineState::CameraCulling() const noexcept
	{
		return cameraCulling;
	}

	std::string_view PipelineState::Name() const noexcept
	{
		return name;
	}

	void PipelineState::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		dirtyFlags |= PipelineStateDirtyFlag::Name;
	}

	PipelineStateDirtyFlag PipelineState::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void PipelineState::ResetDirty() noexcept
	{
		dirtyFlags = PipelineStateDirtyFlag::None;
	}
}
