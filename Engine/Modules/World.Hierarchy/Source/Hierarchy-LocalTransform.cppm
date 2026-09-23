/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:LocalTransform;

import std;

import PonyEngine.Math;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Local transform.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	class LocalTransform final
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
		LocalTransform() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		LocalTransform(const Math::Vector<T, Size>& position, const RotationType& rotation, const Math::Vector<T, Size>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		LocalTransform(const LocalTransform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LocalTransform(LocalTransform&& other) noexcept = default;

		~LocalTransform() noexcept = default;

		/// @brief Gets an identity transform.
		/// @return Identity transform.
		[[nodiscard("Pure function")]]
		static const LocalTransform& Identity() noexcept;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Math::Vector<T, Size>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const Math::Vector<T, Size>& position) noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		const RotationType& Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @note The function normalizes the rotation.
		/// @param rotation Rotation in radians.
		void Rotation(const RotationType& rotation) noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Math::Vector<T, Size>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scale Scale.
		void Scale(const Math::Vector<T, Size>& scale) noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		TRSMatrixType TRSMatrix() const noexcept;
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
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @return Forward.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Forward() const noexcept requires (Size == 3);
		/// @brief Gets the transform back vector.
		/// @return Back.
		[[nodiscard("Pure function")]]
		Math::Vector<T, Size> Back() const noexcept requires (Size == 3);

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Math::Vector<T, Size>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @note The function normalizes the rotation.
		/// @param rotationToAdd Rotation to add.
		void Rotate(const RotationType& rotationToAdd) noexcept;
		/// @brief Multiplies the current scale by the @p stretch components-wise.
		/// @param stretch Stretch.
		void Stretch(const Math::Vector<T, Size>& stretch) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const Math::Vector<T, Size>& direction) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const Math::Vector<T, Size>& direction, const Math::Vector<T, Size>& up) noexcept requires (Size == 3);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const Math::Vector<T, Size>& point) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const Math::Vector<T, Size>& point, const Math::Vector<T, Size>& up) noexcept requires (Size == 3);

		/// @brief Converts the transform to another transform type.
		/// @tparam U Target component type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit operator LocalTransform<U, Size>() const noexcept;

		LocalTransform& operator =(const LocalTransform& other) noexcept = default;
		LocalTransform& operator =(LocalTransform&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const LocalTransform& other) const noexcept = default;

	private:
		/// @brief Gets an identity rotation.
		/// @return Identity rotation.
		[[nodiscard("Pure function")]]
		static const RotationType& IdentityRotation() noexcept;

		Math::Vector<T, Size> position; ///< Position.
		RotationType rotation; ///< Rotation.
		Math::Vector<T, Size> scale; ///< Scale.
	};

	/// @brief Local transform 2D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using LocalTransform2D = LocalTransform<T, 2>;
	/// @brief Local transform 3D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using LocalTransform3D = LocalTransform<T, 3>;

	/// @brief Applies the transform to the point vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformPoint(const LocalTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transform to the direction vector.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformDirection(const LocalTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept;

	/// @brief Checks if positions, rotations and scales of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @param tolerance Tolerance.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const LocalTransform<T, Size>& lhs, const LocalTransform<T, Size>& rhs, 
		const Math::Tolerance<T>& tolerance = Math::Tolerance<T>()) noexcept requires (Size == 2 || Size == 3);
}

