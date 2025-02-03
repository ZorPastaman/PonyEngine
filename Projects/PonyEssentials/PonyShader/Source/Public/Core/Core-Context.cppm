/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Core:Context;

import :ThreadGroupCounts;

export namespace PonyShader::Core
{
	struct Context final
	{
		ThreadGroupCounts dispatchThreadGroupCounts;
		ThreadGroupCounts materialThreadGroupCounts;
		ThreadGroupCounts meshThreadGroupCounts;
	};
}
