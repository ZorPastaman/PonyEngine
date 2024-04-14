/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix2x2;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :Common;
import :Vector2;

namespace PonyEngine::Math
{
	export template<Arithmetic T>
	struct Matrix2x2 final
	{
	public:
		class Access final
		{
		public:
			Access(const Access&) = delete;
			Access(Access&&) = delete;

			inline ~Access() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector2<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline T& operator [](std::size_t columnIndex) const noexcept;

			Access& operator =(const Access&) = delete;
			Access& operator =(Access&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline Access(Matrix2x2& matrix, std::size_t rowIndex) noexcept;

			Matrix2x2& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix2x2;
		};

		class ConstAccess final
		{
		public:
			ConstAccess(const ConstAccess&) = delete;
			ConstAccess(ConstAccess&&) = delete;

			inline ~ConstAccess() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector2<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline const T& operator [](std::size_t columnIndex) const noexcept;

			ConstAccess& operator =(const ConstAccess&) = delete;
			ConstAccess& operator =(ConstAccess&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline ConstAccess(const Matrix2x2& matrix, std::size_t rowIndex) noexcept;

			const Matrix2x2& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix2x2;
		};

		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(T m00, T m01,
								T m10, T m11) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(const Vector2<T>& row0, const Vector2<T>& row1) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(const Matrix2x2& other) noexcept = default;

		constexpr inline ~Matrix2x2() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr inline T Determinant() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Matrix2x2 Adjugate() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Matrix2x2 Transposed() const noexcept;
		inline void Transpose() noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Inversed() const noexcept;
		inline void Inverse() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		// TODO: add set

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Matrix to multiply by.
		void Scale(const Matrix2x2<T>& scale) noexcept;

