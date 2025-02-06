/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Frustum;

import <array>;
import <concepts>;
import <span>;

import PonyMath.Core;

import :Plane;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Frustum final
	{
	public:
		using ValueType = T;

		static constexpr std::size_t LeftIndex = 0;
		static constexpr std::size_t RightIndex = 1;
		static constexpr std::size_t BottomIndex = 2;
		static constexpr std::size_t TopIndex = 3;
		static constexpr std::size_t NearIndex = 4;
		static constexpr std::size_t FarIndex = 5;
		static constexpr std::size_t PlaneCount = 6;

		[[nodiscard("Pure constructor")]]
		constexpr Frustum() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Frustum(const Plane<T>& left, const Plane<T>& right, const Plane<T>& bottom, const Plane<T>& top, const Plane<T>& near, const Plane<T>& far) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit Frustum(const Core::Matrix4x4<T>& vp) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Frustum(std::span<const Plane<T>, 6> planes) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Frustum(const Frustum& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Frustum(Frustum&& other) noexcept = default;

		constexpr ~Frustum() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Left() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Left() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Right() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Right() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Bottom() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Bottom() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Top() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Top() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Near() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Near() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Plane<T>& Far() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Plane<T>& Far() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector3<T>, 8> Corners() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> CenterNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> CenterFar() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T WidthNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T WidthFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T HeightNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T HeightFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T DepthSlant() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		[[nodiscard("Pure function")]]
		T Volume() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;

		constexpr void Set(std::span<const Plane<T>, 6> planesToSet) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr Plane<T>& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const Plane<T>& operator [](std::size_t index) const noexcept;

		constexpr Frustum& operator =(const Frustum& other) noexcept = default;
		constexpr Frustum& operator =(Frustum&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Frustum& other) const noexcept = default;

	private:
		std::array<Plane<T>, 6> planes;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Frustum<T>& left, const Frustum<T>& right, T tolerance = T{0.00001}) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	Plane<T> VpToPlane(const Core::Matrix4x4<T>& vp, std::size_t planeIndex) noexcept;

	template<std::floating_point T>
	constexpr Core::Vector3<T> Corner(const Plane<T>& plane0, const Plane<T>& plane1, const Plane<T>& plane2) noexcept;

	template<std::floating_point T>
	constexpr Frustum<T>::Frustum(const Plane<T>& left, const Plane<T>& right, const Plane<T>& bottom, const Plane<T>& top, const Plane<T>& near, const Plane<T>& far) noexcept :
		planes{ left, right, bottom, top, near, far }
	{
	}

	template<std::floating_point T>
	Frustum<T>::Frustum(const Core::Matrix4x4<T>& vp) noexcept
	{
		for (std::size_t i = 0; i < PlaneCount; ++i)
		{
			planes[i] = VpToPlane(vp, i);
		}
	}

	template<std::floating_point T>
	constexpr Frustum<T>::Frustum(const std::span<const Plane<T>, 6> planes) noexcept
	{
		Set(planes);
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Left() noexcept
	{
		return planes[0];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Left() const noexcept
	{
		return planes[0];
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Right() noexcept
	{
		return planes[1];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Right() const noexcept
	{
		return planes[1];
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Bottom() noexcept
	{
		return planes[2];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Bottom() const noexcept
	{
		return planes[2];
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Top() noexcept
	{
		return planes[3];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Top() const noexcept
	{
		return planes[3];
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Near() noexcept
	{
		return planes[4];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Near() const noexcept
	{
		return planes[4];
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::Far() noexcept
	{
		return planes[5];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::Far() const noexcept
	{
		return planes[5];
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::LeftTopNear() const noexcept
	{
		return Corner(Left(), Top(), Near());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::RightTopNear() const noexcept
	{
		return Corner(Right(), Top(), Near());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::RightBottomNear() const noexcept
	{
		return Corner(Right(), Bottom(), Near());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::LeftBottomNear() const noexcept
	{
		return Corner(Left(), Bottom(), Near());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::LeftTopFar() const noexcept
	{
		return Corner(Left(), Top(), Far());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::RightTopFar() const noexcept
	{
		return Corner(Right(), Top(), Far());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::RightBottomFar() const noexcept
	{
		return Corner(Right(), Bottom(), Far());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::LeftBottomFar() const noexcept
	{
		return Corner(Left(), Bottom(), Far());
	}

	template<std::floating_point T>
	constexpr std::array<Core::Vector3<T>, 8> Frustum<T>::Corners() const noexcept
	{
		return std::array<Core::Vector3<T>, 8>
		{
			LeftTopNear(),
			RightTopNear(),
			RightBottomNear(),
			LeftBottomNear(),
			LeftTopFar(),
			RightTopFar(),
			RightBottomFar(),
			LeftBottomFar(),
		};
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::Center() const noexcept
	{
		return (LeftBottomNear() + RightTopFar() + RightTopNear + LeftBottomFar()) * T{0.25};
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::CenterNear() const noexcept
	{
		return (LeftBottomNear() + RightTopNear()) * T{0.5};
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Frustum<T>::CenterFar() const noexcept
	{
		return (LeftBottomFar() + RightTopFar()) * T{0.5};
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::WidthNear() const noexcept
	{
		return (RightTopNear() - LeftTopNear()).Magnitude();
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::WidthFar() const noexcept
	{
		return (RightTopFar() - LeftTopFar()).Magnitude();
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::HeightNear() const noexcept
	{
		return (LeftTopNear() - LeftBottomNear()) * T{0.5};
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::HeightFar() const noexcept
	{
		return (LeftTopFar() - LeftBottomFar()) * T{0.5};
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::Depth() const noexcept
	{
		return -(Near().Distance() + Far().Distance());
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::DepthSlant() const noexcept
	{
		return (LeftTopFar() - LeftTopNear()).Magnitude();
	}

	template<std::floating_point T>
	constexpr T Frustum<T>::Area() const noexcept
	{
		const T nearPerimeter = (WidthNear() + HeightNear()) * T{2};
		const T farPerimeter = (WidthFar() + HeightFar()) * T{2};

		return (nearPerimeter + farPerimeter) * DepthSlant() * T{0.5};
	}

	template<std::floating_point T>
	T Frustum<T>::Volume() const noexcept
	{
		const T nearArea = WidthNear() * HeightNear();
		const T farArea = WidthFar() * HeightFar();

		return (nearArea + farArea + std::sqrt(nearArea * farArea)) * Depth() * (T{1} / T{3});
	}

	template<std::floating_point T>
	bool Frustum<T>::IsFinite() const noexcept
	{
		for (const Plane<T>& plane : planes)
		{
			if (!plane.IsFinite())
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	constexpr bool Frustum<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		for (const Plane<T>& plane : planes)
		{
			if (!plane.Side(point))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	constexpr void Frustum<T>::Set(const std::span<const Plane<T>, 6> planesToSet) noexcept
	{
		std::ranges::copy(planesToSet, planes.begin());
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Frustum<T>& left, const Frustum<T>& right, const T tolerance) noexcept
	{
		for (std::size_t i = 0; i < Frustum<T>::PlaneCount; ++i)
		{
			if (!AreAlmostEqual(left[i], right[i], tolerance))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	Plane<T> VpToPlane(const Core::Matrix4x4<T>& vp, const std::size_t planeIndex) noexcept
	{
		const T sign = Core::Sign<T>(planeIndex % 2 == 0);
		const std::size_t halfIndex = planeIndex / 2;
		const Core::Vector4<T> normalDistance = vp.Row(3) + vp.Row(halfIndex) * sign;

		const auto normal = Core::Vector3<T>(normalDistance.X(), normalDistance.Y(), normalDistance.Z());
		const T invMagnitude = T{1} / normal.Magnitude();

		return Plane<T>(normal * invMagnitude, normalDistance.W() * invMagnitude);
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Corner(const Plane<T>& plane0, const Plane<T>& plane1, const Plane<T>& plane2) noexcept
	{
		const Core::Vector3<T> cross01 = Core::Cross(plane0.Normal(), plane1.Normal());
		const Core::Vector3<T> cross12 = Core::Cross(plane1.Normal(), plane2.Normal());
		const Core::Vector3<T> cross20 = Core::Cross(plane2.Normal(), plane0.Normal());

		const Core::Vector3<T> r = -plane0.Distance() * cross12 - plane1.Distance() * cross20 - plane2.Distance() * cross01;
		const T denominator = Core::Dot(plane0.Normal(), cross12);

		return r / denominator;
	}

	template<std::floating_point T>
	constexpr Plane<T>& Frustum<T>::operator [](const std::size_t index) noexcept
	{
		return planes[index];
	}

	template<std::floating_point T>
	constexpr const Plane<T>& Frustum<T>::operator [](const std::size_t index) const noexcept
	{
		return planes[index];
	}
}
