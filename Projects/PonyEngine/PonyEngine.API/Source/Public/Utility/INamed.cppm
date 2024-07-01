/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Utility:INamed;

export namespace PonyEngine::Utility
{
	/// @brief Object that has a name.
	class INamed
	{
	public:
		/// @brief Gets a name of an object.
		/// @return Name of an object.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

	protected:
		~INamed() noexcept = default;
	};
}
