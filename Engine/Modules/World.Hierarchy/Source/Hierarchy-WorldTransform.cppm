/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:WorldTransform;

import std;

import PonyEngine.Math;

import :LocalTransform;
import :Types;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief World transform.
	/// @tparam Size Dimension.
	template<std::size_t Size> requires (Size == 2 || Size == 3)
	class WorldTransform final
	{
	public:
		using PositionType = Math::Vector<PositionComponentType, Size>; ///< Position type.
		using RSMatrixType = Math::Matrix<RotationScaleComponentType, Size, Size>; ///< Rotation-scaling matrix type.
		using ScaleType = Math::Vector<RotationScaleComponentType, Size>; ///< Scale type.

		/// @brief Creates a transform with a zero position, zero rotation and scale of one.
		[[nodiscard("Pure constructor")]]
		WorldTransform() noexcept;
		/// @brief Creates a transform with the given position, zero rotation and scale of one.
		/// @param position Position.
		[[nodiscard("Pure constructor")]]
		explicit WorldTransform(const PositionType& position) noexcept;
		/// @brief Creates a transform with a zero position and given rotation and scale.
		/// @param rotationScaling Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		explicit WorldTransform(const RSMatrixType& rotationScaling) noexcept;
		/// @brief Creates a transform.
		/// @param position Position.
		/// @param rotationScaling Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		WorldTransform(const PositionType& position, const RSMatrixType& rotationScaling) noexcept;
		/// @brief Creates a world transform from the local transform.
		/// @param transform Local transform.
		[[nodiscard("Pure constructor")]]
		explicit WorldTransform(const LocalTransform<Size>& transform) noexcept;
		/// @brief Creates a world transform from the local transform.
		/// @param transform Local transform.
		/// @param parentTransform Parent world transform.
		[[nodiscard("Pure constructor")]]
		WorldTransform(const LocalTransform<Size>& transform, const WorldTransform& parentTransform) noexcept;
		[[nodiscard("Pure constructor")]]
		WorldTransform(const WorldTransform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		WorldTransform(WorldTransform&& other) noexcept = default;

		~WorldTransform() noexcept = default;

		/// @brief Gets an identity transform.
		/// @return Identity transform.
		[[nodiscard("Pure function")]]
		static const WorldTransform& Identity() noexcept;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		const PositionType& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		void Position(const PositionType& position) noexcept;
		/// @brief Gets the rotation-scaling matrix.
		/// @return Rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		const RSMatrixType& RotationScaling() const noexcept;
		/// @brief Sets the rotation-scaling matrix.
		/// @param rsMatrix Rotation-scaling matrix.
		void RotationScaling(const RSMatrixType& rsMatrix) noexcept;

		/// @brief Check if all the components of the transform are finite.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Gets the transform right vector.
		/// @return Right.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Right() const noexcept;
		/// @brief Gets the transform left vector.
		/// @return Left.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Left() const noexcept;
		/// @brief Gets the transform up vector.
		/// @return Up.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Up() const noexcept;
		/// @brief Gets the transform down vector.
		/// @return Down.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Down() const noexcept;
		/// @brief Gets the transform forward vector.
		/// @return Forward.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Forward() const noexcept requires (Size == 3);
		/// @brief Gets the transform back vector.
		/// @return Back.
		/// @remark It's scaled.
		[[nodiscard("Pure function")]]
		ScaleType Back() const noexcept requires (Size == 3);

		WorldTransform& operator =(const WorldTransform& other) noexcept = default;
		WorldTransform& operator =(WorldTransform&& other) noexcept = default;

		/// @brief Checks if two transforms are the same: they have the same position, rotation and scale.
		/// @param other Other transform.
		/// @return @a True if they're the same; @a false otherwise.
		[[nodiscard("Pure operator")]]
		bool operator ==(const WorldTransform& other) const noexcept = default;

	private:
		PositionType position; ///< Position.
		RSMatrixType rotationScaling; ///< Rotation-scaling.
	};

	/// @brief World transform 2D.
	using WorldTransform2D = WorldTransform<2>;
	/// @brief World transform 3D.
	using WorldTransform3D = WorldTransform<3>;

	/// @brief Applies the transform to the point vector.
	/// @tparam T Vector component type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Point.
	/// @return Transformed point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformPoint(const WorldTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept;
	/// @brief Applies the transform rotation and scale to the direction vector.
	/// @tparam T Vector component type.
	/// @tparam Size Dimension.
	/// @param transform Transform.
	/// @param vector Direction.
	/// @return Transformed direction.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	Math::Vector<T, Size> TransformDirection(const WorldTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept;

	/// @brief Combines the transforms.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @return Combined transform.
	template<std::size_t Size> [[nodiscard("Pure function")]]
	WorldTransform<Size> Combine(const WorldTransform<Size>& lhs, const WorldTransform<Size>& rhs) noexcept;
	/// @brief Combines the transforms.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @return Combined transform.
	template<std::size_t Size> [[nodiscard("Pure function")]]
	WorldTransform<Size> Combine(const WorldTransform<Size>& lhs, const LocalTransform<Size>& rhs) noexcept;

	/// @brief Checks if positions, rotations and scales of the two transforms are almost equal.
	/// @tparam Size Dimension.
	/// @param lhs Left transform.
	/// @param rhs Right transform.
	/// @param tolerance Tolerance.
	/// @return @a True if they're almost equal; @a false otherwise.
	template<std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const WorldTransform<Size>& lhs, const WorldTransform<Size>& rhs,
		const Math::Tolerance<PositionComponentType>& tolerance = Math::Tolerance<PositionComponentType>()) noexcept requires (Size == 2 || Size == 3);
}

