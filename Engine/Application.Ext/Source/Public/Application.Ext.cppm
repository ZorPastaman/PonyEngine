/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Ext;

export import :FlowState;
export import :IApplicationContext;
export import :ILoggerContext;
export import :ILoggerModuleContext;
export import :IModule;
export import :IModuleContext;
export import :IService;
export import :IServiceModuleContext;
export import :ITickableService;
export import :LoggerHandle;
export import :ModuleDataHandle;
export import :ServiceData;
export import :ServiceHandle;

#if PONY_WINDOWS
export import :Windows.IApplicationContext;
#endif
