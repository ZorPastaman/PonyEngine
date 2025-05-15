/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail.PixelHandlers:PixelHandler;

import :IPixelHandler;

export namespace PonyEngine::Render
{
	/// @brief Pixel handler.
	class PixelHandler : public IPixelHandler
	{
	public:
		virtual ~PixelHandler() noexcept = default;

	protected:
		[[nodiscard("Pure constructor")]]
		PixelHandler() noexcept = default;
		PixelHandler(const PixelHandler&) = delete;
		PixelHandler(PixelHandler&&) = delete;

		PixelHandler& operator =(const PixelHandler&) = delete;
		PixelHandler& operator =(PixelHandler&&) = delete;
	};
}
