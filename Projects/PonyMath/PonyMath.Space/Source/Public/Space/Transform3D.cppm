/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Space:Transform3D;

import <optional>;

import PonyMath.Core;

export namespace PonyMath::Space
{
	class Transform3D final // TODO: Add docs and tests
	{
	public:
		[[nodiscard("Pure constructor")]]
		Transform3D() noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, const Core::Vector3<float>& scale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Core::Vector3<float>& position, const Core::Quaternion<float>& rotation, float uniformScale) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform3D(const Transform3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform3D(Transform3D&& other) noexcept = default;

		~Transform3D() noexcept = default;

		[[nodiscard("Pure function")]]
		const Core::Vector3<float>& Position() const noexcept;
		void Position(const Core::Vector3<float>& positionToSet) noexcept;

		[[nodiscard("Pure function")]]
		const Core::Quaternion<float>& Rotation() const noexcept;
		void Rotation(const Core::Quaternion<float>& rotationToSet) noexcept;

		[[nodiscard("Pure function")]]
		const Core::Vector3<float>& Scale() const noexcept;
		void Scale(const Core::Vector3<float>& scaleToSet) noexcept;
		void Scale(float uniformScale) noexcept;

		[[nodiscard("Pure function")]]
		const Core::Matrix4x4<float>& TrsMatrix() const noexcept;

		[[nodiscard("Pure function")]]
		Core::Vector3<float> Forward() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Back() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Up() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Down() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Right() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<float> Left() const noexcept;

		void Translate(const Core::Vector3<float>& translation) noexcept;
		void Rotate(const Core::Quaternion<float>& rotationToAdd) noexcept;

		void LookIn(const Core::Vector3<float>& direction, const Core::Vector3<float>& up) noexcept;
		void LookAt(const Core::Vector3<float>& point, const Core::Vector3<float>& up) noexcept;

		Transform3D& operator =(const Transform3D& other) noexcept = default;
		Transform3D& operator =(Transform3D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Transform3D& other) const noexcept;

	private:
		Core::Vector3<float> position;
		Core::Quaternion<float> rotation;
		Core::Vector3<float> scale;

		mutable std::optional<Core::Matrix4x4<float>> trs;
	};
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
		scale = Core::Vector3<float>(uniformScale, uniformScale, uniformScale);
		trs = std::nullopt;
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
	}

	void Transform3D::LookAt(const Core::Vector3<float>& point, const Core::Vector3<float>& up) noexcept
	{
		LookIn(point - position, up);
	}

	bool Transform3D::operator ==(const Transform3D& other) const noexcept
	{
		return position == other.position && rotation == other.rotation && scale == other.scale;
	}
}
