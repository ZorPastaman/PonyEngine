/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transform3D;

import std;

import :Matrix;
import :Quaternion;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Transform 3D.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Transform3D final
	{
	public:
		using ValueType = T; ///< Component type.
		using PositionType = Vector3<T>; ///< Position type.
		using RotationType = Quaternion<T>; ///< Rotation type.
		using ScaleType = Vector3<T>; ///< Scale type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform3D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform3D(const Vector3<T>& position, const Quaternion<T>& rotation, const Vector3<T>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Transform3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform3D(Transform3D&& other) noexcept = default;

		~Transform3D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Vector3<T>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const Vector3<T>& position) noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		const Quaternion<T>& Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @note The function normalizes the rotation.
		/// @param rotation Rotation in radians.
		void Rotation(const Quaternion<T>& rotation) noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Vector3<T>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scale Scale.
		void Scale(const Vector3<T>& scale) noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Matrix4x4<T> TrsMatrix() const noexcept;
		/// @brief Computes a compact translation-rotation-scaling matrix.
		/// @return Compact translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Matrix3x4<T> TrsMatrixCompact() const noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Vector3<T> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Vector3<T> Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Vector3<T> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Vector3<T> Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @return Forward.
		[[nodiscard("Pure function")]]
		Vector3<T> Forward() const noexcept;
		/// @brief Gets the transform back vector.
		/// @return Back.
		[[nodiscard("Pure function")]]
		Vector3<T> Back() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Vector3<T>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @note The function normalizes the rotation.
		/// @param rotationToAdd Rotation in radians.
		void Rotate(const Quaternion<T>& rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const Vector3<T>& direction, const Vector3<T>& up) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const Vector3<T>& point, const Vector3<T>& up) noexcept;

		/// @brief Creates a string representing the current state of the transform.
		/// @return String representing the current state of the transform.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		Transform3D& operator =(const Transform3D& other) noexcept = default;
		Transform3D& operator =(Transform3D&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const Transform3D& other) const noexcept = default;

	private:
		Vector3<T> position; ///< Position.
		Quaternion<T> rotation; ///< Rotation.
		Vector3<T> scale; ///< Scale.
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform3D<T>& left, const Transform3D<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform3D<T>& transform);
}

/// @brief Transform3D formatter.
/// @tparam T Component type.
export template<std::floating_point T>
struct std::formatter<PonyEngine::Math::Transform3D<T>, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const PonyEngine::Math::Transform3D<T>& transform, std::format_context& context)
	{
		return std::ranges::copy(transform.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T>
	Transform3D<T>::Transform3D() noexcept :
		position(Vector3<T>::Zero()),
		rotation(Quaternion<T>::Identity()),
		scale(Vector3<T>::One())
	{
	}

	template<std::floating_point T>
	Transform3D<T>::Transform3D(const Vector3<T>& position, const Quaternion<T>& rotation, const Vector3<T>& scale) noexcept :
		position(position),
		scale(scale)
	{
		Rotation(rotation);
	}

	template<std::floating_point T>
	const Vector3<T>& Transform3D<T>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T>
	void Transform3D<T>::Position(const Vector3<T>& position) noexcept
	{
		this->position = position;
	}

	template<std::floating_point T>
	const Quaternion<T>& Transform3D<T>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	void Transform3D<T>::Rotation(const Quaternion<T>& rotation) noexcept
	{
		this->rotation = rotation.Normalized(Quaternion<T>::Identity());
	}

	template<std::floating_point T>
	const Vector3<T>& Transform3D<T>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	void Transform3D<T>::Scale(const Vector3<T>& scale) noexcept
	{
		this->scale = scale;
	}

	template<std::floating_point T>
	Matrix4x4<T> Transform3D<T>::TrsMatrix() const noexcept
	{
		return Math::TrsMatrix(position, rotation, scale);
	}

	template<std::floating_point T>
	Matrix3x4<T> Transform3D<T>::TrsMatrixCompact() const noexcept
	{
		return Math::TrsMatrixCompact(position, rotation, scale);
	}

	template<std::floating_point T>
	bool Transform3D<T>::IsFinite() const noexcept
	{
		return position.IsFinite() && rotation.IsFinite() && scale.IsFinite();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Right() const noexcept
	{
		return rotation * Vector3<T>::Right();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Left() const noexcept
	{
		return rotation * Vector3<T>::Left();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Up() const noexcept
	{
		return rotation * Vector3<T>::Up();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Down() const noexcept
	{
		return rotation * Vector3<T>::Down();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Forward() const noexcept
	{
		return rotation * Vector3<T>::Forward();
	}

	template<std::floating_point T>
	Vector3<T> Transform3D<T>::Back() const noexcept
	{
		return rotation * Vector3<T>::Back();
	}

	template<std::floating_point T>
	void Transform3D<T>::Translate(const Vector3<T>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T>
	void Transform3D<T>::Rotate(const Quaternion<T>& rotationToAdd) noexcept
	{
		Rotation(rotationToAdd * rotation);
	}

	template<std::floating_point T>
	void Transform3D<T>::LookIn(const Vector3<T>& direction, const Vector3<T>& up) noexcept
	{
		Rotation(LookInRotationQuaternion(direction, up));
	}

	template<std::floating_point T>
	void Transform3D<T>::LookAt(const Vector3<T>& point, const Vector3<T>& up) noexcept
	{
		if (const Vector3<T> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized(), up);
		}
	}

	template<std::floating_point T>
	std::string Transform3D<T>::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position, rotation, scale);
	}

	template<std::floating_point T>
	bool AreAlmostEqual(const Transform3D<T>& left, const Transform3D<T>& right, const T tolerance) noexcept
	{
		return AreAlmostEqual(left.Position(), right.Position(), tolerance) && AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform3D<T>& transform)
	{
		return stream << transform.ToString();
	}
}
