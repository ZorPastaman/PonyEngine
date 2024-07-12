/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystemManager;

import <typeinfo>;

export namespace PonyEngine::Core
{
	/// @brief System manager.
	class ISystemManager
	{
	public:
		ISystemManager(const ISystemManager&) = delete;
		ISystemManager(ISystemManager&&) = delete;

		/// @brief Tries to find a system of the type described by the @p typeInfo.
		/// @param typeInfo System type info.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept = 0;
		/// @brief Tries to find a system of the type @p T.
		/// @tparam T System type.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindSystem() const noexcept;

		ISystemManager& operator =(const ISystemManager&) = delete;
		ISystemManager& operator =(ISystemManager&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystemManager() noexcept = default;

		~ISystemManager() noexcept = default;
	};
}

namespace PonyEngine::Core
{
	template<typename T>
	T* ISystemManager::FindSystem() const noexcept
	{
		return static_cast<T*>(FindSystem(typeid(T)));
	}
}