namespace PonyEngine::World::Hierarchy
{
	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform() noexcept :
		position(PositionType::Zero()),
		rotationScaling(RSMatrixType::Identity())
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform(const PositionType& position) noexcept :
		position(position),
		rotationScaling(RSMatrixType::Identity())
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform(const RSMatrixType& rotationScaling) noexcept :
		position(PositionType::Zero()),
		rotationScaling(rotationScaling)
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform(const PositionType& position, const RSMatrixType& rotationScaling) noexcept :
		position(position),
		rotationScaling(rotationScaling)
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform(const LocalTransform<Size>& transform) noexcept :
		position(transform.Position()),
		rotationScaling(Math::RSMatrix(transform.Rotation(), transform.Scale()))
	{
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::WorldTransform(const LocalTransform<Size>& transform, const WorldTransform& parentTransform) noexcept
	{
		*this = Combine(parentTransform, transform);
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const WorldTransform<Size>& WorldTransform<Size>::Identity() noexcept
	{
		static const auto identity = WorldTransform();
		return identity;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const WorldTransform<Size>::PositionType& WorldTransform<Size>::Position() const noexcept
	{
		return position;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void WorldTransform<Size>::Position(const PositionType& position) noexcept
	{
		this->position = position;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	const WorldTransform<Size>::RSMatrixType& WorldTransform<Size>::RotationScaling() const noexcept
	{
		return rotationScaling;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	void WorldTransform<Size>::RotationScaling(const RSMatrixType& rsMatrix) noexcept
	{
		rotationScaling = rsMatrix;
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	bool WorldTransform<Size>::IsFinite() const noexcept
	{
		return position.IsFinite() && rotationScaling.IsFinite();
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Right() const noexcept
	{
		return TransformDirection(*this, ScaleType::Right());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Left() const noexcept
	{
		return TransformDirection(*this, ScaleType::Left());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Up() const noexcept
	{
		return TransformDirection(*this, ScaleType::Up());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Down() const noexcept
	{
		return TransformDirection(*this, ScaleType::Down());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Forward() const noexcept requires (Size == 3)
	{
		return TransformDirection(*this, ScaleType::Forward());
	}

	template<std::size_t Size> requires (Size == 2 || Size == 3)
	WorldTransform<Size>::ScaleType WorldTransform<Size>::Back() const noexcept requires (Size == 3)
	{
		return TransformDirection(*this, ScaleType::Back());
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformPoint(const WorldTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		using PositionComponent = std::conditional_t<(sizeof(T) > sizeof(PositionComponentType)), T, PositionComponentType>;
		using PositionType = Math::Vector<PositionComponent, Size>;
		using RotationScaleComponent = std::conditional_t<(sizeof(T) > sizeof(RotationScaleComponentType)), T, RotationScaleComponentType>;
		using RSMatrixType = Math::Matrix<RotationScaleComponent, Size, Size>;
		using VectorType = Math::Vector<RotationScaleComponent, Size>;

		VectorType result = static_cast<VectorType>(vector);
		result = static_cast<RSMatrixType>(transform.RotationScaling()) * result;

		return static_cast<Math::Vector<T, Size>>(static_cast<PositionType>(result) + static_cast<PositionType>(transform.Position()));
	}

	template<std::floating_point T, std::size_t Size>
	Math::Vector<T, Size> TransformDirection(const WorldTransform<Size>& transform, const Math::Vector<T, Size>& vector) noexcept
	{
		using RotationScaleComponent = std::conditional_t<(sizeof(T) > sizeof(RotationScaleComponentType)), T, RotationScaleComponentType>;
		using RSMatrixType = Math::Matrix<RotationScaleComponent, Size, Size>;
		using VectorType = Math::Vector<RotationScaleComponent, Size>;

		VectorType result = static_cast<VectorType>(vector);
		result = static_cast<RSMatrixType>(transform.RotationScaling()) * result;

		return static_cast<Math::Vector<T, Size>>(result);
	}

	template<std::size_t Size>
	WorldTransform<Size> Combine(const WorldTransform<Size>& lhs, const WorldTransform<Size>& rhs) noexcept
	{
		using PositionMatrix = Math::Matrix<PositionComponentType, Size, Size>;

		const typename WorldTransform<Size>::PositionType position = lhs.Position() + static_cast<PositionMatrix>(lhs.RotationScaling()) * rhs.Position();
		const typename WorldTransform<Size>::RSMatrixType rotationScaling = lhs.RotationScaling() * rhs.RotationScaling();

		return WorldTransform<Size>(position, rotationScaling);
	}

	template<std::size_t Size>
	WorldTransform<Size> Combine(const WorldTransform<Size>& lhs, const LocalTransform<Size>& rhs) noexcept
	{
		using PositionMatrix = Math::Matrix<PositionComponentType, Size, Size>;

		const typename WorldTransform<Size>::PositionType position = lhs.Position() + static_cast<PositionMatrix>(lhs.RotationScaling()) * rhs.Position();
		const typename WorldTransform<Size>::RSMatrixType rotationScaling = lhs.RotationScaling() * Math::RSMatrix(rhs.Rotation(), rhs.Scale());

		return WorldTransform<Size>(position, rotationScaling);
	}

	template<std::size_t Size>
	bool AreAlmostEqual(const WorldTransform<Size>& lhs, const WorldTransform<Size>& rhs,
		const Math::Tolerance<PositionComponentType>& tolerance) noexcept requires (Size == 2 || Size == 3)
	{
		const auto smallTolerance = static_cast<Math::Tolerance<RotationScaleComponentType>>(tolerance);
		return AreAlmostEqual(lhs.Position(), rhs.Position(), tolerance) && AreAlmostEqual(lhs.RotationScaling(), rhs.RotationScaling(), smallTolerance);
	}
}
