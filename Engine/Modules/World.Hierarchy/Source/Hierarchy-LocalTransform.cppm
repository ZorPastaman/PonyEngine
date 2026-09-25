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

import :Types;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Local transform.
	/// @tparam Size Dimension.
	template<std::size_t Size> requires (Size == 2 || Size == 3)
	class LocalTransform final
	{
	public:
		using PositionType = Math::Vector<PositionComponentType, Size>; ///< Position type.
		using RotationType = std::conditional_t<Size == 3, Math::Quaternion<RotationScaleComponentType>, RotationScaleComponentType>; ///< Rotation type.
		using ScaleType = Math::Vector<RotationScaleComponentType, Size>; ///< Scale type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		LocalTransform() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		LocalTransform(const PositionType& position, const RotationType& rotation, const ScaleType& scale) noexcept;
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
		const PositionType& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const PositionType& position) noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation.
		[[nodiscard("Pure function")]]
		const RotationType& Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @note The function normalizes the rotation.
		/// @param rotation Rotation.
		void Rotation(const RotationType& rotation) noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const ScaleType& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scale Scale.
		void Scale(const ScaleType& scale) noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Right.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Left.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Up.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Down.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Forward.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Forward() const noexcept requires (Size == 3);
		/// @brief Gets the transform back vector.
		/// @tparam ApplyScale Should the scale be applied?
		/// @return Back.
		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType Back() const noexcept requires (Size == 3);

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const PositionType& translation) noexcept;
		/// @brief Rotates the transform.
		/// @note The function normalizes the rotation.
		/// @param rotationToAdd Rotation to add.
		void Rotate(const RotationType& rotationToAdd) noexcept;
		/// @brief Multiplies the current scale by the @p stretch components-wise.
		/// @param stretch Stretch.
		void Stretch(const ScaleType& stretch) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const ScaleType& direction) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const ScaleType& direction, const ScaleType& up) noexcept requires (Size == 3);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const PositionType& point) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const PositionType& point, const ScaleType& up) noexcept requires (Size == 3);

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

		template<bool ApplyScale = false> [[nodiscard("Pure function")]]
		ScaleType TransformVector(const ScaleType& vector) const noexcept;

		PositionType position; ///< Position.
		RotationType rotation; ///< Rotation.
		ScaleType scale; ///< Scale.
	};

	/// @brief Local transform 2D.
	using LocalTransform2D = LocalTransform<2>;
	/// @brief Local transform 3D.
	using LocalTransform3D = LocalTransform<3>;

	/// @brief Applies the transform to the point vector.
	/// @tparam T Vector component type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformPoint(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transform rotation and scale to the direction vector.
	/// @tparam T Vector component type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformDirection(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transform rotation to the direction vector.
	/// @tparam T Vector component type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformOrientation(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept;

	/// @brief Checks if positions, rotations and scales of the two transforms are almost equal.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @param tolerance Tolerance.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const LocalTransform<Size>& lhs, const LocalTransform<Size>& rhs, 
		const Math::Tolerance<PositionComponentType>& tolerance = Math::Tolerance<PositionComponentType>()) noexcept requires (Size == 2 || Size == 3);
}

