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
	class Matrix2x2 final
	{
	public:
		class Row final
		{
		public:
			Row(const Row&) = delete;
			Row(Row&&) = delete;

			inline ~Row() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector2<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline T& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline Row(Matrix2x2& matrix, std::size_t rowIndex) noexcept;

			Matrix2x2& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix2x2;
		};

		class ConstRow final
		{
		public:
			ConstRow(const ConstRow&) = delete;
			ConstRow(ConstRow&&) = delete;

			constexpr inline ~ConstRow() noexcept = default;

			[[nodiscard("Pure operator")]]
			constexpr inline operator Vector2<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			constexpr inline const T& operator [](std::size_t columnIndex) const noexcept;

			ConstRow& operator =(const ConstRow&) = delete;
			ConstRow& operator =(ConstRow&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			constexpr inline ConstRow(const Matrix2x2& matrix, std::size_t rowIndex) noexcept;

			const Matrix2x2& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix2x2;
		};

		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(T m00, T m10, T m01, T m11) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(const Vector2<T>& column0, const Vector2<T>& column1) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix2x2(const Matrix2x2& other) noexcept = default;

		constexpr inline ~Matrix2x2() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr inline T& M00() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M00() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M10() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M10() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M01() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M01() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M11() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M11() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T* Data() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T* Data() const noexcept;

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

		inline void Set(T m00, T m10, T m01, T m11) noexcept;

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
		inline Row operator [](std::size_t rowIndex) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr inline ConstRow operator [](std::size_t rowIndex) const noexcept;

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

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order m00, m10, m01, m11.
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
	inline Matrix2x2<T>::Row::Row(Matrix2x2& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::Row::operator Vector2<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline T& Matrix2x2<T>::Row::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.m_components[m_rowIndex + columnIndex * std::size_t{2}];
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::ConstRow::ConstRow(const Matrix2x2& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::ConstRow::operator Vector2<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix2x2<T>::ConstRow::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.m_components[m_rowIndex + columnIndex * std::size_t{2}];
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::Matrix2x2() noexcept :
		Matrix2x2(T{}, T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::Matrix2x2(const T m00, const T m10, const T m01, const T m11) noexcept :
		m_components{m00, m10, m01, m11}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::Matrix2x2(const Vector2<T>& column0, const Vector2<T>& column1) noexcept :
		Matrix2x2(column0.X(), column0.Y(), column1.X(), column1.Y())
	{
	}

	template<Arithmetic T>
	inline constexpr T& Matrix2x2<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix2x2<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix2x2<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix2x2<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix2x2<T>::M01() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix2x2<T>::M01() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix2x2<T>::M11() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix2x2<T>::M11() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline constexpr T* Matrix2x2<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	inline constexpr const T* Matrix2x2<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr inline T Matrix2x2<T>::Determinant() const noexcept
	{
		return M00() * M11() - M01() * M10();
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> Matrix2x2<T>::Adjugate() const noexcept
	{
		return Matrix2x2(M11(), M01(), M10(), M00());
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T> Matrix2x2<T>::Transposed() const noexcept
	{
		return Matrix2x2(M00(), M01(), M10(), M11());
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
			return std::isfinite(M00()) && std::isfinite(M10()) && std::isfinite(M01()) && std::isfinite(M11());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::Set(const T m00, const T m10, const T m01, const T m11) noexcept
	{
		M00() = m00;
		M10() = m10;
		M01() = m01;
		M11() = m11;
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Scale(const Matrix2x2<T>& scale) noexcept
	{
		M00() *= scale.M00();
		M10() *= scale.M10();
		M01() *= scale.M01();
		M11() *= scale.M11();
	}

	template<Arithmetic T>
	Vector2<T> Matrix2x2<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const T x = m_components[rowIndex];
		const T y = m_components[rowIndex + 2];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetRow(const std::size_t rowIndex, const Vector2<T>& value) noexcept
	{
		m_components[rowIndex] = value.X();
		m_components[rowIndex + 2] = value.Y();
	}

	template<Arithmetic T>
	Vector2<T> Matrix2x2<T>::GetColumn(const std::size_t columnIndex) noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{2};

		const T x = m_components[begin];
		const T y = m_components[begin + 1];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetColumn(const std::size_t columnIndex, const Vector2<T>& value) noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{2};

		m_components[begin] = value.X();
		m_components[begin + 1] = value.Y();
	}

	template<Arithmetic T>
	constexpr inline Vector2<T> Matrix2x2<T>::GetDiagonal() const noexcept
	{
		return Vector2<T>(M00(), M11());
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::SetDiagonal(const Vector2<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
	}

	template<Arithmetic T>
	constexpr inline Vector2<T> Matrix2x2<T>::GetCounterDiagonal() const noexcept
	{
		return Vector2<T>(M01(), M10());
	}

	template<Arithmetic T>
	inline void Matrix2x2<T>::SetCounterDiagonal(const Vector2<T>& value) noexcept
	{
		M01() = value.X();
		M10() = value.Y();
	}

	template<Arithmetic T>
	std::string Matrix2x2<T>::ToString() const
	{
		return std::format("({}, {})({}, {})", M00(), M01(), M10(), M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() * right.M00(), left.M10() * right.M10(), left.M01() * right.M01(), left.M11() * right.M11());
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, typename Matrix2x2<T>::ComputationalType tolerance) noexcept
	{
		const Matrix2x2<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.M00() * diff.M00() + diff.M10() * diff.M10() + diff.M01() * diff.M01() + diff.M11() * diff.M11();

		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() + right.M00(), left.M10() + right.M10(), left.M01() + right.M01(), left.M11() + right.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept
	{
		return Matrix2x2<T>(-matrix.M00(), -matrix.M10(), -matrix.M01(), -matrix.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() - right.M00(), left.M10() - right.M10(), left.M01() - right.M01(), left.M11() - right.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const T multiplier) noexcept
	{
		return Matrix2x2<T>(matrix.M00() * multiplier, matrix.M10() * multiplier, matrix.M01() * multiplier, matrix.M11() * multiplier);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M00() * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M10() * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M01() * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M11() * multiplier);

		return Matrix2x2<T>(m00, m10, m01, m11);
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
		const T m00 = left.M00() * right.M00() + left.M01() * right.M10();
		const T m10 = left.M10() * right.M00() + left.M11() * right.M10();
		const T m01 = left.M00() * right.M01() + left.M01() * right.M11();
		const T m11 = left.M10() * right.M01() + left.M11() * right.M11();

		return Matrix2x2<T>(m00, m10, m01, m11);
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept
	{
		const T x = matrix.M00() * vector.X() + matrix.M01() * vector.Y();
		const T y = matrix.M10() * vector.X() + matrix.M11() * vector.Y();

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M00() / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M10() / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M01() / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M11() / divisor);

		return Matrix2x2<T>(m00, m10, m01, m11);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	inline Matrix2x2<T>::Row Matrix2x2<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row(*this, rowIndex);
	}

	template<Arithmetic T>
	constexpr inline Matrix2x2<T>::ConstRow Matrix2x2<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstRow(*this, rowIndex);
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator +=(const Matrix2x2& other) noexcept
	{
		M00() += other.M00();
		M10() += other.M10();
		M01() += other.M01();
		M11() += other.M11();

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator -=(const Matrix2x2& other) noexcept
	{
		M00() -= other.M00();
		M10() -= other.M10();
		M01() -= other.M01();
		M11() -= other.M11();

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		M00() *= multiplier;
		M10() *= multiplier;
		M01() *= multiplier;
		M11() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() * multiplier);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() * multiplier);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() * multiplier);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() * multiplier);

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
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() / divisor);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() / divisor);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() / divisor);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() / divisor);

		return *this;
	}

	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Identity = Matrix2x2<T>(T{1}, T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Zero = Matrix2x2<T>(T{0}, T{0}, T{0}, T{0});
}
