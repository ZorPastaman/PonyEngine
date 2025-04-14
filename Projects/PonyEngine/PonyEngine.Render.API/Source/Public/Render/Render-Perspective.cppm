/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Perspective;

export namespace PonyEngine::Render
{
	/// @brief Perspective projection parameters.
	struct Perspective final
	{
		float fov; ///< Vertical field of view in radians.
		float aspect; ///< Width to height aspect ratio.
		float nearPlane; ///< Near plane distance.
		float farPlane; ///< Far plane distance.
	};
}
