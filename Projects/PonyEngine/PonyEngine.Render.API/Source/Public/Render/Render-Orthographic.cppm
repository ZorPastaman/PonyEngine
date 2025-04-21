/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Orthographic;

export namespace PonyEngine::Render
{
	/// @brief Orthographic projection parameters.
	struct Orthographic final
	{
		float width; ///< Width.
		float height; ///< Height.
		float nearPlane; ///< Near plane distance.
		float farPlane; ///< Far plane distance.
	};
}
