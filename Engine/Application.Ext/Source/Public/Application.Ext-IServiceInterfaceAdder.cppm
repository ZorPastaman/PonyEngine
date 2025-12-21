/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application.Ext:IServiceInterfaceAdder;

import std;

export namespace PonyEngine::Application
{
	/// @brief Service interface adder.
	class IServiceInterfaceAdder
	{
		INTERFACE_BODY(IServiceInterfaceAdder)

		/// @brief Adds an interface.
		/// @param type Interface type.
		/// @param interface 
		virtual void AddInterface(std::type_index type, void* interface) = 0;
		/// @brief Adds an interface.
		/// @tparam T Interface type.
		/// @param interface Interface.
		template<typename T>
		void AddInterface(T& interface);
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	void IServiceInterfaceAdder::AddInterface(T& interface)
	{
		AddInterface(typeid(T), &interface);
	}
}
