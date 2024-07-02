/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:ObjectInterfaces;

import <typeinfo>;
import <utility>;
import <vector>;

export namespace PonyEngine::Core
{
	class ObjectInterfaces final
	{
	public:
		class ObjectInterfacesIterator final
		{
		public:
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(const ObjectInterfacesIterator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(ObjectInterfacesIterator&& other) noexcept = default;

			~ObjectInterfacesIterator() noexcept = default;

			[[nodiscard("Pure function")]]
			bool IsEnd() const noexcept;

			[[nodiscard("Pure operator")]]
			std::pair<const std::type_info&, void*> operator *() const noexcept;
			ObjectInterfacesIterator& operator ++() noexcept;
			ObjectInterfacesIterator operator ++(int) noexcept;

			ObjectInterfacesIterator& operator =(const ObjectInterfacesIterator& other) noexcept = default;
			ObjectInterfacesIterator& operator =(ObjectInterfacesIterator&& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			bool operator ==(const ObjectInterfacesIterator& other) const noexcept = default;

		private:
			[[nodiscard("Pure constructor")]]
			ObjectInterfacesIterator(const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& begin, const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& end) noexcept;

			std::vector<std::pair<const std::type_info&, void*>>::const_iterator current;
			std::vector<std::pair<const std::type_info&, void*>>::const_iterator end;

			friend ObjectInterfaces;
		};

		[[nodiscard("Pure constructor")]]
		ObjectInterfaces() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(const ObjectInterfaces& other) = default;
		[[nodiscard("Pure constructor")]]
		ObjectInterfaces(ObjectInterfaces&& other) noexcept = default;

		~ObjectInterfaces() noexcept = default;

		void AddObjectInterface(const std::type_info& typeInfo, void* pointer);
		[[nodiscard("Pure function")]]
		ObjectInterfacesIterator GetObjectInterfacesIterator() const noexcept;

		ObjectInterfaces& operator =(const ObjectInterfaces& other) = default;
		ObjectInterfaces& operator =(ObjectInterfaces&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const ObjectInterfaces& other) const noexcept = default;

	private:
		std::vector<std::pair<const std::type_info&, void*>> interfaces;
	};
}

namespace PonyEngine::Core
{
	ObjectInterfaces::ObjectInterfacesIterator::ObjectInterfacesIterator(const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& begin, const std::vector<std::pair<const std::type_info&, void*>>::const_iterator& end) noexcept :
		current(begin),
		end(end)
	{
	}

	bool ObjectInterfaces::ObjectInterfacesIterator::IsEnd() const noexcept
	{
		return current == end;
	}

	std::pair<const std::type_info&, void*> ObjectInterfaces::ObjectInterfacesIterator::operator *() const noexcept
	{
		return *current;
	}

	ObjectInterfaces::ObjectInterfacesIterator& ObjectInterfaces::ObjectInterfacesIterator::operator ++() noexcept
	{
		++current;

		return *this;
	}

	ObjectInterfaces::ObjectInterfacesIterator ObjectInterfaces::ObjectInterfacesIterator::operator ++(int) noexcept
	{
		const ObjectInterfacesIterator temp = *this;
		++(*this);

		return temp;
	}

	void ObjectInterfaces::AddObjectInterface(const std::type_info& typeInfo, void* const pointer)
	{
		const auto pair = std::pair<const std::type_info&, void*>(typeInfo, pointer);
		interfaces.push_back(pair);
	}

	ObjectInterfaces::ObjectInterfacesIterator ObjectInterfaces::GetObjectInterfacesIterator() const noexcept
	{
		return ObjectInterfacesIterator(interfaces.cbegin(), interfaces.cend());
	}
}
