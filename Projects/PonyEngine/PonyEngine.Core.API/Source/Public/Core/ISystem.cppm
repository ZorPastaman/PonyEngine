/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

export namespace PonyEngine::Core
{
	/// @brief System.
	class ISystem
	{
	public:
		ISystem(const ISystem&) = delete;
		ISystem(ISystem&&) = delete;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0; // TODO: try string_view instead of char*

		ISystem& operator =(const ISystem&) = delete;
		ISystem& operator =(ISystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystem() noexcept = default;

		~ISystem() noexcept = default;
	};
}
