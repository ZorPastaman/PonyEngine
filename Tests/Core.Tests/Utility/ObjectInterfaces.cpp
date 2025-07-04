/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Utility;

struct IFoo
{
	virtual ~IFoo() = default;
	virtual int Foo() const = 0;
};
struct IBar
{
	virtual ~IBar() = default;
	virtual int Bar() const = 0;
};

struct FooBar final : IFoo, IBar
{
	virtual int Foo() const override { return 42; }
	virtual int Bar() const override { return 24; }
};

TEST_CASE("ObjectInterfaces: AddInterface pointer", "[Utility][ObjectInterfaces]")
{
	PonyEngine::Utility::ObjectInterfaces interfaces;
	FooBar obj;

	interfaces.AddInterface(typeid(IFoo), static_cast<IFoo*>(&obj));
	REQUIRE(interfaces.Capacity() == 1z);
	REQUIRE(interfaces.Count() == 1z);
	REQUIRE(interfaces.Span().size() == 1z);
	REQUIRE(interfaces[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces.Span()[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces.Span()[0].second == static_cast<IFoo*>(&obj));

	interfaces.AddInterface(typeid(IBar), static_cast<IBar*>(&obj));
	REQUIRE(interfaces.Capacity() == 2z);
	REQUIRE(interfaces.Count() == 2z);
	REQUIRE(interfaces.Span().size() == 2z);
	REQUIRE(interfaces[1].first.get() == typeid(IBar));
	REQUIRE(interfaces[1].second == static_cast<IBar*>(&obj));
	REQUIRE(interfaces.Span()[1].first.get() == typeid(IBar));
	REQUIRE(interfaces.Span()[1].second == static_cast<IBar*>(&obj));
}

TEST_CASE("ObjectInterfaces: AddInterface template", "[Utility][ObjectInterfaces]")
{
	PonyEngine::Utility::ObjectInterfaces interfaces;
	FooBar obj;

	interfaces.AddInterface<IFoo>(obj);
	REQUIRE(interfaces.Capacity() == 1z);
	REQUIRE(interfaces.Count() == 1z);
	REQUIRE(interfaces.Span().size() == 1z);
	REQUIRE(interfaces[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces.Span()[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces.Span()[0].second == static_cast<IFoo*>(&obj));

	interfaces.AddInterface<IBar>(obj);
	REQUIRE(interfaces.Capacity() == 2z);
	REQUIRE(interfaces.Count() == 2z);
	REQUIRE(interfaces.Span().size() == 2z);
	REQUIRE(interfaces[1].first.get() == typeid(IBar));
	REQUIRE(interfaces[1].second == static_cast<IBar*>(&obj));
	REQUIRE(interfaces.Span()[1].first.get() == typeid(IBar));
	REQUIRE(interfaces.Span()[1].second == static_cast<IBar*>(&obj));
}

TEST_CASE("ObjectInterfaces: AddInterfaces", "[Utility][ObjectInterfaces]")
{
	PonyEngine::Utility::ObjectInterfaces interfaces;
	FooBar obj;

	interfaces.AddInterfaces<FooBar, IFoo, IBar>(obj);
	REQUIRE(interfaces.Capacity() == 2z);
	REQUIRE(interfaces.Count() == 2z);
	REQUIRE(interfaces.Span().size() == 2z);
	REQUIRE(interfaces[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces.Span()[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces.Span()[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces[1].first.get() == typeid(IBar));
	REQUIRE(interfaces[1].second == static_cast<IBar*>(&obj));
	REQUIRE(interfaces.Span()[1].first.get() == typeid(IBar));
	REQUIRE(interfaces.Span()[1].second == static_cast<IBar*>(&obj));
}

TEST_CASE("ObjectInterfaces: AddInterfacesDeduced", "[Utility][ObjectInterfaces]")
{
	PonyEngine::Utility::ObjectInterfaces interfaces;
	FooBar obj;

	interfaces.AddInterfacesDeduced<IFoo, IBar>(obj);
	REQUIRE(interfaces.Capacity() == 2z);
	REQUIRE(interfaces.Count() == 2z);
	REQUIRE(interfaces.Span().size() == 2z);
	REQUIRE(interfaces[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces.Span()[0].first.get() == typeid(IFoo));
	REQUIRE(interfaces.Span()[0].second == static_cast<IFoo*>(&obj));
	REQUIRE(interfaces[1].first.get() == typeid(IBar));
	REQUIRE(interfaces[1].second == static_cast<IBar*>(&obj));
	REQUIRE(interfaces.Span()[1].first.get() == typeid(IBar));
	REQUIRE(interfaces.Span()[1].second == static_cast<IBar*>(&obj));
}

TEST_CASE("ObjectInterfaces: Reserve", "[Utility][ObjectInterfaces]")
{
	PonyEngine::Utility::ObjectInterfaces interfaces;
	interfaces.Reserve(10z);
	REQUIRE(interfaces.Capacity() == 10z);
	REQUIRE(interfaces.Count() == 0z);
	REQUIRE(interfaces.Span().size() == 0z);
}
