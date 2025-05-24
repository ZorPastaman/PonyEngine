/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Space:Transform2D;

import <concepts>;
import <format>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Space
{
	/// @brief 2D transform implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Transform2D final
	{
	public:
		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform2D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation in radians.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform2D(const Core::Vector2<T>& position, T rotation, const Core::Vector2<T>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform2D(const Transform2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform2D(Transform2D&& other) noexcept = default;

		~Transform2D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		Core::Vector2<T>& Position() noexcept;
		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Core::Vector2<T>& Position() const noexcept;

		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		T& Rotation() noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		const T& Rotation() const noexcept;

		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		Core::Vector2<T>& Scale() noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Core::Vector2<T>& Scale() const noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Core::Matrix3x3<T> TrsMatrix() const noexcept;

		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Core::Vector2<T> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Core::Vector2<T> Down() const noexcept;
		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Core::Vector2<T> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Core::Vector2<T> Left() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Core::Vector2<T>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @param rotationToAdd Rotation in radians.
		void Rotate(T rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const Core::Vector2<T>& direction) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const Core::Vector2<T>& point) noexcept;

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
		bool operator ==(const Transform2D& other) const noexcept;

	private:
		Core::Vector2<T> position; ///< Position.
		T rotation; ///< Rotation.
		Core::Vector2<T> scale; ///< Scale.
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform2D<T>& left, const Transform2D<T>& right, T tolerance = 0.00001f) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform2D<T>& transform);
}

namespace PonyMath::Space
{
	template<std::floating_point T>
	Transform2D<T>::Transform2D() noexcept :
		Transform2D(Core::Vector2<T>::Predefined::Zero, 0.f, Core::Vector2<T>::Predefined::One)
	{
	}

	template<std::floating_point T>
	Transform2D<T>::Transform2D(const Core::Vector2<T>& position, const T rotation, const Core::Vector2<T>& scale) noexcept :
		position(position),
		rotation{rotation},
		scale(scale)
	{
	}

	template<std::floating_point T>
	Core::Vector2<T>& Transform2D<T>::Position() noexcept
	{
		return position;
	}

	template<std::floating_point T>
	const Core::Vector2<T>& Transform2D<T>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T>
	T& Transform2D<T>::Rotation() noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	const T& Transform2D<T>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	Core::Vector2<T>& Transform2D<T>::Scale() noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	const Core::Vector2<T>& Transform2D<T>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	Core::Matrix3x3<T> Transform2D<T>::TrsMatrix() const noexcept
	{
		return Core::TrsMatrix(position, rotation, scale);
	}

	template<std::floating_point T>
	Core::Vector2<T> Transform2D<T>::Up() const noexcept
	{
		return Core::Rotate(Core::Vector2<T>::Predefined::Up, rotation);
	}

	template<std::floating_point T>
	Core::Vector2<T> Transform2D<T>::Down() const noexcept
	{
		return Core::Rotate(Core::Vector2<T>::Predefined::Down, rotation);
	}

	template<std::floating_point T>
	Core::Vector2<T> Transform2D<T>::Right() const noexcept
	{
		return Core::Rotate(Core::Vector2<T>::Predefined::Right, rotation);
	}

	template<std::floating_point T>
	Core::Vector2<T> Transform2D<T>::Left() const noexcept
	{
		return Core::Rotate(Core::Vector2<T>::Predefined::Left, rotation);
	}

	template<std::floating_point T>
	void Transform2D<T>::Translate(const Core::Vector2<T>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T>
	void Transform2D<T>::Rotate(const T rotationToAdd) noexcept
	{
		rotation += rotationToAdd;
	}

	template<std::floating_point T>
	void Transform2D<T>::LookIn(const Core::Vector2<T>& direction) noexcept
	{
		rotation = Core::AngleSigned(Core::Vector2<T>::Predefined::Right, direction);
	}

	template<std::floating_point T>
	void Transform2D<T>::LookAt(const Core::Vector2<T>& point) noexcept
	{
		const Core::Vector2<T> direction = point - position;
		if (const T magnitude = direction.Magnitude(); magnitude > 0.0001f)
		{
			LookIn(direction * (1.f / magnitude));
		}
	}

	template<std::floating_point T>
	std::string Transform2D<T>::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation, scale.ToString());
	}

	template<std::floating_point T>
	bool Transform2D<T>::operator ==(const Transform2D& other) const noexcept
	{
		return position == other.position && rotation == other.rotation && scale == other.scale;
	}

	template<std::floating_point T>
	bool AreAlmostEqual(const Transform2D<T>& left, const Transform2D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position(), tolerance) && Core::AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && Core::AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform2D<T>& transform)
	{
		return stream << transform.ToString();
	}
}
