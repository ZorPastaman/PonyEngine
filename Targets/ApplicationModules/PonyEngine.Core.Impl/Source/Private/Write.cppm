module;

#include <iostream>

#include "PonyEngine/Utility/Compiler.h"

export module Write;

export import PonyEngine.Module;

void WriteThis()
{
	std::cout << "This!\n";
}

export PONY_DLL_EXPORT void WriteThat()
{
	WriteThis();
}