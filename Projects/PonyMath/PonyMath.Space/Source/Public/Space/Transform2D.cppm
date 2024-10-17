/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Space:Transform2D;

import <format>;
import <optional>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Space
{
	/// @brief 3D transform implementation.
	class Transform2D final // TODO: Add docs and tests
	{
	public:
		using PositionType = Core::Vector2<float>; ///< Position type.
		using RotationType = float; ///< Rotation type.
		using ScaleType = Core::Vector2<float>; ///< Scale type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		Transform2D() noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation in radians.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		Transform2D(const Core::Vector2<float>& position, float rotation, const Core::Vector2<float>& scale) noexcept;
		/// @brief Creates a transform with arguments.
		/// @param position Position.
		/// @param rotation Rotation in radians.
		/// @param uniformScale Scale. It will be applied to all the axis.
		[[nodiscard("Pure constructor")]]
		Transform2D(const Core::Vector2<float>& position, float rotation, float uniformScale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform2D(const Transform2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform2D(Transform2D&& other) noexcept = default;

		~Transform2D() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const Core::Vector2<float>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param positionToSet Position to set.
		void Position(const Core::Vector2<float>& positionToSet) noexcept;

		/// @brief Gets the rotation.
		/// @return Rotation in radians.
		[[nodiscard("Pure function")]]
		float Rotation() const noexcept;
		/// @brief Sets the rotation.
		/// @param rotationToSet Rotation in radians to set.
		void Rotation(float rotationToSet) noexcept;

		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const Core::Vector2<float>& Scale() const noexcept;
		/// @brief Sets the scale.
		/// @param scaleToSet Scale to set.
		void Scale(const Core::Vector2<float>& scaleToSet) noexcept;
		/// @brief Sets the uniform scale.
		/// @param uniformScale Scale.
		void Scale(float uniformScale) noexcept;

		/// @brief Gets the translation-rotation-scaling matrix.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		const Core::Matrix3x3<float>& TrsMatrix() const noexcept;

		/// @brief Gets the transform up vector.
		/// @return Up.
		[[nodiscard("Pure function")]]
		Core::Vector2<float> Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		[[nodiscard("Pure function")]]
		Core::Vector2<float> Down() const noexcept;
		/// @brief Gets the transform right vector.
		/// @return Right.
		[[nodiscard("Pure function")]]
		Core::Vector2<float> Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		[[nodiscard("Pure function")]]
		Core::Vector2<float> Left() const noexcept;

		/// @brief Translates the transform.
		/// @param translation Translation.
		void Translate(const Core::Vector2<float>& translation) noexcept;
		/// @brief Rotates the transform.
		/// @param rotationToAdd Rotation in radians.
		void Rotate(float rotationToAdd) noexcept;

		/// @brief Rotates the transform so that it looks in the specific direction.
		/// @param direction Look direction. Must be unit.
		void LookIn(const Core::Vector2<float>& direction) noexcept;
		/// @brief Rotates the transform so that it looks at the specific point.
		/// @note The function does nothing if the @p point is too close to the current position.
		/// @param point Look target.
		void LookAt(const Core::Vector2<float>& point) noexcept;

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
		Core::Vector2<float> position; ///< Position.
		float rotation; ///< Rotation.
		Core::Vector2<float> scale; ///< Scale.

		/// @brief Translation-rotation-scaling matrix.
		/// It becomes nullopt everytime something is changed in the transform. The function @p TrsMatrix() sets a new matrix and if it's nullopt.
		mutable std::optional<Core::Matrix3x3<float>> trs;
	};

	/// @brief Checks if positions, rotations and scaled of the two transforms are almost equal.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they're almost equal; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Transform2D& left, const Transform2D& right, float tolerance = 0.00001f) noexcept;

	/// @brief Puts the transform ToString() to the stream.
	/// @param stream Target.
	/// @param transform Transform.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, const Transform2D& transform);
}

namespace PonyMath::Space
{
	Transform2D::Transform2D() noexcept :
		Transform2D(Core::Vector2<float>::Predefined::Zero, 0.f, Core::Vector2<float>::Predefined::One)
	{
	}

	Transform2D::Transform2D(const Core::Vector2<float>& position, const float rotation, const Core::Vector2<float>& scale) noexcept :
		position(position),
		rotation{rotation},
		scale(scale)
	{
	}

	Transform2D::Transform2D(const Core::Vector2<float>& position, const float rotation, const float uniformScale) noexcept :
		Transform2D(position, rotation, Core::Vector2<float>(uniformScale, uniformScale))
	{
	}

	const Core::Vector2<float>& Transform2D::Position() const noexcept
	{
		return position;
	}

	void Transform2D::Position(const Core::Vector2<float>& positionToSet) noexcept
	{
		position = positionToSet;
		trs = std::nullopt;
	}

	float Transform2D::Rotation() const noexcept
	{
		return rotation;
	}

	void Transform2D::Rotation(const float rotationToSet) noexcept
	{
		rotation = rotationToSet;
		trs = std::nullopt;
	}

	const Core::Vector2<float>& Transform2D::Scale() const noexcept
	{
		return scale;
	}

	void Transform2D::Scale(const Core::Vector2<float>& scaleToSet) noexcept
	{
		scale = scaleToSet;
		trs = std::nullopt;
	}

	void Transform2D::Scale(const float uniformScale) noexcept
	{
		Scale(Core::Vector2<float>(uniformScale, uniformScale));
	}

	const Core::Matrix3x3<float>& Transform2D::TrsMatrix() const noexcept
	{
		if (!trs.has_value())
		{
			trs = Core::TrsMatrix(position, rotation, scale);
		}

		return trs.value();
	}

	Core::Vector2<float> Transform2D::Up() const noexcept
	{
		return Core::Rotate(Core::Vector2<float>::Predefined::Up, rotation);
	}

	Core::Vector2<float> Transform2D::Down() const noexcept
	{
		return Core::Rotate(Core::Vector2<float>::Predefined::Down, rotation);
	}

	Core::Vector2<float> Transform2D::Right() const noexcept
	{
		return Core::Rotate(Core::Vector2<float>::Predefined::Right, rotation);
	}

	Core::Vector2<float> Transform2D::Left() const noexcept
	{
		return Core::Rotate(Core::Vector2<float>::Predefined::Left, rotation);
	}

	void Transform2D::Translate(const Core::Vector2<float>& translation) noexcept
	{
		position += translation;
		trs = std::nullopt;
	}

	void Transform2D::Rotate(const float rotationToAdd) noexcept
	{
		rotation += rotationToAdd;
		trs = std::nullopt;
	}

	void Transform2D::LookIn(const Core::Vector2<float>& direction) noexcept
	{
		rotation = Core::AngleSigned(Core::Vector2<float>::Predefined::Right, direction);
		trs = std::nullopt;
	}

	void Transform2D::LookAt(const Core::Vector2<float>& point) noexcept
	{
		if (!Core::AreAlmostEqual(point, position))
		{
			LookIn((point - position).Normalized());
		}
	}

	std::string Transform2D::ToString() const
	{
		return std::format("Position: {}, Rotation: {}, Scale: {}", position.ToString(), rotation, scale.ToString());
	}

	bool Transform2D::operator ==(const Transform2D& other) const noexcept
	{
		return position == other.position && rotation == other.rotation && scale == other.scale;
	}

	bool AreAlmostEqual(const Transform2D& left, const Transform2D& right, const float tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position(), tolerance) && Core::AreAlmostEqual(left.Rotation(), right.Rotation(), tolerance) && Core::AreAlmostEqual(left.Scale(), right.Scale(), tolerance);
	}

	std::ostream& operator <<(std::ostream& stream, const Transform2D& transform)
	{
		return stream << transform.ToString();
	}
}
