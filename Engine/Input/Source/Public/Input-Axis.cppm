/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Axis;

import std;

export namespace PonyEngine::Input
{
	using AxisIdType = std::uint8_t; ///< Axis ID type.
	/// @brief Layout concept.
	/// @tparam T Layout type.
	template<typename T>
	concept Layout = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, AxisIdType>;

	/// @brief Input axis.
	class Axis final
	{
	public:
		/// @brief Creates an axis.
		/// @tparam T Layout type.
		/// @param axisId Axis ID.
		template<Layout T> [[nodiscard("Pure constructor")]]
		explicit Axis(T axisId) noexcept;
		[[nodiscard("Pure constructor")]]
		Axis(const Axis& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Axis(Axis&& other) noexcept = default;

		~Axis() noexcept = default;

		/// @brief Gets the layout type.
		/// @return Layout type.
		[[nodiscard("Pure function")]]
		const std::type_info& Layout() const noexcept;
		/// @brief Gets the axis ID.
		/// @return Axis ID.
		[[nodiscard("Pure function")]]
		AxisIdType AxisId() const noexcept;
		/// @brief Gets the axis ID.
		/// @tparam T Layout type.
		/// @return Axis ID.
		template<Input::Layout T> [[nodiscard("Pure function")]]
		T AxisId() const;

		Axis& operator =(const Axis& other) noexcept = default;
		Axis& operator =(Axis&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Axis& other) const noexcept = default;

	private:
		const std::type_info* layout = nullptr; ///< Layout.
		AxisIdType axisId = 0u; ///< Axis ID.
	};
}

export
{
	template<>
	struct std::hash<PonyEngine::Input::Axis> final
	{
		[[nodiscard("Pure function")]]
		size_t operator ()(const PonyEngine::Input::Axis axis) const noexcept
		{
			const std::size_t layoutHash = std::hash<const std::type_info*>()(&axis.Layout());
			const std::size_t axisIdHash = std::hash<PonyEngine::Input::AxisIdType>()(axis.AxisId());

			return (23uz * 31uz + layoutHash) * 31uz + axisIdHash;
		}
	};
}

namespace PonyEngine::Input
{
	template<Layout T>
	Axis::Axis(const T axisId) noexcept :
		layout{&typeid(T)},
		axisId{axisId}
	{
	}

	const std::type_info& Axis::Layout() const noexcept
	{
		return *layout;
	}

	AxisIdType Axis::AxisId() const noexcept
	{
		return axisId;
	}

	template<Input::Layout T>
	T Axis::AxisId() const
	{
#if !NDEBUG
		if (*layout != typeid(T)) [[unlikely]]
		{
			throw std::bad_cast();
		}
#endif

		return static_cast<T>(axisId);
	}
}