		[[nodiscard("Pure function")]]
		Vector2<T> GetRow(std::size_t rowIndex) const noexcept;
		void SetRow(std::size_t rowIndex, const Vector2<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		Vector2<T> GetColumn(std::size_t columnIndex) noexcept;
		void SetColumn(std::size_t columnIndex, const Vector2<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector2<T> GetDiagonal() const noexcept;
		inline void SetDiagonal(const Vector2<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector2<T> GetCounterDiagonal() const noexcept;
		inline void SetCounterDiagonal(const Vector2<T>& value) noexcept;

		/// @brief Creates a string representing a state of a @p Matrix.
		///        The format is '(m00, m01)(m10, m11)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		inline Access operator [](std::size_t rowIndex) noexcept;
		[[nodiscard("Pure operator")]]
		inline ConstAccess operator [](std::size_t rowIndex) const noexcept;

		inline Matrix2x2& operator =(const Matrix2x2& other) noexcept = default;
		Matrix2x2& operator +=(const Matrix2x2& other) noexcept;
		Matrix2x2& operator -=(const Matrix2x2& other) noexcept;
		Matrix2x2& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		Matrix2x2& operator *=(ComputationalType multiplier) noexcept;
		inline Matrix2x2& operator *=(const Matrix2x2& other) noexcept;
		Matrix2x2& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr inline bool operator ==(const Matrix2x2& other) const noexcept = default;

		static const Matrix2x2 Identity;
		static const Matrix2x2 Zero;

		constexpr inline static const std::size_t RowCount = 2;
		constexpr inline static const std::size_t ColumnCount = 2;
		constexpr inline static const std::size_t ComponentCount = RowCount * ColumnCount;

		T m00; T m01;
		T m10; T m11;
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Matrix.
	/// @param right Multiplier @p Matrix.
	/// @return Product @p Matrix.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, typename Matrix2x2<T>::ComputationalType tolerance = typename Matrix2x2<T>::ComputationalType{0.00001}) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType multiplier) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix2x2<T> operator *(T multiplier, const Matrix2x2<T>& matrix) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix2x2<T> operator *(typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType divisor) noexcept;

	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix);

	template<Arithmetic T>
	static const std::array<T Matrix2x2<T>::*, Matrix2x2<T>::ComponentCount> s_matrix2x2ComponentPointers
	{
		&Matrix2x2<T>::m00, &Matrix2x2<T>::m01,
		&Matrix2x2<T>::m10, &Matrix2x2<T>::m11
	};

	template<Arithmetic T>
	inline Matrix2x2<T>::Access::Access(Matrix2x2& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::Access::operator Vector2<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline T& Matrix2x2<T>::Access::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.*s_matrix2x2ComponentPointers<T>[m_rowIndex * std::size_t{2} + columnIndex];
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::ConstAccess::ConstAccess(const Matrix2x2& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::ConstAccess::operator Vector2<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline const T& Matrix2x2<T>::ConstAccess::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.*s_matrix2x2ComponentPointers<T>[m_rowIndex * std::size_t{2} + columnIndex];
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::Matrix2x2(const T m00, const T m01, 
											const T m10, const T m11) noexcept :
		m00{m00}, m01{m01},
		m10{m10}, m11{m11}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::Matrix2x2(const Vector2<T>& row0, const Vector2<T>& row1) noexcept :
		Matrix2x2(row0.X(), row0.Y(), row1.X(), row1.Y())
	{
	}

	template<Arithmetic T>
	constexpr inline T Matrix2x2<T>::Determinant() const noexcept
	{
		return m00 * m11 - m01 * m10;
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> Matrix2x2<T>::Adjugate() const noexcept
	{
		return Matrix2x2(m11, m10, 
						m01, m00);
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> Matrix2x2<T>::Transposed() const noexcept
	{
		return Matrix2x2(m00, m10,
						m01, m11);
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::Transpose() noexcept
	{
		*this = Transposed();
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Matrix2x2<T>::Inversed() const noexcept
	{
		const Matrix2x2<T> transposed = Transposed();
		const Matrix2x2<T> adjugate = transposed.Adjugate();
		const T determinant = Determinant();

		return adjugate * (ComputationalType{1} / determinant);
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::Inverse() noexcept
	{
		*this = Inverse();
	}

	template<Arithmetic T>
	bool Matrix2x2<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(m00) && std::isfinite(m01) &&
				std::isfinite(m10) && std::isfinite(m11);
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Scale(const Matrix2x2<T>& scale) noexcept
	{
		m00 *= scale.m00;
		m01 *= scale.m01;
		m10 *= scale.m10;
		m11 *= scale.m11;
	}

	template<Arithmetic T>
	Vector2<T> Matrix2x2<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const std::size_t firstElementIndex = rowIndex * 2;

		const T x = this->*s_matrix2x2ComponentPointers<T>[firstElementIndex];
		const T y = this->*s_matrix2x2ComponentPointers<T>[firstElementIndex + 1];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetRow(const std::size_t rowIndex, const Vector2<T>& value) noexcept
	{
		const std::size_t firstElementIndex = rowIndex * 2;

		this->*s_matrix2x2ComponentPointers<T>[firstElementIndex] = value.x;
		this->*s_matrix2x2ComponentPointers<T>[firstElementIndex + 1] = value.y;
	}

	template<Arithmetic T>
	Vector2<T> Matrix2x2<T>::GetColumn(const std::size_t columnIndex) noexcept
	{
		const T x = this->*s_matrix2x2ComponentPointers<T>[columnIndex];
		const T y = this->*s_matrix2x2ComponentPointers<T>[columnIndex + 2];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetColumn(const std::size_t columnIndex, const Vector2<T>& value) noexcept
	{
		this->*s_matrix2x2ComponentPointers<T>[columnIndex] = value.x;
		this->*s_matrix2x2ComponentPointers<T>[columnIndex + 2] = value.y;
	}

	template<Arithmetic T>
	constexpr inline Vector2<T> Matrix2x2<T>::GetDiagonal() const noexcept
	{
		return Vector2<T>(m00, m11);
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::SetDiagonal(const Vector2<T>& value) noexcept
	{
		m00 = value.x;
		m11 = value.y;
	}

	template<Arithmetic T>
	constexpr inline Vector2<T> Matrix2x2<T>::GetCounterDiagonal() const noexcept
	{
		return Vector2<T>(m01, m10);
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::SetCounterDiagonal(const Vector2<T>& value) noexcept
	{
		m01 = value.x;
		m10 = value.y;
	}

	template<Arithmetic T>
	std::string Matrix2x2<T>::ToString() const
	{
		return std::format("({}, {})({}, {})", m00, m01, m10, m11);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.m00 * right.m00, left.m01 * right.m01,
							left.m10 * right.m10, left.m11 * right.m11);
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, typename Matrix2x2<T>::ComputationalType tolerance) noexcept
	{
		const Matrix2x2<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.m00 * diff.m00 + diff.m01 * diff.m01 +
										diff.m10 * diff.m10 + diff.m11 * diff.m11;

		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.m00 + right.m00, left.m01 + right.m01,
							left.m10 + right.m10, left.m11 + right.m11);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept
	{
		return Matrix2x2<T>(-matrix.m00, -matrix.m01,
							-matrix.m10, -matrix.m11);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.m00 - right.m00, left.m01 - right.m01,
							left.m10 - right.m10, left.m11 - right.m11);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const T multiplier) noexcept
	{
		return Matrix2x2<T>(matrix.m00 * multiplier, matrix.m01 * multiplier,
							matrix.m10 * multiplier, matrix.m11 * multiplier);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m00 * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m01 * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m10 * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m11 * multiplier);

		return Matrix2x2<T>(m00, m01,
							m10, m11);
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> operator *(const T multiplier, const Matrix2x2<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> operator *(const typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		const T m00 = left.m00 * right.m00 + left.m01 * right.m10;
		const T m01 = left.m00 * right.m01 + left.m01 * right.m11;
		const T m10 = left.m10 * right.m00 + left.m11 * right.m10;
		const T m11 = left.m10 * right.m01 + left.m11 * right.m11;

		return Matrix2x2<T>(m00, m01,
							m10, m11);
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept
	{
		const T x = matrix.m00 * vector.x + matrix.m01 * vector.y;
		const T y = matrix.m10 * vector.x + matrix.m11 * vector.y;

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m00 / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m01 / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m10 / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.m11 / divisor);

		return Matrix2x2<T>(m00, m01,
			m10, m11);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::Access Matrix2x2<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Access(*this, rowIndex);
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::ConstAccess Matrix2x2<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstAccess(*this, rowIndex);
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator +=(const Matrix2x2& other) noexcept
	{
		m00 += other.m00;
		m01 += other.m01;
		m10 += other.m10;
		m11 += other.m11;

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator -=(const Matrix2x2& other) noexcept
	{
		m00 -= other.m00;
		m01 -= other.m01;
		m10 -= other.m10;
		m11 -= other.m11;

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		m00 *= multiplier;
		m01 *= multiplier;
		m10 *= multiplier;
		m11 *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		m00 = RoundToIntegralIfPossible<ComputationalType, T>(m00 * multiplier);
		m01 = RoundToIntegralIfPossible<ComputationalType, T>(m01 * multiplier);
		m10 = RoundToIntegralIfPossible<ComputationalType, T>(m10 * multiplier);
		m11 = RoundToIntegralIfPossible<ComputationalType, T>(m11 * multiplier);

		return *this;
	}

	template<Arithmetic T>
	inline Matrix2x2<T>& Matrix2x2<T>::operator *=(const Matrix2x2& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator /=(const ComputationalType divisor) noexcept
	{
		m00 = RoundToIntegralIfPossible<ComputationalType, T>(m00 / divisor);
		m01 = RoundToIntegralIfPossible<ComputationalType, T>(m01 / divisor);
		m10 = RoundToIntegralIfPossible<ComputationalType, T>(m10 / divisor);
		m11 = RoundToIntegralIfPossible<ComputationalType, T>(m11 / divisor);

		return *this;
	}

	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Identity = Matrix2x2<T>(T{1}, T{0},
															T{0}, T{1});
	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Zero = Matrix2x2<T>(T{0}, T{0},
														T{0}, T{0});
}
