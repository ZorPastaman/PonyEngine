/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:PipelineState;

import <cstdint>;
import <memory>;
import <string>;
import <string_view>;
import <utility>;

import PonyEngine.Render;

import :RootSignature;
import :Shader;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state.
	class PipelineState final : public IPipelineState
	{
	public:
		/// @brief Creates a pipeline state.
		/// @param params Pipeline state parameters.
		/// @param rootSignature Root signature.
		/// @param amplificationShader Amplification shader.
		/// @param meshShader Mesh shader.
		/// @param pixelShader Pixel shader.
		[[nodiscard("Pure constructor")]]
		PipelineState(const PipelineStateParams& params, std::shared_ptr<const class RootSignature>&& rootSignature,
			std::shared_ptr<const Shader>&& amplificationShader, std::shared_ptr<const Shader>&& meshShader, std::shared_ptr<const Shader>&& pixelShader) noexcept;
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

		/// @brief Is the name dirty?
		/// @return @a True if it's dirty; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsNameDirty() const noexcept;
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

		PipelineState& operator =(const PipelineState&) = delete;
		PipelineState& operator =(PipelineState&&) = delete;

	private:
		std::shared_ptr<const class RootSignature> rootSignature; ///< Root signature.

		std::shared_ptr<const Shader> amplificationShader; ///< Amplification shader.
		std::shared_ptr<const Shader> meshShader; ///< Mesh shader.
		std::shared_ptr<const Shader> pixelShader; ///< Pixel shader.

		struct Blend blend; ///< Blend.
		struct Rasterizer rasterizer; ///< Rasterizer.
		struct DepthStencil depthStencil; ///< Depth stencil

		struct ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::int32_t renderQueue; ///< Render queue.
		bool cameraCulling; ///< Is camera culling enabled?

		std::string name; ///< Pipeline state name.

		bool isNameDirty; ///< Is the name dirty?
	};
}

namespace PonyEngine::Render
{
	PipelineState::PipelineState(const PipelineStateParams& params, std::shared_ptr<const class RootSignature>&& rootSignature,
		std::shared_ptr<const Shader>&& amplificationShader, std::shared_ptr<const Shader>&& meshShader, std::shared_ptr<const Shader>&& pixelShader) noexcept :
		rootSignature(std::move(rootSignature)),
		amplificationShader(std::move(amplificationShader)),
		meshShader(std::move(meshShader)),
		pixelShader(std::move(pixelShader)),
		blend(params.blend),
		rasterizer(params.rasterizer),
		depthStencil(params.depthStencil),
		threadGroupCounts(params.threadGroupCounts),
		renderQueue{params.renderQueue},
		cameraCulling(params.cameraCulling),
		name(params.name),
		isNameDirty{true}
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
		isNameDirty = true;
	}

	bool PipelineState::IsNameDirty() const noexcept
	{
		return isNameDirty;
	}

	void PipelineState::ResetDirty() noexcept
	{
		isNameDirty = false;
	}
}
