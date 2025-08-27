/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transform;

import std;

import :Common;
import :Matrix;
import :Quaternion;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Transform 3D.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	class Transform final
	{
	public:
		using ValueType = T; ///< Component type.
		using PositionType = Vector<T, Size>; ///< Position type.
		using RotationType = std::conditional_t<Size == 3, Quaternion<T>, T>; ///< Rotation type.
		using ScaleType = Vector<T, Size>; ///< Scale type.
		using TrsMatrixType = std::conditional_t<Size == 3, Matrix4x4<T>, Matrix3x3<T>>; ///< TRS matrix type.
		using TrsMatrixCompactType = std::conditional_t<Size == 3, Matrix3x4<T>, Matrix2x3<T>>; ///< Compact TRS matrix type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform(const Vector<T, Size>& position, const RotationType& rotation, const Vector<T, Size>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform(const Transform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform(Transform&& other) noexcept = default;

		~Transform() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Vector<T, Size>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const Vector<T, Size>& position) noexcept;
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
		const Vector<T, Size>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scale Scale.
		void Scale(const Vector<T, Size>& scale) noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		TrsMatrixType TrsMatrix() const noexcept;
		/// @brief Computes a compact translation-rotation-scaling matrix.
		/// @return Compact translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		TrsMatrixCompactType TrsMatrixCompact() const noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @return Forward.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Forward() const noexcept requires (Size == 3);
		/// @brief Gets the transform back vector.
		/// @return Back.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Back() const noexcept requires (Size == 3);

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Vector<T, Size>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @note The function normalizes the rotation.
		/// @param rotationToAdd Rotation in radians.
		void Rotate(const RotationType& rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const Vector<T, Size>& direction) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const Vector<T, Size>& direction, const Vector<T, Size>& up) noexcept requires (Size == 3);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const Vector<T, Size>& point) noexcept requires (Size == 2);
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const Vector<T, Size>& point, const Vector<T, Size>& up) noexcept requires (Size == 3);

		/// @brief Creates a string representing the current state of the transform.
		/// @return String representing the current state of the transform.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the transform to another transform type.
		/// @tparam U Target component type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Transform<U, Size>() const noexcept;

		Transform& operator =(const Transform& other) noexcept = default;
		Transform& operator =(Transform&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const Transform& other) const noexcept = default;

	private:
		Vector<T, Size> position; ///< Position.
		RotationType rotation; ///< Rotation.
		Vector<T, Size> scale; ///< Scale.
	};

	/// @brief Transform 2D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Transform2D = Transform<T, 2>;
	/// @brief Transform 3D.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Transform3D = Transform<T, 3>;

	/// @brief Checks if positions, rotations and scales of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform<T, Size>& left, const Transform<T, Size>& right, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept requires (Size == 2 || Size == 3);

	/// @brief Puts the transform ToString() to the stream.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Transform<T, Size>& transform) requires (Size == 2 || Size == 3);
}

/// @brief Transform3D formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<std::floating_point T, std::size_t Size>
struct std::formatter<PonyEngine::Math::Transform<T, Size>, char>
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

	static auto format(const PonyEngine::Math::Transform<T, Size>& transform, std::format_context& context)
	{
		return std::ranges::copy(transform.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Transform<T, Size>::Transform() noexcept :
		position(Vector<T, Size>::Zero()),
		scale(Vector<T, Size>::One())
	{
		if constexpr (Size == 3)
		{
			rotation = Quaternion<T>::Identity();
		}
		else
		{
			rotation = T{0};
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Transform<T, Size>::Transform(const Vector<T, Size>& position, const RotationType& rotation, const Vector<T, Size>& scale) noexcept :
		position(position),
		scale(scale)
	{
		Rotation(rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const Vector<T, Size>& Transform<T, Size>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::Position(const Vector<T, Size>& position) noexcept
	{
		this->position = position;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const typename Transform<T, Size>::RotationType& Transform<T, Size>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::Rotation(const RotationType& rotation) noexcept
	{
		if constexpr (Size == 3)
		{
			this->rotation = rotation.Normalized(Quaternion<T>::Identity());
		}
		else
		{
			this->rotation = std::fmod(rotation, std::numbers::pi_v<T> * T{2});
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	const Vector<T, Size>& Transform<T, Size>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::Scale(const Vector<T, Size>& scale) noexcept
	{
		this->scale = scale;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	typename Transform<T, Size>::TrsMatrixType Transform<T, Size>::TrsMatrix() const noexcept
	{
		return Math::TrsMatrix(position, rotation, scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
		typename Transform<T, Size>::TrsMatrixCompactType Transform<T, Size>::TrsMatrixCompact() const noexcept
	{
		return Math::TrsMatrixCompact(position, rotation, scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	bool Transform<T, Size>::IsFinite() const noexcept
	{
		return Math::IsFinite(position) && Math::IsFinite(rotation) && Math::IsFinite(scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Right() const noexcept
	{
		return Math::Rotate(Vector<T, Size>::Right(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Left() const noexcept
	{
		return Math::Rotate(Vector<T, Size>::Left(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Up() const noexcept
	{
		return Math::Rotate(Vector<T, Size>::Up(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Down() const noexcept
	{
		return Math::Rotate(Vector<T, Size>::Down(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Forward() const noexcept requires (Size == 3)
	{
		return Math::Rotate(Vector<T, Size>::Forward(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	Vector<T, Size> Transform<T, Size>::Back() const noexcept requires (Size == 3)
	{
		return Math::Rotate(Vector<T, Size>::Back(), rotation);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::Translate(const Vector<T, Size>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::Rotate(const RotationType& rotationToAdd) noexcept
	{
		Rotation(SumRotations(rotation, rotationToAdd));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::LookIn(const Vector<T, Size>& direction) noexcept requires (Size == 2)
	{
		Rotation(AngleSigned(Vector<T, Size>::Right(), direction));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::LookIn(const Vector<T, Size>& direction, const Vector<T, Size>& up) noexcept requires (Size == 3)
	{
		Rotation(LookInRotationQuaternion(direction, up));
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::LookAt(const Vector<T, Size>& point) noexcept requires (Size == 2)
	{
		if (const Vector<T, Size> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized());
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	void Transform<T, Size>::LookAt(const Vector<T, Size>& point, const Vector<T, Size>& up) noexcept requires (Size == 3)
	{
		if (const Vector<T, Size> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized(), up);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	std::string Transform<T, Size>::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position, rotation, scale);
	}

	template<std::floating_point T, std::size_t Size> requires (Size == 2 || Size == 3)
	template<std::floating_point U>
	constexpr Transform<T, Size>::operator Transform<U, Size>() const noexcept
	{
		return Transform<U, Size>(static_cast<Vector<U, Size>>(position), static_cast<typename Transform<U, Size>::RotationType>(rotation), static_cast<Vector<U, Size>>(scale));
	}

	template<std::floating_point T, std::size_t Size>
	bool AreAlmostEqual(const Transform<T, Size>& left, const Transform<T, Size>& right, const Tolerance<T>& tolerance) noexcept requires (Size == 2 || Size == 3)
	{
		return AreAlmostEqual(left.Position(), right.Position(), tolerance) && AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && 
			AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Transform<T, Size>& transform) requires (Size == 2 || Size == 3)
	{
		return stream << transform.ToString();
	}
}
