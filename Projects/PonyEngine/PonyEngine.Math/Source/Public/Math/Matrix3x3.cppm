/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix3x3;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :Common;
import :Matrix2x2;
import :Vector3;

namespace PonyEngine::Math
{
	export template<Arithmetic T>
	struct Matrix3x3 final
	{
	public:
		class Access final
		{
		public:
			Access(const Access&) = delete;
			Access(Access&&) = delete;

			inline ~Access() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector3<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline T& operator [](std::size_t columnIndex) const noexcept;

			Access& operator =(const Access&) = delete;
			Access& operator =(Access&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline Access(Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			Matrix3x3& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix3x3;
		};

		class ConstAccess final
		{
		public:
			ConstAccess(const ConstAccess&) = delete;
			ConstAccess(ConstAccess&&) = delete;

			inline ~ConstAccess() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector3<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline const T& operator [](std::size_t columnIndex) const noexcept;

			ConstAccess& operator =(const ConstAccess&) = delete;
			ConstAccess& operator =(ConstAccess&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline ConstAccess(const Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			const Matrix3x3& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix3x3;
		};

		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(T m00, T m01, T m02, 
							T m10, T m11, T m12, 
							T m20, T m21, T m22) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix3x3(const Vector3<T>& row0, const Vector3<T>& row1, const Vector3<T>& row2) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(const Matrix3x3& other) noexcept = default;

		constexpr ~Matrix3x3() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr T Determinant() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Adjugate() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Transposed() const noexcept;
		inline void Transpose() noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Inversed() const noexcept;
		inline void Inverse() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Matrix to multiply by.
		void Scale(const Matrix3x3<T>& scale) noexcept;

		[[nodiscard("Pure function")]]
		Vector3<T> GetRow(std::size_t rowIndex) const noexcept;
		void SetRow(std::size_t rowIndex, const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		Vector3<T> GetColumn(std::size_t columnIndex) noexcept;
		void SetColumn(std::size_t columnIndex, const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetDiagonal() const noexcept;
		inline void SetDiagonal(const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetCounterDiagonal() const noexcept;
		inline void SetCounterDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Creates a string representing a state of a @p Matrix.
		///        The format is '(m00, m01, m02)(m10, m11, m12)(m20, m21, m22)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		inline Access operator [](std::size_t rowIndex) noexcept;
		[[nodiscard("Pure operator")]]
		inline ConstAccess operator [](std::size_t rowIndex) const noexcept;

		Matrix3x3& operator =(const Matrix3x3& other) noexcept = default;
		Matrix3x3& operator +=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator -=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		Matrix3x3& operator *=(ComputationalType multiplier) noexcept;
		Matrix3x3& operator *=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix3x3& other) const noexcept = default;

		static const Matrix3x3 Identity;
		static const Matrix3x3 Zero;

		constexpr inline static const std::size_t RowCount = 3;
		constexpr inline static const std::size_t ColumnCount = 3;
		constexpr inline static const std::size_t ComponentCount = RowCount * ColumnCount;

		T m00; T m01; T m02;
		T m10; T m11; T m12;
		T m20; T m21; T m22;
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Matrix.
	/// @param right Multiplier @p Matrix.
	/// @return Product @p Matrix.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, typename Matrix3x3<T>::ComputationalType tolerance = typename Matrix3x3<T>::ComputationalType{0.00001}) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType multiplier) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(T multiplier, const Matrix3x3<T>& matrix) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType divisor) noexcept;

	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix);

	template<Arithmetic T>
	static const std::array<T Matrix3x3<T>::*, Matrix3x3<T>::ComponentCount> s_matrix3x3ComponentPointers
	{
		&Matrix3x3<T>::m00, &Matrix3x3<T>::m01, &Matrix3x3<T>::m02,
		&Matrix3x3<T>::m10, &Matrix3x3<T>::m11, &Matrix3x3<T>::m12,
		&Matrix3x3<T>::m20, &Matrix3x3<T>::m21, &Matrix3x3<T>::m22
	};

	template<Arithmetic T>
	inline Matrix3x3<T>::Access::Access(Matrix3x3& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::Access::operator Vector3<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::Access::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.*s_matrix3x3ComponentPointers<T>[m_rowIndex * std::size_t{3} + columnIndex];
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::ConstAccess::ConstAccess(const Matrix3x3& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::ConstAccess::operator Vector3<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline const T& Matrix3x3<T>::ConstAccess::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.*s_matrix3x3ComponentPointers<T>[m_rowIndex * std::size_t{3} + columnIndex];
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T>::Matrix3x3(const T m00, const T m01, const T m02,
									const T m10, const T m11, const T m12,
									const T m20, const T m21, const T m22) noexcept :
		m00{m00}, m01{m01}, m02{m02},
		m10{m10}, m11{m11}, m12{m12},
		m20{m20}, m21{m21}, m22{m22}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::Matrix3x3(const Vector3<T>& row0, const Vector3<T>& row1, const Vector3<T>& row2) noexcept :
		Matrix3x3<T>(row0.x, row0.y, row0.z, 
					row1.x, row1.y, row1.z, 
					row2.x, row2.y, row2.z)
	{
	}

	template<Arithmetic T>
	constexpr T Matrix3x3<T>::Determinant() const noexcept
	{
		return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 -
			m02 * m11 * m20 - m01 * m10 * m22 - m00 * m12 * m21;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Adjugate() const noexcept
	{
		const T minor00Determinant = Matrix2x2(m11, m12, m21, m22).Determinant();
		const T minor01Determinant = -Matrix2x2(m10, m12, m20, m22).Determinant();
		const T minor02Determinant = Matrix2x2(m10, m11, m20, m21).Determinant();
		const T minor10Determinant = -Matrix2x2(m01, m02, m21, m22).Determinant();
		const T minor11Determinant = Matrix2x2(m00, m02, m20, m22).Determinant();
		const T minor12Determinant = -Matrix2x2(m00, m01, m20, m21).Determinant();
		const T minor20Determinant = Matrix2x2(m01, m02, m11, m12).Determinant();
		const T minor21Determinant = -Matrix2x2(m00, m02, m10, m12).Determinant();
		const T minor22Determinant = Matrix2x2(m00, m01, m10, m11).Determinant();

		return Matrix3x3(minor00Determinant, minor01Determinant, minor02Determinant,
						minor10Determinant, minor11Determinant, minor12Determinant,
						minor20Determinant, minor21Determinant, minor22Determinant);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Transposed() const noexcept
	{
		return Matrix3x3<T>(m00, m10, m20, 
							m01, m11, m21, 
							m02, m12, m22);
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::Transpose() noexcept
	{
		*this = Transposed();
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Inversed() const noexcept
	{
		const Matrix3x3<T> transposed = Transposed();
		const Matrix3x3<T> adjugate = transposed.Adjugate();
		const T determinant = Determinant();

		return adjugate * (ComputationalType{1} / determinant);
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::Inverse() noexcept
	{
		*this = Inversed();
	}

	template<Arithmetic T>
	bool Matrix3x3<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(m00) && std::isfinite(m01) && std::isfinite(m02) &&
				std::isfinite(m10) && std::isfinite(m11) && std::isfinite(m12) &&
				std::isfinite(m20) && std::isfinite(m21) && std::isfinite(m22);
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Matrix3x3<T>::Scale(const Matrix3x3<T>& scale) noexcept
	{
		m00 *= scale.m00;
		m01 *= scale.m01;
		m02 *= scale.m02;
		m10 *= scale.m10;
		m11 *= scale.m11;
		m12 *= scale.m12;
		m20 *= scale.m20;
		m21 *= scale.m21;
		m22 *= scale.m22;
	}

	template<Arithmetic T>
	Vector3<T> Matrix3x3<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const std::size_t firstElementIndex = rowIndex * 3;

		const T x = this->*s_matrix3x3ComponentPointers<T>[firstElementIndex];
		const T y = this->*s_matrix3x3ComponentPointers<T>[firstElementIndex + 1];
		const T z = this->*s_matrix3x3ComponentPointers<T>[firstElementIndex + 2];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetRow(const std::size_t rowIndex, const Vector3<T>& value) noexcept
	{
		const std::size_t firstElementIndex = rowIndex * 3;

		this->*s_matrix3x3ComponentPointers<T>[firstElementIndex] = value.x;
		this->*s_matrix3x3ComponentPointers<T>[firstElementIndex + 1] = value.y;
		this->*s_matrix3x3ComponentPointers<T>[firstElementIndex + 2] = value.z;
	}

	template<Arithmetic T>
	Vector3<T> Matrix3x3<T>::GetColumn(const std::size_t columnIndex) noexcept
	{
		const T x = this->*s_matrix3x3ComponentPointers<T>[columnIndex];
		const T y = this->*s_matrix3x3ComponentPointers<T>[columnIndex + 3];
		const T z = this->*s_matrix3x3ComponentPointers<T>[columnIndex + 6];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetColumn(const std::size_t columnIndex, const Vector3<T>& value) noexcept
	{
		this->*s_matrix3x3ComponentPointers<T>[columnIndex] = value.x;
		this->*s_matrix3x3ComponentPointers<T>[columnIndex + 3] = value.y;
		this->*s_matrix3x3ComponentPointers<T>[columnIndex + 6] = value.z;
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetDiagonal() const noexcept
	{
		return Vector3<T>(m00, m11, m22);
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::SetDiagonal(const Vector3<T>& value) noexcept
	{
		m00 = value.x;
		m11 = value.y;
		m22 = value.z;
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetCounterDiagonal() const noexcept
	{
		return Vector3<T>(m02, m11, m20);
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::SetCounterDiagonal(const Vector3<T>& value) noexcept
	{
		m02 = value.x;
		m11 = value.y;
		m20 = value.z;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		const T m00 = left.m00 * right.m00;
		const T m01 = left.m01 * right.m01;
		const T m02 = left.m02 * right.m02;
		const T m10 = left.m10 * right.m10;
		const T m11 = left.m11 * right.m11;
		const T m12 = left.m12 * right.m12;
		const T m20 = left.m20 * right.m20;
		const T m21 = left.m21 * right.m21;
		const T m22 = left.m22 * right.m22;

		return Matrix3x3<T>(m00, m01, m02,
							m10, m11, m12,
							m20, m21, m22);
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, const typename Matrix3x3<T>::ComputationalType tolerance) noexcept
	{
		const Matrix3x3<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.m00 * diff.m00 + diff.m01 * diff.m01 + diff.m02 * diff.m02 +
										diff.m10 * diff.m10 + diff.m11 * diff.m11 + diff.m12 * diff.m12 +
										diff.m20 * diff.m20 + diff.m21 * diff.m21 + diff.m22 * diff.m22;
		
		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	std::string Matrix3x3<T>::ToString() const
	{
		return std::format("({}, {}, {})({}, {}, {})({}, {}, {})", m00, m01, m02, m10, m11, m12, m20, m21, m22);
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::Access Matrix3x3<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Access(*this, rowIndex);
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::ConstAccess Matrix3x3<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstAccess(*this, rowIndex);
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator +=(const Matrix3x3& other) noexcept
	{
		m00 += other.m00;
		m01 += other.m01;
		m02 += other.m02;
		m10 += other.m10;
		m11 += other.m11;
		m12 += other.m12;
		m20 += other.m20;
		m21 += other.m21;
		m22 += other.m22;

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator -=(const Matrix3x3& other) noexcept
	{
		m00 -= other.m00;
		m01 -= other.m01;
		m02 -= other.m02;
		m10 -= other.m10;
		m11 -= other.m11;
		m12 -= other.m12;
		m20 -= other.m20;
		m21 -= other.m21;
		m22 -= other.m22;

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		m00 *= multiplier;
		m01 *= multiplier;
		m02 *= multiplier;
		m10 *= multiplier;
		m11 *= multiplier;
		m12 *= multiplier;
		m20 *= multiplier;
		m21 *= multiplier;
		m22 *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		m00 = RoundToIntegralIfPossible<ComputationalType, T>(m00 * multiplier);
		m01 = RoundToIntegralIfPossible<ComputationalType, T>(m01 * multiplier);
		m02 = RoundToIntegralIfPossible<ComputationalType, T>(m02 * multiplier);
		m10 = RoundToIntegralIfPossible<ComputationalType, T>(m10 * multiplier);
		m11 = RoundToIntegralIfPossible<ComputationalType, T>(m11 * multiplier);
		m12 = RoundToIntegralIfPossible<ComputationalType, T>(m12 * multiplier);
		m20 = RoundToIntegralIfPossible<ComputationalType, T>(m20 * multiplier);
		m21 = RoundToIntegralIfPossible<ComputationalType, T>(m21 * multiplier);
		m22 = RoundToIntegralIfPossible<ComputationalType, T>(m22 * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const Matrix3x3& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		m00 = RoundToIntegralIfPossible<ComputationalType, T>(m00 / divisor);
		m01 = RoundToIntegralIfPossible<ComputationalType, T>(m01 / divisor);
		m02 = RoundToIntegralIfPossible<ComputationalType, T>(m02 / divisor);
		m10 = RoundToIntegralIfPossible<ComputationalType, T>(m10 / divisor);
		m11 = RoundToIntegralIfPossible<ComputationalType, T>(m11 / divisor);
		m12 = RoundToIntegralIfPossible<ComputationalType, T>(m12 / divisor);
		m20 = RoundToIntegralIfPossible<ComputationalType, T>(m20 / divisor);
		m21 = RoundToIntegralIfPossible<ComputationalType, T>(m21 / divisor);
		m22 = RoundToIntegralIfPossible<ComputationalType, T>(m22 / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		return Matrix3x3<T>(left.m00 + right.m00, left.m01 + right.m01, left.m02 + right.m02,
							left.m10 + right.m10, left.m11 + right.m11, left.m12 + right.m12,
							left.m20 + right.m20, left.m21 + right.m21, left.m22 + right.m22);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator-(const Matrix3x3<T>& matrix) noexcept
	{
		return Matrix3x3<T>(-matrix.m00, -matrix.m01, -matrix.m02,
							-matrix.m10, -matrix.m11, -matrix.m12,
							-matrix.m20, -matrix.m21, -matrix.m22);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		return Matrix3x3<T>(left.m00 - right.m00, left.m01 - right.m01, left.m02 - right.m02,
							left.m10 - right.m10, left.m11 - right.m11, left.m12 - right.m12,
							left.m20 - right.m20, left.m21 - right.m21, left.m22 - right.m22);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Matrix3x3<T>(matrix.m00 * multiplier, matrix.m01 * multiplier, matrix.m02 * multiplier,
							matrix.m10 * multiplier, matrix.m11 * multiplier, matrix.m12 * multiplier,
							matrix.m20 * multiplier, matrix.m21 * multiplier, matrix.m22 * multiplier);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m00 * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m01 * multiplier);
		const T m02 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m02 * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m10 * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m11 * multiplier);
		const T m12 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m12 * multiplier);
		const T m20 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m20 * multiplier);
		const T m21 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m21 * multiplier);
		const T m22 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m22 * multiplier);

		return Matrix3x3<T>(m00, m01, m02,
							m10, m11, m12,
							m20, m21, m22);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const T multiplier, const Matrix3x3<T>& matrix) noexcept requires(std::is_integral_v<T>)
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T> operator *(const typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		const T m00 = left.m00 * right.m00 + left.m01 * right.m10 + left.m02 * right.m20;
		const T m01 = left.m00 * right.m01 + left.m01 * right.m11 + left.m02 * right.m21;
		const T m02 = left.m00 * right.m02 + left.m01 * right.m12 + left.m02 * right.m22;
		const T m10 = left.m10 * right.m00 + left.m11 * right.m10 + left.m12 * right.m20;
		const T m11 = left.m10 * right.m01 + left.m11 * right.m11 + left.m12 * right.m21;
		const T m12 = left.m10 * right.m02 + left.m11 * right.m12 + left.m12 * right.m22;
		const T m20 = left.m20 * right.m00 + left.m21 * right.m10 + left.m22 * right.m20;
		const T m21 = left.m20 * right.m01 + left.m21 * right.m11 + left.m22 * right.m21;
		const T m22 = left.m20 * right.m02 + left.m21 * right.m12 + left.m22 * right.m22;

		return Matrix3x3<T>(m00, m01, m02,
							m10, m11, m12,
							m20, m21, m22);
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept
	{
		const T x = matrix.m00 * vector.x + matrix.m01 * vector.y + matrix.m02 * vector.z;
		const T y = matrix.m10 * vector.x + matrix.m11 * vector.y + matrix.m12 * vector.z;
		const T z = matrix.m20 * vector.x + matrix.m21 * vector.y + matrix.m22 * vector.z;

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m00 / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m01 / divisor);
		const T m02 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m02 / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m10 / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m11 / divisor);
		const T m12 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m12 / divisor);
		const T m20 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m20 / divisor);
		const T m21 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m21 / divisor);
		const T m22 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.m22 / divisor);

		return Matrix3x3<T>(m00, m01, m02,
							m10, m11, m12,
							m20, m21, m22);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	const Matrix3x3<T> Matrix3x3<T>::Identity = Matrix3x3<T>(T{1}, T{0}, T{0},
															T{0}, T{1}, T{0},
															T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Matrix3x3<T> Matrix3x3<T>::Zero = Matrix3x3<T>(T{0}, T{0}, T{0},
														T{0}, T{0}, T{0},
														T{0}, T{0}, T{0});
}
