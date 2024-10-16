/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Space:Transform3D;

import <format>;
import <optional>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Space
{
	/// @brief 3D transform implementation.
	class Transform3D final // TODO: Add docs and tests
	{
	public:
		using PositionType = Core::Vector3<float>; ///< Position type.
		using RotationType = Core::Quaternion<float>; ///< Rotation type.
		using ScaleType = Core::Vector3<float>; ///< Scale type.

		/// @brief Creates a transform with a zero position, identity rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform3D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation. Must be unit.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, const Core::Vector3<float>& scale) noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation. Must be unit.
		/// @param uniformScale Scale. It will be applied to all the axis.
		[[nodiscard("Pure constructor")]]
		Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, float uniformScale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Transform3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform3D(Transform3D&& other) noexcept = default;

		~Transform3D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Core::Vector3<float>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param positionToSet Position to set.
		void Position(const Core::Vector3<float>& positionToSet) noexcept;

		/// @brief Gets the rotation.
		/// @return Rotation.
		[[nodiscard("Pure function")]]
		const Core::Quaternion<float>& Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @param rotationToSet Rotation to set.
		void Rotation(const Core::Quaternion<float>& rotationToSet) noexcept;

		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Core::Vector3<float>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scaleToSet Scale to set.
		void Scale(const Core::Vector3<float>& scaleToSet) noexcept;
		/// @brief Sets the uniform scale.
		/// @param uniformScale Scale.
		void Scale(float uniformScale) noexcept;

		/// @brief Gets the translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		const Core::Matrix4x4<float>& TrsMatrix() const noexcept;

		/// @brief Gets the transform forward vector.
		/// @return Forward.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Forward() const noexcept;
		/// @brief Gets the transform back vector.
		/// @return Back.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Back() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Down() const noexcept;
		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Left() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Core::Vector3<float>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @param rotationToAdd Rotation. Must be unit.
		void Rotate(const Core::Quaternion<float>& rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		/// @param up Up vector. Must be unit.
		void LookIn(const Core::Vector3<float>& direction, const Core::Vector3<float>& up) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @param point Look target.
		/// @param up Up vector. Must be unit.
		void LookAt(const Core::Vector3<float>& point, const Core::Vector3<float>& up) noexcept;

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
		Core::Vector3<float> position; ///< Position.
		Core::Quaternion<float> rotation; ///< Rotation.
		Core::Vector3<float> scale; ///< Scale.

		/// @brief Translation-rotation-scaling matrix.
		/// It becomes nullopt everytime something is changed in the transform. The function @p TrsMatrix() sets a new matrix and if it's nullopt.
		mutable std::optional<Core::Matrix4x4<float>> trs;
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @return @a True if they're almost equal; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform3D& left, const Transform3D& right) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, const Transform3D& transform);
}

namespace PonyMath::Space
{
	Transform3D::Transform3D() noexcept :
		Transform3D(Core::Vector3<float>::Predefined::Zero, Core::Quaternion<float>::Predefined::Identity, Core::Vector3<float>::Predefined::One)
	{
	}

	Transform3D::Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, const Core::Vector3<float>& scale) noexcept :
		position(position),
		rotation(rotation),
		scale(scale)
	{
	}

	Transform3D::Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, const float uniformScale) noexcept :
		Transform3D(position, rotation, Core::Vector3<float>(uniformScale, uniformScale, uniformScale))
	{
	}

	const Core::Vector3<float>& Transform3D::Position() const noexcept
	{
		return position;
	}

	void Transform3D::Position(const Core::Vector3<float>& positionToSet) noexcept
	{
		position = positionToSet;
		trs = std::nullopt;
	}

	const Core::Quaternion<float>& Transform3D::Rotation() const noexcept
	{
		return rotation;
	}

	void Transform3D::Rotation(const Core::Quaternion<float>& rotationToSet) noexcept
	{
		rotation = rotationToSet;
		trs = std::nullopt;
	}

	const Core::Vector3<float>& Transform3D::Scale() const noexcept
	{
		return scale;
	}

	void Transform3D::Scale(const Core::Vector3<float>& scaleToSet) noexcept
	{
		scale = scaleToSet;
		trs = std::nullopt;
	}

	void Transform3D::Scale(const float uniformScale) noexcept
	{
		Scale(Core::Vector3<float>(uniformScale, uniformScale, uniformScale));
	}

	const Core::Matrix4x4<float>& Transform3D::TrsMatrix() const noexcept
	{
		if (!trs.has_value())
		{
			trs = Core::TrsMatrix(position, rotation, scale);
		}

		return trs.value();
	}

	Core::Vector3<float> Transform3D::Forward() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Forward;
	}

	Core::Vector3<float> Transform3D::Back() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Back;
	}

	Core::Vector3<float> Transform3D::Up() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Up;
	}

	Core::Vector3<float> Transform3D::Down() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Down;
	}

	Core::Vector3<float> Transform3D::Right() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Right;
	}

	Core::Vector3<float> Transform3D::Left() const noexcept
	{
		return rotation * Core::Vector3<float>::Predefined::Left;
	}

	void Transform3D::Translate(const Core::Vector3<float>& translation) noexcept
	{
		position += translation;
		trs = std::nullopt;
	}

	void Transform3D::Rotate(const Core::Quaternion<float>& rotationToAdd) noexcept
	{
		rotation = rotationToAdd * rotation;
		trs = std::nullopt;
	}

	void Transform3D::LookIn(const Core::Vector3<float>& direction, const Core::Vector3<float>& up) noexcept
	{
		rotation = Core::LookInRotationQuaternion(direction, up);
		trs = std::nullopt;
	}

	void Transform3D::LookAt(const Core::Vector3<float>& point, const Core::Vector3<float>& up) noexcept
	{
		if (!Core::AreAlmostEqual(point, position))
		{
			LookIn((point - position).Normalized(), up);
		}
	}

	std::string Transform3D::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation.ToString(), scale.ToString());
	}

	bool Transform3D::operator ==(const Transform3D& other) const noexcept
	{
		return position == other.position && rotation == other.rotation && scale == other.scale;
	}

	bool AreAlmostEqual(const Transform3D& left, const Transform3D& right) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position()) && Core::AreAlmostEqual(left.Rotation(), right.Rotation()) && Core::AreAlmostEqual(left.Scale(), right.Scale());
	}

	std::ostream& operator <<(std::ostream& stream, const Transform3D& transform)
	{
		return stream << transform.ToString();
	}
}
