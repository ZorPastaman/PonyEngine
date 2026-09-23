/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:WorldTransform;

import std;

import PonyEngine.Math;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief World transform.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	class WorldTransform final
	{
	public:
		using ValueType = T; ///< Component type.
		using PositionType = Math::Vector<T, Size>; ///< Position type.
		using RotationType = std::conditional_t<Size == 3, Math::Quaternion<T>, T>; ///< Rotation type.
		using ScaleType = Math::Vector<T, Size>; ///< Scale type.
		using TRSMatrixType = std::conditional_t<Size == 3, Math::Matrix4x4<T>, Math::Matrix3x3<T>>; ///< TRS matrix type.
		using TRSMatrixCompactType = std::conditional_t<Size == 3, Math::Matrix3x4<T>, Math::Matrix2x3<T>>; ///< Compact TRS matrix type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		WorldTransform() noexcept;
		/// @brief Creates a transform.
		/// @param matrix TRS matrix.
		[[nodiscard("Pure constructor")]]
		explicit WorldTransform(const TRSMatrixType& matrix) noexcept;
		/// @brief Creates a transform.
		/// @param matrix TRS matrix.
		[[nodiscard("Pure constructor")]]
		explicit WorldTransform(const TRSMatrixCompactType& matrix) noexcept;
		[[nodiscard("Pure constructor")]]
		WorldTransform(const WorldTransform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		WorldTransform(WorldTransform&& other) noexcept = default;

		~WorldTransform() noexcept = default;

		/// @brief Gets an identity transform.
		/// @return Identity transform.
		[[nodiscard("Pure function")]]
		static const WorldTransform& Identity() noexcept;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Position() const noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		RotationType Rotation() const noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Scale() const noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		const TRSMatrixType& TRSMatrix() const noexcept;
		/// @brief Computes a compact translation-rotation-scaling matrix.
		/// @return Compact translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		TRSMatrixCompactType TRSMatrixCompact() const noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @return Right.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @return Forward.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Forward() const noexcept requires (Size == 3);
		/// @brief Gets the transform back vector.
		/// @return Back.
		/// @remark It may be non-normalized.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Back() const noexcept requires (Size == 3);

		/// @brief Converts the transform to another transform type.
		/// @tparam U Target component type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit operator WorldTransform<U, Size>() const noexcept;

		WorldTransform& operator =(const WorldTransform& other) noexcept = default;
		WorldTransform& operator =(WorldTransform&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const WorldTransform& other) const noexcept = default;

	private:
		TRSMatrixType matrix; ///< TRS matrix.
	};

	/// @brief World transform 2D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using WorldTransform2D = WorldTransform<T, 2>;
	/// @brief World transform 3D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using WorldTransform3D = WorldTransform<T, 3>;

	/// @brief Applies the transform to the point vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformPoint(const WorldTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transform to the direction vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformDirection(const WorldTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept;

	/// @brief Checks if positions, rotations and scales of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @param tolerance Tolerance.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const WorldTransform<T, Size>& lhs, const WorldTransform<T, Size>& rhs,
		const Math::Tolerance<T>& tolerance = Math::Tolerance<T>()) noexcept requires (Size == 2 || Size == 3);
}

namespace PonyEngine::World::Hierarchy
{
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<T, Size>::WorldTransform() noexcept :
		matrix(TRSMatrixType::Identity())
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<T, Size>::WorldTransform(const TRSMatrixType& matrix) noexcept :
		matrix(matrix)
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<T, Size>::WorldTransform(const TRSMatrixCompactType& matrix) noexcept :
		WorldTransform(Math::TRSMatrix(matrix))
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const WorldTransform<T, Size>& WorldTransform<T, Size>::Identity() noexcept
	{
		static auto identityTransform = WorldTransform();
		return identityTransform;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Position() const noexcept
	{
		return Math::ExtractTranslationFromTRS(matrix);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<T, Size>::RotationType WorldTransform<T, Size>::Rotation() const noexcept
	{
		if constexpr (Size == 3)
		{
			return Math::ExtractRotationQuaternionFromTRS(matrix);
		}
		else
		{
			return Math::ExtractAngleFromTRS(matrix);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Scale() const noexcept
	{
		return Math::ExtractScalingFromTRS(matrix);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const WorldTransform<T, Size>::TRSMatrixType& WorldTransform<T, Size>::TRSMatrix() const noexcept
	{
		return matrix;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<T, Size>::TRSMatrixCompactType WorldTransform<T, Size>::TRSMatrixCompact() const noexcept
	{
		return Math::ExtractTRSMatrixCompactFromTRS(matrix);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	bool WorldTransform<T, Size>::IsFinite() const noexcept
	{
		return matrix.IsFinite();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Right() const noexcept
	{
		return matrix * Math::Vector<T, Size>::Right();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Left() const noexcept
	{
		return matrix * Math::Vector<T, Size>::Left();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Up() const noexcept
	{
		return matrix * Math::Vector<T, Size>::Up();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Down() const noexcept
	{
		return matrix * Math::Vector<T, Size>::Down();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Forward() const noexcept requires (Size == 3)
	{
		return matrix * Math::Vector<T, Size>::Forward();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> WorldTransform<T, Size>::Back() const noexcept requires (Size == 3)
	{
		return matrix * Math::Vector<T, Size>::Back();
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	template<std::floating_point U>
	WorldTransform<T, Size>::operator WorldTransform<U, Size>() const noexcept
	{
		return WorldTransform<U, Size>(static_cast<WorldTransform<U, Size>::TRSMatrixType>(matrix));
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformPoint(const WorldTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		return Math::TransformPoint(transform.TRSMatrix(), vector);
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformDirection(const WorldTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		return Math::TransformDirection(transform.TRSMatrix(), vector);
	}

	template<std::floating_point T, std::size_t Size>
	bool AreAlmostEqual(const WorldTransform<T, Size>& lhs, const WorldTransform<T, Size>& rhs,
		const Math::Tolerance<T>& tolerance) noexcept requires (Size == 2 || Size == 3)
	{
		return Math::AreAlmostEqual(lhs.TRSMatrix(), rhs.TRSMatrix(), tolerance);
	}
}
