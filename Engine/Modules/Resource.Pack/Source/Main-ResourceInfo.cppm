/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack:ResourceInfo;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	struct ResourceInfo final
	{
		ResourceID id;
		ResourceType type;
	};
}
