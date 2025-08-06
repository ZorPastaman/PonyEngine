/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Transform2D;

import std;

import :Matrix;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Transform 2D.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Transform2D final
	{
	public:
		using ValueType = T; ///< Component type.
		using PositionType = Vector2<T>; ///< Position type.
		using RotationType = T; ///< Rotation type.
		using ScaleType = Vector2<T>; ///< Scale type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform2D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation in radians.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform2D(const Vector2<T>& position, T rotation, const Vector2<T>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform2D(const Transform2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform2D(Transform2D&& other) noexcept = default;

		~Transform2D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Vector2<T>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const Vector2<T>& position) noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		T Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @note The function normalizes the rotation to the range (-2π, 2π).
		/// @param rotation Rotation in radians.
		void Rotation(T rotation) noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Vector2<T>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scale Scale.
		void Scale(const Vector2<T>& scale) noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Matrix3x3<T> TrsMatrix() const noexcept;
		/// @brief Computes a compact translation-rotation-scaling matrix.
		/// @return Compact translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Matrix2x3<T> TrsMatrixCompact() const noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Vector2<T> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Vector2<T> Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Vector2<T> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Vector2<T> Down() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Vector2<T>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @note The function normalizes the rotation to the range (-2π, 2π).
		/// @param rotationToAdd Rotation in radians.
		void Rotate(T rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const Vector2<T>& direction) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const Vector2<T>& point) noexcept;

		/// @brief Creates a string representing the current state of the transform.
		/// @return String representing the current state of the transform.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		Transform2D& operator =(const Transform2D& other) noexcept = default;
		Transform2D& operator =(Transform2D&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const Transform2D& other) const noexcept = default;

	private:
		Vector2<T> position; ///< Position.
		T rotation; ///< Rotation.
		Vector2<T> scale; ///< Scale.
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform2D<T>& left, const Transform2D<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform2D<T>& transform);
}

/// @brief Transform2D formatter.
/// @tparam T Component type.
export template<std::floating_point T>
struct std::formatter<PonyEngine::Math::Transform2D<T>, char>
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

	static auto format(const PonyEngine::Math::Transform2D<T>& transform, std::format_context& context)
	{
		return std::ranges::copy(transform.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T>
	Transform2D<T>::Transform2D() noexcept :
		position(Vector2<T>::Zero()),
		rotation{0.f},
		scale(Vector2<T>::One())
	{
	}

	template<std::floating_point T>
	Transform2D<T>::Transform2D(const Vector2<T>& position, const T rotation, const Vector2<T>& scale) noexcept :
		position(position),
		scale(scale)
	{
		Rotation(rotation);
	}

	template<std::floating_point T>
	const Vector2<T>& Transform2D<T>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T>
	void Transform2D<T>::Position(const Vector2<T>& position) noexcept
	{
		this->position = position;
	}

	template<std::floating_point T>
	T Transform2D<T>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	void Transform2D<T>::Rotation(const T rotation) noexcept
	{
		this->rotation = std::fmod(rotation, std::numbers::pi_v<T> * T{2});
	}

	template<std::floating_point T>
	const Vector2<T>& Transform2D<T>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	void Transform2D<T>::Scale(const Vector2<T>& scale) noexcept
	{
		this->scale = scale;
	}

	template<std::floating_point T>
	Matrix3x3<T> Transform2D<T>::TrsMatrix() const noexcept
	{
		return Math::TrsMatrix(position, rotation, scale);
	}

	template<std::floating_point T>
	Matrix2x3<T> Transform2D<T>::TrsMatrixCompact() const noexcept
	{
		return Math::TrsMatrixCompact(position, rotation, scale);
	}

	template<std::floating_point T>
	bool Transform2D<T>::IsFinite() const noexcept
	{
		return position.IsFinite() && std::isfinite(rotation) && scale.IsFinite();
	}

	template<std::floating_point T>
	Vector2<T> Transform2D<T>::Right() const noexcept
	{
		return Math::Rotate(Vector2<T>::Right(), rotation);
	}

	template<std::floating_point T>
	Vector2<T> Transform2D<T>::Left() const noexcept
	{
		return Math::Rotate(Vector2<T>::Left(), rotation);
	}

	template<std::floating_point T>
	Vector2<T> Transform2D<T>::Up() const noexcept
	{
		return Math::Rotate(Vector2<T>::Up(), rotation);
	}

	template<std::floating_point T>
	Vector2<T> Transform2D<T>::Down() const noexcept
	{
		return Math::Rotate(Vector2<T>::Down(), rotation);
	}

	template<std::floating_point T>
	void Transform2D<T>::Translate(const Vector2<T>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T>
	void Transform2D<T>::Rotate(const T rotationToAdd) noexcept
	{
		Rotation(rotation + rotationToAdd);
	}

	template<std::floating_point T>
	void Transform2D<T>::LookIn(const Vector2<T>& direction) noexcept
	{
		Rotation(AngleSigned(Vector2<T>::Right(), direction));
	}

	template<std::floating_point T>
	void Transform2D<T>::LookAt(const Vector2<T>& point) noexcept
	{
		if (const Vector2<T> direction = point - position; !direction.IsAlmostZero()) [[likely]]
		{
			LookIn(direction.Normalized());
		}
	}

	template<std::floating_point T>
	std::string Transform2D<T>::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position, rotation, scale);
	}

	template<std::floating_point T>
	bool AreAlmostEqual(const Transform2D<T>& left, const Transform2D<T>& right, const T tolerance) noexcept
	{
		return AreAlmostEqual(left.Position(), right.Position(), tolerance) && AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform2D<T>& transform)
	{
		return stream << transform.ToString();
	}
}