namespace PonyEngine::World::Hierarchy
{
	template<std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<Size>::LocalTransform() noexcept :
		position(PositionType::Zero()),
		rotation(IdentityRotation()),
		scale(ScaleType::One())
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	LocalTransform<Size>::LocalTransform(const PositionType& position, const RotationType& rotation, const ScaleType& scale) noexcept :
		position(position),
		scale(scale)
	{
		Rotation(rotation);
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<Size>& LocalTransform<Size>::Identity() noexcept
	{
		static const auto identityTransform = LocalTransform();
		return identityTransform;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<Size>::PositionType& LocalTransform<Size>::Position() const noexcept
	{
		return position;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Position(const PositionType& position) noexcept
	{
		this->position = position;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<Size>::RotationType& LocalTransform<Size>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Rotation(const RotationType& rotation) noexcept
	{
		if constexpr (Size == 3)
		{
			this->rotation = rotation.Normalized(Math::Quaternion<RotationScaleComponentType>::Identity());
		}
		else
		{
			this->rotation = std::fmod(rotation, std::numbers::pi_v<RotationScaleComponentType> * RotationScaleComponentType{2});
		}
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<Size>::ScaleType& LocalTransform<Size>::Scale() const noexcept
	{
		return scale;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Scale(const ScaleType& scale) noexcept
	{
		this->scale = scale;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	bool LocalTransform<Size>::IsFinite() const noexcept
	{
		return Math::IsFinite(position) && Math::IsFinite(rotation) && Math::IsFinite(scale);
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Right() const noexcept
	{
		return TransformVector<ApplyScale>(ScaleType::Right());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Left() const noexcept
	{
		return TransformVector<ApplyScale>(ScaleType::Left());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Up() const noexcept
	{
		return TransformVector<ApplyScale>(ScaleType::Up());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Down() const noexcept
	{
		return TransformVector<ApplyScale>(ScaleType::Down());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Forward() const noexcept requires (Size == 3)
	{
		return TransformVector<ApplyScale>(ScaleType::Forward());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::Back() const noexcept requires (Size == 3)
	{
		return TransformVector<ApplyScale>(ScaleType::Back());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Translate(const PositionType& translation) noexcept
	{
		position += translation;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Rotate(const RotationType& rotationToAdd) noexcept
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

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::Stretch(const ScaleType& stretch) noexcept
	{
		scale.Multiply(stretch);
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::LookIn(const ScaleType& direction) noexcept requires (Size == 2)
	{
		Rotation(Math::AngleSigned(ScaleType::Right(), direction));
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::LookIn(const ScaleType& direction, const ScaleType& up) noexcept requires (Size == 3)
	{
		Rotation(Math::LookInRotationQuaternion(direction, up));
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::LookAt(const PositionType& point) noexcept requires (Size == 2)
	{
		if (const ScaleType direction = static_cast<ScaleType>(point - position); !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized());
		}
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void LocalTransform<Size>::LookAt(const PositionType& point, const ScaleType& up) noexcept requires (Size == 3)
	{
		if (const ScaleType direction = static_cast<ScaleType>(point - position); !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized(), up);
		}
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const LocalTransform<Size>::RotationType& LocalTransform<Size>::IdentityRotation() noexcept
	{
		if constexpr (Size == 3)
		{
			return Math::Quaternion<RotationScaleComponentType>::Identity();
		}
		else
		{
			static constexpr RotationScaleComponentType IdentityRotation = RotationScaleComponentType{0};
			return IdentityRotation;
		}
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	template<bool ApplyScale>
	LocalTransform<Size>::ScaleType LocalTransform<Size>::TransformVector(const ScaleType& vector) const noexcept
	{
		if constexpr (ApplyScale)
		{
			return TransformDirection(*this, vector);
		}
		else
		{
			return TransformOrientation(*this, vector);
		}
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformPoint(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		using PositionComponent = std::conditional_t<(sizeof(T) > sizeof(PositionComponentType)), T, PositionComponentType>;
		using PositionType = Math::Vector<PositionComponent, Size>;
		using RotationScaleComponent = std::conditional_t<(sizeof(T) > sizeof(RotationScaleComponentType)), T, RotationScaleComponentType>;
		using RotationType = std::conditional_t<Size == 3, Math::Quaternion<RotationScaleComponent>, RotationScaleComponent>;
		using ScaleType = Math::Vector<RotationScaleComponent, Size>;

		ScaleType result = static_cast<ScaleType>(vector);
		result.Multiply(static_cast<ScaleType>(transform.Scale()));
		result = Math::Rotate(result, static_cast<RotationType>(transform.Rotation()));

		return static_cast<Math::Vector<T, Size>>(static_cast<PositionType>(result) + static_cast<PositionType>(transform.Position()));
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformDirection(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		using RotationScaleComponent = std::conditional_t<(sizeof(T) > sizeof(RotationScaleComponentType)), T, RotationScaleComponentType>;
		using RotationType = std::conditional_t<Size == 3, Math::Quaternion<RotationScaleComponent>, RotationScaleComponent>;
		using ScaleType = Math::Vector<RotationScaleComponent, Size>;

		ScaleType result = static_cast<ScaleType>(vector);
		result.Multiply(static_cast<ScaleType>(transform.Scale()));
		result = Math::Rotate(result, static_cast<RotationType>(transform.Rotation()));

		return static_cast<Math::Vector<T, Size>>(result);
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformOrientation(const LocalTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		using RotationScaleComponent = std::conditional_t<(sizeof(T) > sizeof(RotationScaleComponentType)), T, RotationScaleComponentType>;
		using RotationType = std::conditional_t<Size == 3, Math::Quaternion<RotationScaleComponent>, RotationScaleComponent>;
		using ScaleType = Math::Vector<RotationScaleComponent, Size>;

		ScaleType result = static_cast<ScaleType>(vector);
		result = Math::Rotate(result, static_cast<RotationType>(transform.Rotation()));

		return static_cast<Math::Vector<T, Size>>(result);
	}

	template<std::size_t Size>
	bool AreAlmostEqual(const LocalTransform<Size>& lhs, const LocalTransform<Size>& rhs,
		const Math::Tolerance<PositionComponentType>& tolerance) noexcept requires (Size == 2 || Size == 3)
	{
		const auto smallTolerance = static_cast<Math::Tolerance<RotationScaleComponentType>>(tolerance);
		return AreAlmostEqual(lhs.Position(), rhs.Position(), tolerance) && AreAlmostEqual(lhs.Rotation(), rhs.Rotation(), smallTolerance) &&
			AreAlmostEqual(lhs.Scale(), rhs.Scale(), smallTolerance);
	}
}
