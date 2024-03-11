/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factories:IWindowFactory;

import PonyEngine.Core;
import PonyEngine.Window;

namespace PonyEngine::Window
{
	/// @brief Window factory.
	export class IWindowFactory
	{
	public:
		/// @brief Creates a window.
		/// @param engine Engine that owns the window.
		/// @return Created window.
		[[nodiscard("Pure function")]]
		virtual IWindow* Create(Core::IEngine& engine) = 0;
		/// @brief Destroys a previously created window.
		/// @param window Window to destroy.
		virtual void Destroy(IWindow* window) = 0;

	protected:
		inline virtual ~IWindowFactory() noexcept = default;
	};
}
