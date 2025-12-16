/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Ray;

import std;

import :Common;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Ray bounds.
	/// @tparam T Value type.
	template<std::floating_point T>
	struct RayBounds final
	{
		/// @brief Gets a full ray bounds [0, +inf).
		/// @return Full ray bounds.
		[[nodiscard("Pure function")]]
		static constexpr const RayBounds& Full() noexcept;
		/// @brief Gets a ray bounds that are default for intersection tests [default relative tolerance, +inf).
		/// @return Intersection ray bounds.
		[[nodiscard("Pure function")]]
		static constexpr const RayBounds& Intersection() noexcept;
		/// @brief Gets an infinite ray bounds (-inf, +inf).
		/// @return Infinite ray bounds.
		[[nodiscard("Pure function")]]
		static constexpr const RayBounds& Infinite() noexcept;

		T min = T{0}; /// Minimum bound.
		T max = std::numeric_limits<T>::infinity(); ///< Maximum bound.
	};

	/// @brief Ray.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	class Ray final
	{
	public:
		using ValueType = T; ///< Component type.
		using OriginType = Vector<T, Size>; ///< Origin type.
		using DirectionType = Vector<T, Size>; ///< Direction type.

		static constexpr std::size_t Dimension = Size; ///< Dimension.

		/// @brief Creates a ray with a zero ray.
		[[nodiscard("Pure constructor")]]
		Ray() noexcept;
		/// @brief Creates a ray.
		/// @param origin Ray origin.
		/// @param direction Ray direction. It's normalized automatically with a fallback to a zero vector.
		[[nodiscard("Pure constructor")]]
		Ray(const Vector<T, Size>& origin, const Vector<T, Size>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		Ray(const Ray& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Ray(Ray&& other) noexcept = default;

		~Ray() noexcept = default;

		/// @brief Creates a ray that starts at the @p origin and looks at the @p target.
		/// @param origin Ray origin.
		/// @param target Ray target.
		/// @return Ray.
		[[nodiscard("Pure function")]]
		static Ray CreateByTarget(const Vector<T, Size>& origin, const Vector<T, Size>& target) noexcept;

		/// @brief Gets the ray origin.
		/// @return Origin.
		[[nodiscard("Pure constructor")]]
		const Vector<T, Size>& Origin() const noexcept;
		/// @brief Sets the ray origin.
		/// @param origin Origin.
		void Origin(const Vector<T, Size>& origin) noexcept;
		/// @brief Gets the ray direction.
		/// @return Direction.
		[[nodiscard("Pure constructor")]]
		const Vector<T, Size>& Direction() const noexcept;
		/// @brief Sets the ray direction.
		/// @param direction Direction. It's normalized automatically with a fallback to a zero vector.
		void Direction(const Vector<T, Size>& direction) noexcept;

		/// @brief Creates a ray with the same origin but an opposite direction.
		/// @return Flipped ray.
		[[nodiscard("Pure function")]]
		Ray Flipped() const noexcept;
		/// @brief Sets an opposite direction.
		void Flip() noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if they are all finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Projects the @p point onto the ray.
		/// @param point Point to project.
		/// @param bounds Ray bounds.
		/// @return Projected point.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Project(const Vector<T, Size>& point, const RayBounds<T>& bounds = RayBounds<T>::Full()) const noexcept;
		/// @brief Normalizes the @p point.
		/// @param point Point to normalize.
		/// @return Normalized point.
		[[nodiscard("Pure function")]]
		T Normalize(const Vector<T, Size>& point) const noexcept;
		/// @brief Unnormalizes a point by its normalized @p value.
		/// @param value Normalized value.
		/// @return Unnormalized point.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Unnormalize(T value) const noexcept;

		/// @brief Converts the ray to a ray of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit operator Ray<U, Size>() const noexcept;

		Ray& operator =(const Ray& other) noexcept = default;
		Ray& operator =(Ray&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Ray& other) const noexcept = default;

	private:
		Vector<T, Size> origin; ///< Ray origin.
		Vector<T, Size> direction; ///< Ray direction.
	};

	/// @brief Ray 1D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Ray1D = Ray<T, 1>;
	/// @brief Ray 2D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Ray2D = Ray<T, 2>;
	/// @brief Ray 3D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Ray3D = Ray<T, 3>;

	/// @brief Checks if the two rays are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param tolerance Tolerance.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Ray<T, Size>& lhs, const Ray<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept requires (Size >= 1);
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr const RayBounds<T>& RayBounds<T>::Full() noexcept
	{
		static constexpr auto FullBounds = RayBounds{.min = T{0}, .max = std::numeric_limits<T>::infinity()};
		return FullBounds;
	}

	template<std::floating_point T>
	constexpr const RayBounds<T>& RayBounds<T>::Intersection() noexcept
	{
		static constexpr auto IntersectionBounds = RayBounds{.min = Tolerance<T>().relative, .max = std::numeric_limits<T>::infinity()};
		return IntersectionBounds;
	}

	template<std::floating_point T>
	constexpr const RayBounds<T>& RayBounds<T>::Infinite() noexcept
	{
		static constexpr auto InfiniteBounds = RayBounds{.min = -std::numeric_limits<T>::infinity(), .max = std::numeric_limits<T>::infinity()};
		return InfiniteBounds;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Ray<T, Size>::Ray() noexcept :
		origin(Vector<T, Size>::Zero()),
		direction(Vector<T, Size>::Zero())
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Ray<T, Size>::Ray(const Vector<T, Size>& origin, const Vector<T, Size>& direction) noexcept :
		origin(origin),
		direction(direction.Normalized(Vector<T, Size>::Zero()))
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Ray<T, Size> Ray<T, Size>::CreateByTarget(const Vector<T, Size>& origin, const Vector<T, Size>& target) noexcept
	{
		return Ray(origin, target - origin);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	const Vector<T, Size>& Ray<T, Size>::Origin() const noexcept
	{
		return origin;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Ray<T, Size>::Origin(const Vector<T, Size>& origin) noexcept
	{
		this->origin = origin;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	const Vector<T, Size>& Ray<T, Size>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Ray<T, Size>::Direction(const Vector<T, Size>& direction) noexcept
	{
		this->direction = direction.Normalized(Vector<T, Size>::Zero());
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Ray<T, Size> Ray<T, Size>::Flipped() const noexcept
	{
		Ray flipped;
		flipped.origin = origin;
		flipped.direction = -direction;

		return flipped;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Ray<T, Size>::Flip() noexcept
	{
		direction = -direction;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	bool Ray<T, Size>::IsFinite() const noexcept
	{
		return origin.IsFinite() && direction.IsFinite();
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Vector<T, Size> Ray<T, Size>::Project(const Vector<T, Size>& point, const RayBounds<T>& bounds) const noexcept
	{
		const T normalized = std::clamp(Normalize(point), bounds.min, bounds.max);

		return Unnormalize(normalized);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	T Ray<T, Size>::Normalize(const Vector<T, Size>& point) const noexcept
	{
		return Dot(direction, point - origin);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Vector<T, Size> Ray<T, Size>::Unnormalize(const T value) const noexcept
	{
		return origin + direction * value;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	template<std::floating_point U>
	Ray<T, Size>::operator Ray<U, Size>() const noexcept
	{
		return Ray<U, Size>(static_cast<Vector<U, Size>>(origin), static_cast<Vector<U, Size>>(direction));
	}

	template<std::floating_point T, std::size_t Size>
	bool AreAlmostEqual(const Ray<T, Size>& lhs, const Ray<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept requires (Size >= 1)
	{
		return AreAlmostEqual(lhs.Origin(), rhs.Origin(), tolerance) && AreAlmostEqual(std::min(Dot(lhs.Direction(), rhs.Direction()), T{1}), T{1}, tolerance);
	}
}
