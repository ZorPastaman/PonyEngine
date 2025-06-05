/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Space:Transform3D;

import <concepts>;
import <format>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Space
{
	/// @brief 3D transform implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Transform3D final
	{
	public:
		/// @brief Creates a transform with a zero position, identity rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform3D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation. Must be unit.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform3D(const Core::Vector3<T>& position, const Core::Quaternion<T>& rotation, const Core::Vector3<T>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Transform3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform3D(Transform3D&& other) noexcept = default;

		~Transform3D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		Core::Vector3<T>& Position() noexcept;
		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Core::Vector3<T>& Position() const noexcept;

		/// @brief Gets the rotation.
		/// @return Rotation.
		[[nodiscard("Pure function")]]
		Core::Quaternion<T>& Rotation() noexcept;
		/// @brief Gets the rotation.
		/// @return Rotation.
		[[nodiscard("Pure function")]]
		const Core::Quaternion<T>& Rotation() const noexcept;

		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		Core::Vector3<T>& Scale() noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Core::Vector3<T>& Scale() const noexcept;

		/// @brief Computes a translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		Core::Matrix4x4<T> TrsMatrix() const noexcept;

		/// @brief Gets the transform forward vector.
		/// @return Forward.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Forward() const noexcept;
		/// @brief Gets the transform back vector.
		/// @return Back.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Back() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Down() const noexcept;
		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Left() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Core::Vector3<T>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @param rotationToAdd Rotation. Must be unit.
		void Rotate(const Core::Quaternion<T>& rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const Core::Vector3<T>& direction, const Core::Vector3<T>& up) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const Core::Vector3<T>& point, const Core::Vector3<T>& up) noexcept;

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
		bool operator ==(const Transform3D& other) const noexcept;

	private:
		Core::Vector3<T> position; ///< Position.
		Core::Quaternion<T> rotation; ///< Rotation.
		Core::Vector3<T> scale; ///< Scale.
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @tparam T Component type.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform3D<T>& left, const Transform3D<T>& right, T tolerance = 0.00001f) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform3D<T>& transform);
}

namespace PonyMath::Space
{
	template<std::floating_point T>
	Transform3D<T>::Transform3D() noexcept :
		Transform3D(Core::Vector3<T>::Predefined::Zero, Core::Quaternion<T>::Predefined::Identity, Core::Vector3<T>::Predefined::One)
	{
	}

	template<std::floating_point T>
	Transform3D<T>::Transform3D(const Core::Vector3<T>& position, const Core::Quaternion<T>& rotation, const Core::Vector3<T>& scale) noexcept :
		position(position),
		rotation(rotation),
		scale(scale)
	{
	}

	template<std::floating_point T>
	Core::Vector3<T>& Transform3D<T>::Position() noexcept
	{
		return position;
	}

	template<std::floating_point T>
	const Core::Vector3<T>& Transform3D<T>::Position() const noexcept
	{
		return position;
	}

	template<std::floating_point T>
	Core::Quaternion<T>& Transform3D<T>::Rotation() noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	const Core::Quaternion<T>& Transform3D<T>::Rotation() const noexcept
	{
		return rotation;
	}

	template<std::floating_point T>
	Core::Vector3<T>& Transform3D<T>::Scale() noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	const Core::Vector3<T>& Transform3D<T>::Scale() const noexcept
	{
		return scale;
	}

	template<std::floating_point T>
	Core::Matrix4x4<T> Transform3D<T>::TrsMatrix() const noexcept
	{
		return Core::TrsMatrix(position, rotation, scale);
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Forward() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Forward;
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Back() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Back;
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Up() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Up;
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Down() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Down;
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Right() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Right;
	}

	template<std::floating_point T>
	Core::Vector3<T> Transform3D<T>::Left() const noexcept
	{
		return rotation * Core::Vector3<T>::Predefined::Left;
	}

	template<std::floating_point T>
	void Transform3D<T>::Translate(const Core::Vector3<T>& translation) noexcept
	{
		position += translation;
	}

	template<std::floating_point T>
	void Transform3D<T>::Rotate(const Core::Quaternion<T>& rotationToAdd) noexcept
	{
		rotation = rotationToAdd * rotation;
	}

	template<std::floating_point T>
	void Transform3D<T>::LookIn(const Core::Vector3<T>& direction, const Core::Vector3<T>& up) noexcept
	{
		rotation = Core::LookInRotationQuaternion(direction, up);
	}

	template<std::floating_point T>
	void Transform3D<T>::LookAt(const Core::Vector3<T>& point, const Core::Vector3<T>& up) noexcept
	{
		const Core::Vector3<T> direction = point - position;
		if (const T magnitude = direction.Magnitude(); magnitude > 0.0001f)
		{
			LookIn(direction * (1.f / magnitude), up);
		}
	}

	template<std::floating_point T>
	std::string Transform3D<T>::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation.ToString(), scale.ToString());
	}

	template<std::floating_point T>
	bool Transform3D<T>::operator ==(const Transform3D& other) const noexcept
	{
		return position == other.position && rotation == other.rotation && scale == other.scale;
	}

	template<std::floating_point T>
	bool AreAlmostEqual(const Transform3D<T>& left, const Transform3D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position(), tolerance) && Core::AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && Core::AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Transform3D<T>& transform)
	{
		return stream << transform.ToString();
	}
}