namespace PonyEngine::World::Hierarchy
{
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<T, Size>::LocalTransform() noexcept :
		position(Math::Vector<T, Size>::Zero()),
		rotation(IdentityRotation()),
		scale(Math::Vector<T, Size>::One())
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<T, Size>::LocalTransform(const Math::Vector<T, Size>& position, const RotationType& rotation, const Math::Vector<T, Size>& scale) noexcept :
		position(position),
		scale(scale)
	{
		Rotation(rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<T, Size>& LocalTransform<T, Size>::Identity() noexcept
	{
		static auto identityTransform = LocalTransform();
		return identityTransform;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const Math::Vector<T, Size>& LocalTransform<T, Size>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Position(const Math::Vector<T, Size>& position) noexcept
	{
		this->position = position;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<T, Size>::RotationType& LocalTransform<T, Size>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Rotation(const RotationType& rotation) noexcept
	{
		if constexpr (Size == 3)
		{
			this->rotation = rotation.Normalized(Math::Quaternion<T>::Identity());
		}
		else
		{
			this->rotation = std::fmod(rotation, std::numbers::pi_v<T> * T{2});
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const Math::Vector<T, Size>& LocalTransform<T, Size>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Scale(const Math::Vector<T, Size>& scale) noexcept
	{
		this->scale = scale;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<T, Size>::TRSMatrixType LocalTransform<T, Size>::TRSMatrix() const noexcept
	{
		return Math::TRSMatrix(position, rotation, scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<T, Size>::TRSMatrixCompactType LocalTransform<T, Size>::TRSMatrixCompact() const noexcept
	{
		return Math::TRSMatrixCompact(position, rotation, scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	bool LocalTransform<T, Size>::IsFinite() const noexcept
	{
		return Math::IsFinite(position) && Math::IsFinite(rotation) && Math::IsFinite(scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Right() const noexcept
	{
		return Math::Rotate(Math::Vector<T, Size>::Right(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Left() const noexcept
	{
		return Math::Rotate(Math::Vector<T, Size>::Left(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Up() const noexcept
	{
		return Math::Rotate(Math::Vector<T, Size>::Up(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Down() const noexcept
	{
		return Math::Rotate(Math::Vector<T, Size>::Down(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Forward() const noexcept requires (Size == 3)
	{
		return Math::Rotate(Math::Vector<T, Size>::Forward(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Math::Vector<T, Size> LocalTransform<T, Size>::Back() const noexcept requires (Size == 3)
	{
		return Math::Rotate(Math::Vector<T, Size>::Back(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Translate(const Math::Vector<T, Size>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Rotate(const RotationType& rotationToAdd) noexcept
	{
		if constexpr (Size == 3)
		{
			Rotation(rotation * rotationToAdd);
		}
		else
		{
			Rotation(rotation + rotationToAdd);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::Stretch(const Math::Vector<T, Size>& stretch) noexcept
	{
		scale.Multiply(stretch);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::LookIn(const Math::Vector<T, Size>& direction) noexcept requires (Size == 2)
	{
		Rotation(Math::AngleSigned(Math::Vector<T, Size>::Right(), direction));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::LookIn(const Math::Vector<T, Size>& direction, const Math::Vector<T, Size>& up) noexcept requires (Size == 3)
	{
		Rotation(Math::LookInRotationQuaternion(direction, up));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::LookAt(const Math::Vector<T, Size>& point) noexcept requires (Size == 2)
	{
		if (const Math::Vector<T, Size> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized());
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<T, Size>::LookAt(const Math::Vector<T, Size>& point, const Math::Vector<T, Size>& up) noexcept requires (Size == 3)
	{
		if (const Math::Vector<T, Size> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized(), up);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	template<std::floating_point U>
	LocalTransform<T, Size>::operator LocalTransform<U, Size>() const noexcept
	{
		return LocalTransform<U, Size>(
			static_cast<Math::Vector<U, Size>>(position), 
			static_cast<LocalTransform<U, Size>::RotationType>(rotation), 
			static_cast<Math::Vector<U, Size>>(scale));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<T, Size>::RotationType& LocalTransform<T, Size>::IdentityRotation() noexcept
	{
		if constexpr (Size == 3)
		{
			return Math::Quaternion<T>::Identity();
		}
		else
		{
			static constexpr T IdentityRotation = T{0};
			return IdentityRotation;
		}
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformPoint(const LocalTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		return transform.Position() + Math::Rotate(Multiply(vector, transform.Scale()), transform.Rotation());
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformDirection(const LocalTransform<T, Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		return Math::Rotate(vector, transform.Rotation());
	}

	template<std::floating_point T, std::size_t Size>
	bool AreAlmostEqual(const LocalTransform<T, Size>& lhs, const LocalTransform<T, Size>& rhs, 
		const Math::Tolerance<T>& tolerance) noexcept requires (Size == 2 || Size == 3)
	{
		return AreAlmostEqual(lhs.Position(), rhs.Position(), tolerance) && AreAlmostEqual(lhs.Rotation(), rhs.Rotation(), tolerance) &&
			AreAlmostEqual(lhs.Scale(), rhs.Scale(), tolerance);
	}
}
